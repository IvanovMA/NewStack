#include <iostream>
#include <stdexcept>

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
};


template <typename T>
stack<T>::stack() : array_(nullptr), array_size_(0), count_(0){};

template <typename T>
stack<T>::stack(const stack& x) : array_size_(x.array_size_), count_(x.count_), array_ (copy_mas(x.array_, x.count_, x.array_size_)){};

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
		size_t size = array_size_ * 2 + (aray_size == 0);
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
stack<T>& stack<T>::operator=(const stack& b){
	if (this != &b){
		T *p = array_;
		array_ = std::copy(b.array_, b.count_, b.array_size_);
		count_ = b.count_;
		array_size_ = b.array_size_;
        delete[] p;
	}
	return *this;
}
template <typename T>
T stack<T>::pop()
{
    if ( count_ == 0 ) {
        throw_is_empty();
    }
    return array_[count_--];
}
