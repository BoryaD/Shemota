#include <io.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
using namespace std;
/* x
   0 o x o x o x o x
   1 x o x o x o x o
   2 o x o x o x o x
   3 x o x o x o x o
   4 o x o x o x o x  x-black
   5 x o x o x o x o  o-white
   6 o x o x o x o x
   7 x o x o x o x o
	 0 1 2 3 4 5 6 7 y
	start ches pos-

	14 12 13 15 16 13 12 14
	11 11 11 11 11 11 11 11 blackside      1 pawn(the peshka)
	0  0  0  0  0  0  0  0                2 kneght(kon)
	0  0  0  0  0  0  0  0                3 bishop (slon)
	0  0  0  0  0  0  0  0                4 rook(ladya)
	0  0  0  0  0  0  0  0                5 qeen(ferz)
	1  1  1  1  1  1  1  1 white side     6 king
	4  2  3  5  6  3  2  4                0 empty
	led - 0 no light, 1 -white ,2- red;

	on expected matrix 1 up, 2 down
*/


byte turn = 0;//0 white ,1 black;
byte expected[8][8] = {
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {1,1,1,1,1,1,1,1},
   {1,1,1,1,1,1,1,1}

};
byte led[8][8] = {
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0}

};

byte indicationMtrixNew[8][8] = {
   {1,1,1,1,1,1,1,1},
   {1,1,1,1,1,1,1,1},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {1,1,1,1,1,1,1,1},
   {1,1,1,1,1,1,1,1}

};





byte indicationMtrixOld[8][8] = {
   {1,1,1,1,1,1,1,1},
   {1,1,1,1,1,1,1,1},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {1,1,1,1,1,1,1,1},
   {1,1,1,1,1,1,1,1}

};

byte startMatrix[8][8] = {
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1}
};

byte chess[8][8] = {
	{14,12,13,16,15,1,1,1},
	{11,11,11,11,11,11,11,11},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1},
	{4,2,3,5,6,3,2,4}
};


byte outA = 5, outB = 6, outC = 7, analogOut = 19;

byte inA = 8, inB = 9, inC = 10, analogIn = 20;
/*void setup() {
	pinMode(outA, OUTPUT);//first mx/dc comtrol input
	pinMode(outB, OUTPUT);//
	pinMode(outC, OUTPUT);//
	pinMode(analogOut, OUTPUT);//first mx/dc input sugnal
	pinMode(inA, OUTPUT);//
	pinMode(inB, OUTPUT);//second mx/dc comtrol input
	pinMode(inC, OUTPUT);//
	pinMode(analogIn, INPUT);//second mx/dc output

}
void demuxOut(int x, int u) {//u 0-255
	digitalWrite(outA, x & 4);
	digitalWrite(outB, x & 2);
	digitalWrite(outC, x & 1);
	analogWrite(analogOut, u);
}
byte demuxIn(int j) {//u 0-255
	digitalWrite(outA, x & 4);
	digitalWrite(outB, x & 2);
	digitalWrite(outC, x & 1);
	return analogRead(analogIn);
}

byte getPos(byte x, byte y) {
	demuxOut(x, 200);
	if (demuxIn(y) > 100) return 1;
	return 0;
}
*/

byte getPos(byte x, byte y) {
	return indicationMtrixNew[x][y];
}
void copyNewToOld() {
	for (byte i = 0; i < 8; i++)
	{
		for (byte j = 0; j < 8; j++)
		{
			indicationMtrixOld[i][j] = indicationMtrixNew[i][j];
		}
	}
}

void check() {
	for (byte i = 0; i < 8; i++)
	{
		for (byte j = 0; j < 8; j++)
		{
			indicationMtrixNew[i][j] = getPos(i, j);
		}
	}
}
void refreshIndicationMatrix() {
	copyNewToOld();
	check();

}
byte dif(byte mat1[8][8], byte mat2[8][8]) {
	byte flag = 65;
	for (byte i = 0; i < 8; i++)
	{
		for (byte j = 0; j < 8; j++)
		{
			if (mat1[i][j] != mat2[i][j]) {
				if (flag == 65) {
					flag = 8 * i + j;
				}
				else {
					flag = 66;
				}
			}
			
		}
	}
	return flag;

}
byte compare(byte mat1[8][8], byte mat2[8][8]) {
	byte flag = 0;
	for (byte i = 0; i < 8; i++)
	{
		for (byte j = 0; j < 8; j++)
		{
			if (mat1[i][j] != mat2[i][j]) {
				flag = 1;

			}
		}
	}
	return flag;
}
void lightOff() {

	for (byte i = 0; i < 8; i++)
	{
		for (byte j = 0; j < 8; j++)
		{
			led[i][j] = 0;

		}
	}
}

