#include <time.h>
#include <internal/syscall.h>
#include <errno.h>
int sleep(unsigned int seconds)
{
    struct timespec req = {seconds, 0};
    struct timespec rem;
    int ret = nanosleep(&req, &rem);
    if (ret == -1)
    {
       return rem.tv_sec;
    }
    return 0;
}
