/**
 * @file avl_tree.h
 */

#ifndef FOREST_AVL_TREE_H
#define FOREST_AVL_TREE_H

#include <iostream>
#include <algorithm>
#include <queue>
#include <fstream>
#include <memory>

/**
 * @brief The forest library namespace
 */
namespace forest {
  namespace avl {
    template <typename key_t>
    struct node {
      key_t key;                     ///< The key of the node
      int balance_factor;            ///< The avl tree balance factor of this node
      std::weak_ptr<node> parent;    ///< The parent of the node
      std::shared_ptr<node> left;    ///< The left child of the node
      std::shared_ptr<node> right;   ///< The right child of the node
      node(const key_t key) {
        this->key = key;
        this->parent.reset();
        this->left = nullptr;
        this->right = nullptr;
      }
    };
    template <typename key_t>
    class tree {
    private:
      std::shared_ptr<node <key_t> > root;
      void pre_order_traversal(std::shared_ptr<node <key_t> > &x, void handler(std::shared_ptr<node <key_t> >)) {
        if (x == nullptr) return;
        handler(x);
        pre_order_traversal(x->left, handler);
        pre_order_traversal(x->right, handler);
      }
      void in_order_traversal(std::shared_ptr<node <key_t> > &x, void handler(std::shared_ptr<node <key_t> >)) {
        if (x == nullptr) return;
        in_order_traversal(x->left, handler);
        handler(x);
        in_order_traversal(x->right, handler);
      }
      void post_order_traversal(std::shared_ptr<node <key_t> > &x, void handler(std::shared_ptr<node <key_t> >)) {
        if (x == nullptr) return;
        post_order_traversal(x->left, handler);
        post_order_traversal(x->right, handler);
        handler(x);
      }
      void breadth_first_traversal(std::shared_ptr<node <key_t> > &x, void handler(std::shared_ptr<node <key_t> >)) {
        std::queue <std::shared_ptr<node <key_t> > > queue;
        if (x == nullptr) return;
        queue.push(x);
        while(queue.empty() == false) {
          std::shared_ptr<node <key_t> > y = queue.front();
          handler(y);
          queue.pop();
          if (y->left != nullptr) queue.push(y->left);
          if (y->right != nullptr) queue.push(y->right);
        }
      }
      const unsigned long long height(std::shared_ptr<node <key_t> > &x) {
        if (x == nullptr) return 0;
        return std::max(height(x->left), height(x->right)) + 1;
      }
      const unsigned long long size(std::shared_ptr<node <key_t> > &x) {
        if (x == nullptr) return 0;
        return size(x->left) + size(x->right) + 1;
      }
      void rotate_right(std::shared_ptr<node <key_t> > &rotation_root) {
        std::shared_ptr<node <key_t> > new_root = rotation_root->left;
        std::shared_ptr<node <key_t> > orphan_subtree = new_root->right;

        rotation_root->left = orphan_subtree;
        if (orphan_subtree != nullptr) {
          orphan_subtree->parent = rotation_root;
        }

        new_root->right = rotation_root;

        if (rotation_root->parent.lock() == nullptr) {
          root = new_root;
        } else if(rotation_root == rotation_root->parent.lock()->left) {
          rotation_root->parent.lock()->left = new_root;
        } else if (rotation_root == rotation_root->parent.lock()->right) {
          rotation_root->parent.lock()->right = new_root;
        }
        new_root->parent = rotation_root->parent;
        rotation_root->parent = new_root;
      }
      void rotate_left(std::shared_ptr<node <key_t> >  &rotation_root) {
        std::shared_ptr<node <key_t> >  new_root = rotation_root->right;
        std::shared_ptr<node <key_t> >  orphan_subtree = new_root->left;

        rotation_root->right = orphan_subtree;
        if (orphan_subtree != nullptr) {
          orphan_subtree->parent = rotation_root;
        }

        new_root->left = rotation_root;

        if (rotation_root->parent.lock() == nullptr) {
          root = new_root;
        } else if(rotation_root == rotation_root->parent.lock()->left) {
          rotation_root->parent.lock()->left = new_root;
        } else {
          rotation_root->parent.lock()->right = new_root;
        }
        new_root->parent = rotation_root->parent;
        rotation_root->parent = new_root;
      }
    public:
      tree() {
        root = nullptr;
      }
      ~tree() {

      }
      /**
       * @brief Performs a Pre Order Traversal starting from the root node
       * @return void
       */
      void pre_order_traversal(void handler(std::shared_ptr<node <key_t> >)) {
        pre_order_traversal(root, handler);
      }
      /**
       * @brief Performs a In Order Traversal starting from the root node
       * @return void
       */
      void in_order_traversal(void handler(std::shared_ptr<node <key_t> >)) {
        in_order_traversal(root, handler);
      }
      /**
       * @brief Performs a Post Order Traversal starting from the root node
       * @return void
       */
      void post_order_traversal(void handler(std::shared_ptr<node <key_t> >)) {
        post_order_traversal(root, handler);
      }
      /**
       * @brief Performs a Breadth First Traversal starting from the root node
       * @return void
       */
      void breadth_first_traversal(void handler(std::shared_ptr<node <key_t> >)) {
        breadth_first_traversal(root, handler);
      }
      /**
       * @brief Inserts a new node into the avl tree
       * @param key The key for the new node
       * @return The inserted node otherwise nullptr
       */
      const std::shared_ptr<node <key_t> > insert(const key_t key) {
        std::shared_ptr<node <key_t> >  current = root;
        std::shared_ptr<node <key_t> >  parent = nullptr;
        std::shared_ptr<node <key_t> >  inserted_node;

        while (current != nullptr) {
          parent = current;
          if (key > current->key) {
            current = current->right;
          } else if (key < current->key) {
            current = current->left;
          } else {
            return nullptr;
          }
        }

        current = std::make_shared<node <key_t> >(key);
        current->parent = parent;

        if(parent == nullptr) {
          root = current;
        } else if (current->key > parent->key) {
          parent->right = current;
        } else if (current->key < parent->key) {
          parent->left = current;
        }

        inserted_node = current;

        // Re-trace up the tree
        while (current != nullptr) {
          current->balance_factor = (height(current->right) - height(current->left));
          if (current->balance_factor == -2) {
            // If left subtree is right heavy -- "double right"
            if (current->left->balance_factor == 1) {
              rotate_left(current->left);
            }
            rotate_right(current);
          } else if (current->balance_factor == 2) {
            // If right subtree is left heavy -- "double left"
            if (current->right->balance_factor == -1) {
              rotate_right(current->right);
            }
            rotate_left(current);
          }
          current = current->parent.lock();
        }

        return inserted_node;
      }
      /**
       * @brief Performs a binary search starting from the root node
       * @return The node with the key specified otherwise nullptr
       */
      const std::shared_ptr<node <key_t> > search(const key_t key) {
        std::shared_ptr<node <key_t> > x = root;
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
      const std::shared_ptr<node <key_t> > minimum() {
        std::shared_ptr<node <key_t> > x = root;
        if (x == nullptr) return nullptr;
        while(x->left != nullptr) x = x->left;
        return x;
      }
      /**
       * @brief Finds the node with the maximum key
       * @return The node with the maximum key otherwise nullptr
       */
      const std::shared_ptr<node <key_t> > maximum() {
        std::shared_ptr<node <key_t> > x = root;
        if (x == nullptr) return nullptr;
        while(x->right != nullptr) x = x->right;
        return x;
      }
      /**
       * @brief Finds the successor of the node with key specified
       * @return The successor of the node with key specified otherwise nullptr
       */
      const std::shared_ptr<node <key_t> > successor(const key_t key) {
        std::shared_ptr<node <key_t> > x = root;
        while (x != nullptr) {
          if (key > x->key) {
            x = x->right;
          } else if (key < x->key) {
            x = x->left;
          } else {
            if (x->right != nullptr) {
              x = x->right;
              while(x->left != nullptr) x = x->left;
              return x;
            }
            std::shared_ptr<node <key_t> > parent = x->parent.lock();
            while (parent != nullptr && x == parent->right) {
              x = parent;
              parent = parent->parent.lock();
            }
            return parent;
          }
        }
        return nullptr;
      }
      /**
       * @brief Finds the predecessor of the node with key specified
       * @return The predecessor of the node with key specified otherwise nullptr
       */
      const std::shared_ptr<node <key_t> > predecessor(const key_t key) {
        std::shared_ptr<node <key_t> > x = root;
        while (x != nullptr) {
          if (key > x->key) {
            x = x->right;
          } else if (key < x->key) {
            x = x->left;
          } else {
            if (x->left != nullptr) {
              x = x->left;
              while(x->right != nullptr) x = x->right;
              return x;
            }
            std::shared_ptr<node <key_t> > parent = x->parent.lock();
            while (parent != nullptr && x == parent->left) {
              x = parent;
              parent = parent->parent.lock();
            }
            return parent;
          }
        }
        return nullptr;
      }
      /**
       * @brief Finds the height of the tree
       * @return The height of the avl tree
       */
      const unsigned long long height() {
        return height(root);
      }
      /**
       * @brief Finds the size of the tree
       * @return The size of the avl tree
       */
      const unsigned long long size() {
        return size(root);
      }
      /**
       * @brief Finds if the avl tree is empty
       * @return true if the avl tree is empty and false otherwise
       */
      const bool empty() noexcept{
        if (root == nullptr) {
          return true;
        } else {
          return false;
        }
      }
    };
  }
}

#endif
