// Tests for helper functions that the header declared but the library did
// not implement before: data from strings, event time, encryption tokens and
// legacy (version 0) frame writing and encryption.
//
// The MIT License (MIT)
// Copyright (c) 2000-2026 Ake Hedman, the VSCP project <info@vscp.org>

#include <string.h>

#include <vscphelperlib.h>

#include <gtest/gtest.h>

#include <vector>

TEST(DataFromString, EventAndArray)
{
  unsigned char data[512];
  unsigned short size = 0;
  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getVscpDataArrayFromString(data, &size, "1,2,0x10,255"));
  ASSERT_EQ(4, size);
  EXPECT_EQ(0x10, data[2]);
  EXPECT_EQ(255, data[3]);
  EXPECT_EQ(VSCP_ERROR_INVALID_POINTER, vscphlp_getVscpDataArrayFromString(NULL, &size, "1"));

  vscpEvent* pev = new vscpEvent;
  memset(pev, 0, sizeof(vscpEvent));
  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getVscpDataFromString(pev, "7,8,9"));
  ASSERT_EQ(3, pev->sizeData);
  ASSERT_NE(nullptr, pev->pdata);
  EXPECT_EQ(9, pev->pdata[2]);
  vscphlp_deleteVSCPevent(pev);
  EXPECT_EQ(VSCP_ERROR_INVALID_POINTER, vscphlp_getVscpDataFromString(NULL, "1"));
}

TEST(EventTime, SetToNow)
{
  vscpEvent ev;
  memset(&ev, 0, sizeof(ev));
  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setEventToNow(&ev));
  EXPECT_GE(ev.year, 2024);
  EXPECT_GE(ev.month, 1);
  EXPECT_LE(ev.month, 12);
  EXPECT_GE(ev.day, 1);

  vscpEventEx ex;
  memset(&ex, 0, sizeof(ex));
  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setEventExToNow(&ex));
  EXPECT_GE(ex.year, 2024);
  EXPECT_EQ(VSCP_ERROR_INVALID_POINTER, vscphlp_setEventToNow(NULL));
  EXPECT_EQ(VSCP_ERROR_INVALID_POINTER, vscphlp_setEventExToNow(NULL));
}

TEST(EncryptionTokens, BothWays)
{
  int code = -1;
  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getEncryptionCodeFromToken("AES192", &code));
  EXPECT_EQ(2, code);
  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getEncryptionCodeFromToken(" aes256 ", &code));
  EXPECT_EQ(3, code);
  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getEncryptionCodeFromToken("", &code));
  EXPECT_EQ(0, code);
  EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_getEncryptionCodeFromToken("DES", &code));

  char token[16];
  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getEncryptionTokenFromCode(1, token, sizeof(token)));
  EXPECT_STREQ("AES128", token);
  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getEncryptionTokenFromCode(0, token, sizeof(token)));
  EXPECT_STREQ("", token);
  EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_getEncryptionTokenFromCode(4, token, sizeof(token)));
  char small[4];
  EXPECT_EQ(VSCP_ERROR_BUFFER_TO_SMALL, vscphlp_getEncryptionTokenFromCode(3, small, sizeof(small)));
}

static std::vector<unsigned char>
frameFor(const vscpEvent& ev)
{
  size_t size = vscphlp_getUDpFrameSizeFromEvent(const_cast<vscpEvent*>(&ev));
  std::vector<unsigned char> frame(size);
  EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_writeEventToUdpFrame(frame.data(), frame.size(), 0, &ev));
  return frame;
}

