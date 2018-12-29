/*
lstack grows to ==>
empty: tail = head
tail(head)

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

*/
template <class T>
class Lstack
{
public:
    Lstack(int);
    ~Lstack();
    void push(T);
    bool  pop(T&);
	bool empty();
	bool full();
    int size();

private:
    void init(int);

private:
    int head;//the next position to be used
	int tail;//the first position which has beed used
    int max_size;
    T* arry;
};

template <class  T>  Lstack<T>::Lstack(int lstack_size) {
    init(lstack_size);
}

template <class T> Lstack<T>::~Lstack() {
    delete []arry;
}

template <class T>
bool Lstack<T>::full() {
	return (head - tail + max_size) % max_size == max_size - 1;
}

template <class T>
bool Lstack<T>::empty() {
	return head == tail;
}

template <class T> void Lstack<T>::push(T t) {
	if (full()) {
		tail = (tail + 1) % max_size;
	}
    arry[head] = t;
	head = (head +1) % max_size;
}

template <class T> bool Lstack<T>::pop(T& t) {
    if(empty())
    {
		return false;
    }
	head = (head - 1 ) % max_size;
    t = arry[head];
    return true;
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
    arry = new T[lstack_size];
}
