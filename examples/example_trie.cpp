#include <forest/trie.h>
#include <iostream>

int main(int argc, char const *argv[]) {
  std::cout << "================" << std::endl;
  std::cout << "[ Trie Example ]" << std::endl;
  std::cout << "================" << std::endl;

  std::cout << std::endl;

  forest::Trie trie;

  trie.insert("a");
  trie.insert("to");
  trie.insert("tea");
  trie.insert("ted");
  trie.insert("ten");
  trie.insert("i");
  trie.insert("in");
  trie.insert("inn");

  std::cout << trie.search("a") << " " << "a" << std::endl;
  std::cout << trie.search("to") << " " << "to" << std::endl;
  std::cout << trie.search("tea") << " " << "tea" << std::endl;
  std::cout << trie.search("ted") << " " << "ted" << std::endl;
  std::cout << trie.search("ten") << " " << "ten" << std::endl;
  std::cout << trie.search("i") << " " << "i" << std::endl;
  std::cout << trie.search("in") << " " << "in" << std::endl;
  std::cout << trie.search("inn") << " " << "inn" << std::endl;

  return 0;
}
