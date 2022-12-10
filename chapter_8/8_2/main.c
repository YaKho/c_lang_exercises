#include <fcntl.h>
#include <stdlib.h>
#include "syscalls.h"

#define PERMS 0666

FILE _iob[OPEN_MAX] = {
	{ 0, (char *) 0, (char *) 0, { ._READ = 1 }, 0 },
	{ 0, (char *) 0, (char *) 0, { ._WRITE = 1 }, 1 },
	{ 0, (char *) 0, (char *) 0, { ._WRITE = 1, ._UNBUF = 1 }, 2 }
};

FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if (fp->_flags._READ == 0 && fp->_flags._WRITE == 0)
			break;
	if (fp >= _iob + OPEN_MAX)
		return NULL;
	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->_flags._READ = fp->_flags._WRITE = fp->_flags._UNBUF = 
		fp->_flags._EOF = fp->_flags._ERR = 0;
	if (*mode == 'r')
		fp->_flags._READ = 1;
	else
		fp->_flags._WRITE = 1;
	return fp;
}

int _fillbuf(FILE *fp)
{
	int bufsize;
	if (fp->_flags._READ == 0 || fp->_flags._EOF == 1 || fp->_flags._ERR == 1)
		return EOF;
	bufsize = (fp->_flags._UNBUF == 1) ? 1 : BUFSIZ;
	if (fp->base == NULL)
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->_flags._EOF = 1;
		else
			fp->_flags._ERR = 1;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}
