#include <memory>
#include <iostream>
using namespace std;
class A{
public:
	int data;
	A():data(0){}
	A(int v) :data(v){}
	void printData(){ cout << data << "\n"; }
	~A(){};
};

ostream& operator << (ostream& obj, const A a){
	obj << a.data;
	return obj;
}

shared_ptr<A> find_some_thing(){
	shared_ptr<A> B(make_shared<A>(10));
	return B;
}
shared_ptr<A> do_something_with(shared_ptr<A> p){
	shared_ptr<A> B(p);
	return B;
}

int main() {
	// create a shared pointer
	shared_ptr<A> p1(make_shared<A>(5));
	p1->printData();
	// p2 and p1 share ownership of the managed object
	shared_ptr<A> p2 = p1;
	p2->printData();
	
	shared_ptr<A> p3(new A(2));
	p3->printData();

	p1 = find_some_thing();
	p1->printData();
	
	cout << *p2 << "\n";

	// 
	p1.reset();
	p2 = nullptr;

	return 0;
}