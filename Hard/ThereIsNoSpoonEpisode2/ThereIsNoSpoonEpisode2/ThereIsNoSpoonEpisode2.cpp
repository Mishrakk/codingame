#include <iostream>
#include <vector>
#include <queue>
#include <sstream>

#include "Node.h"
#include "Grid.h"

using namespace std;

int main() {
	Grid grid;
	grid.test_grid();
	grid.print_grid();
	do {
		grid.print_identifier();
		grid.clear_obvious();
		grid.execute_next_move();
	} while (grid.are_moves());
	return 0;
}
