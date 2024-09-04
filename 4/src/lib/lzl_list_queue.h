#ifndef LZL_LIST_QUEUE_H
#define LZL_LIST_QUEUE_H

#include "lzl_base_list.h"

namespace lzl
{

template <typename T>
class list_queue : public base::_sl_list<T>
{
public:
    using base_type = base::_sl_list<T>;
    using typename base_type::node_type;
    using typename base_type::size_type;
    using typename base_type::value_type;

    list_queue() = default;

    virtual ~list_queue() = default;

    void clear()
    {
        base_type::clear();
        m_tail = nullptr;
    }

    void swap(list_queue& other)
    {
        base_type::swap(other);
        std::swap(this->m_tail, other.m_tail);
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

protected:
    virtual void push_next(node_type* node) override
    {
        if (this->empty())
        {
            m_head = m_tail = node;
        }
        else
        {
            m_tail->next = node;
            m_tail = node;
        }
        this->m_size++;
    }

    virtual void if_empty_then() const override { base_type::throw_if_empty("list_queue"); }

    using base_type::m_head;
    node_type* m_tail = nullptr;
};

} // namespace lzl

#endif // LZL_LIST_QUEUE_H
