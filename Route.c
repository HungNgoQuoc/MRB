/*
 ============================================================================
 Name        : Route.c
 Author      : NGO QUOC HUNG
 Version     : 1.0.0
 Copyright   : Copyright
 Description : Route
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int xX;
	int yY;
} POINT;

int input[9][6] = { { 1, 1, 1, 1 }, { 0, 0, 0, 0, 1 }, { 0, 1, 1, 0 }, { 0, 1,
		0, 1, 1 }, { 0, 0, 1, 0 }, { 0, 1, 1, 1, 1 }, { 0, 0, 1, 0 }, { 0, 1, 0,
		0, 1 }, { 0, 1, 1, 1 } };

int matrix[11][10];

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
			} else {
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

bool isNearWall(int xX, int yY) {
	if (xX - 1 >= 0) {
		if (matrix[xX - 1][yY] == 1) {
			return true;
		}
	}
	if (xX + 1 < 11) {
		if (matrix[xX + 1][yY] == 1) {
			return true;
		}
	}
	if (yY - 1 >= 0) {
		if (matrix[xX][yY - 1] == 1) {
			return true;
		}
	}
	if (yY + 1 < 10) {
		if (matrix[xX][yY + 1] == 1) {
			return true;
		}
	}
	if (xX - 1 >= 0 && yY - 1 >= 0) {
		if (matrix[xX - 1][yY - 1] == 1) {
			return true;
		}
	}
	if (xX + 1 < 11 && yY + 1 < 10) {
		if (matrix[xX + 1][yY + 1] == 1) {
			return true;
		}
	}
	if (xX - 1 >= 0 && yY + 1 < 10) {
		if (matrix[xX - 1][yY + 1] == 1) {
			return true;
		}
	}
	if (xX + 1 < 11 && yY - 1 >= 0) {
		if (matrix[xX + 1][yY - 1] == 1) {
			return true;
		}
	}
	return false;
}

POINT findWay(POINT p, POINT c, int value) {
	POINT point;
	point.xX = 0;
	point.yY = 0;
//	printf("65前点: (%3d,%3d)\n", p.xX, p.yY);
//	printf("66カレント点: (%3d,%3d)\n", c.xX, c.yY);
	if (c.xX - 1 >= 0) {
		if (!(c.xX - 1 == p.xX && c.yY == p.yY)) {
//			printf("1 - matrix[%d][%d]: (%3d) %d\n", c.xX - 1, c.yY,
//					matrix[c.xX - 1][c.yY], isNearWall(c.xX - 1, c.yY));
			if (matrix[c.xX - 1][c.yY] == value && isNearWall(c.xX - 1, c.yY)) {
				point.xX = c.xX - 1;
				point.yY = c.yY;
//				printf("70 - point: (%3d,%3d)\n", point.xX, point.yY);
			}
		}
	}

	if (c.xX + 1 < 11) {
		if (!(c.xX + 1 == p.xX && c.yY == p.yY)) {
//			printf("2 - matrix[%d][%d]: (%3d)\n", c.xX + 1, c.yY,
//					matrix[c.xX + 1][c.yY]);
			if (matrix[c.xX + 1][c.yY] == value && isNearWall(c.xX + 1, c.yY)) {
				point.xX = c.xX + 1;
				point.yY = c.yY;
//				printf("79 - point: (%3d,%3d)\n", point.xX, point.yY);
			}
		}
	}

	if (c.yY - 1 >= 0) {
		if (!(c.xX == p.xX && c.yY - 1 == p.yY)) {
//			printf("3 - matrix[%d][%d]: (%3d)\n", c.xX, c.yY - 1,
//					matrix[c.xX][c.yY - 1]);
			if (matrix[c.xX][c.yY - 1] == value && isNearWall(c.xX, c.yY - 1)) {
				point.xX = c.xX;
				point.yY = c.yY - 1;
//				printf("87 - point: (%3d,%3d)\n", point.xX, point.yY);
			}
		}
	}

	if (c.yY + 1 < 10) {
		if (!(c.xX == p.xX && c.yY + 1 == p.yY)) {
//			printf("4 - matrix[%d][%d]: (%3d)\n", c.xX, c.yY + 1,
//					matrix[c.xX][c.yY + 1]);
			if (matrix[c.xX][c.yY + 1] == value && isNearWall(c.xX, c.yY + 1)) {
				point.xX = c.xX;
				point.yY = c.yY + 1;
//				printf("97 - point: (%3d,%3d)\n", point.xX, point.yY);
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

int main(void) {
	bool bComeBack = false;
	int value = 0;

	// 前点
	POINT p;
	p.xX = 0;
	p.yY = 0;

	// カレント点
	POINT c;

	createMatrix();
	showMatrix();
	if (matrix[p.xX][p.yY + 1] == 1) {
		c.xX = p.xX + 1;
		c.yY = p.yY;
	}

	if (matrix[p.xX + 1][p.yY] == 1) {
		c.xX = p.xX;
		c.yY = p.yY + 1;
	}

	matrix[c.xX][c.yY] -= 1;

//	printf("前点: (%3d,%3d)\n", p.xX, p.yY);
//	printf("カレント点: (%3d,%3d)\n", c.xX, c.yY);

	printf("Dang tim duong...\n");

	while (true) {
		if (c.xX <= 0 && c.yY <= 0) {
			break;
		}

		if (c.xX > 11 || c.yY > 10) {
			break;
		}

		POINT point = findWay(p, c, value);
		if (point.xX <= 0 && point.yY <= 0) {
			if (!bComeBack) {
				p = c;
				bComeBack = true;
				value = -1;
			}

			point = findWay(p, c, value);
		}

		if (!(c.xX == point.xX && c.yY == point.yY)) {
			p = c;
			c = point;
			matrix[c.xX][c.yY] -= 1;
		}

		//歩きの向きを判定する
		char direction = currentDirection(p.xX, p.yY, c.xX, c.yY);
//		printf("%c", (c.xX + c.yY) % 2 == 0 ? direction : ' ');
		printf("%c", direction);
//		printf("188前点: (%3d,%3d)\n", p.xX, p.yY);
//		printf("189カレント点: (%3d,%3d)\n", c.xX, c.yY);
	}

	showMatrix();

	return EXIT_SUCCESS;
}
