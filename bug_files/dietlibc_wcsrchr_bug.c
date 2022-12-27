#include <wchar.h>
#include <stdio.h>

wchar_t* wcsrchr(const wchar_t *wcs, wchar_t wc) {
  wchar_t* last=0;
  for (; *wcs; ++wcs)
    if (*wcs == wc)
      last=(wchar_t*)wcs;
  return last;
}

int main()
{   
  const wchar_t src[] = {128, 64, 0};
  wchar_t* ret = wcsrchr(src, 0);
  if (!ret) {
    printf("BUG!\n");
  }
  return 0;
}