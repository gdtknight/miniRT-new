/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/07 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "bonus.h"

static void	handle_mode_key(int keycode, t_scene *scene)
{
	if (keycode == KEY_1)
		scene->mode = MODE_CAMERA;
	else if (keycode == KEY_2)
		scene->mode = MODE_LIGHT;
	else if (keycode == KEY_3)
		scene->mode = MODE_OBJECT;
	else if (keycode == KEY_TAB && scene->mode == MODE_OBJECT)
	{
		if (scene->obj_count > 0)
			scene->selected_idx = (scene->selected_idx + 1)
				% scene->obj_count;
	}
}

static void	handle_move_key(int keycode, t_scene *scene)
{
	int	is_move;

	is_move = (keycode == KEY_W || keycode == KEY_A
			|| keycode == KEY_S || keycode == KEY_D
			|| keycode == KEY_R || keycode == KEY_F);
	if (!is_move)
		return ;
	move_target(scene, keycode);
	render_scene(scene);
	render_hud(scene);
}

static void	handle_rotate_key(int keycode, t_scene *scene)
{
	int	is_arrow;

	is_arrow = (keycode == KEY_LEFT || keycode == KEY_RIGHT
			|| keycode == KEY_UP || keycode == KEY_DOWN);
	if (!is_arrow || scene->mode != MODE_CAMERA)
		return ;
	rotate_camera(scene, keycode);
	render_scene(scene);
	render_hud(scene);
}

static void	handle_resize_key(int keycode, t_scene *scene)
{
	int	acted;

	acted = 0;
	if (scene->mode != MODE_OBJECT)
		return ;
	if (keycode == KEY_LBRACK || keycode == KEY_RBRACK)
	{
		resize_radius(scene, keycode);
		acted = 1;
	}
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
	{
		resize_height(scene, keycode);
		acted = 1;
	}
	if (!acted)
		return ;
	render_scene(scene);
	render_hud(scene);
}

int	handle_keypress_bonus(int keycode, t_scene *scene)
{
	if (keycode == KEY_ESC)
	{
		free_scene(scene);
		exit(0);
	}
	handle_mode_key(keycode, scene);
	if (keycode == KEY_1 || keycode == KEY_2
		|| keycode == KEY_3 || keycode == KEY_TAB)
		render_hud(scene);
	handle_move_key(keycode, scene);
	handle_rotate_key(keycode, scene);
	handle_resize_key(keycode, scene);
	return (0);
}
