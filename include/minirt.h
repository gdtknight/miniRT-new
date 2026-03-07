/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/07 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "vector.h"
# include "objects.h"

# define WIN_W 1280
# define WIN_H 720
# define EPSILON 1e-6
# define MOVE_STEP 0.5
# define ROT_STEP 5.0
# define RADIUS_STEP 0.2
# define HEIGHT_STEP 0.5

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef enum e_mode
{
	MODE_CAMERA,
	MODE_LIGHT,
	MODE_OBJECT
}	t_mode;

typedef struct s_ambient
{
	double		ratio;
	t_color3	color;
}	t_ambient;

typedef struct s_camera
{
	t_point3	pos;
	t_vec3		dir;
	double		fov;
	t_vec3		right;
	t_vec3		up;
	double		vp_width;
	double		vp_height;
}	t_camera;

typedef struct s_light
{
	t_point3		pos;
	double			brightness;
	t_color3		color;
	struct s_light	*next;
}	t_light;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_scene
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*objects;
	t_light		*lights;
	int			has_ambient;
	int			has_camera;
	int			has_light;
	t_mode		mode;
	int			selected_idx;
	int			obj_count;
}	t_scene;

/* src/utils/ft_atof.c */
double		ft_atof(const char *str);

/* src/utils/get_next_line.c */
char		*get_next_line(int fd);

/* src/scene/scene.c */
void		init_scene(t_scene *scene);
void		free_objects(t_object *objs);

/* src/scene/scene_utils.c */
t_object	*get_object_by_idx(t_object *objs, int idx);

/* src/scene/scene_cleanup.c | src/scene/scene_bonus.c */
void		free_scene(t_scene *scene);
void		free_lights(t_light *lights);

/* src/parsing/parse_error.c */
void		exit_error(char *msg, t_scene *scene);

/* src/window/window.c */
void		init_window(t_scene *scene);
void		destroy_window(t_scene *scene);

/* src/window/hooks.c */
int			handle_keypress(int keycode, t_scene *scene);
int			handle_close(t_scene *scene);
void		setup_hooks(t_scene *scene);

/* src/window/image.c */
void		img_pixel_put(t_img *img, int x, int y, int color);
int			color_to_int(t_color3 c);
void		display_image(t_scene *scene);

#endif
