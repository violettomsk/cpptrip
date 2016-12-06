#include <iostream>

// Lesson: 
// stack unwinding when throw is called 
// then right catch block will be accessed (depend on what is thrown)
// throw in destructor caused crash
class A {
public:
	A() {}
	~A() {
		//throw 42;
		std::cout << "destructor" << std::endl;
	}
};

int main(int argc, const char * argv[]) {
	try {
		A a;
		throw 32;
	}
	catch (int a) {
		std::cout << a;
	}
}
