# makefile 1 

# 최종 실행 파일(app.out)은 main.o와 hello.o에 의존합니다.
#app.out: main.o hello.o
#	g++ -o app.out main.o hello.o

# main.o는 main.cpp와 hello.h에 의존합니다.
#main.o: main.cpp hello.h
#	g++ -c main.cpp

# hello.o는 hello.cpp와 hello.h에 의존합니다.
#hello.o: hello.cpp hello.h
#	g++ -c hello.cpp

# 빌드 결과물을 삭제하는 규칙
#clean:
#	rm -f *.o app.out

# makefile 2 - more advanced 

# Makefile 예제 (변수 활용)
CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = hello_app
SOURCES = main.cpp hello.cpp 
OBJECTS = $(SOURCES:.cpp=.o)

# 기본 타겟
all: $(TARGET)

# 링크 과정
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# 컴파일 과정 (확장자 규칙 .cpp -> .o)
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 청소
clean:
	rm -f $(OBJECTS) $(TARGET)
