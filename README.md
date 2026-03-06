*This project has been created as part of the 42 curriculum by roubelka, ael-most.*

# cub3D 🏰

A small raycasting engine inspired by the legendary **Wolfenstein 3D** (1992) — the game that basically invented the first-person shooter genre. Using nothing but the C language and the MiniLibX graphics library, we built a real-time 3D maze renderer from scratch.

You feed it a `.cub` map file, and it drops you inside that maze in first person. You can walk around, rotate your view, and see textured walls — all computed on the fly, one vertical screen column at a time.

---

## Description

### What is this?

Cub3D is a **42 school project** that asks you to recreate the rendering technique behind Wolfenstein 3D: **raycasting**. The idea is deceptively simple — you're standing on a 2D grid map, and for every pixel column on your screen, you shoot an invisible ray forward until it hits a wall. The distance to that wall tells you how tall to draw it. Do that 1280 times across the screen, slap textures on the walls, and suddenly you're looking at a 3D world.

### How the raycasting works

Imagine you're holding a flashlight in a dark room made of square tiles. You sweep the flashlight left to right across a 60° arc in front of you. For each tiny angle:

1. **March the ray** through the grid using the **DDA algorithm** — it cleverly jumps from one grid line to the next instead of crawling pixel by pixel, which keeps things fast.
2. **When it hits a wall**, you measure the distance. A close wall becomes a tall column on screen; a far wall becomes a short one.
3. **Pick the right texture** (North, South, East, or West face) based on which side of the wall the ray struck.
4. **Apply fisheye correction** — without it, walls would look curved like a barrel. We fix this by multiplying the distance by `cos(angle difference)`.
5. **Draw the column**: ceiling color on top, textured wall in the middle, floor color at the bottom.

Repeat for all 1280 columns. That's one frame. Re-render every time the player moves, and you have a real-time 3D engine running in pure C.

### Features

- Real-time first-person 3D rendering using raycasting
- Textured walls with four distinct XPM textures (N/S/E/W)
- Configurable floor and ceiling colors (RGB)
- Smooth player movement (forward, backward, strafe left/right)
- Keyboard-based view rotation (left/right arrow keys)
- Robust `.cub` map parser with full validation (closed walls, valid characters, single player spawn)
- Wall collision detection with margin buffer

---

## Instructions

### Prerequisites

- **macOS** (this build uses the macOS MiniLibX with OpenGL and AppKit frameworks)
- `cc` compiler (clang, comes with Xcode Command Line Tools)
- `make`

If you don't have Xcode Command Line Tools:
xcode-select --install### Compilation

Clone the repository, then from the project root:

makeThis builds **libft**, the **MiniLibX** library, and the final `cub3D` executable. To clean up:

make clean    # remove object files
make fclean   # remove object files + executable
make re       # full rebuild### Running

./cub3D maps/subject_map.cub
### Controls
*   **W / A / S / D**: Move the player.
*   **Left / Right Arrow**: Rotate the camera.
*   **ESC**: Exit the game cleanly.
*   **Red Cross (Window)**: Close the window.

### Map format

A `.cub` file contains texture paths, floor/ceiling colors, and a 2D grid map:

## Resources

This project was built on the shoulders of giants. Here are the core resources and references used to understand the math and logic behind the engine:

### Documentation & Tutorials
*   **[Lodev's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)**: The absolute "bible" for raycasting engines. It breaks down the DDA (Digital Differential Analyzer) algorithm and the math for textured walls.
*   **[MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)**: Essential reference for handling windows, images, and events within the 42 school's graphical library.
*   **[Wolfenstein 3D Source Code](https://github.com/id-Software/wolf3d)**: Studying the original code helped clarify how the pioneers solved these problems in 1992.

---