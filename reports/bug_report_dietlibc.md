Hi,

I am writing to report bugs in memchr, strcasecmp, strcmp, strncasecmp, swab, wcschr, wcsrchr functions of dietlibc. The source code was downloaded from the [official git repository](https://github.com/ensc/dietlibc).
Please find a detailed report below.

memchr():
This is in reference to the implementations present in the contrib/ directory of the dietlibc repository.
Linux[0] manpage for memchr() specifies that the input argument `c` must be converted to `unsigned char` before performing the check. 
The small version of the implementation (with the macro `WANT_SMALLER_STRING_ROUTINES` defined) does not take this into account and gives a wrong output when `c` is greater than 256. The fast version of the implementation (without the macro `WANT_SMALLER_STRING_ROUTINES` defined) also has the same bug.

An example input is (compiled with the `-m32` flag):
    const char src[] = {1, 0, 0, 0, 0};
    if (!memchr(src, 257, 5)) {
        printf("BUG!\n");
    }

strcasecmp() and strncasecmp():
This is in reference to the implementations present in the lib/ directory of the dietlibc repository.
The Linux[1] manpage for strcasecmp() specifies that the when the LC_CTYPE category of the locale being used is from the POSIX locale, these functions shall behave as if the strings had been converted to lowercase and then a byte comparison performed. The implementation does not handle the case when the characters belong to the extended ASCII set.

An example input is:
    const char src[] = {'A', 1, 0};
    const char dst[] = {'a', 255, 0};
    int ret = strcasecmp(src, dst);
    if (ret >= 0) {
        printf("BUG!\n");
    }

    int ret = strncasecmp(src, dst, 3);
    if (ret >= 0) {
        printf("BUG!\n");
    }

strcmp():
This is in reference to the implementation present in the lib/ directory of the dietlibc repository.
The Linux[2] manpage for strcmp says that the characters have to be interpreted as `unsigned char`. The dietlibc implementation does not follow that; both the small version (with the macro `WANT_SMALL_STRING_ROUTINES` defined) and the fast version (without the macro `WANT_SMALL_STRING_ROUTINES`) have missing type-casts.

An example input is:
    const char src[] = {64, 1, 0};
    const char dst[] = {64, 255, 0};
    int ret = strcmp(src, dst);
    if (ret >= 0) {
        printf("BUG!\n");
    }

A patch that applies the necessary fix is available here for the [small string routine](https://github.com/iitd-plos/superopt-tests/blob/inequivalence_checking/inequivalence/bugs/patch/dietlibc_strcmp-small.patch) and the [fast string routine](https://github.com/iitd-plos/superopt-tests/blob/inequivalence_checking/inequivalence/bugs/patch/dietlibc_strcmp-fast.patch).

swab():
This is in reference to the implementation present in the lib/ directory of the dietlibc repository.
Linux[3] manpage for swab() specifies that the function copies n bytes from the array pointed to by from to the array pointed to by to, exchanging adjacent even and odd bytes. This should also work for coinciding memories and dietlibc's implementation does not take that into account.
An example input is:
    char src[] = {65, 64};
    void* dst = src;
    swab(src, dst, 2);
    if (src[0] != 64 || src[1] != 65) {
		printf("BUG!\n");
	}

A patch that applies the necesaary fix is available [here](https://github.com/iitd-plos/superopt-tests/blob/inequivalence_checking/inequivalence/bugs/patch/dietlibc_swab.patch).

wcschr() and wcsrchr():
This is in reference to the implementation present in the lib/ directory of the dietlibc repository.
OpenBSD[4, 5] manpages for wcschr() and wcsrchr() specify that if the input `c` is the null wide character, then the functions locate the terminating null wide character. Dietlibc's implementation does not follow that and returns NULL instead.

An example input is:
    const wchar_t src[] = {128, 64, 0};
    wchar_t* ret = wcschr(src, 0);
    if (!ret) {
        printf("BUG!\n");
    }
    
    wchar_t* ret = wcsrchr(src, 0);
    if (!ret) {
        printf("BUG!\n");
    }

0: https://linux.die.net/man/3/memchr
1: https://man7.org/linux/man-pages/man3/strcasecmp.3.html
2: https://man7.org/linux/man-pages/man3/strcmp.3.html
3: https://man7.org/linux/man-pages/man3/swab.3.html
4: https://man.openbsd.org/wcschr.3
5: https://man.openbsd.org/wcsrchr.3

Thanks,

Jai Arora, Abhishek Rose, Shubhani Gupta, Sorav Bansal
CompilerAI Research Group
IIT Delhi, India