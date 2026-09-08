# Temple Adventure

237/2022 - Djordje Sajic.  
An immersive 3D computer graphics application featuring a jungle environment, ancient temple, dynamic skybox, first-person camera movement, and an interactive torch mechanic with adjustable light reach.  

## Controls

W, A, S, D -> Player movement  
Mouse -> Camera look / rotation  
Tab -> Toggle GUI menu on  
Esc -> Exit Application  
E -> Toggle torch light on/off  
F -> Swing torch  
1 -> Increase torch light reach  
2 -> Decrease torch light reach  

## Features

### Fundamental:

[x] Model (torch,temple,jungle) with lighting  
[x] Two types of lighting (Directional and Point) with customizable colors and movement through GUI or ACTIONS  
[x] Key F (Swing Torch) --- 0.0s ---Triggers---> Start Swing Animation (rotates 45 deg in 0.25sec) ---> 1.0s ---Triggers---> Reset Swing State in 0.25sec

### Group A:

[ ] Frame-buffers with post-processing  
[ ] Off-screen Anti-Aliasing  
[ ] Parallax Mapping  
[ ] Bloom with the use of HDR  

### Group B:
[ ] Deferred Shading  
[ ] Point Shadows  
[ ] SSAO  

### Engine improvement:

[x] Custom material parsing integration (GLSL shaders receive model color values from .mtl files into material_diffuse)

## Models:

[Torch](https://poly.pizza/m/pNsfJzhXiD)  
[Jungle](https://poly.pizza/m/0nsE2b8uXZy)  
[Temple](https://poly.pizza/m/cf3QwX0JqGN)  

## Textures

[Skybox Pack](https://screamingbrainstudios.itch.io/cloudy-skyboxes-pack)
