
# cub3D

/* Project is currenlty being updated to work with M1 processor and key codes */

## Collaborators

@jboucher154
@linhtng

## Description

cub3D is a walking simulator that uses ray-casting similar to Wolfensterin 3D. This project was completed as part of the 42-School Core Curriculum.

### Technologies

cub3D is written in C and uses MiniLibX, a small graphics library maintained by 42-School network.

### Focus of Project

- Use of C
- Using basic algorithms (flood-fill, DDA)
- Working with minimal graphics library
- Rigor
- Working in team

## Features

### Mandatory Part:

- Parsing map files
- Map validation
- Rendering and walking through raycast maze
- Collision detection

### Bonus Part:

- Minimap system
- Rotate view with mouse
- Raycast floor and ceiling
- Animated ceiling
- Doors that can be opened and closed

## How to Use

### requirements
- Compatible with MacOS and Linux

You will need a gcc compiler and the [minilibx library](https://github.com/42Paris/minilibx-linux)
 
 To run mandatory part:
``` 
$ git clone https://github.com/linhtng/cub3d
$ cd cub3d
$ make && ./cub3D ./maps/[select map]
```
Replace 'select map'  with a map fromt he maps folder /good to see the program run /bad to see error handling for map files.

To run bonus part:

``` 
$ make bonus && ./cub3D_bonus ./maps/bonus/[select map]
```

## Controls

| __Key__        | __Action__   |
| -------------  |:-------------:|
| W              | Move forward |
| A       | Move left      |
| D  | Move right      |
| S  | Move backwards      |
| Left Arrow  | Turn Left      |
| Right Arrow  | Turn Right      |
| Space  | Open/ Close doors      |
| Mouse  | Turn      |
| ESC  | Close window      |
<br><br>
