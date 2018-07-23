#pragma once

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

        VConstListIterator & operator++()
        {
            current_ = current_->next_;
            return *this;
        }

        VConstListIterator & operator--()
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
        _Ty & operator*()
        {
            return this->_Retrive();
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
    VListIterator append(const _Ty& data, VListIterator *it);
    VListIterator prepend(const _Ty& data, VListIterator * it);

public:
    void push_back(const _Ty& data);
    void push_front(const _Ty& data);
    void pop_back() noexcept(false);
    void pop_front() noexcept(false);
    _Ty & get(int dest_index) noexcept(false);
    void clear();
    bool empty() { return size_ == 0; }
    size_t size() {return size_; }

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
VList<_Ty>::VConstListIterator::VConstListIterator(VListNode* node) : current_(node)
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
    *this = VList<_Ty>(rhs);
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
inline typename VList<_Ty>::VListIterator VList<_Ty>::append(const _Ty& data, VListIterator * it)
{
    auto node = it->current_;
    ++size_;

    auto new_node = new VListNode(data, node, node->next_);
    node->next_->prev_ = new_node;
    node->next_ = new_node;

    return VListIterator(new_node);
}

template<typename _Ty>
inline typename VList<_Ty>::VListIterator VList<_Ty>::prepend(const _Ty& data, VListIterator * it)
{
    auto node = it->current_;
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
    prepend(data, &tail_pointer);
}

template<typename _Ty>
inline void VList<_Ty>::push_front(const _Ty& data)
{
    auto head_pointer = begin();
    prepend(data, &head_pointer);
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
_Ty &VList<_Ty>::get(int dest_index)
{
    if (size_ == 0)
    {
        throw std::out_of_range("list is empty");
    }

    if (dest_index > size_ - 1)
    {
        throw std::out_of_range("out of range");
    }

    if (dest_index > size_ / 2)
    {
        auto current_index = size_ - 1;
        auto it = --end();
        while (current_index-- != dest_index + 1)
        {
            --it;
        }
        return *it;
    }
    else
    {
        auto current_index = 0;
        auto it = begin();
        while (current_index++ != dest_index - 1)
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
}
