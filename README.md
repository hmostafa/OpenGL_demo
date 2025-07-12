# OpenGL_demo

This a comprehensive OpenGL C++ program that demonstrates various computer graphics concepts. Here's what the program includes:


Features Demonstrated:
1. Basic 2D Shapes (Demo 0)

Triangle, rectangle, circle, pentagon, hexagon, and star
Each shape uses different colors for easy identification

2. Transformations (Demo 1)

Rotation: Press 'R' to rotate the orange square
Translation: Press 'T' to translate the square
Scaling: Press 'S' to scale the square
Shows both the transformed shape and original position for reference

3. Clipping (Demo 2)

Demonstrates scissor test clipping
Press 'C' to toggle clipping on/off
Shows how objects are clipped against a defined window

4. 3D Shapes (Demo 3)

Cube, sphere, and teapot with 3D lighting
Automatic rotation animation
Proper 3D perspective projection

5. Fill Patterns (Demo 4)

Solid fill: Regular filled circle
Wireframe: Outline-only circle
Stippled pattern: Checkered pattern fill

Controls:

0-4: Switch between different demos
R: Rotate objects (in transformation demo)
T: Translate objects (in transformation demo)
S: Scale objects (in transformation demo)
C: Toggle clipping (in clipping demo)
W: Toggle wireframe mode globally
ESC: Exit program

Compilation Instructions:
bashg++ -o graphics_demo graphics_demo.cpp -lGL -lGLU -lglut
Key Learning Points:

Shape Creation: Using OpenGL primitives (GL_TRIANGLES, GL_QUADS, GL_POLYGON)
Matrix Transformations: Using glTranslate, glRotate, glScale
Clipping: Using glScissor for rectangular clipping
Lighting: Basic OpenGL lighting setup for 3D objects
Fill Techniques: Solid, wireframe, and stippled patterns
3D Rendering: Perspective projection and depth testing

The program provides an interactive way to explore fundamental computer graphics concepts and serves as a solid foundation for learning OpenGL programming.
