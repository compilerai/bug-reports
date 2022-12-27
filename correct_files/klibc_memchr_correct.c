/*
 * memchr.c
 */

#include <stddef.h>
#include <string.h>
#include <stdio.h>

void *memchr(const void *s, int c, size_t n)
{
	const unsigned char *sp = s;

	while (n--) {
		if (*sp == (unsigned char)c)
			return (void *)sp;
		sp++;
	}

	return NULL;
}

int main()
{   
    const char src[] = {1, 0};
    if (!memchr(src, 256, 2)) {
        printf("BUG!\n");
    } else {
        printf("NOT A BUG!\n");
    }
    return 0;
}