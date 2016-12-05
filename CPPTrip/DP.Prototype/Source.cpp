//#include <iostream>
//#include <memory>
//#include <ctime>
//#include <string>
//#include <random>
//#include <vector>
//
//using namespace std;
//
//// animal interface
//
//class Animal {
//public:
//	string name;
//	virtual Animal* clone() = 0;
//	virtual void sayHello() = 0;
//};
//
//// Class Cat
//class Cat : public Animal {
//public:
//	Cat() { name = "Cat"; }
//	void sayHello() {
//		cout << "Hello! I'm Cat\n";
//	}
//
//	Animal* clone() {
//		return new Cat;
//	}
//};
//
//// class Dog
//class Dog : public Animal {
//public:
//	Dog() { name = "Dog"; }
//	
//	Animal* clone() {
//		return new Dog;
//	}
//
//	void sayHello() {
//		cout << "Hello! I'm a cute puppy!\n";
//	}
//};
//
//class Mickey : public Animal {
//public:
//	Mickey() { name = "Mickey"; }
//
//	Animal* clone() {
//		return new Mickey;
//	}
//
//	void sayHello() {
//		cout << "I'm not an animal. I'm a cartoon character\n";
//	}
//};
//
//
//// Factory Class
//class AnimalFactory {
//public:
//	static Animal* createAnimal(int type);
//private:
//	static Animal* s_prototypes[4];
//};
//
//Animal* AnimalFactory::s_prototypes[] = { 0, new Cat, new Dog, new Mickey };
//Animal* AnimalFactory::createAnimal(int type) {
//	return s_prototypes[type]->clone();
//}
//
//int main() {
//
//	Animal *ani1 = AnimalFactory::createAnimal(1);
//	Animal *ani2 = AnimalFactory::createAnimal(2);
//	Animal *ani3 = AnimalFactory::createAnimal(3);
//
//	ani1->sayHello();
//	ani2->sayHello();
//	ani3->sayHello();
//	return 0;
//}

#include <iostream>
#include <memory>
#include <ctime>
#include <string>
#include <random>
#include <vector>

using namespace std;

// animal interface

class Animal {
public:
	string name;
	virtual unique_ptr<Animal> clone() = 0;
	virtual void sayHello() = 0;
};

// Class Cat
class Cat : public Animal {
public:
	Cat() { name = "Cat"; }
	void sayHello() {
		cout << "Hello! I'm Cat\n";
	}

	unique_ptr<Animal> clone() {
		return std::move(make_unique<Cat>());
	}
};

// class Dog
class Dog : public Animal {
public:
	Dog() { name = "Dog"; }

	unique_ptr<Animal> clone() {
		return std::move(make_unique<Dog>());
	}

	void sayHello() {
		cout << "Hello! I'm a cute puppy!\n";
	}
};

class Mickey : public Animal {
public:
	Mickey() { name = "Mickey"; }

	std::unique_ptr<Animal> clone() {
		return std::move(std::make_unique<Mickey>());
	}

	void sayHello() {
		cout << "I'm not an animal. I'm a cartoon character\n";
	}
};

// Factory Class
class AnimalFactory {
public:
	static unique_ptr<Animal> createAnimal(int type);
private:
	static unique_ptr<Animal> s_prototypes[4];
};

unique_ptr<Animal> AnimalFactory::s_prototypes[] = {
	0,
	std::move(make_unique<Cat>()),
	std::move(make_unique<Dog>()),
	std::move(make_unique<Mickey>())};

unique_ptr<Animal> AnimalFactory::createAnimal(int type) {
	return std::move(s_prototypes[type]->clone());
}

int main() {

	unique_ptr<Animal> ani1 = AnimalFactory::createAnimal(1);
	unique_ptr<Animal> ani2 = AnimalFactory::createAnimal(2);
	unique_ptr<Animal> ani3 = AnimalFactory::createAnimal(3);

	ani1->sayHello();
	ani2->sayHello();
	ani3->sayHello();
	return 0;
}