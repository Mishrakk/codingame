#include "Grid.h"

Grid::Grid() {
	int in_width;
	int in_height;
	vector<string> lines;

	cin >> in_width; cin.ignore();
	cin >> in_height; cin.ignore();
	for (int y = 0; y < in_height; y++) {
		string line;
		getline(cin, line);
		lines.push_back(line);
	}
	init_grid(in_width, in_height, lines);
}

Grid::Grid(int width, int height, vector<string> lines) {
	init_grid(width, height, lines);
}

Grid::Grid(Grid& orig_grid) {
	width = orig_grid.width;
	height = orig_grid.height;
	nodes.reserve(sizeof(Node) * width * height);
	map<Node*, Node*> orig_to_new_node_pointers;

	for (vector<Node>::iterator it = orig_grid.nodes.begin(); it != orig_grid.nodes.end(); ++it) {
		Node* onode = &(*it);
		nodes.push_back(Node(onode->x, onode->y, onode->links, nodes.size()));
		Node* new_node = &nodes.back();
		nodes_coordinates[new_node->get_node_coordinates()] = new_node;
		orig_to_new_node_pointers[onode] = new_node;
	}

	for (vector<Node>::iterator it = orig_grid.nodes.begin(); it != orig_grid.nodes.end(); ++it) {
		Node* onode = &(*it);
		Node* new_node = orig_to_new_node_pointers.find(onode)->second;
		for (vector<tuple<Node*, int, bool> >::iterator it = onode->neighbours.begin(); it != onode->neighbours.end(); ++it) {
			Node* new_neighbour = orig_to_new_node_pointers.find(get<0>(*it))->second;
			new_node->neighbours.push_back(make_tuple(new_neighbour, get<1>(*it), get<2>(*it)));
		}
	}
}

void Grid::init_grid(int width, int height, vector<string> lines) {
	this->width = width;
	this->height = height;
	nodes.reserve(sizeof(Node) * width * height);

	Node* top_neighbour;
	Node* left_neighbour;
	string line;
	for (int y = 0; y < height; y++) {
		line = lines[y];
		left_neighbour = NULL;
		for (int x = 0; x < width; x++) {
			top_neighbour = NULL;
			if (line[x] != '.') {
				int links = line[x] - 48;
				nodes.push_back(Node(x, y, links, nodes.size()));
				Node* this_node = &nodes.back();
				nodes_coordinates[this_node->get_node_coordinates()] = this_node;
				left_neighbour = find_left_neighbour(this_node);
				top_neighbour = find_top_neighbour(this_node);
				if (left_neighbour) {
					create_link(this_node, left_neighbour);
				}
				if (top_neighbour) {
					create_link(this_node, top_neighbour);
				}
			}
		}
	}
}

void Grid::create_link(Node* first, Node* second) {
	first->add_neighbour(second);
	second->add_neighbour(first);
}

void Grid::print_grid() {
	for (vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
		it->print_node();
	}
}

Node* Grid::find_top_neighbour(Node* current) {
	for (vector<Node>::reverse_iterator it = nodes.rbegin(); it != nodes.rend(); ++it) {
		if (it->x == current->x && it->y < current->y) {
			return &(*it);
		}
	}
	return NULL;
}

Node* Grid::find_left_neighbour(Node* current) {
	if (nodes.size() > 1) {
		Node* neighbour = &nodes.back();
		neighbour--;
		if (neighbour->y == current->y) {
			return neighbour;
		}
	}
	return NULL;
}

void Grid::fill_link(Node* first, Node* second, int links = 1) {
	int remove_neighbour_first = first->make_link(second, links);
	int remove_neighbour_second = second->make_link(first, links);
	if (remove_neighbour_first || remove_neighbour_second) {
		first->remove_neighbour(second);
		second->remove_neighbour(first);
	}
	if (first->links == 0) {
		remove_node_from_neighbours(first);
	}
	if (second->links == 0) {
		remove_node_from_neighbours(second);
	}
	remove_cross_links(first, second);
	ostringstream move;
	move <<
		first->x << " " << first->y << " " <<
		second->x << " " << second->y << " " <<
		links << endl;
	moves.push(move.str());
}

