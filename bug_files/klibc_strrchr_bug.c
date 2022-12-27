/*
 * strrchr.c
 */

#include <string.h>
#include <stdio.h>

char *strrchr_klibc(const char *s, int c)
{
	const char *found = NULL;

	while (*s) {
		if (*s == (char)c) {
			found = s;
        }
		s++;
	}

	return (char *)found;
}

int main()
{   
    const char src[] = {128, '\0'};
    char *ret = strrchr_klibc(src, 0);
    if (!ret) {
		printf("BUG!\n");
	}
    return 0;
}

