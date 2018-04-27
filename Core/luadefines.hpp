#if !defined(LUA_USE_C89) && defined(_WIN32) && !defined(_WIN32_WCE)
#define LUA_USE_WINDOWS  /* enable goodies for regular Windows */
#endif
#if defined(LUA_USE_WINDOWS)
#define LUA_DL_DLL	/* enable support for DLL */
#define LUA_USE_C89	/* broadly, Windows is C89 */
#endif
#if defined(LUA_USE_LINUX)
#define LUA_USE_POSIX
#define LUA_USE_DLOPEN		/* needs an extra library: -ldl */
#define LUA_USE_READLINE	/* needs some extra libraries */
#endif
#if defined(LUA_USE_MACOSX)
#define LUA_USE_POSIX
#define LUA_USE_DLOPEN		/* MacOS does not need -ldl */
#define LUA_USE_READLINE	/* needs an extra library: -lreadline */
#endif
#if defined(LUA_USE_C89) && !defined(LUA_USE_WINDOWS)
#define LUA_C89_NUMBERS
#endif
#if ((INT_MAX >> 15) >> 15) >= 1
#define LUAI_BITSINT	32
#else
/* 'int' always must have at least 16 bits */
#define LUAI_BITSINT	16
#endif
#define LUA_INT_INT		1
#define LUA_INT_LONG		2
#define LUA_INT_LONGLONG	3
#define LUA_FLOAT_FLOAT		1
#define LUA_FLOAT_DOUBLE	2
#define LUA_FLOAT_LONGDOUBLE	3
#if defined(LUA_32BITS)		/* { */
#if LUAI_BITSINT >= 32  /* use 'int' if big enough */
#define LUA_INT_TYPE	LUA_INT_INT
#else  /* otherwise use 'long' */
#define LUA_INT_TYPE	LUA_INT_LONG
#endif
#define LUA_FLOAT_TYPE	LUA_FLOAT_FLOAT
#elif defined(LUA_C89_NUMBERS)	/* }{ */
#define LUA_INT_TYPE	LUA_INT_LONG
#define LUA_FLOAT_TYPE	LUA_FLOAT_DOUBLE
#endif				/* } */
#if !defined(LUA_INT_TYPE)
#define LUA_INT_TYPE	LUA_INT_LONGLONG
#endif
#if !defined(LUA_FLOAT_TYPE)
#define LUA_FLOAT_TYPE	LUA_FLOAT_DOUBLE
#endif
#define LUA_PATH_SEP            ";"
#define LUA_PATH_MARK           "?"
#define LUA_EXEC_DIR            "!"
#define LUA_VDIR	LUA_VERSION_MAJOR "." LUA_VERSION_MINOR
#if defined(_WIN32)	/* { */
#define LUA_LDIR	"!\\lua\\"
#define LUA_CDIR	"!\\"
#define LUA_SHRDIR	"!\\..\\share\\lua\\" LUA_VDIR "\\"
#define LUA_PATH_DEFAULT  \
		LUA_LDIR"?.lua;"  LUA_LDIR"?\\init.lua;" \
		LUA_CDIR"?.lua;"  LUA_CDIR"?\\init.lua;" \
		LUA_SHRDIR"?.lua;" LUA_SHRDIR"?\\init.lua;" \
		".\\?.lua;" ".\\?\\init.lua"
#define LUA_CPATH_DEFAULT \
		LUA_CDIR"?.dll;" \
		LUA_CDIR"..\\lib\\lua\\" LUA_VDIR "\\?.dll;" \
		LUA_CDIR"loadall.dll;" ".\\?.dll"
#else			/* }{ */
#define LUA_ROOT	"/usr/local/"
#define LUA_LDIR	LUA_ROOT "share/lua/" LUA_VDIR "/"
#define LUA_CDIR	LUA_ROOT "lib/lua/" LUA_VDIR "/"
#define LUA_PATH_DEFAULT  \
		LUA_LDIR"?.lua;"  LUA_LDIR"?/init.lua;" \
		LUA_CDIR"?.lua;"  LUA_CDIR"?/init.lua;" \
		"./?.lua;" "./?/init.lua"
