#include <strings.h>
#include <stdio.h>

int  strcasecmp( const char* s1, const char* s2 )
{
    register unsigned int  x2;
    register unsigned int  x1;

    while (1) {
        x2 = *s2 - 'A'; if (x2 < 26u) x2 += 32;
        x1 = *s1 - 'A'; if (x1 < 26u) x1 += 32;
        printf("%u %u\n", x1, x2);
	s1++; s2++;
        if ( x2 != x1 )
            break;
        if ( x1 == (unsigned int)-'A' )
            break;
    }

    return x1 - x2;
}

int main()
{   
    const char src[] = {'A', 1, 0};
    const char dst[] = {'a', 255, 0};
    int ret = strcasecmp(src, dst);
    if (ret >= 0) {
        printf("BUG!\n");
    }
    return 0;
}