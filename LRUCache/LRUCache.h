// LRUCache.hpp
#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <unordered_map> // For the hash map
#include <iostream>      // For debugging (optional)

// Node structure for the doubly linked list
struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;

    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int capacity_;
    std::unordered_map<int, Node*> cache_map_; // Stores key -> Node*
    Node* head_; // Dummy head of the doubly linked list
    Node* tail_; // Dummy tail of the doubly linked list

    // Private helper function to add a node right after the dummy head (MRU position)
    void _addNodeToHead(Node* node) {
        node->prev = head_;
        node->next = head_->next;
        head_->next->prev = node;
        head_->next = node;
    }

    // Private helper function to remove a node from the doubly linked list
    void _removeNode(Node* node) {
        if (node == nullptr) return; // Should not happen with proper logic
        Node* prev_node = node->prev;
        Node* next_node = node->next;
        prev_node->next = next_node;
        next_node->prev = prev_node;
    }

    // Private helper function to move an existing node to the head (MRU position)
    void _moveToHead(Node* node) {
        _removeNode(node);
        _addNodeToHead(node);
    }

    // Private helper function to remove the node right before the dummy tail (LRU element)
    // Returns the popped node to allow for its key to be removed from the map.
    Node* _popTail() {
        if (tail_->prev == head_) { // Cache is empty or only dummy nodes
            return nullptr;
        }
        Node* lru_node = tail_->prev;
        _removeNode(lru_node);
        return lru_node;
    }

public:
    // Constructor: Initializes the LRU cache with a given capacity.
    // Time Complexity: O(1)
    LRUCache(int capacity) : capacity_(capacity) {
        head_ = new Node(-1, -1); // Dummy head node
        tail_ = new Node(-1, -1); // Dummy tail node
        head_->next = tail_;
        tail_->prev = head_;
    }

    // Destructor: Frees all allocated memory for nodes.
    // Time Complexity: O(N) where N is the number of items in the cache at destruction.
    ~LRUCache() {
        Node* current = head_->next;
        while (current != tail_) {
            Node* next_node = current->next;
            delete current;
            current = next_node;
        }
        delete head_;
        delete tail_;
        // cache_map_ will be cleared automatically as it stores pointers,
        // and the pointed-to objects are deleted above.
    }

    // Get operation: Retrieves the value for a given key.
    // If the key exists, it moves the item to the MRU position.
    // Returns the value if found, otherwise -1.
    // Time Complexity: O(1) on average (due to unordered_map lookup)
    int get(int key) {
        // Check if key exists in the map
        if (cache_map_.find(key) == cache_map_.end()) {
            return -1; // Key not found
        }

        // Key found, retrieve the node
        Node* node = cache_map_[key];
        
        // Move the accessed node to the head (MRU position)
        _moveToHead(node);
        
        return node->value;
    }

    // Put operation: Inserts or updates a key-value pair.
    // If the key exists, its value is updated, and it's moved to MRU.
    // If the key doesn't exist, it's added. If capacity is exceeded, LRU item is evicted.
    // Time Complexity: O(1) on average
    void put(int key, int value) {
        if (capacity_ <= 0) return; // Cannot put anything in a zero or negative capacity cache

        // Check if key already exists in the map
        if (cache_map_.find(key) != cache_map_.end()) {
            // Key exists, update its value and move to head
            Node* node = cache_map_[key];
            node->value = value;
            _moveToHead(node);
        } else {
            // Key does not exist, create a new node
            Node* new_node = new Node(key, value);
            cache_map_[key] = new_node;
            _addNodeToHead(new_node);

            // Check if cache size exceeds capacity
            if (cache_map_.size() > capacity_) {
                // Evict the LRU item
                Node* lru_node = _popTail();
                if (lru_node != nullptr) {
                    cache_map_.erase(lru_node->key);
                    delete lru_node; // Free the memory of the evicted node
                }
            }
        }
    }

    // Optional: Helper to print the cache contents for debugging
    void printCacheState() const {
        Node* current = head_->next;
        std::cout << "Cache (MRU -> LRU): ";
        while (current != tail_) {
            std::cout << "[" << current->key << ":" << current->value << "] ";
            current = current->next;
        }
        std::cout << std::endl;
        std::cout << "Map size: " << cache_map_.size() << std::endl;
    }
};

#endif // LRU_CACHE_HPP
