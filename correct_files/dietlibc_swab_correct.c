#include <unistd.h>
#include <stdio.h>

void swab(const void *src, void *dest, ssize_t nbytes)
{
  ssize_t i;
  const char *s=src;
  char *d=dest;
  nbytes&=~1;
  char temp;
  for (i=0; i<nbytes; i+=2) {
    temp = s[i];
    d[i]=s[i+1];
    d[i+1]=temp;
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