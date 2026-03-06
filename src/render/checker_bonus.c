/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_color3	apply_checkerboard(t_hit hit, t_color3 base_color)
{
	int	ix;
	int	iy;
	int	iz;
	int	sum;

	ix = (int)floor(hit.point.x);
	iy = (int)floor(hit.point.y);
	iz = (int)floor(hit.point.z);
	sum = ix + iy + iz;
	if (((sum % 2) + 2) % 2 == 0)
		return (base_color);
	return (color_new(1.0 - base_color.x, 1.0 - base_color.y,
			1.0 - base_color.z));
}
