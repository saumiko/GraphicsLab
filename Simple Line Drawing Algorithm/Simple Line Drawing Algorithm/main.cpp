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
        for(i = yf; i <= yf2; ++i)
        {
            glVertex2f(xf/100, i/100);
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
            printf("inside");
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
        else
        {
            
            //calculating b of y = mx + b
            double b;
            b = yf - m*xf;
            
            //if slope is small
            if (fabs(m) < 1)
            {
                double i,yi;
                glBegin(GL_POINTS);
                for (i = xf; i <= xf2; ++i)
                {
                    yi = m*i + b;
                    yi = rint(yi);
                    glVertex2f(i/100, yi/100);
                }
                glEnd();
                glFlush();
            }
            
            // if slop is large
            else
            {
                double i,xi;
                glBegin(GL_POINTS);
                
                //if yf < yf2
                if (yf < yf2)
                {
                    for (i = yf; i <= yf2; ++i)
                    {
                        xi = (i-b) / m;
                        xi = rint(xi);
                        glVertex2f(xi/100, i/100);
                    }
                    glEnd();
                    glFlush();
                }
                else
                {
                    for (i = yf2; i <= yf; ++i)
                    {
                        xi = (i-b) / m;
                        xi = rint(xi);
                        glVertex2f(xi/100, i/100);
                    }
                    glEnd();
                    glFlush();
                }
                
            }
        }
    }
    
}


int main(int argc, char** argv)
{
    scanf("%lf %lf %lf %lf",&x,&y,&x2,&y2);
    glutInit(&argc,argv);
    glutCreateWindow("Simple Line Drawing Algorithm");
    glutDisplayFunc(mydisplay);
    glutMainLoop();
    
}
