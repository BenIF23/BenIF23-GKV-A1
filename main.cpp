#include <GL/glut.h>
#include <cmath>

float carX = -1.0f; // Posisi awal mobil
float speed = 0.01f; // Kecepatan mobil
float wheelAngle = 0.0f; // Rotasi roda

void drawPolygonCircle(float x, float y, float radius) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159 / 180;
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    }
    glEnd();
}

void drawWheel(float x, float y, float radius) {
    // Outer Wheel
    glColor3f(0.0f, 0.0f, 0.0f);
    drawPolygonCircle(x, y, radius);
    
    // Inner Circle (Velg)
    glColor3f(0.5f, 0.5f, 0.5f);
    drawPolygonCircle(x, y, radius * 0.5);
    
    // Spokes (Jari-jari Velg)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    for (int i = 0; i < 360; i += 45) {
        float angle = i * 3.14159 / 180;
        glVertex2f(x, y);
        glVertex2f(x + radius * 0.5 * cos(angle), y + radius * 0.5 * sin(angle));
    }
    glEnd();
}

void drawCar() {
    glPushMatrix();
    
    // Body (Pink & Black Color Scheme)
    glColor3f(1.0f, 0.4f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.15f);
    glVertex2f(0.5f, -0.15f);
    glVertex2f(0.5f, 0.15f);
    glVertex2f(-0.5f, 0.15f);
    glEnd();
    
    // Roof (Jendela Kecil)
    glColor3f(0.7f, 0.9f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f, 0.15f);
    glVertex2f(0.2f, 0.15f);
    glVertex2f(0.2f, 0.25f);
    glVertex2f(-0.2f, 0.25f);
    glEnd();
    
    // Door Handles (2 pintu)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1f, 0.02f);
    glVertex2f(-0.05f, 0.02f);
    glVertex2f(-0.05f, 0.04f);
    glVertex2f(-0.1f, 0.04f);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2f(0.05f, 0.02f);
    glVertex2f(0.1f, 0.02f);
    glVertex2f(0.1f, 0.04f);
    glVertex2f(0.05f, 0.04f);
    glEnd();
    
    // Headlights (Depan - Kuning)
    glColor3f(1.0f, 1.0f, 0.0f);
    drawPolygonCircle(0.5f, 0.0f, 0.03f);
    
    // Rear Lights (Belakang - Merah)
    glColor3f(1.0f, 0.0f, 0.0f);
    drawPolygonCircle(-0.5f, 0.0f, 0.03f);
    
    // Wheels with Rotation Effect
    glPushMatrix();
    glTranslatef(-0.35f, -0.22f, 0.0f);
    glRotatef(wheelAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.35f, 0.22f, 0.0f);
    drawWheel(-0.35f, -0.22f, 0.12f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.35f, -0.22f, 0.0f);
    glRotatef(wheelAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.35f, 0.22f, 0.0f);
    drawWheel(0.35f, -0.22f, 0.12f);
    glPopMatrix();
    
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    glTranslatef(carX, -0.35f, 0.0f);
    drawCar();
    glPopMatrix();
    
    glutSwapBuffers();
}

void update(int value) {
    carX += speed;
    wheelAngle -= 10.0f; // Roda berputar
    if (carX > 1.0f) {
        carX = -1.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Polygon-Based Car with Transformations");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);
    glutMainLoop();
    return 0;
}
