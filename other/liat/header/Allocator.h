#pragma once
#include<memory>
#include<cstdlib>
#include<iostream>

namespace mystd {

	template<typename T>
	class MyAllocator {
	public:
		typedef T value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;

	public:
		template<typename U>
		struct rebind {
			typedef MyAllocator<U> other;
		};

	public:
		inline explicit MyAllocator() {}
		inline ~MyAllocator() {}
		inline explicit MyAllocator(MyAllocator const&) {}
		template<typename U>
		inline explicit MyAllocator(MyAllocator<U> const&) {}

		inline pointer address(reference r) { 
			return &r;
		}
		inline const_pointer address(const_reference r) {
			return &r; 
		}

		inline pointer allocate(size_type cnt,typename std::allocator<void>::const_pointer = 0) {
			pointer new_memory = reinterpret_cast<pointer>(operator new(cnt * sizeof(T)));
			return new_memory;
		}
		void* operator new(size_t size) {
			return malloc(size);
		}

		void operator delete(void* ptr) {
			free(ptr);
		}

		inline void deallocate(pointer p, size_type n) {
			operator delete (p);
		}

		inline void construct(pointer p, const T& t) {
			new (p) T(t);
		}
		inline void destroy(pointer p) {
			p->~T();
		}

		inline bool operator==(MyAllocator const&) { return true; }
		inline bool operator!=(MyAllocator const& a) { return !operator==(a); }
	}; 
} 