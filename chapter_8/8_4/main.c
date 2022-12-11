#include <fcntl.h>
#include <stdlib.h>
#include "syscalls.h"

#define PERMS 0666

FILE *fopen(char *name, char *mode);
int fclose(FILE *fp);
int fseek(FILE *fp, long offset, int origin);

int main(int argc, char const *argv[])
{
	FILE *fp;
	int c;
	if ((fp = fopen("t.txt", "w")) != NULL) {
		putc('a', fp);
		putc('d', fp);
		if (fclose(fp) == EOF)
			putchar('e');
	}
	if ((fp = fopen("t.txt", "r")) != NULL) {
		if (fseek(fp, 1L, SEEK_SET)) {
			putchar('e');
			return -1;
		}
		c = getc(fp);
		putchar(c);
		if (fclose(fp) == EOF)
			putchar('e');
	}

	return 0;
}

FILE _iob[OPEN_MAX] = {
	{ 0, (char *) 0, (char *) 0, _READ, 0 },
	{ 0, (char *) 0, (char *) 0, _WRITE, 1 },
	{ 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
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
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}

int _fillbuf(FILE *fp)
{
	int bufsize;
	if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
		return EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL)
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

int _flushbuf(int c, FILE *fp)
{
	int num, bufsize;
	unsigned char uc = c;

	if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
		return EOF;
	if (fp->base == NULL && ((fp->flag & _UNBUF) == 0)) {
		if ((fp->base = malloc(BUFSIZ)) == NULL)
			fp->flag |= _UNBUF;
		else {
			fp->ptr = fp->base;
			fp->cnt = BUFSIZ - 1;
		}
	}
	if (fp->flag & _UNBUF) {
		fp->ptr = fp->base = NULL;
		fp->cnt = 0;
		if (c == EOF)
			return EOF;
		num = write(fp->fd, &uc, 1);
		bufsize = 1;
	} else {
		if (c != EOF)
			*fp->ptr++ = uc;
		bufsize = (int)(fp->ptr - fp->base);
		num = write(fp->fd, fp->base, bufsize);
		fp->ptr = fp->base;
		fp->cnt = BUFSIZ - 1;
	}
	if (num == bufsize)
		return c;
	else {
		fp->flag |= _ERR;
		return EOF;
	}
}

int fflush(FILE *fp)
{
	int i, retval = 0;

	if (fp == NULL) {
		for (i = 0; i < OPEN_MAX; i++) {
			if ((_iob[i].flag & _WRITE) && (fflush(&_iob[i]) == -1))
				retval = -1;
		}
	} else {
		if ((fp->flag & _WRITE) == 0)
			return -1;
		_flushbuf(EOF, fp);
		if (fp->flag & _ERR)
			retval = -1;
	}
	return retval;
}

int fclose(FILE *fp)
{
	int fd;
	if (fp == NULL)
		return -1;
	fd = fp->fd;
	fflush(fp);
	fp->cnt = 0;
	fp->ptr = NULL;
	if (fp->base != NULL)
		free(fp->base);
	fp->base = NULL;
	fp->flag = 0;
	fp->fd = -1;
	return close(fd);
}

int fseek(FILE *fp, long offset, int origin)
{
	if (fp == NULL || fp < _iob || fp >= _iob + OPEN_MAX)
		return EOF;
	else if (origin != SEEK_SET && origin != SEEK_CUR && origin != SEEK_END)
		return EOF;
	else if ((fp->flag & (_READ | _WRITE)) == 0 || (fp->flag & (_READ | _WRITE)) == (_READ | _WRITE))
		return EOF;
	if ((fp->flag & _WRITE) == _WRITE) {
		if (fflush(fp) == EOF)
			return EOF;
	} else {
		if (origin == SEEK_CUR) {
			if (offset >= 0 && offset <= fp->cnt) {
				fp->ptr += offset;
				fp->cnt -= offset;
				return 0;
			}
			offset -= fp->cnt;
		}
		fp->cnt = 0;
	}
	if (lseek(fp->fd, offset, origin) == -1) {
		fp->flag |= _ERR;
		return EOF;
	}
	fp->flag &= ~_EOF;
	return 0;
}