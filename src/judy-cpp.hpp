#ifndef JUDY_CPP_HPP
#define JUDY_CPP_HPP JUDY_CPP_HPP

#include <memory>
#include <iostream>


namespace judy
{

template <typename K, typename V,
    typename A = std::allocator<V> >
class hs
{
public:
    typedef K  key_type;
    typedef V  value_type;
    typedef A  allocator;

    typedef key_type*    key_pointer;
    typedef value_type*  value_pointer;
    typedef key_type&    key_reference;
    typedef value_type&  value_reference;


public:
    bool
    insert(key_reference key, value_reference value)
    {
        return false;
    }


    bool
    remove(key_reference key)
    {
        return false;
    }


    value_type
    get(key_reference key)
    {
        throw 20;
    }
};

}

#endif
