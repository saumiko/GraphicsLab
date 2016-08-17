//
//  main.cpp
//  Mirror_Reflection_About_An_Axis
//
//  Created by Asif Mohaimen on 5/15/16.
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

using namespace std;

int selector;
double xx1,yy1,xx2,yy2,xx3,yy3,xxf1,yyf1,xxf2,yyf2,xxf3,yyf3;

void mydisplay()
{
    xx1 = rint(xx1);
    xx2 = rint(xx2);
    xx3 = rint(xx3);
    yy1 = rint(yy1);
    yy2 = rint(yy2);
    yy3 = rint(yy3);
    
    
    xxf1 = rint(xxf1);
    xxf2 = rint(xxf2);
    xxf3 = rint(xxf3);
    yyf1 = rint(yyf1);
    yyf2 = rint(yyf2);
    yyf3 = rint(yyf3);
    
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2f(-1.0,0);
    glVertex2f(1.0,0);
    glVertex2f(0,-1.0);
    glVertex2f(0,1.0);
    glEnd();
    glColor3f (0.0, 0.0, 1.0); //white
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_TRIANGLES);
    glVertex2f(xx1/100,yy1/100);
    glVertex2f(xx2/100,yy2/100);
    glVertex2f(xx3/100,yy3/100);
    glEnd();
    glColor3f (0.0, 1.0, 0.0); //white
    glBegin(GL_TRIANGLES);
    glVertex2f(xxf1/100,yyf1/100);
    glVertex2f(xxf2/100,yyf2/100);
    glVertex2f(xxf3/100,yyf3/100);
    glEnd();
    glFlush();
}

void mirroringX(){
    xxf1=xx1;
    yyf1=yy1*(-1);
    xxf2=xx2;
    yyf2=yy2*(-1);
    xxf3=xx3;
    yyf3=yy3*(-1);
}

void mirroringY(){
    xxf1=xx1*(-1);
    yyf1=yy1;
    xxf2=xx2*(-1);
    yyf2=yy2;
    xxf3=xx3*(-1);
    yyf3=yy3;
}

int main(int argc, char** argv)
{
    
    printf("Please select the operation you want to perform\n1.Mirroring about X-Axis\n2.Mirroring about Y-Axis");
    scanf("%d",&selector);
    printf("Please provide the points of the triangle within range(-100,100)\n");
    scanf("%lf %lf %lf %lf %lf %lf",&xx1,&yy1,&xx2,&yy2,&xx3,&yy3);
    if (selector==1)
    {
        mirroringX();
    }
    else if (selector==2)
    {
        mirroringY();
    }
    glutInit(&argc,argv);
    glutCreateWindow("Mirroring");
    glutDisplayFunc(mydisplay);
    glutMainLoop();
    return 0;
}

/*
 
 1
 10 10 40 10 20 30
 
 1
 -40 -40 -10 -40 -20 -10
 
 1
 -40 10 -20 40 -20 10
 
 2
 10 10 40 10 20 40
 
 2
 10 -40 20 -10 40 -40
 
 1
 10 10 30 -10 0 -10
 
 */
