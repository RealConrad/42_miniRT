
#include "mini_rt.h"

/**
 * @brief Creates a progress bar in terminal to display the current
 * rendering progress.
 * @param percent The current percentage.
 * @note `((y * 100) / HEIGHT)` Used to calculate the 
 * current position in the progress bar.
 */
void	display_render_progress(int percent)
{
	int	bar_width;
	int	current_pos;
	int	i;

	bar_width = 20;
	current_pos = bar_width * percent / 100;
	i = 0;
	ft_fprintf(STDOUT_FILENO, "\r[");
	while (i < bar_width)
	{
		if (i < current_pos)
			ft_fprintf(STDOUT_FILENO, "#");
		i++;
	}
	ft_fprintf(STDOUT_FILENO, "]%d%%", percent);
}
