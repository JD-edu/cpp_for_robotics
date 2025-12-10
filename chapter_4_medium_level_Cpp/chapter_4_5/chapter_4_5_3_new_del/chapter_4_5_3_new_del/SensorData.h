#include <iostream>

class SensorData {
public:
    SensorData(int size) : dataSize(size) {
        // 동적 메모리 할당
        data = new double[size];
        std::cout << "메모리 할당: " << size << "개의 double" << std::endl;

        // 초기화
        for (int i = 0; i < size; ++i) {
            data[i] = 0.0;
        }
    }

    ~SensorData() {
        // 소멸자에서 메모리 해제 (필수!)
        delete[] data;
        std::cout << "메모리 해제 완료" << std::endl;
    }

    void setData(int index, double value) {
        if (index >= 0 && index < dataSize) {
            data[index] = value;
        }
    }

    double getData(int index) const {
        if (index >= 0 && index < dataSize) {
            return data[index];
        }
        return 0.0;
    }

    int getSize() const { return dataSize; }

private:
    double* data;      // 동적 배열을 가리키는 포인터
    int dataSize;
};
