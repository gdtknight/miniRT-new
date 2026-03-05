# miniRT - Agent Roles and Work Process

## Agent Overview

This project uses three specialized agents coordinated by a PM (Project Manager). Each agent has a clearly defined scope and must follow the conventions in CLAUDE.md.

---

## Agent 1: Code Implementation Agent

### Role
Implement all C source code for miniRT according to the project specification and 42 Norm.

### Responsibilities
- Write all `.c` and `.h` files in `src/` and `include/` (bonus files use `_bonus.c`/`_bonus.h` suffix in the same directories)
- Write the `Makefile` (and `libft/Makefile` if needed)
- Ensure every file starts with the 42 header
- Ensure strict 42 Norm compliance on every file

### Rules
1. **Never exceed 25 lines per function** (excluding braces). Split early.
2. **Never exceed 5 variables per function, 4 parameters per function.**
3. **Never use**: `for`, `do...while`, `switch`, `case`, `goto`, ternary `?:`, VLA.
4. Use `while` loops only. Use function pointers or if-else chains instead of switch.
5. **Max 5 function definitions per `.c` file.** Plan file splits in advance.
6. **Max 80 columns per line.** Use tabs (not spaces) for indentation.
7. All structs declared in `.h` files only. Prefix: `s_` (struct), `t_` (typedef).
8. Return values always in parentheses: `return (val);`
9. Declare variables at top of function, one per line, aligned. Empty line before code.
10. No comments inside function bodies.
11. Pointer `*` attached to variable name: `char *str`, not `char* str`.

### Implementation Order (Priority)
1. **Phase 1 - Foundation**: libft integration, vector math, Makefile
2. **Phase 2 - Parsing**: `.rt` file reader, element parsers, validation
3. **Phase 3 - Window**: miniLibX setup, image buffer, event hooks (ESC, close)
4. **Phase 4 - Core Rendering**: camera rays, render loop, color output
5. **Phase 5 - Objects**: sphere, plane, cylinder intersections
6. **Phase 6 - Lighting**: ambient light, diffuse lighting, shadow rays
7. **Phase 7 - Polish**: edge cases, error messages, memory cleanup
8. **Phase 8 - Bonus** (only after mandatory is complete and tested):
   - Specular (Phong), checkerboard, multi-spot lights, cone, bump mapping
   - Bonus `.c` files use `_bonus.c` suffix, placed in `src/` subdirectories (e.g., `src/render/specular_bonus.c`, `src/objects/cone_bonus.c`)
   - Bonus `.h` files use `_bonus.h` suffix, placed in `include/` (e.g., `include/bonus.h`)

### Branching Strategy
- `main` - stable, reviewed code only
- `dev` - integration branch
- `feature/<module>` - one branch per phase/module (e.g., `feature/parsing`, `feature/render`)
- Each feature branch merges into `dev` via PR after code review

### Commit Convention
```
<type>(<scope>): <short description>

Types: feat, fix, refactor, style, build, test, docs
Scope: parsing, vector, render, objects, light, window, bonus
```
Example: `feat(parsing): add .rt file reader with element dispatch`

---

## Agent 2: Testing Agent

### Role
Validate correctness, robustness, and norm compliance of all code.

### Responsibilities
- Create and maintain test `.rt` scene files in `scenes/`
- Write test scripts in `tests/`
- Run norminette on all `.c` and `.h` files
- Verify memory management (no leaks, no crashes)
- Validate against the evaluation checklist

### Test Categories

#### 1. Norm Check
```bash
norminette src/ include/
```
Run on every commit. Any norm error = immediate fix required.

#### 2. Compilation Tests
- `make` compiles successfully with `-Wall -Wextra -Werror`
- `make` does not relink when run twice
- `make clean`, `make fclean`, `make re` work correctly
- `make bonus` compiles bonus part

#### 3. Scene Parsing Tests
Create `.rt` files for each case:

