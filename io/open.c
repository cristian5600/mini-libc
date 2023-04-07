// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
int open(const char *filename, int flags, ...)
{  va_list arg_list;
    mode_t mode = 0;

 
    if (flags & O_CREAT) {
        va_start(arg_list, flags);
        mode = va_arg(arg_list, mode_t);
        va_end(arg_list);
    }

   
    int ret = syscall(2, filename, flags, mode);
    
    if (ret < 0) {
        
        errno = -ret;
        return -1;
    }
    // Check if the file is opened in write-only mode
    if ((flags & O_WRONLY) || (flags & O_RDWR)) {
        // Check if the file has read permissions
        if (syscall(21,filename, 4) == -1) {
            close(ret);
            errno = EACCES;
            return -1;
        }
    }

    // Check if the file is opened in read-only mode
    if ((flags & O_RDONLY) || (flags & O_RDWR)) {
        // Check if the file has write permissions
        if (syscall(21,filename, 2) == -1) {
            close(ret);
            errno = EACCES;
            return -1;
        }
    }
    

    return ret;
    /*
    va_list arg_list;
    mode_t mode = 0;

    // If O_CREAT flag is specified, get the mode argument
    if (flags & O_CREAT) {
        va_start(arg_list, flags);
        mode = va_arg(arg_list, mode_t);
        va_end(arg_list);
    }

    // Call the system call with the appropriate arguments
    int ret = syscall(2, filename, flags, mode);

    if (ret < 0) {
        if (errno == 0) {
            // Set errno to EINVAL if no specific error was set
            errno = EINVAL;
        }
    }

    return ret; */
}

