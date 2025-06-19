#include "data_types.h"
#include "data_generator.h"
#include "poly_algs.h"
#include "test_poly_algs.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
//NOTE: in quicksort think anbout invalid data
int main(){ 
    std::srand(std::time(NULL));

    Rectangle random_rects[10];
    for(int i = 0; i < 10; ++i){
        random_rects[i] = GetRandomRectangle(Interval{-10, 110}, Interval{-10, 110});
    }
    
    std::cout << "Before:" << std::endl;

    for(int i = 0; i < 10; ++i){
        std::cout << Perimeter(random_rects[i]) << " (";
        std::cout << IsRectValid(random_rects[i]) << "), ";
    }
    std::cout << std::endl;

    //InsertionSort(random_rects, 10, IsPerimGt);
    std::cout << "Last valid: " << QuickSortSafe(random_rects, 0, 10-1, IsPerimGt) << std::endl;

    std::cout << "After:" << std::endl;

    for(int i = 0; i < 10; ++i){
        std::cout << Perimeter(random_rects[i]) << " (";
        std::cout << IsRectValid(random_rects[i]) << "), ";
    }
    std::cout << "\n\n" << std::endl;

    // RunAllTests();
    return 0;
}
