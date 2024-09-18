#ifndef LZL_ARRAY_DEQUE_H
#define LZL_ARRAY_DEQUE_H

#include "lzl_base_array.h"

namespace lzl
{

template <typename T, typename SIZE_T = size_t>
class array_deque : public base::_array<T, SIZE_T>
{
public:
    using base_type = base::_array<T, SIZE_T>;
    using typename base_type::size_type;
    using typename base_type::value_type;

    array_deque(size_type cap = 0) : base_type(cap), m_head(0), m_tail(cap - 1) {}

    array_deque(const array_deque& other) : base_type(other), m_head(0), m_tail(other.m_size - 1) {}

    array_deque(array_deque&& other) noexcept
        : base_type(::std::move(other)), m_head(other.m_head), m_tail(other.m_tail)
    {
        other.m_head = 0;
        other.m_tail = 0;
    }

    virtual ~array_deque() = default;

    array_deque& operator=(const array_deque& other)
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
            m_head = 0;
            m_tail = other.m_size - 1;
        }
        return *this;
    }

    void swap(array_deque& other)
    {
        base_type::swap(other);
        ::std::swap(this->m_head, other.m_head);
        ::std::swap(this->m_tail, other.m_tail);
    }

    void push_front(const value_type& value)
    {
        before_push_front();
        front() = value;
    }

    void push_front(value_type&& value)
    {
        before_push_front();
        front() = ::std::move(value);
    }

    template <class... Args>
    void push_front(Args&&... args)
    {
        before_push_front();
        front() = value_type(::std::forward<Args>(args)...);
    }

    void push_back(const value_type& value)
    {
        before_push_back();
        back() = value;
    }

    void push_back(value_type&& value)
    {
        before_push_back();
        back() = ::std::move(value);
    }

    template <class... Args>
    void push_back(Args&&... args)
    {
        before_push_back();
        back() = value_type(::std::forward<Args>(args)...);
    }

    void pop_front()
    {
        if_empty_then();
        this->m_size--;
        plus(m_head);
    }

    void pop_back()
    {
        if_empty_then();
        this->m_size--;
        minus(m_tail);
    }

    value_type& front()
    {
        if_empty_then();
        return this->m_data[m_head];
    }

    const value_type& front() const
    {
        if_empty_then();
        return this->m_data[m_head];
    }

    value_type& back()
    {
        if_empty_then();
        return this->m_data[m_tail];
    }

    const value_type& back() const
    {
        if_empty_then();
        return this->m_data[m_tail];
    }

private:
    void plus(size_type& value) const
    {
        value++;
        if (value == this->m_cap)
        {
            value = 0;
        }
    }

    void minus(size_type& value) const
    {
        if (value == 0)
        {
            value = this->m_cap;
        }
        value--;
    }

    void before_push_front()
    {
        if_full_then();
        minus(m_head);
        this->m_size++;
    }

    void before_push_back()
    {
        if_full_then();
        plus(m_tail);
        this->m_size++;
    }

protected:
    virtual void copy_to(value_type* new_d) const override
    {
        if (this->empty())
        {
        }
        else if (m_head <= m_tail)
        {
            ::std::copy(this->m_data + m_head, this->m_data + m_tail + 1, new_d);
        }
        else
        {
            ::std::copy(this->m_data + m_head, this->m_data + this->m_cap, new_d);
            ::std::copy(this->m_data, this->m_data + m_tail + 1, new_d + this->m_cap - m_head);
        }
    }

    virtual void copy_to(value_type* new_d, size_type n) const
    {
        assert(n <= this->size());
        if (this->empty())
        {
        }
        else if (m_head <= m_tail)
        {
            ::std::copy(this->m_data + m_head, this->m_data + n, new_d);
        }
        else
        {
            auto count = this->m_cap - m_head;
            if (n <= count)
            {
                ::std::copy(this->m_data + m_head, this->m_data + m_head + n, new_d);
            }
            else
            {
                ::std::copy(this->m_data + m_head, this->m_data + this->m_cap, new_d);
                ::std::copy(this->m_data, this->m_data + n - count, new_d + count);
            }
        }
    }

    virtual void after_reset() override
    {
        m_head = 0;
        m_tail = this->m_size - 1;
    }

    virtual void after_clear() override
    {
        m_head = 0;
        m_tail = this->m_cap - 1;
    }

    virtual void if_empty_then() const override { base_type::throw_if_empty("array_deque"); }

    virtual void if_full_then() const override { base_type::throw_if_full("array_deque"); }

    size_type m_head;
    size_type m_tail;

