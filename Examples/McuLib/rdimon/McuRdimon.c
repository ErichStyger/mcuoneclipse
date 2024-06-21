/*!
** \file McuRdimon.c
** \brief Implementation of the Remote Debugger Interface.
*/         

/* Support files for GNU libc.
   Implementation has been used from 
   gcc-arm-none-eabi-10.3-2021.10-src\gcc-arm-none-eabi-10.3-2021.10\src\newlib\libgloss\arm\syscalls.c
   and adapted and simplifying using the McuSemihost library.
  */

#include "McuRdimon.h"

#if McuRdimon_CONFIG_IS_ENABLED
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <errno.h>
#include <unistd.h>

#include "McuSemihost.h"

int	_stat		(const char *, struct stat *);

/* Struct used to keep track of the file position, just so we
   can implement fseek(fh,x,SEEK_CUR).  */
struct fdent {
  int handle; /* file handle */
  int pos; /* position in file */
};

#define MAX_OPEN_FILES 20

/* User file descriptors (fd) are integer indexes into 
   the openfiles[] array. Error checking is done by using
   findslot(). 

   This openfiles array is manipulated directly by only 
   these 5 functions:

	findslot() - Translate entry.
	newslot() - Find empty entry.
	initialise_monitor_handles() - Initialize entries.
	_swiopen() - Initialize entry.
	_close() - Handle stdout == stderr case.

   Every other function must use findslot().  */

static struct fdent openfiles [MAX_OPEN_FILES];

static int monitor_stdin;
static int monitor_stdout;
static int monitor_stderr;

/* Return a pointer to the structure associated with
   the user file descriptor fd. */ 
static struct fdent*findslot (int fd) {
  /* User file descriptor is out of range. */
  if ((unsigned int)fd >= MAX_OPEN_FILES) {
    return NULL;
  }
  /* User file descriptor is open? */
  if (openfiles[fd].handle == -1) {
    return NULL;
  }
  /* Valid. */
  return &openfiles[fd];
}

/* Return the next lowest numbered free file 
   structure, or -1 if we can't find one. */ 
static int newslot (void) {
  int i;

  for (i = 0; i < MAX_OPEN_FILES; i++) {
    if (openfiles[i].handle == -1) {
      break;
    }
  }
  if (i == MAX_OPEN_FILES) {
    return -1;
  }
  return i;
}

static int get_errno (void) {
  return McuSemihost_SysErrNo();
}

/* Set errno and return result. */
static int error (int result) {
  errno = get_errno ();
  return result;
}

/* fh, is a valid internal file handle.
   ptr, is a null terminated string.
   len, is the length in bytes to read. 
   Returns the number of bytes *not* written. */
int _swiread (int fh, void * ptr, size_t len) {
  return McuSemihost_SysFileRead(fh, ptr, len);
}

/* fd, is a valid user file handle.
   Translates the return of _swiread into
   bytes read. */
int __attribute__((weak)) _read (int fd, void * ptr, size_t len) {
  int res;
  struct fdent *pfd;

  pfd = findslot (fd);
  if (pfd == NULL) {
    errno = EBADF;
    return -1;
  }
  res = _swiread (pfd->handle, ptr, len);
  if (res == -1) {
    return res;
  }
  pfd->pos += len - res;
  /* res == len is not an error, 
     at least if we want feof() to work.  */
  return len - res;
}

/* fd, is a user file descriptor. */
off_t _swilseek (int fd, off_t ptr, int dir) {
  off_t res;
  struct fdent *pfd;

  /* Valid file descriptor? */
  pfd = findslot (fd);
  if (pfd == NULL) {
    errno = EBADF;
    return -1;
  }
  /* Valid whence? */
  if ((dir != SEEK_CUR)
      && (dir != SEEK_SET)
      && (dir != SEEK_END))
  {
    errno = EINVAL;
    return -1;
  }
  /* Convert SEEK_CUR to SEEK_SET */
  if (dir == SEEK_CUR) {
    ptr = pfd->pos + ptr;
    /* The resulting file offset would be negative. */
    if (ptr < 0) {
      errno = EINVAL;
      if ((pfd->pos > 0) && (ptr > 0)) {
        errno = EOVERFLOW;
      }
      return -1;
    }
    dir = SEEK_SET;
  }
  if (dir == SEEK_END) {
    res = McuSemihost_SysFileLen(pfd->handle);
    if (res == -1) {
      return -1;
    }
    ptr += res;
  }
  /* This code only does absolute seeks.  */
  res = McuSemihost_SysFileSeek(pfd->handle, (int)ptr);
  /* At this point ptr is the current file position. */
  if (res >= 0) {
    pfd->pos = ptr;
    return ptr;
  } else {
    return -1;
  }
}

