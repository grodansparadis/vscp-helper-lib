# VSCP Helper library API - Table handling 


## tableCreate

`<code=cpp>`
    int tableCreate( const unsigned char *pTableData ); 
`</code>`

Create table from XML data.

#####  pTableData

Pointer to string containing UTF8 XML definition of table.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableDelete

`<code=cpp>`
    int tableDelete( const unsigned char *pName, int bDeleteFile ); 
`</code>`

Delete named table.

#####  tblName

Name of an existing table.

#####  bDeleteFile

If TRUE (!=0), delete the database **file** as well. Otherwise, it is reused if a table with the same name is created later.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableList

`<code=cpp>`
    int tableList( unsigned char **pLists );
`</code>`

Get a list of all defined tables.

#####  pLists

List of null-terminated strings that will receive table names. The list is allocated on the heap and must be freed by the user. If there are no results, it is set to a NULL pointer.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Pointer to a string containing information about the table. The list is allocated on the heap and must be freed by the user. If there is no result, it is set to a NULL pointer.

##### bXML

If TRUE (!=0), information is returned as Base64-encoded XML data.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGet

`<code=cpp>`
    int tableGet( const unsigned char *pName, 
                                const char *pFrom, 
                                const char *pTo,
                                unsigned char **pResultArray,
                                BOOL bFull ); 
`</code>`

Get data from a named table for a date/time range. You can fetch all columns (bFull) or just the datetime and value (the default).

#####  tblName

Name of an existing table.

#####  from

Start datetime for the data to fetch, in ISO 8601 format YY-MM-DDTHH:MM:SS.

#####  to

End datetime for the data to fetch, in ISO 8601 format YY-MM-DDTHH:MM:SS.

##### pResultArray

List of null-terminated strings that will receive rows, if any, from the table. The list is allocated on the heap and must be freed by the user. If there are no results, it is set to a NULL pointer.

    YY-MM-DDTHH:MM:SSsss, value1[,other fields]`<CR>``<LF>`
    YY-MM-DDTHH:MM:SSsss, value2[,other fields]`<CR>``<LF>`
    YY-MM-DDTHH:MM:SSsss, value3[,other fields]`<CR>``<LF>`
    ...
    YY-MM-DDTHH:MM:SS, valuen[,other fields]`<CR>``<LF>`

##### bFull

If TRUE (!=0), all fields of a table row are returned (//other fields// above) in a comma-separated list. Datetime is always listed first, followed by value, regardless of the table's column order.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetRaw

`<code=cpp>`
    int tableGetRaw( const unsigned char *pName, 
                         const char *pFrom, 
                         const char *pTo,
                         unsigned char **pResultArray ); 
`</code>`

Get data from a named table for a date/time range. All columns of the table are always returned.

#####  tblName

Name of an existing table.

#####  from

Start datetime for the data to fetch, in ISO 8601 format YY-MM-DDTHH:MM:SS.

#####  to

End datetime for the data to fetch, in ISO 8601 format YY-MM-DDTHH:MM:SS.

##### resultArray

List of null-terminated strings that will receive rows, if any, from the table. The list is allocated on the heap and must be freed by the user. If there are no results, it is set to a NULL pointer.

    comma separated row of database columns`<CR>``<LF>`
    comma separated row of database columns`<CR>``<LF>`
    comma separated row of database columns`<CR>``<LF>`
    ...
    comma separated row of database columns`<CR>``<LF>`

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.


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

Pointer to a date/time value. If NULL or empty, the current date and time are used.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableLogSQL

`<code=cpp>`
    int tableLogSQL( const unsigned char *pName, 
                        const unsigned char *psql ); 
`</code>`

Log data using an SQL expression.

#####  tblName

Name of an existing table.

#####  psql

Pointer to a string containing the SQL expression used to log data.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetNumRecords

`<code=cpp>`
    int tableGetNumRecords( const unsigned char *pName, 
                                const char *pFrom, 
                                const char *pTo,
                                size_t *pRecords ); 
`</code>`

Get the number of records for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pRecords

A size_t that will receive the number of records in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetFirstDate

`<code=cpp>`
    int tableGetFirstDate( const unsigned char pName, 
                                const char *pFrom, 
                                const char *pTo,
                                char *pFirst ); 
`</code>`

Get the first date/time for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pFirst

A string buffer that will receive the first date/time in the interval on success. The buffer must hold an ISO-formatted date/time value (YYYY-MM-DDTHH:MM:SS), so it should hold at least twenty characters.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetLastDate

`<code=cpp>`
    int tableGetLastDate( const unsigned char *pName, 
                                const char *pFrom, 
                                const char *pTo,
                                char *pLast ); 
`</code>`

Get the last date/time for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pLast

A string buffer that will receive the last date/time in the interval on success. The buffer must hold an ISO-formatted date/time value (YYYY-MM-DDTHH:MM:SS), so it should hold at least twenty characters.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pSum

Pointer to a double that will receive the sum of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pMin

Pointer to a double that will receive the minimum of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pMax

Pointer to a double that will receive the maximum of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.


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

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pAverage

Pointer to a double that will receive the average of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pMedian

Pointer to a double that will receive the median of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pStdDev

Pointer to a double that will receive the standard deviation of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pVariance

Pointer to a double that will receive the variance of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pMode

Pointer to a double that will receive the mode of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pLowerQ

Pointer to a double that will receive the lower quartile of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pUpperQ

Pointer to a double that will receive the upper quartile of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

\\ 
----
Copyright (c) 2000-2019 [Åke Hedman](mailto/akhe@grodansparadis.com), [Paradise of the Frog / the VSCP Project](https://www.grodansparadis.com)
