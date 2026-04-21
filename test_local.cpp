#include "template.h"
#include <iostream>
#include <cassert>

void test_basic() {
    sjtu::resetMemory();

    // Test 1: Single allocation
    auto* b1 = sjtu::allocate(100);
    assert(b1 != nullptr);
    assert(b1->size == 100);
    assert(b1->is_free == false);
    assert(b1->address == 0);

    std::cout << "Test basic allocation passed!" << std::endl;
}

void test_multiple() {
    sjtu::resetMemory();

    auto* b1 = sjtu::allocate(100);
    auto* b2 = sjtu::allocate(200);

    assert(b1 != nullptr);
    assert(b2 != nullptr);
    assert(b1->size == 100);
    assert(b2->size == 200);
    assert(b2->address == 100 + sizeof(sjtu::MemoryBlock));

    std::cout << "Test multiple allocations passed!" << std::endl;
}

void test_deallocate() {
    sjtu::resetMemory();

    auto* b1 = sjtu::allocate(100);
    auto* b2 = sjtu::allocate(200);
    sjtu::deallocate(b1);

    assert(b1->is_free == true);

    // Should reuse b1
    auto* b3 = sjtu::allocate(50);
    assert(b3 == b1);
    assert(b3->size == 50);

    std::cout << "Test deallocate and reuse passed!" << std::endl;
}

void test_merge() {
    sjtu::resetMemory();

    auto* b1 = sjtu::allocate(100);
    auto* b2 = sjtu::allocate(200);
    auto* b3 = sjtu::allocate(300);

    size_t size_b1 = b1->size;
    size_t size_b2 = b2->size;

    sjtu::deallocate(b2);
    sjtu::deallocate(b1);

    // b1 and b2 should be merged because b1's next was b2 and both are now free
    // Wait, my deallocate only merges with next.
    // When deallocate(b2), it checks b3 (not free).
    // When deallocate(b1), it checks b2 (free) and merges.

    assert(b1->size == size_b1 + sizeof(sjtu::MemoryBlock) + size_b2);
    assert(b1->next == b3);

    std::cout << "Test merge passed!" << std::endl;
}

int main() {
    test_basic();
    test_multiple();
    test_deallocate();
    test_merge();
    std::cout << "All local tests passed!" << std::endl;
    return 0;
}
