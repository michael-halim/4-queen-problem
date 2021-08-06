#include<iostream>
#define SIZE 4
using namespace std;

class Pawn {
	int row, col;

	char ch,restart;
public:
	Pawn() {
		ch = '#';
		row = NULL;
		col = NULL;
		restart = 'g';
	}
	void changeColMap() {
		if (col < SIZE-1) {
			col++;
		}
	}
	void setRes() {
		restart = 'f';
	}
	int getCol() {
		return col;
	}
	char getRes() {
		return restart;
	}
	void setCoord(int row, int col) {
		this->row = row;
		this->col = col;
	}
	void setChar(char ch) {
		this->ch = ch;
	}
	int getRow() {
		return row;
	}
	
	int getChar() {
		return ch;
	}
	bool checkRow(int row,char** map) {
		int count = 0;
		for (int i = 0; i < SIZE; i++)	
			if (map[row][i] == '#')
				count++;

		return count > 1; //kalo lebih besar dari 1 artinya nabrak
	}
	bool checkCol(int col, char** map) {
		int count = 0;
		for (int i = 0; i < SIZE; i++)
			if (map[i][col] == '#')
				count++;

		return count > 1; //kalo lebih besar dari 1 artinya nabrak
	}
	bool checkDiag(int row, int col, char** map) {
		int count = 0;
		for (int i = 1; i < SIZE; i++){					
			if (row - i < 0 || col - i < 0)		break;		
			else {
				if (map[row - i][col - i] == '#')
					count++;
			}
		}
		for (int i = 1; i < SIZE; i++) {
			if (row - i < 0 || col + i > SIZE-1)		break;
			else {
				if (map[row - i][col + i] == '#')
					count++;
			}
		}
		for (int i = 1; i < SIZE; i++) {
			if (row + i > SIZE-1 || col - i < 0)		break;
			else {
				if (map[row + i][col - i] == '#')
					count++;
			}
		}
		for (int i = 1; i < SIZE; i++) {
			if (row + i > SIZE-1 || col + i > SIZE-1)		break;
			else {
				if (map[row + i][col + i] == '#')
					count++;
			}
		}
		return count > 0;		//kalo lebih besar dari 0 artinya nabrak
	}
	bool isCollided(char**map) {
		if (checkCol(col, map) || checkRow(row, map) || checkDiag(row, col, map)) 
			return true;
		return false;
	}
	//d = different row || s = same row
	void placeQueen(char** map, int row, char ch= 'd') {
		if (ch == 's') {
			map[this->row][this->col-1] = '.';
			
		}
		setCoord(row, col);
		map[row][col] = getChar();
	}
	void resetAll() {
		row = NULL;
		col = NULL;
	}
};
void displayMap(char** map) {
	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			cout << map[i][j] << " ";
		}
		cout << '\n';
	}
	cout << endl;
}
void resetMap(char** map) {
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			map[i][j] = '.';
}
void solve(Pawn* queen, char** map, int row, char ch,bool& reset, bool& solved) {
	
	bool changeCol = false;
	
	do {
		if (row == SIZE) {
			bool checkCollided = false;					//cek kalo sudah diletakkan semua apakah ada yang nabrak
			for (int i = 0; i < SIZE; i++)
			{
				if (queen[i].isCollided(map)) {
					checkCollided = true;
					break;
				}

			}
			if (!checkCollided) {
				solved = true;
				break;

			}
		}														// 's' artinya same || 'd' artinya different , itu reference ke kolom nya 
		queen[row].placeQueen(map, row, 'd');					//taruh queen di tempat yang berbeda kolom
		displayMap(map);
		if (!queen[row].isCollided(map)) {
			solve(queen, map, row + 1, 'd', reset, solved);
			if (reset) {
				if (row == 0) {
					changeCol = true;
				}
				else {
					return;
				}
			}
		}
		else {
			queen[row].changeColMap();
			queen[row].placeQueen(map, row, 's');
			displayMap(map);
		}
		if (queen[row].isCollided(map) && queen[row].getCol() == SIZE-1 && !solved) {		//kalo sudah mentok reset dari awal
			reset = true;
			return;
			changeCol = true;
		}
		
		if (changeCol) {																//ganti kolom kalo sudah reset
			resetMap(map);
			queen[row].changeColMap();
			queen[row].placeQueen(map, row, 's');

			for (int i = 1; i < SIZE; i++)
				queen[i].resetAll();
			
			changeCol = false;
			displayMap(map);
			solve(queen, map, row + 1, 'd', reset, solved);
			
		}
		
	} while (!solved);

	cout << "Congratulations You Have Done it !!" << endl;
}
int main() {
	int row = 0,col = 0;
	char** map = new char* [SIZE];
	for (int i = 0; i < SIZE; i++)
		map[i] = new char[SIZE];

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			map[i][j] = '.';

	Pawn* queen = new Pawn [SIZE];
	
	bool reset = false;
	bool solved = false;
	solve(queen, map, row, 'g',reset,solved);


}