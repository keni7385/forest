#include <forest/red_black_tree.h>
#include <iostream>

int main(int argc, char const *argv[]) {
        forest::red_black_tree <int, int> red_black_tree;

        red_black_tree.insert(4,0);
        red_black_tree.insert(2,0);
        red_black_tree.insert(90,0);
        red_black_tree.insert(3,100);
        red_black_tree.insert(0,0);
        red_black_tree.insert(14,0);
        red_black_tree.insert(45,0);

        std::cout << "Pre Order Traversal" << std::endl;
        std::cout << std::endl;
        red_black_tree.pre_order_traversal();
        std::cout << std::endl;

        std::cout << "In Order Traversal" << std::endl;
        std::cout << std::endl;
        red_black_tree.in_order_traversal();
        std::cout << std::endl;

        std::cout << "Post Order Traversal" << std::endl;
        std::cout << std::endl;
        red_black_tree.post_order_traversal();
        std::cout << std::endl;

        std::cout << "Breadth First Traversal" << std::endl;
        std::cout << std::endl;
        red_black_tree.breadth_first_traversal();
        std::cout << std::endl;

        auto min = red_black_tree.minimum();
        if (min != nullptr) {
                std::cout << "Minimum: " << min->key << std::endl;
        }

        auto max = red_black_tree.maximum();
        if (max != nullptr) {
                std::cout << "Maximum: " << max->key << std::endl;
        }

        auto predecessor = red_black_tree.predecessor(90);
        if (predecessor != nullptr) {
                std::cout << "Predecessor of 90: " << predecessor->key << std::endl;
        }

        auto successor = red_black_tree.successor(3);
        if (successor != nullptr) {
                std::cout << "Successor of 3: " << successor->key << std::endl;
        }

        std::cout << "Height: " << red_black_tree.height() << std::endl;

        std::cout << "Size: " << red_black_tree.size() << std::endl;

	std::cout << "Empty: " << (red_black_tree.empty() ? "yes" : "no") << std::endl;

        auto n = red_black_tree.search(3);
        if (n != nullptr) {
                std::cout << std::endl;
                std::cout << "Found node with key 3" << std::endl;
                std::cout << std::endl;
                n->info();
        }

        red_black_tree.graphviz("red_black_tree.dot");

        return 0;
}
