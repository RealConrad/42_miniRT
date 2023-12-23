#include "mini_rt.h"

int	escape(keys_t keycode, void *param)
{
	(void)param;
	if (keycode == MLX_KEY_ESCAPE)
		exit(0);
	return (0);
}
