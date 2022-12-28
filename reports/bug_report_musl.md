Hi,

I am writing to report a bug in the swab function of musl.
The bug is in the C implementation of swab as located in src/string directory of the musl repository. The musl version was `1.2.3` and the source code was downloaded from the [latest release](https://musl.libc.org/releases/musl-1.2.3.tar.gz) on the official website.
Please find a detailed report below.

Linux[0] manpage for swab() specifies that the function copies n bytes from the array pointed to by from to the array pointed to by to, exchanging adjacent even and odd bytes. This should also work for coinciding memories and musl's implementation does not take that into account.
An example input is:
  char src[] = {65, 64};
  void* dst = src;
  swab(src, dst, 2);
  if (src[0] != 64 || src[1] != 65) {
	  printf("BUG!\n");
	}

The file that demonstrates the bug can be found [here](https://github.com/compilerai/bug-reports/blob/master/bug_files/musl_swab_bug.c).
A patch that applies the necessary fix is available [here](https://github.com/compilerai/bug-reports/blob/master/patch/musl_swab.patch).

0: https://man7.org/linux/man-pages/man3/swab.3.html

Thanks,

Jai Arora, Abhishek Rose, Shubhani Gupta, Sorav Bansal
CompilerAI Research Group
IIT Delhi, India