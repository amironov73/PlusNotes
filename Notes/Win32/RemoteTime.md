### Как получить время с другого компьютера

Вот так: https://docs.microsoft.com/en-us/windows/win32/api/lmremutl/nf-lmremutl-netremotetod

```c
#include <stdio.h>
#include <windows.h>
#include <lm.h>
 
#pragma comment(lib, "netapi32.lib")
 
#ifndef UNICODE
#define UNICODE
#endif
 
int wmain (int argc, wchar_t *argv[])
{
    LPTIME_OF_DAY_INFO pBuf = NULL;
    NET_API_STATUS nStatus;
    LPTSTR pszServerName = NULL;
 
    if (argc > 2)
    {
        fwprintf (stderr, L"Usage: %s [\\\\ServerName]\n", argv[0]);
        exit (1);
    }
 
    // The server is not the default local computer.
    if (argc == 2) {
        pszServerName = (LPTSTR) argv[1];
    }
 
    nStatus = NetRemoteTOD
        (
            (LPCWSTR) pszServerName,
            (LPBYTE *) &pBuf
        );
 
    // If the function succeeds, display the current date and time.
    if (nStatus == NERR_Success) {
        if (pBuf != NULL) {
            fprintf (stdout, "\nThe current date is: %02lu/%02lu/%04lu\n",
                    pBuf->tod_month, pBuf->tod_day, pBuf->tod_year);
            fprintf (stderr, "The current time is: %02lu:%02lu:%02lu\n",
                    pBuf->tod_hours, pBuf->tod_mins, pBuf->tod_secs);
        }
    }
 
    // Otherwise, display a system error.
    else {
        fprintf (stderr, "A system error has occurred: %lu\n", nStatus);
    }
 
    // Free the allocated buffer.
    if (pBuf != NULL) {
        NetApiBufferFree (pBuf);
    }
 
    return 0;
}
```
