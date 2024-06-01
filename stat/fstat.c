// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <errno.h>

int fstat(int fd, struct stat *st)
{
	if (syscall(__NR_fstat, fd, st) == 0) {
		return 0;
	} else {
		errno = - syscall(__NR_fstat, fd, st);
		return -1;
	}
}
