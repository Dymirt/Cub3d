# Cub3D Project 
This project is a simple 3D game inspired by **Wolfenstein 3D**, created using the C language and the **minilibx** library. The game features basic 3D rendering with raycasting, textures, map parsing, and player movement.

## Known Bugs and Issues

### 1. Minimap Rendering (Segmentation Fault) (BONUS part)
- **Issue**: The minimap structure has been created, but there is a **segmentation fault** when rendering the minimap and calling the function in `main()`.
- **File**: `src/minimap_imag.c`
- **Status**: Bug needs to be resolved to properly render the minimap.

### 2. Jump Functionality
- **Issue**: The jump movement is not functioning yet.
- **File**: `src/maneuvers.c`
- **Status**: Still in progress and needs further development.

### 3. Animated texture
- **creating algorethm**: to render animated texture -> still in progress 

## Features

- Raycasting for rendering 3D environments
- Basic player movement (forward, backward, strafe left, strafe right, jump)
- Texture mapping
- Map parsing
- In-progress minimap rendering

## Current Structure

### Source Files

- **`src/minimap_imag.c`**: This file handles the minimap rendering.
- **`src/maneuvers.c`**: All player movements are controlled in this file.
  
### Player Movement

The player's movement is fully functional, including walking in all directions. The movements are reconstructed and unified into a single function to manage all actions (in `src/maneuvers.c`).
