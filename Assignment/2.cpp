#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void plotCirclePoints(int xc, int yc, int x, int y, vector<pair<int, int>>& points) {
    // 8-way symmetry points
    points.push_back(make_pair(xc + x, yc + y));
    points.push_back(make_pair(xc - x, yc + y));
    points.push_back(make_pair(xc + x, yc - y));
    points.push_back(make_pair(xc - x, yc - y));
    points.push_back(make_pair(xc + y, yc + x));
    points.push_back(make_pair(xc - y, yc + x));
    points.push_back(make_pair(xc + y, yc - x));
    points.push_back(make_pair(xc - y, yc - x));
}


vector<pair<int, int>> midPointCircle(int xc, int yc, int radius, int thickness) {
    vector<pair<int, int>> allPoints;

    for (int r = radius; r < radius + thickness; r++) {
        vector<pair<int, int>> circlePoints;
        int x = 0;
        int y = r;
        int d = 1 - r; 

        plotCirclePoints(xc, yc, x, y, circlePoints);

        while (x <= y) {
            x++;
            if (d < 0) {
                d = d + 2 * x + 1;
            } else {
                y--;
                d = d + 2 * (x - y) + 1;
            }
            plotCirclePoints(xc, yc, x, y, circlePoints);
        }

        allPoints.insert(allPoints.end(), circlePoints.begin(), circlePoints.end());
    }

    return allPoints;
}

void rainbowColor(float ratio, float& r, float& g, float& b) {
    float h = ratio * 6.0f; // 0-6 for full rainbow
    float s = 1.0f, v = 1.0f;

    int i = int(h);
    float f = h - i;
    float p = v * (1 - s);
    float q = v * (1 - s * f);
    float t = v * (1 - s * (1 - f));

    switch (i % 6) {
        case 0: r = v; g = t; b = p; break; // Red
        case 1: r = q; g = v; b = p; break; // Yellow
        case 2: r = p; g = v; b = t; break; // Green
        case 3: r = p; g = q; b = v; break; // Cyan
        case 4: r = t; g = p; b = v; break; // Blue
        case 5: r = v; g = p; b = q; break; // Magenta
    }
}

void drawConcentricCircles(int centerX, int centerY, int numCircles,
                          int startRadius, int radiusStep,
                          int startThickness, int thicknessStep) {

    for (int i = 0; i < numCircles; i++) {
        int currentRadius = startRadius + i * radiusStep;
        int currentThickness = startThickness + i * thicknessStep;

        float ratio = float(i) / float(numCircles - 1);

        float r, g, b;
        rainbowColor(ratio, r, g, b);

        glColor3f(r, g, b);

        auto circlePoints = midPointCircle(centerX, centerY, currentRadius, currentThickness);

        glBegin(GL_POINTS);
        for (auto point : circlePoints) {
            glVertex2i(point.first, point.second);
        }
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    gluOrtho2D(0, 800, 0, 600);

    drawConcentricCircles(400, 300, 12, 20, 25, 1, 1);

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
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
    glutCreateWindow("Concentric Circles with Gradient and Thickness");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    init();
    glutMainLoop();

    return 0;
}

