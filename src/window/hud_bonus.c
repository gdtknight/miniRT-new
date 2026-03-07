/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/07 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "bonus.h"

static void	draw_hud_bg(t_scene *scene)
{
	int	x;
	int	y;

	y = 0;
	while (y < HUD_H)
	{
		x = 0;
		while (x < HUD_W)
		{
			img_pixel_put(&scene->img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

static void	draw_hud_mode(t_scene *scene)
{
	int	c;

	c = 0xFFFFFF;
	if (scene->mode == MODE_CAMERA)
		mlx_string_put(scene->mlx, scene->win, 10, 40, c,
			"Mode:[CAMERA] light obj");
	else if (scene->mode == MODE_LIGHT)
		mlx_string_put(scene->mlx, scene->win, 10, 40, c,
			"Mode: camera [LIGHT] obj");
	else
		mlx_string_put(scene->mlx, scene->win, 10, 40, c,
			"Mode: camera light [OBJ]");
}

static void	draw_hud_keys(t_scene *scene)
{
	int	c;

	c = 0xFFFFFF;
	mlx_string_put(scene->mlx, scene->win, 10, 20, c,
		"=== miniRT Controls ===");
	mlx_string_put(scene->mlx, scene->win, 10, 60, c,
		"[1]Camera [2]Light [3]Obj");
	mlx_string_put(scene->mlx, scene->win, 10, 80, c,
		"[WASD]Move [RF]Up/Down");
	mlx_string_put(scene->mlx, scene->win, 10, 100, c,
		"[<->]Yaw [Up/Dn]Pitch");
	mlx_string_put(scene->mlx, scene->win, 10, 120, c,
		"[Tab]Select Object");
	mlx_string_put(scene->mlx, scene->win, 10, 140, c,
		"[[/]]Radius [+-]Height");
	mlx_string_put(scene->mlx, scene->win, 10, 160, c,
		"-----------------------");
}

static void	draw_hud_status(t_scene *scene)
{
	t_object	*obj;
	const char	*type_str;
	char		*idx;
	char		buf[64];

	if (scene->mode != MODE_OBJECT)
		return ;
	obj = get_object_by_idx(scene->objects, scene->selected_idx);
	if (!obj)
		return ;
	type_str = "sphere";
	if (obj->type == OBJ_PLANE)
		type_str = "plane";
	else if (obj->type == OBJ_CYLINDER)
		type_str = "cylinder";
	else if (obj->type == OBJ_CONE)
		type_str = "cone";
	idx = ft_itoa(scene->selected_idx + 1);
	ft_strlcpy(buf, "Selected: ", 64);
	ft_strlcat(buf, type_str, 64);
	ft_strlcat(buf, " #", 64);
	ft_strlcat(buf, idx, 64);
	free(idx);
	mlx_string_put(scene->mlx, scene->win, 10, 200, 0xFFFFFF, buf);
}

void	render_hud(t_scene *scene)
{
	draw_hud_bg(scene);
	display_image(scene);
	draw_hud_keys(scene);
	draw_hud_mode(scene);
	draw_hud_status(scene);
}
