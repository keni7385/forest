#pragma once

#include <algorithm>
#include <memory>
#include <queue>

namespace forest {
  template <typename T, typename U>
  class red_black_tree {
  private:
    enum Color { red, black };
    struct Node {
      T key;
      U value;
      Color color;
      Node * parent {nullptr};
      Node * left {nullptr};
      Node * right {nullptr};
      Node(const T key, const U value, const Color color) : key(key), value(value), color(color) {}
      ~Node() {
        delete left;
        delete right;
      }
    };
    Node * root_ {nullptr};
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
      std::queue <const Node *> queue;
      if (root == nullptr) return;
      queue.push(root);
      while (queue.empty() == false) {
        Node * current {queue.front()};
        handler(current->key, current->value);
        queue.pop();
        if (current->left != nullptr) queue.push(current->left);
        if (current->right != nullptr) queue.push(current->right);
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
    void rotate_right(Node * rotation_root) noexcept {
      Node * new_root {rotation_root->left};
      Node * orphan_subtree {new_root->right};

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
    void rotate_left(Node * rotation_root) noexcept {
      Node * new_root {rotation_root->right};
      Node * orphan_subtree {new_root->left};

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
    Node * find_parent(Node * n) noexcept {
      if (n != nullptr) return n->parent;
      return nullptr;
    }
    Node * find_grandparent(Node * n) noexcept {
      if (find_parent(n) != nullptr) return find_parent(n)->parent;
      return nullptr;
    }
    void fix(Node * n) noexcept {
      Node * parent {nullptr};
      Node * grand_parent {nullptr};
      while ((n != root_) && (n->color != black) && (n->parent->color == red)) {
        parent = n->parent;
        grand_parent = n->parent->parent;
        if (parent == grand_parent->left) {
          Node * uncle {grand_parent->right};
          if (uncle != nullptr && uncle->color == red) {
            grand_parent->color = red;
            parent->color = black;
            uncle->color = black;
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
          Node * uncle {grand_parent->left};
          if ((uncle != nullptr) && (uncle->color == red)) {
            grand_parent->color = red;
            parent->color = black;
            uncle->color = black;
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
      root_->color = black;
    }
  public:
    red_black_tree() {}
    ~red_black_tree() {
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
      current = new Node(key, value, red);
      current->parent = parent;
      if (parent == nullptr) {
        root_ = current;
      } else if (current->key > parent->key) {
        parent->right = current;
      } else if (current->key < parent->key) {
        parent->left = current;
      }
      fix(current);
    }
    const Node * search(const T & key) noexcept {
      Node * current {root_};
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
      Node * current = {root_};
      if (current == nullptr) return nullptr;
      while (current->left != nullptr) current = current->left;
      return current;
    }
    const Node * maximum() noexcept {
      Node * current {root_};
      if (current == nullptr) return nullptr;
      while (current->right != nullptr) current = current->right;
      return current;
    }
    const Node * successor(const T & key) noexcept {
      Node * current {root_};
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
          Node * parent {current->parent};
          while (parent != nullptr && current == parent->right) {
            current = parent;
            parent = parent->parent;
          }
          return parent;
        }
      }
      return nullptr;
    }
    const Node * predecessor(const T & key) {
      Node * current {root_};
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
          Node * parent {current->parent};
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
    bool empty() noexcept {
      return !root_;
    }
    const Node * root() noexcept {
      return root_;
    }
  };
}
