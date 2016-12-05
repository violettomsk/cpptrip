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
	virtual void sayHello() = 0;
};

// Class Cat
class Cat : public Animal {
public:
	Cat() { name = "Cat"; }
	void sayHello() {
		cout << "Hello! I'm Cat\n";
	}
};

// class Dog
class Dog : public Animal {
public:
	Dog() { name = "Dog"; }
	void sayHello() {
		cout << "Hello! I'm a cute puppy!\n";
	}
};

class Mickey : public Animal {
public: 
	Mickey() { name = "Mickey"; } 
	void sayHello() {
		cout << "I'm not an animal. I'm a cartoon character\n";
	}
};


// Factory Class
class AnimalFactory {
public:
	unique_ptr<Animal> createAnimal(int type) {
		if (type == 1) {
			return std::move(make_unique<Cat>());
		}
		else {
			if (type == 2) {
				return std::move(make_unique<Dog>());
			} 
			else {
				if (type == 3) {
					return std::move(make_unique<Mickey>());
				}
				else {
					return nullptr;
				}
			}
		}
	}
};


int main() {
	AnimalFactory factory;
	unique_ptr<Animal> a = std::move(factory.createAnimal(1));
	a->sayHello();

	unique_ptr<Animal> b = std::move(factory.createAnimal(2));
	b->sayHello();

	unique_ptr<Animal> c = std::move(factory.createAnimal(3));
	c->sayHello();

	srand(time(NULL));
	std::vector<unique_ptr<Animal>> zoo;
	for (int i = 0; i < 5;i++) {
		zoo.push_back(std::move(factory.createAnimal(rand() % 3 + 1)));
	}
	for (int i = 0; i < 5; i++) {
		zoo[i]->sayHello();
	}
	return 0;
}