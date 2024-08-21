#ifndef LZL_BASE_H
#define LZL_BASE_H

namespace lzl {

template <class T>
class Base
{
public:
    Base() {}
    virtual ~Base() {}

    // 增
    virtual void push_back(const T& value) = 0;
    virtual void push_front(const T& value) = 0;
    virtual void insert(size_t index, const T& value) = 0;
    virtual void insert(size_t index, size_t size, const T& value) = 0;
    virtual void insert(size_t index, const Base<T>& other) = 0;
    virtual void insert(size_t index, Base<T>&& other) = 0;

    // 删
    virtual void clear() = 0;
    virtual void pop_back() = 0;
    virtual void pop_front() = 0;
    virtual void remove(size_t index) = 0;
    virtual void remove(size_t index, size_t size) = 0;
    virtual void remove(const T& value) = 0;

    // 改
    virtual void swap(const Base<T>& other) = 0;
    virtual void resize(size_t size) = 0;
    virtual void resize(size_t size, const T& value) = 0;

    // 查
    virtual T& at(size_t index) = 0;
    virtual const T& at(size_t index) const = 0;
    virtual T& front() = 0;
    virtual const T& front() const = 0;
    virtual T& back() = 0;
    virtual const T& back() const = 0;
    virtual size_t find(const T& value) const = 0;
    virtual size_t count(const T& value) const = 0;

    size_t size() const { return m_length; }
    size_t length() const { return m_length; }
    bool empty() const { return m_length == 0; }
    T& operator[](size_t index) { return at(index); }
    const T& operator[](size_t index) const { return at(index); }

protected:
    size_t m_length = 0;
};


} // namespace lzl

#endif // LZL_BASE_H
