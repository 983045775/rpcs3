#pragma once

#include <cstdint>
#include <cstddef>
#include <immintrin.h>
#include <emmintrin.h>

#define IS_LE_MACHINE 1
#define IS_BE_MACHINE 0

#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

#ifdef _MSC_VER
#define ASSUME(cond) __assume(cond)
#define LIKELY(cond) (cond)
#define UNLIKELY(cond) (cond)
#else
#define ASSUME(cond) do { if (!(cond)) __builtin_unreachable(); } while (0)
#define LIKELY(cond) __builtin_expect(!!(cond), 1)
#define UNLIKELY(cond) __builtin_expect(!!(cond), 0)
#endif

// Some platforms don't support thread_local well yet.
#ifndef _MSC_VER
#define thread_local __thread
#endif

#ifdef _MSC_VER
#define never_inline __declspec(noinline)
#else
#define never_inline __attribute__((noinline))
#endif

#ifdef _MSC_VER
#define force_inline __forceinline
#else
#define force_inline __attribute__((always_inline)) inline
#endif

#if defined(__GNUG__)

#include <stdlib.h>

#define _fpclass(x) std::fpclassify(x)
#define INFINITE 0xFFFFFFFF

#ifdef __APPLE__

// XXX only supports a single timer
#define TIMER_ABSTIME -1
/* The opengroup spec isn't clear on the mapping from REALTIME to CALENDAR
 being appropriate or not.
 http://pubs.opengroup.org/onlinepubs/009695299/basedefs/time.h.html */
#define CLOCK_REALTIME  1 // #define CALENDAR_CLOCK 1 from mach/clock_types.h
#define CLOCK_MONOTONIC 0 // #define SYSTEM_CLOCK 0

typedef int clockid_t;

/* the mach kernel uses struct mach_timespec, so struct timespec
    is loaded from <sys/_types/_timespec.h> for compatability */
// struct timespec { time_t tv_sec; long tv_nsec; };

int clock_gettime(clockid_t clk_id, struct timespec *tp);

#endif /* __APPLE__ */
#endif /* __GNUG__ */

inline std::uint32_t cntlz32(std::uint32_t arg)
{
#if defined(_MSC_VER)
	unsigned long res;
	return _BitScanReverse(&res, arg) ? res ^ 31 : 32;
#else
	return arg ? __builtin_clzll(arg) - 32 : 32;
#endif
}

inline std::uint64_t cntlz64(std::uint64_t arg)
{
#if defined(_MSC_VER)
	unsigned long res;
	return _BitScanReverse64(&res, arg) ? res ^ 63 : 64;
#else
	return arg ? __builtin_clzll(arg) : 64;
#endif
}

// Convert 2-byte string to u16 value like reinterpret_cast does
constexpr std::uint16_t operator""_u16(const char* s, std::size_t length)
{
	return length != 2 ? throw s :
#if IS_LE_MACHINE == 1
		std::uint16_t(s[1]) << 8 | std::uint16_t(s[0]);
#endif
}

// Convert 4-byte string to u32 value like reinterpret_cast does
constexpr std::uint32_t operator""_u32(const char* s, std::size_t length)
{
	return length != 4 ? throw s :
#if IS_LE_MACHINE == 1
		std::uint32_t(s[3]) << 24 | std::uint32_t(s[2]) << 16 | std::uint32_t(s[1]) << 8 | std::uint32_t(s[0]);
#endif
}

// Convert 8-byte string to u64 value like reinterpret_cast does
constexpr std::uint64_t operator""_u64(const char* s, std::size_t length)
{
	return length != 8 ? throw s :
#if IS_LE_MACHINE == 1
		std::uint64_t(s[7]) << 56 | std::uint64_t(s[6]) << 48 | std::uint64_t(s[5]) << 40 | std::uint64_t(s[4]) << 32 |
		std::uint64_t(s[3]) << 24 | std::uint64_t(s[2]) << 16 | std::uint64_t(s[1]) << 8 | std::uint64_t(s[0]);
#endif
}
