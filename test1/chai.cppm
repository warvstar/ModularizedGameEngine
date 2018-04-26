export module chai;

export {
import std.core;
#ifdef UNICODE
#define LoadLibrary  LoadLibraryW
#else
#define LoadLibrary  LoadLibraryA
#endif
#ifdef UNICODE
#define FormatMessage  FormatMessageW
#else
#define FormatMessage  FormatMessageA
#endif
#define LPTSTR char *
#define FORMAT_MESSAGE_ALLOCATE_BUFFER 0x00000100
#define FORMAT_MESSAGE_IGNORE_INSERTS  0x00000200
#define FORMAT_MESSAGE_FROM_STRING     0x00000400
#define FORMAT_MESSAGE_FROM_HMODULE    0x00000800
#define FORMAT_MESSAGE_FROM_SYSTEM     0x00001000
#define FORMAT_MESSAGE_ARGUMENT_ARRAY  0x00002000
#define FORMAT_MESSAGE_MAX_WIDTH_MASK  0x000000FF
#define	LANG_NEUTRAL	0x00
#define	SUBLANG_DEFAULT	0x01	/* user default */
#define	MAKELANGID(p, s) ((((uint16_t)(s)) << 10) | (uint16_t)(p))
#define assert
#ifdef WIN32
#define stdin  (__acrt_iob_func(0))
#define stdout (__acrt_iob_func(1))
#define stderr (__acrt_iob_func(2))
#else
#endif
#include "chaiscript.hpp"
}

