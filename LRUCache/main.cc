// main.cpp
// To compile (e.g., with g++): g++ main.cpp -o lru_cache_demo -std=c++11
// Then run: ./lru_cache_demo

#include "LRUCache.h" // If LRUCache.hpp is in a separate file
#include <iostream>

int main() {
    std::cout << "LRU Cache Demonstration" << std::endl;
    std::cout << "-----------------------" << std::endl;

    // Create an LRU Cache with capacity 2
    LRUCache cache(2);
    std::cout << "Initialized Cache with capacity 2." << std::endl;

    // put(1, 10)
    cache.put(1, 10);
    std::cout << "put(1, 10)" << std::endl;
    cache.printCacheState(); // Expected: [1:10]

    // put(2, 20)
    cache.put(2, 20);
    std::cout << "put(2, 20)" << std::endl;
    cache.printCacheState(); // Expected: [2:20] [1:10]

    // get(1)
    std::cout << "get(1): " << cache.get(1) << std::endl; // Expected: 10
    cache.printCacheState(); // Expected: [1:10] [2:20] (1 becomes MRU)

    // put(3, 30) - This will evict key 2 (LRU)
    cache.put(3, 30);
    std::cout << "put(3, 30)" << std::endl;
    cache.printCacheState(); // Expected: [3:30] [1:10]

    // get(2)
    std::cout << "get(2): " << cache.get(2) << std::endl; // Expected: -1 (not found as it was evicted)
    cache.printCacheState(); // Expected: [3:30] [1:10]

    // put(4, 40) - This will evict key 1 (LRU)
    cache.put(4, 40);
    std::cout << "put(4, 40)" << std::endl;
    cache.printCacheState(); // Expected: [4:40] [3:30]

    // get(1)
    std::cout << "get(1): " << cache.get(1) << std::endl; // Expected: -1 (not found)
    cache.printCacheState();

    // get(3)
    std::cout << "get(3): " << cache.get(3) << std::endl; // Expected: 30
    cache.printCacheState(); // Expected: [3:30] [4:40] (3 becomes MRU)

    // get(4)
    std::cout << "get(4): " << cache.get(4) << std::endl; // Expected: 40
    cache.printCacheState(); // Expected: [4:40] [3:30] (4 becomes MRU)

    std::cout << "-----------------------" << std::endl;
    std::cout << "Testing with capacity 1:" << std::endl;
    LRUCache cache_cap1(1);
    cache_cap1.put(1,1);
    cache_cap1.printCacheState(); // [1:1]
    cache_cap1.put(2,2); // evicts 1
    cache_cap1.printCacheState(); // [2:2]
    std::cout << "get(1): " << cache_cap1.get(1) << std::endl; // -1
    std::cout << "get(2): " << cache_cap1.get(2) << std::endl; // 2
    cache_cap1.printCacheState(); // [2:2]

    std::cout << "-----------------------" << std::endl;
    std::cout << "Testing with capacity 0 (should not store anything):" << std::endl;
    LRUCache cache_cap0(0);
    cache_cap0.put(1,1);
    cache_cap0.printCacheState(); // Cache (MRU -> LRU): \n Map size: 0
    std::cout << "get(1): " << cache_cap0.get(1) << std::endl; // -1


    return 0;
}

