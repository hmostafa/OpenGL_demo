#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <cmath>
#include <vector>

// Global variables for animation and interaction
float rotationAngle = 0.0f;
float scaleX = 1.0f, scaleY = 1.0f;
float translateX = 0.0f, translateY = 0.0f;
int currentDemo = 0;
bool enableClipping = false;
bool wireframe = false;

// Colors for different demonstrations
float colors[][3] = {
    {1.0f, 0.0f, 0.0f}, // Red
    {0.0f, 1.0f, 0.0f}, // Green
    {0.0f, 0.0f, 1.0f}, // Blue
    {1.0f, 1.0f, 0.0f}, // Yellow
    {1.0f, 0.0f, 1.0f}, // Magenta
    {0.0f, 1.0f, 1.0f}, // Cyan
    {1.0f, 0.5f, 0.0f}, // Orange
    {0.5f, 0.0f, 0.5f}  // Purple
};

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    // Set up lighting
    GLfloat lightPos[] = {2.0f, 2.0f, 2.0f, 1.0f};
    GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat lightDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
}

void drawBasicShapes() {
    glDisable(GL_LIGHTING);
    
    // Triangle
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.8f, -0.5f);
        glVertex2f(-0.5f, 0.0f);
        glVertex2f(-0.2f, -0.5f);
    glEnd();
    
    // Rectangle
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, -0.3f);
        glVertex2f(0.3f, -0.3f);
        glVertex2f(0.3f, 0.1f);
        glVertex2f(-0.1f, 0.1f);
    glEnd();
    
    // Circle (approximated with polygon)
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i += 10) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(0.6f + 0.15f * cos(angle), 0.2f + 0.15f * sin(angle));
    }
    glEnd();
    
    // Pentagon
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 5; i++) {
        float angle = i * 2.0f * M_PI / 5.0f - M_PI / 2.0f;
        glVertex2f(0.6f + 0.12f * cos(angle), -0.2f + 0.12f * sin(angle));
    }
    glEnd();
    
    // Hexagon
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 6; i++) {
        float angle = i * 2.0f * M_PI / 6.0f;
        glVertex2f(-0.6f + 0.12f * cos(angle), 0.2f + 0.12f * sin(angle));
    }
    glEnd();
    
    // Star
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < 5; i++) {
        float angle1 = i * 2.0f * M_PI / 5.0f - M_PI / 2.0f;
        float angle2 = (i + 1) * 2.0f * M_PI / 5.0f - M_PI / 2.0f;
        
        glVertex2f(-0.6f, -0.6f); // Center
        glVertex2f(-0.6f + 0.15f * cos(angle1), -0.6f + 0.15f * sin(angle1));
        glVertex2f(-0.6f + 0.08f * cos(angle1 + M_PI / 5.0f), -0.6f + 0.08f * sin(angle1 + M_PI / 5.0f));
        
        glVertex2f(-0.6f, -0.6f); // Center
        glVertex2f(-0.6f + 0.08f * cos(angle1 + M_PI / 5.0f), -0.6f + 0.08f * sin(angle1 + M_PI / 5.0f));
        glVertex2f(-0.6f + 0.15f * cos(angle2), -0.6f + 0.15f * sin(angle2));
    }
    glEnd();
}

void drawTransformations() {
    glDisable(GL_LIGHTING);
    
    // Save current matrix
    glPushMatrix();
    
    // Apply transformations
    glTranslatef(translateX, translateY, 0.0f);
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
    glScalef(scaleX, scaleY, 1.0f);
    
    // Draw a square that will be transformed
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, -0.2f);
        glVertex2f(0.2f, -0.2f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(-0.2f, 0.2f);
    glEnd();
    
    // Draw coordinate axes
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
        glVertex2f(-0.3f, 0.0f);
        glVertex2f(0.3f, 0.0f);
        glVertex2f(0.0f, -0.3f);
        glVertex2f(0.0f, 0.3f);
    glEnd();
    
    glPopMatrix();
    
    // Draw original position for reference
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.2f, -0.2f);
        glVertex2f(0.2f, -0.2f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(-0.2f, 0.2f);
    glEnd();
}

