#include <GL/glut.h>


float xmin = 200, ymin = 150, xmax = 600, ymax = 450;

bool liangBarsky(float x1, float y1, float x2, float y2,
                 float &x1_clip, float &y1_clip, float &x2_clip, float &y2_clip) {

    float dx = x2 - x1;
    float dy = y2 - y1;
    float t1 = 0, t2 = 1;

    float p[4] = {-dx, dx, -dy, dy};
    float q[4] = {x1 - xmin, xmax - x1, y1 - ymin, ymax - y1};

    for (int i = 0; i < 4; i++) {
        if (p[i] == 0) {
            if (q[i] < 0) return false;
        } else {
            float t = q[i] / p[i];
            if (p[i] < 0) {
                if (t > t1) t1 = t;
            } else {
                if (t < t2) t2 = t;
            }
        }
    }

    if (t1 > t2) return false;

    x1_clip = x1 + t1 * dx;
    y1_clip = y1 + t1 * dy;
    x2_clip = x1 + t2 * dx;
    y2_clip = y1 + t2 * dy;

    return true;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    float x1a = 100, y1a = 500, x2a = 700, y2a = 100;
    float x1c_a, y1c_a, x2c_a, y2c_a;

    glColor3f(1.0, 0.0, 0.0); 
    glBegin(GL_LINES);
    glVertex2f(x1a, y1a);
    glVertex2f(x2a, y2a);
    glEnd();

    if (liangBarsky(x1a, y1a, x2a, y2a, x1c_a, y1c_a, x2c_a, y2c_a)) {
        glColor3f(0.0, 1.0, 0.0); 
        glBegin(GL_LINES);
        glVertex2f(x1c_a, y1c_a);
        glVertex2f(x2c_a, y2c_a);
        glEnd();
    }

    // LINE 2: Fully inside - Small diagonal inside window
    float x1b = 300, y1b = 200, x2b = 500, y2b = 400;
    float x1c_b, y1c_b, x2c_b, y2c_b;

    glColor3f(1.0, 0.0, 0.0); 
    glBegin(GL_LINES);
    glVertex2f(x1b, y1b);
    glVertex2f(x2b, y2b);
    glEnd();

    if (liangBarsky(x1b, y1b, x2b, y2b, x1c_b, y1c_b, x2c_b, y2c_b)) {
        glColor3f(0.0, 1.0, 0.0); 
        glBegin(GL_LINES);
        glVertex2f(x1c_b, y1c_b);
        glVertex2f(x2c_b, y2c_b);
        glEnd();
    }

    // LINE 3: Horizontal line crossing window
    float x1c = 100, y1c = 300, x2c = 700, y2c = 300;
    float x1c_c, y1c_c, x2c_c, y2c_c;

    glColor3f(1.0, 0.0, 0.0); 
    glBegin(GL_LINES);
    glVertex2f(x1c, y1c);
    glVertex2f(x2c, y2c);
    glEnd();

    if (liangBarsky(x1c, y1c, x2c, y2c, x1c_c, y1c_c, x2c_c, y2c_c)) {
        glColor3f(0.0, 1.0, 0.0); 
        glBegin(GL_LINES);
        glVertex2f(x1c_c, y1c_c);
        glVertex2f(x2c_c, y2c_c);
        glEnd();
    }

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Liang-Barsky Line Clipping - 3 Lines");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}

