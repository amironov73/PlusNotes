### MS-DOS API

https://en.wikipedia.org/wiki/DOS_API

The DOS API is an API which originated with 86-DOS and is used in MS-DOS/PC DOS and other DOS-compatible operating systems. Most calls to the DOS API are invoked using software interrupt 21h (INT 21h). By calling INT 21h with a subfunction number in the AH processor register and other parameters in other registers, various DOS services can be invoked. These include handling keyboard input, video output, disk file access, program execution, memory allocation, and various other activities. In the late 1980s, DOS extenders along with the DOS Protected Mode Interface (DPMI) allow the programs to run in either 16-bit or 32-bit protected mode and still have access to the DOS API.

#### History of the DOS API

The original DOS API in 86-DOS and MS-DOS 1.0 was designed to be functionally compatible with CP/M. Files were accessed using file control blocks (FCBs). The DOS API was greatly extended in MS-DOS 2.0 with several Unix concepts, including file access using file handles, hierarchical directories and device I/O control. In DOS 3.1, network redirector support was added. In MS-DOS 3.31, the INT 25h/26h functions were enhanced to support hard disks greater than 32 MB. MS-DOS 5 added support for using upper memory blocks (UMBs). After MS-DOS 5, the DOS API was unchanged for the successive standalone releases of DOS.

#### The DOS API and Windows

In Windows 9x, DOS loaded the protected-mode system and graphical shell. DOS was usually accessed from a virtual DOS machine (VDM) but it was also possible to boot directly to real mode MS-DOS 7.0 without loading Windows. The DOS API was extended with enhanced internationalization support and long filename support, though the long filename support was only available in a VDM. With Windows 95 OSR2, DOS was updated to 7.1, which added FAT32 support, and functions were added to the DOS API to support this. Windows 98 and Windows ME also implement the MS-DOS 7.1 API, though Windows ME reports itself as MS-DOS 8.0.

Windows NT and the systems based on it (e.g. Windows XP and Windows Vista) are not based on MS-DOS, but use a virtual machine, NTVDM, to handle the DOS API. NTVDM works by running a DOS program in virtual 8086 mode (an emulation of real mode within protected mode available on 80386 and higher processors). NTVDM supports the DOS 5.0 API. DOSEMU for Linux uses a similar approach.

#### Interrupt vectors used by DOS

The following is the list of interrupt vectors used by programs to invoke the DOS API functions.


Interrupt vector | Description | Version | Notes
-----------------|-------------|---------|------
20h | Terminate program | 1.0+ | Implemented in DOS kernel
21h | Main DOS API | 1.0+ | Implemented in DOS kernel
22h | Program terminate address | 1.0+ | Return address in calling program
23h | Control-C handler address | 1.0+ | Default handler is in the command shell (usually COMMAND.COM)
24h | Critical error handler address | 1.0+ | Default handler is in the command shell (usually COMMAND.COM)
25h | Absolute disk read | 1.0+ | Implemented in DOS kernel, enhanced in DOS 3.31 to support up to 2 GB partitions
26h | Absolute disk write | 1.0+ | Implemented in DOS kernel, enhanced in DOS 3.31 to support up to 2 GB partitions
27h | Terminate and stay resident | 1.0+ | Implemented in COMMAND.COM in DOS 1.0, DOS kernel in DOS 2.0+
28h | Idle callout | 2.0+ | Called by DOS kernel when waiting for input
29h | Fast console output | 2.0+ | Implemented by the built-in console device driver or a replacement driver like ANSI.SYS
2Ah | Networking and critical section | 3.0+ | Called by DOS kernel to interface with networking software
2Bh | Unused |  | 
2Ch | Unused |  | 
2Dh | Unused |  | 
2Eh | Reload transient | 2.0+ | Implemented in COMMAND.COM
2Fh | Multiplex | 3.0+ | Implemented in DOS kernel and various programs (PRINT, MSCDEX, DOSKEY, APPEND, etc.) depending on subfunction number

#### DOS INT 21h services

The following is the list of functions provided via the DOS API primary software interrupt vector.

