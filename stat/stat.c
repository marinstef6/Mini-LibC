// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <fcntl.h>
#include <errno.h>

int stat(const char *restrict path, struct stat *restrict buf)
{
	if (syscall(__NR_stat, path, buf) == 0) {
		return 0;
	} else {
		errno = - syscall(__NR_stat, path, buf);
		return -1;
	}
}
