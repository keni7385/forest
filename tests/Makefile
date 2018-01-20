CXX=g++
CXXFLAGS=-std=c++11

test: test_main.o test_binary_search_tree.o test_avl_tree.o test_splay_tree.o test_red_black_tree.o test_trie.o
	$(CXX) test_main.o test_binary_search_tree.o test_avl_tree.o test_splay_tree.o test_red_black_tree.o test_trie.o $(CXXFLAGS) -o test

test_main.o: test_main.cpp
	$(CXX) -c test_main.cpp $(CXXFLAGS) -I ..

test_binary_search_tree.o: test_binary_search_tree.cpp
	$(CXX) -c test_binary_search_tree.cpp $(CXXFLAGS) -I ..

test_avl_tree.o: test_avl_tree.cpp
	$(CXX) -c test_avl_tree.cpp $(CXXFLAGS) -I ..

test_splay_tree.o: test_splay_tree.cpp
	$(CXX) -c test_splay_tree.cpp $(CXXFLAGS) -I ..

test_red_black_tree.o: test_red_black_tree.cpp
	$(CXX) -c test_red_black_tree.cpp $(CXXFLAGS) -I ..

test_trie.o: test_trie.cpp
	$(CXX) -c test_trie.cpp $(CXXFLAGS) -I ..

clean:
	rm -f *.o
	rm -f test
