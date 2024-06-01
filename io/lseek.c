// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

off_t lseek(int fd, off_t offset, int whence)
{
	if (fd >= 0 && whence >= 0 && whence <= 2 && offset >= 0) {
		return syscall(__NR_lseek, fd, offset, whence);
	} else {
		errno = - syscall(__NR_lseek, fd, offset, whence);
		return -1;
	}
}
