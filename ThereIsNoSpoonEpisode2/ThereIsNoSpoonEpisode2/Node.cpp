#include "Node.h"

Node::Node(int in_x, int in_y, int in_links, int in_id) {
	x = in_x;
	y = in_y;
	links = in_links;
	id = in_id;
}

void Node::print_node() {
	cerr << x << " " << y << " " << links << " " << active_neighbours() << endl;
}

void Node::add_neighbour(Node* neighbour) {
	bool is_active = neighbour->links > 0 && links > 0;
	neighbours.push_back(make_tuple(neighbour, 0, is_active));
}

void Node::remove_neighbour(Node* neighbour) {
	for (vector<tuple<Node*, int, bool> >::iterator it = neighbours.begin(); it != neighbours.end(); ++it) {
		if (get<0>(*it) == neighbour) {
			get<2>(*it) = false;
			return;
		}
	}
}

int Node::make_link(Node* neighbour, int connections = 1) {
	links -= connections;
	links = links < 0 ? 0 : links;
	for (vector<tuple<Node*, int, bool> >::iterator it = neighbours.begin(); it != neighbours.end(); ++it) {
		if (get<0>(*it) == neighbour) {
			get<1>(*it) += connections;
			if (get<1>(*it) == 2) {
				return 1;
			}
		}
	}
	return 0;
}

void Node::test_myself() {
	if (x > 30 || y > 30 || links > 8 || neighbours.size() > 4) {
		cerr << "bad node! ";
		print_node();
	}
	for (vector<tuple<Node*, int, bool> >::iterator it = neighbours.begin(); it != neighbours.end(); it++) {
		Node* it2 = get<0>(*it);
		if (it2->x > 30 || it2->y > 30 || it2->links > 8 || it2->neighbours.size() > 4) {
			cerr << "bad neighbour! ";
			it2->print_node();
		}
	}
}

int Node::active_neighbours() {
	int active = 0;
	for (vector<tuple<Node*, int, bool> >::iterator it = neighbours.begin(); it != neighbours.end(); it++) {
		if (get<2>(*it) == true) {
			active++;
		}
	}
	return active;
}

Node* Node::first_active_neighbour() {
	for (vector<tuple<Node*, int, bool> >::iterator it = neighbours.begin(); it != neighbours.end(); it++) {
		if (get<2>(*it) == true) {
			return get<0>(*it);
		}
	}
	return NULL;
}

vector<Node*> Node::list_active_neighbours() {
	vector<Node*> active_neighbours;
	for (vector<tuple<Node*, int, bool> >::iterator it = neighbours.begin(); it != neighbours.end(); it++) {
		if (get<2>(*it) == true) {
			active_neighbours.push_back(get<0>(*it));
		}
	}
	return active_neighbours;
}

int Node::get_right_neighbour_links() {
	for (vector<tuple<Node*, int, bool> >::iterator it = neighbours.begin(); it != neighbours.end(); it++) {
		Node* neighbour = get<0>(*it);
		if (neighbour->y == y && neighbour->x > x) {
			return get<1>(*it);
		}
	}
	return 0;
}

// Links symbol generated from right and bottom links
string Node::get_links_symbol() {
	int right_links = 0;
	int bottom_links = 0;
	char symbols[] = "abc";
	ostringstream links_symbol;
	links_symbol << symbols[right_links] << symbols[bottom_links];
	return links_symbol.str();
}

string Node::get_node_coordinates() {
	ostringstream coordinates;
	coordinates << x << "," << y;
	return coordinates.str();
}

int Node::possible_links_to_do() {
	int sum = 0;
	for (vector<tuple<Node*, int, bool> >::iterator it = neighbours.begin(); it != neighbours.end(); it++) {
		Node* neighbour = get<0>(*it);
		if (neighbour->links <= 0) {
			continue;
		}
		if (get<1>(*it) == 0) {
			sum += min(2, neighbour->links);
		}
		else if (get<1>(*it) == 1 && neighbour->links > 0) {
			sum += 1;
		}
	}
	return sum;
}