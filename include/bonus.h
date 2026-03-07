/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/07 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "minirt.h"

/* macOS key codes */
# define KEY_ESC    53
# define KEY_1      18
# define KEY_2      19
# define KEY_3      20
# define KEY_TAB    48
# define KEY_W      13
# define KEY_A      0
# define KEY_S      1
# define KEY_D      2
# define KEY_R      15
# define KEY_F      3
# define KEY_LEFT   123
# define KEY_RIGHT  124
# define KEY_UP     126
# define KEY_DOWN   125
# define KEY_LBRACK 33
# define KEY_RBRACK 30
# define KEY_PLUS   24
# define KEY_MINUS  27

/* HUD dimensions */
# define HUD_W      280
# define HUD_H      220

/* src/window/hooks_bonus.c */
int		handle_keypress_bonus(int keycode, t_scene *scene);

/* src/window/hooks_key_bonus.c */
int		handle_close_bonus(t_scene *scene);
void	setup_hooks(t_scene *scene);

/* src/window/move_bonus.c */
void	move_target(t_scene *scene, int keycode);

/* src/window/rotate_bonus.c */
void	rotate_camera(t_scene *scene, int keycode);

/* src/window/transform_bonus.c */
void	resize_radius(t_scene *scene, int keycode);
void	resize_height(t_scene *scene, int keycode);

/* src/window/hud_bonus.c */
void	render_hud(t_scene *scene);

#endif
