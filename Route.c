/*
 ============================================================================
 Name        : Route.c
 Author      : NGO QUOC HUNG
 Version     : 2.0.0
 Copyright   : Copyright
 Description : Route
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "graphics.h"
#pragma comment(lib, "graphics.lib")

//typedef struct p {
//	int x;
//	int y;
//} POINT;

int gd = DETECT, gm;

int input[9][6] = { { 1, 1, 1, 1 }, 
					{ 0, 0, 0, 0, 1 }, 
					{ 0, 1, 1, 0 },
					{ 0, 1, 0, 1, 1 },
					{ 0, 0, 1, 0 },
					{ 0, 1, 1, 1, 1 },
					{ 0, 0, 1, 0 },
					{ 0, 1, 0, 0, 1 },
					{ 0, 1, 1, 1 } };

int matrix[11][10];

POINT graphMatrix[11][10];

void createMatrix() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 6; j++) {
			if (i % 2 == 0) {
				matrix[i + 1][j * 2 + 1] = input[i][j];
				matrix[i + 1][j * 2] =
					matrix[i + 1][j * 2] == 0 ?
					input[i][j] : matrix[i + 1][j * 2];
				matrix[i + 1][j * 2 + 2] =
					matrix[i + 1][j * 2 + 2] == 0 ?
					input[i][j] : matrix[i + 1][j * 2 + 2];
			}
			else {
				matrix[i + 1][j * 2] = input[i][j];
				matrix[i][j * 2] =
					matrix[i][j * 2] == 0 ? input[i][j] : matrix[i][j * 2];
				matrix[i + 2][j * 2] =
					matrix[i + 2][j * 2] == 0 ?
					input[i][j] : matrix[i + 2][j * 2];
			}
		}
	}
}

void showMatrix() {
	printf("\nMatrix:\n");
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%3d", matrix[i][j]);
			fflush(stdout);
		}
		printf("\n");
		fflush(stdout);
	}
}

void deleteMatrix() {
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 10; j++) {
			matrix[i][j] = 0;
		}
	}
}

bool isNearWall(int x, int y) {
	if (x - 1 >= 0) {
		if (matrix[x - 1][y] == 1) {
			return true;
		}
	}
	if (x + 1 < 11) {
		if (matrix[x + 1][y] == 1) {
			return true;
		}
	}
	if (y - 1 >= 0) {
		if (matrix[x][y - 1] == 1) {
			return true;
		}
	}
	if (y + 1 < 10) {
		if (matrix[x][y + 1] == 1) {
			return true;
		}
	}
	if (x - 1 >= 0 && y - 1 >= 0) {
		if (matrix[x - 1][y - 1] == 1) {
			return true;
		}
	}
	if (x + 1 < 11 && y + 1 < 10) {
		if (matrix[x + 1][y + 1] == 1) {
			return true;
		}
	}
	if (x - 1 >= 0 && y + 1 < 10) {
		if (matrix[x - 1][y + 1] == 1) {
			return true;
		}
	}
	if (x + 1 < 11 && y - 1 >= 0) {
		if (matrix[x + 1][y - 1] == 1) {
			return true;
		}
	}
	return false;
}

POINT findWay(POINT p, POINT c, int value) {
	POINT point;
	point.x = 0;
	point.y = 0;

	if (c.x - 1 >= 0) {
		if (!(c.x - 1 == p.x && c.y == p.y)) {
			if (matrix[c.x - 1][c.y] == value && isNearWall(c.x - 1, c.y)) {
				point.x = c.x - 1;
				point.y = c.y;
			}
		}
	}

	if (c.x + 1 < 11) {
		if (!(c.x + 1 == p.x && c.y == p.y)) {
			if (matrix[c.x + 1][c.y] == value && isNearWall(c.x + 1, c.y)) {
				point.x = c.x + 1;
				point.y = c.y;
			}
		}
	}

	if (c.y - 1 >= 0) {
		if (!(c.x == p.x && c.y - 1 == p.y)) {
			if (matrix[c.x][c.y - 1] == value && isNearWall(c.x, c.y - 1)) {
				point.x = c.x;
				point.y = c.y - 1;
			}
		}
	}

	if (c.y + 1 < 10) {
		if (!(c.x == p.x && c.y + 1 == p.y)) {
			if (matrix[c.x][c.y + 1] == value && isNearWall(c.x, c.y + 1)) {
				point.x = c.x;
				point.y = c.y + 1;
			}
		}
	}

	return point;
}

//前点とカレント点の座標から歩き向きを判定する
char currentDirection(int pX, int pY, int cX, int cY) {
	if ((cX == pX) && (cY > pY))
		return 'R';
	if ((cX == pX) && (cY < pY))
		return 'L';
	if ((cY == cY) && (cX > pX))
		return 'D';
	if ((cY == cY) && (cX < pX))
		return 'U';
}

void createGraph() {
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 10; j++) {
			POINT p;
			p.x = j * 40 + 10;
			p.y = i * 40 + 10;
			graphMatrix[i][j] = p;

			if (matrix[i][j] == 0)
			{
				setcolor(WHITE);
				circle(p.x, p.y, 10);
			}
			else
			{
				setcolor(RED);
				//bar(p.x - 20, p.y - 20, p.x + 20, p.y + 20);
				rectangle(p.x - 20, p.y - 20, p.x + 20, p.y + 20);
			}
		}
	}
}

void printfResulf(char *output, int index) {
	char *result = (char *)malloc(index + 1);
	result = output;
	*(result + index + 1) = '\0';
	setcolor(14);
	outtextxy(graphMatrix[10][0].x + 20, graphMatrix[10][0].y + 20, result);
}

int main()
{
	initgraph(&gd, &gm, "c:\\tc\\bgi");

	do
	{
		clearviewport();
		bool bComeBack = false;
		int value = 0, index = 7;
		char *output = (char *)malloc(100);
		*output = 'R', *(output + 1) = 'e', *(output + 2) = 's', *(output + 3) = 'u', *(output + 4) = 'l', *(output + 5) = 't', *(output + 6) = ':';
		
		// 前点
		POINT p;
		p.x = 0;
		p.y = 0;

		// カレント点
		POINT c;

		createMatrix();
		showMatrix();
		createGraph();

		if (matrix[p.x][p.y + 1] == 1) {
			c.x = p.x + 1;
			c.y = p.y;
		}
		setcolor(13);
		circle(graphMatrix[p.x][p.y].x, graphMatrix[p.x][p.y].y, 10);

		if (matrix[p.x + 1][p.y] == 1) {
			c.x = p.x;
			c.y = p.y + 1;
		}
		setcolor(5);
		circle(graphMatrix[c.x][c.y].x, graphMatrix[c.x][c.y].y, 10);

		matrix[c.x][c.y] -= 1;
		*(output + index) = currentDirection(p.x, p.y, c.x, c.y);
		index++;

		while (true) {
			if (c.x <= 0 && c.y <= 0) {
				break;
			}

			if (c.x > 11 || c.y > 10) {
				break;
			}

			POINT point = findWay(p, c, value);
			if (point.x <= 0 && point.y <= 0) {
				if (!bComeBack) {
					p = c;
					bComeBack = true;
					value = -1;
					setcolor(13);
					circle(graphMatrix[p.x][p.y].x, graphMatrix[p.x][p.y].y, 10);
					setcolor(5);
					circle(graphMatrix[c.x][c.y].x, graphMatrix[c.x][c.y].y, 10);
				}

				point = findWay(p, c, value);
			}

			if (!(c.x == point.x && c.y == point.y)) {
				p = c;
				c = point;
				setcolor(13);
				circle(graphMatrix[p.x][p.y].x, graphMatrix[p.x][p.y].y, 10);
				setcolor(5);
				circle(graphMatrix[c.x][c.y].x, graphMatrix[c.x][c.y].y, 10);
				matrix[c.x][c.y] -= 1;
			}

			//歩きの向きを判定する
			char direction = currentDirection(p.x, p.y, c.x, c.y);
			//printf("%c", (c.x + c.y) % 2 != 0 && !(c.x == p.x && c.y == p.y) ? direction : ' ');

			if ((c.x + c.y) % 2 != 0) {
				if (*(output + index - 1) == direction) {
					*(output + index) = direction;
				}
				else {
					index--;
					*(output + index) = direction;
				}
				index++;
			}

			printfResulf(output, index);

			Sleep(100);
		}

		printf("%s", output);

		deleteMatrix();
		free(output);
		//showMatrix();

		getch();
	} while (true);

	closegraph();

	return 0;
}
