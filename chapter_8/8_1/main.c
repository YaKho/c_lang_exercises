#include <stdio.h>
#include <fcntl.h>

#define BUFSIZE 1024

int main(int argc, char const *argv[])
{
	int fd;
	void filecopy(int from, int to);

	if (argc == 1)
		filecopy(0, 1);
	else
		while (--argc > 0)
			if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
				printf("cat: can't open file %s\n", *argv);
				return 1;
			} else {
				filecopy(fd, 1);
				close(fd);
			}
	return 0;
}


void filecopy(int from, int to)
{
	int c;
	char buf[BUFSIZE];

	while ((c = read(from, buf, BUFSIZE)) > 0)
		write(to, buf, c);
}