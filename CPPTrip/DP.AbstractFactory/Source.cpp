#include <vector>
#include <memory>
#include <iostream>
using namespace std;

class Widget {
public:
	virtual void draw() = 0;
};

class LinuxButton : public Widget {
public:
	void draw() { cout << "Linux button\n"; }
};

class WindowsButton : public Widget{
public:
	void draw() { cout << "Windows button\n"; }
};

class LinuxMenu : public Widget {
public:
	void draw() { cout << "Linux Menu\n"; }
};

class WindowsMenu : public Widget {
public:
	void draw() { cout << "Windows Menu\n"; }
};

class Factory {
public:
	virtual std::unique_ptr<Widget> createButton() = 0;
	virtual std::unique_ptr<Widget> createMenu() = 0;
};

class LinuxFactory : public Factory {
public:
	std::unique_ptr<Widget> createButton() {
		return move(make_unique<LinuxButton>());
	}
	std::unique_ptr<Widget> createMenu() {
		return std::move(make_unique<LinuxMenu>());
	}
};

class WindowsFactory : public Factory {
public:
	std::unique_ptr<Widget> createButton() {
	    return std::move(make_unique<WindowsButton>());
	}
	std::unique_ptr<Widget> createMenu() {
		return std::move(make_unique<WindowsMenu>());
	}
};

class Client {
private:
	std::unique_ptr<Factory> factory;
public:
	// constructor
	Client(std::unique_ptr<Factory> _fac) {
		factory = std::move(_fac);
	}

	void DrawWindowA() {
		std::vector<unique_ptr<Widget>> wgets;
		wgets.push_back(std::move(factory->createButton()));
		wgets.push_back(std::move(factory->createMenu()));
		wgets[0]->draw();
		wgets[1]->draw();
	}

	void DrawWindowB() {
		std::vector<unique_ptr<Widget>> wgets;
		wgets.push_back(std::move(factory->createButton()));
		wgets.push_back(std::move(factory->createMenu()));
		wgets[0]->draw();
		wgets[1]->draw();
	}

	void draw() {
		DrawWindowA();
		DrawWindowB();
	}	
};

int main() {
	
#ifdef LINUX
	Client client(std::move(std::make_unique<LinuxFactory>()));
#else 
	Client client(std::move(std::make_unique<WindowsFactory>()));
#endif
	client.draw();
return 0;
}



