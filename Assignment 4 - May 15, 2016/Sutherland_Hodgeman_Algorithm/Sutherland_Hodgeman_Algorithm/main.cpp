//
//  main.cpp
//  Sutherland_Hodgeman_Algorithm
//
//  Created by Asif Mohaimen on 5/15/16.
//  Copyright © 2016 Asif Mohaimen. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
//#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>

//#include <conio.h>


using namespace std;

typedef pair<int,int> ii;

#define EPS 1e-9

const int MAX = 105;
double xx0,xx1;
double yy0,yy1;
int N;
double x1[MAX], y1[MAX], x2[MAX], y2[MAX], xMin, xMax, yMin, yMax, m;
bool done = false;
vector<double> res;
double xx2, yy2, xx3, yy3;
double polygon[MAX][MAX][2], outputPolygon[MAX][MAX][2];
double nextInt[MAX][MAX][2];
double self[MAX][MAX][2];


void init(void) {
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100.0,100.0,-100.0,100.0);
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






bool onLeft(double x1,double y1,double x2,double y2,double x, double y) {
    return (x2-x1)*(y-y1) - (y2-y1)*(x-x1) >= 0;
}

bool onRight(double x1,double y1,double x2,double y2,double x, double y) {
    return (x2-x1)*(y-y1) - (y2-y1)*(x-x1) < 0.0;
}

void takeIntersection(int polygonNo, int cur, int next, double x1, double y1, double x2, double y2) { //next update
    double dy = y2-y1;
    double dx = x2-x1;
    
    double fx = polygon[polygonNo][cur][0];
    double fy = polygon[polygonNo][cur][1];
    double sx = polygon[polygonNo][next][0];
    double sy = polygon[polygonNo][next][1];
    
    if(abs(dx) < EPS) { // vertical line
        if(abs(sy-fy) < EPS) { // horizontal line
            outputPolygon[polygonNo][next][0] = x1;
            nextInt[polygonNo][cur][0] = x1;
            outputPolygon[polygonNo][next][1] = fy;
            nextInt[polygonNo][cur][1] = fy;
        } else {
            outputPolygon[polygonNo][next][0] = x1;
            nextInt[polygonNo][cur][0] = x1;
            outputPolygon[polygonNo][next][1] = sy + (sy-fy)*(x1-sx)/(sx-fx);
            nextInt[polygonNo][cur][1] = sy + (sy-fy)*(x1-sx)/(sx-fx);
        }
    } else { // horizontal line
        if(abs(sx-fx) < EPS) { // vertical line
            outputPolygon[polygonNo][next][1] = y1;
            nextInt[polygonNo][cur][1] = y1;
            outputPolygon[polygonNo][next][0] = fx;
            nextInt[polygonNo][cur][0] = fx;
        } else {
            outputPolygon[polygonNo][next][1] = y1;
            nextInt[polygonNo][cur][1] = y1;
            outputPolygon[polygonNo][next][0] = fx + (fx-sx)/(fy-sy)*(y1-fy);
            nextInt[polygonNo][cur][0] = fx + (fx-sx)/(fy-sy)*(y1-fy);
        }
    }
    return ;
}

void takeTwo(int polygonNo, int cur, int next, double x1, double y1, double x2, double y2) {
    double m;
    double dy = y2-y1;
    double dx = x2-x1;
    
    double fx = polygon[polygonNo][cur][0];
    double fy = polygon[polygonNo][cur][1];
    double sx = polygon[polygonNo][next][0];
    double sy = polygon[polygonNo][next][1];
    
    
    if(abs(dx) < EPS) { // vertical line
        if(abs(sy-fy) < EPS) { // horizontal line
            outputPolygon[polygonNo][cur][0] = x1;
            self[polygonNo][cur][0] = x1;
            outputPolygon[polygonNo][cur][1] = fy;
            self[polygonNo][cur][1] = fy;
        } else {
            outputPolygon[polygonNo][cur][0] = x1;
            self[polygonNo][cur][0] = x1;
            outputPolygon[polygonNo][cur][1] = sy + (sy-fy)*(x1-sx)/(sx-fx);
            self[polygonNo][cur][1] = sy + (sy-fy)*(x1-sx)/(sx-fx);
        }
    } else { // horizontal line
        if(abs(sx-fx) < EPS) { // vertical line
            outputPolygon[polygonNo][cur][1] = y1;
            self[polygonNo][cur][1] = y1;
            outputPolygon[polygonNo][cur][0] = fx;
            self[polygonNo][cur][0] = fx;
        } else {
            outputPolygon[polygonNo][cur][1] = y1;
            self[polygonNo][cur][1] = y1;
            outputPolygon[polygonNo][cur][0] = fx + (fx-sx)/(fy-sy)*(y1-fy);
            self[polygonNo][cur][0] = fx + (fx-sx)/(fy-sy)*(y1-fy);
        }
    }
    return ;
}

void doActions(int polygonNo, int cur, int next, double x1, double y1, double x2, double y2) {
    double firstX, firstY;
    double secondX, secondY;
    firstX = polygon[polygonNo][cur][0];
    firstY = polygon[polygonNo][cur][1];
    secondX = polygon[polygonNo][next][0];
    secondY = polygon[polygonNo][next][1];
    if(onLeft(x1,y1,x2,y2,firstX,firstY) == true && onLeft(x1,y1,x2,y2,secondX,secondY) == true) { // both on left
        ;// ok
    } else if(onRight(x1,y1,x2,y2,firstX,firstY)==true && onRight(x1,y1,x2,y2,secondX,secondY) == true) { // both on Right
        outputPolygon[polygonNo][cur][0] = 1000; //ignore
        outputPolygon[polygonNo][cur][1] = 1000; //ignore
        outputPolygon[polygonNo][next][0] = 1000; //ignore
        outputPolygon[polygonNo][next][1] = 1000; //ignore
    } else if(onLeft(x1,y1,x2,y2,firstX,firstY) == true) { // only first point is on left
        takeIntersection(polygonNo, cur, next, x1, y1, x2, y2);
    } // take intersection
    else{ // only second point is on left
        takeTwo(polygonNo,cur,next,x1,y1,x2,y2); // only cur update
    }
    ; // take intersection and second
}