| Test | File | Expected |
|------|------|----------|
| Valid basic scene | `scenes/valid_basic.rt` | Renders without error |
| Missing ambient | `scenes/err_no_ambient.rt` | `Error\n` + message |
| Missing camera | `scenes/err_no_camera.rt` | `Error\n` + message |
| Invalid extension | `scenes/test.txt` | `Error\n` + message |
| Duplicate camera | `scenes/err_dup_camera.rt` | `Error\n` + message |
| Out of range values | `scenes/err_range.rt` | `Error\n` + message |
| Empty file | `scenes/err_empty.rt` | `Error\n` + message |
| Non-existent file | (no file) | `Error\n` + message |
| No arguments | (no args) | `Error\n` + message |
| Extra arguments | (2+ args) | `Error\n` + message |

#### 4. Rendering Tests (Visual)
One scene per evaluation criterion:

| Test | Scene | Validates |
|------|-------|-----------|
| Single sphere | `scenes/test_sphere.rt` | Eval #4 |
| Single plane | `scenes/test_plane.rt` | Eval #4 |
| Single cylinder | `scenes/test_cylinder.rt` | Eval #4 |
| Translation | `scenes/test_translate.rt` | Eval #5 |
| Rotation | `scenes/test_rotate.rt` | Eval #5 |
| Intersecting objects | `scenes/test_intersect.rt` | Eval #6 |
| Multiple same type | `scenes/test_multi.rt` | Eval #6 |
| Camera on X axis | `scenes/test_cam_x.rt` | Eval #7 |
| Camera on Y axis | `scenes/test_cam_y.rt` | Eval #7 |
| Camera on Z axis | `scenes/test_cam_z.rt` | Eval #7 |
| Camera arbitrary | `scenes/test_cam_arb.rt` | Eval #7 |
| Side lighting | `scenes/test_diffuse.rt` | Eval #8 |
| Lighting after translate | `scenes/test_light_tr.rt` | Eval #8 |
| Shadow on plane | `scenes/test_shadow.rt` | Eval #9 |
| Complex shadows | `scenes/test_complex.rt` | Eval #9 |

#### 5. Robustness Tests
- Segfault tests: malformed files, huge values, negative dimensions
- Memory leak check: `leaks miniRT` or `valgrind --leak-check=full ./miniRT`
- Window tests: minimize, resize, obscure, ESC, red cross

#### 6. Bonus Tests (if applicable)
- Specular highlight visible on sphere
- Checkerboard pattern on plane/sphere
- Multiple colored lights produce correct color mixing
- Cone renders correctly
- Bump map distorts surface normals visibly

### Test Execution Script
```bash
#!/bin/bash
# tests/run_tests.sh

echo "=== Norm Check ==="
norminette src/ include/

echo "=== Build Test ==="
make fclean && make
make  # Should print nothing (no relink)

echo "=== Error Handling ==="
./miniRT                          # No args
./miniRT scenes/test.txt          # Wrong extension
./miniRT nonexistent.rt           # Missing file
./miniRT scenes/err_no_ambient.rt # Missing required element

echo "=== Rendering Tests ==="
# Visual inspection required for each scene
for scene in scenes/test_*.rt; do
    echo "Testing: $scene"
    ./miniRT "$scene" &
    sleep 2
    kill $! 2>/dev/null
done

echo "=== Memory Leak Check ==="
leaks --atExit -- ./miniRT scenes/valid_basic.rt &
sleep 3
kill $! 2>/dev/null
```

---

## Agent 3: GitHub Deployment Agent

### Role
Manage the Git repository, branches, PRs, and releases.

### Responsibilities
- Initialize and maintain the Git repository
- Enforce branching strategy and PR workflow
- Ensure clean commit history
- Prepare final submission

### Repository Setup
```bash
git init
git remote add origin <repository-url>
```

### Branch Structure
```
main          # Stable, submission-ready code
├── dev       # Integration branch
│   ├── feature/libft       # libft integration
│   ├── feature/parsing     # .rt file parser
│   ├── feature/vector      # Vector math module
│   ├── feature/window      # miniLibX window management
│   ├── feature/render      # Core rendering pipeline
│   ├── feature/objects     # Object intersections
│   ├── feature/lighting    # Lighting and shadows
│   └── feature/bonus       # Bonus features
```

