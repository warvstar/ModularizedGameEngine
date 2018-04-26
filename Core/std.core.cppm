#ifdef _WIN32
#define _WIN32_WINNT 0x0602 //win8
#endif
export module std.core;

export {
#include <windows.h>
#include <signal.h>>
#include <string>
#include <vector>
#include <tuple>
#include <variant>
#include <optional>
#include <string_view>
#include <cctype>
#include <chrono>
#include <unordered_map>
#include <algorithm>
#include <limits.h>
#include <memory>
#include <array>
#include <functional>
#include <locale>
#include <clocale>
#include <iosfwd>
#include <iomanip>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <codecvt>
#include <queue>
#include <filesystem>
#include <experimental\vector>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <thread>
#include <bitset>
#include <ciso646> // and, not, or
#include <forward_list> // forward_list
#include <initializer_list> // initializer_list
#include <atomic>
#include <iostream>
using ui8 = uint8_t;
using ui16 = uint16_t;
using ui32 = uint32_t;
using ui64 = uint64_t;
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using nullptr_t = std::nullptr_t;
}
#define LLONG_MAX     9223372036854775807i64       // maximum signed long long int value
#define LUA_USE_WINDOWS
#define offsetof(s,m) ((size_t)&(((s*)0)->m))
#define RAND_MAX 0x7fff
#define HUGE_VAL   ((double)INFINITY)
#ifndef _HUGE_ENUF
#define _HUGE_ENUF  1e+300  // _HUGE_ENUF*_HUGE_ENUF must overflow
#endif
#define LC_ALL          0
#define LC_COLLATE      1
#define LC_CTYPE        2
#define LC_MONETARY     3
#define LC_NUMERIC      4
#define LC_TIME         5
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define INFINITY   ((float)(_HUGE_ENUF * _HUGE_ENUF))
#define L_tmpnam   260 // _MAX_PATH
#define BUFSIZ  512
#define LLONG_MAX

#define MAX_PATH 260

#define FORMAT_MESSAGE_IGNORE_INSERTS 0x00000200
#define FORMAT_MESSAGE_FROM_SYSTEM 0x00001000
#define CLOCKS_PER_SEC  ((clock_t)1000)
#define LDBL_MANT_DIG 16
#define DBL_MANT_DIG 16
#define _IOFBF 0x0000
#define _IOLBF 0x0040
#define _IONBF 0x0004
#define EOF    (-1)
#define assert()

#define NULL nullptr
#define DBL_MAX_10_EXP 999
#define LC_MIN          LC_ALL
#define LC_MAX          LC_TIME



#if __STDC_WANT_SECURE_LIB__
    #define L_tmpnam_s L_tmpnam 
#endif

#define SEEK_CUR    1
#define SEEK_END    2
#define SEEK_SET    0

#ifdef WIN32
//_ACRTIMP int* __cdecl _errno(void);
#define errno (*_errno())
#define stdin  (__acrt_iob_func(0))
#define stdout (__acrt_iob_func(1))
#define stderr (__acrt_iob_func(2))
#else
#define errno (*__errno())
typedef int sig_atomic_t;
typedef long time_t;
typedef long clock_t;
#endif


export {
#include "luadefines.h"
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#define LUA_CORE
#define LUA_LIB
#define ltable_c
#define lvm_c
#include "luadefines.h"

/* do not export internal symbols */

/* core -- used by all */
#include "lapi.c"
#include "lcode.c"
#include "lctype.c"
#include "ldebug.c"
#include "ldo.c"
#include "ldump.c"
#include "lfunc.c"
#include "lgc.c"
#include "llex.c"
#include "lmem.c"
#include "lobject.c"
#include "lopcodes.c"
#include "lparser.c"
#include "lstate.c"
#include "lstring.c"
#include "ltable.c"
#include "ltm.c"
#include "lundump.c"
#include "lvm.c"
#include "lzio.c"

/* auxiliary library -- used by all */
#include "lauxlib.c"

/* standard library  -- not used by luac */
#ifndef MAKE_LUAC
#include "lbaselib.c"
#include "lbitlib.c"
#include "lcorolib.c"
#include "ldblib.c"
#include "liolib.c"
#include "lmathlib.c"
#include "loadlib.c"
#include "loslib.c"
#include "lstrlib.c"
#include "ltablib.c"
#include "linit.c"
#endif
#include  "lutf8lib.c"
/* lua */
#ifdef MAKE_LUA
#include "lua.c"
#endif

/* luac */
#ifdef MAKE_LUAC
#include "luac.c"
#endif

}