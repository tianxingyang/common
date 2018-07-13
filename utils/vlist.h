#ifndef V_LIST_H_
#define V_LIST_H_

namespace vcommon
{
template <typename _Ty>
class VList
{
    struct VListNode
    {
        VListNode() : next_(nullptr), prev_(nullptr) {}
        VListNode(const _Ty & data, VListNode * next = nullptr, VListNode * prev = nullptr);
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
    VList<_Ty> & operator=(const VList<_Ty> & rhs);

public:
    VListIterator begin();
    VListIterator end();

public:
    void push_back(const _Ty& data);
    void push_front(const _Ty& data);
    void pop_back() noexcept(false);
    void pop_front() noexcept(false);
    void clear();
    bool empty() { return size_ == 0; }

    // TODO ≤‚ ‘¥˙¬Î
public:
    VListNode * head_;
    VListNode * tail_;
    size_t size_;
};

template <typename _Ty>
VList<_Ty>::VConstListIterator::VConstListIterator(VListNode* node) : current_(node)
{
}

template<typename _Ty>
inline VList<_Ty>::VList() : head_(new VListNode), tail_(head_), size_(0)
{
}

template<typename _Ty>
inline VList<_Ty>::VList(const _Ty & element) : head_(new VListNode), tail_(head_), size_(0)
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
inline void VList<_Ty>::push_back(const _Ty& data)
{
    VListNode * node_tmp = new VListNode;
    memcpy(&(node_tmp->data_), &data, sizeof(_Ty));

    tail_->next_ = node_tmp;
    node_tmp->prev_ = tail_;
    node_tmp->next_ = head_;

    tail_ = node_tmp;

    ++size_;
}

template<typename _Ty>
inline void VList<_Ty>::push_front(const _Ty& data)
{
    VListNode * node_tmp = new VListNode;
    memcpy(&(node_tmp->data_), &data, sizeof(_Ty));

    head_->next_->prev_ = node_tmp;
    node_tmp->next_ = head_->next_->next_;
    node_tmp->prev_ = head_;
    head_->next_ = node_tmp;

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
    tail_ = tail_->prev_;
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

template<typename _Ty>
inline VList<_Ty>::VListNode::VListNode(const _Ty & data, VListNode * next, VListNode * prev)
    : next_(next), prev_(prev), data_(data)
{
}
}

#endif // V_LIST_H_
