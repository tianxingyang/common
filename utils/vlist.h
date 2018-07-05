#ifndef V_LIST_H_
#define V_LIST_H_

#include <stdio.h>
#include <string.h>

namespace vcommon
{
template <typename _Ty>
struct VListNode
{
    VListNode() : next(nullptr), prev(nullptr) {}
    VListNode * next;
    VListNode * prev;
    _Ty data;
};

template <typename _Ty>
class VList
{
public:
    VList();
    ~VList();

public:
    void push_back(_Ty * data);
    void push_front(_Ty * data);
    void pop_back();
    void pop_front();
    bool empty() { return size_ == 0; }

private:
    void append(VListNode<_Ty> * node, _Ty * data);
    void prepend(VListNode<_Ty> * node, _Ty * data);

private:
    VListNode<_Ty> * head_;
    VListNode<_Ty> * tail_;
    size_t size_;
};

template<typename _Ty>
inline vcommon::VList<_Ty>::VList()
{
    head_ = new VListNode<_Ty>;
    tail_ = head_;
    size_ = 0;
}

template<typename _Ty>
inline vcommon::VList<_Ty>::~VList()
{
    while (size_ != 0)
    {
        pop_back();
    }
}

template<typename _Ty>
inline void vcommon::VList<_Ty>::append(VListNode<_Ty> * node, _Ty * data)
{
    VListNode<_Ty> * node_tmp = new VListNode<_Ty>;
    memcpy(&(node_tmp->data), data, sizeof(_Ty));
    node->next->prev = node_tmp;
    node_tmp->next = node->next;
    node->next = node_tmp;
    node_tmp->prev = node;

    ++size_;
}

template<typename _Ty>
inline void vcommon::VList<_Ty>::prepend(VListNode<_Ty> * node, _Ty * data)
{
    VListNode<_Ty> * node_tmp = new VListNode<_Ty>;
    memcpy(&(node_tmp->data), data, sizeof(_Ty));
    node->prev->next = node_tmp;
    node_tmp->prev = node->prev;
    node->prev = node_tmp;
    node_tmp->next = node;

    ++size_;
}

template<typename _Ty>
inline void vcommon::VList<_Ty>::push_back(_Ty * data)
{
    append(tail_, data);
}

template<typename _Ty>
inline void vcommon::VList<_Ty>::push_front(_Ty * data)
{
    prepend(head_, data);
}
template<typename _Ty>
inline void vcommon::VList<_Ty>::pop_back()
{
}
template<typename _Ty>
inline void vcommon::VList<_Ty>::pop_front()
{
}
}

#endif // V_LIST_H_
