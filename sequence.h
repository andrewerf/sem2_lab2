#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP


#include <cstdlib>
#include <utility>


template<typename T>
class Sequence {
protected:
	typedef typename std::remove_reference<T>::type& ref;
	typedef const typename std::remove_reference<T>::type& const_ref;
public:

	virtual ref get(size_t i) = 0;
	virtual ref getFirst() {return get(0);}
	virtual ref getLast() {return get(size()-1);}

	virtual const_ref get(size_t i) const = 0;
	virtual const_ref getFirst() const {return get(0);}
	virtual const_ref getLast() const {return get(size()-1);}

	virtual size_t size() const noexcept = 0;

	virtual void insert(size_t i, T&& val) = 0;
	virtual void insert(size_t i, const T &val) = 0;

	virtual void append(T&& val) = 0;
	virtual void append(const T &val) = 0;
	virtual void prepend(T&& val) = 0;
	virtual void prepend(const T &val) = 0;

	virtual ref operator[](size_t i) = 0;
	virtual const_ref operator[](size_t i) const = 0;

	virtual Sequence<T>* operator[](std::pair<size_t, size_t> range) const = 0;
	virtual Sequence<T>* getSubsequence(size_t from, size_t to) const = 0;

	virtual Sequence<T>* concat(Sequence<T> *list) const = 0;
	virtual Sequence<T>* operator +(Sequence<T> *a) const = 0;
};


#endif // SEQUENCE_HPP