void Grid::fill_link(string move) {
	stringstream ss(move);
	string token;
	vector<int> tokens;
	while (getline(ss, token, ' ')) {
		tokens.push_back(stoi(token));
	}
	Node* first = get_node_at_coordinates(tokens[0], tokens[1]);
	Node* second = get_node_at_coordinates(tokens[2], tokens[3]);
	fill_link(first, second, tokens[4]);
}

void Grid::remove_node_from_neighbours(Node* node_to_delete) {
	for (vector<tuple<Node*, int, bool> >::iterator it = node_to_delete->neighbours.begin(); it != node_to_delete->neighbours.end(); ++it) {
		get<0>(*it)->remove_neighbour(node_to_delete);
		get<2>(*it) = false;
	}
}

void Grid::remove_cross_links(Node* first, Node* second) {
	int x1 = min(first->x, second->x);
	int x2 = max(first->x, second->x);
	int y1 = min(first->y, second->y);
	int y2 = max(first->y, second->y);

	if (first->x == second->x) {
		for (vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
			if (it->y > y1&& it->y < y2) {
				vector<Node*> active_neighbours = it->list_active_neighbours();
				for (auto& it2 : active_neighbours) {
					if (it2->y > y1&& it2->y < y2 && (it2->x > x1&& it->x < x1 || it2->x < x1 && it->x > x1)) {
						it->remove_neighbour(it2);
						it2->remove_neighbour(&(*it));
					}
				}
			}
		}
	}
	else {
		for (vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
			if (it->x > x1&& it->x < x2) {
				vector<Node*> active_neighbours = it->list_active_neighbours();
				for (auto& it2 : active_neighbours) {
					if (it2->x > x1&& it2->x < x2 && (it2->y > y1&& it->y < y1 || it2->y < y1 && it->y > y1)) {
						it->remove_neighbour(it2);
						it2->remove_neighbour(&(*it));
					}
				}
			}
		}
	}
}

void Grid::clear_single_nodes() {
	vector<Node*> active_nodes = list_active_nodes();
	for (vector<Node*>::iterator jit = active_nodes.begin(); jit != active_nodes.end(); jit++) {
		Node* it = *jit;
		if (it->links > 0 && it->active_neighbours() == 1) {
			fill_link(&(*it), it->first_active_neighbour());
		}
	}
}

void Grid::clear_max_nodes() {
	vector<Node*> active_nodes = list_active_nodes();
	for (vector<Node*>::iterator jit = active_nodes.begin(); jit != active_nodes.end(); jit++) {
		Node* it = *jit;
		if (it->links > 0 && it->links == it->possible_links_to_do() ) {
			int links_to_do = it->possible_links_to_do();
			for (vector<tuple<Node*, int, bool> >::iterator nit = it->neighbours.begin(); nit != it->neighbours.end(); nit++) {
				Node* neighbour = get<0>(*nit);
				if (get<2>(*nit) == false) {
					continue;
				}
				else if (neighbour->links >= 2 && get<1>(*nit) == 0) {
					fill_link(&(*it), neighbour, 2);
				}
				else if (neighbour->links >= 1 && get<1>(*nit) < 2) {
					fill_link(&(*it), neighbour, 1);
				}
			}
		}
	}
}

void Grid::clear_one_link_for_neighbour() {
	vector<Node*> active_nodes = list_active_nodes();
	for (vector<Node*>::iterator jit = active_nodes.begin(); jit != active_nodes.end(); jit++) {
		Node* it = *jit;
		if (it->links > 1 && it->links == 2 * it->active_neighbours() - 1) {
			vector<Node*> active_neighbours = it->list_active_neighbours();
			for (auto& it2 : active_neighbours) {
				it2->test_myself();
				fill_link(&(*it), it2);
			}
		}
	}
}

void Grid::test_grid() {
	for (vector<Node>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		it->test_myself();
	}
}

