#include <iostream>
#include <vector>

#include "dynamic_array.hpp"
#include "array_sequence.hpp"
using namespace std;


class Base{
public:
	Base()
	{
		cout << "Base created\n";
	}

	Base(int t) :
		Base()
	{
		_t = t;
	}

	Base(const Base&){
		cout << "Base const-copied\n";
	}
	Base(Base&){
		cout << "Base moved\n";
	}
//	Base(Base&&){
//		cout << "Base rvalue-copied\n";
//	}


	int _t = 10;
};

class nBase{
public:
	nBase(int k){

	}
};

template <typename T>
class Cont{
public:
	Cont(T &&val){
		_val = val;
	}

private:
	T _val;
};


int main()
{
	Base b;
//	DynamicArray<Base> vec1(10, b);
//	vec1[3] = b;

//	std::vector<Base> svec(10,b);
//	svec.assign(3, b);

//	DynamicArray<Base> vec2(std::move(vec1));
//	ArraySequence<Base> seq(10);

	ArraySequence<int> as(5, 10);
	as.insert(3, 5);

	for(size_t i = 0; i < as.length(); ++i){
		std::cout << as.get(i) << ' ';
	}

//	Cont<Base> vec = Cont<Base>(std::forward<Base&&>(Base()));



//	Base b1;
//	Base b2 = b1;

	return 0;
}
