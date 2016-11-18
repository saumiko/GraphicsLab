//
//  main.cpp
//  ScanLinePolygonFilling
//
//  Created by Asif Mohaimen on 4/23/16.
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
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

double scanline[500][500];

double finalmin=1000.0,finalmax=-1000.0;

struct finalscanlinestruct{
    double x[500];
    int cnt;
};

struct edgeliststructure{
    double x1,y1,x2,y2;
    double onebym;
    double ymin;
    double x;
    double ymax;
};

struct pointstructure{
    double x,y;
};

struct edgeliststructure edgelist[200];
struct pointstructure points[200];
struct finalscanlinestruct finalscanline[300];
int numofvertices;
int difofyminymax=0;

void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    //drawing the polygon
    glBegin(GL_LINES);
    for (int i=0;i<numofvertices;++i){
        glVertex2f(edgelist[i].x1/100, edgelist[i].y1/100);
        glVertex2f(edgelist[i].x2/100, edgelist[i].y2/100);
    }
    glEnd();
    //    glFlush();
    
    double k2 = finalmin;
    glBegin(GL_LINES);
    for (int i=0;i<difofyminymax;++i){
        for (int j=0;j<finalscanline[i].cnt;j+=2){
            glVertex2f(finalscanline[i].x[j]/100, k2/100);
            glVertex2f(finalscanline[i].x[j+1]/100, k2/100);
        }
        ++k2;
    }
    glEnd();
    
    glFlush();
}

