#ifndef JUDY_CPP_HPP
#define JUDY_CPP_HPP JUDY_CPP_HPP

#include <Judy.h>
// uint64_t
#include <inttypes.h>

namespace judy {

typedef Pvoid_t  hs_array_type;
typedef Pvoid_t  hs_value_type;
typedef PPvoid_t hs_value_pointer;
typedef uint8_t* hs_key_type;
typedef Word_t   hs_length_type;

template <typename K,
    typename V >
class hs
{
public:
    typedef K key_type;
    typedef key_type& key_reference;

    typedef V value_type;
    typedef value_type& value_reference;

    typedef uint64_t size_type;


public:
    hs()
        : size_(0),
          judy_array_((hs_array_type) 0)
    {}


    ~hs()
    {
        JudyHSFreeArray(&this->judy_array_, PJE0);
    }


    value_type
    insert(const key_reference key,
           const hs_length_type key_size,
           const value_reference value)
    {
        // Obtain value-pointer for the (new) index.
        hs_value_pointer target_ptr =
            JudyHSIns(&this->judy_array_,
                static_cast<void*>(key), key_size, PJE0);

        // Retrieve any old value to return later.
        value_type old_value = 0;
        if (target_ptr != 0)
            old_value = static_cast<value_type>(*target_ptr);

        // Write the value to the array.
        *target_ptr = value;

        // Increment the array's size if a value was actually inserted.
        if (old_value == 0) this->size_++;
        return old_value;
    }


    value_type
    remove(const key_reference key,
           const hs_length_type key_size)
    {
        // Look for an old value already present for the given key.
        value_type old_value = 0;
        try {
            old_value = this->get(key, key_size);
        }
        catch (bool) {}

        JudyHSDel(&this->judy_array_, static_cast<void*>(key), key_size, PJE0);

        // Decrease the array's size if an element was actually removed.
        if (old_value != 0) this->size_--;

        // Return the removed value or a null pointer.
        return old_value;
    }


    value_type
    get(const key_reference key,
        const hs_length_type key_size)
        const throw (bool)
    {
        hs_value_pointer value_p =
            JudyHSGet(this->judy_array_, static_cast<void*>(key), key_size);

        // Throw `false` in case the key was not present.
        if (value_p != NULL) {
            return static_cast<value_type>(*value_p);
        }
        else {
            throw false;
        }
    }


    inline size_type
    size() const
    {
        return this->size_;
    }


private:
    /// The current array's size, cached
    size_type size_;

    /// Reference to the JudyHS array we're wrapping
    hs_array_type judy_array_;
};

}

#endif
