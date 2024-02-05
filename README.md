<div align="center">
  <h1>
    📗 MiniRT
  </h1>
  <p>
    <b><i>A custom built ray tracer</i></b>
  </p>
  <p>
    Developed using&nbsp&nbsp
    <a href="https://skillicons.dev">
      <img src="https://skillicons.dev/icons?i=c,vscode" />
    </a>
  </p>
</div>

<br />

## Table Of Contents
- [Features](#features)
- [Installation](#installation)
- [Example](#example)
- [Contributors](#contributors)
- [License](#license)

## Features
- **Anti-Aliasing:** Reduces the jagged edge effects to produce a smoother image. This works by sending multiple rays er pixel and averaging the ray colour.
- **Objects:** Supports the rendering of the following 3D objects:
  - Cylinder
  - Sphere
  - Plane
- **Lighting:** Supports the full phong reflection model to simulate the interaction of light with the surfaces. This creates a realistic depiction of shadows, reflections and diffusion.
- **Ambient Light:** Adds a constant indirect ambient light throughout the scene.
- **Camera:** Conditionally calculate a virtual viewport based on the camera's FOV (Field of view). This ensures images are rendered correctly.
- **Multi-Threading**: Utilizes multi-threading to improve rendering performance, enabling faster image rendering.
- **Documentation:** All functions have doxygen comments to ensure readability and to better understand the underlying logic at a glance.

## Installation
1. Clone the repository.
```bash
git clone https://github.com/RealConrad/42minirt.git
```
2. Enter the directory.
```bash
cd 42minirt
```
3. Compile the program.
```bash
make
```
3. Run the program (it may take a while to open the window, depending on the rays per pixels and the scene contents).
```
./miniRT scene/<file_name>
```

## Example
The program only accepts 2 arguments: The executable and the scene you want to run.
```bash
./miniRT scene/basic_sphere.rt
```

## Contributors
- [RealConrad](https://github.com/RealConrad)
- [itseugen](https://github.com/itseugen)

## Liencse
[MIT](https://choosealicense.com/licenses/mit/)
