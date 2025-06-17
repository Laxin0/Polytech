#include <iostream>
#include "test_poly_algs.h"
#include "poly_algs.h"
#include "data_types.h"
#include "data_generator.h"

void TestGenerateRandomDoubleBounds(){
    int c = 0;
    for(int i = 0; i < 1100000; ++i){
        double rand = GenerateRandomDouble(-10, 99, 3);
        if(rand < -10.35 || rand > 99.875) c++;
    }
    if(c == 0){
        std::cout << "TestGenerateRandomDoubleBounds: OK\n";
    }else{
        std::cout << "TestGenerateRandomDoubleBounds: FAILED\n";
    }
}

void TestGenerateRandomIntBounds(){
    int c = 0;
    for(int i = 0; i < 1100000; ++i){
        int rand = GenerateRandomInt(-10, 99);
        if(rand < -10 || rand > 99) c++;
    }
    if(c == 0){
        std::cout << "TestGenerateRandomIntBounds: OK\n";
    }else{
        std::cout << "TestGenerateRandomIntBounds: FAILED\n";
    }
}

void TestGenerateRandomIntDistribution(){
    int average = 1100000/110;
    int acuracy = 500;
    int errors = 0;

    int numsc[110];
    for(int i = 0; i < 110; ++i){
        numsc[i] = 0;
    }

    for (int i = 0; i < 1100000; ++i){
        int rand = GenerateRandomInt(-10, 99);
        numsc[rand+10]++;
    }

    for(int i = 0; i < 110; ++i){
        if (numsc[i] < average-acuracy || numsc[i] > average+acuracy){
            errors++;
            std::cout << i-10 << ": " << numsc[i] << "\n";
        }
        //std::cout << i-10 << ": " << numsc[i] << "\n";
    }

    if(errors == 0){
         std::cout << "TestGenerateRandomIntDistribution: OK\n";
    }else{
         std::cout << "TestGenerateRandomIntDistribution: FAILED\n";
    }
}

void TestGenerateRandomDoubleDistribution(){
    int numsc[10];
    int average = 1000000/10;
    int accuracy = 4000;
    int errors = 0;

    for(int i = 0; i < 10; ++i){
        numsc[i] = 0;
    }
    
    double step = (99.875+10.35)/10;

    for(int n = 0; n < 1000000; ++n){
        int rand = GenerateRandomDouble(-10.35, 99.875, 6);
        int i = 0;
        for(double s = -10.35; s < 99.875; s += step){
            if (rand >= s && rand < s+step){
                numsc[i]++;
                break;
            }
            i++;
        }
    }

    for(int i = 0; i<10;++i){
        if(numsc[i] < average-accuracy || numsc[i] > average+accuracy){
            errors++;
            std::cout << numsc[i] << "\n";
        }
    }
    if(errors == 0){
        std::cout << "TestGenerateRandomDoubleDistribution: OK\n";
    }else{
        std::cout << "TestGenerateRandomDoubleDistribution: FAILED\n";   
    }
}

void TestGetRandomRectangleAspect(){
    int errors = 0;
    for (int i = 0; i < 10000; ++i){
        Rectangle rect = GetRandomRectangle(Interval{-10, 100}, Interval{-10, 100});
        if (rect.length <= rect.width-EPSILON){
            std::cout << "width: " << rect.width << " length: " << rect.length << std::endl;
            errors++;
        }
    }
    if(errors == 0){
        std::cout << "TestGetRandomRectangleAspect: OK\n";
    }else{
        std::cout << "TestGetRandomRectangleAspect: FAILED\n";
    }

}

void TestFindRectanglePerFound1(){
    Rectangle rects[] = {
        Rectangle{10, 10}, // 40
        Rectangle{10, 15}, // 50
        Rectangle{30, 40}  // 140
    };

    int i = FindRectanglePer(rects, 3, Interval{45, 55}); 
    if (i == 1){
        std::cout << "TestFindRectanglePerFound1: OK" << std::endl;
    }else{
        std::cout << "Expected 1, but got " << i << std::endl;
        std::cout << "TestFindRectanglePerFound1: FAILED" << std::endl;
    }
}

void TestFindRectanglePerNotFound(){
    Rectangle rects[] = {
        Rectangle{10, 10}, // 40
        Rectangle{10, 15}, // 50
        Rectangle{30, 40}  // 140
    };

    int i = FindRectanglePer(rects, 3, Interval{55, 100}); 
    if (i == INVALID_INDEX){
        std::cout << "TestFindRectanglePerNotFound: OK" << std::endl;
    }else{
        std::cout << "Expected 1, but got " << i << std::endl;
        std::cout << "TestFindRectanglePerNotFound: FAILED" << std::endl;
    }
}

