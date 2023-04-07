// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	// return if no memory is allocated to the destination
    if (destination == NULL) {
        return NULL;
    }
 
    // take a pointer pointing to the beginning of the destination string
    char *ptr = destination;
 
    // copy the C-string pointed by source into the array
    // pointed by destination
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
 
    // include the terminating null character
    *destination = '\0';
 
    // the destination is returned by standard `strcpy()`
    return ptr;
	//return destination;
}

char *strncpy(char *destination, const char *source, size_t num)
{
	 // return if no memory is allocated to the destination
    if (destination == NULL) {
        return NULL;
    }
 
    // take a pointer pointing to the beginning of the destination string
    char* ptr = destination;
 
    // copy first `num` characters of C-string pointed by source
    // into the array pointed by destination
    while (*source && num--)
    {
        *destination = *source;
        destination++;
        source++;
    }
 
    // null terminate destination string
    *destination = '\0';
 
    // the destination is returned by standard `strncpy()`
    return ptr;
}

char *strcat(char *destination, const char *source)
{
	// make `ptr` point to the end of the destination string
    char* ptr = destination + strlen(destination);
 
    // appends characters of the source to the destination string
    while (*source != '\0') {
        *ptr++ = *source++;
    }
 
    // null terminate destination string
    *ptr = '\0';
 
    // the destination is returned by standard `strcat()`
    return destination;
}

char *strncat(char *destination, const char *source, size_t num)
{
	 // make `ptr` point to the end of the destination string
    char* ptr = destination + strlen(destination);
 
    // Appends characters of the source to the destination string
    while (*source != '\0' && num--) {
        *ptr++ = *source++;
    }
 
    // null terminate destination string
    *ptr = '\0';
 
    // destination string is returned by standard `strncat()`
    return destination;
}

int strcmp(const char *X, const char *Y)
{
	 while (*X)
    {
        // if characters differ, or end of the second string is reached
        if (*X != *Y) {
            break;
        }
 
        // move to the next pair of characters
        X++;
        Y++;
    }
 
    // return the ASCII difference after converting `char*` to `unsigned char*`
    return *(const unsigned char*)X - *(const unsigned char*)Y;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
	while ( n && *s1 && ( *s1 == *s2 ) )
    {
        ++s1;
        ++s2;
        --n;
    }
    if ( n == 0 )
    {
        return 0;
    }
    else
    {
        return ( *(unsigned char *)s1 - *(unsigned char *)s2 );
    }
}

size_t strlen(const char *str)
{
	/*size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i; */
	size_t count = 0;
    while(*str!='\0')
    {
        count++;
        str++;
    }
    return count;
}

char *strchr(const char *str, int c)
{
	while(*str != c && *str != '\0') {
      str++;
   }
   if(*str == c) {
      return str;
   }else {
      return NULL;
}
}

char *strrchr(const char *str, int c)
{
	char *isCharFind = NULL;
    //handling null pointer
    if(str != NULL)
    {
        do
        {
            if( *str == (char)c )
            {
                isCharFind=str;
            }
        }
        while(*str++);
    }
    return isCharFind;
}

char *strstr(const char *haystack, const char *needle)
{
	
    return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	static char* ptr;

    ptr = haystack;

    while (*ptr) {
        if (strncmp(ptr, needle, strlen(needle)) == 0)
            return ptr;
        ptr++;
    }
    return NULL;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	char *csrc = (char *)source; 
char *cdest = (char *)destination; 
  
// Copy contents of src[] to dest[] 
for (int i=0; i<num; i++) 
    cdest[i] = csrc[i];

	return NULL;
}

void *memmove(void *destination, const void *source, size_t num)
{
    return memcpy(destination, source, num);
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	 unsigned char *p = ptr1;
    unsigned char *q = ptr2;
    int charCompareStatus = 0;
    //If both pointer pointing same memory block
    if (ptr1 == ptr2)
    {
        return charCompareStatus;
    }
    while (num > 0)
    {
        if (*p != *q)
        {  //compare the mismatching character
            charCompareStatus = (*p >*q)?1:-1;
            break;
        }
        num--;
        p++;
        q++;
    }
    return charCompareStatus;
}

void *memset(void *source, int value, size_t num)
{
	unsigned char* p=source;
    while(num--)
    {
        *p++ = (unsigned char)value;
    }
    return source;
};
