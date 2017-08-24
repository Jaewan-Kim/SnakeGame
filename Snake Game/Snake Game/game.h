#ifndef GAME
#define GAME

#include <vector>
#include <conio.h>
#include <Windows.h>
#include <iostream>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class Game {
	//variablese
	COORD last_coord;
	bool block_exists = true;;
	int input;
	int number_of_blocks;
	vector<COORD> locations_of_blocks;
	vector<COORD> previous_locations;
	char block = 254;
	int number_of_rows;
	int number_of_columns;
	int const left = 0;
	int const right = 1;
	COORD block_location;
	int const up = 2; 
	int const down = 3;
	int direction = right;
	bool game_over = false;
	//functions
	void draw_board();
	void show_console_cursor(bool show_flag);
	void set_cursor_position(COORD coord);
	void move();
	void crash();
	void get_input();
	void display();
	void new_block();

public:
	void start_game();
};

#endif