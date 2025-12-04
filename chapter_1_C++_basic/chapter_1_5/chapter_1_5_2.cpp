#include <iostream>
#include <string>
using namespace std;

int main() {
    // 정수형
    int age = 25;
    unsigned int population = 50000000u;

    // 실수형
    double height = 175.5;
    float weight = 70.2f;

    // 문자형
    char grade = 'A';

    // 불린형
    bool isStudent = true;

    // 문자열 (클래스)
    string name = "김철수";

    cout << "이름: " << name << endl;
    cout << "나이: " << age << endl;
    cout << "신장: " << height << "cm" << endl;
    cout << "체중: " << weight << "kg" << endl;
    cout << "학점: " << grade << endl;
    cout << "학생 여부: " << isStudent << endl;
    cout << "인구: " << population << "명" << endl;

    return 0;
}
