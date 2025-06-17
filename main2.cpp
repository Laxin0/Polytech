#include "data_types.h"
#include "data_generator.h"
#include "poly_algs.h"
#include "test_poly_algs.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

int main(){ 
    std::srand(std::time(NULL));
    Rectangle rects[] = {
        Rectangle{10, 10},   // 40  20
        Rectangle{10, 15},   // 50  150
        Rectangle{30, 40},   // 140 1200
        Rectangle{-20, 50},  // 60  -1000
        Rectangle{-20, -20}, //-80  400
    };
    
    std::cout << "Before: " << std::endl;
    for(int i = 0; i < 5; ++i){
        std::cout << Perimeter(rects[i]) << std::endl;
    }
    //InsertionSortByPer(rects, 5);
    InsertionSort(rects, 5, IsPerimGt);

    std::cout << "After: " << std::endl;
    for(int i = 0; i < 5; ++i){
        std::cout << Perimeter(rects[i]) << std::endl;
    }

    RunAllTests();
    return 0;
}
