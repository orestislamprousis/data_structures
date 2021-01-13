#include <cassert>
#include "vector.hpp"
#include "doubly_linked_list.hpp"
#include "singly_linked_list.hpp"

bool int_comparator(const int& a, const int& b)
{
    return a == b;
}

void test_vector()
{
    ::orla::vector<int> vec(int_comparator);

    assert(vec.is_empty());
    assert(vec.capacity() == ::orla::initial_vector_capacity);

    vec.push(1);
    vec.push(2);
    assert(vec.size() == 2);
    assert(vec.at(0) == 1);
    assert(vec.at(1) == 2);

    vec.insert(1, 3);
    assert(vec.at(1) == 3);
    assert(vec.at(2) == 2);

    vec.prepend(4);
    assert(vec.at(0) == 4);
    assert(vec.at(1) == 1);
    assert(vec.at(2) == 3);
    assert(vec.at(3) == 2);
    assert(vec.size() == 4);
    assert(vec.capacity() == ::orla::initial_vector_capacity);

    assert(vec.find(3) == 2);

    vec.remove(3);
    assert(vec.find(3) == -1);
    assert(vec.size() == 3);
    assert(vec.at(2) == 2);
    assert(vec.capacity() == 8);

    assert(vec.find(1) == 1);
    vec.erase_at(1);
    assert(vec.find(1) == -1);
    assert(vec.size() == 2);
    assert(vec.capacity() == 4);
    assert(vec.at(1) == 2);

    int popped = vec.pop();
    assert(popped == 2);
    assert(vec.size() == 1);
    assert(vec.capacity() == 2);
    assert(vec.at(0) == 4);

    /* test insertion at the end */
    vec.insert(1, 5);
    assert(vec.size() == 2);
    assert(vec.capacity() == 2);
    assert(vec.at(0) == 4);
    assert(vec.at(1) == 5);

    /* test capacity doubled */
    vec.push(4);
    assert(vec.capacity() == 4);

    /* test mutltiple removed */
    vec.remove(4);
    assert(vec.size() == 1);
    assert(vec.at(0) == 5);
    assert(vec.capacity() == 2);
    assert(!vec.is_empty());

    /* test empty vector capacity unchanged */
    vec.pop();
    assert(vec.size() == 0);
    assert(vec.is_empty());
    assert(vec.capacity() == 2);
}

void test_doubly_linked_list()
{
    ::orla::doubly_linked_list<int> list(int_comparator);
    assert(list.is_empty());

    list.insert(0, 1);
    assert(list.size() == 1);
    int res = list.pop_back();
    assert(res == 1);
    assert(list.is_empty());

    list.insert(0, 1);
    res = list.pop_front();
    assert(res == 1);
    assert(list.is_empty());

    list.push_front(2);
    list.push_front(1);
    assert(!list.is_empty());
    assert(list.size() == 2);
    assert(list.value_at(0) == 1);
    assert(list.value_at(1) == 2);

    res = list.pop_front();
    assert(res == 1);
    assert(list.size() == 1);
    assert(list.value_at(0) == 2);
    res = list.pop_front();
    assert(res == 2);
    assert(list.size() == 0);

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    assert(list.size() == 3);
    assert(list.value_at(0) == 1);
    assert(list.value_at(1) == 2);
    assert(list.value_at(2) == 3);

    res = list.pop_back();
    assert(res == 3);
    assert(list.size() == 2);

    res = list.front();
    assert(res == 1);

    res = list.back();
    assert(res == 2);

    list.insert(0, 0);
    res = list.front();
    assert(res == 0);
    assert(list.size() == 3);

    list.insert(3, 3);
    res = list.back();
    assert(res == 3);
    assert(list.size() == 4);

    list.insert(2, 4);
    assert(list.value_at(0) == 0);
    assert(list.value_at(1) == 1);
    assert(list.value_at(2) == 4);
    assert(list.value_at(3) == 2);
    assert(list.value_at(4) == 3);
    assert(list.size() == 5);

    list.erase(2);
    assert(list.size() == 4);
    assert(list.value_at(0) == 0);
    assert(list.value_at(1) == 1);
    assert(list.value_at(2) == 2);
    assert(list.value_at(3) == 3);

    list.erase(0);
    assert(list.size() == 3);
    assert(list.value_at(0) == 1);
    assert(list.value_at(1) == 2);
    assert(list.value_at(2) == 3);

    res = list.value_n_from_end(0);
    assert(res == 3);
    res = list.value_n_from_end(1);
    assert(res == 2);
    res = list.value_n_from_end(2);
    assert(res == 1);

    list.reverse();
    assert(list.size() == 3);
    assert(list.value_at(0) == 3);
    assert(list.value_at(1) == 2);
    assert(list.value_at(2) == 1);
    assert(list.front() == 3);
    assert(list.back() == 1);

    list.reverse();
    assert(list.size() == 3);
    assert(list.value_at(0) == 1);
    assert(list.value_at(1) == 2);
    assert(list.value_at(2) == 3);

    list.remove_value(2);
    assert(list.size() == 2);
    assert(list.value_at(0) == 1);
    assert(list.value_at(1) == 3);

    list.remove_value(1);
    assert(list.size() == 1);
    assert(list.value_at(0) == 3);

    list.remove_value(3);
    assert(list.size() == 0);
}

