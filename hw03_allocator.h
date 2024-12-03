#pragma once
#include <new>

using elemsNumType = unsigned short;

template <class T, elemsNumType maxNum>
struct hw03_allocator 
{
    using value_type = T;

    T* mem_pool = nullptr;

    //T data[maxNum]; // If we only needed a fixed pool size, we could do it like this.

    hw03_allocator()
    {
        allocatedNum = 0;
    }

    ~hw03_allocator() = default;
 
    template <class U, elemsNumType maxNumU = maxNum> hw03_allocator(hw03_allocator <U, maxNum>& a) noexcept
    {
        allocatedNum = a.size();
        mem_pool = (T*)a.mem_pool;
    }
    
    T* allocate(std::size_t n)
    {
        if (n == 0)        
            return nullptr;

        if (allocatedNum + n > maxNum)
            throw std::bad_array_new_length();

        if (allocatedNum == 0)  // Memory has not yet been allocated.
        {            
            mem_pool = static_cast<T*>(malloc(maxNum * sizeof(T)));
            return mem_pool;
        }
            
        if (!mem_pool)
            throw std::bad_alloc();   // For case when at least one element was deallocated and, accordingly, all previously allocated memory was freed.

        allocatedNum += n;

        return static_cast<T*>(mem_pool + allocatedNum*sizeof(T));
    }

    void deallocate(T* p, std::size_t n)
    {
        // can we thrown exception here ?
        // if (n != maxSize)
        //    throw invalid_argument("In the current implementation, only all memory is freed."); 

        std::free(static_cast<void*>(mem_pool));
        mem_pool = nullptr;
    }

    elemsNumType max_size() const noexcept
    {
        return maxNum;
    }

    elemsNumType size() const noexcept
    {
        return allocatedNum;
    }

    template<typename U, elemsNumType maxNumU = maxNum>
    struct rebind
    {
        using other = hw03_allocator<U, maxNumU>;
    };

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type; //UB if std::false_type and a1 != a2;

 private:
     elemsNumType allocatedNum = 0;
};

template <class T, elemsNumType n, class U>
constexpr bool operator== (const hw03_allocator<T, n>& a1, const hw03_allocator<U, n>& a2) noexcept
{
    return a1.mem_pool == a2.mem_pool;
}

template <class T, elemsNumType n, class U>
constexpr bool operator!= (const hw03_allocator<T, n>& a1, const hw03_allocator<U, n>& a2) noexcept
{
    return a1.mem_pool != a2.mem_pool;
}
