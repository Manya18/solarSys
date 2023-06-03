#include <GL/glut.h>
#include <cmath>

float x = 0.0f; // координата луны
float y = 0.0f; // координата луны
float a = 0.55f; // радиус орбиты
float b = 0.3f; // высота орбиты
int part = 0; // в какой половине находитс€ луна
float scaledCo = 1.0;

void drawArc(int koef, float z)
{
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();

    glScalef(1.0f, 0.5f, 1.0f);
    glBegin(GL_LINE_STRIP);

    for (float angle = 0.0f; angle <= 3.1415926; angle += 0.01f)
    {
        float x = koef * a * cos(angle);
        float y = koef * a * sin(angle);
        glVertex3f(x, y, z);
    }

    glEnd();
    glFlush();
    glPopMatrix();
}

void display_game() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // рисуем луну
    glColor3f(0.5, 0.5, 0.5);
    glPushMatrix();
    if (part == 0) glTranslatef(x, y, 0.9f); // луна за землей
    else glTranslatef(x, y, -0.9f); // луна перед землей
    glScalef(scaledCo, scaledCo, 0.0f); //чтобы отдал€лась
    glutSolidSphere(0.08, 30, 30);
    glPopMatrix();

    drawArc(-1, -0.2f); // нижн€€ траектори€

    // рисуем землю
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glutSolidSphere(0.3, 30, 30);
    glPopMatrix();

    drawArc(1, 0.9f); // верхн€€ траектори€

    glutSwapBuffers();
}

void update(int value) {
    if (part == 0)
    {
        x += 0.01f;
        y = (b / a) * sqrtf(pow(a, 2) - pow(x, 2));
        if (x >= a) part = 1;
    }
    if (part == 1)
    {
        x -= 0.01f;
        y = -1 * (b / a) * sqrtf(pow(a, 2) - pow(x, 2));
        if (x <= -a+0.01f) part = 0;
    }
    if (x > 0) scaledCo += 0.008f;
    else scaledCo -= 0.008f;
    glutPostRedisplay(); // вызываем функцию отображени€
    glutTimerFunc(30, update, 0); // регистрируем функцию обновлени€ через 16 миллисекунд
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sphere Example");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(display_game);

    glutTimerFunc(0, update, 0);
    glutMainLoop();

    return 0;
}