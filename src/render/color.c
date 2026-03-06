/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_color3	color_new(double r, double g, double b)
{
	return (vec3_new(r, g, b));
}

t_color3	color_add(t_color3 a, t_color3 b)
{
	return (vec3_add(a, b));
}

t_color3	color_mul(t_color3 c, double t)
{
	return (vec3_mul(c, t));
}

t_color3	color_hadamard(t_color3 a, t_color3 b)
{
	return (vec3_new(a.x * b.x, a.y * b.y, a.z * b.z));
}

t_color3	color_clamp(t_color3 c)
{
	c.x = fmin(1.0, fmax(0.0, c.x));
	c.y = fmin(1.0, fmax(0.0, c.y));
	c.z = fmin(1.0, fmax(0.0, c.z));
	return (c);
}