off_t _lseek (int fd, off_t ptr, int dir) {
  return _swilseek (fd, ptr, dir);
}

/* fh, is a valid internal file handle.
   Returns the number of bytes *not* written. */
int _swiwrite (int fh, const void * ptr, size_t len) {
  return McuSemihost_SysFileWrite(fh, ptr, len);
}

/* fd, is a user file descriptor. */
int __attribute__((weak)) _write (int fd, const void * ptr, size_t len) {
  int res;
  struct fdent *pfd;

  pfd = findslot (fd);
  if (pfd == NULL) {
    errno = EBADF;
    return -1;
  }
  res = _swiwrite (pfd->handle, ptr,len);
  /* Clearly an error. */
  if (res < 0) {
    return -1;
  }
  pfd->pos += len - res;
  /* We wrote 0 bytes? 
     Retrieve errno just in case. */
  if ((len - res) == 0) {
    return error (0);
  }
  return (len - res);
}

int _swiopen (const char *path, int flags) {
  int aflags = 0, fh;
 
  int fd = newslot ();
  if (fd == -1) {
    errno = EMFILE;
    return -1;
  }
  /* It is an error to open a file that already exists. */
  if ((flags & O_CREAT) && (flags & O_EXCL)) {
    struct stat st;
    int res;
    res = _stat(path, &st);
    if (res != -1) {
      errno = EEXIST;
      return -1;
    }
  }
  /* The flags are Unix-style, so we need to convert them.  */
#ifdef O_BINARY
  if (flags & O_BINARY)
    aflags |= SYS_FILE_MODE_READBINARY;
#endif
  /* In O_RDONLY we expect aflags == 0. */
  if (flags & O_RDWR) {
    aflags |= SYS_FILE_MODE_READWRITE;
  }
  if ((flags & O_CREAT)
      || (flags & O_TRUNC)
      || (flags & O_WRONLY))
  {
    aflags |= SYS_FILE_MODE_WRITE;
  }
  if (flags & O_APPEND) {
    aflags &= ~SYS_FILE_MODE_WRITE; /* Can't ask for w AND a; means just 'a'.  */
    aflags |= SYS_FILE_MODE_APPEND;
  }
  fh = McuSemihost_SysFileOpen((const unsigned char*)path, aflags);
  /* Return a user file descriptor or an error. */
  if (fh >= 0) {
    openfiles[fd].handle = fh;
    openfiles[fd].pos = 0;
    return fd;
  } else {
    return error (fh);
  }
}

int _open (const char * path, int flags, ...) {
  return _swiopen (path, flags);
}

int _close (int fd) {
  int res;
  struct fdent *pfd;

  pfd = findslot (fd);
  if (pfd == NULL) {
    errno = EBADF;
    return -1;
  }
  /* Handle stderr == stdout. */
  if ((fd == 1 || fd == 2)
      && (openfiles[1].handle == openfiles[2].handle))
  {
    pfd->handle = -1;
    return 0;
  }

  /* Attempt to close the handle. */
  res = McuSemihost_SysFileClose(pfd->handle);
  /* Reclaim handle? */
  if (res == 0) {
    pfd->handle = -1;
  }
  return res;
}

int _swistat (int fd, struct stat * st) {
  struct fdent *pfd;
  int res;

  pfd = findslot (fd);
  if (pfd == NULL) {
    errno = EBADF;
    return -1;
  }
  /* Always assume a character device,
     with 1024 byte blocks. */
  st->st_mode |= S_IFCHR;
  st->st_blksize = 1024;
  res = McuSemihost_SysFileLen(pfd->handle);
  if (res == -1) {
    return -1;
  }
  st->st_size = res; /* set the file size. */
  return 0;
}

int __attribute__((weak)) _fstat (int fd, struct stat * st) {
  memset (st, 0, sizeof (*st));
  return _swistat (fd, st);
}

