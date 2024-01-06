#include "mini_rt.h"

/**
 * @brief Creates a progress bar in terminal to display the current rendering progress.
 * @param percent The current percentage `((y * 100) / HEIGHT)`. Used to calculate the 
 * current position in the progress bar.
 */
void	display_render_progress(int percent)
{
	int		bar_width;
	char	*percent_as_str;
	int		current_pos;
	int		i;

	bar_width = 20;
	current_pos = bar_width * percent / 100;
	i = 0;
	write(STDOUT_FILENO, "\r[", 2);
	while (i < bar_width)
	{
		if (i < current_pos)
			write(STDOUT_FILENO, "#", 1);
		i++;
	}
	percent_as_str = ft_itoa(percent);
	write(STDOUT_FILENO, "]", 1);
	write(STDOUT_FILENO, percent_as_str, ft_strlen(percent_as_str));
	write(STDOUT_FILENO, "%%", 1);
	free(percent_as_str);
}
