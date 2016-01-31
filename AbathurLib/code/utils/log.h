#ifndef INC_LOG_H
#define INC_LOG_H

#pragma once

#include <stdio.h>
#include <cassert>

/////////////
// asserts //
/////////////

#define ASSERT(condition)          assert(condition);
#define ASSERT_MSG(condition, ...) ASSERT(condition)

#if _MSC_VER >= 1600
#define STATIC_ASSERT_MESSAGE(condition, errMessage) static_assert(condition, errMessage)
#define STATIC_ASSERT(condition) STATIC_ASSERT_MESSAGE(condition, "ERROR_STATIC_ASSERT")
#else
template<bool> struct CompileTimeChecker;
template<> struct CompileTimeChecker<false> { CompileTimeChecker() {} };
template<> struct CompileTimeChecker<true> { CompileTimeChecker(...) {} };

#define STATIC_ASSERT(condition) { class ERROR_STATIC_ASSERT{}; CompileTimeChecker< (condition) != 0 > compile_test( (ERROR_STATIC_ASSERT())); }
#define STATIC_ASSERT_MESSAGE(condition, errMessage) STATIC_ASSERT(condition)
#endif

//////////
// Logs //
//////////

#define LOG( place, log ) printf("[ %s ] %s", place , log );

#endif // INC_LOG_H