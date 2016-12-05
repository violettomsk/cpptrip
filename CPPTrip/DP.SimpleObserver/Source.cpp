#include <iostream>
#include <vector>
#include <memory>

class Observer;

class Subject {
private:
	std::vector<std::shared_ptr<Observer>> views;
	int value;
public:
	void Register(std::shared_ptr<Observer> ob) {
		views.push_back(ob);
	}

	void SetValue(int val) {
		value = val;
		Notify();
	}

	int GetValue() {
		return value;
	}

	void Notify();
};

class Observer : public std::enable_shared_from_this<Observer> {
private:
	std::shared_ptr<Subject> model;
	int denom;
	std::vector<std::weak_ptr<Subject>> wps;
public:
	Observer(std::shared_ptr<Subject> &_model, int div) {
		wps.push_back(_model);
		model.reset(&_model);
		denom = div;
		model->Register(shared_from_this());
	}
	
	virtual void update() = 0;

	std::shared_ptr<Subject> getSubject(){
		return std::move(model);
	}

	int getDivisor() {
		return denom;
	}
};


void Subject::Notify() {
	for (auto i : views) {
		i->update();
	}
}

class DivObserver : public Observer {
public:
	DivObserver(std::shared_ptr<Subject> &mod, int div) : Observer(std::make_shared<Subject>(&mod), div){}
	void update() {
		int v = getSubject()->GetValue();
		int d = getDivisor();
		std::cout << v << " div " << d << " is " << v / d << "\n";
	}
};

class ModObserver : public Observer {
public:
	ModObserver(std::shared_ptr<Subject> mod, int div) : Observer(mod, div) {}
	void update() {
		int v = getSubject()->GetValue();
		int d = getDivisor();
		std::cout << v << " mod " << d << " is " << v % d << "\n";
	}
};																  


int main() {
	std::shared_ptr<Subject> sub(std::make_shared<Subject>());
	DivObserver divObser(sub, 4);
	DivObserver divObser2(sub, 6);
	ModObserver modObser(sub, 5);

	sub->SetValue(10);
}