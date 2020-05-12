#pragma once

template<class T, size_t SIZE>
class MyAllocator {
public:
	using value_type = T;

	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	using void_pointer = void*;
	using const_void_pointer = const void*;

	using size_type = size_t;

	template<class U>
	struct rebind
	{
		using other = MyAllocator<U, SIZE>;
	};

	MyAllocator() {
		size_ = SIZE + 1;
		count_ = 0;
		buff_ = reinterpret_cast<pointer>(::operator new(size_ * sizeof(T)));
	}
	~MyAllocator() = default;

	template<class U>
	MyAllocator(MyAllocator<U, SIZE>& other) {
		size_ = SIZE + 1;
		count_ = 0;
		buff_ = reinterpret_cast<pointer>(operator new(size_ * sizeof(T)));
	}

	pointer allocate(size_type numObjects) {
		if (size_ - numObjects < count_)
			throw;
		count_++;
		return (buff_ + (count_ - 1));
	}

	pointer allocate(size_type numObjects, const_void_pointer hint) {
		return allocate(numObjects);
	}

	void deallocate(pointer p, size_type numObjects) {
		--count_;
		if (!count_) {
			operator delete(p);
		}
	}

	size_t max_size() const {
		return size_;
	}

	template<class U, class... Args>
	void construct(U* p, Args&& ...args) {
		new(p) U(std::forward<Args>(args)...);
	}

	template<class U>
	void destroy(U* p) {
		p->~U();
	}

private:
	size_t size_;
	size_t count_;
	pointer buff_;
};