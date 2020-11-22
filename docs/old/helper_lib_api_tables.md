# VSCP Helper library API - Table handling 


## tableCreate

`<code=cpp>`
    int tableCreate( const unsigned char *pTableData ); 
`</code>`

Create table from XML data.

#####  pTableData

Pointer to string containing UTF8 XML definition of table.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableDelete

`<code=cpp>`
    int tableDelete( const unsigned char *pName, int bDeleteFile ); 
`</code>`

Delete named table.

#####  tblName

Name of an existing table.

#####  bDeleteFile

If TRUE (!=0) the database **file** also should be deleted. If not it will be reused if a table with the same name is created later.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableList

`<code=cpp>`
    int tableList( unsigned char **pLists );
`</code>`

Get a list of all defined tables.

#####  pLists

List of null terminated strings that will get filled with table names. The list is allocated on the heap and must be freed by the user. If no result is returned set to a NULL pointer.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableListInfo

`<code=cpp>`
    int tableListInfo( const unsigned char *pName, 
                            unsigned char *pTableInfo, 
                            int bXML ); 
`</code>`

Delete named table.

#####  tblName

Name of an existing table.

#####  pTableInfo

Pointer to string that contain information about the table. The list is allocated on the heap and must be freed by the user. If no result is returned set to a NULL pointer.

##### bXML

If TREU (!=0) info will be returned as BASE64 encoded XML data.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGet

`<code=cpp>`
    int tableGet( const unsigned char *pName, 
                                const char *pFrom, 
                                const char *pTo,
                                unsigned char **pResultArray,
                                BOOL bFull ); 
`</code>`

Get data from a named table in a range to-from. One can fetch all columns of the table (bFull) or just datetime and value (default).

#####  tblName

Name of an existing table.

#####  from

Datetime from which data should be fetched. Should be given on ISO 8601 format YY-MM-DDTHH:MM:SS. 

#####  to

Datetime up to which data is fetched. Should be given on ISO 8601 format YY-MM-DDTHH:MM:SS. 

##### pResultArray

List of null terminated strings that will get filled with rows (if any) from the table. The list is allocated on the heap and must be freed by the user. If no result is returned set to a NULL pointer.

    YY-MM-DDTHH:MM:SSsss, value1[,other fields]`<CR>``<LF>`
    YY-MM-DDTHH:MM:SSsss, value2[,other fields]`<CR>``<LF>`
    YY-MM-DDTHH:MM:SSsss, value3[,other fields]`<CR>``<LF>`
    ...
    YY-MM-DDTHH:MM:SS, valuen[,other fields]`<CR>``<LF>`

##### bFull

