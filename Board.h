#pragma once
#include "Tile.h"
#include<string>
#include <vector>
using namespace std;

struct Board
{
	int width;
	int height;
	int mine_count;
	int tile_count;
	int flag_count;
	vector <int> board;

	Board();
	void LoadBoard(string board_filename);
	void LoadRandBoard();
	vector<vector<Tile>> LoadMineField();
	bool Win(vector<vector<Tile>>& grid);
	bool Lose(vector<vector<Tile>>& grid);
	vector<int> Counter(int number);
};