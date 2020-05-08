#ifndef LIST_HPP
#define LIST_HPP


#include <stdexcept>


template<typename T>
class List {
public:
	List();

	template<typename V>
	List(size_t count, V&& val);

	template<typename TIter,
			 typename = typename std::enable_if<
										!std::is_same<
											typename std::remove_reference<T>::type,
											typename std::remove_reference<TIter>::type>::value,
										TIter>::type>
	List(TIter begin, TIter end);


	List(T *array, size_t count);
	List(const List<T> &list);
	List(List<T> &&list);


	List& operator= (const List<T> &list);
	List& operator= (List<T> &&list);

	bool operator== (const List<T> &list) const;
	bool operator!= (const List<T> &list) const {return !(list == *this);}

	T& getFirst() {return get(0);}
	const T& getFirst() const {return get(0);}

	T& getLast() {return get(_count-1);}
	const T& getLast() const {return get(_count-1);}

	T& get(size_t i);
	const T& get(size_t i) const;


	size_t size() const noexcept {return _count;}

	template<typename V>
	void set(size_t i, V&& val) {get(i) = val;}

	void erase(size_t i);
	void erase(size_t from, size_t to);

	template<typename V>
	void insert(size_t i, V&& val) {_check_range(i); _insert(i, std::forward<V>(val));}

	template<typename V>
	void append(V&& val) noexcept {_insert(_count, std::forward<V>(val));}

	template<typename V>
	void prepend(V&& val) noexcept {_insert(0, std::forward<V>(val));}

	void clear() {erase(0, size());}


	List<T> operator[] (std::pair<size_t, size_t> range);
	const List<T> operator[] (std::pair<size_t, size_t> range) const;

	template<typename TT>
	friend List<TT>* operator+ (List<TT> a, List<TT> b);

	~List();
private:
	struct _Node {
		_Node *next, *prev;
		T val;
	};

	void _check_range(size_t i);

	template<typename V>
	void _insert(size_t i, V&& val);

	_Node* _getPointer(size_t i);

	_Node *_pre_head, *_tail;
	size_t _count;
};



template<typename T>
List<T>::List():
	_pre_head(new _Node{nullptr, nullptr}),
	_tail(nullptr),
	_count(0)
{}

template<typename T>
template<typename V>
List<T>::List(size_t count, V&& val):
	List()
{
	for(size_t i = 0; i < count; ++i)
		_insert(i, std::forward<V>(val));
	_count = count;
}

template<typename T>
template<typename TIter,
		 typename>
List<T>::List(TIter begin, TIter end) :
	List()
{
	for(size_t i = 0; begin != end; ++begin, ++i){
		_insert(i, *begin);
	}
}

template<typename T>
List<T>::List(T *array, size_t count) :
	List()
{
	for(size_t i = 0; i < count; ++i)
		_insert(i, array[i]);
	_count = count;
}

template<typename T>
List<T>::List(const List<T> &list) :
	List()
{
	_Node *t = list._pre_head->next;
	for(size_t i = 0; i < list.size(); ++i, t = t->next)
		_insert(i, t->val);
}

template<typename T>
List<T>::List(List<T> &&list) :
	List()
{
	_pre_head = list._pre_head;
	_tail = list._tail;
	_count = list._count;

	list._count = 0;
	list._pre_head->next = nullptr;
	list._tail = nullptr;
}

template<typename T>
List<T>::~List()
{
	if(size() > 0)
		erase(0, size());
}


template<typename T>
List<T> &List<T>::operator=(const List<T> &list)
{
	clear();
	for(_Node *t = list._pre_head->next; t != nullptr; t = t->next){
		append(t->val);
	}
}

template<typename T>
List<T> &List<T>::operator=(List<T> &&list)
{
	clear();
	_pre_head->next = list._pre_head->next;
	_tail = list._tail;

	list._tail = 0;
	list._pre_head->next = nullptr;
	list._count = 0;
}

template<typename T>
bool List<T>::operator== (const List<T> &list) const
{
	bool ret = (size() == list.size());
	for(_Node *t1 = _pre_head->next, *t2 = list._pre_head->next;
		t1 != nullptr && t2 != nullptr && ret;
		t1 = t1->next, t2 = t2->next)
	{
		ret = (t1->val == t2->val);
	}

	return ret;
}


template<typename T>
T& List<T>::get(size_t i)
{
	_check_range(i);
	return _getPointer(i)->val;
}

template<typename T>
const T& List<T>::get(size_t i) const
{
	_check_range(i);
	return _getPointer(i)->val;
}

template<typename T>
void List<T>::erase(size_t i)
{
	_Node *t = _getPointer(i);
	t->prev->next = t->next;

	if(t != _tail)
		t->next->prev = t->prev;
	else
		_tail = t->prev;

	delete t;
	--_count;
}

template<typename T>
void List<T>::erase(size_t from, size_t to)
{
	for(size_t i = from; i < to; ++i)
		erase(from);
}

template<typename T>
const List<T> List<T>::operator[](std::pair<size_t, size_t> range) const
{
	_check_range(range.second);
	_check_range(range.first);

	List ret;
	ret._pre_head = _getPointer(range.first);
	ret._tail = _getPointer(range.second - 1);
	ret._count = range.second - range.first;

	return ret;
}

template<typename T>
List<T> List<T>::operator[](std::pair<size_t, size_t> range)
{
	_check_range(range.second);
	_check_range(range.first);

	List ret;
	_Node *t = _getPointer(range.first);

	for(size_t i = range.first; i < range.second; ++i){
		ret.append(t->val);
		t = t->next;
	}
	return ret;
}


template<typename T>
void List<T>::_check_range(size_t i)
{
	if(i > _count)
		throw std::out_of_range("List out of range!");
}


template<typename T>
template<typename V>
void List<T>::_insert(size_t i, V&& val)
{
	_Node *in = new _Node{nullptr, nullptr, val};
	_Node *t;

	if(i == 0)
		t = _pre_head;
	else
		t = _getPointer(i-1);

	if(t->next != nullptr)
		t->next->prev = in;
	in->next = t->next;
	in->prev = t;
	t->next = in;

	if(i == _count)
		_tail = in;
	++_count;
}


template<typename T>
typename List<T>::_Node* List<T>::_getPointer(size_t i)
{
	_Node *t;
	if(1/*i <= _count / 2*/){
		t = _pre_head->next;
		for(size_t j = 0; j < i; ++j, t = t->next){}
	}
// @TODO: implement starting from the end
//	else{
//		t = _tail;
//		for(size_t j = _count-1; j > i; --j, t = t->prev){}
//	}

	return t;
}



template<typename T>
List<T>* operator+ (List<T> a, List<T> b)
{
	List<T> *ret = new List<T>;
	typename List<T>::_Node *t;

	t = a._pre_head->next;
	while(t != nullptr){
		ret->append(t->val);
		t = t->next;
	}

	t = b._pre_head->next;
	while(t != nullptr){
		ret->append(t->val);
		t = t->next;
	}

	return ret;
}





#endif // LIST_HPP
