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
      std::weak_ptr<Node> parent;
      std::shared_ptr<Node> left;
      std::shared_ptr<Node> right;
      Node(T key, U value) {
        this->key = key;
	    	this->value = value;
	    }
    };
    std::shared_ptr<Node> root;
    void pre_order_traversal(std::shared_ptr<Node> & x, void handler(T & key, U & value)) {
      if (x == nullptr) return;
      handler(x->key, x->value);
      pre_order_traversal(x->left, handler);
      pre_order_traversal(x->right, handler);
    }
    void in_order_traversal(std::shared_ptr<Node> & x, void handler(T & key, U & value)) {
      if (x == nullptr) return;
      in_order_traversal(x->left, handler);
      handler(x->key, x->value);
      in_order_traversal(x->right, handler);
    }
    void post_order_traversal(std::shared_ptr<Node> & x, void handler(T & key, U & value)) {
      if (x == nullptr) return;
      post_order_traversal(x->left, handler);
      post_order_traversal(x->right, handler);
      handler(x->key, x->value);
    }
    void breadth_first_traversal(std::shared_ptr<Node> & x, void handler(T & key, U & value)) {
      std::queue <std::shared_ptr<Node> > queue;
      if (x == nullptr) return;
      queue.push(x);
      while(queue.empty() == false) {
        std::shared_ptr<Node> y = queue.front();
        handler(y->key, y->value);
        queue.pop();
        if (y->left != nullptr) queue.push(y->left);
        if (y->right != nullptr) queue.push(y->right);
      }
    }
    size_t height(std::shared_ptr<Node> & x) {
      if (x == nullptr) return 0;
      return std::max(height(x->left), height(x->right)) + 1;
    }
    size_t size(std::shared_ptr<Node> & x) {
      if (x == nullptr) return 0;
      return size(x->left) + size(x->right) + 1;
    }
    void rotate_right(std::shared_ptr<Node> & rotation_root) {
      std::shared_ptr<Node> new_root = rotation_root->left;
      std::shared_ptr<Node> orphan_subtree = new_root->right;

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
    void rotate_left(std::shared_ptr<Node> & rotation_root) {
      std::shared_ptr<Node>  new_root = rotation_root->right;
      std::shared_ptr<Node>  orphan_subtree = new_root->left;

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
    void pre_order_traversal(void handler(T & key, U & value)) {
      pre_order_traversal(root, handler);
    }
    void in_order_traversal(void handler(T & key, U & value)) {
      in_order_traversal(root, handler);
    }
    void post_order_traversal(void handler(T & key, U & value)) {
      post_order_traversal(root, handler);
    }
    void breadth_first_traversal(void handler(T & key, U & value)) {
      breadth_first_traversal(root, handler);
    }
    void insert(T key, U value) {
      std::shared_ptr<Node> current = root;
      std::shared_ptr<Node> parent = nullptr;
      std::shared_ptr<Node> inserted_node;

      while (current != nullptr) {
        parent = current;
        if (key > current->key) {
          current = current->right;
        } else if (key < current->key) {
          current = current->left;
        }
      }

      current = std::make_shared<Node>(key, value);
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
    }
    std::shared_ptr<const Node> search(T key) {
      std::shared_ptr<Node> x = root;
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
    std::shared_ptr<const Node> minimum() {
      std::shared_ptr<Node> x = root;
      if (x == nullptr) return nullptr;
      while(x->left != nullptr) x = x->left;
      return x;
    }
    std::shared_ptr<const Node> maximum() {
      std::shared_ptr<Node> x = root;
      if (x == nullptr) return nullptr;
      while(x->right != nullptr) x = x->right;
      return x;
    }
    std::shared_ptr<const Node> successor(T key) {
      std::shared_ptr<Node> x = root;
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
          std::shared_ptr<Node> parent = x->parent.lock();
          while (parent != nullptr && x == parent->right) {
            x = parent;
            parent = parent->parent.lock();
          }
          return parent;
        }
      }
      return nullptr;
    }
    std::shared_ptr<Node> predecessor(T key) {
      std::shared_ptr<Node> x = root;
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
          std::shared_ptr<Node> parent = x->parent.lock();
          while (parent != nullptr && x == parent->left) {
            x = parent;
            parent = parent->parent.lock();
          }
          return parent;
        }
      }
      return nullptr;
    }
    size_t height() {
      return height(root);
    }
    size_t size() {
      return size(root);
    }
    bool empty() const{
		return (root == nullptr);
    }
  };
}