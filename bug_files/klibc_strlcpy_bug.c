/*
 * strlcpy.c
 */

#include <string.h>
#include <stdio.h>

size_t strlcpy(char *dst, const char *src, size_t size)
{
	size_t bytes = 0;
	char *q = dst;
	const char *p = src;
	char ch;

	while ((ch = *p++)) {
		if (bytes + 1 < size)
			*q++ = ch;

		bytes++;
	}

	/* If size == 0 there is no space for a final null... */
	if (size)
		*q = '\0';

	return bytes;
}

int main()
{   
    const char src[] = {64, 255, 0};
    char dst[6] = {64, 255, 0, 0, 0, 0};
    int ret = strlcpy(dst, src, 3);
    printf("%d\n", ret);
    return 0;
}
