#include "mini_rt.h"

double	random_double(void)
{
	return (arc4random() / (RAND_MAX + 1.0));
}
