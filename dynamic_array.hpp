#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP


#include <cstdlib>
#include <memory.h>
#include <stdexcept>
#include "allocator.hpp"

#include <iostream>


template<typename T>
class DynamicArray {
	typedef typename std::remove_reference<T>::type& ref;
	typedef const typename std::remove_reference<T>::type& const_ref;
public:
	DynamicArray();
	DynamicArray(size_t count);

	template<typename V>
	DynamicArray(size_t count, V&& val);

	template<typename TIter,
			 typename = typename std::enable_if<
										!std::is_same<
											typename std::remove_reference<T>::type,
											typename std::remove_reference<TIter>::type>::value,
										TIter>::type>
	DynamicArray(TIter begin, TIter end);

	DynamicArray(T *array, size_t count, bool wrapper = false);
	DynamicArray(const DynamicArray<T> &array);
	DynamicArray(DynamicArray<T> &&array);

	DynamicArray& operator= (const DynamicArray<T> &array);
	DynamicArray& operator= (DynamicArray<T> &&array);

	bool operator== (const DynamicArray<T> &array) const;
	bool operator!= (const DynamicArray<T> &array) const {return !(array == *this);}


	ref get(size_t i) {_check_range(i); return _array[i];}
	const_ref get(size_t i) const {_check_range(i); return _array[i];}

	ref operator[](size_t i) noexcept {return _array[i];}
	const_ref operator[](size_t i) const noexcept {return _array[i];}

	size_t size() const noexcept {return _count;}

	bool is_wrapper() const {return _is_wrapper;}


	template<typename V>
	void set(size_t i, V&& val);

	void erase(size_t i) {erase(i, i+1);}
	void erase(size_t from, size_t to);

	template<typename V>
	void push_back(V&& val);

	void swap(size_t i, size_t j);

	void reserve(size_t new_capacity);
	void resize(size_t new_size);
	void clear();

	~DynamicArray();
private:
	void _check_range(size_t i);

	template<typename TVal>
	void _assign(size_t i, TVal&& val);
	void _allocate(size_t new_capacity = 0);

	T* _array;
	size_t _count;
	size_t _allocated;
	bool _is_wrapper = false;
};



template<typename T>
DynamicArray<T>::DynamicArray() :
	_count(0),
	_allocated(0)
{}

template<typename T>
DynamicArray<T>::DynamicArray(size_t count) :
	DynamicArray()
{
	resize(count);
}

template<typename T>
template<typename V>
DynamicArray<T>::DynamicArray(size_t count, V&& val):
	DynamicArray(count)
{
	for(size_t i = 0; i < count; ++i)
		_assign(i, std::forward<V>(val));
}

template<typename T>
template<typename TIter,
		 typename>
DynamicArray<T>::DynamicArray(TIter begin, TIter end) :
	DynamicArray(end - begin)
{
	for(size_t i = 0; begin != end; ++begin, ++i){
		_assign(i, *begin);
	}
}

template<typename T>
DynamicArray<T>::DynamicArray(T *array, size_t count, bool wrapper) :
	_array(array),
	_count(count),
	_allocated(count),
	_is_wrapper(wrapper)
{
	array = nullptr;
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &array) :
	DynamicArray(array._count)
{
	for(size_t i = 0; i < _count; ++i){
		_assign(i, array._array[i]);
	}
}

template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T> &&array) :
	_array(array._array),
	_count(array._count),
	_allocated(array._allocated),
	_is_wrapper(array._is_wrapper)
{
	array._array = nullptr;
	array._count = 0;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T> &array)
{
	clear();
	for(size_t i = 0; i < array.size(); ++i){
		_assign(i, array[i]);
	}
	_count = array.size();
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T> &&array)
{
	clear();
	for(size_t i = 0; i < array.size(); ++i){
		_assign(i, std::move(array[i]));
	}
	array._allocated = 0;
	_count = array.size();
	_is_wrapper = array._is_wrapper;
}

template<typename T>
bool DynamicArray<T>::operator== (const DynamicArray<T> &array) const
{
	bool ret = (array.size() == size());
	for(size_t i = 0; i < array.size() && ret; ++i)
		ret = (array[i] == _array[i]);
	return ret;
}


template<typename T>
void DynamicArray<T>::erase(size_t from, size_t to)
{
	size_t i;

	for(i = to; i < _count; ++i){
		_assign(from + i - to, std::move(_array[i]));
	}

	_count -= to - from;
}


template<typename T>
template<typename V>
void DynamicArray<T>::set(size_t i, V&& val)
{
	if(i > _count)
		throw std::out_of_range("DynamicArray out of range!");

	_assign(i, std::forward<V>(val));
}


template<typename T>
template<typename V>
void DynamicArray<T>::push_back(V&& val)
{
	if(_count == _allocated){
		_allocate();
	}

	_assign(_count++, std::forward<V>(val));
}


template<typename T>
void DynamicArray<T>::swap(size_t i, size_t j)
{
	_check_range(i);
	_check_range(j);

	auto t = std::move(_array[i]);
	_assign(i, std::move(_array[j]));
	_assign(j, std::move(t));
}


template<typename T>
void DynamicArray<T>::reserve(size_t new_capacity)
{
	if(new_capacity > _allocated){
		_allocate(new_capacity);
	}
}

template<typename T>
void DynamicArray<T>::resize(size_t new_size)
{
	if(new_size > _count){
		reserve(new_size);
	}
	else{
		erase(new_size, _count);
	}

	_count = new_size;
}

template<typename T>
void DynamicArray<T>::clear()
{
	erase(0, _count);
}

template<typename T>
DynamicArray<T>::~DynamicArray()
{
	if(_allocated > 0 && _array != nullptr && !_is_wrapper){
		delete[] _array;
		_array = nullptr;
	}
	_count = 0;
}

template<typename T>
void DynamicArray<T>::_check_range(size_t i)
{
	if(i > _count)
		throw std::out_of_range("DynamicArray out of range!");
}

template<typename T>
template<typename TVal>
void DynamicArray<T>::_assign(size_t i, TVal&& val)
{
	new(_array + i) T(std::forward<TVal>(val));
}

template<typename T>
void DynamicArray<T>::_allocate(size_t new_capacity)
{
	if(_allocated == 0){
		_array = (T*)malloc(10 * sizeof(T));
		_allocated = 10;
	}
	else{
		if(new_capacity == 0){
			//@TODO: implement different allocation policies
			new_capacity = _allocated*2;
		}
		_array = (T*)realloc(_array, new_capacity);
		_allocated = new_capacity;
	}
}

#endif // DYNAMIC_ARRAY_HPP















