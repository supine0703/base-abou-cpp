#ifndef LZL_LIST_STACK_H
#define LZL_LIST_STACK_H

#include "lzl_base_list.h"

namespace lzl
{

template <typename T>
class list_stack : public base::_sl_list<T>
{
public:
    using base_type = base::_sl_list<T>;
    using typename base_type::node_type;
    using typename base_type::size_type;
    using typename base_type::value_type;

    list_stack() = default;

    virtual ~list_stack() = default;

    void swap(list_stack& other) { base_type::swap(other); }

    value_type& top()
    {
        if_empty_then();
        return this->m_head->value;
    }

    const value_type& top() const
    {
        if_empty_then();
        return this->m_head->value;
    }

protected:
    virtual void push_next(node_type* node) override
    {
        node->next = this->m_head;
        this->m_head = node;
        this->m_size++;
    }

    virtual void if_empty_then() const override { base_type::throw_if_empty("list_stack"); }
};

} // namespace lzl

#endif // LZL_LIST_STACK_H
