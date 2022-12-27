/* fast strcmp -- Copyright (C) 2003 Thomas M. Ogrisegg <tom@hi-tek.fnord.at> */
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "dietstring.h"

#define WANT_SMALL_STRING_ROUTINES

int
strcmp (const char *s1, const char *s2)
{
#ifdef WANT_SMALL_STRING_ROUTINES
    while (*s1 && *s1 == *s2)
        s1++, s2++;
    return (*(unsigned char*)s1 - *(unsigned char*)s2);
#else
    const unsigned long *lx1, *lx2;
    unsigned long   l1, l2;
    int             tmp;

    if (UNALIGNED(s1, s2)
    ) {
        while (*s1 && *s1 == *s2) s1++, s2++;
        return (*s1 - *s2);
    }

    if ((tmp = STRALIGN(s1)))
        for (; tmp--; s1++, s2++)
            if (!*s1 || *s1 != *s2)
                return (*s1 - *s2);

    lx1 = (unsigned long *) s1;
    lx2 = (unsigned long *) s2;

    while (1) {
        l1 = *lx1++;
        l2 = *lx2++;
        if ((((l1 - MKW(0x1ul)) & ~l1) & MKW(0x80ul)) ||
            ((((l2 - MKW(0x1ul)) & ~l2) & MKW(0x80ul))) || l1 != l2) {
            unsigned char c1, c2;
            while (1) {
		c1 = GFC(l1);
                c2 = GFC(l2);
                if (!c1 || c1 != c2)
                    return (c1 - c2);
                INCSTR(l1);
                INCSTR(l2);
            }
        }
    }
#endif
}

int main()
{   
    const char src[] = {64, 1, 0};
    const char dst[] = {64, 255, 0};
    int ret = strcmp(src, dst);
    if (ret >= 0) {
        printf("BUG!\n");
    }
    return 0;
}