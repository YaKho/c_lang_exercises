#include <stdio.h>

#define getline __getline
#define MAXLINE 1000
#define NPOS 8

int getline(char s[], int maxline);

int main() {
    char line[MAXLINE];

    while (getline(line, MAXLINE)) {
        printf("\n%s", line);
    }

    return 0;
}


int getline(char s[], int maxline) {
    int c, i, j, n;
    for (i = 0, n = 0; i < maxline && ((c = getchar()) != EOF); ++i) {
        if (n >= NPOS) {
        	if (c == ' ' || c == '\t') {
        		s[i] = '\n';
        		n = 0;
        	} else {
	            for (j = i; s[j] != ' ' && s[j] != '\t' && s[j] != '\n' && j > 0;) {
	                --j;
	            }
	            if (s[j] == '\n' || j == 0) {
	            	s[i++] = '-';
	            	s[i++] = '\n';
	            	n = 0;
	            } else {
	            	s[j] = '\n';
	            	n = i-j;
	        	}
	        	s[i] = c;
	        }
        } else {
        	++n;
        	s[i] = c;
        }
    }
    s[i] = '\0';

    return i;
}
