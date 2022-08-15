#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <map>
#include <stack>
#include <tuple>

using namespace std;

class Node {
public:
	int x, y, links, id;
	vector<tuple<Node*, int, bool> > neighbours;//pointer to node, number of filled links, active (possible to connect to)
	Node(int x, int y, int links, int id);
	void print_node();
	void add_neighbour(Node* neighbour);
	void remove_neighbour(Node* neighbour);
	void test_myself();
	int active_neighbours();
	int possible_links_to_do();
	int make_link(Node* neighbour, int connections);
	int get_right_neighbour_links();
	string get_links_symbol();
	string get_node_coordinates();
	Node* first_active_neighbour();
	vector<Node*> list_active_neighbours();
};

