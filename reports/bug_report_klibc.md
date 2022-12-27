Hi,

I am writing to report a bug in the strrchr function of klibc.
The bug is in the C implementation of strrchr as located in usr/klibc/ directory of the klibc repository. The klibc version was `2.0.11` and the source code was downloaded from the [Linux Kernel Archives](https://mirrors.edge.kernel.org/pub/linux/libs/klibc/2.0/klibc-2.0.11.tar.gz).
Please find a detailed report below.

Linux[0] manpage for strrchr() specifies that the terminating null byte is considered part of the string, so that if c is specified as '\0', this function returns a pointer to the terminator. klibc's implementation does not follow this and thus gives wrong output when `c' is '\0'.
An example input is:
  const char src[] = {128, '\0'};
  char *ret = strrchr(src, 0);
  if (!ret) {
		printf("BUG!\n");
	}


0: https://man7.org/linux/man-pages/man3/strchr.3.html

Thanks,

Jai Arora, Abhishek Rose, Shubhani Gupta, Sorav Bansal
CompilerAI Research Group
IIT Delhi, India