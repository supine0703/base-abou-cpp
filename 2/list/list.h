#ifndef LZL_LIST_H
#define LZL_LIST_H


namespace lzl {

template <class T>
class List
{
public:
    List() {}
    virtual ~List();

public:
    struct Node
    {
        Node();
        ~Node();
        T data;
        Node* prev;
        Node* next;
    };

    Node* m_head;
    Node* m_tail;
};

} // namespace lzl

#endif // LZL_LIST_H
