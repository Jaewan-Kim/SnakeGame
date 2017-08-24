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
	last_coord = locations_of_blocks[0];

	while (!game_over) {

		
		
		

		get_input();

		move();

		display();
		
		Sleep(100);

	}

}

void Game::display() {
	set_cursor_position(last_coord);
	cout << " ";
	set_cursor_position(locations_of_blocks[0]);
	cout << block;
	set_cursor_position(COORD{ (SHORT)22,(SHORT)number_of_rows + 2});
	cout << number_of_blocks;
}
void Game::get_input() {
	
	if (kbhit()) {
		switch (input = getch()) {
		case KEY_UP:
			if (direction != down)
				direction = up;
			break;
		case KEY_DOWN:
			if (direction != up)
				direction = down;
			break;
		case KEY_RIGHT:
			if (direction != left)
				direction = right;
			break;
		case KEY_LEFT:
			if (direction != right)
				direction = left;
			break;
		}
		return;
	}


}

void Game::new_block() {
	last_coord = locations_of_blocks[number_of_blocks - 1];
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
	previous_locations = locations_of_blocks;
	if (locations_of_blocks[0].X == block_location.X && locations_of_blocks[0].Y == block_location.Y) {

		new_block();
		set_cursor_position(block_location);
		cout << "O";
		number_of_blocks++;
		locations_of_blocks.push_back(last_coord);

	}
	last_coord.X = locations_of_blocks[number_of_blocks - 1].X;
	last_coord.Y = locations_of_blocks[number_of_blocks - 1].Y;
	if (direction == right) {
		if (locations_of_blocks[0].X == number_of_columns) {
			game_over = true;
		}
		else {
			locations_of_blocks[0].X++;
		}
	}
	else if (direction == left) {
		if (locations_of_blocks[0].X == 1) {
			game_over = true;
		}
		else {
			locations_of_blocks[0].X--;

		}
	}
	else if (direction == up) {
		if (locations_of_blocks[0].Y == 1)
			game_over = true;
		else
			locations_of_blocks[0].Y--;

	}
	else {
		if (locations_of_blocks[0].Y == number_of_rows)
			game_over = true;
		else		
			locations_of_blocks[0].Y++;

	}

	for (int i = 1; i < number_of_blocks; i++) {
		locations_of_blocks[i] = previous_locations[i - 1];
	}

	crash();
	
}

void Game::crash() {
	for (int i = 1; i < number_of_blocks; i++) {
		if (locations_of_blocks[0].X == locations_of_blocks[i].X && locations_of_blocks[0].Y == locations_of_blocks[i].Y) {
			game_over = true;
			return;
		}
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
	cout << endl;
	cout << "The current score is: ";

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