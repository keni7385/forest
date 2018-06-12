#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>

namespace forest {
  template <typename T, typename U>
  class avl_tree {
  private:
    struct Node {
      T key;
      U value;
      int balance_factor;
      Node * parent;
      Node * left;
      Node * right;
      Node(T key, U value) :key(key), value(value), balance_factor(0), parent(nullptr), left(nullptr), right(nullptr){}
    };
    Node * root_;
    void pre_order_traversal(Node * x, void handler(const T & key, const U & value)) {
      if (x == nullptr) return;
      handler(x->key, x->value);
      pre_order_traversal(x->left, handler);
      pre_order_traversal(x->right, handler);
    }
    void in_order_traversal(Node * x, void handler(const T & key, const U & value)) {
      if (x == nullptr) return;
      in_order_traversal(x->left, handler);
      handler(x->key, x->value);
      in_order_traversal(x->right, handler);
    }
    void post_order_traversal(Node * x, void handler(const T & key, const U & value)) {
      if (x == nullptr) return;
      post_order_traversal(x->left, handler);
      post_order_traversal(x->right, handler);
      handler(x->key, x->value);
    }
    void breadth_first_traversal(Node * x, void handler(const T & key, const U & value)) {
      std::queue <std::shared_ptr<Node> > queue;
      if (x == nullptr) return;
      queue.push(x);
      while(queue.empty() == false) {
        Node * y = queue.front();
        handler(y->key, y->value);
        queue.pop();
        if (y->left != nullptr) queue.push(y->left);
        if (y->right != nullptr) queue.push(y->right);
      }
    }
    size_t height(Node * x) {
      if (x == nullptr) return 0;
      return std::max(height(x->left), height(x->right)) + 1;
    }
    size_t size(Node * x) {
      if (x == nullptr) return 0;
      return size(x->left) + size(x->right) + 1;
    }
    void rotate_right(Node * rotation_root) {
      Node * new_root = rotation_root->left;
      Node * orphan_subtree = new_root->right;

      rotation_root->left = orphan_subtree;
      if (orphan_subtree != nullptr) {
        orphan_subtree->parent = rotation_root;
      }

      new_root->right = rotation_root;

      if (rotation_root->parent == nullptr) {
        root_ = new_root;
      } else if(rotation_root == rotation_root->parent->left) {
        rotation_root->parent->left = new_root;
      } else if (rotation_root == rotation_root->parent->right) {
        rotation_root->parent->right = new_root;
      }
      new_root->parent = rotation_root->parent;
      rotation_root->parent = new_root;
    }
    void rotate_left(Node * rotation_root) {
      Node * new_root = rotation_root->right;
      Node * orphan_subtree = new_root->left;

      rotation_root->right = orphan_subtree;
      if (orphan_subtree != nullptr) {
        orphan_subtree->parent = rotation_root;
      }

      new_root->left = rotation_root;

      if (rotation_root->parent == nullptr) {
        root_ = new_root;
      } else if(rotation_root == rotation_root->parent->left) {
        rotation_root->parent->left = new_root;
      } else {
        rotation_root->parent->right = new_root;
      }
      new_root->parent = rotation_root->parent;
      rotation_root->parent = new_root;
    }
  public:
    avl_tree() : root_(nullptr) {}
    void pre_order_traversal(void handler(const T & key, const U & value)) {
      pre_order_traversal(root_, handler);
    }
    void in_order_traversal(void handler(const T & key, const U & value)) {
      in_order_traversal(root_, handler);
    }
    void post_order_traversal(void handler(const T & key, const U & value)) {
      post_order_traversal(root_, handler);
    }
    void breadth_first_traversal(void handler(const T & key, const U & value)) {
      breadth_first_traversal(root_, handler);
    }
    void insert(const T & key, const U & value) {
      Node * current = root_;
      Node * parent = nullptr;
      Node * inserted_node = nullptr;

      while (current != nullptr) {
        parent = current;
        if (key > current->key) {
          current = current->right;
        } else if (key < current->key) {
          current = current->left;
        }
      }

      current = new Node(key, value);
      current->parent = parent;

      if(parent == nullptr) {
        root_ = current;
      } else if (current->key > parent->key) {
        parent->right = current;
      } else if (current->key < parent->key) {
        parent->left = current;
      }

      inserted_node = current;

      while (current != nullptr) {
        current->balance_factor = (height(current->right) - height(current->left));
        if (current->balance_factor == -2) {
          if (current->left->balance_factor == 1) {
            rotate_left(current->left);
          }
          rotate_right(current);
        } else if (current->balance_factor == 2) {
          if (current->right->balance_factor == -1) {
            rotate_right(current->right);
          }
          rotate_left(current);
        }
        current = current->parent;
      }
    }
    const Node * search(const T & key) {
      Node * x = root_;
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
    const Node * minimum() {
      Node * x = root_;
      if (x == nullptr) return nullptr;
      while(x->left != nullptr) x = x->left;
      return x;
    }
    const Node * maximum() {
      Node * x = root_;
      if (x == nullptr) return nullptr;
      while(x->right != nullptr) x = x->right;
      return x;
    }
    const Node * successor(const T & key) {
      Node * x = root_;
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
          Node * parent = x->parent;
          while (parent != nullptr && x == parent->right) {
            x = parent;
            parent = parent->parent;
          }
          return parent;
        }
      }
      return nullptr;
    }
    const Node * predecessor(const T & key) {
      Node * x = root_;
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
          Node * parent = x->parent;
          while (parent != nullptr && x == parent->left) {
            x = parent;
            parent = parent->parent;
          }
          return parent;
        }
      }
      return nullptr;
    }
    size_t height() {
      return height(root_);
    }
    size_t size() {
      return size(root_);
    }
    bool empty() const {
      return !root_;
    }
    const Node * root() {
      return root_;
    }
  };
}
