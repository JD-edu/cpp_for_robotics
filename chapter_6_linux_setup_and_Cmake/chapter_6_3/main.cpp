// main.cpp
#include <iostream>
#include "hello.h" // hello.h를 포함하여 say_hello와 add 함수를 사용

int main() {
    std::cout << "--- Program Start ---" << std::endl;
    
    // hello.cpp에서 구현된 함수 호출
    say_hello(); 

    int result = add(5, 7);
    std::cout << "The sum of 5 and 7 is: " << result << std::endl;
    
    std::cout << "--- Program End ---" << std::endl;
    return 0;
}