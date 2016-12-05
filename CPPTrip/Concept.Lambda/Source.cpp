#include <iostream>
#include <vector>

using namespace std;

void ori_dost(int n) {
	cout << ++n << " ";
}

void for_each(vector<int> v, void(*func)(int a)) {
	for (auto i = v.begin(); i != v.end(); ++i) {
		func(*i);
	}
}

void main() {
	vector<int> v { 1, 2, 3, 4, 5 };
	for_each(v, ori_dost);
	std::cout << "\n";
	// using lambda
	for_each(v, [](int a) { cout << ++a << " "; });

	auto max = [](int a, int b) {
		return a > b ? a : b;
	};

	std::cout << "\n";
	cout << []		  // lambda definition
		    (int a, int b) 				   // variables
	        { return a > b ? a : b; } 				   // operations
	        (10, 20);												// invoke
	
	std::cout << "\n";
	int b=0;
	[&](int &a) {a = 100; }(b);
	cout << b;
}