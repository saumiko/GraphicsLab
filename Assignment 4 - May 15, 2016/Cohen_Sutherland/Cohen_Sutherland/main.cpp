//
//  main.cpp
//  Cohen_Sutherland
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
#include <string>
#include <iostream>
using namespace std;

struct inLines
{
    double x1,y1,x2,y2;
    double cL1,cL2;
    string sCL1,sCL2;
    double m;
    int flag;
    double mx1,my1,mx2,my2;
};

double xxmin,xxmax,yymin,yymax;
int numOfLines;
struct inLines myLines[100];
int once=1;

void mydisplay()
{
    if (once == 1)
    {
        once = 0;
        glClear(GL_COLOR_BUFFER_BIT);
        //glPointSize(5.0f);
        glBegin(GL_LINES);
        glVertex2f(-1,0);
        glVertex2f(1,0);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(0,-1);
        glVertex2f(0,1);
        glEnd();
        
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glBegin(GL_QUADS);
        glColor3f (0.0, 1.0, 0.0); //green
        glVertex2f(xxmin/100,yymin/100);
        glVertex2f(xxmax/100,yymin/100);
        glVertex2f(xxmax/100,yymax/100);
        glVertex2f(xxmin/100,yymax/100);
        glEnd();
        for (int i=0; i<numOfLines; ++i)
        {
            glBegin(GL_LINES);
            glColor3f (0.0, 0.0, 1.0); //blue
            glVertex2f(myLines[i].mx1/100,myLines[i].my1/100);
            glVertex2f(myLines[i].mx2/100,myLines[i].my2/100);
            glEnd();
        }
        for (int i=0; i<numOfLines; ++i)
        {
            if (myLines[i].flag==1)
            {
                
                glBegin(GL_LINES);
                glColor3f (1.0, 0.0, 0.0); //red
                glVertex2f(myLines[i].x1/100,myLines[i].y1/100);
                glVertex2f(myLines[i].x2/100,myLines[i].y2/100);
                glEnd();
            }
        }
        glFlush();
    }
}

