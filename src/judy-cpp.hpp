#ifndef JUDY_CPP_HPP
#define JUDY_CPP_HPP JUDY_CPP_HPP

#include <Judy.h>

#include <boost/pool/poolfwd.hpp>
#include <boost/pool/pool_alloc.hpp>

namespace judy
{

template <typename K, typename V>
class hs
{
public:
    typedef K           key_type;
    typedef key_type&   key_reference;
    typedef V           value_type;
    typedef value_type& value_reference;

    // JudyHS's internal types.
    typedef Pvoid_t  hs_array_type;
    typedef Pvoid_t  hs_value_type;
    typedef PPvoid_t hs_value_pointer;
    typedef uint8_t* hs_key_type;
    typedef Word_t   hs_length_type;


public:
    hs()
        : size_(0),
          judy_array_((hs_array_type) 0)
    {}


    value_type
    insert(const key_reference key,
           const std::size_t key_size,
           const value_reference value)
    {
        // Obtain value-pointer for the (new) index.
        hs_value_pointer target_ptr =
            JudyHSIns(&(this->judy_array_),
                static_cast<void*>(key), key_size, PJE0);

        // Return the old value if present.
        value_type old_value = 0;
        if (target_ptr != 0) old_value = static_cast<value_type>(*target_ptr);

        *target_ptr = value;

        return old_value;
    }


    bool
    remove(const key_reference key,
           const std::size_t key_size)
    {
        // TODO - Implement!
        return false;
    }


    value_type
    get(const key_reference key,
        const std::size_t key_size)
        throw (bool)
    {
        hs_value_pointer value_p =
            JudyHSGet(this->judy_array_, static_cast<void*>(key), key_size);

        if (value_p != NULL) {
            return static_cast<value_type>(*value_p);
        }
        else {
            throw false;
        }
    }


private:
    /// The current array's size cached
    std::size_t size_;

    /// Reference to the JudyHS array we're wrapping
    hs_array_type judy_array_;
};

}

#endif
