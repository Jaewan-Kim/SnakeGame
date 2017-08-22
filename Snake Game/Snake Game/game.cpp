#include "game.h"

void Game::start_game() {
	cout << "How many rows? ";
	cin >> number_of_rows;
	cout << "How many columns? ";
	cin >> number_of_columns;

	show_console_cursor(false);
	system("CLS");
	draw_board();
	locations_of_blocks.push_back(COORD{ 1,1 });
	number_of_blocks = 1;
	set_cursor_position(locations_of_blocks[0]);
	cout << block;
	new_block();
	set_cursor_position(block_location);
	cout << "O";

	while (!game_over) {
		
		if (kbhit()) {
			switch (input = getch()) {
			case KEY_UP:
				direction = up;
				break;
			case KEY_DOWN:
				direction = down;
				break;
			case KEY_RIGHT:
				direction = right;
				break;
			case KEY_LEFT:
				direction = left;
				break;
			}
		}
		set_cursor_position(locations_of_blocks[number_of_blocks-1]);
		cout << "X";


		move();
		set_cursor_position(locations_of_blocks[0]);
		cout << block;
		
		
		Sleep(100);


	}

}


void Game::new_block() {
	while (true) {
		int x = rand() % number_of_columns + 1;
		int y = rand() % number_of_rows + 1;
		block_location = COORD{ (SHORT)x, (SHORT)y };
		int count= 0;
		for (COORD c : locations_of_blocks) {
			if (!(c.X == x && c.Y == y)) {
				count++;
			}
		}
		if (count == number_of_blocks)
			break;
	}
}

void Game::move() {
	last_coord = locations_of_blocks[number_of_blocks - 1];
	if (direction == right) {
		if (locations_of_blocks[0].X == number_of_columns) {
			game_over = true;
		}
		else {
			for (COORD& c : locations_of_blocks) {
				c.X = c.X +1;
			}
		}
	}
	else if (direction == left) {
		if (locations_of_blocks[0].X == 1) {
			game_over = true;
		}
		else {
			for (COORD& c : locations_of_blocks) {
				c.X = c.X - 1;
			}
		}
	}
	else if (direction == up) {
		if (locations_of_blocks[0].Y == 1)
			game_over = true;
		else
			for (COORD& c : locations_of_blocks) {
				c.Y = c.Y -1;
			}
	}
	else {
		if (locations_of_blocks[0].Y == number_of_rows)
			game_over = true;
		else
			for (COORD& c : locations_of_blocks)
				c.Y = c.Y +1;
	}

	if (locations_of_blocks[0].X == block_location.X && locations_of_blocks[0].Y == block_location.Y) {
		new_block();
		set_cursor_position(block_location);
		cout << "O";
		number_of_blocks++;
		locations_of_blocks.push_back(last_coord);

	}
}


void Game::draw_board() {
	for (int i = 0; i < number_of_columns+2; i++) {
		cout << block;
	}
	cout << endl;
	for (int i = 0; i < number_of_rows; i++) {
		cout << block;
		for (int i = 0; i < number_of_columns; i++)
			cout << " ";
		cout << block;
		cout << endl;
	}
	for (int i = 0; i < number_of_columns + 2; i++) {
		cout << block;
	}

}










void Game::show_console_cursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
void Game::set_cursor_position(COORD coord)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout.flush();
	SetConsoleCursorPosition(hOut, coord);
}