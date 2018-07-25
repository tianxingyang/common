#pragma once

#include <list>

std::list<int> l;

namespace vcommon
{
template <typename _Ty>
class VList
{
    struct VListNode
    {
        explicit VListNode(const _Ty & data = _Ty(), VListNode * prev = nullptr, VListNode * next = nullptr);
        VListNode * next_;
        VListNode * prev_;
        _Ty data_;
    };

public:
    class VConstListIterator
    {
        friend class VList<_Ty>;

    public:
        VConstListIterator() : current_(nullptr) {}
        virtual ~VConstListIterator() = default;

        virtual VConstListIterator & operator++()
        {
            current_ = current_->next_;
            return *this;
        }

        virtual VConstListIterator & operator--()
        {
            current_ = current_->prev_;
            return *this;
        }

        const _Ty & operator*() const
        {
            return _Retrive();
        }

        bool operator==(const VConstListIterator & rhs)
        {
            return current_ == rhs.current_;
        }

        bool operator!=(const VConstListIterator & rhs)
        {
            return !(*this == rhs);
        }

    protected:
        _Ty & _Retrive() const
        {
            return current_->data_;
        }
        explicit VConstListIterator(VListNode* node);

    protected:
        VListNode * current_;
    };

    class VListIterator : public VConstListIterator
    {
        friend class VList<_Ty>;
    public:
        VListIterator() : VConstListIterator() {}

    public:
        VListIterator & operator++()
        {
            this->current_ = this->current_->next_;
            return *this;
        }

        VListIterator & operator--()
        {
            this->current_ = this->current_->prev_;
            return *this;
        }
        _Ty & operator*()
        {
            return this->_Retrive();
        }

        bool operator==(const VListIterator & rhs)
        {
            return this->current_ == rhs.current_;
        }

        bool operator!=(const VListIterator & rhs)
        {
            return !(*this == rhs);
        }

    protected:
        explicit VListIterator(VListNode * node) : VConstListIterator(node) {}
    };

