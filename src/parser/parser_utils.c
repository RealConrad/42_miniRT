#include "mini_rt.h"

void	exit_analize(t_scene *scene, char **tokens, int fd)
{
	(void)scene;
	close(fd);
	free_2d_array(tokens);
	parser_exit(FORMAT, NULL);
}

