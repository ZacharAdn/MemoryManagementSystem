//
// Created by zahar on 04/01/17.
//

#ifndef CPPEX2_MYALLOCATOR_H
#define CPPEX2_MYALLOCATOR_H

#include<memory>
#include<cstdlib>
#include<iostream>
#include <limits>

//namespace mystd {

    template<typename T>
    class MyAllocator{
    public :
        //    typedefs

        typedef T value_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

    public :
        //    convert an allocator<T> to allocator<U>

        template<typename U>
        struct rebind {
            typedef MyAllocator<U> other;
        };

    public :
        inline explicit MyAllocator() {}
        inline ~MyAllocator() {}
        inline explicit MyAllocator(MyAllocator const&) {}
        template<typename U>
        inline explicit MyAllocator(MyAllocator<U> const&) {}

        //    address

        inline pointer address(reference r) { return &r; }
        inline const_pointer address(const_reference r) { return &r; }

        //    memory allocation

        inline pointer allocate(size_type cnt,
                                typename std::allocator<void>::const_pointer = 0) {
            std::cout<<"Trying to allocate "<<cnt<<" objects in memory"<<std::endl;
            pointer new_memory = reinterpret_cast<pointer>(malloc(cnt * sizeof (T)));
            std::cout<<"Allocated "<<cnt<<" objects in memory at location:"<<new_memory<<std::endl;
            return new_memory;
        }
        inline void deallocate(pointer p, size_type n) {
            free(p);
            std::cout<<"Deleted "<<n<<" objects from memory"<<std::endl;
        }
        //    size
        inline size_type max_size() const {
            return std::numeric_limits<size_type>::max() / sizeof(T);
        }

        //    construction/destruction

        inline void construct(pointer p, const T& t) {
            std::cout<<"Constructing at memory location:" <<p<<std::endl;
            new(p) T(t);
        }
        inline void destroy(pointer p) {
            std::cout<<"Destroying object at memory location:" <<p<<std::endl;
            p->~T();
        }

        inline bool operator==(MyAllocator const&) { return true; }
        inline bool operator!=(MyAllocator const& a) { return !operator==(a); }
    };    //    end of class MyAllocator
//} // end of namespace mystd



//};


#endif //CPPEX2_MYALLOCATOR_H
