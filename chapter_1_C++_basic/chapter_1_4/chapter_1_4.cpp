#include <iostream>
using namespace std;

int main() {
    // C++: 타입 명시 필수, 타입 고정
    int x = 100;
    cout << x << endl;  // 100
  
    // x = "안녕";  //  컴파일 에러!
  
    // 다른 타입의 데이터를 저장하려면 새 변수 필요
    string message = "안녕";
    cout << message << endl;  // 안녕
  
    int arr[] = {1, 2, 3};
    cout << arr[0] << endl;  // 1
  
    return 0;
}