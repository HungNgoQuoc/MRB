/*
 ============================================================================
 Name        : RecursiveCalculation.c
 Author      : NGO QUOC HUNG
 Version     : 1.0.0
 Copyright   : Copyright
 Description : Recursive Calculation
 SHA256:nThbg6kXUpJWGl7E1IGOCspRomTxdCARLviKw6E5SY8
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ツールのタイトル
#define TITLE "再帰的計算ツール\n"
// 区切り線(マイナス記号を 40 個繋げた文字列)
#define SEPARATOR "----------------------------------------\n"
// 計算に用いる数値の数
#define DATA_CNT 5
// 計算に用いる数値の最大桁数
#define DATA_MAX_LENGTH 12

#define RECURSIVE_NOTIFICATION1 "%dつ目の数値を入力してください。\n"
#define RECURSIVE_NOTIFICATION2 "1 : 総和\n2 : 総乗\n"
#define RECURSIVE_NOTIFICATION3 "処理番号を入力してください。\n"
#define RECURSIVE_NOTIFICATION4 "入力した 5 つの数値の%sは %d です。\n"
#define RECURSIVE_NOTIFICATION5 "もう一度計算しますか?(y/n)\n"

#define RECURSIVE_NOTIFICATION6 "総和"
#define RECURSIVE_NOTIFICATION7 "総乗"

#define ERROR_NOTIFICATION2 "不正な入力です。\n"
#define STOP_NOTIFICATION "終了します。\n"

// 計算に用いる 5 つの数値と処理番号を保持
typedef struct {
	char value[DATA_CNT][DATA_MAX_LENGTH];
	char number[DATA_MAX_LENGTH];
} VALUE_LIST;

// 入力情報を取得
int getData(VALUE_LIST*);
// 入力値の数字チェック
bool isNumber(const char*);
// プロセス実行
bool execProcess(const VALUE_LIST*);
// 再帰的計算 総和
int recursiveA(const char[][DATA_MAX_LENGTH], int cnt);
// 再帰的計算 総乗
int recursiveB(const char[][DATA_MAX_LENGTH], int cnt);

/*
 * 入力情報取得関数
 */
int getData(VALUE_LIST *lstData) {
	printf(TITLE);
	printf(SEPARATOR);
	fflush(stdout);

	int iIndex = 0;

	do {
		char *sData = (char*) calloc(DATA_MAX_LENGTH, sizeof(char));

		printf(RECURSIVE_NOTIFICATION1, iIndex + 1);
		fflush(stdout);
		scanf("%12s", sData);

		if (!isNumber(sData)) {
			printf(ERROR_NOTIFICATION2);
			fflush(stdout);

			continue;
		}

		strcpy(lstData->value[iIndex], sData);

		iIndex++;
		free(sData);
	} while (iIndex < DATA_CNT);

	printf(SEPARATOR);
	printf(RECURSIVE_NOTIFICATION2);
	printf(SEPARATOR);
	printf(RECURSIVE_NOTIFICATION3);
	fflush(stdout);

	int iData;
	do {
		char *sData = (char*) calloc(1, sizeof(char));

		scanf("%1s", sData);

		iData = (int) strtol(sData, (char**) NULL, 10);

		if (!isNumber(sData) || (iData != 1 && iData != 2)) {
			printf(SEPARATOR);
			printf(RECURSIVE_NOTIFICATION2);
			printf(SEPARATOR);
			printf(RECURSIVE_NOTIFICATION3);
			fflush(stdout);

			continue;
		}

		strcpy(lstData->number, sData);

		free(sData);
	} while (iData != 1 && iData != 2);

	return 0;
}

/*
 * 入力値の数字チェック関数
 * "-1": true
 * " -1": true
 * "+1": true
 * " +1": true
 * "-1-": false
 * "+1+": false
 * " -1-": false
 * " +1+": false
 * "--1": false
 * "++1": false
 * " --1": false
 * " ++1": false
 */
//bool isNumber(const char *input) {
//	int iData = (int) strtol(input, (char**) NULL, 10);
//printf("121 - iData: %d\n", iData);
//	if (iData == 0) {
//		for (int i = 0; input[i] != '\0'; i++) {
//			if (!('0' <= input[i] && input[i] <= '9')) {
//				return false;
//			}
//		}
//	}
//
//	return true;
//}
bool isNumber(const char *input) {
	int i = 0;

	for (i = 0; input[i] != '\0'; i++) {
		if (input[i] == '-' || input[i] == '+') {
			break;
		}
	}

	for (i++; input[i] != '\0'; i++) {
		if (!('0' <= input[i] && input[i] <= '9')) {
			return false;
		}
	}

	return true;
}

/*
 * プロセス実行関数
 */
bool execProcess(const VALUE_LIST *lstData) {
	int (*func[])(const char sData[][DATA_MAX_LENGTH],
			int cnt) = {recursiveA , recursiveB };

	int iChoose = (int) strtol(lstData->number, (char**) NULL, 10);

	int result = (*func[iChoose - 1])(lstData->value, 0);

	printf(RECURSIVE_NOTIFICATION4,
			iChoose == 1 ? RECURSIVE_NOTIFICATION6 : RECURSIVE_NOTIFICATION7,
			result);
	printf(RECURSIVE_NOTIFICATION5);
	fflush(stdout);

	char *sData;

	do {
		sData = (char*) calloc(1, sizeof(char));

		scanf("%1s", sData);

		if (sData[0] != 'y' && sData[0] != 'n') {
			printf(RECURSIVE_NOTIFICATION5);
			fflush(stdout);

			continue;
		}

		printf(SEPARATOR);
	} while (sData[0] != 'y' && sData[0] != 'n');

	return sData[0] == 'y' ? true : false;
}

/*
 * 再帰的計算 総和関数
 */
//int recursiveA(const char sData[][DATA_MAX_LENGTH], int cnt) {
//	int sum = 0;
//
//	for (int i = 0; i < DATA_CNT; ++i) {
//		int iData = (int) strtol(sData[i], (char**) NULL, 10);
//
//		sum += iData;
//	}
//
//	return sum;
//}
int recursiveA(const char sData[][DATA_MAX_LENGTH], int cnt) {
	int iData = (int) strtol(sData[cnt], (char**) NULL, 10);

	if (cnt >= DATA_CNT - 1) {
		return iData;
	}

	return iData + recursiveA(sData, cnt + 1);
}

/*
 * 再帰的計算 総乗関数
 */
//int recursiveB(const char sData[][DATA_MAX_LENGTH], int cnt) {
//	int power = 1;
//
//	for (int i = 0; i < DATA_CNT; ++i) {
//		int iData = (int) strtol(sData[i], (char**) NULL, 10);
//
//		power *= iData;
//	}
//
//	return power;
//}
int recursiveB(const char sData[][DATA_MAX_LENGTH], int cnt) {
	int iData = (int) strtol(sData[cnt], (char**) NULL, 10);

	if (cnt >= DATA_CNT - 1) {
		return iData;
	}

	return iData * recursiveB(sData, cnt + 1);
}

int main(void) {
	VALUE_LIST *lstData = (VALUE_LIST*) calloc(1, sizeof(VALUE_LIST));

	while (true) {
		if (getData(lstData) != 0) {
			printf(STOP_NOTIFICATION);
			fflush(stdout);

			break;
		}

		if (!execProcess(lstData)) {
			printf(STOP_NOTIFICATION);
			fflush(stdout);

			break;
		}
	}

	getchar();
	return EXIT_SUCCESS;
}
