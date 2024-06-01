// SPDX-License-Identifier: BSD-3-Clause
#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int close(int fd)
{
	//verific daca fd este valid
	if (fd >= 0)
		return 0;
	return -1;
}