#define LUA_CPATH_DEFAULT \
		LUA_CDIR"?.so;" LUA_CDIR"loadall.so;" "./?.so"
#endif			/* } */
#if defined(_WIN32)
#define LUA_DIRSEP	"\\"
#else
#define LUA_DIRSEP	"/"
#endif
#if defined(LUA_BUILD_AS_DLL)	/* { */
#if defined(LUA_CORE) || defined(LUA_LIB)	/* { */
#define LUA_API __declspec(dllexport)
#else						/* }{ */
#define LUA_API __declspec(dllimport)
#endif						/* } */
#else				/* }{ */
#define LUA_API		extern
#endif				/* } */
#define LUALIB_API	LUA_API
#define LUAMOD_API	LUALIB_API
#if defined(__GNUC__) && ((__GNUC__*100 + __GNUC_MINOR__) >= 302) && \
    defined(__ELF__)		/* { */
#define LUAI_FUNC	__attribute__((visibility("hidden"))) extern
#else				/* }{ */
#define LUAI_FUNC	extern
#endif				/* } */
#define LUAI_DDEC	LUAI_FUNC
#define LUAI_DDEF	/* empty */
#if defined(LUA_COMPAT_5_2)	/* { */
#define LUA_COMPAT_MATHLIB
#define LUA_COMPAT_BITLIB
#define LUA_COMPAT_IPAIRS
#define LUA_COMPAT_APIINTCASTS
#endif		
#if defined(LUA_COMPAT_5_1)	/* { */
#define LUA_COMPAT_MATHLIB
#define LUA_COMPAT_APIINTCASTS
#define LUA_COMPAT_UNPACK
#define LUA_COMPAT_LOADERS
#define lua_cpcall(L,f,u) (lua_pushcfunction(L, (f)), lua_pushlightuserdata(L,(u)), lua_pcall(L,1,0,0))
#define LUA_COMPAT_LOG10
#define LUA_COMPAT_LOADSTRING
#define LUA_COMPAT_MAXN
#define lua_strlen(L,i)		lua_rawlen(L, (i))
#define lua_objlen(L,i)		lua_rawlen(L, (i))
#define lua_equal(L,idx1,idx2)		lua_compare(L,(idx1),(idx2),LUA_OPEQ)
#define lua_lessthan(L,idx1,idx2)	lua_compare(L,(idx1),(idx2),LUA_OPLT)
#define LUA_COMPAT_MODULE
#endif
#define l_floor(x)		(l_mathop(floor)(x))
#define lua_number2str(s,sz,n)  l_sprintf((s), sz, LUA_NUMBER_FMT, (LUAI_UACNUMBER)(n))
#define lua_numbertointeger(n,p) ((n) >= (LUA_NUMBER)(LUA_MININTEGER) && (n) < -(LUA_NUMBER)(LUA_MININTEGER) && (*(p) = (LUA_INTEGER)(n), 1))
#if LUA_FLOAT_TYPE == LUA_FLOAT_FLOAT		/* { single float */
#define LUA_NUMBER	float
#define l_mathlim(n)		(FLT_##n)
#define LUAI_UACNUMBER	double
#define LUA_NUMBER_FRMLEN	""
#define LUA_NUMBER_FMT		"%.7g"
#define l_mathop(op)		op##f
#define lua_str2number(s,p)	strtof((s), (p))
#elif LUA_FLOAT_TYPE == LUA_FLOAT_LONGDOUBLE	/* }{ long double */
#define LUA_NUMBER	long double
#define l_mathlim(n)		(LDBL_##n)
#define LUAI_UACNUMBER	long double
#define LUA_NUMBER_FRMLEN	"L"
#define LUA_NUMBER_FMT		"%.19Lg"
#define l_mathop(op)		op##l
#define lua_str2number(s,p)	strtold((s), (p))
#elif LUA_FLOAT_TYPE == LUA_FLOAT_DOUBLE	/* }{ double */
#define LUA_NUMBER	double
#define l_mathlim(n)		(DBL_##n)
#define LUAI_UACNUMBER	double
#define LUA_NUMBER_FRMLEN	""
#define LUA_NUMBER_FMT		"%.14g"
#define l_mathop(op)		op
#define lua_str2number(s,p)	strtod((s), (p))
#else						/* }{ */
#error "numeric float type not defined"
#endif					/* } */
#define LUA_INTEGER_FMT		"%" LUA_INTEGER_FRMLEN "d"
#define LUAI_UACINT		LUA_INTEGER
#define lua_integer2str(s,sz,n)  \
	l_sprintf((s), sz, LUA_INTEGER_FMT, (LUAI_UACINT)(n))
