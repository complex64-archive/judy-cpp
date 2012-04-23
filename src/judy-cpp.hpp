#ifndef JUDY_CPP_HPP
#define JUDY_CPP_HPP JUDY_CPP_HPP

#include <memory>
#include <iostream>


namespace judy
{

template <typename T,
    typename A = std::allocator<T> >
class hs
{
public:
    typedef T           value_type;
    typedef value_type  key_type;
    typedef A           allocator;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef std::size_t size_type;


public:
    inline bool
    insert(reference key, reference value)
    {
        return false;
    }
};

}

#endif
