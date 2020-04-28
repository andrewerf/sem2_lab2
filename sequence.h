#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP


#include <cstdlib>
#include <utility>


template<typename T>
class Sequence {
public:

	virtual T& get(size_t i) = 0;
	virtual T& getFirst() {return get(0);}
	virtual T& getLast() {return get(size()-1);}

	virtual const T& get(size_t i) const = 0;
	virtual const T& getFirst() const {return get(0);}
	virtual const T& getLast() const {return get(size()-1);}

	virtual size_t size() const noexcept = 0;

	virtual void insert(size_t i, const T &val) = 0;

	virtual void append(const T &val) = 0;
	virtual void prepend(const T &val) = 0;

	virtual T& operator[](size_t i) = 0;
	virtual const T& operator[](size_t i) const = 0;

	virtual Sequence<T>* operator[](std::pair<size_t, size_t> range) const = 0;
	virtual Sequence<T>* getSubsequence(size_t from, size_t to) const = 0;

	virtual Sequence<T>* concat(Sequence<T> *list) const = 0;
	virtual Sequence<T>* operator +(Sequence<T> *a) const = 0;
};


#endif // SEQUENCE_HPP
