
#include "mini_rt.h"
#include <float.h>

double	ft_dabs(double nb)
{
	if (nb >= 0)
		return (nb);
	else if (nb == DBL_MIN)
		return (nb);
	else
		return (-nb);
}
