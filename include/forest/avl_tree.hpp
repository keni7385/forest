#pragma once

#include <algorithm>
#include <memory>
#include <queue>

namespace forest {
  template <typename T, typename U>
  class avl_tree {
  private:
    struct Node {
      Node(const T KEY, const U VALUE) :key(KEY), value(VALUE) {}
      ~Node() {
        delete left;
        delete right;
      }
      T key;
      U value;
      int balance_factor {0};
      Node * parent {nullptr};
      Node * left {nullptr};
      Node * right {nullptr};
    };
    Node * root_ {nullptr};
    void pre_order_traversal(const Node * root, void handler(const T & key, const U & value)) noexcept {
      if (!root) return;
      handler(root->key, root->value);
      pre_order_traversal(root->left, handler);
      pre_order_traversal(root->right, handler);
    }
    void in_order_traversal(const Node * root, void handler(const T & key, const U & value)) noexcept {
      if (!root) return;
      in_order_traversal(root->left, handler);
      handler(root->key, root->value);
      in_order_traversal(root->right, handler);
    }
    void post_order_traversal(const Node * root, void handler(const T & key, const U & value)) noexcept {
      if (!root) return;
      post_order_traversal(root->left, handler);
      post_order_traversal(root->right, handler);
      handler(root->key, root->value);
    }
    void breadth_first_traversal(const Node * root, void handler(const T & key, const U & value)) noexcept {
      std::queue <const Node *> queue;
      if (!root) return;
      queue.push(root);
      while(!queue.empty()) {
        Node * current {queue.front()};
        handler(current->key, current->value);
        queue.pop();
        if (current->left) queue.push(current->left);
        if (current->right) queue.push(current->right);
      }
    }
    size_t height(const Node * root) noexcept {
      if (!root) return 0;
      return std::max(height(root->left), height(root->right)) + 1;
    }
    size_t size(const Node * root) noexcept {
      if (!root) return 0;
      return size(root->left) + size(root->right) + 1;
    }
    void rotate_right(Node * rotation_root) noexcept {
      Node * new_root {rotation_root->left};
      Node * orphan_subtree {new_root->right};

      rotation_root->left = orphan_subtree;
      if (orphan_subtree) {
        orphan_subtree->parent = rotation_root;
      }

      new_root->right = rotation_root;

      if (!rotation_root->parent) {
        root_ = new_root;
      } else if(rotation_root == rotation_root->parent->left) {
        rotation_root->parent->left = new_root;
      } else if (rotation_root == rotation_root->parent->right) {
        rotation_root->parent->right = new_root;
      }
      new_root->parent = rotation_root->parent;
      rotation_root->parent = new_root;
    }
    void rotate_left(Node * rotation_root) noexcept {
      Node * new_root {rotation_root->right};
      Node * orphan_subtree {new_root->left};

      rotation_root->right = orphan_subtree;
      if (orphan_subtree) {
        orphan_subtree->parent = rotation_root;
      }

      new_root->left = rotation_root;

      if (!rotation_root->parent) {
        root_ = new_root;
      } else if(rotation_root == rotation_root->parent->left) {
        rotation_root->parent->left = new_root;
      } else {
        rotation_root->parent->right = new_root;
      }
      new_root->parent = rotation_root->parent;
      rotation_root->parent = new_root;
    }
    Node * find_parent(Node * n) noexcept {
      if (n) return n->parent;
      return nullptr;
    }
    Node * find_grandparent(Node * n) noexcept {
      if (find_parent(n)) return find_parent(n)->parent;
      return nullptr;
    }
  public:
    avl_tree() {
      
    }
    ~avl_tree() {
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
      Node * current {root_};
      Node * parent {nullptr};
      Node * inserted_node {nullptr};

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

      current = new Node(key, value);
      current->parent = parent;

      if(!parent) {
        root_ = current;
      } else if (current->key > parent->key) {
        parent->right = current;
      } else if (current->key < parent->key) {
        parent->left = current;
      }

      while (current) {
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
    const Node * search(const T & key) noexcept {
      Node * current {root_};
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
    const Node * minimum() noexcept {
      Node * current {root_};
      if (!current) return nullptr;
      while(current->left) current = current->left;
      return current;
    }
    const Node * maximum() noexcept {
      Node * current {root_};
      if (!current) return nullptr;
      while(current->right) current = current->right;
      return current;
    }
    const Node * successor(const T & key) noexcept {
      Node * current {root_};
      while (current) {
        if (key > current->key) {
          current = current->right;
        } else if (key < current->key) {
          current = current->left;
        } else {
          if (current->right) {
            current = current->right;
            while(current->left) current = current->left;
            return current;
          }
          Node * parent {current->parent};
          while (parent && current == parent->right) {
            current = parent;
            parent = parent->parent;
          }
          return parent;
        }
      }
      return nullptr;
    }
    const Node * predecessor(const T & key) noexcept {
      Node * current {root_};
      while (current) {
        if (key > current->key) {
          current = current->right;
        } else if (key < current->key) {
          current = current->left;
        } else {
          if (current->left) {
            current = current->left;
            while(current->right) current = current->right;
            return current;
          }
          Node * parent {current->parent};
          while (parent && current == parent->left) {
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
    bool empty() noexcept {
      return !root_;
    }
    const Node * root() noexcept {
      return root_;
    }
  };
}