void exOff() {
	for (byte i = 0; i < 8; i++)
	{
		for (byte j = 0; j < 8; j++)
		{
			expected[i][j] = 0;

		}
	}
}


byte chesInSpace;
//----------------------------------------------
bool isEmpty(byte y, byte x) {
	if (chess[x][y] == 0)return true;
	return false;
}
bool isEnemy(byte y, byte x, byte ch) {
	if (ch < 10 && (chess[x][y] > 10 && chess[x][y] < 20))return true;
	if (ch > 10 && (chess[x][y] > 0 && chess[x][y] < 10))return true;
	return false;
}

void bishopEx(byte x, byte y) {
	int ht = 0;
	for (int i = x + 1, j = y + 1; i < 8, j < 8; i++, j++) {
		if (isEmpty(i, j)) {
			expected[x][j] = 1;
			led[i][j] = 2;
		}
		else
		{
			if (isEnemy(i, j, chesInSpace) && ht == 0) {
				expected[i][j] = 1;
				led[i][j] = 2;
				ht = 1;
			}
			else
			{
				break;
			}
		}
	}
	ht = 0;
	for (int i = x - 1, j = y; i >= 0, j < 8; i--, j++) {
		if (isEmpty(i, j)) {
			expected[x][j] = 1;
			led[i][j] = 2;
		}
		else
		{
			if (isEnemy(i, j, chesInSpace) && ht == 0) {
				expected[i][j] = 1;
				led[i][j] = 2;
				ht = 1;
			}
			else
			{
				break;
			}
		}
	}
	ht = 0;
	for (int i = x, j = y - 1; i < 8, j >= 0; i++, j--) {
		if (isEmpty(i, j)) {
			expected[x][j] = 1;
			led[i][j] = 2;
		}
		else
		{
			if (isEnemy(i, j, chesInSpace) && ht == 0) {
				expected[i][j] = 1;
				led[i][j] = 2;
				ht = 1;
			}
			else
			{
				break;
			}
		}
	}
	ht = 0;
	for (int i = x - 1, j = y - 1; i >= 0, j >= 0; i--, j--) {
		if (isEmpty(i, j)) {
			expected[x][j] = 1;
			led[i][j] = 2;
		}
		else
		{
			if (isEnemy(i, j, chesInSpace)&&ht==0) {
				expected[i][j] = 1;
				led[i][j] = 2;
				ht = 1;
			}
			else
			{
				break;
			}
		}
	}
}

