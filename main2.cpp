#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

#define EPSILON 0.00000000001
#define INVALID_INDEX -1

//NOTE: Федор Пикус c++ 9ch

int GenerateRandomInt(int min, int max){
    int x = std::rand() % (max + 1 - min);
    x += min;
    return x;
}

double GenerateRandomDouble(double min, double max, int precision){
    int randInt = GenerateRandomInt(0, pow(10, precision)-1);
    return (max-min)/pow(10, precision) * randInt + min;
}

struct Rectangle{
    double width;
    double length;
};

struct Range{
    double lhs, rhs;
};

Rectangle GetRandomRectangle(Range lengthRange, Range widthRange){
    double width = GenerateRandomDouble(widthRange.lhs, widthRange.rhs, 2);
    double length = GenerateRandomDouble(width, lengthRange.rhs, 2);
    Rectangle rect = {.width = width,
                      .length = length};
    return rect;
}

void TestGetRandomRectangleAspect(){
    int errors = 0;
    for (int i = 0; i < 10000; ++i){
        Rectangle rect = GetRandomRectangle(Range{-10, 100}, Range{-10, 100});
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

double Perimeter(Rectangle rect){
    return rect.length * 2 + rect.width * 2;
}

int FindRectanglePer(Rectangle *rects, int size, Range perRange){
    for (int i = 0; i < size; ++i){
        double per = Perimeter(rects[i]);
        if (per >= perRange.lhs + EPSILON && per < perRange.rhs - EPSILON){
            return i;
        }
    }
    return INVALID_INDEX;
}

int FindRectangle(Rectangle *rects, int size, bool (*cond)(Rectangle)){
     for (int i = 0; i < size; ++i){
        if (cond(rects[i])){
            return i;
        }
    }
    return INVALID_INDEX;
}

// void TestFindRectanglePerBouds

void TestFindRectanglePerFound1(){
    Rectangle rects[] = {
        Rectangle{10, 10}, // 40
        Rectangle{10, -15}, // 50
        Rectangle{30, 40}  // 140
    };

    int i = FindRectanglePer(rects, 3, Range{45, 55}); 
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

    int i = FindRectanglePer(rects, 3, Range{55, 100}); 
    if (i == INVALID_INDEX){
        std::cout << "TestFindRectanglePerNotFound: OK" << std::endl;
    }else{
        std::cout << "Expected 1, but got " << i << std::endl;
        std::cout << "TestFindRectanglePerNotFound: FAILED" << std::endl;
    }
}

bool IsPerInRange(Rectangle rect){ // [45, 55]
    double per = Perimeter(rect);
    if (per > 45 + EPSILON && per + EPSILON < 55){
        return true;
    }
    return false;
}

bool IsLengthGt42(Rectangle rect){ return rect.length > 42; }
    
int main(){ 
    std::srand(std::time(NULL));
    Rectangle rects[] = {
        Rectangle{10, 10},   // 40
        Rectangle{10, 15},   // 50
        Rectangle{30, 40},   // 140
        Rectangle{43, 43},
        Rectangle{-20, 50},  // 60
        Rectangle{-20, -20}, //-80
    };
 
    // std::cout << "0..3 IsPerInRange: " << FindRectangle(rects, 3, IsPerInRange) << std::endl;
    // std::cout << "0..3 IsLengthGt42: " << FindRectangle(rects, 3, IsLengthGt42) << std::endl;
    // std::cout << "0..4 IsLengthGt42: " << FindRectangle(rects, 4, IsLengthGt42) << std::endl;
    
    std::cout << "Bound 40..42: " <<
    FindRectanglePer(rects, sizeof(rects)/sizeof(rects[0]), Range{40, 42}) << std::endl; 

    std::cout << "Neg: " <<
    FindRectanglePer(rects, sizeof(rects)/sizeof(rects[0]), Range{59, 61}) << std::endl; 
    
    TestGetRandomRectangleAspect();
    TestFindRectanglePerFound1();
    TestFindRectanglePerNotFound();
    return 0;
}


