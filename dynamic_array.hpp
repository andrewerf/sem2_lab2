#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP


#include <cstdlib>
#include <memory.h>
#include <stdexcept>
#include "allocator.hpp"


template<typename T>
class DynamicArray {
	typedef typename std::remove_reference<T>::type& ref;
	typedef const typename std::remove_reference<T>::type& const_ref;
public:
	DynamicArray() noexcept;
	DynamicArray(size_t count) noexcept;
	DynamicArray(size_t count, const T& val);

	template<typename TIter>
	DynamicArray(TIter begin, TIter end) noexcept;

	DynamicArray(T *array, size_t count) noexcept;
	DynamicArray(const DynamicArray<T> &array) noexcept;
	DynamicArray(DynamicArray<T> &&array) noexcept;


	ref get(size_t i) {_check_range(i); return _array[i];}
	const_ref get(size_t i) const {_check_range(i); return _array[i];}

	ref operator[](size_t i) noexcept {return _array[i];}
	const_ref operator[](size_t i) const noexcept {return _array[i];}

	size_t size() const noexcept {return _count;}


	void set(size_t i, T&& val);
	void set(size_t i, const T &val);
	void erase(size_t i) {erase(i, i+1);}
	void erase(size_t from, size_t to);

	void push_back(T&& val);
	void push_back(const T &val);
	void swap(size_t i, size_t j);

	void reserve(size_t new_capacity) noexcept;
	void resize(size_t new_size);
	void clear();

	~DynamicArray();
private:
	void _check_range(size_t i);

	template<typename TVal>
	void _assign(size_t i, TVal&& val);
	void _allocate(size_t new_capacity = 0) noexcept;

	T* _array;
	size_t _count;
	size_t _allocated;
};



template<typename T>
DynamicArray<T>::DynamicArray() noexcept :
	_count(0),
	_allocated(0)
{}

template<typename T>
DynamicArray<T>::DynamicArray(size_t count) noexcept :
	DynamicArray()
{
	_allocate(count);
}

template<typename T>
DynamicArray<T>::DynamicArray(size_t count, const T& val):
	DynamicArray(count)
{
	for(size_t i = 0; i < count; ++i)
		_assign(i, val);
	_count = count;
}

template<typename T>
template<typename TIter>
DynamicArray<T>::DynamicArray(TIter begin, TIter end) noexcept :
	DynamicArray(end - begin)
{
	for(size_t i = 0; begin != end; ++begin, ++i){
		_assign(i, *begin);
	}
}

template<typename T>
DynamicArray<T>::DynamicArray(T *array, size_t count) noexcept :
	_array(array),
	_count(count),
	_allocated(count)
{
	array = nullptr;
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &array) noexcept :
	DynamicArray(array._count)
{
	for(size_t i = 0; i < _count; ++i){
		_assign(i, array._array[i]);
	}
}

template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T> &&array) noexcept :
	_array(array._array),
	_count(array._count),
	_allocated(array._allocated)
{
	array._array = nullptr;
	array._count = 0;
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
void DynamicArray<T>::set(size_t i, T&& val)
{
	if(i > _count)
		throw std::out_of_range("DynamicArray out of range!");

	_assign(i, std::move(val));
}

template<typename T>
void DynamicArray<T>::set(size_t i, const T &val)
{
	if(i > _count)
		throw std::out_of_range("DynamicArray out of range!");

	_assign(i, val);
}

template<typename T>
void DynamicArray<T>::push_back(T&& val)
{
	if(_count == _allocated){
		_allocate();
	}

	_assign(_count++, std::move(val));
}

template<typename T>
void DynamicArray<T>::push_back(const T &val)
{
	if(_count == _allocated){
		_allocate();
	}

	_assign(_count++, val);
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
void DynamicArray<T>::reserve(size_t new_capacity) noexcept
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
	if(_count > 0)
		free(_array);
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
	_array[i] = T(std::forward<TVal>(val));
}

template<typename T>
void DynamicArray<T>::_allocate(size_t new_capacity) noexcept
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















