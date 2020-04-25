#ifndef ITERATOR_HPP
#define ITERATOR_HPP


namespace astd {

template <class TVal>
class Iterator {
public:
	virtual TVal operator*();

	virtual bool operator==(const Iterator<TVal> &it) noexcept;
	virtual bool operator!=(const Iterator<TVal> &it) noexcept;
};

template <class TVal>
class ForwardIterator : public Iterator<TVal> {
public:
	virtual Iterator<TVal>& operator++();
	virtual Iterator<TVal> operator++(int);
};


}


#endif // ITERATOR_HPP
