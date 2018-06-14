#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>

namespace forest {
  template <typename T, typename U>
  class splay_tree {
  private:
    struct Node {
      T key;
      U value;
      Node * parent;
      Node * left;
      Node * right;
      Node(const T key, const U value) : key(key), value(value), parent(nullptr), left(nullptr), right(nullptr) { }
      ~Node() {
        delete left;
        delete right;
      }
    };
    Node * root_;
    void pre_order_traversal(const Node * root, void handler(const T & key, const U & value)) noexcept {
      if (root == nullptr) return;
      handler(root->key, root->value);
      pre_order_traversal(root->left, handler);
      pre_order_traversal(root->right, handler);
    }
    void in_order_traversal(const Node * root, void handler(const T & key, const U & value)) noexcept {
      if (root == nullptr) return;
      in_order_traversal(root->left, handler);
      handler(root->key, root->value);
      in_order_traversal(root->right, handler);
    }
    void post_order_traversal(const Node * root, void handler(const T & key, const U & value)) noexcept {
      if (root == nullptr) return;
      post_order_traversal(root->left, handler);
      post_order_traversal(root->right, handler);
      handler(root->key, root->value);
    }
    void breadth_first_traversal(const Node * root, void handler(const T & key, const U & value)) noexcept {
      if (root == nullptr) return;
      std::queue <const Node *> queue;
      queue.push(root);
      while (queue.empty() == false) {
        Node * y = queue.front();
        handler(y->key, y->value);
        queue.pop();
        if (y->left != nullptr) queue.push(y->left);
        if (y->right != nullptr) queue.push(y->right);
      }
    }
    size_t height(const Node * root) noexcept {
      if (root == nullptr) return 0;
      return std::max(height(root->left), height(root->right)) + 1;
    }
    size_t size(const Node * root) noexcept {
      if (root == nullptr) return 0;
      return size(root->left) + size(root->right) + 1;
    }
    void left_rotate(Node * root) noexcept {
      Node * y = root->right;
      if (y != nullptr) {
        root->right = y->left;
        if (y->left != nullptr) y->left->parent = root;
        y->parent = root->parent;
      }
      if (root->parent == nullptr) {
        root_ = y;
      } else if (root == root->parent->left) {
        root->parent->left = y;
      } else {
        root->parent->right = y;
      }
      if (y != nullptr) {
        y->left = root;
      }
      root->parent = y;
    }
    void right_rotate(Node * root) noexcept {
      Node * y = root->left;
      if (y != nullptr) {
        root->left = y->right;
        if (y->right != nullptr) y->right->parent = root;
        y->parent = root->parent;
      }
      if (root->parent == nullptr) {
        root_ = y;
      } else if (root == root->parent->left) {
        root->parent->left = y;
      } else {
        root->parent->right = y;
      }
      if (y != nullptr) {
        y->right = root;
      }
      root->parent = y;
    }
    Node * find_parent(Node * n) noexcept {
      return n->parent;
    }
    Node * find_grand_parent(Node * n) noexcept {
      if (find_parent(n) != nullptr) {
        return find_parent(n)->parent;
      }
      return nullptr;
    }
    void splay(Node * n) noexcept {
      while (find_parent(n) != nullptr) {
        if (find_grand_parent(n) == nullptr) {
          if (find_parent(n)->left == n) {
            right_rotate(find_parent(n));
          } else if (find_parent(n)->right == n) {
            left_rotate(find_parent(n));
          }
        } else if (find_parent(n)->left == n && find_grand_parent(n)->left == find_parent(n)) {
          right_rotate(find_grand_parent(n));
          right_rotate(find_parent(n));
        } else if (find_parent(n)->right == n && find_grand_parent(n)->right == find_parent(n)) {
          left_rotate(find_grand_parent(n));
          left_rotate(find_parent(n));
        } else if (find_parent(n)->left == n && find_grand_parent(n)->right == find_parent(n)) {
          right_rotate(find_parent(n));
          left_rotate(find_parent(n));
        } else if (find_parent(n)->right == n && find_grand_parent(n)->left == find_parent(n)) {
          left_rotate(find_parent(n));
          right_rotate(find_parent(n));
        }
      }
    }
  public:
    splay_tree() : root_(nullptr) { }
    ~splay_tree() {
      delete root_;
    }
    void pre_order_traversal(void handler(const T & key, const U & value)) noexcept {
      pre_order_traversal(root_, handler);
    }
    void in_order_traversal(void handler(const T & key, const U & value)) noexcept {
      in_order_traversal(root_, handler);
    }
    void post_order_traversal(void handler(const T & key, const U & value)) noexcept {
      post_order_traversal(root_, handler);
    }
    void breadth_first_traversal(void handler(const T & key, const U & value)) noexcept {
      breadth_first_traversal(root_, handler);
    }
    void insert(const T & key, const U & value) noexcept {
      Node * current = root_;
      Node * parent = nullptr;
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
      current = new Node(key, value);
      current->parent = parent;
      if (parent == nullptr) {
        root_ = current;
      } else if (current->key > parent->key) {
        parent->right = current;
      } else if (current->key < parent->key) {
        parent->left = current;
      }
      splay(current);
    }
    const Node * search(const T & key) noexcept {
      Node * current = root_;
      while (current != nullptr) {
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
    const Node * minimum() noexcept {
      Node * current = root_;
      if (current == nullptr) return nullptr;
      while (current->left != nullptr) current = current->left;
      return current;
    }
    const Node * maximum() noexcept {
      Node * current = root_;
      if (current == nullptr) return nullptr;
      while (current->right != nullptr) current = current->right;
      return current;
    }
    const Node * successor(const T & key) noexcept {
      Node * current = root_;
      while (current != nullptr) {
        if (key > current->key) {
          current = current->right;
        } else if (key < current->key) {
          current = current->left;
        } else {
          if (current->right != nullptr) {
            current = current->right;
            while (current->left != nullptr) current = current->left;
            return current;
          }
          Node * parent = current->parent;
          while (parent != nullptr && current == parent->right) {
            current = parent;
            parent = parent->parent;
          }
          return parent;
        }
      }
      return nullptr;
    }
    const Node * predecessor(const T & key) noexcept {
      Node * current = root_;
      while (current != nullptr) {
        if (key > current->key) {
          current = current->right;
        } else if (key < current->key) {
          current = current->left;
        } else {
          if (current->left != nullptr) {
            current = current->left;
            while (current->right != nullptr) current = current->right;
            return current;
          }
          Node * parent = current->parent;
          while (parent != nullptr && current == parent->left) {
            current = parent;
            parent = parent->parent;
          }
          return parent;
        }
      }
      return nullptr;
    }
    size_t height() noexcept {
      return height(root_);
    }
    size_t size() noexcept {
      return size(root_);
    }
    bool empty() const noexcept {
      return !root_;
    }
    const Node * root() noexcept {
      return root_;
    }
  };
}
