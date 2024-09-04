#ifndef LZL_ARRAY_STACK_H
#define LZL_ARRAY_STACK_H

#include "lzl_base_array.h"

namespace lzl
{

template <typename T, typename SIZE_T = size_t>
class array_stack : public base::_array<T, SIZE_T>
{
public:
    using base_type = base::_array<T, SIZE_T>;
    using typename base_type::size_type;
    using typename base_type::value_type;

    array_stack(size_type cap = 0) : base_type(cap) {}

    virtual ~array_stack() = default;

    void swap(array_stack& other) { base_type::swap(other); }

    void push(const value_type& value)
    {
        if_full_then();
        this->m_data[this->m_size] = value;
        this->m_size++;
    }

    void push(value_type&& value)
    {
        if_full_then();
        this->m_data[this->m_size] = ::std::move(value);
        this->m_size++;
    }

    template <class... Args>
    void push(Args&&... args)
    {
        if_full_then();
        this->m_data[this->m_size] = value_type(::std::forward<Args>(args)...);
        this->m_size++;
    }

    void pop()
    {
        if_empty_then();
        this->m_size--;
    }

    value_type& top()
    {
        if_empty_then();
        return this->m_data[this->m_size - 1];
    }

    const value_type& top() const
    {
        if_empty_then();
        return this->m_data[this->m_size - 1];
    }

protected:
    virtual void if_empty_then() const override { base_type::throw_if_empty("array_stack"); }

    virtual void if_full_then() const override { base_type::throw_if_full("array_stack"); }

    // iterator
    using iterator = value_type*;
    using const_iterator = const value_type*;

    constexpr iterator begin() noexcept { return this->m_data; }
    constexpr const_iterator begin() const noexcept { return this->m_data; }

    constexpr iterator end() noexcept { return this->m_data + this->m_size; }
    constexpr const_iterator end() const noexcept { return this->m_data + this->m_size; }

public:
    // compare
    constexpr bool operator==(const array_stack& other) const
    {
        return this->m_size == other.m_size &&
               ::std::equal(this->begin(), this->end(), other.begin());
    }

    constexpr bool operator<(const array_stack& other) const
    {
        return (
            this->m_size != other.m_size
                ? this->m_size < other.m_size
                : ::std::lexicographical_compare(
                      this->begin(), this->end(), other.begin(), other.end()
                  )
        );
    }
};

} // namespace lzl

#endif // LZL_ARRAY_STACK_H
