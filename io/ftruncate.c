// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>
#include <internal/io.h>
#include <internal/types.h>

int ftruncate(int fd, off_t length) {
    int ret = syscall(77, fd, length);
    if (ret < 0) {
        errno = -ret;
        ret = -1;
    }
    return ret;
}
