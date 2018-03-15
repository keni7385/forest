#include "forest/binary_search_tree.h"
#include <iostream>

void handler(std::shared_ptr<forest::binary_search_tree_node <int> > x) {
        std::cout << x->key << "\t";
        if (x->left != nullptr) {
                std::cout << x->left->key << "\t";
        } else {
                std::cout << "null" << "\t";
        }
        if (x->right != nullptr) {
                std::cout << x->right->key << "\t";
        } else {
                std::cout << "null" << "\t";
        }
        if (x->parent.lock() != nullptr) {
                std::cout << x->parent.lock()->key << std::endl;
        } else {
                std::cout << "null" << std::endl;
        }
}

int main(int argc, char const *argv[]) {
        forest::binary_search_tree <int> binary_search_tree;

        binary_search_tree.insert(4);
        binary_search_tree.insert(2);
        binary_search_tree.insert(90);
        binary_search_tree.insert(3);
        binary_search_tree.insert(0);
        binary_search_tree.insert(14);
        binary_search_tree.insert(45);

        std::cout << "Pre Order Traversal" << std::endl;
        std::cout << std::endl;
        binary_search_tree.pre_order_traversal(handler);
        std::cout << std::endl;

        std::cout << "In Order Traversal" << std::endl;
        std::cout << std::endl;
        binary_search_tree.in_order_traversal(handler);
        std::cout << std::endl;

        std::cout << "Post Order Traversal" << std::endl;
        std::cout << std::endl;
        binary_search_tree.post_order_traversal(handler);
        std::cout << std::endl;

        std::cout << "Breadth First Traversal" << std::endl;
        std::cout << std::endl;
        binary_search_tree.breadth_first_traversal(handler);
        std::cout << std::endl;

        auto min = binary_search_tree.minimum();
        if (min != nullptr) {
                std::cout << "Minimum: " << min->key << std::endl;
        }

        auto max = binary_search_tree.maximum();
        if (max != nullptr) {
                std::cout << "Maximum: " << max->key << std::endl;
        }

        auto predecessor = binary_search_tree.predecessor(90);
        if (predecessor != nullptr) {
                std::cout << "Predecessor of 90: " << predecessor->key << std::endl;
        }

        auto successor = binary_search_tree.successor(3);
        if (successor != nullptr) {
                std::cout << "Successor of 3: " << successor->key << std::endl;
        }

        std::cout << "Height: " << binary_search_tree.height() << std::endl;

        std::cout << "Size: " << binary_search_tree.size() << std::endl;

	std::cout << "Empty: " << (binary_search_tree.empty() ? "yes" : "no") << std::endl;

        auto n = binary_search_tree.search(3);
        if (n != nullptr) {
                std::cout << std::endl;
                std::cout << "Found node with key 3" << std::endl;
        }

        return 0;
}
