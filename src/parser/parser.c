
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
	if (error_code == NORMAL)
		exit(0);
	ft_fprintf(2, "Error\n");
	if (error_code == MALLOC_FAIL)
		ft_fprintf(2, "Malloc fail in parser\n");
	else if (error_code == OPEN_FAIL)
		ft_fprintf(2, "Open fail in parser\n");
	else if (error_code == INPUT_FILE)
		ft_fprintf(2, "Input file isn't a .rt file\n");
	else if (error_code == DUPLICATED)
		ft_fprintf(2, "A, L or C duplicated\n");
	else if (error_code == MISSING)
		ft_fprintf(2, " A, L or C is missing\n");
	else if (error_code == INPUT_MISSING)
		ft_fprintf(2, "No input, please provide a .rt file\n");
	exit(1);
}
