
#include <time.h>

unsigned int sleep(unsigned int seconds){
  
    struct timespec request, remaining;
    request.tv_sec = seconds;
    request.tv_nsec = 0;
    while (nanosleep(&request, &remaining) == -1) {
        if (remaining.tv_sec == 0 && remaining.tv_nsec == 0) {
            return 0;
        }
        request = remaining;
    }
    return 0;
}