int __attribute__((weak)) _stat (const char *fname, struct stat *st) {
  int fd, res;
  memset (st, 0, sizeof (* st));
  /* The best we can do is try to open the file readonly.  If it exists,
     then we can guess a few things about it.  */
  if ((fd = _open (fname, O_RDONLY)) == -1) {
    return -1;
  }
  #ifndef S_IREAD /* define locally, e.g. because __BSD_VISIBLE might not be set to 1 */
    #define	S_IREAD		0000400	/* read permission, owner */
  #endif
  st->st_mode |= S_IFREG | S_IREAD;
  res = _swistat (fd, st);
  /* Not interested in the error.  */
  _close (fd); 
  return res;
}

int _unlink (const char *path) {
#if McuSemihost_CONFIG_HAS_SYS_REMOVE
  int res;
  res = McuSemihost_SysFileRemove((const unsigned char*)path);
  if (res == -1) {
    return error (res);
  }
  return 0;
#else
  return -1;
#endif
}

int _gettimeofday (struct timeval * tp, void * tzvp) {
  struct timezone *tzp = tzvp;
  if (tp) {
  /* Ask the host for the seconds since the Unix epoch.  */
    tp->tv_sec = McuSemihost_SysHostTime();
    tp->tv_usec = 0;
  }
  /* Return fixed data for the timezone.  */
  if (tzp) {
    tzp->tz_minuteswest = 0;
    tzp->tz_dsttime = 0;
  }
  return 0;
}

/* Return a clock that ticks at 100Hz.  */
clock_t _clock (void) {
  clock_t timeval;

  timeval = McuSemihost_SysHostClock();
  return timeval;
}

/* Return a clock that ticks at 100Hz.  */
clock_t _times (struct tms * tp) {
  clock_t timeval = _clock();
  if (tp) {
    tp->tms_utime  = timeval;	/* user time */
    tp->tms_stime  = 0;	/* system time */
    tp->tms_cutime = 0;	/* user time, children */
    tp->tms_cstime = 0;	/* system time, children */
  }
  return timeval;
};

int _isatty (int fd) {
  struct fdent *pfd;
  int tty;

  pfd = findslot (fd);
  if (pfd == NULL) {
    errno = EBADF;
    return 0;
  }
  tty = McuSemihost_SysIsTTY(pfd->handle);
  if (tty == 1) {
    return 1;
  }
  errno = get_errno();
  return 0;
}

int _rename (const char *oldpath, const char *newpath) {
#if McuSemihost_CONFIG_HAS_SYS_RENAME
  return McuSemihost_SysFileRename((const unsigned char*)oldpath, (const unsigned char*)newpath);
#else
  return -1;
#endif
}

void McuRdimon_Init(void) {
  /* Open the standard file descriptors by opening the special
   * teletype device, ":tt", read-only to obtain a descriptor for
   * standard input and write-only to obtain a descriptor for standard
   * output. Finally, open ":tt" in append mode to obtain a descriptor
   * for standard error. Since this is a write mode, most kernels will
   * probably return the same value as for standard output, but the
   * kernel can differentiate the two using the mode flag and return a
   * different descriptor for standard error.
   */
  monitor_stdin = McuSemihost_SysFileOpen((unsigned char*)":tt", SYS_FILE_MODE_READ); /* stdin */
  monitor_stdout = McuSemihost_SysFileOpen((unsigned char*)":tt", SYS_FILE_MODE_WRITE); /* stdout */
  monitor_stderr = McuSemihost_SysFileOpen((unsigned char*)":tt", SYS_FILE_MODE_APPEND); /* stderr */
  for (int i = 0; i < MAX_OPEN_FILES; i ++) {
    openfiles[i].handle = -1;
  }

  /* If we failed to open stderr, redirect to stdout. */
  if (monitor_stderr == -1) {
    monitor_stderr = monitor_stdout;
  }
  openfiles[0].handle = monitor_stdin;
  openfiles[0].pos = 0;
  openfiles[1].handle = monitor_stdout;
  openfiles[1].pos = 0;
  openfiles[2].handle = monitor_stderr;
  openfiles[2].pos = 0;
}

#endif /* McuRdimon_CONFIG_IS_ENABLED */
