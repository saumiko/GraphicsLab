//
//  main.cpp
//  Bresenham Line Drawing Algorithm
//
//  Created by Asif Mohaimen on 4/08/16.
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

double x,y,x2,y2;

void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0f);
    double xf,yf,xf2,yf2;
    
    //rounding
    xf = rint(x);
    xf2 = rint(x2);
    yf = rint(y);
    yf2 = rint(y2);
    
    //swapping if necessary
    if (xf2 < xf)
    {
        double temp = xf2;
        xf2 = xf;
        xf = temp;
        temp = yf2;
        yf2 = yf;
        yf = temp;
    }
    
    
    //if horizontal line
    if (yf2 - yf == 0)
    {
        double i;
        glBegin(GL_POINTS);
        for(i = xf; i <= xf2; ++i)
        {
            glVertex2f(i/100, yf/100);
        }
        glEnd();
        glFlush();
    }
    
    //if vertical line
    else if (xf2 - xf == 0)
    {
        double i;
        glBegin(GL_POINTS);
        if (yf<yf2){
            for(i = yf; i <= yf2; ++i)
            {
                glVertex2f(xf/100, i/100);
            }
        }
        else{
            for(i = yf2; i <= yf; ++i)
            {
                glVertex2f(xf/100, i/100);
            }
        }
        glEnd();
        glFlush();
    }
    
    //if others
    else
    {
        //calculating m of y = mx + b
        double m;
        m = (yf2-yf)/(xf2-xf);
        
        //if diagonal line
        if (fabs(m) == 1.0)
        {
            double i,j;
            glBegin(GL_POINTS);
            
            //if yf < yf2
            if (yf < yf2)
            {
                for(i = xf,j = yf; i <= xf2; ++i,++j)
                {
                    glVertex2f(i/100, j/100);
                }
                glEnd();
                glFlush();
            }
            else
            {
                for(i = xf,j = yf; i <= xf2; ++i,--j)
                {
                    glVertex2f(i/100, j/100);
                }
                glEnd();
                glFlush();
            }
            
        }
        
        //if others
        else if (m>0 && m<1)
        {
            if (xf2 < xf)
            {
                double temp = xf2;
                xf2 = xf;
                xf = temp;
                temp = yf2;
                yf2 = yf;
                yf = temp;
            }
            double i,j;
            i = xf;
            j = yf;
            double dx = xf2 - xf;
            double dy = yf2 - yf;
            double dT = 2 * (dy - dx);
            double dS = 2 * dy;
            double d = 2*dy - dx;
            glBegin(GL_POINTS);
            glVertex2f(i/100, j/100);
            for (;i<=xf2;){
                ++i;
                if (d<0){
                    d = d + dS;
                }
                else{
                    j++;
                    d = d + dT;
                }
                glVertex2f(i/100, j/100);
            }
            glEnd();
            glFlush();
        }
        else if (m<0 && m>-1)
        {
            if (xf < xf2)
            {
                double temp = xf2;
                xf2 = xf;
                xf = temp;
                temp = yf2;
                yf2 = yf;
                yf = temp;
            }
            xf *= (-1.0);
            xf2 *= (-1.0);
            double i,j;
            i = xf;
            j = yf;
            double dx = xf2 - xf;
            double dy = yf2 - yf;
            double dT = 2 * (dy - dx);
            double dS = 2 * dy;
            double d = 2*dy - dx;
            glBegin(GL_POINTS);
            glVertex2f(i/-100, j/100);
            for (;i<=xf2;){
                ++i;
                if (d<0){
                    d = d + dS;
                }
                else{
                    j++;
                    d = d + dT;
                }
                glVertex2f(-i/100, j/100);
            }
            glEnd();
            glFlush();
        }
        else if (m>1)
        {
            if (yf2 < yf)
            {
                double temp = xf2;
                xf2 = xf;
                xf = temp;
                temp = yf2;
                yf2 = yf;
                yf = temp;
            }
            double i,j;
            double tempx,tempy;
            tempx = xf;
            tempy = yf;
            xf = yf;
            yf = tempx;
            tempx = xf2;
            tempy = yf2;
            xf2 = yf2;
            yf2 = tempx;
            i = xf;
            j = yf;
            double dx = xf2 - xf;
            double dy = yf2 - yf;
            double dT = 2 * (dy - dx);
            double dS = 2 * dy;
            double d = 2*dy - dx;
            glBegin(GL_POINTS);
            glVertex2f(j/100, i/100);
            for (;i<=xf2;){
                ++i;
                if (d<0){
                    d = d + dS;
                }
                else{
                    j++;
                    d = d + dT;
                }
                glVertex2f(j/100, i/100);
            }
            glEnd();
            glFlush();
            
        }
        else if (m<-1){
            if (xf2 > xf)
            {
                double temp = xf2;
                xf2 = xf;
                xf = temp;
                temp = yf2;
                yf2 = yf;
                yf = temp;
            }
            xf *= (-1.0);
            xf2 *= (-1.0);
            double i,j;
            double tempx,tempy;
            tempx = xf;
            tempy = yf;
            xf = yf;
            yf = tempx;
            tempx = xf2;
            tempy = yf2;
            xf2 = yf2;
            yf2 = tempx;
            i = xf;
            j = yf;
            double dx = xf2 - xf;
            double dy = yf2 - yf;
            double dT = 2 * (dy - dx);
            double dS = 2 * dy;
            double d = 2*dy - dx;
            glBegin(GL_POINTS);
            for (;i<=xf2;){
                ++i;
                if (d<0){
                    d = d + dS;
                }
                else{
                    j++;
                    d = d + dT;
                }
                glVertex2f(-j/100, i/100);
            }
            glEnd();
            glFlush();
        }
    }
}
int main(int argc, char** argv)
{
    
    
    scanf("%lf %lf %lf %lf",&x,&y,&x2,&y2);
    glutInit(&argc,argv);
    glutCreateWindow("Bresenham Line Drawing Algorithm");
    glutDisplayFunc(mydisplay);
    glutMainLoop();
    
}