void rockEx(byte x, byte y) {
	int ht = 0;
	for (byte i = x + 1; i < 8; i++) {
		if (isEmpty(i, y)) {
			expected[i][y] = 1;
			led[i][y] = 2;
		}
		else
		{
			if (isEnemy(i, y, chesInSpace)&&ht==0) {
				expected[i][y] = 1;
				led[i][y] = 2;
				ht = 1;
			}
			else
			{
				break;
			}
		}
		
		
	}
	ht = 0;
	for (byte i = x - 1; i >= 0; i--) {
		if (isEmpty(i, y)) {
			expected[i][y] = 1;
			led[i][y] = 2;
			ht = 1;
		}
		else
		{
			if (isEnemy(i, y, chesInSpace) && ht == 0) {
				expected[i][y] = 1;
				led[i][y] = 2;
				ht = 1;
			}
			else
			{
				break;
			}
		}
		
		
	}

	ht = 0;
	for (byte i = y + 1; i < 8; i++) {
		if (isEmpty(x, i)) {
			expected[x][i] = 1;
			led[x][i] = 2;
			ht = 1;
		}
		else
		{
			if (isEnemy(x, i, chesInSpace) && ht == 0) {
				expected[x][i] = 1;
				led[x][i] = 2;
				ht = 1;
			}
			else
			{
				break;
			}
		}
		
		
	}
	ht = 0;
	for (byte i = y - 1; i >= 0; i--) {
		if (isEmpty(x, i)) {
			expected[x][i] = 1;
			led[x][i] = 2;
		}
		else
		{
			if (isEnemy(x, i, chesInSpace) && ht == 0) {
				expected[x][i] = 1;
				led[x][i] = 2;
				ht = 1;
			}
			else
			{
				break;
			}
		}
		
		
	}
}
void refreshExepted(byte y, byte x, byte olState, byte newState) {
	exOff();
	lightOff();
	byte chesType = chesInSpace;
	if (chesInSpace > 10)chesType -= 10;
	if (olState == 0 && newState == 1) {
		switch (chesType) {
		case 1: {
			if (chesInSpace > 10) {
				if (isEmpty(y + 1, x)) {
					expected[y + 1][x] = 2;
					led[y + 1][x] = 1;
				}
				if (isEnemy(y + 1, x-1, chesInSpace)) {
					expected[y + 1][x - 1] = 1;
					led[y + 1][x - 1] = 2;
				}
				if (isEnemy(y + 1, x+1, chesInSpace)) {
					expected[y + 1][x + 1] = 1;
					led[y + 1][x + 1] = 2;
				}//blackpawn
			}
			else {
				//white pawn
				if (isEmpty( y - 1,x)) {
					expected[y - 1][x] = 2;
					led[y - 1][x] = 1;
				}
				if (isEnemy(x + 1, y - 1, chesInSpace)) {
					expected[x + 1][y + 1] = 1;
					led[x + 1][y + 1] = 2;
				}
				if (isEnemy(x - 1, y - 1, chesInSpace)) {
					expected[x - 1][y + 1] = 1;
					led[x - 1][y + 1] = 2;
				}
			}
		}; break;
		case 2: {
			if (isEmpty(x + 2, y + 1)) {
				expected[x + 2][y + 1] = 2;
				led[x + 2][y + 1] = 1;
			}
			if (isEnemy(x + 2, y + 1, chesInSpace)) {
				expected[x + 2][y + 1] = 1;
				led[x + 2][y + 1] = 2;
			}

			///
			if (isEmpty(x + 2, y - 1)) {
				expected[x + 2][y - 1] = 2;
				led[x + 2][y - 1] = 1;
			}
			if (isEnemy(x + 2, y - 1, chesInSpace)) {
				expected[x + 2][y - 1] = 1;
				led[x + 2][y - 1] = 2;
			}
			///
			if (isEmpty(x + 1, y + 2)) {
				expected[x + 1][y + 2] = 2;
				led[x + 1][y + 2] = 1;
			}
			if (isEnemy(x + 1, y + 2, chesInSpace)) {
				expected[x + 1][y + 2] = 1;
				led[x + 1][y + 2] = 2;
			}
			//
			if (isEmpty(x - 1, y + 2)) {
				expected[x - 1][y + 2] = 2;
				led[x - 1][y + 2] = 1;
			}
			if (isEnemy(x - 1, y + 2, chesInSpace)) {
				expected[x - 1][y + 2] = 1;
				led[x - 1][y + 2] = 2;
			}
			//
			if (isEmpty(x - 1, y - 2)) {
				expected[x - 1][y - 2] = 2;
				led[x - 1][y - 2] = 1;
			}
			if (isEnemy(x - 1, y - 2, chesInSpace)) {
				expected[x - 1][y - 2] = 1;
				led[x - 1][y - 2] = 2;
			}
			//
			if (isEmpty(x + 1, y - 2)) {
				expected[x + 1][y - 2] = 2;
				led[x + 1][y - 2] = 1;
			}
			if (isEnemy(x + 1, y - 2, chesInSpace)) {
				expected[x + 1][y - 2] = 1;
				led[x + 1][y - 2] = 2;
			}
			//
			if (isEmpty(x - 2, y - 1)) {
				expected[x - 2][y - 1] = 2;
				led[x - 2][y - 1] = 1;
			}
			if (isEnemy(x - 2, y - 1, chesInSpace)) {
				expected[x - 2][y - 1] = 1;
				led[x - 2][y - 1] = 2;
			}
			//
			if (isEmpty(x - 2, y + 1)) {
				expected[x - 2][y + 1] = 2;
				led[x - 2][y + 1] = 1;
			}
			if (isEnemy(x - 2, y + 1, chesInSpace)) {
				expected[x - 2][y + 1] = 1;
				led[x - 2][y + 1] = 2;
			}
		}; break;
		case 3: {

			bishopEx(y, x)
				;
		}; break;//bishop
		case 4: {

			rockEx(y, x);
		}; break;//rock
		case 5: {
			bishopEx(y, x);
				rockEx(y, x);
		}; break;//ferz
		case 6: {
			if (isEmpty(x, y + 1)) {
				expected[x][y + 1] = 2;
				led[x][y + 1] = 1;
			}
			if (isEnemy(x, y + 1, chesInSpace)) {
				expected[x + 1][y + 1] = 1;
				led[x + 1][y + 1] = 2;
			}

			///
			if (isEmpty(x + 1, y + 1)) {
				expected[x + 1][y + 1] = 2;
				led[x + 1][y + 1] = 1;
			}
			if (isEnemy(x + 1, y + 1, chesInSpace)) {
				expected[x + 1][y + 1] = 1;
				led[x + 1][y + 1] = 2;
			}
			///
			if (isEmpty(x + 1, y)) {
				expected[x + 1][y] = 2;
				led[x + 1][y] = 1;
			}
			if (isEnemy(x + 1, y, chesInSpace)) {
				expected[x + 1][y] = 1;
				led[x + 1][y] = 2;
			}
			//
			if (isEmpty(x + 1, y - 1)) {
				expected[x + 1][y - 1] = 2;
				led[x + 1][y - 1] = 1;
			}
			if (isEnemy(x + 1, y - 1, chesInSpace)) {
				expected[x + 1][y - 1] = 1;
				led[x + 1][y - 1] = 2;
			}
			//
			if (isEmpty(x, y - 1)) {
				expected[x][y - 1] = 2;
				led[x][y - 1] = 1;
			}
			if (isEnemy(x, y - 1, chesInSpace)) {
				expected[x][y - 1] = 1;
				led[x][y - 1] = 2;
			}
			//
			if (isEmpty(x - 1, y - 1)) {
				expected[x - 1][y - 1] = 2;
				led[x - 1][y - 1] = 1;
			}
			if (isEnemy(x - 1, y - 1, chesInSpace)) {
				expected[x - 1][y - 1] = 1;
				led[x - 1][y - 1] = 2;
			}
			//
			if (isEmpty(x - 1, y)) {
				expected[x - 1][y] = 2;
				led[x - 1][y] = 1;
			}
			if (isEnemy(x - 1, y, chesInSpace)) {
				expected[x - 1][y] = 1;
				led[x - 1][y] = 2;
			}
			//
			if (isEmpty(x - 1, y + 1)) {
				expected[x - 1][y + 1] = 2;
				led[x - 1][y + 1] = 1;
			}
			if (isEnemy(x - 1, y + 1,chesInSpace)) {
				expected[x - 1][y + 1] = 1;
				led[x - 1][y + 1] = 2;
			}
			//
		}; break;//ferz
		}
	}
	if (newState == 0) {
		lightOff();
			exOff();
		chess[x][y] = chesInSpace;
		if (turn == 0) { turn == 1; }
		else { turn = 0; }

		if (turn == 0) {
			//wait white figure up
			for (byte i = 0; i < 8; i++)
			{
				for (byte j = 0; j < 8; j++)
				{
					if (chess[i][j] != 0 && chess[i][j] < 10) {
						expected[i][j] = 1;

					}
				}
			}
		}
		if (turn == 1) {
		
			for (byte i = 0; i < 8; i++)
			{
				for (byte j = 0; j < 8; j++)
				{
					if (chess[i][j] != 0 && chess[i][j] < 10) {
						expected[i][j] = 1;

					}
				}
			}
		}
	}
	if (newState == 2) {
		//wait down figure in same place
		expected[x][y] = 2;
		led[x][y] = 1;
	}
}


