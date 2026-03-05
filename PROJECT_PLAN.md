# miniRT - Detailed Project Plan

This document is the implementation blueprint for the Code Agent.
Every phase lists the exact files, types, function signatures, algorithms, and acceptance criteria.

---

## Data Architecture

### Core Types (include/vector.h)

```c
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef t_vec3	t_point3;   // position in 3D space
typedef t_vec3	t_color3;   // RGB as 0.0-1.0 per channel
```

### Ray (include/render.h)

```c
typedef struct s_ray
{
	t_point3	origin;
	t_vec3		dir;
}	t_ray;
```

### Hit Record (include/render.h)

```c
typedef struct s_hit
{
	double		t;          // ray parameter at intersection
	t_point3	point;      // world-space hit position
	t_vec3		normal;     // outward surface normal (normalized)
	t_color3	color;      // object surface color
	int			hit;        // 1 = valid hit, 0 = miss
}	t_hit;
```

### Objects (include/objects.h)

```c
typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_obj_type;

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
	t_color3	color;
}	t_sphere;

typedef struct s_plane
{
	t_point3	point;
	t_vec3		normal;     // normalized
	t_color3	color;
}	t_plane;

typedef struct s_cylinder
{
	t_point3	center;     // center of the cylinder axis midpoint
	t_vec3		axis;       // normalized axis direction
	double		radius;
	double		height;
	t_color3	color;
}	t_cylinder;

typedef struct s_object
{
	t_obj_type	type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	}	u_data;
	struct s_object	*next;
}	t_object;
```

> Note: Objects are stored as a linked list. The `next` pointer chains all scene objects.

### Scene Elements (include/minirt.h)

```c
typedef struct s_ambient
{
	double		ratio;      // 0.0 - 1.0
	t_color3	color;
}	t_ambient;

typedef struct s_camera
{
	t_point3	pos;
	t_vec3		dir;        // normalized
	double		fov;        // degrees, 0-180
	t_vec3		right;      // computed: orthonormal basis
	t_vec3		up;         // computed: orthonormal basis
	double		vp_width;   // computed: viewport width
	double		vp_height;  // computed: viewport height
}	t_camera;

typedef struct s_light
{
	t_point3	pos;
	double		brightness; // 0.0 - 1.0
	t_color3	color;      // unused in mandatory
}	t_light;
```

### Image Buffer (include/minirt.h)

```c
typedef struct s_img
{
	void	*ptr;           // mlx_new_image return
	char	*addr;          // mlx_get_data_addr return
	int		bpp;            // bits per pixel
	int		line_len;       // bytes per scanline
	int		endian;
}	t_img;
```

### Main Scene Context (include/minirt.h)

```c
# define WIN_W 1280
# define WIN_H 720
# define EPSILON 1e-6

typedef struct s_scene
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*objects;   // linked list head
	int			has_ambient;
	int			has_camera;
	int			has_light;
}	t_scene;
```

---

## Phase 1: Foundation

**Goal**: Makefile compiles, libft linked, vector math fully operational.

### Task 1-1: Makefile

**File**: `Makefile`

```makefile
NAME        = miniRT
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -I include -I libft/include -I minilibx
LIBFT       = libft/libft.a
MLX         = minilibx/libmlx.a
MLX_FLAGS   = -framework OpenGL -framework AppKit  # macOS
LIBS        = $(LIBFT) $(MLX) $(MLX_FLAGS) -lm

# Source files explicitly listed (no wildcards)
SRC = src/main.c \
      src/vector/vec_basic.c \
      src/vector/vec_ops.c \
      ...  # every file listed explicitly

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C libft

$(MLX):
	make -C minilibx

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C libft clean
	make -C minilibx clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

bonus: # defined in Phase 8

.PHONY: all clean fclean re bonus
```

**Acceptance**:
- `make` produces `./miniRT`
- `make` a second time prints nothing (no relink)
- `make clean` / `make fclean` / `make re` work

### Task 1-2: libft Integration

**Directory**: `libft/`

Copy an existing libft with its Makefile. Required functions at minimum:
- `ft_strlen`, `ft_strncmp`, `ft_strcmp` (or custom)
- `ft_atoi`, `ft_atof` (custom: parse float strings)
- `ft_split` (split string by delimiter)
- `ft_substr`, `ft_strdup`, `ft_strtrim`
- `ft_putstr_fd`, `ft_putendl_fd`
- `ft_isdigit`, `ft_isspace` (custom)
- `ft_lstnew`, `ft_lstadd_back`, `ft_lstclear` (if using libft lists)
- `get_next_line` (read file line by line)

