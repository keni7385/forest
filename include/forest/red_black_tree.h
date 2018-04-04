/**
 * @file red_black_tree.h
 */

#ifndef FOREST_RED_BLACK_TREE_H
#define FOREST_RED_BLACK_TREE_H

#include <iostream>
#include <algorithm>
#include <queue>
#include <fstream>
#include <memory>

/**
 * @brief The forest library namespace
 */
namespace forest {
  namespace red_black {
    enum color_t {red, black};
    template <typename key_t>
    struct node {
      key_t key;                     ///< The key of the node
      color_t color;                 ///< The color of the node
      std::weak_ptr<node> parent;    ///< The parent of the node
      std::shared_ptr<node> left;    ///< The left child of the node
      std::shared_ptr<node> right;   ///< The right child of the node
      node(const key_t key, const color_t color) {
        this->key = key;
        this->color = color;
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
      void left_rotate(std::shared_ptr<node <key_t> > &x) {
        std::shared_ptr<node <key_t> > y = x->right;
        if(y != nullptr) {
          x->right = y->left;
          if(y->left != nullptr) y->left->parent = x;
          y->parent = x->parent;
        }
        if(x->parent.lock() == nullptr) {
          root = y;
        } else if (x == x->parent.lock()->left) {
          x->parent.lock()->left = y;
        } else {
          x->parent.lock()->right = y;
        }
        if(y != nullptr) {
          y->left = x;
        }
        x->parent = y;
      }
      void right_rotate(std::shared_ptr<node <key_t> > &x) {
        std::shared_ptr<node <key_t> > y = x->left;
        if (y != nullptr) {
          x->left = y->right;
          if (y->right != nullptr) y->right->parent = x;
          y->parent = x->parent;
        }
        if(x->parent.lock() == nullptr) {
          root = y;
        } else if (x == x->parent.lock()->left) {
          x->parent.lock()->left = y;
        } else {
          x->parent.lock()->right = y;
        }
        if(y != nullptr) {
          y->right = x;
        }
        x->parent = y;
      }
      std::shared_ptr<node <key_t> > find_sibling(std::shared_ptr<node <key_t> > &x) {
        if (x == find_parent(x)->left) {
          return find_parent(x)->right;
        } else if (x == find_parent(x)->right) {
          return find_parent(x)->left;
        }
        return nullptr;
      }
      std::shared_ptr<node <key_t> > find_parent(std::shared_ptr<node <key_t> > &x) {
        return x->parent.lock();
      }
      std::shared_ptr<node <key_t> > find_grand_parent(std::shared_ptr<node <key_t> > &x) {
        if (find_parent(x) != nullptr) {
          return find_parent(x)->parent.lock();
        }
        return nullptr;
      }
      std::shared_ptr<node <key_t> > find_uncle(std::shared_ptr<node <key_t> > &x) {
        if (find_grand_parent(x) != nullptr) {
          return find_sibling(find_parent(x));
        }
        return nullptr;
      }
      void fix(std::shared_ptr<node <key_t> > &x) {
        std::shared_ptr<node <key_t> > parent = nullptr;
        std::shared_ptr<node <key_t> > grand_parent = nullptr;
        while ((x != root) && (x->color != black) && (x->parent.lock()->color == red)) {
          parent = x->parent.lock();
          grand_parent = x->parent.lock()->parent.lock();
          /**
           * @brief Case A - Parent of x is left child of the grand parent of x
           */
          if (parent == grand_parent->left) {
            std::shared_ptr<node <key_t> > uncle = grand_parent->right;
            /**
             * @brief Case 1 - The uncle of x is also red. Only recoloring is required
             */
            if (uncle != nullptr && uncle->color == red) {
              grand_parent->color = red;
              parent->color = black;
              uncle->color = black;
              x = grand_parent;
            } else {
              /**
               * @brief Case 2 - x is right child of its parent. Left rotation is required
               */
              if (x == parent->right) {
                left_rotate(parent);
                x = parent;
                parent = x->parent.lock();
              }
              /**
               * @brief Case 3 - x is left child of its parent. Right rotation is required
               */
              right_rotate(grand_parent);
              std::swap(parent->color, grand_parent->color);
              x = parent;
            }
          } else {
            /**
             * @brief Case B - Parent of x is right child of the grand parent of x
             */
            std::shared_ptr<node <key_t> > uncle = grand_parent->left;
            /**
             * @brief Case 1 - The uncle of x is also red. Only recoloring required
             */
            if ((uncle != nullptr) && (uncle->color == red)) {
              grand_parent->color = red;
              parent->color = black;
              uncle->color = black;
              x = grand_parent;
            } else {
              /**
               * @brief Case 2 - x is left child of its parent. Right rotation is required
               */
              if (x == parent->left) {
                right_rotate(parent);
                x = parent;
                parent = x->parent.lock();
              }
              /**
               * @brief Case 3 - x is right child of its parent. Left rotation is required
               */
              left_rotate(grand_parent);
              std::swap(parent->color, grand_parent->color);
              x = parent;
            }
          }
        }
        root->color = black;
      }
    public:
      tree() {
        root = nullptr;
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
       * @brief Inserts a new node into the red black tree
       * @param key The key for the new node
       * @return The the inserted node otherwise nullptr
       */
      const std::shared_ptr<node <key_t> > insert(const key_t key) {
        std::shared_ptr<node <key_t> > current = root;
        std::shared_ptr<node <key_t> > parent = nullptr;
        while(current!=nullptr) {
          parent = current;
          if (key > current->key) {
            current = current->right;
          } else if (key < current->key) {
            current = current->left;
          } else {
            return nullptr;
          }
        }
        current = std::make_shared<node <key_t> > (key, red);
        current->parent = parent;
        if(parent == nullptr) {
          root = current;
        } else if (current->key > parent->key) {
          parent->right = current;
        } else if (current->key < parent->key) {
          parent->left = current;
        }
        fix(current);
        return current;
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
       * @brief Finds the height of the red black tree
       * @return The height of the red black tree
       */
      const unsigned long long height() {
        return height(root);
      }
      /**
       * @brief Finds the size of the red black tree
       * @return The size of the red black tree
       */
      const unsigned long long size() {
        return size(root);
      }
      /**
       * @brief Finds if the red black tree is empty
       * @return true if the red black tree is empty and false otherwise
       */
      const bool empty() {
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