int main(int argc, char** argv)
{
    for (int i=0;i<500;++i)
        for (int j=0;j<500;++j)
            scanline[i][j] = -10000.0;
    
    for (int i=0;i<300;++i){
        for (int j=0;j<500;++j){
            finalscanline[i].x[j]=1000;
        }
        finalscanline[i].cnt = 0;
    }
    
    printf("Enter number of vertices: ");
    scanf("%d",&numofvertices);
    printf("Provide the Points: ");
    for(int i=0;i<numofvertices;++i){
        scanf("%lf %lf",&points[i].x,&points[i].y);
        //rounding to int
        points[i].x = rint(points[i].x);
        points[i].y = rint(points[i].y);
        if (points[i].y < finalmin)
            finalmin = points[i].y;
    }
    
    
    //finding finalmax
    for(int i=0;i<numofvertices;++i){
        if (points[i].y > finalmax)
            finalmax = points[i].y;
    }
    
    //converting points to edges
    for(int i=1;i<numofvertices;++i){
        edgelist[i-1].x1 = points[i-1].x;
        edgelist[i-1].y1 = points[i-1].y;
        edgelist[i-1].x2 = points[i].x;
        edgelist[i-1].y2 = points[i].y;
        edgelist[i-1].onebym = (edgelist[i-1].y2 - edgelist[i-1].y1)/(edgelist[i-1].x2 - edgelist[i-1].x1);
        edgelist[i-1].onebym = 1/(edgelist[i-1].onebym);
    }
    //connecting last point with first point to make a polygon
    edgelist[numofvertices-1].x1 = points[numofvertices-1].x;
    edgelist[numofvertices-1].y1 = points[numofvertices-1].y;
    edgelist[numofvertices-1].x2 = points[0].x;
    edgelist[numofvertices-1].y2 = points[0].y;
    edgelist[numofvertices-1].onebym = (edgelist[numofvertices-1].y2 - edgelist[numofvertices-1].y1)/(edgelist[numofvertices-1].x2 - edgelist[numofvertices-1].x1);
    edgelist[numofvertices-1].onebym = 1/(edgelist[numofvertices-1].onebym);
    
    
    
    //check the condition yp<yc<yn and yp>yc>yn
    for (int i=1;i<numofvertices;++i){
        if ((edgelist[i-1].y1<edgelist[i-1].y2) && (edgelist[i].y1<edgelist[i].y2)){
            edgelist[i-1].x2 = rint(edgelist[i-1].x1 + (edgelist[i-1].onebym * (edgelist[i-1].y2 - 1 - edgelist[i-1].y1)));
            edgelist[i-1].y2 -= 1;
        }
        else if ((edgelist[i-1].y1>edgelist[i-1].y2) && (edgelist[i].y1>edgelist[i].y2)){
            edgelist[i].x1 = rint(edgelist[i].x2 + (edgelist[i].onebym * (edgelist[i-1].y2 - 1 - edgelist[i].y2)));
            edgelist[i].y1 -= 1;
        }
    }
    
    
    if ((edgelist[numofvertices-1].y1<edgelist[numofvertices-1].y2) && (edgelist[numofvertices-1].y2<edgelist[0].y2)){
        edgelist[numofvertices-1].x2 = rint(edgelist[numofvertices-1].x1 + (edgelist[numofvertices-1].onebym * (edgelist[numofvertices-1].y2 - 1 - edgelist[numofvertices-1].y1)));
        edgelist[numofvertices-1].y2 -= 1;
    }
    else if ((edgelist[numofvertices-1].y1>edgelist[numofvertices-1].y2) && (edgelist[numofvertices-1].y2>edgelist[0].y2)){
        edgelist[0].x1 = rint(edgelist[0].x2 + (edgelist[0].onebym * (edgelist[numofvertices-1].y2 - 1 - edgelist[0].y2)));
        edgelist[0].y1 -= 1;
    }
    
    //calculating ymin,ymax and x
    for(int i=0;i<numofvertices;++i){
        if (edgelist[i].y1>=edgelist[i].y2){
            edgelist[i].ymin = edgelist[i].y2;
            edgelist[i].x = edgelist[i].x2;
            edgelist[i].ymax = edgelist[i].y1;
        }
        else {
            edgelist[i].ymin = edgelist[i].y1;
            edgelist[i].x = edgelist[i].x1;
            edgelist[i].ymax = edgelist[i].y2;
        }
    }
    
    struct edgeliststructure tempstr;
    
    //sorting according to ymin
    for (int i=0;i<numofvertices-1;++i){
        for (int j=i+1;j<numofvertices;++j){
            if (edgelist[i].ymin>edgelist[j].ymin){
                tempstr = edgelist[i];
                edgelist[i] = edgelist[j];
                edgelist[j] = tempstr;
            }
        }
    }
    
    for (int i=0;i<numofvertices;++i){
        printf("x1=%lf y1=%lf x2=%lf y2=%lf ymin=%lf\n",edgelist[i].x1,edgelist[i].y1,edgelist[i].x2,edgelist[i].y2,edgelist[i].ymin);
    }
    
    for (int i=0;i<numofvertices;++i){
        printf("inside \n");
        int k = 0;
        int l = 0;
        for (int j = (int)edgelist[i].ymin+300; j <= (int)edgelist[i].ymax+300; ++j){
            while(scanline[j][k] != -10000.0)
                ++k;
            if (l==0){
                scanline[j][k] = edgelist[i].x;
                //printf("x=%lf\n",scanline[j][k]);
                ++l;
            }
            else{
                scanline[j][k] = rint(edgelist[i].x + edgelist[i].onebym);
                //printf("xmin=%lf 1/m=%lf x=%lf\n",edgelist[i].x,edgelist[i].onebym,scanline[j][k]);
                edgelist[i].x += edgelist[i].onebym;
            }
            ++k;
        }
    }
    
    int cnt2=0;
    for (int i=0;i<500;++i){
        int flag = 0;
        cnt2 = 0;
        for(int j=0;j<500;++j){
            if (scanline[i][j]!=-10000.0){
                printf("%lf ",scanline[i][j]);
                finalscanline[difofyminymax].x[cnt2] = scanline[i][j];
                flag = 1;
                ++cnt2;
            }
        }
        if (flag == 1){
            finalscanline[difofyminymax++].cnt = cnt2;
            printf("\n");
        }
    }
    
    double k = finalmin;
    for (int i=0;i<difofyminymax;++i){
        printf("%lf --> ",k);
        for (int j=0;j<finalscanline[i].cnt;++j)
            printf("%lf ",finalscanline[i].x[j]);
        printf("\n");
        ++k;
    }
    
    for (int i=0;i<difofyminymax;++i){
        for (int j=0;j<finalscanline[i].cnt-1;++j){
            for (int k=j+1;k<finalscanline[i].cnt;++k){
                if (finalscanline[i].x[j]>finalscanline[i].x[k]){
                    double temp;
                    temp = finalscanline[i].x[j];
                    finalscanline[i].x[j] = finalscanline[i].x[k];
                    finalscanline[i].x[k] = temp;
                }
            }
        }
    }
    
    k = finalmin;
    for (int i=0;i<difofyminymax;++i){
        printf("%lf --> ",k);
        for (int j=0;j<finalscanline[i].cnt;++j)
            printf("%lf ",finalscanline[i].x[j]);
        printf("\n");
        ++k;
    }
    
    
    glutInit(&argc,argv);
    glutCreateWindow("Scan_Line_Polygon_Filling_Algo_");
    glutDisplayFunc(mydisplay);
    glutMainLoop();
    return 0;
}

//test case:

// vertex           points

// 7 2 7 4 12 8 15 16 9 11 5 8 7 5 5
// 7 10 5 5 30 20 40 20 70 80 50 60 10 30 3
// 7 -10 5 -5 30 -20 40 -20 70 -80 50 -60 10 -30 3
// 7 10 -5 5 -30 20 -40 20 -70 80 -50 60 -10 30 -3
// 7 -10 -5 -5 -30 -20 -40 -20 -70 -80 -50 -60 -10 -30 -3
