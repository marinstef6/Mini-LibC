// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	if (syscall(__NR_open, filename, flags) > 0) {
		return syscall(__NR_open, filename, flags);
	} else {
		errno = - syscall(__NR_open, filename, flags);
		return -1;
	}
}
