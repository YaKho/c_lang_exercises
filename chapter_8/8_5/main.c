#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>

#define MAX_PATH 1024

void fsize(char const *);

int main(int argc, char const *argv[])
{
	if (argc == 1)
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);

	return 0;
}

//int stat(char *, struct stat *);
void dirwalk(char const *, void (*fcn)(char const *));

void fsize(char const *name)
{
	struct stat stbuf;
	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: don't access to %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);
	struct passwd *pwd = getpwuid(stbuf.st_uid);
	printf("%81d %s Owner: %s\n", (int)stbuf.st_size, name, pwd->pw_name);
}

void dirwalk(char const *dir, void (*fcn)(char const *))
{
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) != NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	while ((dp = readdir(dfd)) != NULL) {
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
			continue;
		if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
			fprintf(stderr, "dirwalk: too long name %s/%s\n", dir, dp->d_name);
		else {
			sprintf(name, "%s/%s", dir, dp->d_name);
			(*fcn)(name);
		}
	}
	closedir(dfd);
}
