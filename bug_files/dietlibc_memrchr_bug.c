#include <sys/types.h>
#include <stdio.h>
#include <string.h>

void* memrchr(const void *s, int c, size_t n) {
  register const char* t=s;
  register const char* last=0;
  int i;
  for (i=n; i; --i) {
    if (*t==c)
      last=t;
    ++t;
  }
  return (void*)last; /* man, what an utterly b0rken prototype */
}

int main()
{   
    const char src[] = {1, 0};
    if (!memrchr(src, 257, 2)) {
        printf("BUG!\n");
    }
    return 0;
}