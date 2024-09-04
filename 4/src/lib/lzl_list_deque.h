#ifndef LZL_LIST_DEQUE_H
#define LZL_LIST_DEQUE_H

#include "lzl_base_list.h"

namespace lzl
{

template <typename T>
class list_deque : public base::_basic_list<T>
{
    template <typename U, typename UNIT_SIZE_T, UNIT_SIZE_T _u_min_size>
    friend class deque;

public:
    using base_type = base::_basic_list<T>;
    using node_type = typename base_type::dl_node;
    using typename base_type::size_type;
    using typename base_type::value_type;

    virtual ~list_deque() { clear(); }

    void clear()
    {
        m_size = 0;
        if (m_head)
        {
            delete m_head;
            m_head = nullptr;
        }
        m_tail = nullptr;
    }

    void swap(list_deque& other)
    {
        ::std::swap(this->m_size, other.m_size);
        ::std::swap(this->m_head, other.m_head);
        ::std::swap(this->m_tail, other.m_tail);
    }

    void push_front(const value_type& value) { push_front_next(new node_type(value)); }

    void push_front(value_type&& value) { push_front_next(new node_type(std::move(value))); }

    template <class... Args>
    void push_front(Args&&... args)
    {
        push_front_next(new node_type(std::forward<Args>(args)...));
    }

    void push_back(const value_type& value) { push_back_next(new node_type(value)); }

    void push_back(value_type&& value) { push_back_next(new node_type(std::move(value))); }

    template <class... Args>
    void push_back(Args&&... args)
    {
        push_back_next(new node_type(std::forward<Args>(args)...));
    }

    void pop_front()
    {
        if_empty_then();
        auto node = m_head;
        m_head = node->next;
        node->next = nullptr;
        if (m_head)
        {
            m_head->prev = nullptr;
        }
        delete node;
        m_size--;
    }

    void pop_back()
    {
        if_empty_then();
        auto node = m_tail;
        m_tail = node->prev;
        node->prev = nullptr;
        if (m_tail)
        {
            m_tail->next = nullptr;
        }
        delete node;
        m_size--;
    }

    value_type& front()
    {
        if_empty_then();
        return m_head->value;
    }

    const value_type& front() const
    {
        if_empty_then();
        return m_head->value;
    }

    value_type& back()
    {
        if_empty_then();
        return m_tail->value;
    }

    const value_type& back() const
    {
        if_empty_then();
        return m_tail->value;
    }

private:
    void push_front_next(node_type* node)
    {
        if (this->empty())
        {
            m_head = m_tail = node;
        }
        else
        {
            node->next = m_head;
            m_head->prev = node;
            m_head = node;
        }
        m_size++;
    }

    void push_back_next(node_type* node)
    {
        if (this->empty())
        {
            m_head = m_tail = node;
        }
        else
        {
            node->prev = m_tail;
            m_tail->next = node;
            m_tail = node;
        }
        m_size++;
    }

protected:
    virtual void if_empty_then() const override { base_type::throw_if_empty("list_deque"); }

    using base_type::m_size;
    node_type* m_head = nullptr;
    node_type* m_tail = nullptr;

protected:
    // iterator
    class iterator : public base_type::iterator<node_type>
    {
        using base_type = typename list_deque::base_type::iterator<node_type>;

    public:
        using base_type::difference_type;
        using base_type::iterator_category;
        using base_type::node_type;
        using base_type::pointer;
        using base_type::reference;

        using base_type::iterator;

        iterator& operator--()
        {
            m_node = m_node->prev;
            return *this;
        }

        iterator operator--(int)
        {
            iterator tmp = *this;
            m_node = m_node->prev;
            return tmp;
        }

    private:
        using base_type::m_node;
    };

    class const_iterator : public base_type::const_iterator<node_type>
    {
        using base_type = typename list_deque::base_type::const_iterator<node_type>;

    public:
        using base_type::difference_type;
        using base_type::iterator_category;
        using base_type::node_type;
        using base_type::pointer;
        using base_type::reference;
        using base_type::value_type;

        using base_type::const_iterator;

        const_iterator& operator--()
        {
            m_node = m_node->prev;
            return *this;
        }

        const_iterator operator--(int)
        {
            const_iterator tmp = *this;
            m_node = m_node->prev;
            return tmp;
        }

    private:
        using base_type::m_node;
    };

    iterator begin() { return iterator(m_head); }

    const_iterator begin() const { return const_iterator(m_head); }

    iterator end() { return iterator(); }

    const_iterator end() const { return const_iterator(); }

public:
    constexpr bool operator==(const list_deque& other) const
    {
        return this->m_size == other.m_size &&
               ::std::equal(this->begin(), this->end(), other.begin());
    }

    constexpr bool operator<(const list_deque& other) const
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

#endif // LZL_LIST_DEQUE_H
