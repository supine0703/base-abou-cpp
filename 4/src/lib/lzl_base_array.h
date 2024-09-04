#ifndef LZL_BASE_ARRAY_H
#define LZL_BASE_ARRAY_H

#include "lzl_base_cap.h"
#include "lzl_limits.h"
#include "lzl_relops.h"

#include <utility>

namespace lzl::base
{

template <typename T, typename SIZE_T = size_t>
class _array : public _cap<SIZE_T>, public _max_size_interface<T, SIZE_T>
{
public:
    using base_type = _cap<SIZE_T>;
    using typename base_type::size_type;
    using value_type = T;

    virtual ~_array()
    {
        if (m_data != nullptr)
        {
            delete[] m_data;
            m_data = nullptr;
        }
    }

    // Assign data does not change the capacity
    void assign(const _array& other)
    {
        if (this->m_cap >= other.m_size)
        {
            this->m_size = other.m_size;
            other.copy_to(this->m_data);
        }
        else
        {
            this->m_size = this->m_cap;
            other.copy_to(this->m_data, this->m_cap);
        }
        after_reset();
    }

    void clear()
    {
        this->m_size = 0;
        after_clear();
    }

    void shrink_to_fit()
    {
        if (this->m_cap > this->m_size)
        {
            auto new_d = new value_type[this->m_size];
            copy_to(new_d);
            delete[] m_data;
            m_data = new_d;
            this->m_cap = this->m_size;
        }
        after_reset();
    }

    void reserve(size_type new_cap)
    {
        if (this->m_cap < new_cap)
        {
            auto new_d = new value_type[chk_max(new_cap)];
            copy_to(new_d);
            if (m_data != nullptr)
            {
                delete[] m_data;
            }
            m_data = new_d;
            this->m_cap = new_cap;
        }
        after_reset();
    }

protected:
    _array(size_type cap = 0) : base_type(cap), m_data(new value_type[chk_max(cap)]) {}

    _array(size_type cap, size_type size)
        : base_type(cap, size)
        , m_data(new value_type[chk_max(cap)]{} /* this m_data will initialized */)
    {}

    /* prevent conflict if 'size_type == value_type' without 'const value_type&' */
    _array(size_type size, const value_type* value)
        : base_type(size, size), m_data(new value_type[chk_max(size)])
    {
        ::std::fill(m_data, m_data + size, *value);
    }

    _array(const _array& other) : _array(other.m_cap, other.m_size) { other.copy_to(m_data); }

    _array(_array&& other) noexcept : base_type(other.m_cap, other.m_size), m_data(other.m_data)
    {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_cap = 0;
    }

    _array& operator=(const _array& other)
    {
        if (this != &other)
        {
            if (this->m_cap < other.m_cap)
            {
                auto new_d = new value_type[other.m_cap];
                delete[] this->m_data;
                this->m_data = new_d;
            }
            other.copy_to(this->m_data);
            this->m_cap = other.m_cap;
            this->m_size = other.m_size;
        }
        return *this;
    }

    void swap(_array& other)
    {
        ::std::swap(this->m_cap, other.m_cap);
        ::std::swap(this->m_size, other.m_size);
        ::std::swap(this->m_data, other.m_data);
    }

    // copy cannot use memcpy because it maybe a POD type
    virtual void copy_to(value_type* new_d) const { copy_to(new_d, this->m_size); }

    virtual void copy_to(value_type* new_d, size_type n) const
    {
        assert(n <= this->size());
        ::std::copy(m_data, m_data + n, new_d);
    }

    virtual void after_reset() {}

    virtual void after_clear() {}

    virtual void if_empty_then() const {}

    virtual void if_full_then() const {}

    using base_type::throw_if_empty;
    using base_type::throw_if_full;

    value_type* m_data;

private:
    size_type chk_max(size_type n) const
    {
        if (n > this->max_size())
        {
            throw ::std::length_error("reserve size > max_size()");
        }
        return n;
    }
};

} // namespace lzl::base

#endif // LZL_BASE_ARRAY_H
