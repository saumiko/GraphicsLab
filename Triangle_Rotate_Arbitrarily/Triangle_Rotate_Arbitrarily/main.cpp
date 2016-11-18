//
//  main.cpp
//  Triangle_Rotate_Arbitrarily
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

double pmatrix[3][3];
double rmatrix[3][3];
double tmatrix[3][3];
double timatrix[3][3];
double tempmatrix[3][3];
double tempmatrix2[3][3];
double finalmatrix[3][3];
double c[3][3];
int selector;

double rotateAboutX,rotateAboutY;


void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0f);
    glBegin(GL_LINES);
    glVertex2f(-1,0);
    glVertex2f(1,0);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0,-1);
    glVertex2f(0,1);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(pmatrix[0][0]/100,pmatrix[1][0]/100);
    glVertex2f(pmatrix[0][1]/100,pmatrix[1][1]/100);
    glVertex2f(pmatrix[0][2]/100,pmatrix[1][2]/100);
    glEnd();
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(finalmatrix[0][0]/100,finalmatrix[1][0]/100);
    glVertex2f(finalmatrix[0][1]/100,finalmatrix[1][1]/100);
    glVertex2f(finalmatrix[0][2]/100,finalmatrix[1][2]/100);
    glEnd();
    glFlush();
    
}

void rotateTriangleAboutAPoint()
{
    
    printf("Please provide three points of the triangle\n");
    scanf("%lf %lf %lf %lf %lf %lf",&pmatrix[0][0],&pmatrix[1][0],&pmatrix[0][1],&pmatrix[1][1],&pmatrix[0][2],&pmatrix[1][2]);
    pmatrix[2][0]=1;
    pmatrix[2][1]=1;
    pmatrix[2][2]=1;
    
    printf("Please provide the rotation in degrees\n");
    double d;
    scanf("%lf",&d);
    d*=(3.14159/180.0);
    rmatrix[0][0]=cos(d);
    rmatrix[1][0]=sin(d);
    rmatrix[2][0]=0.0;
    rmatrix[0][1]=(-1)*sin(d);
    rmatrix[1][1]=cos(d);
    rmatrix[2][1]=0.0;
    rmatrix[0][2]=0.0;
    rmatrix[1][2]=0.0;
    rmatrix[2][2]=1.0;
    
    printf("Provide the point about which you want to rotate the triangle(tx & ty)\n");
    scanf("%lf %lf",&rotateAboutX,&rotateAboutY);
    rotateAboutX = rint(rotateAboutX);
    rotateAboutY = rint(rotateAboutY);
    
    tmatrix[0][0]=1.0;
    tmatrix[0][1]=0;
    tmatrix[0][2]=rotateAboutX;
    tmatrix[1][0]=0;
    tmatrix[1][1]=1.0;
    tmatrix[1][2]=rotateAboutY;
    tmatrix[2][0]=0;
    tmatrix[2][1]=0;
    tmatrix[2][2]=1.0;
    
    timatrix[0][0]=1.0;
    timatrix[0][1]=0;
    timatrix[0][2]=rotateAboutX*(-1.0);
    timatrix[1][0]=0;
    timatrix[1][1]=1.0;
    timatrix[1][2]=rotateAboutY*(-1.0);
    timatrix[2][0]=0;
    timatrix[2][1]=0;
    timatrix[2][2]=1.0;
    
    int i=0,j=0,k=0;
    double sum=0;
    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            c[i][j]=0;
    
    
    for(i=0; i<3; i++) //row of first matrix
    {
        for(j=0; j<3; j++) //column of second matrix
        {
            sum=0;
            for(k=0; k<3; k++)
                sum=sum+rmatrix[i][k]*timatrix[k][j];
            c[i][j]=sum;
        }
    }
    
    i=0;
    j=0;
    k=0;
    sum=0;
    
    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            tempmatrix[i][j]=0;
    
    
    for(i=0; i<3; i++) //row of first matrix
    {
        for(j=0; j<3; j++) //column of second matrix
        {
            sum=0;
            for(k=0; k<3; k++)
                sum=sum+tmatrix[i][k]*c[k][j];
            tempmatrix[i][j]=sum;
        }
    }
    
    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            finalmatrix[i][j]=0;
    
    for(i=0; i<3; i++) //row of first matrix
    {
        for(j=0; j<3; j++) //column of second matrix
        {
            sum=0;
            for(k=0; k<3; k++)
                sum=sum+tempmatrix[i][k]*pmatrix[k][j];
            finalmatrix[i][j]=sum;
        }
    }
    
    for(i=0; i<3; i++) //row of first matrix
    {
        for(j=0; j<3; j++) //column of second matrix
        {
            finalmatrix[i][j]=rint(finalmatrix[i][j]);
        }
    }
    
}



int main(int argc, char** argv)
{
    printf("ALL THE POINTS MUST BE IN RANGE (-100,100)\n");
    rotateTriangleAboutAPoint();
    glutInit(&argc,argv);
    glutCreateWindow("Rotating a triangle about an arbitrary point");
    glutDisplayFunc(mydisplay);
    glutMainLoop();
    return 0;
}

/*
 
 0 0 60 0 60 50
 -90
 0 0
 
 
 0 0 10 10 50 20
 45
 -10 -10
 
 0 34 10 10 50 20
 30
 -10 -10
 
 5 0 60 10 50 20
 57
 -10 -10
 
 */


