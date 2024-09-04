#ifndef LZL_STACK_H
#define LZL_STACK_H

#include "lzl_array_stack.h"
#include "lzl_list_stack.h"

namespace lzl
{

template <typename T, typename UNIT_SIZE_T = uint8_t, UNIT_SIZE_T _u_min_size = UNIT_BLOCK_MIN_SIZE>
class stack
{
public:
    using value_type = T;
    using unit_size_type = UNIT_SIZE_T;
    using array_type = array_stack<value_type, UNIT_SIZE_T>;
    using list_type = list_stack<array_type>;
    using size_type = typename list_type::size_type;

    static constexpr size_t array_unit_size() noexcept
    {
        unit_size_type value_size = sizeof(value_type);
        return static_cast<size_t>(
            _u_min_size / value_size + ((value_size & (value_size - 1)) != 0)
        );
    }

    stack() = default;

    virtual ~stack() = default;

    void clear() { m_list.clear(); }

    void swap(stack& other) { m_list.swap(other.m_list); }

    bool empty() const { return m_list.empty(); }

    size_type size() const { return m_list.size(); }

    value_type& top()
    {
        if_empty_then();
        return m_list.top().top();
    }

    const value_type& top() const
    {
        if_empty_then();
        return m_list.top().top();
    }

    void push(const value_type& value)
    {
        before_push();
        m_list.top().push(value);
    }

    void push(value_type&& value)
    {
        before_push();
        m_list.top().push(::std::move(value));
    }

    template <class... Args>
    void push(Args&&... args)
    {
        before_push();
        m_list.top().push(::std::forward<Args>(args)...);
    }

    void pop()
    {
        if_empty_then();
        m_list.top().pop();
        if (m_list.top().empty())
        {
            m_list.pop();
        }
        else
        {
            base::_sl_list_change_size_interface* p = &m_list;
            p->size_down();
        }
    }

private:
    void before_push()
    {
        if (m_list.empty() || m_list.top().full())
        {
            m_list.push(array_unit_size()); // push new array
        }
        else
        {
            base::_sl_list_change_size_interface* p = &m_list;
            p->size_up();
        }
    }

    void if_empty_then() const { lzl::utils::throw_if(empty(), "stack", "is empty"); }

protected:
    list_type m_list;

public:
    constexpr bool operator==(const stack& other) const { return this->m_list == other.m_list; }

    constexpr bool operator<(const stack& other) const { return this->m_list < other.m_list; }
};

} // namespace lzl

#endif // LZL_STACK_H
