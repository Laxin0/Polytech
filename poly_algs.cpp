#include "data_types.h"
#include "poly_algs.h"
#include <cmath>

bool DoubleGreat(double a, double b){ return a > b + EPSILON; }
bool DoubleLess (double a, double b){ return a + EPSILON < b; }
bool DoubleEq   (double a, double b){ return fabs(a - b) < EPSILON; }

double Perimeter(Rectangle rect){
    return rect.length * 2 + rect.width * 2;
}

double Area(Rectangle rect){
    return rect.length * rect.width;
}

bool IsRectValid(Rectangle rect){
    return rect.length > 0 && rect.width > 0;
}

int FindRectanglePer(Rectangle *rects, int size, Interval perInter){
    for (int i = 0; i < size; ++i){
        double per = Perimeter(rects[i]);
        if (DoubleGreat(per, perInter.lhs) && DoubleLess(per, perInter.rhs)){
            return i;
        }
    }
    return INVALID_INDEX;
}

int FindRectangleIf(Rectangle *rects, int size, Interval interval, bool (*cond)(Rectangle, Interval)){
     for (int i = 0; i < size; ++i){
        if (IsRectValid(rects[i]) && cond(rects[i], interval)){
            return i;
        }
    }
    return INVALID_INDEX;
}

bool IsPerInInterval(Rectangle rect, Interval interval){
    double per = Perimeter(rect);
    if ((DoubleGreat(per, interval.lhs) && DoubleLess(per, interval.rhs)) ||
        DoubleEq(interval.lhs, per) || DoubleEq(interval.rhs, per)){
        return true;
    }
    return false;
}
bool IsAreaInInterval(Rectangle rect, Interval interval){ // [45, 55]
    double sq = rect.length * rect.width;
    if ((DoubleGreat(sq, interval.lhs) && DoubleLess(sq, interval.rhs)) ||
        DoubleEq(interval.lhs, sq) || DoubleEq(interval.rhs, sq)){
        return true;
    }
    return false;
}

void Swap(Rectangle rects[], int i, int j){
    Rectangle t = rects[i];
    rects[i] = rects[j];
    rects[j] = t;
}

void InsertionSortByPer(Rectangle rects[], int size){
    for(int i = 1; i < size; ++i){
        for(int j = i; j > 0; --j){
            if(DoubleLess(Perimeter(rects[j]), Perimeter(rects[j-1]))){
                Swap(rects, j, j-1);
            }else{
                break;
            }
        }
    }
}

void InsertionSort(Rectangle rects[], int size, bool (*cmp)(Rectangle, Rectangle)){
    for(int i = 1; i < size; ++i){
        for(int j = i; j > 0; --j){
            if(cmp(rects[j-1], rects[j])){
                Swap(rects, j-1, j);
            }else{
                break;
            }
        }
    }
}

int Partition(Rectangle rects[], int i, int j, bool (*cmp)(Rectangle, Rectangle)){
    int pivot = j;
    int low = i;
    for(int i = low; i < j; ++i){
        if (!cmp(rects[i], rects[pivot])){
            Swap(rects, i, low);
            low++;
        }
    }
    Swap(rects, pivot, low);
    return low;
}

void QuickSort(Rectangle rects[], int j, int k, bool (*cmp)(Rectangle, Rectangle)){
    if(j >= k) return;
    
    int i = Partition(rects, j, k, cmp);
    QuickSort(rects, j, i-1, cmp);
    QuickSort(rects, i+1, k, cmp);
}

bool IsPerimGt(Rectangle a, Rectangle b){
    return Perimeter(a) > Perimeter(b) + EPSILON;
}

bool IsAreaGt(Rectangle a, Rectangle b){
    return Area(a) > Area(b) + EPSILON;
}


