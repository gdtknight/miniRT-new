/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/07 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static void	recalc_cone_theta(t_cone *cone)
{
	double	h;
	double	r;

	h = cone->height;
	r = cone->radius;
	cone->cos_theta = h / sqrt(r * r + h * h);
}

static void	resize_radius_obj(t_object *obj, int keycode)
{
	double	*r;

	if (obj->type == OBJ_SPHERE)
		r = &obj->data.sphere.radius;
	else if (obj->type == OBJ_CYLINDER)
		r = &obj->data.cylinder.radius;
	else if (obj->type == OBJ_CONE)
		r = &obj->data.cone.radius;
	else
		return ;
	if (keycode == KEY_RBRACK)
		*r += RADIUS_STEP;
	else if (keycode == KEY_LBRACK && *r > RADIUS_STEP)
		*r -= RADIUS_STEP;
	if (obj->type == OBJ_CONE)
		recalc_cone_theta(&obj->data.cone);
}

void	resize_radius(t_scene *scene, int keycode)
{
	t_object	*obj;

	if (scene->mode != MODE_OBJECT)
		return ;
	obj = get_object_by_idx(scene->objects, scene->selected_idx);
	if (!obj)
		return ;
	resize_radius_obj(obj, keycode);
}

static void	resize_height_obj(t_object *obj, int keycode)
{
	double	*h;

	if (obj->type == OBJ_CYLINDER)
		h = &obj->data.cylinder.height;
	else if (obj->type == OBJ_CONE)
		h = &obj->data.cone.height;
	else
		return ;
	if (keycode == KEY_PLUS)
		*h += HEIGHT_STEP;
	else if (keycode == KEY_MINUS && *h > HEIGHT_STEP)
		*h -= HEIGHT_STEP;
	if (obj->type == OBJ_CONE)
		recalc_cone_theta(&obj->data.cone);
}

void	resize_height(t_scene *scene, int keycode)
{
	t_object	*obj;

	if (scene->mode != MODE_OBJECT)
		return ;
	obj = get_object_by_idx(scene->objects, scene->selected_idx);
	if (!obj)
		return ;
	resize_height_obj(obj, keycode);
}
