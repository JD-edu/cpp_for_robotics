#include <iostream>
using namespace std;

int main() {
    int count = 1;
  
    cout << "1부터 5까지 출력:" << endl;
  
    while (count <= 5) {
        cout << "현재 숫자: " << count << endl;
        count++; // count를 1 증가
    }
  
    cout << "반복 완료!" << endl;
  
    return 0;
}