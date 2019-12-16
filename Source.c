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

//2�_�̍��W����A�ǂ����邩�ǂ������肷��
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

//�O�_�ƃJ�����g�_�̍��W������������𔻒肷��
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

//�J�����g�_�ƕ����������獶�_�𔻒肷��
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

//�J�����g�_�ƕ�����������E�_�𔻒肷��
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
//�J�����g�_�ƕ������������_�𔻒肷��
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
//�J�����g�_�ƕ����������牺�_�𔻒肷��
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


	//�O�_
	int pX = 0;
	int pY = 0;

	//�J�����g�_
	int cX = 0;
	int cY = 0;
	
	//A�_�ƉE�_�̊Ԃ���
	if(checkWallExistPoint2Point(0, 0, 0, 1) == true) {
		//A�_�̉E�_���J�����g�_�ɐݒ肷��
		cX = 0;
		cY = 1;
	}
	//A�_�Ɖ��_�̊Ԃ���
	else if(checkWallExistPoint2Point(0, 0, 1, 0) == true) {
		//A�_�̉��_���J�����g�_�ɐݒ肷��
		cX = 1;
		cY = 0;
	}

	if ((pX == cX) && (pY == cY)) {
		printf("A�_����ǂ������B");
		system("pause");
		return 0;
	}

	do{
		//�����̌����𔻒肷��
		char direction = currentDirection(pX, pY, cX, cY);
		printf("%c", direction);

		//�O�_(1,0)����_A�ɖ߂�@->�I��
		if ((cX == 0) && (cY == 0) && (pX == 1) && (pY == 0))  {
			break;
		}
		//�O�_(0,1)����A�_�ɖ߂�ꍇ����A�_��(1,0)�_�̊Ԃ͕ǂȂ� ->�I��
		if ((cX == 0) && (cY == 0) && (pX == 0) && (pY == 1) && checkWallExistPoint2Point(0, 0, 1, 0) == false) {
			break;
		}
		//������
		int leftX = 0;
		int leftY = 0;
		int upX = 0;
		int upY = 0;
		int rightX = 0;
		int rightY = 0;
		int downX = 0;
		int downY = 0;

		//���_�̍��W��T���ĕǂ�����ꍇ�A���_�ɕ���
		if ((findLeftPoint(cX, cY, direction, &leftX, &leftY) == true) && (checkWallExistPoint2Point(cX, cY, leftX, leftY) == true)) {
			pX = cX;
			pY = cY;

			cX = leftX;
			cY = leftY;
			continue;
		} 
		//��_�̍��W��T���ĕǂ�����ꍇ�A��_�ɕ���
		else if((findUpPoint(cX, cY, direction, &upX, &upY) == true) && (checkWallExistPoint2Point(cX, cY, upX, upY) == true)) {
			pX = cX;
			pY = cY;

			cX = upX;
			cY = upY;
			continue;	
		} 
		//�E�_�̍��W��T���ĕǂ�����ꍇ�A�E�_�ɕ���
		else if ((findRightPoint(cX, cY, direction, &rightX, &rightY) == true) && (checkWallExistPoint2Point(cX, cY, rightX, rightY) == true)) {
			pX = cX;
			pY = cY;
		
			cX = rightX;
			cY = rightY;
			continue;
		}
		//���_�̍��W��T���ĕǂ�����ꍇ�A���_�ɕ���
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