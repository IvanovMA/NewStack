#include <iostream>
#include <new>  
#include <stdexcept>
#include <vector>
#include <memory>


class bitset
{
public:
	explicit
		bitset(size_t size) /*strong*/;

	bitset(bitset const & other) = delete;
	auto operator =(bitset const & other)->bitset & = delete;
	bitset(bitset && other) = delete;
	auto operator =(bitset && other)->bitset & = delete;


	auto set(size_t index) /*strong*/ -> void;
	auto reset(size_t index) /*strong*/ -> void;
	auto test(size_t index) /*strong*/ -> bool;
	auto counter() /*noexcept*/ -> size_t;
	auto size() /*noexcept*/ -> size_t;

private:
	std::unique_ptr<bool[]>  ptr_;
	size_t size_;
	size_t counter_;
};

auto bitset::size()-> size_t {
	return size_;
}
auto bitset::counter()-> size_t {
	return counter_;
}

bitset::bitset(size_t size) :
	ptr_(std::make_unique<bool[]>(size)),
	size_(size),counter_(0) {
	
}



auto bitset::reset(size_t index)->void {
	
	if (index <= size()) {
		if (test(index) != false) {
			ptr_[index] = false;
			--counter_;
		}
	}
	else {
		throw std::out_of_range("Error");
	}
}



auto bitset::set(size_t index)->void {
	
	
	if (index <= size()) {
		if (test(index) != true) {
			
			ptr_[index] = true;
			++counter_;
			std::cout << counter_ << " counter" << std::endl;
		}
	}
	else {
		throw std::out_of_range("Error");
	}


}


auto bitset::test(size_t index) ->bool{
	if (index <= size()) {
		return ptr_[index];
	}
	else {
		throw std::out_of_range("Error");
	}
}


template <typename T>
class allocator
{
public:
	explicit
		allocator(std::size_t size = 0) /*strong*/;
	allocator(allocator const & other) /*strong*/;
	auto operator =(allocator const & other)->allocator & = delete;
	~allocator();

	auto resize() /*strong*/ -> void;

	auto construct(T * ptr, T const & value) /*strong*/ -> void;
	auto destroy(T * ptr) /*noexcept*/ -> void;

	auto get() /*noexcept*/ -> T *;
	auto get() const /*noexcept*/ -> T const *;

	auto count() const /*noexcept*/ -> size_t;
	auto full() const /*noexcept*/ -> bool;
	auto empty() const /*noexcept*/ -> bool;
	auto swap(allocator & other) /*noexcept*/ -> void;
	auto refact()->void;
private:
	auto destroy(T * first, T * last) /*noexcept*/ -> void;
	

	size_t size_;
	T * ptr_;
	std::unique_ptr<bitset> map_;
};


template <typename T>
allocator<T>::allocator(size_t size) : ptr_((T*)(operator new(size*sizeof(T)))), size_(size), map_(std::make_unique<bitset>(size)) {};

template<typename T>
	allocator<T>::allocator(allocator const& other) :
	allocator<T>(other.size_){
	for (size_t i=0; i < size_; ++i)
		if (other.map_->test(i))
		construct(ptr_ + i, other.ptr_[i]);
}

template <typename T>
allocator<T>::~allocator() {

	operator delete(ptr_);
};

template <typename T>
auto allocator<T>::swap(allocator & other)->void {
	std::swap(ptr_, other.ptr_);
	std::swap(size_, other.size_);
	std::swap(map_, other.map_);
};

template <typename T>
auto allocator<T>::construct(T * ptr, T const & value)->void {
	if (ptr < ptr_ || ptr >= ptr_ + size_) {
		throw std::out_of_range("Error");
	}
	new(ptr) T(value);
	map_->set(ptr - ptr_);	
}

template <typename T>
auto allocator<T>::destroy(T * ptr)->void
{
	
	if (ptr < ptr_ || ptr >= ptr_ + size_) {
		throw std::out_of_range("Error");
	}


	ptr->~T();
	map_->reset(ptr - ptr_);
	
	
	
}


template <typename T>
auto allocator<T>::destroy(T * first, T * last)->void
{
	for (; first != last; ++first) {
		destroy(&*first);
	}
}

template<typename T>
auto allocator<T>::refact()->void
{
	allocator<T> buff(size_);
	size_t j=0;
	for (size_t i=0;i<size_; i++)
	{
		if(ptr_ != nullptr) 
		{
			buff.construct(buff.ptr_ + j, ptr_[i]);
			++j;
		}
	}
	this->swap(buff);
}

template<typename T>
auto allocator<T>::resize()-> void {
	allocator<T>::refact();
	size_t size = size_ * 2 + (size_ == 0);
	allocator<T> buff(size);
	for (size_t i = 0; i < size_; ++i) {
		buff.construct(buff.ptr_ + i, ptr_[i]);
	}
	this->swap(buff);
	size_ = size;
}

template<typename T>
auto allocator<T>::empty() const -> bool {
	return (map_->counter() == 0);
}

template<typename T>
auto allocator<T>::full() const -> bool {
	return (map_->counter() == size_);
}

template<typename T>
auto allocator<T>::get() -> T * {
	return ptr_;
}

template<typename T>
auto allocator<T>::get() const -> T const * {
	return ptr_;
}

template<typename T>
auto allocator<T>::count() const -> size_t {
	return map_->counter();
}


template <typename T>
class stack
{
public:
	explicit
		stack(size_t size = 0);
	auto operator =(stack const & other) /*strong*/ -> stack &;

	auto empty() const /*noexcept*/ -> bool;
	auto count() const /*noexcept*/ -> size_t;

	auto push(T const & value) /*strong*/ -> void;
	auto pop() /*strong*/ -> void;
	auto top() /*strong*/ -> T &;
	auto top() const /*strong*/ -> T const &;

private:
	allocator<T> allocate;
};

template<typename T>
auto stack<T>::empty() const->bool {
	return (allocate.count() == 0);
}


template <typename T>
stack<T>::stack(size_t size) : allocate(size) {};



template <typename T>
auto stack<T>::push(T const &val)->void {
	if (allocate.empty() == true || allocate.full() == true) {
		allocate.resize();
	}
	allocate.construct(allocate.get() + allocate.count(), val);
}



template <typename T>
auto stack<T>::operator=(const stack &tmp)->stack&  {
	if (this != &tmp) {
		for (size_t i = 0; i < tmp.count(); i++) 
			this->push(*(tmp.allocate.get() + i));
	}
	return *this;
}


template <typename T>
auto stack<T>::count() const->size_t {
	return allocate.count();
}

template <typename T>
auto stack<T>::pop()->void {
	if (allocate.count() == 0) throw std::logic_error("Empty!");
	allocate.destroy(allocate.get() + (this->count()-1));
}

template <typename T>
auto stack<T>::top() const->const T&{
	if (allocate.count() == 0) throw std::logic_error("Empty!");
return(*(allocate.get() + this->count() - 1));

}

template <typename T>
auto stack<T>::top()->T&{
	if (allocate.count() == 0) throw std::logic_error("Empty!");
return(*(allocate.get() + this->count() - 1));
}