> `ft_atof` is critical: must parse strings like `"-50.0"`, `"0.6"`, `"1.0"` to `double`.

### Task 1-3: Vector Math

**Files**: `src/vector/vec_basic.c`, `src/vector/vec_ops.c`
**Header**: `include/vector.h`

#### vec_basic.c (5 functions max)

| Function | Signature | Description |
|----------|-----------|-------------|
| `vec3_new` | `t_vec3 vec3_new(double x, double y, double z)` | Constructor |
| `vec3_add` | `t_vec3 vec3_add(t_vec3 a, t_vec3 b)` | Component-wise addition |
| `vec3_sub` | `t_vec3 vec3_sub(t_vec3 a, t_vec3 b)` | Component-wise subtraction |
| `vec3_mul` | `t_vec3 vec3_mul(t_vec3 v, double t)` | Scalar multiplication |
| `vec3_div` | `t_vec3 vec3_div(t_vec3 v, double t)` | Scalar division |

#### vec_ops.c (5 functions max)

| Function | Signature | Description |
|----------|-----------|-------------|
| `vec3_dot` | `double vec3_dot(t_vec3 a, t_vec3 b)` | Dot product |
| `vec3_cross` | `t_vec3 vec3_cross(t_vec3 a, t_vec3 b)` | Cross product |
| `vec3_length` | `double vec3_length(t_vec3 v)` | Euclidean length = `sqrt(dot(v,v))` |
| `vec3_normalize` | `t_vec3 vec3_normalize(t_vec3 v)` | Unit vector = `v / length(v)` |
| `vec3_negate` | `t_vec3 vec3_negate(t_vec3 v)` | Returns `(-x, -y, -z)` |

**Algorithm Details**:
```
dot(a,b) = a.x*b.x + a.y*b.y + a.z*b.z
cross(a,b) = (a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x)
length(v) = sqrt(dot(v,v))
normalize(v) = v / length(v)   // guard: if length == 0, return (0,0,0)
```

**Acceptance**: Unit test each function with known values. e.g. `dot((1,0,0),(0,1,0)) == 0`.

---

## Phase 2: Parsing

**Goal**: Read `.rt` file, populate `t_scene` with all elements, reject invalid input.

### Task 2-1: Error Utilities

**File**: `src/parsing/parse_error.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `exit_error` | `void exit_error(char *msg, t_scene *scene)` | Print `"Error\n"` + `msg` to stderr, free scene, `exit(1)` |
| `is_valid_ext` | `int is_valid_ext(char *filename)` | Check `.rt` extension |

### Task 2-2: Parse Utilities

**File**: `src/parsing/parse_utils.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `parse_double` | `double parse_double(char *str, t_scene *scene)` | Parse float string, error on invalid |
| `parse_color` | `t_color3 parse_color(char *str, t_scene *scene)` | Parse `"R,G,B"` -> `t_color3` (0-1 normalized). Validate 0-255 |
| `parse_vec3` | `t_vec3 parse_vec3(char *str, t_scene *scene)` | Parse `"x,y,z"` -> `t_vec3` |
| `parse_normal` | `t_vec3 parse_normal(char *str, t_scene *scene)` | Parse + validate range [-1,1] + normalize |
| `count_fields` | `int count_fields(char **fields)` | Count NULL-terminated string array length |

**Algorithm for `parse_color`**:
```
1. ft_split(str, ',') -> tokens
2. Validate exactly 3 tokens
3. Parse each to int, validate 0-255
4. Return t_color3 with each / 255.0
5. Free tokens
```

**Algorithm for `parse_vec3`**:
```
1. ft_split(str, ',') -> tokens
2. Validate exactly 3 tokens
3. Parse each to double via ft_atof
4. Return t_vec3
5. Free tokens
```

### Task 2-3: Scene Element Parsers

