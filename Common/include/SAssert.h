#pragma once
#include <stdio.h>
#include <assert.h>

#ifdef ST_RELEASE
#include <Windows.h>
#endif

#ifndef ST_REPORT_ERROR
	#ifdef ST_DEBUG
	#define ST_REPORT_ERROR(msg)     							\
	{							   								\
		::_wassert(_CRT_WIDE(msg), _CRT_WIDE(__FILE__), __LINE__);	\
	}
	#else
	#define ST_REPORT_ERROR(msg)    							\
	{							   								\
		printf("Assertion failed: %s, file %s, line %d\n", msg, __FILE__, __LINE__);	\
		MessageBoxA(NULL, "An Error has occured in the Program\n\nAbort will be called\n\nFurther information in console", "Error", MB_ICONERROR | MB_OK); \
		abort();\
	}
	#endif // ST_DEBUG
#endif // !ST_REPORT_ERROR

#ifndef ST_VERIFY
#define ST_VERIFY(expr, msg)                                 \
if (!(expr)) {                                               \
	ST_REPORT_ERROR(msg);                                    \
}                                   
#endif // !ST_VERIFY

#ifndef ST_ASSERT
#define ST_ASSERT(expr, msg) ST_VERIFY(expr, msg)
#endif // !ST_ASSERT