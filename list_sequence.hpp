#ifndef LIST_SEQUENCE_HPP
#define LIST_SEQUENCE_HPP


#include "sequence.h"
#include "list.hpp"


template<typename T>
class ListSequence : public Sequence<T> {
public:
	ListSequence() : _list(new List<T>) {}

	template <typename ...Args>
	ListSequence(Args&&... args) : _list(new List<T>(std::forward<Args>(args)...)) {}

	ListSequence(const ListSequence<T> &list) noexcept : _list(new List<T>(list._list)) {}
	ListSequence(ListSequence<T> &&list) noexcept : _list(new List<T>(std::move(list._list))) {}

	T& get(size_t i) {return _list->get(i);}
	const T& get(size_t i) const {return _list->get(i);}

	size_t size() const noexcept {return _list->size();}

	void insert(size_t i, const T &val) {_list->insert(i, val);}

	void append(const T &val) {_list->append(val);}
	void prepend(const T &val) {_list->prepend(val);}

	void erase(size_t i) {_list->erase(i);}
	void erase(size_t from, size_t to) {_list->erase(from, to);}

	T& operator[](size_t i) {return get(i);}
	const T& operator[](size_t i) const {return get(i);}

	Sequence<T>* operator[](std::pair<size_t, size_t> range) const {return getSubsequence(range.first, range.second);}
	Sequence<T>* getSubsequence(size_t from, size_t to) const;

	Sequence<T>* concat(Sequence<T> *seq) const;
	Sequence<T>* operator +(Sequence<T> *a) const {return concat(a);}

private:
	List<T> *_list;
};


template<typename T>
Sequence<T>* ListSequence<T>::getSubsequence(size_t from, size_t to) const
{
	List<T> *subseq = new List<T>((*_list)[{from, to}]);
	ListSequence<T> *ret = new ListSequence<T>;
	ret->_list = subseq;
}

template<typename T>
Sequence<T>* ListSequence<T>::concat(Sequence<T> *seq) const
{
	ListSequence<T> *ret = new ListSequence;
	ListSequence<T> *list = dynamic_cast<ListSequence<T>*>(seq);
	if(list != nullptr){
		ret->_list = *list->_list + *_list;
	}
	else{
		List<T> t;
		for(size_t i = 0; i < seq->size(); ++i)
			t.append(seq->get(i));

		ret->_list = t + *_list;
	}

	return ret;
}














#endif // LIST_SEQUENCE_HPP
