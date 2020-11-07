Final version of Cub3d project for 42. <br>
This project aims at creating a clone of Wolfenstein3D by implementing a simple raycaster with a custom graphic library.

Linux version of minilibx (42 custom graphic library) can be found on github: <br>
https://github.com/42Paris/minilibx-linux

Although a manual is provided, Harm Smits at Codam made a wonderfull work of documentation on this library: <br>
https://harm-smits.github.io/42docs/libs/minilibx

The engine itself is a C adaptation of lodev's C++ raycaster: <br>
https://lodev.org/cgtutor/raycasting.html

Instructions: <br>
"make" creates a simple executable to showcase basic functionnality required for Cub3D project.

"make bonus" creates an alternate version of the program that includes extended functionnalities like vertical camera rotation, character animations or distance fog.

Execution: <br>
Cub3D requires path to a valid map file with .cub extension as argument. <br>
"ressources/maps" folder contains sample maps for both versions of the program: <br>
	-"map.cub" is compatible with the standard "make" executable. <br>
	-"ice.cub" showcases the bonus version with custom textures. <br>

Controls (bonus version): <br>
-Strafing can be done with 'Z', 'Q', 'S', 'D' (or 'W', 'A', 'S', 'D' on QWERTY keyboards). <br>
-Camera rotation is bound to the arrow keys. <br>
-',' (or 'M' on QWERTY keyboards) toggles minimap on and off. <br>
-'R' sheathes and unsheathes woodaxe. <br>
-'Left Control' triggers a strike when axe is unsheathed. <br>
-'Left Shift' while strafing activates sprinting. <br>
-'C' activates crouching. <br>
-'Spacebar' triggers a jump. <br>
-'Esc' exits the program. <br>
