#include <iostream>
using namespace std;

int main() {
    cout << "카운트다운 시작!" << endl;
  
    for (int i = 5; i >= 1; i--) {
        cout << i << "초..." << endl;
    }
  
    cout << "발사!" << endl;
  
    return 0;
}