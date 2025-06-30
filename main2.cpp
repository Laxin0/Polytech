#include "data_types.h"
#include "data_generator.h"
#include "poly_algs.h"
#include "test_poly_algs.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

/* TODO: TestPartition failed (right bound included or not).
*        Check one more time if Partition works correctly and returns right value.
*        If it does think how to make all functions to use one style ( `[,]` or `[,)` )
*/

// #define TEST
int main(){
    std::srand(std::time(NULL));
#ifdef TEST
    RunAllTests();
#else

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
    std::cout << "First invalid: " <<  QuickSortSafe(random_rects, 0, 9, IsPerimGt) << std::endl;
    //std::cout << "First invalid: " << Partition(random_rects, 0, 10-1, IsFirstRectInvalid) << std::endl;

    std::cout << "After:" << std::endl;

    for(int i = 0; i < 10; ++i){
        std::cout << Perimeter(random_rects[i]) << " (";
        std::cout << IsRectValid(random_rects[i]) << "), ";
    }
    std::cout << "\n\n" << std::endl;

#endif //TEST
    return 0;
}
