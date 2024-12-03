#pragma once
#include <memory>

template <typename T, typename Allocator = std::allocator<T>>
class hw03_vector
{
  public:
	hw03_vector()
	{
		_elements = nullptr;
		_elementsNum = 0;
		_capacity = 0;
	}

	~hw03_vector()
	{
		clear();
		_alloc.deallocate(_elements, _capacity);
	}

	struct Iterator {
 	  public:		
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		Iterator(T* ptr) : _ptr(ptr) {}

		T& operator*() const { return *_ptr; }
		T* operator->() { return _ptr; }		
		
		Iterator& operator++() { ++_ptr; return *this; }

		friend bool operator==(const Iterator& a, const Iterator& b) { return a._ptr == b._ptr; };
		friend bool operator!=(const Iterator& a, const Iterator& b) { return a._ptr != b._ptr; };

	  private:
		T* _ptr;
	};

	T& operator[](elemsNumType ind) { return *(_elements + ind); }

	Iterator begin() { return Iterator(_elements); }
	Iterator end() { return Iterator(_elements + _elementsNum); }
	
	void push_back(const T& value)
	{
		if (_elementsNum == _capacity) 
		{
			reserve(_capacity == 0 ? 10 : _capacity * 2);
		}

		std::allocator_traits<Allocator>::construct(_alloc, _elements + _elementsNum, value);
		++_elementsNum;
	}

	void reserve(size_t newCapacity)
	{
		if (newCapacity <= _capacity) return;
		
		T* newElements = _alloc.allocate(newCapacity);
		for (size_t i = 0; i < _elementsNum; ++i)
		{
			std::allocator_traits<Allocator>::construct(_alloc, newElements + i, std::move(_elements[i]));
		}

		_alloc.deallocate(_elements, _capacity);
		_elements = newElements;
		_capacity = newCapacity;
	}

	void clear()
	{
		for (size_t i = 0; i < _elementsNum; ++i)
		{
			std::allocator_traits<Allocator>::destroy(_alloc, _elements + i);
		}
		_elementsNum = 0;
	}

	unsigned size()
	{
		return _elementsNum;
	}

  private:
	  Allocator _alloc;
	  T* _elements;
	  size_t _elementsNum;
	  size_t _capacity;
};
