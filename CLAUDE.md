# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

miniRT is a ray tracer written in C for 42 School. It renders 3D scenes from `.rt` files, supporting sphere, plane, and cylinder primitives with ambient and diffuse lighting. All code must comply with 42 Norm v4.1.

## Build Commands

```bash
make          # Build miniRT executable
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Full rebuild
make bonus    # Build with bonus features
```

```bash
norminette src/ include/         # Check norm compliance (must pass with zero errors)
```

```bash
./miniRT scenes/example.rt       # Run with a scene file
leaks --atExit -- ./miniRT scenes/example.rt   # Check for memory leaks (macOS)
```

## Build Configuration

- **Compiler**: `cc` with `-Wall -Wextra -Werror`
- **Executable**: `miniRT`
- **Libraries**: miniLibX, libft (in `libft/`), math (`-lm`)
- **No relinking**: `make` run twice must not recompile unchanged files
- **No wildcards**: source files must be explicitly listed in Makefile

## 42 Norm v4.1 (Mandatory - violations = grade 0)

### Critical Constraints
- **Max 25 lines per function** (excluding braces)
- **Max 80 columns per line** (tabs count as visual width)
- **Max 4 parameters per function**
- **Max 5 variable declarations per function**
- **Max 5 function definitions per `.c` file**
- **Indent with tabs** (4-char-wide, ASCII 9), not spaces

### Forbidden Constructs
`for`, `do...while`, `switch`, `case`, `goto`, ternary `?:`, VLA, implicit types, multiline macros, comments inside function bodies

### Naming & Style
- snake_case only. Prefixes: `s_` (struct), `t_` (typedef), `u_` (union), `e_` (enum), `g_` (global)
- No global variables unless `const` or `static`
- Pointer `*` attached to variable name: `char *str`
- Return values in parentheses: `return (value);`
- Single tab between return type and function name
- Variables declared at top of function, one per line, aligned to same column
- Empty line between declarations and code body; no other empty lines in functions
- Declaration and initialization cannot be on same line (except global/static/const)
- Braces on their own line (except struct/enum/union declarations)
- One empty line between functions; no consecutive empty lines
- No trailing whitespace; no consecutive spaces
- Every `.c` and `.h` file must start with the 42 standard header comment
- Structs declared in `.h` files only
- Include guards: `#ifndef FT_FOO_H` / `# define FT_FOO_H` / `#endif`
- Use `while` loops only (no `for`). Use if-else chains instead of switch.

### Allowed External Functions
`open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`, math library (`-lm`), all miniLibX functions, `gettimeofday()`

## Project Structure

```
miniRT-new/
├── Makefile
├── include/          # Headers: minirt.h, parsing.h, vector.h, render.h, objects.h
├── libft/            # libft library with its own Makefile
├── minilibx/         # miniLibX library
├── src/
│   ├── main.c        # Entry point
│   ├── parsing/      # .rt file reading, element dispatch, validation
│   ├── vector/       # Vector math (add, sub, scale, dot, cross, normalize)
│   ├── render/       # Ray creation, render loop, color ops, lighting/shadows
│   ├── objects/      # Sphere, plane, cylinder intersection
│   ├── scene/        # Scene init/cleanup, camera setup
│   └── window/       # miniLibX window, event hooks, image buffer
└── scenes/           # Test .rt scene files
```

## Scene File Format (.rt)

Capital-letter elements (A, C, L) declared once only. Fields separated by spaces.

| ID | Format |
|----|--------|
| `A` | `A <ratio:0-1> <R,G,B:0-255>` |
| `C` | `C <x,y,z> <dir:-1~1> <FOV:0-180>` |
| `L` | `L <x,y,z> <brightness:0-1> <R,G,B>` |
| `sp` | `sp <center:x,y,z> <diameter> <R,G,B>` |
| `pl` | `pl <point:x,y,z> <normal:-1~1> <R,G,B>` |
| `cy` | `cy <center:x,y,z> <axis:-1~1> <diameter> <height> <R,G,B>` |

Misconfigured files: print `"Error\n"` + explicit message, exit cleanly. No segfaults, leaks, or double frees.

## Architecture Notes

- **Rendering pipeline**: Camera generates rays per pixel -> test intersection with all objects -> find closest hit -> compute lighting (ambient + diffuse) -> cast shadow rays for occlusion -> output pixel color
- **Ray-object intersection**: quadratic equations for sphere/cylinder, dot product for plane
- **Cylinder**: handle curved surface AND two end caps
- **Camera**: construct orthonormal basis from direction vector and up-reference
- Use miniLibX image buffers (`mlx_new_image`, `mlx_get_data_addr`) for pixel rendering

## Commit Convention

```
<type>(<scope>): <short description>
Types: feat, fix, refactor, style, build, test, docs
Scope: parsing, vector, render, objects, light, window, bonus
```

## Detailed Plan

See [PROJECT_PLAN.md](PROJECT_PLAN.md) for the full implementation blueprint including all struct definitions, function signatures, algorithms, and per-phase acceptance criteria.

## Implementation Phases

1. Foundation: libft, vector math, Makefile
2. Parsing: .rt file reader, validation
3. Window: miniLibX setup, event hooks
4. Core Rendering: camera rays, render loop
5. Objects: sphere, plane, cylinder intersections
6. Lighting: ambient, diffuse, shadow rays
7. Polish: edge cases, error messages, memory cleanup
8. Bonus (only after mandatory is perfect): specular/Phong, checkerboard, multi-spot lights, cone, bump mapping
   - Bonus source files use `_bonus.c` suffix and go in `src/` subdirectories (e.g., `src/render/specular_bonus.c`)
   - Bonus headers use `_bonus.h` suffix and go in `include/` (e.g., `include/bonus.h`)

## Evaluation Criteria

1. `make` compiles without relinking
2. `.rt` parsing with proper error handling (misconfigured file = `Error\n` + message)
3. Window management (ESC, red cross, minimize, resize - content must stay consistent)
4. Sphere, plane, cylinder rendering without glitching
5. Translation and rotation transforms
6. Multiple intersecting objects (including same type multiple times)
7. Camera works from any axis and arbitrary positions
8. Diffuse lighting with correct illumination after translation
9. Hard shadows properly displayed
