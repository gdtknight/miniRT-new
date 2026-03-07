/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/07 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "bonus.h"

t_hit	find_closest_hit(t_object *objs, t_ray ray)
{
	t_hit		closest;
	t_hit		hit;
	t_object	*current;
	int			idx;

	closest.hit = 0;
	closest.t = 1e30;
	closest.obj_idx = -1;
	current = objs;
	idx = 0;
	while (current)
	{
		hit = intersect_object(current, ray);
		if (hit.hit && hit.t > EPSILON && hit.t < closest.t)
		{
			closest = hit;
			closest.obj_idx = idx;
			closest.checker = current->checker;
		}
		idx++;
		current = current->next;
	}
	return (closest);
}

static void	render_pixel(t_scene *scene, int x, int y)
{
	t_ray		ray;
	t_color3	color;

	if (x < HUD_W && y < HUD_H)
		return ;
	ray = generate_ray(&scene->camera, x, y);
	color = trace_ray(scene, ray);
	img_pixel_put(&scene->img, x, y, color_to_int(color));
}

void	render_scene(t_scene *scene)
{
	int	x;
	int	y;

	init_camera(&scene->camera);
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			render_pixel(scene, x, y);
			x++;
		}
		y++;
	}
	display_image(scene);
}