void drawClippingDemo() {
    glDisable(GL_LIGHTING);
    
    // Define clipping window
    if(enableClipping) {
        glEnable(GL_SCISSOR_TEST);
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        int scissorX = viewport[2] / 2 - 100;
        int scissorY = viewport[3] / 2 - 100;
        glScissor(scissorX, scissorY, 200, 200);
    }
    
    // Draw clipping window outline
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.3f, -0.3f);
        glVertex2f(0.3f, -0.3f);
        glVertex2f(0.3f, 0.3f);
        glVertex2f(-0.3f, 0.3f);
    glEnd();
    
    // Draw objects that will be clipped
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.1f);
        glVertex2f(0.1f, -0.1f);
        glVertex2f(0.1f, 0.1f);
        glVertex2f(-0.5f, 0.1f);
    glEnd();
    
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i += 10) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(0.2f + 0.2f * cos(angle), 0.2f + 0.2f * sin(angle));
    }
    glEnd();
    
    if(enableClipping) {
        glDisable(GL_SCISSOR_TEST);
    }
}

void draw3DShapes() {
    glEnable(GL_LIGHTING);
    
    // Cube
    glPushMatrix();
    glTranslatef(-0.5f, 0.0f, 0.0f);
    glRotatef(rotationAngle, 1.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidCube(0.3);
    glPopMatrix();
    
    // Sphere
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.15, 20, 20);
    glPopMatrix();
    
    // Teapot
    glPushMatrix();
    glTranslatef(0.5f, 0.0f, 0.0f);
    glRotatef(rotationAngle, 1.0f, 0.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glutSolidTeapot(0.1);
    glPopMatrix();
}

void drawFillingDemo() {
    glDisable(GL_LIGHTING);
    
    // Solid fill
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i += 10) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(-0.5f + 0.15f * cos(angle), 0.0f + 0.15f * sin(angle));
    }
    glEnd();
    
    // Wireframe
    glColor3f(0.0f, 1.0f, 0.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i += 10) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(0.0f + 0.15f * cos(angle), 0.0f + 0.15f * sin(angle));
    }
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // Stippled pattern
    glEnable(GL_POLYGON_STIPPLE);
    GLubyte stipple[] = {
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55
    };
    glPolygonStipple(stipple);
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i += 10) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(0.5f + 0.15f * cos(angle), 0.0f + 0.15f * sin(angle));
    }
    glEnd();
    glDisable(GL_POLYGON_STIPPLE);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Set up 3D view for 3D shapes demo
    if(currentDemo == 3) {
        gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }
    
    switch(currentDemo) {
        case 0:
            drawBasicShapes();
            break;
        case 1:
            drawTransformations();
            break;
        case 2:
            drawClippingDemo();
            break;
        case 3:
            draw3DShapes();
            break;
        case 4:
            drawFillingDemo();
            break;
    }
    
    // Draw instructions
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.95f, 0.9f);
    
    const char* instructions[] = {
        "Demo 0: Basic 2D Shapes",
        "Demo 1: Transformations (R/T/S keys)",
        "Demo 2: Clipping (C key to toggle)",
        "Demo 3: 3D Shapes",
        "Demo 4: Fill Patterns"
    };
    
    const char* str = instructions[currentDemo];
    while(*str) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *str);
        str++;
    }
    
    glRasterPos2f(-0.95f, 0.85f);
    str = "Press 0-4 to switch demos, ESC to quit";
    while(*str) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *str);
        str++;
    }
    
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(currentDemo == 3) {
        gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);
    } else {
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    }
    
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case '0': case '1': case '2': case '3': case '4':
            currentDemo = key - '0';
            reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            break;
        case 'r': case 'R':
            rotationAngle += 10.0f;
            break;
        case 't': case 'T':
            translateX += 0.1f;
            translateY += 0.1f;
            break;
        case 's': case 'S':
            scaleX *= 1.1f;
            scaleY *= 1.1f;
            break;
        case 'c': case 'C':
            enableClipping = !enableClipping;
            break;
        case 'w': case 'W':
            wireframe = !wireframe;
            glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
            break;
        case 27: // ESC key
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void timer(int value) {
    rotationAngle += 1.0f;
    if(rotationAngle > 360.0f) {
        rotationAngle -= 360.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // 60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Graphics Demonstration");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    
    std::cout << "OpenGL Graphics Demonstration" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  0-4: Switch between demos" << std::endl;
    std::cout << "  R: Rotate (in transformation demo)" << std::endl;
    std::cout << "  T: Translate (in transformation demo)" << std::endl;
    std::cout << "  S: Scale (in transformation demo)" << std::endl;
    std::cout << "  C: Toggle clipping (in clipping demo)" << std::endl;
    std::cout << "  W: Toggle wireframe mode" << std::endl;
    std::cout << "  ESC: Exit" << std::endl;
    
    glutMainLoop();
    return 0;
}
