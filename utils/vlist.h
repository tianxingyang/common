#ifndef V_LIST_H_
#define V_LIST_H_

#include <stdio.h>
#include <string.h>
#include <assert.h>

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
inline void vcommon::VList<_Ty>::push_back(_Ty * data)
{
    VListNode<_Ty> * node_tmp = new VListNode<_Ty>;
    memcpy(&(node_tmp->data), data, sizeof(_Ty));

    tail_->next = node_tmp;
    node_tmp->prev = tail_;
    node_tmp->next = head_;

    tail_ = node_tmp;

    ++size_;
}

template<typename _Ty>
inline void vcommon::VList<_Ty>::push_front(_Ty * data)
{
    VListNode<_Ty> * node_tmp = new VListNode<_Ty>;
    memcpy(&(node_tmp->data), data, sizeof(_Ty));

    head_->next->prev = node_tmp;
    node_tmp->next = head_->next->next;
    node_tmp->prev = head_;
    head_->next = node_tmp;

    ++size_;
}

template<typename _Ty>
inline void vcommon::VList<_Ty>::pop_back()
{
    assert(size_ > 0);

    auto node_to_delete = tail_;
    tail_ = tail_->prev;
    delete node_to_delete;
    node_to_delete = nullptr;

    --size_;
}

template<typename _Ty>
inline void vcommon::VList<_Ty>::pop_front()
{
    assert(size_ > 0);

    auto node_to_delete = head_->next;
    head_->next = head_->next->next;
    delete node_to_delete;
    node_to_delete = nullptr;

    --size_;
}
}

#endif // V_LIST_H_
