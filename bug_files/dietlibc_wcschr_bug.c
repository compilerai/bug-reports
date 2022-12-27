#include <wchar.h>
#include <stdio.h>

wchar_t* wcschr(const wchar_t *wcs, wchar_t wc) {
  for (; *wcs; ++wcs)
    if (*wcs == wc)
      return (wchar_t*)wcs;
  return 0;
}

int main()
{   
  const wchar_t src[] = {128, 64, 0};
  wchar_t* ret = wcschr(src, 0);
  if (!ret) {
      printf("BUG!\n");
  }
  return 0;
}