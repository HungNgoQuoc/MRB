#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;

int input[9][6] ={	{1,1,1,1},
					{0,0,0,0,1},
					{0,1,1,0},
					{0,1,0,1,1},
					{0,0,1,0},
					{0,1,1,1,1},
					{0,0,1,0},
					{0,1,0,0,1},
					{0,1,1,1}	};

//2点の座標から、壁があるかどうか判定する
bool checkWallExistPoint2Point(int x1, int y1, int x2, int y2) {

	if ((x1 == x2) && (abs(y1 - y2) == 1)) {
		if (y1 < y2) {
			if (input[x1 * 2][y1] == 1) {
				return true;
			}
		}else {
			if (input[x1 * 2][y2] == 1) {
				return true;
			}
		}
	}

	if ((y1 == y2) && (abs(x1 - x2) == 1)) {
		if (input[x1 + x2][y1] == 1) {
			return true;
		}
	}
	return false;
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

//カレント点と歩き向きから左点を判定する
bool findLeftPoint(int cX, int cY, char direction, int *leftX, int *leftY) {
	if (direction == 'R') {
		*leftX = cX - 1;
		*leftY = cY;
	} else if(direction == 'L') {
		*leftX = cX + 1;
		*leftY = cY;

	} else if(direction == 'U') {
		*leftX = cX;
		*leftY = cY - 1;
	}
	else {
		*leftX = cX;
		*leftY = cY + 1;
	}

	if ((*leftX < 0) || (*leftY < 0) || (*leftX > 4) || (*leftY > 4))
			return false;
	return true;
}

//カレント点と歩き向きから右点を判定する
bool findRightPoint(int cX, int cY, char direction, int *rightX, int *rightY) {
	
	if (direction == 'R') {
		*rightX = cX + 1;
		*rightY = cY;
	}
	else if (direction == 'L') {
		*rightX = cX - 1;
		*rightY = cY;

	}
	else if (direction == 'U') {
		*rightX = cX;
		*rightY = cY + 1;
	}
	else {
		*rightX = cX;
		*rightY = cY - 1;
	}

	if ((*rightX < 0) || (*rightY < 0) || (*rightX > 4) || (*rightY > 4))
		return false;
	return true;

}
//カレント点と歩き向きから上点を判定する
bool findUpPoint(int cX, int cY, char direction, int *upX, int *upY) {
	if(direction == 'R') {
		*upX = cX;
		*upY = cY +	1;
	}else if (direction == 'L') {
		*upX = cX;
		*upY = cY - 1;
	}else if (direction == 'U') {
		*upX = cX - 1;
		*upY = cY;
	}else {
		*upX = cX + 1;
		*upY = cY;
	}

	if ((*upX < 0) || (*upY < 0) || (*upX > 4) || (*upY > 4))
		return false;
	return true;
}
//カレント点と歩き向きから下点を判定する
bool findDownPoint(int cX, int cY, char direction, int *downX, int *downY) {
	if (direction == 'R') {
		*downX = cX;
		*downY = cY - 1;
	}else if (direction == 'L') {
		*downX = cX;
		*downY = cY + 1;
	}
	else if (direction == 'U') {
		*downX = cX + 1;
		*downY = cY;
	}else {
		*downX = cX - 1;
		*downY = cY;
	}

	if ((*downX < 0) || (*downY < 0) || (*downX > 4) || (*downY > 4))
		return false;
	return true;
}


int main() 
{
	int i = 0;
	char val_array[5][5];
	
	/*for (i = 0; i < 9; i++) {
		printf("line %d:", i + 1);
		scanf("%s", &input[i]);
	}*/


	//前点
	int pX = 0;
	int pY = 0;

	//カレント点
	int cX = 0;
	int cY = 0;
	
	//A点と右点の間が壁
	if(checkWallExistPoint2Point(0, 0, 0, 1) == true) {
		//A点の右点をカレント点に設定する
		cX = 0;
		cY = 1;
	}
	//A点と下点の間が壁
	else if(checkWallExistPoint2Point(0, 0, 1, 0) == true) {
		//A点の下点をカレント点に設定する
		cX = 1;
		cY = 0;
	}

	if ((pX == cX) && (pY == cY)) {
		printf("A点から壁が無い。");
		system("pause");
		return 0;
	}

	do{
		//歩きの向きを判定する
		char direction = currentDirection(pX, pY, cX, cY);
		printf("%c", direction);

		//前点(1,0)から点Aに戻る　->終了
		if ((cX == 0) && (cY == 0) && (pX == 1) && (pY == 0))  {
			break;
		}
		//前点(0,1)からA点に戻る場合かつA点と(1,0)点の間は壁なし ->終了
		if ((cX == 0) && (cY == 0) && (pX == 0) && (pY == 1) && checkWallExistPoint2Point(0, 0, 1, 0) == false) {
			break;
		}
		//初期化
		int leftX = 0;
		int leftY = 0;
		int upX = 0;
		int upY = 0;
		int rightX = 0;
		int rightY = 0;
		int downX = 0;
		int downY = 0;

		//左点の座標を探して壁がある場合、左点に歩き
		if ((findLeftPoint(cX, cY, direction, &leftX, &leftY) == true) && (checkWallExistPoint2Point(cX, cY, leftX, leftY) == true)) {
			pX = cX;
			pY = cY;

			cX = leftX;
			cY = leftY;
			continue;
		} 
		//上点の座標を探して壁がある場合、上点に歩き
		else if((findUpPoint(cX, cY, direction, &upX, &upY) == true) && (checkWallExistPoint2Point(cX, cY, upX, upY) == true)) {
			pX = cX;
			pY = cY;

			cX = upX;
			cY = upY;
			continue;	
		} 
		//右点の座標を探して壁がある場合、右点に歩き
		else if ((findRightPoint(cX, cY, direction, &rightX, &rightY) == true) && (checkWallExistPoint2Point(cX, cY, rightX, rightY) == true)) {
			pX = cX;
			pY = cY;
		
			cX = rightX;
			cY = rightY;
			continue;
		}
		//下点の座標を探して壁がある場合、下点に歩き
		else if ((findDownPoint(cX, cY, direction, &downX, &downY) == true) && (checkWallExistPoint2Point(cX, cY, downX, downY) == true)) {
			pX = cX;
			pY = cY;

			cX = downX;
			cY = downY;
			continue;
		}

	} while (1);

	system("pause");
	return 0;
	
}