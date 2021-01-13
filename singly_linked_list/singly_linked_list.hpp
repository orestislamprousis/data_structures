#pragma once

#include <stdexcept>
#include <stddef.h>

namespace orla
{

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member)                   \
    ({                                                    \
        const typeof(((type*)0)->member)* __mptr = (ptr); \
        (type*)((char*)__mptr - offsetof(type, member));  \
    })

template <class T>
class singly_linked_list
{
public:
    typedef bool (*item_comparator)(const T& a, const T& b);

    singly_linked_list(item_comparator comparator);
    singly_linked_list(const singly_linked_list& list) = delete;
    ~singly_linked_list();

    size_t size();
    bool   is_empty();
    T&     value_at(const size_t index);
    void   push_front(const T& value);
    T      pop_front();
    void   push_back(const T& value);
    T      pop_back();
    T&     front();
    T&     back();
    void   insert(const size_t index, const T& value);
    void   erase(const size_t index);
    T&     value_n_from_end(const size_t n);
    void   reverse();
    void   remove_value(const T& value);

private:
    /* data */
    typedef struct node
    {
        T     item;
        node* next;
    } node_t;

    size_t          m_size;
    node_t*         m_head;
    node_t*         m_tail;
    item_comparator m_comparator;

    /* functions */
    void remove_next_node(node_t** node);
};

template <class T>
singly_linked_list<T>::singly_linked_list(item_comparator comparator)
    : m_size{ 0 }
    , m_head{ nullptr }
    , m_tail{ nullptr }
    , m_comparator{ comparator }
{
    if (!m_comparator)
    {
        throw std::invalid_argument("Comparator cannot be null");
    }
}

template <class T>
singly_linked_list<T>::~singly_linked_list()
{
    node_t* del;
    while (m_head)
    {
        del    = m_head;
        m_head = m_head->next;
        delete del;
    }
}

template <class T>
size_t singly_linked_list<T>::size()
{
    return m_size;
}

template <class T>
bool singly_linked_list<T>::is_empty()
{
    return !m_size;
}

template <class T>
T& singly_linked_list<T>::value_at(const size_t index)
{
    if (index >= m_size)
        throw std::out_of_range("Out of range index");

    node_t* tmp = m_head;
    for (size_t i = 1; i <= index; i++)
        tmp = tmp->next;

    return tmp->item;
}

template <class T>
void singly_linked_list<T>::push_front(const T& value)
{
    insert(0, value);
}

template <class T>
T singly_linked_list<T>::pop_front()
{
    if (!m_size)
        throw std::logic_error("Cannot pop from an empty list");

    T ret = m_head->item;
    remove_next_node(&m_head);
    return ret;
}

template <class T>
void singly_linked_list<T>::push_back(const T& value)
{
    node_t* n = new node_t;
    n->next   = nullptr;
    n->item   = value;

    if (m_tail)
        m_tail->next = n;
    else
        m_head = n;

    m_tail = n;
    m_size++;
}

template <class T>
T singly_linked_list<T>::pop_back()
{
    if (!m_size)
        throw std::logic_error("Cannot pop from an empty list");

    node_t** node = &m_head;
    while ((*node)->next != nullptr)
        node = &(*node)->next;

    T ret = (*node)->item;

    delete *node;
    *node = nullptr;

    if (!m_head)
        m_tail = m_head;
    else
        m_tail = container_of(node, node_t, next);

    m_size--;

    return ret;
}

template <class T>
T& singly_linked_list<T>::front()
{
    if (!m_size)
        throw std::logic_error("Cannot get front item from an empty list");

    return m_head->item;
}

template <class T>
T& singly_linked_list<T>::back()
{
    if (!m_size)
        throw std::logic_error("Cannot get last item from an empty list");

    return m_tail->item;
}

template <class T>
void singly_linked_list<T>::insert(const size_t index, const T& value)
{
    if (index > m_size)
        throw std::out_of_range("Out of range index to insert item. Index should be <= size()");

    if (m_size && index == m_size)
    {
        push_back(value);
        return;
    }

    node_t* new_node = new node_t;
    new_node->item   = value;

    node_t** current_next_node = &m_head;
    for (size_t i = 0; i < index; ++i)
        current_next_node = &(*current_next_node)->next;

    new_node->next = *current_next_node;

    *current_next_node = new_node;

    if (!m_tail)
        m_tail = new_node;

    m_size++;
}

template <class T>
T& singly_linked_list<T>::value_n_from_end(const size_t n)
{
    if (n >= m_size)
        throw std::out_of_range("Out of range index to get value from end");

    node_t* current_node = m_head;
    for (size_t index_from_head = m_size - 1 - n; index_from_head; --index_from_head)
        current_node = current_node->next;

    return current_node->item;
}

template <class T>
void singly_linked_list<T>::reverse()
{
    if (!m_size || m_size == 1)
        return;

    node_t* next = nullptr;
    node_t* prev = nullptr;
    node_t* current_node;
    for (current_node = m_head; current_node; current_node = next)
    {
        next               = current_node->next;
        current_node->next = prev;
        prev               = current_node;
    }

    current_node = m_head;
    m_head       = m_tail;
    m_tail       = current_node;
}

template <class T>
void singly_linked_list<T>::remove_value(const T& value)
{
    if (!m_size)
        return;

    node_t** node;
    for (node = &m_head; *node != nullptr; node = &(*node)->next)
    {
        if (m_comparator(value, (*node)->item))
        {
            remove_next_node(node);
            break;
        }
    }
}

template <class T>
void singly_linked_list<T>::erase(const size_t index)
{
    if (index >= m_size)
        throw std::out_of_range("Out of range index to erase");

    if (index == m_size - 1)
    {
        pop_back();
        return;
    }

    node_t** node = &m_head;
    for (size_t i = 0; i < index; ++i)
        node = &(*node)->next;

    remove_next_node(node);
}

template <class T>
void singly_linked_list<T>::remove_next_node(node_t** node)
{
    node_t* to_destroy = *node;

    if (!to_destroy->next)
        m_tail = container_of(node, node_t, next);

    *node = to_destroy->next;
    delete to_destroy;
    m_size--;
}
} // namespace orla