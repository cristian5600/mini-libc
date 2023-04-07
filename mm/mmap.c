// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#include <internal/mm/mem_list.h>
	void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    
    if (syscall(72,fd, 3) < 0 && !(flags & 0x20)) { //F_GETFL =3
        errno = EBADF;
        return MAP_FAILED;
    }
    if(fd == -1 && ((flags == 0x20))){
        errno = EINVAL;
        return MAP_FAILED;
    }
    void *ret = (void*)syscall(9, addr, length, prot, flags, fd, offset);

    if (ret == MAP_FAILED) {
        errno = EINVAL;
    }

    return ret;
}
	/* void *ret = syscall(9, addr, length, prot, flags, fd, offset);
    if (ret == MAP_FAILED) {
        errno = EINVAL;
        return MAP_FAILED;
    }
    return ret; */
	// write(1,"\nmmap\n",6);
	/* TODO: Implement mmap(). */
	//return syscall(9,addr,length,prot,flags,fd,offset);
	
	// return MAP_FAILED;


void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
   
    
	void *new_address;
    
    // Check if old_address is NULL
    if (old_address == NULL) {
        errno = EINVAL;
        return MAP_FAILED;
    }
    
    // Check if new_size is zero
    if (new_size == 0) {
        munmap(old_address, old_size);
        return NULL;
    }
    
    // Resize memory block
    new_address =(void*) syscall(25,old_address, old_size, new_size, flags);
    if (new_address == MAP_FAILED) {
        return MAP_FAILED;
    }
    
    return new_address; 

}

int munmap(void *addr, size_t length)
{
	int ret = syscall(11, addr, length);
    if (ret < 0) {
        errno = -ret;
        return -1;
    }

    
    struct mem_list *item = mem_list_find(addr);
    if (item != NULL) {
        mem_list_del(item);
    }

    return ret; 

    return 0; 
}

