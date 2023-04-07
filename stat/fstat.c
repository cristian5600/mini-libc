// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <errno.h>
#include <internal/syscall.h>
int fstat(int fd, struct stat *st)
{
	int ret = syscall(5, fd, st);
    if (ret < 0) {
        errno = -ret;
        return -1;
    }
    return ret;
}
