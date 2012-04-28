#ifndef JUDY_CPP_HPP
#define JUDY_CPP_HPP JUDY_CPP_HPP

#include <Judy.h>

#include <boost/pool/poolfwd.hpp>
#include <boost/pool/pool_alloc.hpp>

#include <memory>
#include <iostream>


namespace judy
{

template <
    typename K,
    typename V,
    typename A = boost::fast_pool_allocator<V> >
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
    /** TODO - Document. */
    hs()
        : size_(0),
          hs_array_((Pvoid_t) 0)
    {}


    /** TODO - Document. */
    ~hs()
    {
        // Force freeing the system memory.
        boost::singleton_pool<
            boost::pool_allocator_tag, sizeof(value_pointer)
        >::release_memory();
    }


    /** TODO - Document. */
    bool
    insert(key_reference key, value_reference value)
    {
        return false;
    }


    /** TODO - Document. */
    bool
    remove(key_reference key)
    {
        int status = 0;
        JHSD(status, hs_array_, reinterpret_cast<void*>(&key), sizeof(key));

        bool was_removed = (status == 1);
        if (was_removed) this->size_--;
        return was_removed;
    }


    /** TODO - Document. */
    value_type
    get(key_reference key)
    {
        throw 20;
    }


private:
    /** TODO - Document. */
    boost::fast_pool_allocator<value_type> allocator_;

    /** TODO - Document. */
    std::size_t size_;

    /** TODO - Document. */
    Pvoid_t hs_array_;
};

}

#endif
