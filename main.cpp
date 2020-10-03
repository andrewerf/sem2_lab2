#include <iostream>
#include <vector>

#include "dynamic_array.hpp"
#include "array_sequence.hpp"
#include "queue.hpp"
#include "list.hpp"
#include "list_sequence.hpp"

using namespace std;


template <typename Cont>
std::ostream& operator<< (std::ostream &os, const Cont &a)
{
	for(size_t i = 0; i < a.size(); ++i){
		os << a[i] << " ";
	}
	return os;
}


int main()
{
//	Base b;
//	DynamicArray<Base> vec1(10, b);
//	vec1[3] = b;

//	std::vector<Base> svec(10,b);
//	svec.assign(3, b);

//	DynamicArray<Base> vec2(std::move(vec1));
//	ArraySequence<Base> seq(10);

	int a[] = {1, 2, 3, 4, 5, 6};

	DynamicArray<int> array(a, true);
	Sequence<int> *seq = new ListSequence<int>(a, 6);
	auto seq2 = seq->getSubsequence(1, 4);
	auto seq3 = seq->concat(seq2);

	cout << array;

//	Queue<int> q;

//	vector<Base> vs;
//	vs.push_back(Base());
//	DynamicArray<Base> bs(1, Base());
//	bs.push_back(vs[0]);
//	ArraySequence<Base> *as = new ArraySequence<Base>;
//	as->append(Base());
//	as->insert(3, Base());
//	as->insert(3, 6);

//	auto t = as->getSubsequence(3, 5);
//	print(*t);

//	Cont<Base> vec = Cont<Base>(std::forward<Base&&>(Base()));



//	Base b1;
//	Base b2 = b1;

	return 0;
}
