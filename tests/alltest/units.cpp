// Tests for the measurement unit conversion functions of the helper library:
// the compiled unit table and the expressions loaded at runtime.
//
// The MIT License (MIT)
// Copyright (c) 2000-2026 Ake Hedman, the VSCP project <info@vscp.org>

#include <math.h>
#include <string.h>

#include <vscphelperlib.h>

#include <gtest/gtest.h>

#include <string>

#ifndef VSCP_UNITS_JSON
#error "VSCP_UNITS_JSON must be the path to vscp-units.json"
#endif

static const unsigned short TEMPERATURE = 6;
static const unsigned short PRESSURE    = 12;
static const unsigned short POSITION    = 31;

static bool
near(double a, double b, double rel = 1e-12)
{
  return fabs(a - b) <= rel * (fabs(a) > 1 ? fabs(a) : 1);
}

TEST(UnitTable, Convert)
{
  double r = 0;
  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_convertMeasurementUnit(TEMPERATURE, 2, 1, 212, &r));
  EXPECT_TRUE(near(100, r));
  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_convertMeasurementUnit(PRESSURE, 3, 1, 1, &r));
  EXPECT_TRUE(near(1.01325, r));
  EXPECT_EQ(VSCP_ERROR_NOT_SUPPORTED, vscphlp_convertMeasurementUnit(POSITION, 0, 1, 1, &r));
  EXPECT_EQ(VSCP_ERROR_UNKNOWN_ITEM, vscphlp_convertMeasurementUnit(TEMPERATURE, 0, 7, 1, &r));
  EXPECT_EQ(VSCP_ERROR_INVALID_POINTER, vscphlp_convertMeasurementUnit(TEMPERATURE, 0, 1, 1, NULL));
}

TEST(UnitTable, Info)
{
  char name[32], ascii[16], utf8[16];
  int convertible = -1;
  ASSERT_EQ(VSCP_ERROR_SUCCESS,
            vscphlp_getMeasurementUnitInfo(TEMPERATURE, 1, name, sizeof(name), ascii, sizeof(ascii), utf8,
                                           sizeof(utf8), &convertible));
  EXPECT_STREQ("Celsius", name);
  EXPECT_STREQ("C", ascii);
  EXPECT_STREQ("\xC2\xB0" "C", utf8);
  EXPECT_EQ(1, convertible);
  // Only some of the values, and a buffer that is too small
  ASSERT_EQ(VSCP_ERROR_SUCCESS,
            vscphlp_getMeasurementUnitInfo(POSITION, 1, NULL, 0, NULL, 0, NULL, 0, &convertible));
  EXPECT_EQ(0, convertible);
  char small[3];
  EXPECT_EQ(VSCP_ERROR_BUFFER_TO_SMALL,
            vscphlp_getMeasurementUnitInfo(TEMPERATURE, 1, small, sizeof(small), NULL, 0, NULL, 0, NULL));
  EXPECT_STREQ("", small);
  EXPECT_EQ(VSCP_ERROR_UNKNOWN_ITEM,
            vscphlp_getMeasurementUnitInfo(9999, 0, name, sizeof(name), NULL, 0, NULL, 0, NULL));
}

TEST(UnitTable, Event)
{
  // CLASS2.MEASUREMENT_FLOAT: index, zone, subzone, unit, double MSB first
  unsigned char data[12] = { 0, 0, 0, 1 /* bar */ };
  double v = 2.5;
  unsigned long long bits;
  memcpy(&bits, &v, 8);
  for (int i = 0; i < 8; i++) {
    data[4 + i] = (unsigned char) (bits >> (56 - 8 * i));
  }
  vscpEvent ev;
  memset(&ev, 0, sizeof(ev));
  ev.vscp_class = 1060;
  ev.vscp_type  = PRESSURE;
  ev.sizeData   = sizeof(data);
  ev.pdata      = data;
  double r      = 0;
  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_convertMeasurement(&ev, 0, &r));
  EXPECT_TRUE(near(250000, r));

  vscpEventEx ex;
  memset(&ex, 0, sizeof(ex));
  ex.vscp_class = 1060;
  ex.vscp_type  = PRESSURE;
  ex.sizeData   = sizeof(data);
  memcpy(ex.data, data, sizeof(data));
  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_convertMeasurementEx(&ex, 3 /* atm */, &r));
  EXPECT_TRUE(near(250000 / 101325.0, r));

  ev.vscp_class = 20; // Not a measurement
  EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_convertMeasurement(&ev, 0, &r));
}

TEST(UnitExpressions, EvaluateAndConvert)
{
  double r = 0;
  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_evalUnitExpression("({{{val}}} + 459.67) * 5/9", 32, &r));
  EXPECT_TRUE(near(273.15, r));
  EXPECT_EQ(VSCP_ERROR_INVALID_SYNTAX, vscphlp_evalUnitExpression("2^3", 0, &r));
  EXPECT_EQ(VSCP_ERROR_INVALID_POINTER, vscphlp_evalUnitExpression(NULL, 0, &r));

  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_loadUnitExpressions(VSCP_UNITS_JSON));
  // Same results as the compiled table for every unit pair of a few types
  for (unsigned short type : { TEMPERATURE, PRESSURE, (unsigned short) 13, (unsigned short) 30, (unsigned short) 32 }) {
    for (int a = 0; a < 8; a++) {
      for (int b = 0; b < 8; b++) {
        double rt = 0, re = 0;
        int rvt = vscphlp_convertMeasurementUnit(type, a, b, 21.5, &rt);
        int rve = vscphlp_convertMeasurementUnitExpr(type, a, b, 21.5, &re);
        ASSERT_EQ(rvt, rve) << "type " << type << " " << a << "->" << b;
        if (VSCP_ERROR_SUCCESS == rvt) {
          EXPECT_TRUE(near(rt, re)) << "type " << type << " " << a << "->" << b;
        }
      }
    }
  }

  // A failed load keeps the loaded units
  EXPECT_EQ(VSCP_ERROR_INVALID_PATH, vscphlp_loadUnitExpressions("/no/such/vscp-units.json"));
  EXPECT_EQ(VSCP_ERROR_INVALID_FORMAT, vscphlp_loadUnitExpressionsFromString("{"));
  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_convertMeasurementUnitExpr(TEMPERATURE, 1, 0, 0, &r));
  EXPECT_TRUE(near(273.15, r));

  // Units from a string replace them
  ASSERT_EQ(VSCP_ERROR_SUCCESS,
            vscphlp_loadUnitExpressionsFromString(
              R"({"units":[{"type":500,"unit":0},{"type":500,"unit":1,"conversion0":"{{{val}}}*2","conversion":"{{{val}}}/2"}]})"));
  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_convertMeasurementUnitExpr(500, 1, 0, 4, &r));
  EXPECT_EQ(8, r);
  EXPECT_EQ(VSCP_ERROR_UNKNOWN_ITEM, vscphlp_convertMeasurementUnitExpr(TEMPERATURE, 1, 0, 0, &r));
}