**File**: `src/parsing/parse_scene.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `parse_ambient` | `void parse_ambient(char **fields, t_scene *scene)` | Parse `A` line |
| `parse_camera` | `void parse_camera(char **fields, t_scene *scene)` | Parse `C` line |
| `parse_light` | `void parse_light(char **fields, t_scene *scene)` | Parse `L` line |
| `dispatch_line` | `void dispatch_line(char *line, t_scene *scene)` | Identify element type, dispatch to parser |

**`parse_ambient` algorithm**:
```
1. Validate field count == 3 (A, ratio, color)
2. Parse ratio = parse_double(fields[1])
3. Validate ratio in [0.0, 1.0]
4. Parse color = parse_color(fields[2])
5. Set scene->ambient.ratio, scene->ambient.color
6. If scene->has_ambient already set -> error "duplicate ambient"
7. scene->has_ambient = 1
```

**`parse_camera` algorithm**:
```
1. Validate field count == 4 (C, pos, dir, fov)
2. Parse pos = parse_vec3(fields[1])
3. Parse dir = parse_normal(fields[2])
4. Parse fov = parse_double(fields[3])
5. Validate fov in [0, 180]
6. Set scene->camera fields
7. Duplicate check -> error
8. scene->has_camera = 1
```

**`parse_light` algorithm**:
```
1. Validate field count == 4 (L, pos, brightness, color)
2. Parse pos = parse_vec3(fields[1])
3. Parse brightness = parse_double(fields[2])
4. Validate brightness in [0.0, 1.0]
5. Parse color = parse_color(fields[3])  // stored but unused in mandatory
6. Duplicate check -> error
7. scene->has_light = 1
```

**`dispatch_line` algorithm**:
```
1. ft_split(line, ' ') -> fields   (handle tabs: replace \t with space first)
2. if fields[0] is empty or starts with '#' -> skip (allow comments/empty lines)
3. Compare fields[0] with "A", "C", "L", "sp", "pl", "cy"
4. Dispatch to corresponding parser
5. Else -> error "unknown element"
6. Free fields
```

### Task 2-4: Object Parsers

**File**: `src/parsing/parse_objects.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `parse_sphere` | `void parse_sphere(char **fields, t_scene *scene)` | Parse `sp` line |
| `parse_plane` | `void parse_plane(char **fields, t_scene *scene)` | Parse `pl` line |
| `parse_cylinder` | `void parse_cylinder(char **fields, t_scene *scene)` | Parse `cy` line |
| `add_object` | `void add_object(t_scene *scene, t_object *obj)` | Append to linked list |

**`parse_sphere`**: fields = `[sp, center, diameter, color]` -> 4 fields
```
1. Validate field count == 4
2. center = parse_vec3(fields[1])
3. diameter = parse_double(fields[2]) -> validate > 0
4. color = parse_color(fields[3])
5. Create t_object with type=OBJ_SPHERE, sphere={center, diameter/2, color}
6. add_object(scene, obj)
```

**`parse_plane`**: fields = `[pl, point, normal, color]` -> 4 fields
```
1. Validate field count == 4
2. point = parse_vec3(fields[1])
3. normal = parse_normal(fields[2])
4. color = parse_color(fields[3])
5. Create t_object with type=OBJ_PLANE, plane={point, normal, color}
6. add_object(scene, obj)
```

**`parse_cylinder`**: fields = `[cy, center, axis, diameter, height, color]` -> 6 fields
```
1. Validate field count == 6
2. center = parse_vec3(fields[1])
3. axis = parse_normal(fields[2])
4. diameter = parse_double(fields[3]) -> validate > 0
5. height = parse_double(fields[4]) -> validate > 0
6. color = parse_color(fields[5])
7. Create t_object with type=OBJ_CYLINDER, cylinder={center, axis, diameter/2, height, color}
8. add_object(scene, obj)
```

### Task 2-5: File Reader

**File**: `src/parsing/parse_file.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `parse_file` | `void parse_file(char *filename, t_scene *scene)` | Open file, read line by line, dispatch each |
| `validate_scene` | `void validate_scene(t_scene *scene)` | Check has_ambient, has_camera, has_light |

**`parse_file` algorithm**:
```
1. Validate extension with is_valid_ext(filename)
2. fd = open(filename, O_RDONLY) -> error if -1
3. while (line = get_next_line(fd))
   a. Strip trailing newline
   b. Skip empty lines / whitespace-only lines
   c. dispatch_line(line, scene)
   d. free(line)
4. close(fd)
5. validate_scene(scene) -> error if missing A, C, or L
```

### Task 2-6: Validation

**File**: `src/parsing/validate.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `validate_range_d` | `int validate_range_d(double val, double min, double max)` | Check double in range |
| `validate_range_i` | `int validate_range_i(int val, int min, int max)` | Check int in range |
| `is_valid_number` | `int is_valid_number(char *str)` | Check string is valid float format |
| `free_split` | `void free_split(char **split)` | Free ft_split result |

**Acceptance**:
- Valid `.rt` file -> scene populated, no errors
- Missing element -> `"Error\n"` + message
- Duplicate A/C/L -> error
- Out of range values -> error
- Invalid file extension -> error
- Non-existent file -> error
- No args / extra args -> error (handled in main)

---

## Phase 3: Window Management

**Goal**: Open window, display solid color, handle ESC / close / resize.

### Task 3-1: Window Setup

