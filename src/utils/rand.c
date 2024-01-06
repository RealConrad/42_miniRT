#include "mini_rt.h"

double	random_double(void)
{
	return (arc4random() / ((double)UINT32_MAX + 1.0));
}
