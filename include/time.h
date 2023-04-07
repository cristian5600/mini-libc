/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef __TIME_H__
#define __TIME_H__	1

#ifdef __cplusplus
extern "C" {
#endif

#include <internal/types.h>


typedef long time_t;
typedef long clock_t;

/* Define struct tm type for date and time */
struct tm {
    int tm_sec;   /* seconds [0,60] */
    int tm_min;   /* minutes [0,59] */
    int tm_hour;  /* hours [0,23] */
    int tm_mday;  /* day of the month [1,31] */
    int tm_mon;   /* month [0,11] */
    int tm_year;  /* year - 1900 */
    int tm_wday;  /* day of the week [0,6] (Sunday=0) */
    int tm_yday;  /* day in the year [0,365] */
    int tm_isdst; /* daylight saving time */
};

/* Define timespec_t type for representing time in nanoseconds */
typedef struct timespec {
    int64_t tv_sec; /* seconds */
    int64_t tv_nsec; /* nanoseconds */
} timespec;

int nanosleep(const timespec *req, timespec *rem);

#ifdef __cplusplus
}
#endif

#endif

