#include <cassert>
#include "vector.hpp"

bool int_vec_comparator(const int& a, const int& b)
{
    return a == b;
}

void test_vector()
{
    ::orla::vector<int> vec(int_vec_comparator);

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

int main()
{
    test_vector();
    return 0;
}