void Grid::execute_next_move() {
	cout << moves.front();
	moves.pop();
}

bool Grid::are_moves() {
	return moves.size() ? true : false;
}

vector<Node*> Grid::list_active_nodes() {
	vector<Node*> active_nodes;
	for (vector<Node>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		if (it->links) {
			active_nodes.push_back(&(*it));
		}
	}
	return active_nodes;
}

void Grid::clear_obvious() {
	clear_max_nodes();
	clear_single_nodes();
	clear_one_link_for_neighbour();
}

string Grid::get_identifier() {
	ostringstream identifier;
	int current_y = 0;
	for (vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
		if (it->y > current_y) {
			current_y = it->y;
			identifier << '|';
		}
		identifier << it->links << it->get_links_symbol();
	}
	return identifier.str();
}

void Grid::print_identifier() {
	cerr << get_identifier() << endl;
}

bool Grid::is_solved() {
	for (vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
		if (it->links > 0) {
			return false;
		}
	}
	return true;
}

bool Grid::solve() {
	int previous_moves = moves.size();
	while (!is_solved()) {
		clear_obvious();
		if (previous_moves == moves.size()) {
			string first;
			vector<Node*> active_neighbours;
			int min_active_neighbours = INT_MAX;
			for (vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
				if (it->links > 0 && it->active_neighbours() > 0 && it->active_neighbours() < min_active_neighbours) {
					first = it->get_node_coordinates();
					active_neighbours = it->list_active_neighbours();
					if (it->active_neighbours() == 2) {
						break;
					}
				}
			}
			if (first == "") {
				return false;
			}
			for (int i = 0; i < active_neighbours.size() - 1; i++) {
				Grid test_grid = *this;
				Node* ff = test_grid.nodes_coordinates.find(first)->second;
				Node* ss = test_grid.nodes_coordinates.find(active_neighbours[i]->get_node_coordinates())->second;
				test_grid.fill_link(ff, ss);
				bool test_result = test_grid.solve();
				if (test_result) {
					while (!test_grid.moves.empty()) {
						fill_link(test_grid.moves.front());
						test_grid.moves.pop();
					}
					return true;
				}
			}
			fill_link(nodes_coordinates.find(first)->second, 
				nodes_coordinates.find(active_neighbours.back()->get_node_coordinates())->second);
		}
		previous_moves = moves.size();
	}
	return is_correct_solution();
}

bool Grid::is_correct_solution() {
	if (!is_solved()) {
		return false;
	}
	map<int, bool> visited_nodes;
	stack<int> to_visit;
	to_visit.push(0);
	while (!to_visit.empty()) {
		int node_index = to_visit.top();
		to_visit.pop();
		Node current = nodes[node_index];
		visited_nodes[node_index] = true;
		for (vector<tuple<Node*, int, bool> >::iterator it = current.neighbours.begin(); it != current.neighbours.end(); ++it) {
			Node* neighbour = get<0>(*it);
			auto mit = visited_nodes.find(neighbour->id);
			if (get<1>(*it) > 0 && (mit == visited_nodes.end() || mit->second == false)) {
				to_visit.push(neighbour->id);
			}
		}
	}
	return visited_nodes.size() == nodes.size() ? true : false;
}

Node* Grid::get_node_at_coordinates(int x, int y) {
	ostringstream coordinates;
	coordinates << x << "," << y;
	auto it = nodes_coordinates.find(coordinates.str());
	return it != nodes_coordinates.end() ? it->second : NULL;
}

vector<string> Grid::get_grid_representation() {
	vector<string> grid_representation;
	for (int y = 0; y < height; y++) {
		ostringstream line;
		for (int x = 0; x < width; x++) {
			Node* node_at_coordinates = get_node_at_coordinates(x , y);
			if (node_at_coordinates != NULL) {
				line << max(node_at_coordinates->links, 0);
			}
			else {
				line << ".";
			}
		}
		grid_representation.push_back(line.str());
	}
	return grid_representation;
}