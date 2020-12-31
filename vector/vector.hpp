#pragma once

#include <cstddef>
#include <stdexcept>

namespace orla
{

static const size_t initial_vector_capacity = 16;

template <class T>
class vector
{
public:
    typedef bool (*item_comparator)(const T& a, const T& b);

    vector(item_comparator comparator);
    vector(const vector& vector) = delete;
    ~vector();

    size_t size();
    size_t capacity();
    bool   is_empty();

    T&   at(const size_t index);
    void push(const T& item);
    void insert(const size_t index, const T& item);
    void prepend(const T& item);
    T    pop();
    void erase_at(const size_t index);
    void remove(const T& item);
    int  find(const T& item);

private:
    /* data */
    size_t          m_capacity;
    size_t          m_size;
    T*              m_array;
    item_comparator m_comparator;

    /* functions */
    void        resize(const size_t new_capacity);
    void        check_resize(bool will_add = true);
    int         find_from_index(const size_t index, const T& item);
    inline void post_delete_actions();
};

template <class T>
vector<T>::vector(item_comparator comparator)
    : m_capacity{ initial_vector_capacity }
    , m_size{ 0 }
    , m_array{ nullptr }
    , m_comparator{ comparator }
{
    if (!m_comparator)
    {
        throw std::invalid_argument("Comparator cannot be null");
    }
    m_array = new T[m_capacity];
}

template <class T>
vector<T>::~vector()
{
    if (m_array)
        delete[] m_array;
}

template <class T>
size_t vector<T>::size()
{
    return m_size;
}

template <class T>
size_t vector<T>::capacity()
{
    return m_capacity;
}

template <class T>
bool vector<T>::is_empty()
{
    return !m_size;
}

template <class T>
T& vector<T>::at(const size_t index)
{
    if (index >= m_size)
        throw std::out_of_range("Out of range index");

    return *(m_array + index);
}

template <class T>
void vector<T>::push(const T& item)
{
    check_resize();

    *(m_array + m_size) = item;
    m_size++;
}

template <class T>
void vector<T>::insert(const size_t index, const T& item)
{
    if (index > m_size)
        throw std::out_of_range("Out of range index to insert item. Index should be <= size()");

    check_resize();

    /* Shift trailing items if they exist */
    if (m_size)
    {
        size_t max_index = m_size - 1;
        for (size_t i = max_index; i >= index && i <= max_index; --i)
        {
            *(m_array + i + 1) = *(m_array + i);
        }
    }

    *(m_array + index) = item;
    m_size++;
}

template <class T>
void vector<T>::prepend(const T& item)
{
    insert(0, item);
}

template <class T>
T vector<T>::pop()
{
    if (!m_size)
        throw std::logic_error("Cannot pop from an empty vector");

    T ret = *(m_array + m_size - 1);
    post_delete_actions();
    return ret;
}

template <class T>
void vector<T>::erase_at(const size_t index)
{
    if (!m_size || index >= m_size)
        throw std::out_of_range("Out of range index to delete item.");

    if (index == m_size - 1)
    {
        pop();
        return;
    }

    for (size_t i = index; i < m_size - 1; ++i)
        *(m_array + i) = *(m_array + i + 1);

    post_delete_actions();

    return;
}

template <class T>
int vector<T>::find(const T& item)
{
    if (!m_size)
        return -1;

    for (size_t i = 0; i < m_size; ++i)
    {
        if (m_comparator(*(m_array + i), item))
            return i;
    }

    return -1;
}

template <class T>
void vector<T>::remove(const T& item)
{
    if (!m_size)
        return;

    int index = 0;
    while (-1 != (index = find_from_index(index, item)))
        erase_at(index);

    return;
}

template <class T>
int vector<T>::find_from_index(const size_t index, const T& item)
{
    if (!m_size || index >= m_size)
        return -1;

    for (size_t i = index; i < m_size; ++i)
    {
        if (m_comparator(*(m_array + i), item))
            return i;
    }

    return -1;
}

template <class T>
void vector<T>::resize(const size_t new_capacity)
{
    if (new_capacity < m_size)
        throw std::logic_error("Loss of data due to resizing");

    T* temp_array = new T[new_capacity];
    for (size_t i = 0; i < m_size; ++i)
    {
        *(temp_array + i) = *(m_array + i);
    }

    delete[] m_array;
    m_array = temp_array;

    m_capacity = new_capacity;
}

template <class T>
void vector<T>::check_resize(bool will_add)
{
    if (will_add && m_size >= m_capacity)
    {
        resize(m_capacity * 2);
    }
    else if (!will_add && m_size && m_size <= m_capacity / 4)
    {
        resize(m_capacity / 2);
    }
}

template <class T>
inline void vector<T>::post_delete_actions()
{
    m_size--;
    check_resize(false);
}

} // namespace orla
