// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>
#include <internal/io.h>
#include <internal/types.h>
off_t lseek(int fd, off_t offset, int whence)
{
	/* off_t ret = syscall(8, fd, offset, whence);
    if (ret < 0) {
        errno = -ret;
        return (off_t)-1;
    }
    return ret; */
	off_t ret = syscall(8, fd, offset, whence);
    if (ret < 0) {
        if (ret == -1) {
            errno = EINVAL;
        } else {
            errno = -ret;
        }
        return (off_t)-1;
    }
    return ret;
}