void cutPolygons(double x1, double y1, double x2, double y2) {
    for(int i=0; i<N; i++) {
        for(int j=1; j<=polygon[i][0][0]; j++) {
            int next = j + 1;
            if(next > polygon[i][0][0]) next = 1;
            doActions(i,j,next,x1,y1,x2,y2);
        }
    }
    return ;
}

double checkX(double x){
    if(x >= xx0 && x <= xx2)
        return x;
    if(x < xx0)
        return xx0;
    if(x > xx2)
        return xx2;
}

double checkY(double y){
    if(y >= yy0 && y <= yy2)
        return y;
    if(y < yy0)
        return yy0;
    if(y > yy2)
        return yy2;
}

bool rightSelf(int i, int j){
    double a1 = abs(self[i][j][0]-1000) + abs(self[i][j][1]-1000);
    double& a2 = self[i][j][0];
    double& a3 = self[i][j][1];
    if(a2 < xx0) a2 = xx0;
    else if(a2 > xx2) a2 = xx2;
    if(a3 < yy0) a3 = yy0;
    else if(a3 > yy2) a3 = yy2;
    if(a1 > EPS && a2 >= xx0 && a2 <= xx2 && a3 >= yy0 && a3 <= yy2)
        return true;
    return false;
}

bool rightNextInt(int i,int j){
    double a1 = abs(nextInt[i][j][0]-1000) + abs(nextInt[i][j][1]-1000);
    double& a2 = nextInt[i][j][0];
    double& a3 = nextInt[i][j][1];
    if(a2 < xx0) a2 = xx0;
    else if(a2 > xx2) a2 = xx2;
    if(a3 < yy0) a3 = yy0;
    else if(a3 > yy2) a3 = yy2;
    if(a1 > EPS && a2 >= xx0 && a2 <= xx2 && a3 >= yy0 && a3 <= yy2)
        return true;
    return false;
}

bool rightOutput(int i, int j){
    double a1 = abs(outputPolygon[i][j][0]-1000) + abs(outputPolygon[i][j][1]-1000);
    double& a2 = outputPolygon[i][j][0];
    double& a3 = outputPolygon[i][j][1];
    if(a2 < xx0) a2 = xx0;
    else if(a2 > xx2) a2 = xx2;
    if(a3 < yy0) a3 = yy0;
    else if(a3 > yy2) a3 = yy2;
    if(a1 > EPS && a2 >= xx0 && a3 <= xx2)
        return true;
    return false;
}


void clip() {
    if(done) return ; // avoiding recalculation
    done = true;
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xx0,yy0);
    glVertex2f(xx1, yy1);
    glVertex2f(xx2, yy2);
    glVertex2f(xx3, yy3);
    glEnd();
    cutPolygons(xx0, yy0, xx1, yy1);
    cutPolygons(xx1, yy1, xx2, yy2);
    cutPolygons(xx2, yy2, xx3, yy3);
    cutPolygons(xx3, yy3, xx0, yy0);
    glColor3f(0.0, 0.5, 0.5);
    for(int i=0; i<N; i++) {
        glBegin(GL_LINE_LOOP);
        for(int j=1; j<=polygon[i][0][0]; j++) {
            int next = j+1;
            if(next > polygon[i][0][0]) next = 1;
            if(rightSelf(i,j) == true)
                glVertex2f(self[i][j][0], self[i][j][1]);
            else if(rightOutput(i,j) == true)
                glVertex2f(outputPolygon[i][j][0],outputPolygon[i][j][1]);
            if(rightNextInt(i,j) == true)
                glVertex2f(nextInt[i][j][0], nextInt[i][j][1]);
        }
        glEnd();
    }
    glFlush();
}

void read() {
    printf("\nEnter lower left corner of the window(x,y): ");
    cin>>xx0>>yy0;
    printf("Enter upper right corner of the window(x,y): ");
    cin>>xx2>>yy2;
    xx1 = xx2;
    yy1 = yy0;
    xx3 = xx0;
    yy3 = yy2;
    
    printf("Number of Polygons: ");
    scanf("%d",&N);
    for(int i=0; i<N; i++) {
        printf("\n\t\tPolygon %d:\n", i+1);
        printf("Number of vertices: ");
        scanf("%lf", &polygon[i][0][0]);
        outputPolygon[i][0][0] = polygon[i][0][0];
        for(int j=1; j<=polygon[i][0][0]; j++) {
            printf("P%d: ", j);
            cin>>polygon[i][j][0]>>polygon[i][j][1];
            outputPolygon[i][j][0] = polygon[i][j][0];
            outputPolygon[i][j][1] = polygon[i][j][1];
            nextInt[i][j][0] = 1000;
            nextInt[i][j][1] = 1000;
            self[i][j][0] = 1000;
            self[i][j][1] = 1000;
        }
    }
    return ;
}


int main(int argc,char **argv) {
    printf("                        SUTHERLAND HODGEMAN ALGORITHM\n\n");
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    read();
    glutCreateWindow("Sutherland Hodgeman algorithm");
    init();
    glutDisplayFunc( clip );
    glutMainLoop();
    return 0;
}