**File**: `src/window/window.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `init_window` | `void init_window(t_scene *scene)` | Create mlx instance, window, image buffer |
| `destroy_window` | `void destroy_window(t_scene *scene)` | Destroy image, window, mlx; free all |

**`init_window` algorithm**:
```
1. scene->mlx = mlx_init()
2. scene->win = mlx_new_window(scene->mlx, WIN_W, WIN_H, "miniRT")
3. scene->img.ptr = mlx_new_image(scene->mlx, WIN_W, WIN_H)
4. scene->img.addr = mlx_get_data_addr(scene->img.ptr, &bpp, &line_len, &endian)
5. Store bpp, line_len, endian in scene->img
```

### Task 3-2: Event Hooks

**File**: `src/window/hooks.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `handle_keypress` | `int handle_keypress(int keycode, t_scene *scene)` | ESC (key 53 macOS / 65307 Linux) -> clean exit |
| `handle_close` | `int handle_close(t_scene *scene)` | Red cross click -> clean exit |
| `setup_hooks` | `void setup_hooks(t_scene *scene)` | Register all hooks with mlx |

**`setup_hooks`**:
```
mlx_hook(scene->win, 2, 1L<<0, handle_keypress, scene);   // KeyPress
mlx_hook(scene->win, 17, 0, handle_close, scene);          // DestroyNotify (red cross)
```

### Task 3-3: Image Buffer Operations

**File**: `src/window/image.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `img_pixel_put` | `void img_pixel_put(t_img *img, int x, int y, int color)` | Write pixel to image buffer |
| `color_to_int` | `int color_to_int(t_color3 c)` | Convert `t_color3` (0-1) to 0xRRGGBB int |
| `display_image` | `void display_image(t_scene *scene)` | `mlx_put_image_to_window` |

**`img_pixel_put` algorithm**:
```
1. offset = y * img->line_len + x * (img->bpp / 8)
2. *(unsigned int *)(img->addr + offset) = color
```

**`color_to_int` algorithm**:
```
1. Clamp each channel to [0.0, 1.0]
2. r = (int)(c.x * 255)
3. g = (int)(c.y * 255)
4. b = (int)(c.z * 255)
5. return (r << 16 | g << 8 | b)
```

**Acceptance**:
- Window opens showing a solid-color image
- ESC closes cleanly
- Red cross closes cleanly
- Minimize + restore preserves content

---

## Phase 4: Core Rendering

**Goal**: Generate camera rays, render loop iterates all pixels.

### Task 4-1: Camera Setup

**File**: `src/scene/camera.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `init_camera` | `void init_camera(t_camera *cam)` | Compute orthonormal basis and viewport |

**Algorithm**:
```
1. world_up = (0, 1, 0)
   - If cam->dir is parallel to world_up (|dot| > 0.999), use world_up = (0, 0, 1)
2. cam->right = normalize(cross(world_up, cam->dir))
3. cam->up = cross(cam->dir, cam->right)
4. aspect_ratio = WIN_W / WIN_H
5. fov_rad = cam->fov * M_PI / 180.0
6. cam->vp_width = 2.0 * tan(fov_rad / 2.0)
7. cam->vp_height = cam->vp_width / aspect_ratio
```

### Task 4-2: Ray Generation

**File**: `src/render/ray.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `ray_new` | `t_ray ray_new(t_point3 origin, t_vec3 dir)` | Constructor |
| `ray_at` | `t_point3 ray_at(t_ray ray, double t)` | `origin + t * dir` |
| `generate_ray` | `t_ray generate_ray(t_camera *cam, int px, int py)` | Camera ray for pixel (px, py) |

**`generate_ray` algorithm**:
```
1. u = (2.0 * (px + 0.5) / WIN_W - 1.0) * cam->vp_width / 2.0
2. v = (1.0 - 2.0 * (py + 0.5) / WIN_H) * cam->vp_height / 2.0
3. dir = normalize(cam->dir + u * cam->right + v * cam->up)
4. return ray_new(cam->pos, dir)
```

> Note: `u` maps pixel x from [-vp_width/2, +vp_width/2], `v` maps pixel y (flipped: top=+, bottom=-).

### Task 4-3: Render Loop

**File**: `src/render/render.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `render_scene` | `void render_scene(t_scene *scene)` | Iterate all pixels, compute color, write to image |
| `trace_ray` | `t_color3 trace_ray(t_scene *scene, t_ray ray)` | Main ray-trace: intersect + lighting |

