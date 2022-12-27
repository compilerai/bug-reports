#include <unistd.h>
#include <stdio.h>

void swab(const void *restrict _src, void *restrict _dest, ssize_t n)
{
	const char *src = _src;
	char *dest = _dest;
	char temp;
	for (; n>1; n-=2) {
		temp = src[0];
		dest[0] = src[1];
		dest[1] = temp;
		dest += 2;
		src += 2;
	}
}

int main()
{   
    char src[] = {65, 64};
    void* dst = src;
    swab(src, dst, 2);
    if (src[0] != 64 || src[1] != 65) {
		printf("BUG!\n");
	}
    return 0;
}