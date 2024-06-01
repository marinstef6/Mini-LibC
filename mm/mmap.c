// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    //de obicei rezultatul va fi mai mare decat este int-ul si de aceea trebuie cu long
    long result = syscall(__NR_mmap, addr, length, prot, flags, fd, offset);
    if (result < 0) {
        errno = -syscall(__NR_mmap, addr, length, prot, flags, fd, offset);
        return MAP_FAILED;
    }
    //returneaza adresa
    return (void *) result;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	if (syscall(__NR_mremap, old_address, old_size, new_size, flags) < 0) {
        errno = -syscall(__NR_mremap, old_address, old_size, new_size, flags);
        return MAP_FAILED;
    } else {
        return old_address;
    }
}

int munmap(void *addr, size_t length)
{
	if (syscall(__NR_munmap, addr, length) < 0) {
        errno = -syscall(__NR_munmap, addr, length);
        return -1;
    } else {
        return 0;
    }
}