void TestFindRectangleIfBounds(){
    Rectangle rects[] = {
        Rectangle{10, 10}, // 40
        Rectangle{10, 15}, // 50
        Rectangle{30, 40}  // 140
    };
    
    int i = FindRectangleIf(rects, 3, Interval{40, 45}, IsPerInInterval); 
    if (i != 0){
        std::cout << "Expected 0, but got " << i << std::endl;
        std::cout << "TestFindRectangleIfBounds: FAILED" << std::endl;
        return;
    }
    i = FindRectangleIf(rects, 3, Interval{42, 50}, IsPerInInterval); 
    if (i != 1){
        std::cout << "Expected 1, but got " << i << std::endl;
        std::cout << "TestFindRectangleIfBounds: FAILED" << std::endl;
        return;
    }
    std::cout << "TestFindRectangleIfBounds: OK" << std::endl; 
}

void TestFindRectangleIfInvalidData(){
    Rectangle rects[] = {
        Rectangle{10, 10},   // 40
        Rectangle{10, 15},   // 50
        Rectangle{30, 40},   // 140
        Rectangle{-20, 50},  // 60
        Rectangle{-20, -20}, //-80 400
    };
    
    int i = FindRectangleIf(rects, 5, Interval{60, 61}, IsPerInInterval); 
    if (i != INVALID_INDEX){
        std::cout << "Expected " << INVALID_INDEX << ", but got " << i << std::endl;
        std::cout << "TestFindRectangleIfInvalidData: FAILED" << std::endl;
        return;
    }
    i = FindRectangleIf(rects, 5, Interval{300, 500}, IsAreaInInterval); 
    if (i != INVALID_INDEX){
        std::cout << "Expected " << INVALID_INDEX << " but got " << i << std::endl;
        std::cout << "TestFindRectangleIfInvalidData: FAILED" << std::endl;
        return;
    }
    std::cout << "TestFindRectangleIfInvalidData: OK" << std::endl; 
}

//TODO: write checkSort for all kinds of funclion
bool CheckSort(Rectangle rects[], int size){
    for(int i = 0; i < size-1; ++i){
        if (Perimeter(rects[i]) > Perimeter(rects[i+1])){
            return false;
        }
    }
    return true;
}

void TestInsertionSort(){
    Rectangle rects[] = {
        Rectangle{10, 10},   // 40
        Rectangle{10, 15},   // 50
        Rectangle{30, 40},   // 140
        Rectangle{-20, 50},  // 60
        Rectangle{-20, -20}, //-80 400
    };

    InsertionSort(rects, 5, IsPerimGt);
    if (!CheckSort(rects, 5)){
        std::cout << "TestInsertionSort: FAILED" << std::endl;
        return;
    }

    std::cout << "TestInsertionSort: OK" << std::endl;
}

void TestInsertionSortEmptyArray(){
    Rectangle rectsBefore[] = {
        Rectangle{30, 40},   // 140
        Rectangle{10, 15},   // 50
        Rectangle{10, 10},   // 40
    };
    Rectangle rectsAfter[] = {
        Rectangle{30, 40},   // 140
        Rectangle{10, 15},   // 50
        Rectangle{10, 10},   // 40
    };

    InsertionSort(rectsAfter, 0, IsPerimGt);
    
    for(int i = 0; i < 3; ++i){
        if (!DoubleEq(Perimeter(rectsBefore[i]), Perimeter(rectsAfter[i]))){
            std::cout << "TestInsertionSortEmptyArray: FAILED" << std::endl;
            std::cout << "B: " << Perimeter(rectsBefore[i]) << " A: " << Perimeter(rectsAfter[i]) << std::endl;
            return;
        }
    }
    std::cout << "TestInsertionSortEmptyArray: OK" << std::endl;

}

void RunAllTests(){
    TestGenerateRandomDoubleBounds();
    TestGenerateRandomIntBounds();
    TestGenerateRandomIntDistribution();
    TestGenerateRandomDoubleDistribution();
    TestGetRandomRectangleAspect();
    TestFindRectanglePerFound1();
    TestFindRectanglePerNotFound();
    TestFindRectangleIfBounds();
    TestFindRectangleIfInvalidData();
    TestInsertionSort();
    TestInsertionSortEmptyArray();
}


