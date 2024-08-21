#include "list.h"

using namespace lzl;

template <class T>
List<T>::~List()
{
    if (m_head)
    {
        delete m_head;
    }
    m_head = m_tail = nullptr;
}

template <class T>
List<T>::Node::~Node()
{
    if (next)
    {
        delete next;
    }
    next = prev = nullptr;
}