TEST(Frames, WriteEventAndEventEx)
{
  unsigned char data[] = { 1, 2, 3 };
  vscpEvent ev;
  memset(&ev, 0, sizeof(ev));
  ev.vscp_class = 10;
  ev.vscp_type  = 6;
  ev.sizeData   = sizeof(data);
  ev.pdata      = data;
  std::vector<unsigned char> frame = frameFor(ev);
  ASSERT_EQ(38u + sizeof(data), frame.size()); // Header, GUID, size, data, CRC
  EXPECT_EQ(0x10, frame[0]); // Frame type 1 (event) in the high nibble, encryption 0
  EXPECT_EQ(10, (frame[14] << 8) | frame[15]);
  EXPECT_EQ(6, (frame[16] << 8) | frame[17]);
  EXPECT_EQ(3, (frame[34] << 8) | frame[35]);
  EXPECT_EQ(3, frame[38]);

  vscpEventEx ex;
  memset(&ex, 0, sizeof(ex));
  ex.vscp_class = 10;
  ex.vscp_type  = 6;
  ex.sizeData   = sizeof(data);
  memcpy(ex.data, data, sizeof(data));
  ASSERT_EQ(frame.size(), vscphlp_getUDpFrameSizeFromEventEx(&ex));
  std::vector<unsigned char> frameEx(frame.size());
  ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_writeEventExToUdpFrame(frameEx.data(), frameEx.size(), 0, &ex));
  EXPECT_EQ(frame, frameEx);

  // Too small a buffer, NULL pointers
  EXPECT_NE(VSCP_ERROR_SUCCESS, vscphlp_writeEventToUdpFrame(frame.data(), 10, 0, &ev));
  EXPECT_EQ(VSCP_ERROR_INVALID_POINTER, vscphlp_writeEventToUdpFrame(NULL, 10, 0, &ev));
  EXPECT_EQ(0u, vscphlp_getUDpFrameSizeFromEvent(NULL));
}

TEST(Frames, EncryptDecryptRoundTrip)
{
  unsigned char data[] = { 0x11, 0x22, 0x33, 0x44, 0x55 };
  vscpEvent ev;
  memset(&ev, 0, sizeof(ev));
  ev.vscp_class = 20;
  ev.vscp_type  = 3;
  ev.sizeData   = sizeof(data);
  ev.pdata      = data;
  std::vector<unsigned char> frame = frameFor(ev);

  unsigned char key[32];
  unsigned char iv[16];
  for (int i = 0; i < 32; i++) {
    key[i] = (unsigned char) i;
  }
  for (int i = 0; i < 16; i++) {
    iv[i] = (unsigned char) (0xa0 + i);
  }
  for (unsigned char algorithm = 1; algorithm <= 3; algorithm++) {
    std::vector<unsigned char> encrypted(frame.size() + 32);
    ASSERT_EQ(VSCP_ERROR_SUCCESS,
              vscphlp_encryptVscpUdpFrame(encrypted.data(), frame.data(), frame.size(), key, iv, algorithm));
    EXPECT_EQ(algorithm, encrypted[0] & 0x0f);
    const size_t encryptedLen = 1 + 16 * ((frame.size() - 1) / 16 + 1) + 16;
    EXPECT_EQ(0, memcmp(encrypted.data() + encryptedLen - 16, iv, 16)) << "IV is appended";
    EXPECT_NE(0, memcmp(encrypted.data() + 1, frame.data() + 1, frame.size() - 1)) << "payload is encrypted";

    std::vector<unsigned char> decrypted(encryptedLen + 32);
    ASSERT_EQ(VSCP_ERROR_SUCCESS,
              vscphlp_decryptVscpUdpFrame(decrypted.data(), encrypted.data(), encryptedLen, key, NULL, algorithm));
    EXPECT_EQ(0, memcmp(decrypted.data() + 1, frame.data() + 1, frame.size() - 1)) << "algorithm " << int(algorithm);

    // A wrong key does not give the frame back
    unsigned char wrong[32];
    memcpy(wrong, key, 32);
    wrong[0] ^= 1;
    std::vector<unsigned char> bad(encryptedLen + 32);
    int rv = vscphlp_decryptVscpUdpFrame(bad.data(), encrypted.data(), encryptedLen, wrong, NULL, algorithm);
    EXPECT_TRUE((VSCP_ERROR_SUCCESS != rv) || (0 != memcmp(bad.data() + 1, frame.data() + 1, frame.size() - 1)));
  }
  EXPECT_EQ(VSCP_ERROR_INVALID_POINTER, vscphlp_encryptVscpUdpFrame(NULL, frame.data(), frame.size(), key, iv, 1));
  EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_decryptVscpUdpFrame(frame.data(), frame.data(), 0, key, iv, 1));
}
