/**
 * @file splaytree.hpp
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
   * @brief Splay tree class
   */
  template <typename T, typename U>
  class splaytree {
  private:
    class splaynode {
    public:
      splaynode() = default;
      splaynode(const T & KEY, const U & VALUE) : key(KEY), value(VALUE) {

      }
      splaynode(const splaynode &) = delete;
      splaynode(splaynode &&) = delete;
      splaynode& operator=(const splaynode &) = delete;
      splaynode& operator=(splaynode &&) = delete;
      ~splaynode() {
        delete left;
        delete right;
      }
      T key;
      U value;
      friend class splaytree;
    private:
      splaynode * parent {nullptr};
      splaynode * left {nullptr};
      splaynode * right {nullptr};
    };
    splaynode * tree_root {nullptr};
    void pre_order_traversal(const splaynode * root, void handler(const T & key, const U & value)) noexcept {
      if (!root) return;
      handler(root->key, root->value);
      pre_order_traversal(root->left, handler);
      pre_order_traversal(root->right, handler);
    }
    void in_order_traversal(const splaynode * root, void handler(const T & key, const U & value)) noexcept {
      if (!root) return;
      in_order_traversal(root->left, handler);
      handler(root->key, root->value);
      in_order_traversal(root->right, handler);
    }
    void post_order_traversal(const splaynode * root, void handler(const T & key, const U & value)) noexcept {
      if (!root) return;
      post_order_traversal(root->left, handler);
      post_order_traversal(root->right, handler);
      handler(root->key, root->value);
    }
    void breadth_first_traversal(const splaynode * root, void handler(const T & key, const U & value)) noexcept {
      if (!root) return;
      std::queue <const splaynode *> queue;
      queue.push(root);
      while (!queue.empty()) {
        splaynode * root {queue.front()};
        handler(root->key, root->value);
        queue.pop();
        if (root->left) queue.push(root->left);
        if (root->right) queue.push(root->right);
      }
    }
    size_t height(const splaynode * root) noexcept {
      if (!root) return 0;
      return std::max(height(root->left), height(root->right)) + 1;
    }
    size_t size(const splaynode * root) noexcept {
      if (!root) return 0;
      return size(root->left) + size(root->right) + 1;
    }
    void rotate_right(splaynode * rotation_root) noexcept {
      splaynode * new_root {rotation_root->left};
      splaynode * orphan_subtree {new_root->right};
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
    void rotate_left(splaynode * rotation_root) noexcept {
      splaynode * new_root {rotation_root->right};
      splaynode * orphan_subtree {new_root->left};
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
    void fix(splaynode * n) noexcept {
      while (n->parent) {
        if (!n->parent->parent) {
          if (n->parent->left == n) {
            rotate_right(n->parent);
          } else if (n->parent->right == n) {
            rotate_left(n->parent);
          }
        } else if (n->parent->left == n && n->parent->parent->left == n->parent) {
          rotate_right(n->parent->parent);
          rotate_right(n->parent);
        } else if (n->parent->right == n && n->parent->parent->right == n->parent) {
          rotate_left(n->parent->parent);
          rotate_left(n->parent);
        } else if (n->parent->left == n && n->parent->parent->right == n->parent) {
          rotate_right(n->parent);
          rotate_left(n->parent);
        } else if (n->parent->right == n && n->parent->parent->left == n->parent) {
          rotate_left(n->parent);
          rotate_right(n->parent);
        }
      }
    }
  public:
    /**
     * @brief Default constructor.
     */
    splaytree() = default;
    /**
     * @brief Initializer list constructor.
     */
    explicit splaytree(std::initializer_list <std::pair <T, U> > list) {
      for (auto element : list) {
        insert(element.first, element.second);
      }
    }
    /**
     * @brief Copy constructor.
     */
    splaytree(const splaytree &) = delete;
    /**
     * @brief Move constructor.
     */
    splaytree(splaytree &&) = delete;
    /**
     * @brief Copy assignment operator.
     */
    splaytree& operator=(const splaytree &) = delete;
    /**
     * @brief Move assignment operator.
     */
    splaytree& operator=(splaytree &&) = delete;
    /**
     * @brief Destructor.
     */
    ~splaytree() {
      delete tree_root;
    }
    /**
     * @brief Performs pre-order traversal.
     */
    void pre_order_traversal(void handler(const T & key, const U & value)) noexcept {
      pre_order_traversal(tree_root, handler);
    }
    /**
     * @brief Performs in-order traversal.
     */
    void in_order_traversal(void handler(const T & key, const U & value)) noexcept {
      in_order_traversal(tree_root, handler);
    }
    /**
     * @brief Performs post-order traversal.
     */
    void post_order_traversal(void handler(const T & key, const U & value)) noexcept {
      post_order_traversal(tree_root, handler);
    }
    /**
     * @brief Performs breadth first traversal.
     */
    void breadth_first_traversal(void handler(const T & key, const U & value)) noexcept {
      breadth_first_traversal(tree_root, handler);
    }
    /**
     * @brief Inserts a node and rebalances the tree.
     */
    void insert(const T & key, const U & value) noexcept {
      splaynode * current {tree_root};
      splaynode * parent {nullptr};
      while (current) {
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
      current = new splaynode(key, value);
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
     * @return The node with the matching key, nullptr otherwise.
     */
    const splaynode * search(const T & key) noexcept {
      splaynode * current {tree_root};
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
     * @return The node with the minimum key, nullptr otherwise.
     */
    const splaynode * minimum() noexcept {
      splaynode * current {tree_root};
      if (!current) return nullptr;
      while (current->left) current = current->left;
      return current;
    }
    /**
     * @return The node with the maximum key, nullptr otherwise.
     */
    const splaynode * maximum() noexcept {
      splaynode * current {tree_root};
      if (!current) return nullptr;
      while (current->right) current = current->right;
      return current;
    }
    /**
     * @return The successor of a node if it exists, nullptr otherwise.
     */
    const splaynode * successor(const T & key) noexcept {
      splaynode * current {tree_root};
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
          splaynode * parent {current->parent};
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
    const splaynode * predecessor(const T & key) noexcept {
      splaynode * current {tree_root};
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
          splaynode * parent {current->parent};
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
