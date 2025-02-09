# cub3D
Cub3D is a 42 school team project to create a dynamic view inside a 3D maze. Using the [MLX42 library](https://github.com/codam-coding-college/MLX42), we must implement raycasting in the style of the famous [Wolfenstein 3D](http://users.atw.hu/wolf3d/) game, the first true FPS in videogame history.

## Status

Validated. Grade: 125%.

## Clone

Clone the MLX42 library in desktop:

```shell
cd ~/Desktop
git clone https://github.com/codam-coding-college/MLX42.git
cd MLX42
cmake -B build # build here refers to the outputfolder.
cmake --build build -j4 # or do make -C build -j4
```
Clone the repository:

```shell
git clone https://github.com/asmaeelk1/Cub_3D.git
```


To compile the mandatory part, `cd` into the cloned directory and:

```shell
make
```

To compile the bonus part, `cd` into the cloned directory and:

```shell
make bonus
```
Note: you will need to change both mandatory and bonus header /home/oel-feng/.... to your specified machine user name instead of oel-feng.


To run the program:

```shell
./cub3D <path/to/map.cub>
```
or
```shell
./cub3D_bonus <path/to/map.cub>
```
Note: some maps are only bonus specific and will throw an invalid map error if passed to mandatory (any map containing doors portraited as D in the map).


The program takes a map file as an argument. Maps are available in the `maps` directory. There are good maps which the program should run smoothly with, and bad maps which the program should reject.
For example:

- `./cub3D <path/to/valid/map` should run.

- `./cub3D <path/to/invalid/map>` should print an error and abort.


## Controls

Controls for movement and rotation are:

- `W`: move forward
- `S`: move backward
- `A`: strafe left
- `D`: strafe right
- `left arrow`: rotate left
- `right arrow`: rotate right
- `mouse`: rotate by moving the mouse (bonus only)
- `space`: play weapon inspect animation (bonus only)
- `O`: open door (bonus only)
- `C`: close door (bonus only)


## Useful Resources

Useful resources for this project are:

- MLX42: [MLX42 official docs](https://github.com/codam-coding-college/MLX42/tree/master/docs)
- Raycasting: [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html)
- Textures: [Lode's Computer Graphics Tutorial - Textured Raycaster](https://lodev.org/cgtutor/raycasting.html#Textured_Raycaster)

## Credit
This two-person project was done by both [Asmae ELKHATTAB](https://github.com/asmaeelk1) and [Ouadie El Fengour](https://github.com/Wayde-Ouadie).