If TREU (!=0) all fields of a table row is returned (//other fields// above) in a comma separated list. Note that datetime is always listed first followed by value regardless of how the columns of the table is arranged.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetRaw

`<code=cpp>`
    int tableGetRaw( const unsigned char *pName, 
                         const char *pFrom, 
                         const char *pTo,
                         unsigned char **pResultArray ); 
`</code>`

Get data from a named table in a range to-from. All columns of the table is always returned.

#####  tblName

Name of an existing table.

#####  from

Datetime from which data should be fetched. Should be given on ISO 8601 format YY-MM-DDTHH:MM:SS. 

#####  to

Datetime up to which data is fetched. Should be given on ISO 8601 format YY-MM-DDTHH:MM:SS. 

##### resultArray

List of null terminated strings that will get filled with rows (if any) from the table. The list is allocated on the heap and must be freed by the user. If no result is returned set to a NULL pointer.

    comma separated row of database columns`<CR>``<LF>`
    comma separated row of database columns`<CR>``<LF>`
    comma separated row of database columns`<CR>``<LF>`
    ...
    comma separated row of database columns`<CR>``<LF>`

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.


## tableLog

`<code=cpp>`
    int tableLog( const unsigned char *pName, 
                        double value, 
                        char *pdt ); 
`</code>`

Log a value, date/time pair to a table.

#####  tblName

Name of an existing table.

#####  value

Value to log. 

#####  pdt

Pointer to date/time value. Can be NULL (or empty) and in which case the current date/time is used. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableLogSQL

`<code=cpp>`
    int tableLogSQL( const unsigned char *pName, 
                        const unsigned char *psql ); 
`</code>`

Log data to with a SQL expression. 

#####  tblName

Name of an existing table.

#####  psql

Pointer to string that contain SQL expression used to log data. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetNumRecords

`<code=cpp>`
    int tableGetNumRecords( const unsigned char *pName, 
                                const char *pFrom, 
                                const char *pTo,
                                size_t *pRecords ); 
`</code>`

Get number of records for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pRecords

size_t that will get number of records in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetFirstDate

`<code=cpp>`
    int tableGetFirstDate( const unsigned char pName, 
                                const char *pFrom, 
                                const char *pTo,
                                char *pFirst ); 
`</code>`

Get the first data/time for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pFirst

A string buffer that will get the first date/time in the interval on success. The buffer is supposed to hold a ISO formatted date/time value (YYYY-MM-DDTHH:MM:SS) so it should be able to hold at least twenty characters.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetLastDate

`<code=cpp>`
    int tableGetLastDate( const unsigned char *pName, 
                                const char *pFrom, 
                                const char *pTo,
                                char *pLast ); 
`</code>`

Get the last data/time for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pLast

A string buffer that will get the last date/time in the interval on success. The buffer is supposed to hold a ISO formatted date/time value (YYYY-MM-DDTHH:MM:SS) so it should be able to hold at least twenty characters.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetSum

`<code=cpp>`
    int tableGetSum( const unsigned char *pName, 
                        const char *pFrom, 
                        const char *pTo,
                        double *pSum ); 
`</code>`

Get the sum of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pSum

Pointer to a double that will get the sum of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetMin

`<code=cpp>`
    int tableGetMin( const unsigned char *pName, 
                        const char *pFrom, 
                        const char *pTo,
                        double *pMin ); 
`</code>`

Get the minimum of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pMin

Pointer to a double that will get the minimum of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetMax

`<code=cpp>`
    int tableGetMax( const unsigned char *pName, 
                        const char *pFrom, 
                        const char *pTo,
                        double *pMax ); 
`</code>`

Get the maximum of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pMax

Pointer to a double that will get the maximum of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.


## tableGetAverage

`<code=cpp>`
    int tableGetAverage( const unsigned char *pName, 
                            const char *pFrom, 
                            const char *pTo,
                            double *pAverage ); 
`</code>`

Get the average of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pAverage

Pointer to a double that will get the average of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetMedian

`<code=cpp>`
    int tableGetMedian( const unsigned char *pName, 
                            const char *pFrom, 
                            const char *pTo,
                            double *pMedian ); 
`</code>`

Get the median (middle/second quartile) of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pMedian

Pointer to a double that will get the median of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetStdDev

`<code=cpp>`
    int tableGetStdDev( const unsigned char *pName, 
                            const char *pFrom, 
                            const char *pTo,
                            double *pStdDev ); 
`</code>`

Get the standard deviation of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pStdDev

Pointer to a double that will get the standard deviation of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetVariance

`<code=cpp>`
    int tableGetVariance( const unsigned char *pName, 
                            const char *pFrom, 
                            const char *pTo,
                            double *pVariance ); 
`</code>`

Get the variance of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pVariance

Pointer to a double that will get the variance of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetMode

`<code=cpp>`
    int tableGetMode( const unsigned char *pName, 
                            const char *pFrom, 
                            const char *pTo,
                            double *pMode ); 
`</code>`

Get the mode of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pMode

Pointer to a double that will get the mode of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetLowerQ

`<code=cpp>`
    int tableGetLowerQ( const unsigned char *pName, 
                            const char *pFrom, 
                            const char *pTo,
                            double *pLowerQ ); 
`</code>`

Get the lower/first quartile of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pLowerQ

Pointer to a double that will get the lower quartile of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetUpperQ

`<code=cpp>`
    int tableGetUpperQ( const unsigned char *pName, 
                            const char *pFrom, 
                            const char *pTo,
                            double *pUpperQ ); 
`</code>`

Get the upper/third quartile of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pUpperQ

Pointer to a double that will get the upper quartile of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableClear

`<code=cpp>`
    int tableClear( const unsigned char *pName, 
                            const char *pFrom, 
                            const char *pTo ); 
`</code>`

Remove all records in an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

\\ 
----
Copyright (c) 2000-2019 [Åke Hedman](mailto/akhe@grodansparadis.com), [Paradise of the Frog / Grodans Paradis AB](https://www.grodansparadis.com)
