#include <time.h>
#include <internal/syscall.h>
#include <errno.h>



#define SYS_nanosleep 35

int nanosleep(const struct timespec *req, struct timespec *rem) {
    int ret;
    do {
        ret = syscall(SYS_nanosleep, req, rem);
    } while (ret == -1 && errno == EINTR);
    return ret;
}