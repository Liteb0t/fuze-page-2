#include <stdio.h>
#include <string.h>
// #include "syscalls.h"

#define NORMAL 'n'
#define OPENTOKEN 'o'
#define CLOSETOKEN 'c'
#define TOKEN 't'
#define ESCAPE '\\'
#define TEMPLATEDIR "_templates/"

int tokenise(FILE *in, FILE *out);

int main() {
	// char buf[BUFSIZ];
	FILE *finp;
	FILE *foutp;
	char c, fc;
	int i, n, fnci;
	char fname[100];
	char outfname[100];
	int found_tokens = 0;
	int underscore_index = -1;
	i = n = fnci = 0;
	char mode = NORMAL;

	while ((c = getchar()) != EOF) {
		if (c != '\n') {
			if (c == '_' && underscore_index == -1)
				underscore_index = fnci;
			else if (c == '/')
				underscore_index = -1;
			fname[fnci++] = c;
		}
		else {
			fname[fnci] = '\0';
			strcpy(outfname, fname);
			printf("IN FILENAME: %s", fname);
			if (underscore_index == -1) {
				printf(" skipping!\n");
			}
			else {
				for (i = underscore_index; i < fnci; i++)
					outfname[i] = outfname[i+1];
				printf(" OUT FILENAME: %s\n", outfname);
				finp = fopen(fname, "r");
				foutp = fopen(outfname, "w");
				tokenise(finp, foutp);
				// while ((fc = getc(fp)) != EOF)
				// 	putchar(fc);
			}
			fnci = 0;
			underscore_index = -1;
		}
	}
	/*

	*/

	// printf("found tokens: %d", found_tokens);
	return 0;
}

int tokenise(FILE *finp, FILE *foutp) {
	FILE *ftokp;
	char c, tc;
	char tstr[100];
	char tname[100];
	char mode = NORMAL;
	const char warning[] = "<!-- Warning: this file is auto-generated, so edits will be overwritten -->\n";
	int i, n;
	i = 0;

	fputs(warning, foutp);
	while ((c = getc(finp)) != EOF) {
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
				putc(tstr[n], foutp);
				// putc('0', foutp);
				// tstr[n] = '';
			}
			i = 0;
			mode = NORMAL;
			// tstr[i] = EOF;
		}
		else if (mode == CLOSETOKEN) {
			if (c == '}') {
				mode = NORMAL;
				tstr[i] = '\0';
				// printf("<!--TOK %s-->\n", tstr);
				strcpy(tname, TEMPLATEDIR);
				strcat(tname, "/");
				strcat(tname, tstr);
				ftokp = fopen(tname, "r");
				if (ftokp != NULL) {
					while ((tc = getc(ftokp)) != EOF)
						putc(tc, foutp);
				}
				else
					printf("ERROR: could not open file %s", tname);
				i = 0;
				// printf("Oh my fauci there was a token here!");
				// found_tokens++;
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
			putc(c, foutp);
	}
}
