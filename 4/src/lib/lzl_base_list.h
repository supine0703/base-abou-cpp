#ifndef LZL_BASE_LIST_H
#define LZL_BASE_LIST_H

#include "lzl_base_cap.h"
#include "lzl_limits.h"

namespace lzl
{

template <typename T, typename UNIT_SIZE_T, UNIT_SIZE_T _u_min_size>
class stack;

template <typename T, typename UNIT_SIZE_T, UNIT_SIZE_T _u_min_size>
class queue;

template <typename T, typename UNIT_SIZE_T, UNIT_SIZE_T _u_min_size>
class deque;

namespace base
{

template <typename T>
class _basic_list : public _size<>, public _max_size_interface<T>
{
public:
    using base_type = _size<>;
    using typename base_type::size_type;
    using value_type = T;

    virtual ~_basic_list() = default;

protected:
    struct sl_node
    {
        constexpr sl_node() = default;
        constexpr sl_node(const T& t) : value(t) {}
        constexpr sl_node(T&& t) : value(std::move(t)) {}
        template <class... Args>
        constexpr sl_node(Args&&... args) : value(std::forward<Args>(args)...)
        {}
        virtual ~sl_node()
        {
            if (next && next != this)
            {
                delete next;
                next = nullptr;
            }
        }

        T value;
        sl_node* next = nullptr;
    };

    struct dl_node
    {
        constexpr dl_node() = default;
        constexpr dl_node(const T& t) : value(t) {}
        constexpr dl_node(T&& t) : value(std::move(t)) {}
        template <class... Args>
        constexpr dl_node(Args&&... args) : value(std::forward<Args>(args)...)
        {}
        virtual ~dl_node()
        {
            if (next && next != this)
            {
                delete next;
                next = nullptr;
            }
            prev = nullptr;
        }

        T value;
        dl_node* next = nullptr;
        dl_node* prev = nullptr;
    };

    virtual void if_empty_then() const {}

    using base_type::throw_if_empty;

    using base_type::m_size;

    // iterator
    template <typename NODE_T>
    class iterator
    {
    public:
        using iterator_category = ::std::forward_iterator_tag;
        using difference_type = ::std::ptrdiff_t;
        using node_type = NODE_T;
        using value_type = T;
        using pointer = value_type*;
        using reference = value_type&;

        iterator() = default;

        iterator(node_type* node) : m_node(node) {}

        virtual ~iterator() = default;

        reference operator*() const { return m_node->value; }

        pointer operator->() const { return &(m_node->value); }

        iterator& operator++()
        {
            m_node = m_node->next;
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp = *this;
            m_node = m_node->next;
            return tmp;
        }

        constexpr friend bool operator==(const iterator& x, const iterator& y)
        {
            return x.m_node == y.m_node;
        }

    protected:
        node_type* m_node = nullptr;
    };

    template <typename NODE_T>
    class const_iterator
    {
    public:
        using iterator_category = ::std::forward_iterator_tag;
        using difference_type = ::std::ptrdiff_t;
        using node_type = NODE_T;
        using value_type = const T;
        using pointer = value_type*;
        using reference = value_type&;

        const_iterator() = default;

        const_iterator(node_type* node) : m_node(node) {}

        virtual ~const_iterator() = default;

        reference operator*() const { return m_node->value; }

        pointer operator->() const { return &(m_node->value); }

        const_iterator& operator++()
        {
            m_node = m_node->next;
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp = *this;
            m_node = m_node->next;
            return tmp;
        }

        constexpr friend bool operator==(const const_iterator& x, const const_iterator& y)
        {
            return x.m_node == y.m_node;
        }

    protected:
        node_type* m_node = nullptr;
    };
};

class _sl_list_change_size_interface
{
    template <typename T, typename UNIT_SIZE_T, UNIT_SIZE_T _u_min_size>
    friend class lzl::stack;

public:
    virtual ~_sl_list_change_size_interface() = default;

protected:
    virtual void size_up() = 0;
    virtual void size_down() = 0;
};

template <typename T>
class _sl_list : public _basic_list<T>, public _sl_list_change_size_interface
{
    template <typename U, typename UNIT_SIZE_T, UNIT_SIZE_T _u_min_size>
    friend class lzl::queue;

public:
    using base_type = _basic_list<T>;
    using node_type = typename base_type::sl_node;
    using typename base_type::size_type;
    using typename base_type::value_type;

    virtual ~_sl_list() { clear(); }

    void clear()
    {
        m_size = 0;
        if (m_head)
        {
            delete m_head;
            m_head = nullptr;
        }
    }

    void push(const T& value) { push_next(new node_type(value)); }

    void push(T&& value) { push_next(new node_type(std::move(value))); }

    template <class... Args>
    void push(Args&&... args)
    {
        push_next(new node_type(std::forward<Args>(args)...));
    }

    void pop()
    {
        if_empty_then();
        node_type* node = m_head;
        m_head = node->next;
        node->next = nullptr;
        delete node;
        m_size--;
    }

protected:
    virtual void push_next(node_type* node) = 0;

    void swap(_sl_list& other)
    {
        ::std::swap(this->m_head, other.m_head);
        ::std::swap(this->m_size, other.m_size);
    }

    using base_type::if_empty_then;

    using base_type::m_size;
    node_type* m_head = nullptr;

protected:
    virtual void size_up() override { m_size++; }
    virtual void size_down() override { m_size--; }

    // iterator
    using iterator = typename base_type::template iterator<node_type>;
    using const_iterator = typename base_type::template const_iterator<node_type>;

    iterator begin() { return iterator(m_head); }

    const_iterator begin() const { return const_iterator(m_head); }

    iterator end() { return iterator(); }

    const_iterator end() const { return const_iterator(); }

public:
    constexpr bool operator==(const _sl_list& other) const
    {
        return this->m_size == other.m_size &&
               ::std::equal(this->begin(), this->end(), other.begin());
    }

    constexpr bool operator<(const _sl_list& other) const
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

} // namespace base
} // namespace lzl

#endif // LZL_BASE_LIST_H
