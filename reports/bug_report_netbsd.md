Hi,

I am writing to report a bug in the swab function of NetBSD.
The bugs is in the C implementation of swab as located in lib/libc/string/ directory of the NetBSD repository. The source code was downloaded from the [official git repository](https://github.com/NetBSD/src) (top level commit on the `trunk` branch).
Please find a detailed report below.

Linux[0] manpage for swab() specifies that the function copies n bytes from the array pointed to by from to the array pointed to by to, exchanging adjacent even and odd bytes. Netbsd's implementation incorrectly rounds n to a multiple of 8, leading one less memory swap than expected.
An example input is:
  const char src[] = {90, 91, 1, 2};
  char dst[4] = {'A', 'B', 'C', 'D'};
  swab(src, dst, 4);
  if (dst[0] != 91 || dst[1] != 90 || dst[2] != 2 || dst[3] != 1) {
		printf("BUG!\n");
	}

The file that demonstrates the bug can be found [here](https://github.com/compilerai/bug-reports/blob/master/bug_files/netbsd_swab_bug.c).
A patch that applies the necesaary fix is available [here](https://github.com/compilerai/bug-reports/blob/master/patch/netbsd_swab.patch).

0: https://man7.org/linux/man-pages/man3/swab.3.html

Thanks,

Jai Arora, Abhishek Rose, Shubhani Gupta, Sorav Bansal
CompilerAI Research Group
IIT Delhi, India