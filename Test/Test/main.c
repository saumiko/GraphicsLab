
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>

void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    float x1, x2, y1, y2;
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
    glVertex3f(x1/100, y1/100, 0.0);
    glVertex3f(x2/100, y2/100, 0.0);
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutCreateWindow("Whatever");
    glutDisplayFunc(mydisplay);
    glutMainLoop();
}