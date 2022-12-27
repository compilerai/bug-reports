#define _POSIX_SOURCE
#define _XOPEN_SOURCE
#include <sys/types.h>
#include <string.h>
#include <stdio.h>

void *memccpy(void *dst, const void *src, int c, size_t count)
{
  char *a = dst;
  const char *b = src;
  while (count--)
  {
    *a++ = *b;
    if (*b==c)
    {
      return (void *)a;
    }
    b++;
  }
  return 0;
}

int main()
{   
    const char src[] = {255, 128};
    char dst[2] = {'A', 'B'};
    memccpy(dst, src, 255, 2);
    if (dst[1] != 'B') {
        printf("BUG!\n");
    }
    return 0;
}
