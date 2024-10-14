#include <stdio.h>
#include <string.h>
// #include "syscalls.h"

#define NORMAL 'n'
#define OPENTOKEN 'o'
#define CLOSETOKEN 'c'
#define TOKEN 't'
#define ESCAPE '\\'
#define TEMPLATEDIR "_templates"

int main() {
	// char buf[BUFSIZ];
	FILE *fp;
	char c, tc;
	int i, n;
	char tstr[100];
	char tname[100];
	int found_tokens = 0;
	i = n = 0;
	char mode = 'n';

	while ((c = getchar()) != EOF) {
		if (c == '{') {
			tstr[i++] = c;
			if (mode == NORMAL)
				mode = OPENTOKEN;
			else if (mode == OPENTOKEN) {
				mode = TOKEN;
				// for (n = 0; n < i; n++)
				i = 0;
			}
			continue;
		}
		if (mode == OPENTOKEN) {
			for (n = 0; n < i; n++) {
				// putchar(tstr[n]);
				putchar('0');
				// tstr[n] = '';
			}
			// tstr[i] = EOF;
		}
		else if (mode == CLOSETOKEN) {
			if (c == '}') {
				mode = NORMAL;
				printf("<!--TOK %s-->\n", tstr);
				strcpy(tname, TEMPLATEDIR);
				strcat(tname, "/");
				strcat(tname, tstr);
				fp = fopen(tname, "r");
				if (fp != NULL) {
					while ((tc = getc(fp)) != EOF)
						putchar(tc);
				}
				else
					printf("ERROR: could not open file %s", tname);
				// printf("Oh my fauci there was a token here!");
				found_tokens++;
			}
			else {
				mode = TOKEN;
				tstr[i++] = '}';
				tstr[i++] = c;
				// continue;
			}
		}
		else if (mode == TOKEN) {
			if (c == '}')
				mode = CLOSETOKEN;
			else {
				tstr[i++] = c;
			}
		}
		else if (mode == NORMAL)
			putchar(c);
	}

	printf("found tokens: %d", found_tokens);
	return 0;
}
