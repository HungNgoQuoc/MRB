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
#define RECURSIVE_NOTIFICATION4 "入力した 5 つの数値の総和は [計算結果] です。\nもう一度計算しますか?(y/n)\n"
#define ERROR_NOTIFICATION2 "不正な入力です。\n"

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

	int iData, iIndex = 0;

	do {
		iData = -1;

		char *sData = (char *) calloc(DATA_MAX_LENGTH, sizeof(char));

		printf(RECURSIVE_NOTIFICATION1, iIndex - 1);
		fflush(stdout);
		scanf("%12s", sData);

		if (!isNumber(sData)) {
			printf(ERROR_NOTIFICATION2);
			fflush(stdout);

			continue;
		}

//		iData = (int) strtol(sData, (char**) NULL, 10);

		*(lstData + iIndex)->value = sData;

		iIndex++;
		free(sData);
	} while (iIndex < DATA_CNT);

	return 0;
}

/*
 * 入力値の数字チェック関数
 */
bool isNumber(const char *input) {
	int iData = (int) strtol(input, (char**) NULL, 10);

	if (iData == 0) {
		for (int i = 0; input[i] != '\0'; i++) {
			if (!('0' <= input[i] && input[i] <= '9')) {
				return false;
			}
		}
	}

	return true;
}

/*
 * プロセス実行関数
 */
bool execProcess(const VALUE_LIST *lstData) {
	int (*func[])(const char[][DATA_MAX_LENGTH],
			int cnt) = {recursiveA , recursiveB };

//	int iChoose = (int) strtol(sChoose, (char**) NULL, 10);
//	int iLines = (int) strtol(sLines, (char**) NULL, 10);
	int iChoose = 0, iLines = 0;
	(*func[iChoose - 1])(lstData, iLines);
}

int main(void) {
	VALUE_LIST *lstData = (VALUE_LIST *) calloc(DATA_CNT, sizeof(VALUE_LIST));
	getData(lstData);
	return EXIT_SUCCESS;
}
