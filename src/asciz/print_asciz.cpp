#include "print_asciz.h"

void 
print_asciz( const char * s )
{
	while( *s != '\0')
	{
		putchar(toggle_asciz(*s));
		++s;
	}
}
