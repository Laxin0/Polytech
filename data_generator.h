#ifndef DATA_GETERATOR_H
#define DATA_GENERATOR_H

#include "data_types.h"

Rectangle GetRandomRectangle(Interval lengthInterv, Interval widthInterv);
int GenerateRandomInt(int min, int max);
double GenerateRandomDouble(double min, double max, int precision);
#endif //DATA_GENERATOR_H
