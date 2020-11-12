# Using from Python {#c_python}

See exempamples [here](https://github.com/grodansparadis/pyvscp/tree/master/vscp) of helperlib usage.

Import with

>import vscp

and then prefix all methods with **vscphelper.**

Example
```python
# Constant
vscpclass = vscp.CLASS1_SECURITY
vscptype = vscp.VSCP_TYPE_PROTOCOL_GENERAL
errcode = VSCP_ERROR_SUCCESS

# Helper
h1 = vscp.pyvscphlp_newSession()
if (0 == h1 ):
    vscp.pyvscphlp_closeSession(h1)
    raise ValueError('Unable to open vscphelp library session')
```


[filename](./bottom_copyright.md ':include')