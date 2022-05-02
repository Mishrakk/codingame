#pragma once

#include "Node.h"

class Grid {
public:
	int width, height;
	queue<string> moves;
	vector<Node> nodes;
	map<string, Node*> nodes_coordinates;
	Grid();
	Grid(int width, int height, vector<string> lines);
	Grid(Grid &grid);
	void init_grid(int width, int height, vector<string> lines);
	void print_grid();
	void test_grid();
	void execute_next_move();
	void create_link(Node* first, Node* second);
	void fill_link(Node* first, Node* second, int links);
	void fill_link(string move);
	void remove_node_from_neighbours(Node* node_to_delete);
	void remove_cross_links(Node* first, Node* second);
	void clear_single_nodes();
	void clear_max_nodes();
	void clear_one_link_for_neighbour();
	void clear_obvious();
	void print_identifier();
	bool solve();
	bool are_moves();
	bool is_solved();
	bool is_correct_solution();
	string get_identifier();
	Node* find_top_neighbour(Node* current);
	Node* find_left_neighbour(Node* current);
	Node* get_node_at_coordinates(int x, int y);
	vector<Node*> list_active_nodes();
	vector<string> get_grid_representation();
};

