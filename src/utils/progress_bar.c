#include "mini_rt.h"

void	display_render_progress(int percent)
{
	int	bar_width;
	int	current_pos;
	int	i;

	bar_width = 20;
	current_pos = bar_width * percent / 100;
	i = 0;
	ft_fprintf(STDOUT_FILENO, "\r");
	ft_fprintf(STDOUT_FILENO, "[");
	while (i < bar_width)
	{
		if (i < current_pos)
			ft_fprintf(STDOUT_FILENO, "#");
		i++;
	}
	ft_fprintf(STDOUT_FILENO, "]%d%%", percent);
}
