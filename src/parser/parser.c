
#include "../../includes/mini_rt.h"

t_scene	parser(int argc, char *argv[])
{
	t_scene	scene;

	if (argc != 2)
		parser_exit(2, NULL);
}


/**
 * @brief Cleanly exits the parser
 * @param error_code the code for the exit message
 * @param free_me NULLABLE, for freeing allocated memory 
 * takes an unallocated array
 */
void	parser_exit(int error_code, void **free_me)
{
	int	i;

	i = -1;
	if (free_me != NULL)
	{
		while (free_me[++i] != NULL)
			free(free_me[i]);
	}
}
