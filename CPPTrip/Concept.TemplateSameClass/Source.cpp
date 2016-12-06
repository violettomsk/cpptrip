#include <iostream>
#include <type_traits>

// LESSON: 
// 1. Determine the same type of class/type
// 2. Order of template definition. 
// clearly if [TEMPLATE 2] is defined before [TEMPLATE 1], 
// the compiler will not understand and know the existence of [TEMPLATE1]

// TEMPLATE 1
template<typename T, typename D>
struct isSame {
	static const bool Same = false;
};


// TEMPLATE 2
template<typename T>
struct isSame<T, T> {
	static const bool Same = true;
};


template<typename A, typename B>
bool isSameClasS() {
	return isSame<A, B>::Same;
}

int main() {
	std::cout << std::noboolalpha << isSameClasS<int, int>();
	std::cout << std::noboolalpha << isSameClasS<int, int>();
	std::cout << std::noboolalpha << isSameClasS<int, int>();
	std::cout << std::noboolalpha << isSameClasS<int, int>();
	std::cout << std::boolalpha << true;
	return 0;
}