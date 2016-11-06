#include <iostream>
#include <stdexcept>
#include <algorithm>

template<typename T>
class stack
{
public:
    stack(); 
    ~stack(); 
    stack(const stack&); 
    size_t count() const;
    void push(T const&); 
    T pop();
    stack& operator= (stack const & right);
private:
    T * array_;
    size_t array_size_;
    size_t count_;
	void swap(stack & right);
};


template <typename T>
stack<T>::stack() : array_(nullptr), array_size_(0), count_(0){};

template <typename T>
stack<T>::stack(const stack& x) : array_size_(x.array_size_), count_(x.count_)
{
	array_size_ = x.array_size_;
	T * buff = new T[x.array_size];
	count_ = x.count;
	for (int i = 0; i < count_; i++) 
	{
		buff[i] = array_[i];
	}
};

template <typename T>
stack<T>::~stack() 
{
	delete[] array_;
}

template <typename T>
size_t stack<T>::count() const 
{
	return count_;
}

template<typename T>
void stack<T>::push(T const &item) {
	if (count_ == array_size_) {
		count_++;
		size_t size = array_size_ * 2 ;
		T * buff = new T[size];
		for (int i = 0; i < count_; i++) {
			buff[i] = array_[i];
		}
		delete[] array_;
		array_ = buff;
		array_size_ = size;
		array_[count_ - 1] = item;
	}
}

template<typename T>
void stack<T>::swap(stack & right)
{
	array_size_ = right.array_size_;
	count_ = right.count_;
	T * buff = new T[array_size_];
	std::swap(buff, array_);
	std::swap(buff, right.array_);
	std::swap(buff, array_);
}

template<typename T>
stack& stack<T>::operator=(stack const & right)
{
	if (this != &right) {
		(stack(right)).swap(*this);
	}
	return *this;
}
template <typename T>
T stack<T>::pop()
{
    if ( count_ == 0 ) {
        throw std::logic_error("stack is empty");
    }
    return array_[count_--];
}