    friend class VConstListIterator;
    friend class VListIterator;

public:
    VList<_Ty>();
    explicit VList<_Ty>(const _Ty & element);
    VList<_Ty>(const VList<_Ty> & rhs);
    ~VList();

public:
    VList<_Ty> & operator=(const VList<_Ty> & rhs);

public:
    VListIterator begin();
    VListIterator end();
    VConstListIterator cbegin() const;
    VConstListIterator cend() const;

public:
    void push_back(const _Ty& data);
    void push_front(const _Ty& data);
    void pop_back() noexcept(false);
    void pop_front() noexcept(false);
    void remove(const _Ty& data);
    void clear();
    bool empty() { return size_ == 0; }
    size_t size() {return size_; }
    _Ty & get(int dest_index) noexcept(false);
    VListIterator erase(VListIterator position) noexcept(false);
    VListIterator erase(VListIterator from, VListIterator to) noexcept(false);
    VListIterator insert(VListIterator it, const _Ty &data);

private:
    //head_和tail_都是list外的节点
    //head_.next_指向首元素，tail_.prev_指向尾元素
    VListNode * head_;
    VListNode * tail_;
    size_t size_;
};

template<typename _Ty>
inline VList<_Ty>::VListNode::VListNode(const _Ty & data, VListNode * prev, VListNode * next)
    : next_(next), prev_(prev), data_(data)
{
}

template <typename _Ty>
inline  VList<_Ty>::VConstListIterator::VConstListIterator(VListNode* node) : current_(node)
{
}

template<typename _Ty>
inline VList<_Ty>::VList() : head_(new VListNode()), tail_(new VListNode()), size_(0)
{
    head_->next_ = tail_;
    tail_->prev_ = head_;
}

template<typename _Ty>
inline VList<_Ty>::VList(const _Ty & element) : head_(new VListNode()), tail_(new VListNode()), size_(0)
{
    head_->next_ = tail_;
    tail_->prev_ = head_;

    push_back(element);
}

template<typename _Ty>
inline VList<_Ty>::VList(const VList<_Ty>& rhs)
{
    clear();
    auto it = rhs.cbegin();
    while (it != rhs.cend())
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
    if (this == &rhs)
    {
        return *this;
    }

    clear();
    for(auto itr = rhs.cbegin(); itr != rhs.cend(); ++ itr)
    {
        push_back(*itr);
    }

    return *this;
}

template<typename _Ty>
inline typename VList<_Ty>::VListIterator VList<_Ty>::begin()
{
    return VListIterator(head_->next_);
}

template<typename _Ty>
inline typename VList<_Ty>::VListIterator VList<_Ty>::end()
{
    return VListIterator(tail_);
}

template<typename _Ty>
inline typename VList<_Ty>::VConstListIterator VList<_Ty>::cbegin() const
{
    return VConstListIterator(head_->next_);
}

template<typename _Ty>
inline typename VList<_Ty>::VConstListIterator VList<_Ty>::cend() const
{
    return VConstListIterator(tail_);
}

template<typename _Ty>
inline typename VList<_Ty>::VListIterator VList<_Ty>::insert(VListIterator it, const _Ty &data)
{
    auto node = it.current_;
    ++size_;

    auto new_node = new VListNode(data, node->prev_, node);
    node->prev_->next_ = new_node;
    node->prev_ = new_node;

    return VListIterator(new_node);
}

template<typename _Ty>
inline void VList<_Ty>::push_back(const _Ty& data)
{
    auto tail_pointer = end();
    insert(tail_pointer, data);
}

template<typename _Ty>
inline void VList<_Ty>::push_front(const _Ty& data)
{
    auto head_pointer = begin();
    insert(head_pointer, data);
}

template<typename _Ty>
inline void VList<_Ty>::pop_back()
{
    if (size_ == 0)
    {
        throw std::out_of_range("list is empty");
    }

    auto node_to_delete = tail_->prev_;
    tail_->prev_ = tail_->prev_->prev_;
    delete node_to_delete;
    tail_->prev_->next_ = tail_;

    --size_;
}

template<typename _Ty>
inline void VList<_Ty>::pop_front()
{
    if (size_ == 0)
    {
        throw std::out_of_range("list is empty");
    }

    auto node_to_delete = head_->next_;
    head_->next_ = head_->next_->next_;
    delete node_to_delete;
    head_->next_->prev_ = head_;

    --size_;
}

template<typename _Ty>
inline void VList<_Ty>::remove(const _Ty &data)
{
    for (auto it = begin(); it != end();)
    {
        if (it.current_->data_ == data)
        {
            it = erase(it);
        }
        else
        {
            ++it;
        }
    }
}

template<typename _Ty>
inline _Ty & VList<_Ty>::get(int dest_index)
{
    if (size_ == 0)
    {
        throw std::out_of_range("list is empty");
    }

    if (dest_index > int(size_ - 1))
    {
        throw std::out_of_range("out of range");
    }

    if (dest_index > int(size_ / 2))
    {
        auto current_index = int(size_ - 1);
        auto it = --end();
        while (current_index-- != dest_index)
        {
            --it;
        }
        return *it;
    }
    else
    {
        auto current_index = 0;
        auto it = begin();
        while (current_index++ != dest_index)
        {
            ++it;
        }
        return *it;
    }
}

template<typename _Ty>
inline void VList<_Ty>::clear()
{
    while (size_ != 0)
    {
        pop_back();
    }
}

template<typename _Ty>
inline typename VList<_Ty>::VListIterator VList<_Ty>::erase(VListIterator position)
{
    if (size_ == 0)
    {
        throw std::out_of_range("list is empty");
    }

    if (position == this->end())
    {
        throw std::out_of_range("cannot erase end()");
    }

    auto node_to_delete = position.current_;
    auto node_to_return = node_to_delete->next_;

    node_to_delete->next_->prev_ = node_to_delete->prev_;
    node_to_delete->prev_->next_ = node_to_delete->next_;

    delete node_to_delete;

    --size_;

    return VListIterator(node_to_return);
}

template<typename _Ty>
inline typename VList<_Ty>::VListIterator VList<_Ty>::erase(VListIterator from, VListIterator to)
{
    if (size_ == 0)
    {
        throw std::out_of_range("list is empty");
    }

    if (from == this->end() || to == this->end())
    {
        throw std::out_of_range("cannot erase end()");
    }

    auto it = from;

    while (it != to)
    {
        it = erase(it);
    }

    return it;
}
}
