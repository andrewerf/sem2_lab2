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

	 ref get(size_t i);
	 ref getFirst() {return get(0);}
	 ref getLast() {return get(length());}

	 const_ref get(size_t i) const;
	 const_ref getFirst() const {return get(0);}
	 const_ref getLast() const {return get(length());}

	 size_t length() const noexcept;

	 void insert(size_t i, T&& val);
	 void insert(size_t i, const T &val);

	 void append(T&& val);
	 void append(const T &val);
	 void prepend(T&& val);
	 void prepend(const T &val);

	 Sequence<T>* operator[](std::pair<size_t, size_t> range);
	 Sequence<T>* getSubsequence(size_t from, size_t to);

	 Sequence<T>* concat(Sequence<T> *list);
	 Sequence<T>* operator +(Sequence<T> *a);
};


#endif // SEQUENCE_HPP
