// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int ftruncate(int fd, off_t length)
{
	if (syscall(__NR_ftruncate, fd, length) == 0) {
		return 0;
	} else {
		errno = - syscall(__NR_ftruncate, fd, length);
		return -1;
	}
}
