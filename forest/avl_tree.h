/**
 * @file avl_tree.h
 */

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <algorithm>
#include <queue>
#include <fstream>

/**
 * @brief The forest library namespace
 */
namespace forest {
        template <typename key_t, typename value_t>
        struct avl_tree_node {
                key_t key;     ///< The key of the node
                value_t value; ///< The value of the node
                int balance_factor; ///< The avl tree balance factor of this node
                avl_tree_node *parent;  ///< A pointer to the parent of the node
                avl_tree_node *left;    ///< A pointer to the left child of the node
                avl_tree_node *right;   ///< A pointer to the right child of the node
                /**
                 * @brief Constructor of an avl tree node
                 */
                avl_tree_node(key_t key, value_t value) {
                        this->key = key;
                        this->value = value;
                        this->parent = nullptr;
                        this->left = nullptr;
                        this->right = nullptr;
                }
                /**
                 * @brief Prints information about the avl tree node to the std::cout
                 * @return void
                 */
                void info() const {
                        std::cout << this->key << "\t";
                        if (this->left != nullptr) {
                                std::cout << this->left->key << "\t";
                        } else {
                                std::cout << "null" << "\t";
                        }
                        if (this->right != nullptr) {
                                std::cout << this->right->key << "\t";
                        } else {
                                std::cout << "null" << "\t";
                        }
                        if (this->parent != nullptr) {
                                std::cout << this->parent->key << std::endl;
                        } else {
                                std::cout << "null" << std::endl;
                        }
                }
        };
        template <typename key_t, typename value_t>
        class avl_tree {
        private:
                avl_tree_node <key_t, value_t> *root;
                void pre_order_traversal(avl_tree_node <key_t, value_t> *x) {
                        if (x == nullptr) return;
                        x->info();
                        pre_order_traversal(x->left);
                        pre_order_traversal(x->right);
                }
                void in_order_traversal(avl_tree_node <key_t, value_t> *x) {
                        if (x == nullptr) return;
                        in_order_traversal(x->left);
                        x->info();
                        in_order_traversal(x->right);
                }
                void post_order_traversal(avl_tree_node <key_t, value_t> *x) {
                        if (x == nullptr) return;
                        post_order_traversal(x->left);
                        post_order_traversal(x->right);
                        x->info();
                }
                void breadth_first_traversal(avl_tree_node <key_t, value_t> *x) {
                        std::queue <avl_tree_node <key_t, value_t> *> queue;
                        if (x == nullptr) return;
                        queue.push(x);
                        while(queue.empty() == false) {
                                avl_tree_node <key_t, value_t> *y = queue.front();
                                y->info();
                                queue.pop();
                                if (y->left != nullptr) queue.push(y->left);
                                if (y->right != nullptr) queue.push(y->right);
                        }
                }
                unsigned long long height(avl_tree_node <key_t, value_t> *x) {
                        if (x == nullptr) return 0;
                        return std::max(height(x->left), height(x->right)) + 1;
                }
                unsigned long long size(avl_tree_node <key_t, value_t> *x) {
                        if (x == nullptr) return 0;
                        return size(x->left) + size(x->right) + 1;
                }
                void graphviz(std::ofstream &file, avl_tree_node <key_t, value_t> *x, unsigned long long *count) {
                        if (x == nullptr) return;
                        graphviz(file, x->left, count);
                        if (x->left != nullptr) {
                                file << "\t" << x->key << " -> " << x->left->key << ";" << std::endl;
                        } else {
                                file << "\t" << "null" << *count << " " << "[shape=point]" << ";" << std::endl;
                                file << "\t" << x->key << " -> " << "null" << *count << ";" << std::endl;
                                (*count)++;
                        }
                        if (x->right != nullptr) {
                                file << "\t" << x->key << " -> " << x->right->key << ";" << std::endl;
                        } else {
                                file << "\t" << "null" << *count << " " << "[shape=point]" << ";" << std::endl;
                                file << "\t" << x->key << " -> " << "null" << *count << ";" << std::endl;
                                (*count)++;
                        }
                        graphviz(file, x->right, count);
                }
                void rotate_right(avl_tree_node <key_t, value_t> * rotation_root) {
                    avl_tree_node <key_t, value_t> * new_root = rotation_root->left;
                    avl_tree_node <key_t, value_t> * orphan_subtree = new_root->right;

                    rotation_root->left = orphan_subtree;
                    if (orphan_subtree != nullptr) {
                        orphan_subtree->parent = rotation_root;
                    }

                    new_root->right = rotation_root;

                    if (rotation_root->parent == nullptr) {
                        root = new_root;
                    } else if(rotation_root == rotation_root->parent->left) {
                        rotation_root->parent->left = new_root;
                    } else if (rotation_root == rotation_root->parent->right) {
                        rotation_root->parent->right = new_root;
                    }
                    new_root->parent = rotation_root->parent;
                    rotation_root->parent = new_root;
                }
                void rotate_left(avl_tree_node <key_t, value_t> * rotation_root) {
                    avl_tree_node <key_t, value_t> * new_root = rotation_root->right;
                    avl_tree_node <key_t, value_t> * orphan_subtree = new_root->left;

                    rotation_root->right = orphan_subtree;
                    if (orphan_subtree != nullptr) {
                        orphan_subtree->parent = rotation_root;
                    }

                    new_root->left = rotation_root;

                    if (rotation_root->parent == nullptr) {
                        root = new_root;
                    } else if(rotation_root == rotation_root->parent->left) {
                        rotation_root->parent->left = new_root;
                    } else {
                        rotation_root->parent->right = new_root;
                    }
                    new_root->parent = rotation_root->parent;
                    rotation_root->parent = new_root;
                }
                const avl_tree_node <key_t, value_t> * insert(
                    avl_tree_node <key_t, value_t> * current, 
                    avl_tree_node <key_t, value_t> * parent, 
                    key_t key, 
                    value_t value) {

                    const avl_tree_node <key_t, value_t> * inserted_node;    

                    if (current == nullptr) {
                        current = new avl_tree_node <key_t, value_t> (key, value);
                        inserted_node = current;
                        current->parent = parent;

                        if(parent == nullptr) {
                            root = current;
                        }
                        else if (current->key > parent->key) {
                                parent->right = current;
                        } else if (current->key < parent->key) {
                                parent->left = current;
                        }

                    } else if (key > current->key) {
                        inserted_node = insert(current->right, current, key, value);
                    } else if (key < current->key) {
                        inserted_node = insert(current->left, current, key, value);
                    }

                    current->balance_factor = (height(current->right) - height(current->left));

                    // Rotate right
                    if (current->balance_factor == -2) {
                        // If left subtree is right heavy -- "double right"
                        if (current->left->balance_factor == 1) {
                            rotate_left(current->left);
                        }
                        rotate_right(current);
                    }
                    // Rotate left
                    else if (current->balance_factor == 2) {
                        // If right subtree is left heavy -- "double left"
                        if (current->right->balance_factor == -1) {
                            rotate_right(current->right);
                        }
                        rotate_left(current);
                    }
                    return inserted_node;
                }
        public:
                avl_tree() {
                        root = nullptr;
                }
                ~avl_tree() {

                }
                /**
                 * @brief Performs a Pre Order Traversal starting from the root node
                 * @return void
                 */
                void pre_order_traversal() {
                        pre_order_traversal(root);
                }
                /**
                 * @brief Performs a In Order Traversal starting from the root node
                 * @return void
                 */
                void in_order_traversal() {
                        in_order_traversal(root);
                }
                /**
                 * @brief Performs a Post Order Traversal starting from the root node
                 * @return void
                 */
                void post_order_traversal() {
                        post_order_traversal(root);
                }
                /**
                 * @brief Performs a Breadth First Traversal starting from the root node
                 * @return void
                 */
                void breadth_first_traversal() {
                        breadth_first_traversal(root);
                }
                /**
                 * @brief Generates a DOT file representing the AVL tree
                 * @param filename The filename of the .dot file
                 * @return void
                 */
                void graphviz(std::string filename) {
                        std::ofstream file;
                        unsigned long long count = 0;
                        file.open(filename);
                        file << "digraph {" << std::endl;
                        graphviz(file, root, &count);
                        file << "}" << std::endl;
                        file.close();
                }
                /**
                 * @brief Inserts a new node into the AVL tree
                 * @param key The key for the new node
                 * @param value The value for the new node
                 * @return The inserted node otherwise nullptr
                 */
                const avl_tree_node <key_t, value_t> * insert(key_t key, value_t value) {
                    return insert (root, nullptr, key, value);
                }
                /**
                 * @brief Performs a binary search starting from the root node
                 * @return The node with the key specified otherwise nullptr
                 */
                const avl_tree_node <key_t, value_t> *search(key_t key) {
                        avl_tree_node <key_t, value_t> *x = root;
                        while (x != nullptr) {
                                if (key > x->key) {
                                        x = x->right;
                                } else if (key < x->key) {
                                        x = x->left;
                                } else {
                                        return x;
                                }
                        }
                        return nullptr;
                }
                /**
                 * @brief Finds the node with the minimum key
                 * @return The node with the minimum key otherwise nullptr
                 */
                const avl_tree_node <key_t, value_t> *minimum() {
                        avl_tree_node <key_t, value_t> *x = root;
                        if (x == nullptr) return nullptr;
                        while(x->left != nullptr) x = x->left;
                        return x;
                }
                /**
                 * @brief Finds the node with the maximum key
                 * @return The node with the maximum key otherwise nullptr
                 */
                const avl_tree_node <key_t, value_t> *maximum() {
                        avl_tree_node <key_t, value_t> *x = root;
                        if (x == nullptr) return nullptr;
                        while(x->right != nullptr) x = x->right;
                        return x;
                }
                /**
                 * @brief Finds the height of the tree
                 * @return The height of the AVL tree
                 */
                unsigned long long height() {
                        return height(root);
                }
                /**
                 * @brief Finds the size of the tree
                 * @return The size of the AVL tree
                 */
                unsigned long long size() {
                        return size(root);
                }
                /**
                 * @brief Finds if the AVL tree is empty
                 * @return true if the AVL tree is empty and false otherwise
                 */
                bool empty() {
                        if (root == nullptr) {
                                return true;
                        } else {
                                return false;
                        }
                }
        };
}

#endif
