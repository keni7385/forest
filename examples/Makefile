CXX=g++
CXXFLAGS=-std=c++11

all: example_binary_search_tree example_avl_tree example_splay_tree example_red_black_tree example_trie

example_binary_search_tree: example_binary_search_tree.o
	$(CXX) example_binary_search_tree.o $(CXXFLAGS) -o example_binary_search_tree

example_avl_tree: example_avl_tree.o
	$(CXX) example_avl_tree.o $(CXXFLAGS) -o example_avl_tree

example_splay_tree: example_splay_tree.o
	$(CXX) example_splay_tree.o $(CXXFLAGS) -o example_splay_tree

example_red_black_tree: example_red_black_tree.o
	$(CXX) example_red_black_tree.o $(CXXFLAGS) -o example_red_black_tree

example_trie: example_trie.o
	$(CXX) example_trie.o $(CXXFLAGS) -o example_trie

example_binary_search_tree.o: example_binary_search_tree.cpp
	$(CXX) -c example_binary_search_tree.cpp $(CXXFLAGS) -I ../include

example_avl_tree.o: example_avl_tree.cpp
	$(CXX) -c example_avl_tree.cpp $(CXXFLAGS) -I ../include

example_splay_tree.o: example_splay_tree.cpp
	$(CXX) -c example_splay_tree.cpp $(CXXFLAGS) -I ../include

example_red_black_tree.o: example_red_black_tree.cpp
	$(CXX) -c example_red_black_tree.cpp $(CXXFLAGS) -I ../include

example_trie.o: example_trie.cpp
	$(CXX) -c example_trie.cpp $(CXXFLAGS) -I ../include

clean:
	rm -f *.o
	rm -f example_binary_search_tree
	rm -f example_avl_tree
	rm -f example_splay_tree
	rm -f example_red_black_tree
	rm -f example_trie
