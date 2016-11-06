
#include <stdlib.h>
#include <iostream>
using namespace std;
template <typename T>
class stack
{
public:
	stack();
	~stack();
	size_t count() const;
	auto push(T const &) -> void;
	T pop();
	auto operator=(stack const & right)->stack &;
private:
	T * array_;
	size_t array_size_;
	size_t count_;
	auto swap(stack & right) -> void;
};


template <typename T>
size_t stack<T>::count() const
{
	return count_;
}
template <typename T>
stack<T>::stack()
{
	array_size_ = 0;
	array_ = new T[array_size_];
	count_ = 0;
}

template <typename T>
stack<T>::~stack()
{
	delete[] array_;
}

template<typename T>
void stack<T>::push(T const &item) {
	if (count_ == array_size_) {
		count_++;
		size_t size = array_size_ * 2 + (array_size_ == 0);
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
T stack<T>::pop() {
	if (count_ == 0) {
		throw std::logic_error("Stack is empty!");
	}
	return array_[--count_];
}
template<typename T>
auto stack<T>::swap(stack & right) -> void {
	array_size_ = right.array_size_;
	count_ = right.count_;
	T * buff = new T[array_size_];
	std::swap(buff, array_);
	std::swap(buff, right.array_);
	std::swap(buff, array_);
}

template<typename T>
auto stack<T>::operator=(stack const & right) -> stack & {
	if (this != &right) {
		(stack(right)).swap(*this);
	}
	return *this;
}

