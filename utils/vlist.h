#ifndef V_LIST_H_
#define V_LIST_H_

#include <assert.h>
#include <list>

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
    friend class VListIterator;

public:
    class VListIterator
    {
        friend class VList<_Ty>;

    public:
        VListIterator & operator++()
        {
            iter_ = iter_->next;
            return *this;
        }

        VListIterator & operator--()
        {
            iter_ = iter_->prev;
            return *this;
        }

        _Ty & operator*()
        {
            return iter_->data;
        }

        bool operator==(const VListIterator & rhs)
        {
            return this->iter_->data == rhs.iter_->data;
        }

    private:
        VListNode<_Ty> * iter_;
    };

public:
    VList<_Ty>();
    explicit VList<_Ty>(const _Ty & element);
    VList<_Ty>(const VList<_Ty> & rhs);
    ~VList();
    VList<_Ty> & operator=(const VList<_Ty> & rhs);

public:
    VListIterator & begin();
    VListIterator & end();

public:
    void push_back(const _Ty& data);
    void push_front(const _Ty& data);
    void pop_back() noexcept(false);
    void pop_front() noexcept(false);
    void clear();
    bool empty() { return size_ == 0; }

    // TODO ≤‚ ‘¥˙¬Î
public:
    VListNode<_Ty> * head_;
    VListNode<_Ty> * tail_;
    size_t size_;
};

template<typename _Ty>
inline VList<_Ty>::VList<_Ty>() : head_(new VListNode<_Ty>), tail_(head_), size_(0)
{
}

template<typename _Ty>
inline VList<_Ty>::VList<_Ty>(const _Ty & element) : head_(new VListNode<_Ty>), tail_(head_), size_(0)
{
    push_back(element);
}

template<typename _Ty>
inline VList<_Ty>::VList(const VList<_Ty>& rhs)
{
    clear();
    auto it = rhs.begin();
    while (it != rhs.end())
    {
        this->push_back(*it);
    }
}

template<typename _Ty>
inline VList<_Ty>::~VList()
{
    clear();
}

template<typename _Ty>
inline VList<_Ty>& VList<_Ty>::operator=(const VList<_Ty>& rhs)
{
    *this = VList<_Ty>(rhs);
    return *this;
}

template<typename _Ty>
inline VListIterator & VList<_Ty>::begin()
{
    return VListIterator(*(head_->next));
}

template<typename _Ty>
inline VListIterator & VList<_Ty>::end()
{
    return VListIterator(*(this->tail_));
}

template<typename _Ty>
inline void VList<_Ty>::push_back(const _Ty& data)
{
    VListNode<_Ty> * node_tmp = new VListNode<_Ty>;
    memcpy(&(node_tmp->data), &data, sizeof(_Ty));

    tail_->next = node_tmp;
    node_tmp->prev = tail_;
    node_tmp->next = head_;

    tail_ = node_tmp;

    ++size_;
}

template<typename _Ty>
inline void VList<_Ty>::push_front(const _Ty& data)
{
    VListNode<_Ty> * node_tmp = new VListNode<_Ty>;
    memcpy(&(node_tmp->data), &data, sizeof(_Ty));

    head_->next->prev = node_tmp;
    node_tmp->next = head_->next->next;
    node_tmp->prev = head_;
    head_->next = node_tmp;

    ++size_;
}

template<typename _Ty>
inline void VList<_Ty>::pop_back()
{
    if (size_ == 0)
    {
        throw std::out_of_range("list is empty");
    }

    auto node_to_delete = tail_;
    tail_ = tail_->prev;
    delete node_to_delete;
    node_to_delete = nullptr;
    tail_->next = head_;

    --size_;
}

template<typename _Ty>
inline void VList<_Ty>::pop_front()
{
    if (size_ == 0)
    {
        throw std::out_of_range("list is empty");
    }

    auto node_to_delete = head_->next;
    head_->next = head_->next->next;
    delete node_to_delete;
    node_to_delete = nullptr;
    head_->next->prev = head_;

    --size_;
}
template<typename _Ty>
inline void VList<_Ty>::clear()
{
    while (size_ != 0)
    {
        pop_back();
    }
}
}

#endif // V_LIST_H_
