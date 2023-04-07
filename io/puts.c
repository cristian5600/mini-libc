#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
// #include <io.h>
#ifndef EOF
# define EOF (-1)
#endif
int puts(const char *string){
     int i = 0;
    while(string[i])
    {
        if(write(1, &string[i], 1) == -1)  // Use write() instead of putchar()
        { 
            return EOF;
        }
        i++;
    }
    if(write(1, "\n", 1) == -1)
    {
        return EOF;
    }
    return 1;
}

