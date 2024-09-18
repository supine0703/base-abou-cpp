#ifndef LZL_QUEUE_H
#define LZL_QUEUE_H

#include "lzl_array_deque.h"
#include "lzl_list_queue.h"

namespace lzl
{

template <typename T, typename UNIT_SIZE_T = uint8_t, UNIT_SIZE_T _u_min_size = UNIT_BLOCK_MIN_SIZE>
class queue
{
public:
    using value_type = T;
    using unit_size_type = UNIT_SIZE_T;
    using array_type = array_deque<value_type, UNIT_SIZE_T>;
    using list_type = list_queue<array_type>;
    using size_type = typename list_type::size_type;

    static constexpr size_t array_unit_size() noexcept
    {
        unit_size_type value_size = sizeof(value_type);
        return static_cast<size_t>(
            _u_min_size / value_size + ((value_size & (value_size - 1)) != 0)
        );
    }

    queue() = default;

    virtual ~queue() = default;

    void swap(queue& other) { m_list.swap(other.m_list); }

    bool empty() const { return m_list.empty(); }

    size_type size() const { return m_list.size(); }

    value_type& front()
    {
        if_empty_then();
        return m_list.front().front();
    }

    const value_type& front() const
    {
        if_empty_then();
        return m_list.front().front();
    }

    value_type& back()
    {
        if_empty_then();
        return m_list.back().back();
    }

    const value_type& back() const
    {
        if_empty_then();
        return m_list.back().back();
    }

    void push(const value_type& value)
    {
        before_push();
        m_list.back().push(value);
    }

    void push(value_type&& value)
    {
        before_push();
        m_list.back().push_back(::std::move(value));
    }

    template <class... Args>
    void push(Args&&... args)
    {
        before_push();
        m_list.back().push(::std::forward<Args>(args)...);
    }

    void pop()
    {
        if_empty_then();
        m_list.front().pop_front();
        if (m_list.front().empty())
        {
            m_list.pop();
        }
        else
        {
            m_list.m_size--;
        }
    }

private:
    void before_push()
    {
        if (m_list.empty() || m_list.back().full())
        {
            m_list.push(array_unit_size()); // push new array
        }
        else
        {
            m_list.m_size++;
        }
    }

    void if_empty_then() const { lzl::utils::throw_if(empty(), "queue", "is empty"); }

protected:
    list_type m_list;

    class iterator
    {
    public:
        using iterator_category = ::std::forward_iterator_tag;
        using difference_type = ::std::ptrdiff_t;
        using value_type = T;
        using pointer = value_type*;
        using reference = value_type&;
        using array_it = array_type::iterator;
        using list_it = list_type::iterator;

        iterator() = default;

        iterator(list_it lit) : lit(lit)
        {
            if (lit != nullptr)
            {
                ait = lit->begin();
            }
        }

        iterator(list_it lit, array_it ait) : lit(lit), ait(ait) {}

        reference operator*() const { return *ait; }

        pointer operator->() const { return &(*ait); }

        iterator& operator++()
        {
            if (++ait == lit->end() && ++lit != nullptr)
            {
                ait = lit->begin();
            }
            return *this;
        }

        iterator operator++(int)
        {
            auto it = *this;
            if (++ait == lit->end() && ++lit != nullptr)
            {
                ait = lit->begin();
            }
            return it;
        }

        constexpr bool operator==(const iterator& other) const
        {
            return (ait == other.ait) || (lit == nullptr && other.lit == nullptr);
        }

    private:
        array_it ait;
        list_it lit;
    };

    class const_iterator
    {
    public:
        using iterator_category = ::std::forward_iterator_tag;
        using difference_type = ::std::ptrdiff_t;
        using value_type = const T;
        using pointer = value_type*;
        using reference = value_type&;
        using array_it = array_type::const_iterator;
        using list_it = list_type::const_iterator;

        const_iterator() = default;

        const_iterator(list_it lit) : lit(lit)
        {
            if (lit != nullptr)
            {
                ait = lit->begin();
            }
        }

        const_iterator(list_it lit, array_it ait)
            : lit(lit), ait(ait)
        {}

        reference operator*() const { return *ait; }

        pointer operator->() const { return &(*ait); }

        const_iterator& operator++()
        {
            if (++ait == lit->end() && ++lit != nullptr)
            {
                ait = lit->begin();
            }
            return *this;
        }

        const_iterator operator++(int)
        {
            auto it = *this;
            if (++ait == lit->end() && ++lit != nullptr)
            {
                ait = lit->begin();
            }
            return it;
        }

        constexpr bool operator==(const const_iterator& other) const
        {
            return (ait == other.ait) || (lit == nullptr && other.lit == nullptr);
        }

    private:
        array_it ait;
        list_it lit;
    };

    iterator begin() { return iterator(m_list.begin()); }

    const_iterator begin() const { return const_iterator(m_list.begin()); }

    iterator end() { return iterator(m_list.end()); }

    const_iterator end() const { return const_iterator(m_list.end()); }

public:
    constexpr bool operator==(const queue& other) const
    {
        return this->m_list.size() == other.m_list.size() &&
               ::std::equal(this->begin(), this->end(), other.begin());
    }

    constexpr bool operator<(const queue& other) const
    {
        return (
            this->m_list.size() != other.m_list.size()
                ? this->m_list.size() < other.m_list.size()
                : ::std::lexicographical_compare(
                      this->begin(), this->end(), other.begin(), other.end()
                  )
        );
    }
};

} // namespace lzl

#endif // LZL_QUEUE_H
