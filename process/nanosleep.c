#include <time.h>
#include <internal/syscall.h>
#include <errno.h>
//https://elixir.bootlin.com/musl/latest/source/src/time/nanosleep.c
int nanosleep(const struct timespec *req, struct timespec *rem)
{
    return syscall(__NR_nanosleep, req, rem);
}
