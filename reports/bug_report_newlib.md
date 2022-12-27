Hi,

I am writing to report a bug in the memccpy function of newlib.
The bug is in the C implementation of newlib as located in the newlib/libc/string/ directory of the newlib repository. The newlib version was `4.2.0` and the source code was downloaded from the [latest release](https://sourceware.org/pub/newlib/newlib-4.2.0.20211231.tar.gz) on the official website.
Please find a detailed report below.

memccpy():
As specified in the OpenBSD manpage[0], memccpy should convert the input argument `c` to `unsigned char` before performing the check. Newlib's fast implementation of `memccpy` (when the macros `PREFER_SIZE_OVER_SPEED` and `__OPTIMIZE_SIZE__` are not defined) converts `c` to `signed char` (stored in endchar) and computes a mask as follows:
```
for (i = 0; i < LITTLEBLOCKSIZE; i++)
    mask = (mask << 8) + endchar;
```
This is used to detect `endchar` in one long word and is supposed to represent a word whose each byte has the same value as `endchar`. But if the input character lies in the extended ASCII set, then `endchar` is negative, which leads to an incorrect mask computation.

An example input is:
    const char src[] = {1, 2, 3, 4, 5, 192, 6, 7};
    char dst[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    memccpy(dst, src, 192, 8);
    if (dst[7] != 'H') {
        printf("BUG!\n");
    }

A patch that applies the necessary fix is available [here](https://github.com/iitd-plos/superopt-tests/blob/inequivalence_checking/inequivalence/bugs/patch/newlib_memccpy.patch)

0: https://man.openbsd.org/memccpy

Thanks,

Jai Arora, Abhishek Rose, Shubhani Gupta, Sorav Bansal
CompilerAI Research Group
IIT Delhi, India