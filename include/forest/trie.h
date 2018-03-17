/**
 * @file trie.h
 */

#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <memory>

#define ALPHABET_SIZE 26

/**
 * @brief The forest library namespace
 */
namespace forest {
        namespace trie {
                /**
                 * @brief trie node struct
                 */
                struct node {
                        std::shared_ptr<node> children[ALPHABET_SIZE];
                        bool end;
                        /**
                         * @brief Constructor of a trie node
                         */
                        node() {
                                this->end = false; 
                                for (int i = 0; i < ALPHABET_SIZE; i++) {
                                        this->children[i] = NULL;
                                }
                        }
                };
                /**
                 * @brief trie class
                 */
                class tree {
                private:
                        std::shared_ptr<node> root;
                public:
                        tree() {
                                root = std::make_shared<node>();
                        }
                        /**
                         * @brief Inserts the given key into the trie
                         * @param key The key to be inserted
                         * @return void
                         */
                        void insert(const std::string &key) {
                                std::shared_ptr<node> n = root;
                                for (int i = 0; i < key.length(); i++) {
                                        int index = key[i] - 'a';
                                        if (n->children[index] == nullptr) {
                                                n->children[index] = std::make_shared<node>();
                                        }
                                        n = n->children[index];
                                }
                                n->end = true;
                        }
                        /**
                         * @brief Searches for the given key in the trie
                         * @param key The key to be inserted
                         * @return true if key exists in the trie and false otherwise
                         */
                        const bool search(const std::string &key) {
                                std::shared_ptr<node> n = root;
                                for (int i = 0; i < key.length(); i++) {
                                        int index = key[i] - 'a';
                                        if (n->children[index] == nullptr) {
                                                return false;
                                        }
                                        n = n->children[index];
                                }
                                return (n != nullptr && n->end == true);
                        }
                };
        }
}

#endif
