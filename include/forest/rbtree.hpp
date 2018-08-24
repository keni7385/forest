/**
 * @file rbtree.hpp
 * @author George Fotopoulos
 */

#pragma once

#include <algorithm>
#include <initializer_list>
#include <memory>
#include <queue>
#include <utility>

namespace forest {
  /**
   * @brief Red-Black tree class
   */
  template <typename T, typename U>
  class rbtree {
  private:
    enum rbcolor {
      RED,
      BLACK
    };
    class rbnode {
    public:
      rbnode() = default;
      rbnode(const T & KEY, const U & VALUE, const rbcolor & COLOR) : key(KEY), value(VALUE), color(COLOR) {

      }
      rbnode(const rbnode &) = delete;
      rbnode(rbnode &&) = delete;
      rbnode& operator=(const rbnode &) = delete;
      rbnode& operator=(rbnode &&) = delete;
      ~rbnode() {
        delete left;
        delete right;
      }
      T key;
      U value;
      friend class rbtree;
    private:
      rbcolor color;
      rbnode * parent {nullptr};
      rbnode * left {nullptr};
      rbnode * right {nullptr};
    };
    rbnode * tree_root {nullptr};
    void pre_order_traversal(const rbnode * root, void handler(const T & key, const U & value)) noexcept {
      if (!root) return;
      handler(root->key, root->value);
      pre_order_traversal(root->left, handler);
      pre_order_traversal(root->right, handler);
    }
    void in_order_traversal(const rbnode * root, void handler(const T & key, const U & value)) noexcept {
      if (!root) return;
      in_order_traversal(root->left, handler);
      handler(root->key, root->value);
      in_order_traversal(root->right, handler);
    }
    void post_order_traversal(const rbnode * root, void handler(const T & key, const U & value)) noexcept {
      if (!root) return;
      post_order_traversal(root->left, handler);
      post_order_traversal(root->right, handler);
      handler(root->key, root->value);
    }
    void breadth_first_traversal(const rbnode * root, void handler(const T & key, const U & value)) noexcept {
      std::queue <const rbnode *> queue;
      if (!root) return;
      queue.push(root);
      while (!queue.empty()) {
        rbnode * current {queue.front()};
        handler(current->key, current->value);
        queue.pop();
        if (current->left) queue.push(current->left);
        if (current->right) queue.push(current->right);
      }
    }
    size_t height(const rbnode * root) noexcept {
      if (!root) return 0;
      return std::max(height(root->left), height(root->right)) + 1;
    }
    size_t size(const rbnode * root) noexcept {
      if (!root) return 0;
      return size(root->left) + size(root->right) + 1;
    }
    void rotate_right(rbnode * rotation_root) noexcept {
      rbnode * new_root {rotation_root->left};
      rbnode * orphan_subtree {new_root->right};
      rotation_root->left = orphan_subtree;
      if (orphan_subtree) {
        orphan_subtree->parent = rotation_root;
      }
      new_root->right = rotation_root;
      if (!rotation_root->parent) {
        tree_root = new_root;
      } else if(rotation_root == rotation_root->parent->left) {
        rotation_root->parent->left = new_root;
      } else if (rotation_root == rotation_root->parent->right) {
        rotation_root->parent->right = new_root;
      }
      new_root->parent = rotation_root->parent;
      rotation_root->parent = new_root;
    }
    void rotate_left(rbnode * rotation_root) noexcept {
      rbnode * new_root {rotation_root->right};
      rbnode * orphan_subtree {new_root->left};
      rotation_root->right = orphan_subtree;
      if (orphan_subtree) {
        orphan_subtree->parent = rotation_root;
      }
      new_root->left = rotation_root;
      if (!rotation_root->parent) {
        tree_root = new_root;
      } else if(rotation_root == rotation_root->parent->left) {
        rotation_root->parent->left = new_root;
      } else {
        rotation_root->parent->right = new_root;
      }
      new_root->parent = rotation_root->parent;
      rotation_root->parent = new_root;
    }
    void fix(rbnode * n) noexcept {
      rbnode * parent {nullptr};
      rbnode * grand_parent {nullptr};
      while ((n != tree_root) && (n->color != BLACK) && (n->parent->color == RED)) {
        parent = n->parent;
        grand_parent = n->parent->parent;
        if (parent == grand_parent->left) {
          rbnode * uncle {grand_parent->right};
          if (uncle && uncle->color == RED) {
            grand_parent->color = RED;
            parent->color = BLACK;
            uncle->color = BLACK;
            n = grand_parent;
          } else {
            if (n == parent->right) {
              rotate_left(parent);
              n = parent;
              parent = n->parent;
            }
            rotate_right(grand_parent);
            std::swap(parent->color, grand_parent->color);
            n = parent;
          }
        } else {
          rbnode * uncle {grand_parent->left};
          if (uncle && (uncle->color == RED)) {
            grand_parent->color = RED;
            parent->color = BLACK;
            uncle->color = BLACK;
            n = grand_parent;
          } else {
            if (n == parent->left) {
              rotate_right(parent);
              n = parent;
              parent = n->parent;
            }
            rotate_left(grand_parent);
            std::swap(parent->color, grand_parent->color);
            n = parent;
          }
        }
      }
      tree_root->color = BLACK;
    }
  public:
    /**
     * @brief Default constructor.
     */
    rbtree() = default;
    /**
     * @brief Initializer list constructor.
     */
    explicit rbtree(std::initializer_list <std::pair <T, U> > list) {
      for (auto element : list) {
        insert(element.first, element.second);
      }
    }
    /**
     * @brief Copy constructor.
     */
    rbtree(const rbtree &) = delete;
    /**
     * @brief Move constructor.
     */
    rbtree(rbtree &&) = delete;
    /**
     * @brief Copy assignment operator.
     */
    rbtree& operator=(const rbtree &) = delete;
    /**
     * @brief Move assignment operator.
     */
    rbtree& operator=(rbtree &&) = delete;
    /**
     * @brief Destructor.
     */
    ~rbtree() {
      delete tree_root;
    }
    /**
     * @brief Performs pre-order traversal from root.
     */
    void pre_order_traversal(void handler(const T & key, const U & value)) noexcept {
      pre_order_traversal(tree_root, handler);
    }
    /**
     * @brief Performs in-order traversal from root.
     */
    void in_order_traversal(void handler(const T & key, const U & value)) noexcept {
      in_order_traversal(tree_root, handler);
    }
    /**
     * @brief Performs post-order traversal from root.
     */
    void post_order_traversal(void handler(const T & key, const U & value)) noexcept {
      post_order_traversal(tree_root, handler);
    }
    /**
     * @brief Performs breadth first traversal from root.
     */
    void breadth_first_traversal(void handler(const T & key, const U & value)) noexcept {
      breadth_first_traversal(tree_root, handler);
    }
    /**
     * @brief Inserts a node and rebalances the tree.
     */
    void insert(const T & key, const U & value) noexcept {
      rbnode * current {tree_root};
      rbnode * parent {nullptr};
      while (current != nullptr) {
        parent = current;
        if (key > current->key) {
          current = current->right;
        } else if (key < current->key) {
          current = current->left;
        } else if (key == current->key) {
          current->value = value;
          return;
        }
      }
      current = new rbnode(key, value, RED);
      current->parent = parent;
      if (!parent) {
        tree_root = current;
      } else if (current->key > parent->key) {
        parent->right = current;
      } else if (current->key < parent->key) {
        parent->left = current;
      }
      fix(current);
    }
    /**
     * @return The node the matching key, nullptr otherwise.
     */
    const rbnode * search(const T & key) noexcept {
      rbnode * current {tree_root};
      while (current) {
        if (key > current->key) {
          current = current->right;
        } else if (key < current->key) {
          current = current->left;
        } else {
          return current;
        }
      }
      return nullptr;
    }
    /**
     * @return The node the minimum key, nullptr otherwise.
     */
    const rbnode * minimum() noexcept {
      rbnode * current = {tree_root};
      if (!current) return nullptr;
      while (current->left) current = current->left;
      return current;
    }
    /**
     * @return The node the maximum key, nullptr otherwise.
     */
    const rbnode * maximum() noexcept {
      rbnode * current {tree_root};
      if (!current) return nullptr;
      while (current->right) current = current->right;
      return current;
    }
    /**
     * @return The successor of a node if it exists, nullptr otherwise.
     */
    const rbnode * successor(const T & key) noexcept {
      rbnode * current {tree_root};
      while (current) {
        if (key > current->key) {
          current = current->right;
        } else if (key < current->key) {
          current = current->left;
        } else {
          if (current->right) {
            current = current->right;
            while (current->left) current = current->left;
            return current;
          }
          rbnode * parent {current->parent};
          while (parent && current == parent->right) {
            current = parent;
            parent = parent->parent;
          }
          return parent;
        }
      }
      return nullptr;
    }
    /**
     * @return The predecessor of a node if it exists, nullptr otherwise.
     */
    const rbnode * predecessor(const T & key) {
      rbnode * current {tree_root};
      while (current) {
        if (key > current->key) {
          current = current->right;
        } else if (key < current->key) {
          current = current->left;
        } else {
          if (current->left) {
            current = current->left;
            while (current->right) current = current->right;
            return current;
          }
          rbnode * parent {current->parent};
          while (parent && current == parent->left) {
            current = parent;
            parent = parent->parent;
          }
          return parent;
        }
      }
      return nullptr;
    }
    /**
     * @return The height of the tree.
     */
    size_t height() noexcept {
      return height(tree_root);
    }
    /**
     * @return The number of nodes in the tree.
     */
    size_t size() noexcept {
      return size(tree_root);
    }
    /**
     * @return True if tree is empty, false otherwise.
     */
    bool empty() noexcept {
      return !tree_root;
    }
    /**
     * @return The root of the tree, nullptr otherwise.
     */
    const rbnode * root() noexcept {
      return tree_root;
    }
  };
}
