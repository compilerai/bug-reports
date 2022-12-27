#include <string.h>
#include <stdio.h>
#include "../dietstring.h"

void* memchr(const void *s, int c, size_t n) {
  const unsigned char *pc = (unsigned char *) s;
  for (;n--;pc++)
    if (*pc == c)
      return ((void *) pc);
  return 0;
}

int main()
{   
    const char src[] = {1, 0};
    if (!memchr(src, 256, 2)) {
        printf("BUG!\n");
    }
    return 0;
}