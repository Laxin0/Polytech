#include <cmath>
#include <cstdlib>

#include "data_generator.h"
#include "data_types.h"

int GenerateRandomInt(int min, int max){
    int x = std::rand() % (max + 1 - min);
    x += min;
    return x;
}

double GenerateRandomDouble(double min, double max, int precision){
    int randInt = GenerateRandomInt(0, pow(10, precision)-1);
    return (max-min)/pow(10, precision) * randInt + min;
}

Rectangle GetRandomRectangle(Interval lengthInterv, Interval widthInterv){
    double width = GenerateRandomDouble(widthInterv.lhs, widthInterv.rhs, 2);
    double length = GenerateRandomDouble(width, lengthInterv.rhs, 2);
    Rectangle rect = {.width = width,
                      .length = length};
    return rect;
}
