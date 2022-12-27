#include <string.h>
#include <stdio.h>

char *
strrchr(const char *p, int ch)
{
	char *save;
	const char c = ch;

	for (save = NULL;; ++p) {
		if (*p == c) {
			/* LINTED const cast-away */
			save = p;
		}
		if (!*p)
			return(save);
	}
	/* NOTREACHED */
}

int main()
{   
    const char src[] = {128, '\0'};
    char *ret = strrchr(src, 0);
    printf("%p\n", ret);
    return 0;
}