#include <iostream>
#include <mutex>
#include <memory>
using namespace std;
class GlobalClass {
	int m_value;
	static GlobalClass *m_instance;
	//GlobalClass(int v = 0) :m_value(v){}
public:
	int get_value()	{
		return m_value;
	}

	void set_value(int v) {
		m_value = v;
	}

	static shared_ptr<GlobalClass> getInstance() {
		static std::weak_ptr<GlobalClass> instance;
		static std::mutex mutex;
		const::std::lock_guard<std::mutex> lock(mutex);
		if (const auto result = instance.lock()) return result;
		return (instance = std::make_shared<GlobalClass>()).lock();
	}
};

GlobalClass* GlobalClass::m_instance = nullptr;

int main() {
	GlobalClass::getInstance()->set_value(5);
	cout << GlobalClass::getInstance()->get_value() << "\n";
	GlobalClass::getInstance()->set_value(10);
	cout << GlobalClass::getInstance()->get_value() << "\n";
	return 0;
}