**`render_scene` algorithm**:
```
1. init_camera(&scene->camera)
2. y = 0
3. while (y < WIN_H)
   a. x = 0
   b. while (x < WIN_W)
      i.   ray = generate_ray(&scene->camera, x, y)
      ii.  color = trace_ray(scene, ray)
      iii. img_pixel_put(&scene->img, x, y, color_to_int(color))
      iv.  x++
   c. y++
4. display_image(scene)
```

**`trace_ray` algorithm** (stub in Phase 4, completed in Phase 5-6):
```
1. hit = find_closest_hit(scene->objects, ray)
2. if (!hit.hit) -> return background_color (black or dark gray)
3. color = compute_lighting(scene, hit)
4. return color
```

**Acceptance**:
- With a stub that returns a gradient or solid color, the full render loop runs and displays an image in the window.

---

## Phase 5: Object Intersections

**Goal**: Ray-sphere, ray-plane, ray-cylinder intersections working.

### Task 5-1: Intersection Dispatcher

**File**: `src/render/render.c` (add to existing)

| Function | Signature | Description |
|----------|-----------|-------------|
| `find_closest_hit` | `t_hit find_closest_hit(t_object *objs, t_ray ray)` | Test all objects, return closest hit |
| `intersect_object` | `t_hit intersect_object(t_object *obj, t_ray ray)` | Dispatch by `obj->type` |

**`find_closest_hit` algorithm**:
```
1. closest.hit = 0, closest.t = INFINITY
2. current = objs
3. while (current)
   a. hit = intersect_object(current, ray)
   b. if (hit.hit && hit.t > EPSILON && hit.t < closest.t)
      closest = hit
   c. current = current->next
4. return closest
```

### Task 5-2: Sphere Intersection

**File**: `src/objects/sphere.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `intersect_sphere` | `t_hit intersect_sphere(t_sphere *sp, t_ray ray)` | Ray-sphere intersection |

**Algorithm** (quadratic equation):
```
oc = ray.origin - sp->center
a = dot(ray.dir, ray.dir)                         // = 1 if dir is normalized
b = 2.0 * dot(oc, ray.dir)
c = dot(oc, oc) - sp->radius * sp->radius
discriminant = b*b - 4*a*c

if (discriminant < 0) -> miss

t1 = (-b - sqrt(discriminant)) / (2*a)
t2 = (-b + sqrt(discriminant)) / (2*a)

t = t1 if t1 > EPSILON, else t2 if t2 > EPSILON, else miss

hit.point = ray_at(ray, t)
hit.normal = normalize(hit.point - sp->center)
hit.color = sp->color
hit.t = t
hit.hit = 1
```

> Inside handling: if `dot(hit.normal, ray.dir) > 0`, flip normal: `hit.normal = negate(hit.normal)`.

### Task 5-3: Plane Intersection

**File**: `src/objects/plane.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `intersect_plane` | `t_hit intersect_plane(t_plane *pl, t_ray ray)` | Ray-plane intersection |

**Algorithm**:
```
denom = dot(pl->normal, ray.dir)
if (fabs(denom) < EPSILON) -> miss  (ray parallel to plane)

t = dot(pl->point - ray.origin, pl->normal) / denom
if (t < EPSILON) -> miss  (behind camera)

hit.point = ray_at(ray, t)
hit.normal = pl->normal
if (dot(hit.normal, ray.dir) > 0)
    hit.normal = negate(hit.normal)
hit.color = pl->color
hit.t = t
hit.hit = 1
```

### Task 5-4: Cylinder Intersection

**File**: `src/objects/cylinder.c`

This is the most complex intersection. It requires checking the curved surface and both end caps.

| Function | Signature | Description |
|----------|-----------|-------------|
| `intersect_cylinder` | `t_hit intersect_cylinder(t_cylinder *cy, t_ray ray)` | Full cylinder intersection |
| `intersect_cy_body` | `t_hit intersect_cy_body(t_cylinder *cy, t_ray ray)` | Curved surface only |
| `intersect_cy_caps` | `t_hit intersect_cy_caps(t_cylinder *cy, t_ray ray)` | Top and bottom discs |
| `check_cy_cap` | `t_hit check_cy_cap(t_cylinder *cy, t_ray ray, t_point3 cap_center, t_vec3 cap_normal)` | Single disc |