#define LUA_UNSIGNED		unsigned LUAI_UACINT
#if LUA_INT_TYPE == LUA_INT_INT		/* { int */
#define LUA_INTEGER		int
#define LUA_INTEGER_FRMLEN	""
#define LUA_MAXINTEGER		INT_MAX
#define LUA_MININTEGER		INT_MIN
#elif LUA_INT_TYPE == LUA_INT_LONG	/* }{ long */
#define LUA_INTEGER		long
#define LUA_INTEGER_FRMLEN	"l"
#define LUA_MAXINTEGER		LONG_MAX
#define LUA_MININTEGER		LONG_MIN
#elif LUA_INT_TYPE == LUA_INT_LONGLONG	/* }{ long long */
#if defined(LLONG_MAX)		/* { */
#define LUA_INTEGER		long long
#define LUA_INTEGER_FRMLEN	"ll"
#define LUA_MAXINTEGER		LLONG_MAX
#define LUA_MININTEGER		LLONG_MIN
#elif defined(LUA_USE_WINDOWS) /* }{ */
#define LUA_INTEGER		__int64
#define LUA_INTEGER_FRMLEN	"I64"
#define LUA_MAXINTEGER		_I64_MAX
#define LUA_MININTEGER		_I64_MIN
#else				/* }{ */
#error "Compiler does not support 'long long'. Use option '-DLUA_32BITS' \
  or '-DLUA_C89_NUMBERS' (see file 'luaconf.h' for details)"
#endif				/* } */
#else				/* }{ */
#error "numeric integer type not defined"
#endif				/* } */
#if !defined(LUA_USE_C89)
#define l_sprintf(s,sz,f,i)	snprintf(s,sz,f,i)
#else
#define l_sprintf(s,sz,f,i)	((void)(sz), sprintf(s,f,i))
#endif
#if !defined(LUA_USE_C89)
#define lua_strx2number(s,p)		lua_str2number(s,p)
#endif
#if !defined(LUA_USE_C89)
#define lua_number2strx(L,b,sz,f,n)  \
	((void)L, l_sprintf(b,sz,f,(LUAI_UACNUMBER)(n)))
#endif
#if defined(LUA_USE_C89) || (defined(HUGE_VAL) && !defined(HUGE_VALF))
#undef l_mathop  /* variants not available */
#undef lua_str2number
#define l_mathop(op)		(lua_Number)op  /* no variant */
#define lua_str2number(s,p)	((lua_Number)strtod((s), (p)))
#endif
#define LUA_KCONTEXT	ptrdiff_t
#if !defined(LUA_USE_C89) && defined(__STDC_VERSION__) && \
    __STDC_VERSION__ >= 199901L