int main(int argc, char** argv)
{
    printf("All co ordinate range must be between (-100,100)\n");
    printf("Please provide lower left corner of the window: ");
    scanf("%lf %lf",&xxmin,&yymin);
    printf("Please provide upper right corner of the window: ");
    scanf("%lf %lf",&xxmax,&yymax);
    xxmin=rint(xxmin);
    xxmax=rint(xxmax);
    yymin=rint(yymin);
    yymax=rint(yymax);
    printf("Please enter number of lines: ");
    scanf("%d",&numOfLines);
    for (int i=0; i<numOfLines; ++i)
    {
        myLines[i].sCL1="0000";
        myLines[i].sCL2="0000";
        myLines[i].flag=-1;
    }
    printf("Please provide the end points of the lines like this x1 y1 x2 y2\n");
    for (int i=0; i<numOfLines; ++i)
    {
        scanf("%lf %lf %lf %lf",&myLines[i].x1,&myLines[i].y1,&myLines[i].x2,&myLines[i].y2);
        myLines[i].x1=rint(myLines[i].x1);
        myLines[i].y1=rint(myLines[i].y1);
        myLines[i].x2=rint(myLines[i].x2);
        myLines[i].y2=rint(myLines[i].y2);
        myLines[i].mx1=myLines[i].x1;
        myLines[i].mx2=myLines[i].x2;
        myLines[i].my1=myLines[i].y1;
        myLines[i].my2=myLines[i].y2;
        myLines[i].m = (myLines[i].y2-myLines[i].y1) / (myLines[i].x2-myLines[i].x1);
    }
    
    int tracker=0;
    int testerTracker=0;
    while(tracker<numOfLines)
    {
        
        
        for (int i=0; i<numOfLines; ++i)
        {
            if (myLines[i].flag==-1)
            {
                myLines[i].sCL1="0000";
                myLines[i].sCL2="0000";
            }
        }
        
        
        
        //for point1
        if(myLines[tracker].y1-yymax>0)
        {
            myLines[tracker].sCL1[0]='1';
        }
        if(yymin-myLines[tracker].y1>0)
        {
            myLines[tracker].sCL1[1]='1';
        }
        if(myLines[tracker].x1-xxmax>0)
        {
            myLines[tracker].sCL1[2]='1';
        }
        if(xxmin-myLines[tracker].x1>0)
        {
            myLines[tracker].sCL1[3]='1';
        }
        
        //for point2
        if(myLines[tracker].y2-yymax>0)
        {
            myLines[tracker].sCL2[0]='1';
        }
        if(yymin-myLines[tracker].y2>0)
        {
            myLines[tracker].sCL2[1]='1';
        }
        if(myLines[tracker].x2-xxmax>0)
        {
            myLines[tracker].sCL2[2]='1';
        }
        if(xxmin-myLines[tracker].x2>0)
        {
            myLines[tracker].sCL2[3]='1';
        }
        
        //now convert it into decimal for and operation
        if (myLines[tracker].sCL1 == "1001")
            myLines[tracker].cL1=9;
        else if (myLines[tracker].sCL1 == "1000")
            myLines[tracker].cL1=8;
        else if (myLines[tracker].sCL1 == "1010")
            myLines[tracker].cL1=10;
        else if (myLines[tracker].sCL1 == "0001")
            myLines[tracker].cL1=1;
        else if (myLines[tracker].sCL1 == "0000")
            myLines[tracker].cL1=0;
        else if (myLines[tracker].sCL1 == "0010")
            myLines[tracker].cL1=2;
        else if (myLines[tracker].sCL1 == "0100")
            myLines[tracker].cL1=4;
        else if (myLines[tracker].sCL1 == "0101")
            myLines[tracker].cL1=5;
        else if (myLines[tracker].sCL1 == "0110")
            myLines[tracker].cL1=6;
        
        
        if (myLines[tracker].sCL2 == "1001")
            myLines[tracker].cL2=9;
        else if (myLines[tracker].sCL2 == "1000")
            myLines[tracker].cL2=8;
        else if (myLines[tracker].sCL2 == "1010")
            myLines[tracker].cL2=10;
        else if (myLines[tracker].sCL2 == "0001")
            myLines[tracker].cL2=1;
        else if (myLines[tracker].sCL2 == "0000")
            myLines[tracker].cL2=0;
        else if (myLines[tracker].sCL2 == "0010")
            myLines[tracker].cL2=2;
        else if (myLines[tracker].sCL2 == "0100")
            myLines[tracker].cL2=4;
        else if (myLines[tracker].sCL2 == "0101")
            myLines[tracker].cL2=5;
        else if (myLines[tracker].sCL2 == "0110")
            myLines[tracker].cL2=6;
        
        int tester = (int)myLines[tracker].cL1 & (int)myLines[tracker].cL2;
        
        
        if (myLines[tracker].cL1==0 && myLines[tracker].cL2 == 0)
        {
            myLines[tracker].flag=1;
            ++tracker;
            testerTracker=0;
        }
        else if (tester == 0 && testerTracker<2)
        {
            ++testerTracker;
            printf("hello");
            double insX,insY;
            if (myLines[tracker].sCL1[0]=='1' || myLines[tracker].sCL1[1]=='1')
            {
                printf("cond1");
                if (myLines[tracker].sCL1[0]=='1')
                    insY = yymax;
                else if (myLines[tracker].sCL1[1]=='1')
                    insY = yymin;
                double xi = myLines[tracker].x1+((insY-myLines[tracker].y1)/myLines[tracker].m);
                myLines[tracker].x1=rint(xi);
                myLines[tracker].y1=rint(insY);
            }
            else if (myLines[tracker].sCL1[2]=='1' || myLines[tracker].sCL1[3]=='1')
            {
                printf("cond2");
                if (myLines[tracker].sCL1[2]=='1')
                    insX = xxmax;
                else if (myLines[tracker].sCL1[3]=='1')
                    insX = xxmin;
                double yi = myLines[tracker].y1 + myLines[tracker].m * (insX - myLines[tracker].x1);
                myLines[tracker].x1 = rint(insX);
                myLines[tracker].y1 = rint(yi);
            }
            
            
            double insX2,insY2;
            if (myLines[tracker].sCL2[0]=='1' || myLines[tracker].sCL2[1]=='1')
            {
                printf("cond3");
                if (myLines[tracker].sCL2[0]=='1')
                    insY2 = yymax;
                else if (myLines[tracker].sCL2[1]=='1')
                    insY2 = yymin;
                double xi = myLines[tracker].x2+((insY2-myLines[tracker].y2)/myLines[tracker].m);
                myLines[tracker].x2=rint(xi);
                myLines[tracker].y2=rint(insY2);
            }
            else if (myLines[tracker].sCL2[2]=='1' || myLines[tracker].sCL2[3]=='1')
            {
                printf("cond4");
                if (myLines[tracker].sCL2[2]=='1')
                    insX2 = xxmax;
                else if (myLines[tracker].sCL2[3]=='1')
                    insX2 = xxmin;
                double yi = myLines[tracker].y2 + myLines[tracker].m * (insX2 - myLines[tracker].x2);
                myLines[tracker].x2 = rint(insX2);
                myLines[tracker].y2 = rint(yi);
            }
        }
        else
        {
            myLines[tracker].flag=0;
            ++tracker;
            testerTracker = 0;
        }
    }
    
    glutInit(&argc,argv);
    glutInitWindowSize (640, 480);
    glutCreateWindow("Cohen_Sutherland");
    glutDisplayFunc(mydisplay);
    glutMainLoop();
    return 0;
}

/*
 0 0 40 40
 12
 -10 50 20 -20
 -10 50 60 -10
 -10 20 20 60
 20 60 30 60
 0 0 40 0
 1 2 20 20
 30 50 50 30
 30 60 60 20
 20 -10 50 20
 30 -40 70 10
 20 -20 -40 10
 -50 30 10 60
 */
