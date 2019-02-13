/*
lstack grows to ==>
empty: tail = head
tail(head)

head: the position for the next element.
tail: the position for the earliest element.

normal:  
tail....................... head
data1, data2, data3, dataN, .... dataMax

(head - tail + N) % N== N-1
full-case1:
tail....................... ... head
data1, data2, data3, dataN, ... dataMax


full-case2:
head   tail....................... ...
data1, data2, data3, dataN, ... dataMax

put:when we put new ele into the stack, we should delete the earliest ele first.
pop: f
*/
#ifndef __LSTACK_H__
#define __LSTACK_H__
template <class T>
class Lstack
{
public:
    Lstack(int);
    ~Lstack();
    void push(T &);
    void pop();
    T& top();
	bool empty();
    int size();

private:
    void init(int);
	bool full();

private:
    int head;//the next position to be used
	int tail;//the first position which has beed used
    int max_size;
    T* data_;
};

template <class  T>  Lstack<T>::Lstack(int lstack_size) {
    init(lstack_size);
}

template <class T> Lstack<T>::~Lstack() {
    delete []data_;
}

template <class T>
bool Lstack<T>::full() {
	return ((head - tail + max_size) % max_size ) == (max_size - 1);
}

template <class T>
bool Lstack<T>::empty() {
	return head == tail;
}

template <class T> void Lstack<T>::push(T &t) {
	if (full()) {
		tail = (tail + 1) % max_size;
	}
    data_[head] = t;
	head = (head +1) % max_size;
}

template <class T> T& Lstack<T>::top() {
    int index = (head -1 + max_size) % max_size;
    return data_[index];
}

template <class T> void Lstack<T>::pop() {
    if(!empty())
    {
	    head = (head - 1 + max_size) % max_size;
    }
}

template <class T> int Lstack<T>::size() {
    return (head - tail + max_size )%max_size;
}

template <class  T>  void Lstack<T>::init(int lstack_size) {
    if(lstack_size <= 0)
    {
        return;
    }
    head = 0;
	tail = 0;
    max_size = lstack_size;
    data_ = new T[lstack_size];
}
#endif
