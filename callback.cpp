#include <iostream>

void check(int n, bool (*cond)(int)){
    if (cond(n)){
        std::cout << "TRUE" << std::endl;
    }else{
        std::cout << "FALSE" << std::endl;
    }
}

bool is_even(int n){
    return n % 2 == 0;
}

int main(){
    
    check(4, &is_even);
    check(5, &is_even);

    return 0;
}
