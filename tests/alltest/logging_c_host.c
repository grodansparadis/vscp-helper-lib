#include <vscphelperlib.h>

int main(void)
{
    const char* version = vscphlp_getVersionString();
    if (NULL == version || '\0' == version[0]) {
        return 1;
    }

    if (VSCP_ERROR_SUCCESS != vscphlp_configureLogging(
                                  VSCPHELPER_LOG_LEVEL_OFF,
                                  VSCPHELPER_LOG_LEVEL_OFF,
                                  NULL,
                                  0,
                                  0)) {
        return 2;
    }

    return VSCP_ERROR_SUCCESS == vscphlp_disableLogging() ? 0 : 3;
}
