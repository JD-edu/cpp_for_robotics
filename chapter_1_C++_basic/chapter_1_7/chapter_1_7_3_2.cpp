#include <iostream>
using namespace std;

int main() {
    int number;
  
    cout << "양수를 입력하세요 (0 또는 음수 입력시 종료): ";
    cin >> number;
  
    while (number > 0) {
        cout << "입력한 수: " << number << ", 제곱: " << (number * number) << endl;
        cout << "다음 양수를 입력하세요 (0 또는 음수 입력시 종료): ";
        cin >> number;
    }
  
    cout << "프로그램을 종료합니다." << endl;
  
    return 0;
}