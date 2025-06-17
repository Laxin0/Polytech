#ifndef POLY_ALGS_H
#define POLY_ALGS_H

#include "data_types.h"

#define EPSILON 0.00000000001
#define INVALID_INDEX -1

bool DoubleGreat(double a, double b);
bool DoubleLess (double a, double b);
bool DoubleEq   (double a, double b);

double Perimeter(Rectangle rect);

int FindRectanglePer(Rectangle *rects, int size, Interval perInter);

int FindRectangleIf(Rectangle *rects, int size, Interval interval, bool (*cond)(Rectangle, Interval));

bool IsPerInInterval(Rectangle rect, Interval interval);

bool IsSquareInInterval(Rectangle rect, Interval interval);

//void Swap(Rectangle rects[], int i, int j);

void InsertionSortByPer(Rectangle rects[], int size);

void InsertionSort(Rectangle rects[], int size, bool (*cmp)(Rectangle, Rectangle));

bool IsPerimGt(Rectangle a, Rectangle b);

#endif
