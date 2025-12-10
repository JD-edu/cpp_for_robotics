#pragma once
#include <iostream>
#include <string>

// ========== 간단한 데이터 보관함 클래스 템플릿 ==========
// 로봇이 하나의 값을 저장하고 관리하는 용도
template<typename T>
class DataBox {
private:
    T data;           // 저장될 데이터
    bool hasData;     // 데이터가 있는지 여부
    std::string name; // 데이터 이름

public:
    // 생성자
    DataBox(const std::string& boxName)
        : name(boxName), hasData(false), data(T{}) {
        std::cout << "DataBox<" << typeid(T).name() << "> '"
            << name << "' 생성됨" << std::endl;
    }

    // 데이터 저장
    void store(T value) {
        data = value;
        hasData = true;
        std::cout << name << "에 값 저장: " << value << std::endl;
    }

    // 데이터 가져오기
    T get() const {
        if (!hasData) {
            std::cout << "경고: " << name << "에 데이터가 없습니다!" << std::endl;
            return T{};  // 기본값 반환
        }
        return data;
    }

    // 데이터 존재 여부
    bool isEmpty() const {
        return !hasData;
    }

    // 데이터 초기화
    void clear() {
        data = T{};
        hasData = false;
        std::cout << name << " 초기화됨" << std::endl;
    }

    // 데이터 출력
    void display() const {
        std::cout << "=== " << name << " ===" << std::endl;
        if (hasData) {
            std::cout << "저장된 값: " << data << std::endl;
        }
        else {
            std::cout << "데이터 없음" << std::endl;
        }
        std::cout << "===============" << std::endl;
    }
};

// ========== 두 개의 값을 저장하는 Pair 클래스 템플릿 ==========
template<typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;

public:
    // 생성자
    Pair(T1 f, T2 s) : first(f), second(s) {}

    // Getter
    T1 getFirst() const { return first; }
    T2 getSecond() const { return second; }

    // Setter
    void setFirst(T1 f) { first = f; }
    void setSecond(T2 s) { second = s; }

    // 출력
    void display() const {
        std::cout << "(" << first << ", " << second << ")" << std::endl;
    }
};

// ========== 간단한 배열 래퍼 클래스 템플릿 ==========
template<typename T>
class SimpleArray {
private:
    T* data;
    int size;

public:
    // 생성자
    SimpleArray(int arraySize) : size(arraySize) {
        data = new T[size];
        std::cout << "SimpleArray<" << typeid(T).name()
            << "> 크기 " << size << " 생성됨" << std::endl;
    }

    // 소멸자
    ~SimpleArray() {
        delete[] data;
        std::cout << "SimpleArray 메모리 해제됨" << std::endl;
    }

    // 인덱스 접근
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            std::cout << "잘못된 인덱스: " << index << std::endl;
            return data[0];  // 에러 처리 (실제로는 예외 사용)
        }
        return data[index];
    }

    // 배열 크기
    int getSize() const { return size; }

    // 모든 요소 출력
    void displayAll() const {
        std::cout << "배열 내용: ";
        for (int i = 0; i < size; i++) {
            std::cout << data[i];
            if (i < size - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
};