#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

int GenerateRandomInt(int min, int max){
    int x = std::rand() % (max + 1 - min);
    x += min;
    return x;
}

double GenerateRandomDouble(double min, double max, int precision){
    int randInt = GenerateRandomInt(0, pow(10, precision)-1);
    return (max-min)/pow(10, precision) * randInt + min;
}

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

enum ShapeType{
  triangle = 1,
  rectangle,
  circle
};

struct Shape{
    ShapeType type;
    double width;
    double length;
};

Shape GetRandomShape(){
    Shape shape;
    int type = GenerateRandomInt(0, 2);
    switch (type){
        case 0:
            shape.type = triangle;
            break;
        case 1:
            shape.type = rectangle;
            break;
        case 2:
            shape.type = circle;
            break;
        default:
            std::cerr << "Unreacheble";
    }
    double width = GenerateRandomDouble(-10.35, 99.875, 6);
    shape.width = width;
    shape.length = GenerateRandomDouble(width, 99.875, 6);
    return shape;
}

int main(){
    std::srand(std::time(NULL));
    TestGenerateRandomDoubleBounds();
    TestGenerateRandomDoubleDistribution();
    TestGenerateRandomIntBounds();
    TestGenerateRandomIntDistribution();
    for(int i = 0; i < 10; ++i){
        Shape sh = GetRandomShape();
        std::cout << "type: " << sh.type <<
                     ", width: " << sh.width << 
                     ", length: " << sh.length << "\n";
    }   
}