AH | Description | Version
---|-------------|--------
00h | Program terminate | 1.0+
01h | Character input | 1.0+
02h | Character output | 1.0+
03h | Auxiliary input | 1.0+
04h | Auxiliary output | 1.0+
05h | Printer output | 1.0+
06h | Direct console I/O | 1.0+
07h | Direct console input without echo | 1.0+
08h | Console input without echo | 1.0+
09h | Display string | 1.0+
0Ah | Buffered keyboard input | 1.0+
0Bh | Get input status | 1.0+
0Ch | Flush input buffer and input | 1.0+
0Dh | Disk reset | 1.0+
0Eh | Set default drive | 1.0+
0Fh | Open file | 1.0+
10h | Close file | 1.0+
11h | Find first file | 1.0+
12h | Find next file | 1.0+
13h | Delete file | 1.0+
14h | Sequential read | 1.0+
15h | Sequential write | 1.0+
16h | Create or truncate file | 1.0+
17h | Rename file | 1.0+
18h | Reserved | 1.0+
19h | Get default drive | 1.0+
1Ah | Set disk transfer address | 1.0+
1Bh | Get allocation info for default drive | 1.0+
1Ch | Get allocation info for specified drive | 1.0+
1Dh | Reserved | 1.0+
1Eh | Reserved | 1.0+
1Fh | Get disk parameter block for default drive | 1.0+
20h | Reserved | 1.0+
21h | Random read | 1.0+
22h | Random write | 1.0+
23h | Get file size in records | 1.0+
24h | Set random record number | 1.0+
25h | Set interrupt vector | 1.0+
26h | Create PSP | 1.0+
27h | Random block read | 1.0+
28h | Random block write | 1.0+
29h | Parse filename | 1.0+
2Ah | Get date | 1.0+
2Bh | Set date | 1.0+
2Ch | Get time | 1.0+
2Dh | Set time | 1.0+
2Eh | Set verify flag | 1.0+
2Fh | Get disk transfer address | 2.0+
30h | Get DOS version | 2.0+
31h | Terminate and stay resident | 2.0+
32h | Get disk parameter block for specified drive | 2.0+
33h | Get or set Ctrl-Break | 2.0+
34h | Get InDOS flag pointer | 2.0+
35h | Get interrupt vector | 2.0+
36h | Get free disk space | 2.0+
37h | Get or set switch character | 2.0+
38h | Get or set country info | 2.0+
39h | Create subdirectory | 2.0+
3Ah | Remove subdirectory | 2.0+
3Bh | Change current directory | 2.0+
3Ch | Create or truncate file | 2.0+
3Dh | Open file | 2.0+
3Eh | Close file | 2.0+
3Fh | Read file or device | 2.0+
40h | Write file or device | 2.0+
41h | Delete file | 2.0+
42h | Move file pointer | 2.0+
43h | Get or set file attributes | 2.0+
44h | I/O control for devices | 2.0+
45h | Duplicate handle | 2.0+
46h | Redirect handle | 2.0+
47h | Get current directory | 2.0+
48h | Allocate memory | 2.0+
49h | Release memory | 2.0+
4Ah | Reallocate memory | 2.0+
4Bh | Execute program | 2.0+
4Ch | Terminate with return code | 2.0+
4Dh | Get program return code | 2.0+
4Eh | Find first file | 2.0+
4Fh | Find next file | 2.0+
50h | Set current PSP | 2.0+
51h | Get current PSP | 2.0+
52h | Get DOS internal pointers (SYSVARS) | 2.0+
53h | Create disk parameter block | 2.0+
54h | Get verify flag | 2.0+
55h | Create program PSP | 2.0+
56h | Rename file | 2.0+
57h | Get or set file date and time | 2.0+
58h | Get or set allocation strategy | 2.11+
59h | Get extended error info | 3.0+
5Ah | Create unique file | 3.0+
5Bh | Create new file | 3.0+
5Ch | Lock or unlock file | 3.0+
5Dh | File sharing functions | 3.0+
5Eh | Network functions | 3.0+
5Fh | Network redirection functions | 3.0+
60h | Qualify filename | 3.0+
61h | Reserved | 3.0+
62h | Get current PSP | 3.0+
63h | Get DBCS lead byte table pointer | 3.0+
64h | Set wait for external event flag | 3.2+
65h | Get extended country info | 3.3+
66h | Get or set code page | 3.3+
67h | Set handle count | 3.3+
68h | Commit file | 3.3+
69h | Get or set media id | 4.0+
6Ah | Commit file | 4.0+
6Bh | Reserved | 4.0+
6Ch | Extended open/create file | 4.0+



