#include <forest/AVL_tree.h>
#include <iostream>

int main(int argc, char const *argv[]) {
        forest::AVL_tree <int, int> AVL_tree;

        AVL_tree.insert(2,0);
        AVL_tree.insert(4,0);
        AVL_tree.insert(90,0);
        AVL_tree.insert(3,100);
        AVL_tree.insert(0,0);
        AVL_tree.insert(14,0);
        AVL_tree.insert(45,0);

        std::cout << "Pre Order Traversal" << std::endl;
        std::cout << std::endl;
        AVL_tree.pre_order_traversal();
        std::cout << std::endl;

        std::cout << "In Order Traversal" << std::endl;
        std::cout << std::endl;
        AVL_tree.in_order_traversal();
        std::cout << std::endl;

        std::cout << "Post Order Traversal" << std::endl;
        std::cout << std::endl;
        AVL_tree.post_order_traversal();
        std::cout << std::endl;

        std::cout << "Breadth First Traversal" << std::endl;
        std::cout << std::endl;
        AVL_tree.breadth_first_traversal();
        std::cout << std::endl;

        auto min = AVL_tree.minimum();
        if (min != nullptr) {
                std::cout << "Minimum: " << min->key << std::endl;
        }

        auto max = AVL_tree.maximum();
        if (max != nullptr) {
                std::cout << "Maximum: " << max->key << std::endl;
        }

        std::cout << "Height: " << AVL_tree.height() << std::endl;

        std::cout << "Size: " << AVL_tree.size() << std::endl;

	std::cout << "Empty: " << (AVL_tree.empty() ? "yes" : "no") << std::endl;

        auto n = AVL_tree.search(3);
        if (n != nullptr) {
                std::cout << std::endl;
                std::cout << "Found node with key 3" << std::endl;
                std::cout << std::endl;
                n->info();
        }

        AVL_tree.graphviz("AVL_tree.dot");

        return 0;
}
