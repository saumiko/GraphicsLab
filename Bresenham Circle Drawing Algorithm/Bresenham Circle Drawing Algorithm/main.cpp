//
//  main.cpp
//  Bresenham Circle Drawing Algorithm
//
//  Created by Asif Mohaimen on 4/10/16.
//  Copyright © 2016 Asif Mohaimen. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double cx,cy,r;

void mydisplay()
{
    cx = rint(cx);
    cy = rint(cy);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    double i,j,d;
    j = r;
    d = 3 - 2*r;
    for (i=0;i<=j;++i){
        glVertex2f((i/100)+cx/100, (j/100)+cy/100);
        glVertex2f((i/100)+cx/100, -(j/100)+cy/100);
        glVertex2f((j/100)+cx/100, -(i/100)+cy/100);
        glVertex2f((j/100)+cx/100, (i/100)+cy/100);
        glVertex2f(-(j/100)+cx/100, -(i/100)+cy/100);
        glVertex2f(-(i/100)+cx/100, -(j/100)+cy/100);
        glVertex2f(-(i/100)+cx/100, (j/100)+cy/100);
        glVertex2f(-(j/100)+cx/100, (i/100)+cy/100);
        if (d<0)
            d = d + 4*i + 6;
        else{
            d = d + 4*(i-j) + 10;
            --j;
        }
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    
    scanf("%lf %lf %lf",&cx,&cy,&r);
    glutInit(&argc,argv);
    glutCreateWindow("Bresenham Circle Drawing Algorithm");
    glutDisplayFunc(mydisplay);
    glutMainLoop();
    
}