#include <stdint.h>
#if defined(INTPTR_MAX)  /* even in C99 this type is optional */
#undef LUA_KCONTEXT
#define LUA_KCONTEXT	intptr_t
#endif
#endif
#if !defined(lua_getlocaledecpoint)
#define lua_getlocaledecpoint()		(localeconv()->decimal_point[0])
#endif
#if defined(LUA_USE_APICHECK)
#include <assert.h>
#define luai_apicheck(l,e)	assert(e)
#endif
#if LUAI_BITSINT >= 32
#define LUAI_MAXSTACK		1000000
#else
#define LUAI_MAXSTACK		15000
#endif
#define LUA_EXTRASPACE		(sizeof(void *))
#define LUA_IDSIZE	60
#if LUA_FLOAT_TYPE == LUA_FLOAT_LONGDOUBLE
#define LUAL_BUFFERSIZE		8192
#else
#define LUAL_BUFFERSIZE   ((int)(0x80 * sizeof(void*) * sizeof(lua_Integer)))
#endif
#define LUA_QL(x)	"'" x "'"
#define LUA_QS		LUA_QL("%s")
#define LUA_VERSION_MAJOR	"5"
#define LUA_VERSION_MINOR	"3"
#define LUA_VERSION_NUM		503
#define LUA_VERSION_RELEASE	"4"
#define LUA_VERSION	"Lua " LUA_VERSION_MAJOR "." LUA_VERSION_MINOR
#define LUA_RELEASE	LUA_VERSION "." LUA_VERSION_RELEASE
#define LUA_COPYRIGHT	LUA_RELEASE "  Copyright (C) 1994-2017 Lua.org, PUC-Rio"
#define LUA_AUTHORS	"R. Ierusalimschy, L. H. de Figueiredo, W. Celes"
#define LUA_SIGNATURE	"\x1bLua"
#define LUA_MULTRET	(-1)
#define LUA_REGISTRYINDEX	(-LUAI_MAXSTACK - 1000)
#define lua_upvalueindex(i)	(LUA_REGISTRYINDEX - (i))
#define LUA_OK		0
#define LUA_YIELD	1
#define LUA_ERRRUN	2
#define LUA_ERRSYNTAX	3
#define LUA_ERRMEM	4
#define LUA_ERRGCMM	5
#define LUA_ERRERR	6
#define LUA_TNONE		(-1)
#define LUA_TNIL		0
#define LUA_TBOOLEAN		1
#define LUA_TLIGHTUSERDATA	2
#define LUA_TNUMBER		3
#define LUA_TSTRING		4
#define LUA_TTABLE		5
#define LUA_TFUNCTION		6
#define LUA_TUSERDATA		7
#define LUA_TTHREAD		8
#define LUA_NUMTAGS		9
#define LUA_MINSTACK	20
#define LUA_RIDX_MAINTHREAD	1
#define LUA_RIDX_GLOBALS	2
#define LUA_RIDX_LAST		LUA_RIDX_GLOBALS
#if defined(LUA_USER_H)
#include LUA_USER_H
#endif
#define LUA_OPADD	0	/* ORDER TM, ORDER OP */
#define LUA_OPSUB	1
#define LUA_OPMUL	2
#define LUA_OPMOD	3
#define LUA_OPPOW	4
#define LUA_OPDIV	5
#define LUA_OPIDIV	6
#define LUA_OPBAND	7
#define LUA_OPBOR	8
#define LUA_OPBXOR	9
#define LUA_OPSHL	10
#define LUA_OPSHR	11
#define LUA_OPUNM	12
#define LUA_OPBNOT	13
#define LUA_OPEQ	0
#define LUA_OPLT	1
#define LUA_OPLE	2
#define lua_call(L,n,r)		lua_callk(L, (n), (r), 0, NULL)
#define lua_pcall(L,n,r,f)	lua_pcallk(L, (n), (r), (f), 0, NULL)
#define lua_yield(L,n)		lua_yieldk(L, (n), 0, NULL)
#define LUA_GCSTOP		0
#define LUA_GCRESTART		1
#define LUA_GCCOLLECT		2
#define LUA_GCCOUNT		3
#define LUA_GCCOUNTB		4
#define LUA_GCSTEP		5
#define LUA_GCSETPAUSE		6
#define LUA_GCSETSTEPMUL	7
#define LUA_GCISRUNNING		9
#define lua_getextraspace(L)	((void *)((char *)(L) - LUA_EXTRASPACE))
#define lua_tonumber(L,i)	lua_tonumberx(L,(i),NULL)
#define lua_tointeger(L,i)	lua_tointegerx(L,(i),NULL)
#define lua_pop(L,n)		lua_settop(L, -(n)-1)
#define lua_newtable(L)		lua_createtable(L, 0, 0)
#define lua_register(L,n,f) (lua_pushcfunction(L, (f)), lua_setglobal(L, (n)))
#define lua_pushcfunction(L,f)	lua_pushcclosure(L, (f), 0)
#define lua_isfunction(L,n)	(lua_type(L, (n)) == LUA_TFUNCTION)
#define lua_istable(L,n)	(lua_type(L, (n)) == LUA_TTABLE)
#define lua_islightuserdata(L,n)	(lua_type(L, (n)) == LUA_TLIGHTUSERDATA)
#define lua_isnil(L,n)		(lua_type(L, (n)) == LUA_TNIL)
#define lua_isboolean(L,n)	(lua_type(L, (n)) == LUA_TBOOLEAN)
#define lua_isthread(L,n)	(lua_type(L, (n)) == LUA_TTHREAD)
#define lua_isnone(L,n)		(lua_type(L, (n)) == LUA_TNONE)
#define lua_isnoneornil(L, n)	(lua_type(L, (n)) <= 0)
#define lua_pushliteral(L, s)	lua_pushstring(L, "" s)
#define lua_pushglobaltable(L)  \
	((void)lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS))
