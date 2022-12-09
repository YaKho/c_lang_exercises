#include <stdio.h>
#include <string.h>

void filecmp(FILE *fp1, FILE *fp2);

int main(int argc, char const *argv[])
{
	FILE *fp1, *fp2;
	if ((fp1 = fopen("first.txt", "r")) == NULL) {
		printf("error; can't open file first.txt\n");
		return -1;
	}
	if ((fp2 = fopen("second.txt", "r")) == NULL) {
		printf("error; can't open file second.txt\n");
		return -1;
	}

	filecmp(fp1, fp2);

	fclose(fp1);
	fclose(fp2);

	return 0;
}

#define MAXLINE 1000

void filecmp(FILE *fp1, FILE *fp2)
{
	char line1[MAXLINE];
	char line2[MAXLINE];

	while(fgets(line1, MAXLINE, fp1) != NULL &&
		 fgets(line2, MAXLINE, fp2) != NULL)
		if (strcmp(line1, line2) != 0) {
			printf("%s%s", line1, line2);
			return;
		}

	printf("files are same\n");
}