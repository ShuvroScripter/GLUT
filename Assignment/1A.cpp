#include <GL/glut.h>
#include <vector>
#include <utility>
#include <cmath>
#include <iostream>

using namespace std;

// Bresenham Line Drawing Algorithm
vector<pair<int, int>> drawBresenhamLine(int x1, int y1, int x2, int y2) {
    vector<pair<int, int>> points;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;
    int x = x1;
    int y = y1;

    while (true) {
        points.push_back(make_pair(x, y));

        if (x == x2 && y == y2) break;

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }

        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }

    return points;
}


void drawLineGL(int x1, int y1, int x2, int y2) {
    glBegin(GL_POINTS);

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;
    int x = x1;
    int y = y1;

    while (true) {
        glVertex2i(x, y);

        if (x == x2 && y == y2) break;

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }

        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }

    glEnd();
}


void drawTestLines() {
    glColor3f(1.0, 0.0, 0.0); // Red - Positive slope
    drawLineGL(50, 50, 200, 150);

    glColor3f(0.0, 1.0, 0.0); // Green - Negative slope
    drawLineGL(250, 150, 400, 50);

    glColor3f(0.0, 0.0, 1.0); // Blue - Horizontal
    drawLineGL(50, 250, 400, 250);

    glColor3f(1.0, 1.0, 0.0); // Yellow - Vertical
    drawLineGL(225, 50, 225, 300);

    glColor3f(1.0, 0.0, 1.0); // Magenta - Steep positive
    drawLineGL(450, 50, 500, 250);

    glColor3f(0.0, 1.0, 1.0); // Cyan - Steep negative
    drawLineGL(550, 250, 600, 50);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    
    gluOrtho2D(0, 800, 0, 600);

    
    drawTestLines();

    glFlush();
}


void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}


void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC key
            exit(0);
            break;
        case 'r':
        case 'R':
            glutPostRedisplay();
            break;
    }
}


int main(int argc, char** argv) {
  
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham's Line Drawing Algorithm");

  
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

 
    init();


    cout << "Testing Bresenham's Algorithm with different line orientations:\n";

    // Test 1: Positive slope
    auto line1 = drawBresenhamLine(0, 0, 5, 3);
    cout << "Positive slope (0,0 to 5,3): ";
    for (auto p : line1) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;

    // Test 2: Negative slope
    auto line2 = drawBresenhamLine(0, 3, 5, 0);
    cout << "Negative slope (0,3 to 5,0): ";
    for (auto p : line2) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;

    // Test 3: Horizontal line
    auto line3 = drawBresenhamLine(0, 2, 5, 2);
    cout << "Horizontal line (0,2 to 5,2): ";
    for (auto p : line3) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;

    // Test 4: Vertical line
    auto line4 = drawBresenhamLine(2, 0, 2, 5);
    cout << "Vertical line (2,0 to 2,5): ";
    for (auto p : line4) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;

 
    glutMainLoop();

    return 0;
}

