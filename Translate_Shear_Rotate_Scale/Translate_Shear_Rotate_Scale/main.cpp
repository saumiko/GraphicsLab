//
//  main.cpp
//  Translate_Shear_Rotate_Scale
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

//for all
int selector;
double xx1,yy1,xx2,yy2,xx3,yy3,xx4,yy4,xxf1,yyf1,xxf2,yyf2,xxf3,yyf3,xxf4,yyf4;

//for shear
double a,b;

//for translate
double tx,ty;

//for rotate
double angle;

//for scale
double sx,sy;


void mydisplay()
{
    
    xx1 = rint(xx1);
    xx2 = rint(xx2);
    xx3 = rint(xx3);
    xx4 = rint(xx4);
    yy1 = rint(yy1);
    yy2 = rint(yy2);
    yy3 = rint(yy3);
    yy4 = rint(yy4);
    
    
    xxf1 = rint(xxf1);
    xxf2 = rint(xxf2);
    xxf3 = rint(xxf3);
    xxf4 = rint(xxf4);
    yyf1 = rint(yyf1);
    yyf2 = rint(yyf2);
    yyf3 = rint(yyf3);
    yyf4 = rint(yyf4);
    
    
    glClear(GL_COLOR_BUFFER_BIT);
    //glPointSize(5.0f);
    glBegin(GL_LINES);
    glVertex2f(-1.0,0);
    glVertex2f(1.0,0);
    glVertex2f(0,-1.0);
    glVertex2f(0,1.0);
    glEnd();
    
    glColor3f (0.0, 1.0, 0.0); //green
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(xx1/100,yy1/100);
    glVertex2f(xx2/100,yy2/100);
    glVertex2f(xx3/100,yy3/100);
    glVertex2f(xx4/100,yy4/100);
    glEnd();
    glColor3f (0.0, 0.0, 1.0); //blue
    glBegin(GL_QUADS);
    glVertex2f(xxf1/100,yyf1/100);
    glVertex2f(xxf2/100,yyf2/100);
    glVertex2f(xxf3/100,yyf3/100);
    glVertex2f(xxf4/100,yyf4/100);
    glEnd();
    glFlush();
    
    
}

void shearing()
{
    printf("Please provide a & b\n");
    scanf("%lf %lf",&a,&b);
    xxf1=xx1+a*yy1;
    yyf1=yy1+b*xx1;
    xxf2=xx2+a*yy2;
    yyf2=yy2+b*xx2;
    xxf3=xx3+a*yy3;
    yyf3=yy3+b*xx3;
    xxf4=xx4+a*yy4;
    yyf4=yy4+b*xx4;
    
}

void translating(){
    printf("Please provide tx & ty\n");
    scanf("%lf %lf",&tx,&ty);
    xxf1=xx1+tx;
    yyf1=yy1+ty;
    xxf2=xx2+tx;
    yyf2=yy2+ty;
    xxf3=xx3+tx;
    yyf3=yy3+ty;
    xxf4=xx4+tx;
    yyf4=yy4+ty;
}

void rotating(){
    printf("Please provide the angle in degree\n");
    scanf("%lf",&angle);
    angle*=(3.14159/180.0);
    xxf1=xx1*cos(angle)-yy1*sin(angle);
    yyf1=xx1*sin(angle)+yy1*cos(angle);
    xxf2=xx2*cos(angle)-yy2*sin(angle);
    yyf2=xx2*sin(angle)+yy2*cos(angle);
    xxf3=xx3*cos(angle)-yy3*sin(angle);
    yyf3=xx3*sin(angle)+yy3*cos(angle);
    xxf4=xx4*cos(angle)-yy4*sin(angle);
    yyf4=xx4*sin(angle)+yy4*cos(angle);
}

void scaling(){
    printf("Please provide sx & sy\n");
    scanf("%lf %lf",&sx,&sy);
    xxf1=xx1*sx;
    yyf1=yy1*sy;
    xxf2=xx2*sx;
    yyf2=yy2*sy;
    xxf3=xx3*sx;
    yyf3=yy3*sy;
    xxf4=xx4*sx;
    yyf4=yy4*sy;
}



int main(int argc, char** argv)
{
    printf("Please select the operation you want to perform\n1.Translate\n2.Rotate.\n3.Scale\n4.Shear\n\n");
    scanf("%d",&selector);
    printf("\nPlease provide left lower point of the square(All input range (-100,100))\n");
    scanf("%lf %lf",&xx1,&yy1);
    xx2=xx1+50.0;
    yy2=yy1;
    xx3=xx1+50.0;
    yy3=yy1+50.0;
    xx4=xx1;
    yy4=yy1+50.0;
    if (selector==4){
        shearing();
    }
    else if (selector==1){
        translating();
    }
    else if (selector==2){
        rotating();
    }
    else if (selector==3){
        scaling();
    }
    glutInit(&argc,argv);
    //glutInitWindowSize (640, 480);
    glutCreateWindow("Translate, Rotate, Scale, Shear");
    glutDisplayFunc(mydisplay);
    glutMainLoop();
    return 0;
}

/*
 
 4
 0 0
 1 0
 
 4
 0 0
 0 1
 
 2
 30
 30
 20
 
 2
 10
 10
 45
 
 2
 10
 10
 90
 
 2
 -10
 10
 30
 
 */


