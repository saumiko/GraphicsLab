//
//  main.cpp
//  BoundaryFill
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

//#include <conio.h>


using namespace std;

typedef pair<int,int> ii;

const int MAX = 105, MAX1 = 100;
int xx0,xx1;
int yy0,yy1;
int seedX, seedY;
int N, x[MAX], y[MAX];
bool colored[2*MAX][2*MAX], done = false;


void init(void) {
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100.0,100.0,-100.0,100.0);
}

void setColored(int x, int y){
    x += MAX1;
    y += MAX1;
    colored[x][y] = true;
}

bool isColored(int x, int y){
    x += MAX1;
    y += MAX1;
    //    printf("iscolored, x = %d\ty = %d\tcolor = %d\n",x,y,colored[x][y]);
    return colored[x][y];
}

void setPixel(GLint x,GLint y, bool boundaryColor) {
    if(!boundaryColor)
        glColor3f(0.498039,1.0,0.0);
    else
        glColor3f(1.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    setColored(x, y);
}



void drawHorizontalLine() {
    if(xx0 > xx1) swap(xx0, xx1);
    int x=xx0, y=yy0;
    while(x <= xx1) {
        setPixel(x, y,true);
        setColored(x,y);
        x++;
    }
}

void drawVerticalLine() {
    if(yy0 > yy1) swap(yy0, yy1);
    int x=xx0, y=yy0;
    while(y <= yy1) {
        setPixel(x,y,true);
        setColored(x,y);
        y++;
    }
}

void drawOthers() {
    int dx=abs(xx1-xx0), dy=abs(yy1-yy0);
    double x=xx0,y=yy0;
    if(dy <= dx) { // As |m| <= 1 we are going to increase x and get the corresponding y value
        double m = (double)(yy1-yy0)/(double)(xx1-xx0);
        while(x<=xx1) {
            setPixel((int)x,(int)y,true);
            x++;
            y = y + m;
        }
    } else { // |m| > 1, so the interval in ys is greater than that of x. so we shall iterate over y to get more points.
        int k = yy0 < yy1 ? 1 : -1;
        double m = (double)(yy1-yy0)/(double)(xx1-xx0), add = k/m;
        while((y <= yy1 && k == 1) || (y >= yy1 && k == -1)) {
            setPixel((int)x, (int)y,true);
            y = y+k;
            x = x+add;
        }
    }
}

void swap(int& a, int& b) {
    a += b;
    b = a-b;
    a = a-b;
}

void drawAxes() {
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(0, 100);
    glVertex2f(0, -100);
    glVertex2f(100, 0);
    glVertex2f(-100, 0);
    glEnd();
    
}

int validateSeed() {
    int cnt = 0;
    if(isColored(seedX,seedY)) //this is on boundary
        return -1;
    for(int i=seedX; i<=100; i++) {
        if(isColored(i,seedY)) // an edge has been found
            cnt++;
    }
    if(cnt%2 == 1) return 1;
    for(int i=seedY; i<=100; i++) {
        if(isColored(seedX,i)) // an edge has been found
            cnt++;
    }
    return cnt%2;
}



void rec(int x, int y){
    //    printf("x = %d\ty = %d\n", x, y);getch();
    if(isColored(x,y))
        return ;
    setPixel(x, y, false);
    if(!isColored(x-1, y))
        rec(x-1, y);
    if(!isColored(x+1,y))
        rec(x+1, y);
    if(!isColored(x,y-1))
        rec(x, y-1);
    if(!isColored(x,y+1))
        rec(x, y+1);
}

void boundaryFill() {
    int v = validateSeed();
    if(v == -1) {
        printf("seed is on vertex\n");
    } else if(v == 0){
        printf("seed is outside boundary\n");
    } else{
        rec(seedX,seedY);
    }
    return ;
}

void line() {
    if(done) return ; // so that the filled region is not cleared.
    done = true;
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    for(int i=1; i<=N; i++) {
        xx0 = x[i];
        xx1 = x[(i==N ? 1 : i+1)];
        yy0 = y[i];
        yy1 = y[(i==N ? 1: i+1)];
        if(xx0 > xx1) {
            swap(xx0, xx1);
            swap(yy0, yy1);
        }
        //        printf("(x0,y0,x1,y1) = (%d,%d,%d,%d)\n",xx0,yy0,xx1,yy1);
        if(yy0 == yy1) drawHorizontalLine();
        else if(xx0 == xx1) drawVerticalLine();
        else drawOthers();
    }
    boundaryFill();
    glFlush();
}

void read() {
    printf("\nNumber of vertices(Greater than 2): ");
    scanf("%d", &N);
    if(N < 3) {
        read();
    } else {
        for(int i=1; i<=N; i++) {
            printf("v%d: ", i);
            scanf("%d %d", x+i, y+i);
        }
    }
    printf("Enter seed: ");
    scanf("%d %d", &seedX, &seedY);
}


int main(int argc,char **argv) {
    memset(colored, 0, sizeof colored);
    //    printf("Enter (x0,y0,x1,y1): ");
    //    scanf("%d %d %d %d",&xx0,&yy0,&xx1,&yy1);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    read();
    glutCreateWindow("Boundary fill algorithm");
    init();
    glutDisplayFunc( line );
    glutMainLoop();
    return 0;
}

/*
 
 7
 5 10
 20 50
 30 30
 70 30
 80 65
 25 95
 -30 75
 45 35
 
 3
 -100 -100
 100 -100
 100 100
 70 10
 
 10
 -10 -90
 20 -95
 50 -60
 80 10
 45 40
 30 80
 -10 90
 -25 70
 -80 50
 -50 -60
 0 0
 
 4
 10 10
 30 10
 30 70
 10 70
 15 15
 
 10
 25 -90
 20 -15
 70 10
 30 30
 89 90
 -25 30
 -90 18
 -30 10
 -35 -55
 -10 -30
 0 0
 
 */

