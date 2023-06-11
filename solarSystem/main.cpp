#include <GL/glut.h>
#include <cmath>
#include <soil.h>
#include <Gl/GL.h>

float moonPosX = 0.0f; // moon x coordinates
float moonPosY = 0.0f; // moon Y coordinates
float orbitRX = 0.55f; // orbit radius 
float orbitRY = orbitRX/2; // orbit radius 
int part = 0; // which half is the moon in (temporary)
float scalingFactor = 1.0;

void drawArc(int koef, float z)
{
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();

    glScalef(1.0f, 0.5f, 1.0f);
    glBegin(GL_LINE_STRIP);

    for (float angle = 0.0f; angle <= 3.1415926; angle += 0.01f)
    {
        float moonPosX = koef * orbitRX * cos(angle);
        float y = koef * orbitRX * sin(angle);
        glVertex3f(moonPosX, y, z);
    }

    glEnd();
    glFlush();
    glPopMatrix();
}

void display_game() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // the moon
    glColor3f(0.5, 0.5, 0.5);
    glPushMatrix();

    if (part == 0) glTranslatef(moonPosX, moonPosY, 0.9f); // the moon is behind the earth
    else glTranslatef(moonPosX, moonPosY, -0.9f); // the moon in front of the earth
    glScalef(scalingFactor, scalingFactor, 0.0f); // to scale
    glutSolidSphere(0.08, 30, 30);
    glPopMatrix();

    drawArc(-1, -0.2f); // lower trajectory

    // the earth
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glutSolidSphere(0.3, 30, 30);
    glPopMatrix();

    drawArc(1, 0.9f); // upper trajectory

    glutSwapBuffers();
}

void update(int value) {
    if (part == 0)
    {
        moonPosX += 0.01f;
        moonPosY = (orbitRY / orbitRX) * sqrtf(pow(orbitRX, 2) - pow(moonPosX, 2));
        if (moonPosX >= orbitRX) part = 1;
    }
    if (part == 1)
    {
        moonPosX -= 0.01f;
        moonPosY = -1 * (orbitRY / orbitRX) * sqrtf(pow(orbitRX, 2) - pow(moonPosX, 2));
        if (moonPosX <= -orbitRX +0.01f) part = 0;
    }
    if (moonPosX > 0) scalingFactor += 0.008f;
    else scalingFactor -= 0.008f;
    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Solar System");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(display_game);

    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}