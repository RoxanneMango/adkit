#include "toggle_asciz.h"

char
toggle_asciz(char s)
{
	return (((s >= 'a') && (s <= 'z')) ? s-32 : ((s >= 'A') && (s <= 'Z')) ? s+32 : s);
}