### PR Workflow
1. Code Agent pushes to `feature/<module>`
2. Test Agent reviews: runs norminette, compilation, tests
3. If all pass, merge `feature/<module>` -> `dev`
4. When a phase is complete and stable, merge `dev` -> `main`

### PR Template
```markdown
## Summary
- What was implemented/changed

## Checklist
- [ ] Norminette passes on all files
- [ ] Compiles with -Wall -Wextra -Werror without warnings
- [ ] No relink on second `make`
- [ ] No memory leaks
- [ ] No crashes (segfault, bus error, double free)
- [ ] Relevant test scenes added/updated
- [ ] Visual rendering verified (if applicable)
```

### .gitignore
```
# Objects and binaries
*.o
*.a
miniRT

# OS files
.DS_Store
*.dSYM/

# Editor files
*.swp
*~
.vscode/
.idea/

# miniLibX build artifacts
minilibx/*.o
```

### Release Checklist (Final Submission)
1. All evaluation criteria pass (sections 1-9)
2. Norminette clean on all `.c` and `.h` files
3. `make` / `make clean` / `make fclean` / `make re` all work
4. No memory leaks confirmed
5. No crashes with any valid or invalid input
6. Test scenes for each evaluation section included in `scenes/`
7. Clean git history (no merge conflicts, no WIP commits on main)
8. If bonus: `make bonus` compiles, bonus files use `_bonus.{c,h}` naming in `src/` and `include/`

### Tags
- `v1.0` - Mandatory part complete
- `v1.1` - Bonus part complete (if applicable)

---

## Work Process

### Phase Flow

```
Phase 1: Foundation
  Code Agent -> implements libft, vector math, Makefile
  Test Agent -> verifies norminette, compilation, vector unit tests
  Deploy Agent -> creates repo, feature/libft, feature/vector branches

Phase 2: Parsing
  Code Agent -> implements .rt parser and validation
  Test Agent -> creates error/valid scene files, runs all parsing tests
  Deploy Agent -> PR feature/parsing -> dev

Phase 3: Window
  Code Agent -> implements miniLibX window, hooks, image buffer
  Test Agent -> tests ESC, close, minimize, resize
  Deploy Agent -> PR feature/window -> dev

Phase 4: Core Rendering
  Code Agent -> implements camera, ray generation, render loop
  Test Agent -> visual tests with solid-color output
  Deploy Agent -> PR feature/render -> dev

Phase 5: Objects
  Code Agent -> implements sphere, plane, cylinder intersections
  Test Agent -> per-object scene tests, intersection edge cases
  Deploy Agent -> PR feature/objects -> dev

Phase 6: Lighting
  Code Agent -> implements ambient, diffuse, shadows
  Test Agent -> lighting and shadow scene tests (eval sections 8-9)
  Deploy Agent -> PR feature/lighting -> dev

Phase 7: Polish
  Code Agent -> fixes edge cases, finalizes error handling
  Test Agent -> full evaluation dry-run (all 9 sections)
  Deploy Agent -> merge dev -> main, tag v1.0

Phase 8: Bonus (optional)
  Code Agent -> implements bonus features as *_bonus.c in src/ subdirectories
  Test Agent -> bonus-specific tests
  Deploy Agent -> PR feature/bonus -> dev -> main, tag v1.1
```

### Communication Protocol

- **Code Agent** notifies Test Agent when a feature is ready for testing
- **Test Agent** reports pass/fail with specific details back to Code Agent
- **Deploy Agent** only merges after Test Agent gives approval
- **PM** resolves conflicts between agents and adjusts priorities

### Definition of Done (per feature)

1. Norminette passes
2. Compiles without warnings
3. No memory leaks
4. Relevant tests pass
5. PR reviewed and approved
6. Merged to `dev`
