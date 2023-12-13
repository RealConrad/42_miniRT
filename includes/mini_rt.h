
#ifndef MINI_RT_H
# define MINI_RT_H

/* -------------------------------------------------------------------------- */
/*                                  Libraries                                 */
/* -------------------------------------------------------------------------- */

# include "../libraries/libft/libft.h"
# include "../libraries/mlx/include/MLX42/MLX42.h"

# include "structs.h"
# include "parser.h"

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include <pthread.h>

/* -------------------------------------------------------------------------- */
/*                                   Defines                                  */
/* -------------------------------------------------------------------------- */

# ifndef WIDTH
#  define WIDTH 1920
# endif /*WIDTH*/

# ifndef HEIGHT
#  define HEIGHT 1080
# endif /*HEIGHT*/

enum e_exit_msg
{
	NORMAL = 0,
	MALLOC_FAIL,
	OPEN_FAIL,
	INPUT_FILE,
	INPUT_MISSING,
	DUPLICATED,
	MISSING
};

#endif /*MINI_RT_H*/
