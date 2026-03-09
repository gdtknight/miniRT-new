# miniRT

A minimal ray tracer built in C as part of the 42 School curriculum.

## Features

### Mandatory
- Scene parsing (`.rt` files) with full validation and error reporting
- Sphere, plane, and cylinder rendering (including cylinder end caps)
- Ambient and diffuse lighting with hard shadows
- Camera positioning and orientation with configurable FOV

### Bonus
- Specular/Phong lighting model
- Checkerboard texture pattern on objects
- Multiple spotlights support
- Cone primitive rendering
- Interactive camera, light, and object movement
- Camera rotation controls
- Object resize controls
- Object selection with highlight tint
- HUD overlay for interactive mode

## Build

```bash
make        # Build mandatory part
make bonus  # Build with bonus features
make clean  # Remove object files
make fclean # Remove all build artifacts
make re     # Rebuild from scratch
```

## Usage

```bash
./miniRT <scene.rt>
```

## Scene File Format

Fields are separated by spaces. Capital-letter identifiers (`A`, `C`, `L`) must appear exactly once.

| ID | Format | Description |
|----|--------|-------------|
| `A` | `A <ratio:0-1> <R,G,B:0-255>` | Ambient light |
| `C` | `C <x,y,z> <dir:-1~1> <FOV:0-180>` | Camera |
| `L` | `L <x,y,z> <brightness:0-1> <R,G,B>` | Point light |
| `sp` | `sp <center:x,y,z> <diameter> <R,G,B>` | Sphere |
| `pl` | `pl <point:x,y,z> <normal:-1~1> <R,G,B>` | Plane |
| `cy` | `cy <center:x,y,z> <axis:-1~1> <diameter> <height> <R,G,B>` | Cylinder |
| `co` | `co <apex:x,y,z> <axis:-1~1> <diameter> <height> <R,G,B>` | Cone (bonus) |

Append `checker` after the color to apply a checkerboard pattern to any object (bonus).

### Example Scene

```
A  0.2           255,255,255
C  0,5,20        0,-0.2,1    70
L  -10,10,10     0.8         255,255,255

pl  0,0,0        0,1,0       200,100,50
sp  0,2,10       4           100,200,50
cy  5,0,15       0,1,0       3  6  50,100,200
```

Misconfigured files print `Error\n` with an explicit message and exit cleanly.

## Controls (Bonus)

The bonus build supports interactive scene manipulation. Select objects and the camera/light with the keyboard.

| Key | Action |
|-----|--------|
| `Tab` | Cycle selection (camera → light → objects) |
| `W` / `S` | Move selected object/camera forward / backward |
| `A` / `D` | Move selected object/camera left / right |
| `Q` / `E` | Move selected object/camera up / down |
| `↑` / `↓` | Rotate camera pitch up / down |
| `←` / `→` | Rotate camera yaw left / right |
| `+` / `-` | Resize selected object (diameter / height) |
| `ESC` | Close window and exit |

A HUD overlay displays the current selection and mode.

## Release History

| Tag | Description |
|-----|-------------|
| v1.2 | Interactive controls — camera/light/object movement, camera rotation, object resize, HUD overlay, and selected object highlight tint added to bonus mode. |
| v1.1 | Refactor — all `#ifdef BONUS` guards removed from shared sources. Bonus functionality lives exclusively in `_bonus.c`/`_bonus.h` files, eliminating conditional compilation from the mandatory code path. |
| v1.0 | Initial release — mandatory ray tracer (sphere, plane, cylinder, ambient+diffuse lighting, hard shadows) plus bonus features (specular/Phong, checkerboard, multi-light, cone). Memory leaks plugged and 42 Norm violations fixed. |
