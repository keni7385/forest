#include <forest/avl_tree.h>
#include <iostream>

int main(int argc, char const *argv[]) {
        forest::avl_tree <int, int> avl_tree;

        avl_tree.insert(2,0);
        avl_tree.insert(4,0);
        avl_tree.insert(90,0);
        avl_tree.insert(3,100);
        avl_tree.insert(0,0);
        avl_tree.insert(14,0);
        avl_tree.insert(45,0);

        std::cout << "Pre Order Traversal" << std::endl;
        std::cout << std::endl;
        avl_tree.pre_order_traversal();
        std::cout << std::endl;

        std::cout << "In Order Traversal" << std::endl;
        std::cout << std::endl;
        avl_tree.in_order_traversal();
        std::cout << std::endl;

        std::cout << "Post Order Traversal" << std::endl;
        std::cout << std::endl;
        avl_tree.post_order_traversal();
        std::cout << std::endl;

        std::cout << "Breadth First Traversal" << std::endl;
        std::cout << std::endl;
        avl_tree.breadth_first_traversal();
        std::cout << std::endl;

        auto min = avl_tree.minimum();
        if (min != nullptr) {
                std::cout << "Minimum: " << min->key << std::endl;
        }

        auto max = avl_tree.maximum();
        if (max != nullptr) {
                std::cout << "Maximum: " << max->key << std::endl;
        }

        std::cout << "Height: " << avl_tree.height() << std::endl;

        std::cout << "Size: " << avl_tree.size() << std::endl;

	std::cout << "Empty: " << (avl_tree.empty() ? "yes" : "no") << std::endl;

        auto n = avl_tree.search(3);
        if (n != nullptr) {
                std::cout << std::endl;
                std::cout << "Found node with key 3" << std::endl;
                std::cout << std::endl;
                n->info();
        }

        avl_tree.graphviz("avl_tree.dot");

        return 0;
}