//-----------------------------
byte state = 0;//0 vse stabilno ,1 figura podnyta ,2 dve figuri podnyto

void gameCore() {
	byte cor = dif(indicationMtrixNew,indicationMtrixOld);
	byte x, y, what;
	if (cor < 65) {
		y = cor / 8;
		x = cor % 8;
		if (indicationMtrixNew[y][x] == 1 && indicationMtrixOld[y][x] == 0 && (state == 1 || state == 2)) {
			
			lightOff();
			refreshExepted(y,x,state,0);
			state = 0;
		}
		if (indicationMtrixNew[y][x] == 0 && indicationMtrixOld[y][x] == 1 && state == 0) {
			chesInSpace = chess[y][x];
			chess[y][x] = 0;
			refreshExepted(y, x, state, 1);
				state = 1;
		}
		if (indicationMtrixNew[y][x] == 0 && indicationMtrixOld[y][x] == 1 && state == 1) {
		
			refreshExepted(y, x, state, 2);
			state = 2;
		}
	}


}
//-----------------------------
byte start = 0;
void loop() {
	refreshIndicationMatrix();
	if (compare(indicationMtrixNew, startMatrix) == 0) {
		start = 1;
	}
	if (start == 1) {
		gameCore();
	}

}
void kostil() {
	char c;
	cin >> c;
	if (c != 'n') {
		int x, y;
		cin >> y;
		cin >> x;
		if (indicationMtrixNew[x][y] == 0) {
			indicationMtrixNew[x][y] = 1;
		}
		else
		{
			indicationMtrixNew[x][y] = 0;
		}
	}
}

int main() {
	while (true) {
		kostil();
		gameCore();
	}

	return 0;
}