**Curved surface algorithm**:
```
// Project ray onto plane perpendicular to cylinder axis
// cy->center is the center of the cylinder. Bottom cap = center - axis*height/2, Top = center + axis*height/2
bottom = cy->center - cy->axis * (cy->height / 2.0)

oc = ray.origin - bottom
d_proj = ray.dir - cy->axis * dot(ray.dir, cy->axis)
oc_proj = oc - cy->axis * dot(oc, cy->axis)

a = dot(d_proj, d_proj)
b = 2.0 * dot(d_proj, oc_proj)
c = dot(oc_proj, oc_proj) - cy->radius * cy->radius

discriminant = b*b - 4*a*c
if (discriminant < 0) -> miss

t1, t2 = solve quadratic

For each t (try smaller first):
  hit_point = ray_at(ray, t)
  m = dot(hit_point - bottom, cy->axis)   // project onto axis
  if (0 <= m <= cy->height):
    hit.t = t
    hit.point = hit_point
    hit.normal = normalize(hit_point - bottom - cy->axis * m)
    // flip normal if inside
    hit.color = cy->color
    hit.hit = 1
    break
```

**Cap intersection algorithm** (for each cap):
```
cap_center = bottom (or top = bottom + axis * height)
cap_normal = -cy->axis (bottom) or cy->axis (top)
// Intersect ray with plane at cap_center with normal = cy->axis
denom = dot(cy->axis, ray.dir)
if (fabs(denom) < EPSILON) -> miss
t = dot(cap_center - ray.origin, cy->axis) / denom
if (t < EPSILON) -> miss
hit_point = ray_at(ray, t)
dist = length(hit_point - cap_center)
if (dist > cy->radius) -> miss
// Valid cap hit
hit.normal = cap_normal (flip if needed)
```

**`intersect_cylinder`**: returns closest valid hit among body and two caps.

**Acceptance**:
- Sphere renders as a circle from any angle
- Plane renders as an infinite flat surface
- Cylinder renders with visible body and caps
- Multiple objects intersect correctly (closest wins)

---

## Phase 6: Lighting

**Goal**: Ambient + diffuse lighting, hard shadows.

### Task 6-1: Color Operations

**File**: `src/render/color.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `color_new` | `t_color3 color_new(double r, double g, double b)` | Constructor |
| `color_add` | `t_color3 color_add(t_color3 a, t_color3 b)` | Add two colors |
| `color_mul` | `t_color3 color_mul(t_color3 c, double t)` | Scale color |
| `color_hadamard` | `t_color3 color_hadamard(t_color3 a, t_color3 b)` | Per-channel multiply |
| `color_clamp` | `t_color3 color_clamp(t_color3 c)` | Clamp each channel to [0, 1] |

### Task 6-2: Lighting Computation

**File**: `src/render/light.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `compute_lighting` | `t_color3 compute_lighting(t_scene *scene, t_hit hit)` | Ambient + diffuse |
| `compute_diffuse` | `t_color3 compute_diffuse(t_light *light, t_hit hit)` | Lambert's cosine law |
| `is_in_shadow` | `int is_in_shadow(t_scene *scene, t_hit hit)` | Shadow ray test |

**`compute_lighting` algorithm**:
```
1. ambient_color = color_mul(hit.color, scene->ambient.ratio)
   // ambient = surface_color * ambient_ratio
   // (optionally multiply with ambient color too: hadamard)
   ambient_color = color_hadamard(ambient_color, scene->ambient.color)

2. if (is_in_shadow(scene, hit))
   return ambient_color   // only ambient, no diffuse

3. diffuse_color = compute_diffuse(&scene->light, hit)

4. result = color_add(ambient_color, diffuse_color)
5. return color_clamp(result)
```

**`compute_diffuse` algorithm** (Lambert):
```
1. light_dir = normalize(light->pos - hit.point)
2. cos_angle = dot(hit.normal, light_dir)
3. if (cos_angle < 0) -> cos_angle = 0   // light behind surface
4. diffuse = color_mul(hit.color, cos_angle * light->brightness)
5. return diffuse
```

**`is_in_shadow` algorithm**:
```
1. light_dir = light->pos - hit.point
2. light_dist = length(light_dir)
3. light_dir = normalize(light_dir)
4. shadow_origin = hit.point + hit.normal * EPSILON   // offset to avoid self-intersection
5. shadow_ray = ray_new(shadow_origin, light_dir)
6. shadow_hit = find_closest_hit(scene->objects, shadow_ray)
7. if (shadow_hit.hit && shadow_hit.t > 0 && shadow_hit.t < light_dist)
   return (1)   // in shadow
8. return (0)
```

> Critical: offset shadow ray origin by `EPSILON` along normal to prevent "shadow acne" (self-intersection).

**Acceptance**:
- Objects illuminated on the side facing the light, dark on opposite side
- Shadows visible on planes behind objects
- Moving objects (via translation in .rt) produces correct lighting position
- Ambient light prevents total darkness

---

## Phase 7: Polish

**Goal**: Robust error handling, no leaks, all edge cases covered.

### Task 7-1: Scene Cleanup

