class person {
public:
	// constructors
	person(void);
	explicit person(int);
	person(const person &ob);

	// operator 


	// destructor
	~person();

private:
	int data;
};

person::person(void) :data(0) {}

person::person(int a) : data(a) {}

person::person(const person &ob){
	data = ob.data;
}

person::~person() {}

int main() {

	person ob1;
	person ob();
	person ob2 = person(5);

	return 0;
}