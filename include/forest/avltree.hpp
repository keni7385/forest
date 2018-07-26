#pragma once

#include <algorithm>
#include <memory>
#include <queue>

namespace forest {
  template <typename T, typename U>
  class avltree {
  private:
    struct avlnode {
      avlnode(const T & KEY, const U & VALUE) :key(KEY), value(VALUE) {

      }
      ~avlnode() {
        delete left;
        delete right;
      }
      T key;
      U value;
      char balance_factor {0};
      avlnode * parent {nullptr};
      avlnode * left {nullptr};
      avlnode * right {nullptr};
    };
    avlnode * _root {nullptr};
    void pre_order_traversal(const avlnode * root, void handler(const T & key, const U & value)) noexcept {
      if (!root) return;
      handler(root->key, root->value);
      pre_order_traversal(root->left, handler);
      pre_order_traversal(root->right, handler);
    }
    void in_order_traversal(const avlnode * root, void handler(const T & key, const U & value)) noexcept {
      if (!root) return;
      in_order_traversal(root->left, handler);
      handler(root->key, root->value);
      in_order_traversal(root->right, handler);
    }
    void post_order_traversal(const avlnode * root, void handler(const T & key, const U & value)) noexcept {
      if (!root) return;
      post_order_traversal(root->left, handler);
      post_order_traversal(root->right, handler);
      handler(root->key, root->value);
    }
    void breadth_first_traversal(const avlnode * root, void handler(const T & key, const U & value)) noexcept {
      std::queue <const avlnode *> queue;
      if (!root) return;
      queue.push(root);
      while(!queue.empty()) {
        avlnode * current {queue.front()};
        handler(current->key, current->value);
        queue.pop();
        if (current->left) queue.push(current->left);
        if (current->right) queue.push(current->right);
      }
    }
    size_t height(const avlnode * root) noexcept {
      if (!root) return 0;
      return std::max(height(root->left), height(root->right)) + 1;
    }
    size_t size(const avlnode * root) noexcept {
      if (!root) return 0;
      return size(root->left) + size(root->right) + 1;
    }
    void rotate_right(avlnode * rotation_root) noexcept {
      avlnode * new_root {rotation_root->left};
      avlnode * orphan_subtree {new_root->right};
      rotation_root->left = orphan_subtree;
      if (orphan_subtree) {
        orphan_subtree->parent = rotation_root;
      }
      new_root->right = rotation_root;
      if (!rotation_root->parent) {
        _root = new_root;
      } else if(rotation_root == rotation_root->parent->left) {
        rotation_root->parent->left = new_root;
      } else if (rotation_root == rotation_root->parent->right) {
        rotation_root->parent->right = new_root;
      }
      new_root->parent = rotation_root->parent;
      rotation_root->parent = new_root;
    }
    void rotate_left(avlnode * rotation_root) noexcept {
      avlnode * new_root {rotation_root->right};
      avlnode * orphan_subtree {new_root->left};
      rotation_root->right = orphan_subtree;
      if (orphan_subtree) {
        orphan_subtree->parent = rotation_root;
      }
      new_root->left = rotation_root;
      if (!rotation_root->parent) {
        _root = new_root;
      } else if(rotation_root == rotation_root->parent->left) {
        rotation_root->parent->left = new_root;
      } else {
        rotation_root->parent->right = new_root;
      }
      new_root->parent = rotation_root->parent;
      rotation_root->parent = new_root;
    }
    void fix(avlnode * n) noexcept {
      while (n) {
        n->balance_factor = (height(n->right) - height(n->left));
        if (n->balance_factor == -2) {
          if (n->left->balance_factor == 1) {
            rotate_left(n->left);
          }
          rotate_right(n);
        } else if (n->balance_factor == 2) {
          if (n->right->balance_factor == -1) {
            rotate_right(n->right);
          }
          rotate_left(n);
        }
        n = n->parent;
      }
    }
  public:
    avltree() {

    }
    ~avltree() {
      delete _root;
    }
    void pre_order_traversal(void handler(const T & key, const U & value)) noexcept {
      pre_order_traversal(_root, handler);
    }
    void in_order_traversal(void handler(const T & key, const U & value)) noexcept {
      in_order_traversal(_root, handler);
    }
    void post_order_traversal(void handler(const T & key, const U & value)) noexcept {
      post_order_traversal(_root, handler);
    }
    void breadth_first_traversal(void handler(const T & key, const U & value)) noexcept {
      breadth_first_traversal(_root, handler);
    }
    void insert(const T & key, const U & value) noexcept {
      avlnode * current {_root};
      avlnode * parent {nullptr};
      avlnode * inserted_node {nullptr};
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
      current = new avlnode(key, value);
      current->parent = parent;
      if(!parent) {
        _root = current;
      } else if (current->key > parent->key) {
        parent->right = current;
      } else if (current->key < parent->key) {
        parent->left = current;
      }
      fix(current);
    }
    const avlnode * search(const T & key) noexcept {
      avlnode * current {_root};
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
    const avlnode * minimum() noexcept {
      avlnode * current {_root};
      if (!current) return nullptr;
      while(current->left) current = current->left;
      return current;
    }
    const avlnode * maximum() noexcept {
      avlnode * current {_root};
      if (!current) return nullptr;
      while(current->right) current = current->right;
      return current;
    }
    const avlnode * successor(const T & key) noexcept {
      avlnode * current {_root};
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
          avlnode * parent {current->parent};
          while (parent && current == parent->right) {
            current = parent;
            parent = parent->parent;
          }
          return parent;
        }
      }
      return nullptr;
    }
    const avlnode * predecessor(const T & key) noexcept {
      avlnode * current {_root};
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
          avlnode * parent {current->parent};
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
      return height(_root);
    }
    size_t size() noexcept {
      return size(_root);
    }
    bool empty() noexcept {
      return !_root;
    }
    const avlnode * root() noexcept {
      return _root;
    }
  };
}
