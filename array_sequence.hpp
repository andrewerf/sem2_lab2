#ifndef ARRAY_SEQUENCE_HPP
#define ARRAY_SEQUENCE_HPP


#include "sequence.h"
#include "dynamic_array.hpp"


template <typename T>
class ArraySequence : public Sequence<T> {
public:
	ArraySequence() : _array(new DynamicArray<T>) {}

	template <typename ...Args>
	ArraySequence(Args&&... args) : _array(new DynamicArray<T>(std::forward<Args>(args)...)) {}

	ArraySequence(const ArraySequence<T> &array) noexcept;
	ArraySequence(ArraySequence<T> &&array) noexcept;

	T& get(size_t i) {return _array->get(i);}
	const T& get(size_t i) const {return _array->get(i);}

	size_t size() const noexcept {return _array->size();}

	void insert(size_t i, const T &val) {_insert(i, val);}

	void append(const T &val) {_array->push_back(val);}
	void prepend(const T &val) {_insert(0, val);}

	T& operator[](size_t i) {return (*_array)[i];}
	const T& operator[](size_t i) const {return (*_array)[i];}

	Sequence<T>* operator[](std::pair<size_t, size_t> range) const {return getSubsequence(range.first, range.second);}
	Sequence<T>* getSubsequence(size_t from, size_t to) const;

	Sequence<T>* concat(Sequence<T> *list) const;
	Sequence<T>* operator +(Sequence<T> *a) const {return concat(a);}

private:
	template<typename TVal>
	void _insert(size_t i, TVal&& val);

	DynamicArray<T> *_array;
};



template<typename T>
ArraySequence<T>::ArraySequence(const ArraySequence<T> &array) noexcept :
	_array(new DynamicArray<T>(array._array))
{}

template<typename T>
ArraySequence<T>::ArraySequence(ArraySequence<T>&& array) noexcept :
	_array(new DynamicArray<T>(std::move(array._array)))
{}

template<typename T>
Sequence<T> *ArraySequence<T>::getSubsequence(size_t from, size_t to) const
{
	return new ArraySequence<T>(&_array->get(from), &_array->get(to));
}

template<typename T>
Sequence<T> *ArraySequence<T>::concat(Sequence<T> *list) const
{
	size_t n = _array->size() + list->size();
	auto res = new ArraySequence<T>();
	res->_array->reserve(n);
	for(size_t i = 0; i < _array->size(); ++i){
		res->append(_array->get(i));
	}
	for(size_t i = 0; i < list->size(); ++i){
		res->append(list->get(i));
	}

	return res;
}

template<typename T>
template<typename TVal>
void ArraySequence<T>::_insert(size_t i, TVal &&val)
{
	_array->resize(_array->size() + 1);
	for(size_t j = _array->size() - 1; j > i; --j)
		_array->set(j, std::move(_array->get(j-1)));
	_array->set(i, std::forward<TVal>(val));
}

#endif // ARRAY_SEQUENCE_HPP





