#define lua_tostring(L,i)	lua_tolstring(L, (i), NULL)
#define lua_insert(L,idx)	lua_rotate(L, (idx), 1)
#define lua_remove(L,idx)	(lua_rotate(L, (idx), -1), lua_pop(L, 1))
#define lua_replace(L,idx)	(lua_copy(L, -1, (idx)), lua_pop(L, 1))
#if defined(LUA_COMPAT_APIINTCASTS)
#define lua_pushunsigned(L,n)	lua_pushinteger(L, (lua_Integer)(n))
#define lua_tounsignedx(L,i,is)	((lua_Unsigned)lua_tointegerx(L,i,is))
#define lua_tounsigned(L,i)	lua_tounsignedx(L,(i),NULL)
#endif
#define LUA_HOOKCALL	0
#define LUA_HOOKRET	1
#define LUA_HOOKLINE	2
#define LUA_HOOKCOUNT	3
#define LUA_HOOKTAILCALL 4
#define LUA_MASKCALL	(1 << LUA_HOOKCALL)
#define LUA_MASKRET	(1 << LUA_HOOKRET)
#define LUA_MASKLINE	(1 << LUA_HOOKLINE)
#define LUA_MASKCOUNT	(1 << LUA_HOOKCOUNT)
#define LUA_VERSUFFIX          "_" LUA_VERSION_MAJOR "_" LUA_VERSION_MINOR
#define LUA_COLIBNAME	"coroutine"
#define LUA_TABLIBNAME	"table"
#define LUA_IOLIBNAME	"io"
#define LUA_OSLIBNAME	"os"
#define LUA_STRLIBNAME	"string"
#define LUA_UTF8LIBNAME	"utf8"
#define LUA_BITLIBNAME	"bit32"
#define LUA_MATHLIBNAME	"math"
#define LUA_DBLIBNAME	"debug"
#define LUA_LOADLIBNAME	"package"
#if !defined(lua_assert)
#define lua_assert(x)	((void)0)
#endif
#define LUA_ERRFILE     (LUA_ERRERR+1)
#define LUA_LOADED_TABLE	"_LOADED"
#define LUA_PRELOAD_TABLE	"_PRELOAD"
#define LUAL_NUMSIZES	(sizeof(lua_Integer)*16 + sizeof(lua_Number))
#define luaL_checkversion(L)  \
	  luaL_checkversion_(L, LUA_VERSION_NUM, LUAL_NUMSIZES)
