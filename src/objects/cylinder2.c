#include "mini_rt.h"

/**
 * @brief Returns which cap is closer (bottom or top)
 * @param data The data that contains the discriminant and
 * cylinder data 
 * @return The closer distance or -1 if no intersection
 */
double	find_closest_cap(t_cy_data *data)
{
	if (data->hit_top_cap && (!data->hit_bot_cap || data->d_top_cap < data->d_bot_cap))
		return (data->d_top_cap);
	else if (data->hit_bot_cap)
		return (data->d_bot_cap);
	return (-1.0);
}

/**
 * @brief Returns the closest side hit
 * @param data The data that contains the discriminant and
 * cylinder data
 * @return The closer hit distance or -1 if no intersection
 */
double	find_closest_side(t_cy_data *data)
{
	if (data->within_bounds_d0 && data->d0 > 0)
	{
		if (data->within_bounds_d1 && data->d1 > 0 && data->d1 < data->d0)
			return (data->d1);
		return (data->d0);
	}
	else if (data->within_bounds_d1 && data->d1 > 0)
		return (data->d1);
	return (-1.0);
}
