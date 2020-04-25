#ifndef ITERATOR_H
#define ITERATOR_H


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


#endif // ITERATOR_H