**File**: `src/scene/scene.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `init_scene` | `void init_scene(t_scene *scene)` | Zero-initialize all fields |
| `free_scene` | `void free_scene(t_scene *scene)` | Free object list, destroy mlx resources |
| `free_objects` | `void free_objects(t_object *objs)` | Walk and free linked list |

### Task 7-2: Main Entry Point

**File**: `src/main.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `main` | `int main(int argc, char **argv)` | Validate args, parse, render, event loop |

**`main` algorithm**:
```
1. if (argc != 2) -> exit_error("usage: ./miniRT <scene.rt>")
2. init_scene(&scene)
3. parse_file(argv[1], &scene)
4. init_window(&scene)
5. render_scene(&scene)
6. setup_hooks(&scene)
7. mlx_loop(scene.mlx)
8. return (0)
```

### Task 7-3: Edge Cases to Handle

| Case | Expected Behavior |
|------|-------------------|
| Empty .rt file | `Error\n` + "empty scene file" |
| .rt with only whitespace/empty lines | `Error\n` + "missing required elements" |
| Huge coordinate values (1e15) | Render normally (may look odd but no crash) |
| Diameter/height = 0 | `Error\n` + "invalid dimension" |
| Negative diameter/height | `Error\n` + "invalid dimension" |
| Direction vector = (0,0,0) | `Error\n` + "invalid direction" |
| Color value = 256 or -1 | `Error\n` + "color out of range" |
| FOV = 0 or FOV = 180 | Render (edge behavior OK) |
| Non-numeric values | `Error\n` + "invalid number" |
| Extra fields on a line | `Error\n` + "too many fields" |
| Missing fields on a line | `Error\n` + "too few fields" |
| Tabs as separators | Treat same as spaces |
| Multiple spaces between fields | Handle correctly (ft_split) |
| Binary file as input | Error gracefully |

### Task 7-4: Memory Leak Audit

Walk every allocation path and ensure `free()`:
1. `ft_split` results -> always `free_split()`
2. `get_next_line` returns -> always `free(line)`
3. `t_object` nodes -> `free_objects()` on exit
4. `mlx_destroy_image`, `mlx_destroy_window` before exit
5. `exit_error` calls `free_scene` before `exit(1)`

**Acceptance**:
- `leaks --atExit -- ./miniRT scenes/valid.rt` reports 0 leaks
- No segfault/crash with any malformed input from Task 7-3 table
- All 9 evaluation criteria pass

---

## Phase 8: Bonus

**Prerequisite**: Mandatory part scores 100%. Do NOT start bonus until Phase 7 is fully verified.

### Task 8-1: Specular Reflection (Phong Model)

**File**: `src/render/specular_bonus.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `compute_specular` | `t_color3 compute_specular(t_light *light, t_hit hit, t_vec3 view_dir)` | Phong specular highlight |

**Algorithm**:
```
1. light_dir = normalize(light->pos - hit.point)
2. reflect_dir = 2 * dot(hit.normal, light_dir) * hit.normal - light_dir
3. spec_angle = max(0, dot(reflect_dir, view_dir))
4. specular = pow(spec_angle, shininess)   // shininess ~ 32-128
5. return color_mul(color_new(1,1,1), specular * light->brightness)
```

Add to `compute_lighting`: `result = ambient + diffuse + specular`

### Task 8-2: Checkerboard Pattern

**File**: `src/render/checker_bonus.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `apply_checkerboard` | `t_color3 apply_checkerboard(t_hit hit, t_color3 base_color)` | Alternate color based on position |

**Algorithm**:
```
scale = 1.0  // checker size
ix = (int)floor(hit.point.x * scale)
iy = (int)floor(hit.point.y * scale)
iz = (int)floor(hit.point.z * scale)
if ((ix + iy + iz) % 2 == 0)
    return base_color
else
    return color_new(1, 1, 1) - base_color  // or just white
```

### Task 8-3: Colored and Multi-spot Lights

**Modify**: `t_scene` to hold `t_light *lights` (linked list or array) instead of single `t_light`.

**File**: `src/render/light_bonus.c`

- Parse multiple `L` lines (remove duplicate check for `L`)
- `compute_lighting` iterates all lights
- Each light's color multiplied into diffuse contribution

### Task 8-4: Cone

