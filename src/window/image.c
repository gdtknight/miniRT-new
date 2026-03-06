/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	clamp_int(int val, int min, int max)
{
	if (val < min)
		return (min);
	if (val > max)
		return (max);
	return (val);
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	color_to_int(t_color3 c)
{
	int	r;
	int	g;
	int	b;

	r = clamp_int((int)(c.x * 255), 0, 255);
	g = clamp_int((int)(c.y * 255), 0, 255);
	b = clamp_int((int)(c.z * 255), 0, 255);
	return (r << 16 | g << 8 | b);
}

void	display_image(t_scene *scene)
{
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.ptr, 0, 0);
}
