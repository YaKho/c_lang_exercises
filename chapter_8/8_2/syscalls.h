#ifdef NULL
	#undef NULL
#endif

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

typedef struct _iobuf {
	int cnt;
	char *ptr;
	char *base;
	struct flags {
		unsigned int _READ : 1;
		unsigned int _WRITE : 1;
		unsigned int _UNBUF : 1;
		unsigned int _EOF : 1;
		unsigned int _ERR : 1;
	} _flags;
	int fd;
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)
#define getc(p) (--(p)->cnt >= 0 \
	? (unsigned char) *(p)->ptr++ : _fillhbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 \
	? *(p)->ptr++ = (x) : _flushbuf((x), p))
#define getchar() getc(stdin)
//#define putchar(x) putc((x), stdout)