protected: // for vector's construction
    array_deque(size_type size, void*) : base_type(size, size), m_head(0), m_tail(size - 1) {}

    array_deque(size_type size, const value_type& value)
        : base_type(size, &value), m_head(0), m_tail(size - 1)
    {}

public:
    // iterator
    class iterator
    {
    public:
        using iterator_category = ::std::forward_iterator_tag;
        using difference_type = ::std::ptrdiff_t;
        using super_pointer = const array_deque*;
        using value_type = T;
        using pointer = value_type*;
        using reference = value_type&;

        iterator() = default;

        iterator(super_pointer p, size_type i) : p(p), i(i) {}

        T& operator*() const { return p->m_data[i]; }

        T* operator->() const { return &(p->m_data[i]); }

        iterator& operator++()
        {
            if (i == p->m_tail)
            {
                i = p->m_cap;
            }
            else
            {
                p->plus(i);
            }
            return *this;
        }

        iterator operator++(int)
        {
            auto it = *this;
            if (i == p->m_tail)
            {
                i = p->m_cap;
            }
            else
            {
                p->plus(i);
            }
            return it;
        }

        iterator& operator--()
        {
            if (i != p->m_head)
            {
                p->minus(i);
            }
            return *this;
        }

        iterator operator--(int)
        {
            auto it = *this;
            if (i != p->m_head)
            {
                p->minus(i);
            }
            return it;
        }

        friend constexpr bool operator==(const iterator& x, const iterator& y)
        {
            return x.p == y.p && x.i == y.i;
        }

    private:
        super_pointer p;
        size_type i;
    };

    class const_iterator
    {
    public:
        using iterator_category = ::std::forward_iterator_tag;
        using difference_type = ::std::ptrdiff_t;
        using super_pointer = const array_deque*;
        using value_type = const T;
        using pointer = value_type*;
        using reference = value_type&;

        const_iterator() = default;

        const_iterator(super_pointer p, size_type i) : p(p), i(i) {}

        const T& operator*() const { return p->m_data[i]; }

        const T* operator->() const { return &(p->m_data[i]); }

        const_iterator& operator++()
        {
            if (i == p->m_tail)
            {
                i = p->m_cap;
            }
            else
            {
                p->plus(i);
            }
            return *this;
        }

        const_iterator operator++(int)
        {
            auto it = *this;
            if (i == p->m_tail)
            {
                i = p->m_cap;
            }
            else
            {
                p->plus(i);
            }
            return it;
        }

        const_iterator& operator--()
        {
            if (i != p->m_head)
            {
                p->minus(i);
            }
            return *this;
        }

        const_iterator operator--(int)
        {
            auto it = *this;
            if (i != p->m_head)
            {
                p->minus(i);
            }
            return it;
        }

        friend constexpr bool operator==(const const_iterator& x, const const_iterator& y)
        {
            return x.p == y.p && x.i == y.i;
        }

    private:
        super_pointer p;
        size_type i;
    };

    constexpr iterator begin() noexcept { return iterator(this, m_head); }
    constexpr const_iterator begin() const noexcept { return const_iterator(this, m_head); }

    constexpr iterator end() { return ++iterator(this, m_tail); }
    constexpr const_iterator end() const { return ++const_iterator(this, m_tail); }

    // compare
    constexpr bool operator==(const array_deque& other) const
    {
        return this->m_size == other.m_size &&
               ::std::equal(this->begin(), this->end(), other.begin());
    }

    constexpr bool operator<(const array_deque& other) const
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

#endif // LZL_ARRAY_DEQUE_H