void test_singly_linked_list()
{
    ::orla::singly_linked_list<int> list(int_comparator);
    assert(list.is_empty());

    list.insert(0, 1);
    assert(list.size() == 1);
    int res = list.pop_back();
    assert(res == 1);
    assert(list.is_empty());

    list.insert(0, 2);
    res = list.pop_front();
    assert(res == 2);
    assert(list.is_empty());

    list.push_front(2);
    list.push_front(1);
    assert(!list.is_empty());
    assert(list.size() == 2);
    assert(list.value_at(0) == 1);
    assert(list.value_at(1) == 2);

    res = list.pop_front();
    assert(res == 1);
    assert(list.size() == 1);
    assert(list.value_at(0) == 2);
    res = list.pop_front();
    assert(res == 2);
    assert(list.size() == 0);

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    assert(list.size() == 3);
    assert(list.value_at(0) == 1);
    assert(list.value_at(1) == 2);
    assert(list.value_at(2) == 3);

    res = list.pop_back();
    assert(res == 3);
    assert(list.size() == 2);

    res = list.front();
    assert(res == 1);

    res = list.back();
    assert(res == 2);

    list.insert(0, 0);
    res = list.front();
    assert(res == 0);
    assert(list.size() == 3);

    list.insert(3, 3);
    res = list.back();
    assert(res == 3);
    assert(list.size() == 4);

    list.insert(2, 4);
    assert(list.value_at(0) == 0);
    assert(list.value_at(1) == 1);
    assert(list.value_at(2) == 4);
    assert(list.value_at(3) == 2);
    assert(list.value_at(4) == 3);
    assert(list.size() == 5);

    list.erase(2);
    assert(list.size() == 4);
    assert(list.value_at(0) == 0);
    assert(list.value_at(1) == 1);
    assert(list.value_at(2) == 2);
    assert(list.value_at(3) == 3);

    list.erase(0);
    assert(list.size() == 3);
    assert(list.value_at(0) == 1);
    assert(list.value_at(1) == 2);
    assert(list.value_at(2) == 3);

    res = list.value_n_from_end(0);
    assert(res == 3);
    res = list.value_n_from_end(1);
    assert(res == 2);
    res = list.value_n_from_end(2);
    assert(res == 1);

    list.reverse();
    assert(list.size() == 3);
    assert(list.value_at(0) == 3);
    assert(list.value_at(1) == 2);
    assert(list.value_at(2) == 1);
    assert(list.front() == 3);
    assert(list.back() == 1);

    list.reverse();
    assert(list.size() == 3);
    assert(list.value_at(0) == 1);
    assert(list.value_at(1) == 2);
    assert(list.value_at(2) == 3);

    list.remove_value(2);
    assert(list.size() == 2);
    assert(list.value_at(0) == 1);
    assert(list.value_at(1) == 3);

    list.remove_value(1);
    assert(list.size() == 1);
    assert(list.value_at(0) == 3);

    list.remove_value(3);
    assert(list.size() == 0);
}

int main()
{
    test_vector();
    test_doubly_linked_list();
    test_singly_linked_list();
    return 0;
}