#define LUA_NOREF       (-2)
#define LUA_REFNIL      (-1)
#define luaL_loadfile(L,f)	luaL_loadfilex(L,f,NULL)
#define luaL_newlibtable(L,l)	\
  lua_createtable(L, 0, sizeof(l)/sizeof((l)[0]) - 1)
#define luaL_newlib(L,l)  \
  (luaL_checkversion(L), luaL_newlibtable(L,l), luaL_setfuncs(L,l,0))
#define luaL_argcheck(L, cond,arg,extramsg)	\
		((void)((cond) || luaL_argerror(L, (arg), (extramsg))))
#define luaL_checkstring(L,n)	(luaL_checklstring(L, (n), NULL))
#define luaL_optstring(L,n,d)	(luaL_optlstring(L, (n), (d), NULL))
#define luaL_typename(L,i)	lua_typename(L, lua_type(L,(i)))
#define luaL_dofile(L, fn) \
	(luaL_loadfile(L, fn) || lua_pcall(L, 0, LUA_MULTRET, 0))
#define luaL_dostring(L, s) \
	(luaL_loadstring(L, s) || lua_pcall(L, 0, LUA_MULTRET, 0))
#define luaL_getmetatable(L,n)	(lua_getfield(L, LUA_REGISTRYINDEX, (n)))
#define luaL_opt(L,f,n,d)	(lua_isnoneornil(L,(n)) ? (d) : f(L,(n)))
#define luaL_loadbuffer(L,s,sz,n)	luaL_loadbufferx(L,s,sz,n,NULL)
#define luaL_addchar(B,c) \
  ((void)((B)->n < (B)->size || luaL_prepbuffsize((B), 1)), \
   ((B)->b[(B)->n++] = (c)))
#define luaL_addsize(B,s)	((B)->n += (s))
#define luaL_prepbuffer(B)	luaL_prepbuffsize(B, LUAL_BUFFERSIZE)
#define LUA_FILEHANDLE          "FILE*"
#if defined(LUA_COMPAT_MODULE)
LUALIB_API void (luaL_pushmodule)(lua_State *L, const char *modname,
	LUALIB_API void (luaL_openlib)(lua_State *L, const char *libname,
		const luaL_Reg *l, int nup);
#define luaL_register(L,n,l)	(luaL_openlib(L,(n),(l),0))
#endif
#if !defined(lua_writestring)
#define lua_writestring(s,l)   fwrite((s), sizeof(char), (l), stdout)
#endif
#if !defined(lua_writeline)
#define lua_writeline()        (lua_writestring("\n", 1), fflush(stdout))
#endif
#if !defined(lua_writestringerror)
#define lua_writestringerror(s,p) \
        (fprintf(stderr, (s), (p)), fflush(stderr))
#endif
#if defined(LUA_COMPAT_APIINTCASTS)
#define luaL_checkunsigned(L,a)	((lua_Unsigned)luaL_checkinteger(L,a))
#define luaL_optunsigned(L,a,d)	\
	((lua_Unsigned)luaL_optinteger(L,a,(lua_Integer)(d)))
#define luaL_checkint(L,n)	((int)luaL_checkinteger(L, (n)))
#define luaL_optint(L,n,d)	((int)luaL_optinteger(L, (n), (d)))
#define luaL_checklong(L,n)	((long)luaL_checkinteger(L, (n)))
#define luaL_optlong(L,n,d)	((long)luaL_optinteger(L, (n), (d)))
#endif