**File**: `src/objects/cone_bonus.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `intersect_cone` | `t_hit intersect_cone(t_cone *cone, t_ray ray)` | Ray-cone intersection |

**Algorithm** (similar to cylinder but with varying radius):
```
// Cone: vertex at apex, opening angle theta
// Equation: dot(P-apex, axis)^2 = dot(P-apex, P-apex) * cos^2(theta)
// Solve quadratic and clamp to height
```

### Task 8-5: Bump Mapping

**File**: `src/render/bump_bonus.c`

| Function | Signature | Description |
|----------|-----------|-------------|
| `apply_bump_map` | `t_vec3 apply_bump_map(t_hit *hit, /* texture data */)` | Perturb normal based on texture |

**Approach**: Use procedural noise (sine-based perturbation) or load a bump texture image.

### Bonus Makefile Rule

```makefile
BONUS_SRC = src/render/specular_bonus.c \
            src/render/checker_bonus.c \
            src/render/light_bonus.c \
            src/objects/cone_bonus.c \
            src/render/bump_bonus.c

bonus: CFLAGS += -D BONUS=1
bonus: $(NAME)
```

Use `#ifdef BONUS` in code to conditionally include bonus logic.

**Acceptance**: Each bonus feature visually verified with dedicated test scenes.

---

## File Summary (All Files)

### Headers (include/)

| File | Contents |
|------|----------|
| `minirt.h` | `t_scene`, `t_ambient`, `t_camera`, `t_light`, `t_img`, `WIN_W/H`, `EPSILON`, main prototypes |
| `vector.h` | `t_vec3`, `t_point3`, `t_color3`, all `vec3_*` prototypes |
| `render.h` | `t_ray`, `t_hit`, ray/render/color/light function prototypes |
| `objects.h` | `t_obj_type`, `t_sphere`, `t_plane`, `t_cylinder`, `t_object`, intersection prototypes |
| `parsing.h` | All `parse_*`, `validate_*`, `exit_error` prototypes |

### Sources (src/)

| File | Functions (max 5 each) |
|------|------------------------|
| `main.c` | `main` |
| `vector/vec_basic.c` | `vec3_new`, `vec3_add`, `vec3_sub`, `vec3_mul`, `vec3_div` |
| `vector/vec_ops.c` | `vec3_dot`, `vec3_cross`, `vec3_length`, `vec3_normalize`, `vec3_negate` |
| `parsing/parse_error.c` | `exit_error`, `is_valid_ext` |
| `parsing/parse_utils.c` | `parse_double`, `parse_color`, `parse_vec3`, `parse_normal`, `count_fields` |
| `parsing/parse_scene.c` | `parse_ambient`, `parse_camera`, `parse_light`, `dispatch_line` |
| `parsing/parse_objects.c` | `parse_sphere`, `parse_plane`, `parse_cylinder`, `add_object` |
| `parsing/parse_file.c` | `parse_file`, `validate_scene` |
| `parsing/validate.c` | `validate_range_d`, `validate_range_i`, `is_valid_number`, `free_split` |
| `scene/scene.c` | `init_scene`, `free_scene`, `free_objects` |
| `scene/camera.c` | `init_camera` |
| `window/window.c` | `init_window`, `destroy_window` |
| `window/hooks.c` | `handle_keypress`, `handle_close`, `setup_hooks` |
| `window/image.c` | `img_pixel_put`, `color_to_int`, `display_image` |
| `render/ray.c` | `ray_new`, `ray_at`, `generate_ray` |
| `render/render.c` | `render_scene`, `trace_ray`, `find_closest_hit`, `intersect_object` |
| `render/color.c` | `color_new`, `color_add`, `color_mul`, `color_hadamard`, `color_clamp` |
| `render/light.c` | `compute_lighting`, `compute_diffuse`, `is_in_shadow` |
| `objects/sphere.c` | `intersect_sphere` |
| `objects/plane.c` | `intersect_plane` |
| `objects/cylinder.c` | `intersect_cylinder`, `intersect_cy_body`, `intersect_cy_caps`, `check_cy_cap` |

**Total**: 21 source files, 5 headers (mandatory part).

---

## Dependency Graph

```
Phase 1 ─── vector.h, vec_basic.c, vec_ops.c, Makefile, libft
              │
Phase 2 ─── parsing.h, parse_*.c, validate.c  (depends on: vector, libft)
              │
Phase 3 ─── window.c, hooks.c, image.c, minirt.h  (depends on: miniLibX)
              │
Phase 4 ─── camera.c, ray.c, render.c, render.h  (depends on: vector, window)
              │
Phase 5 ─── sphere.c, plane.c, cylinder.c, objects.h  (depends on: vector, render)
              │
Phase 6 ─── color.c, light.c  (depends on: vector, render, objects)
              │
Phase 7 ─── scene.c, main.c  (integrates all modules)
              │
Phase 8 ─── *_bonus.c  (depends on: all mandatory)
```

Each phase can only begin after its dependencies are complete and tested.
