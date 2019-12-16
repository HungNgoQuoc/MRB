/*
 ============================================================================
 Name        : RecursiveCalculation2.c
 Author      : NGO QUOC HUNG
 Version     : 1.0.0
 Copyright   : Copyright
 Description : Recursive Calculation 2
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TITLE "再帰的計算ツール (双方リスト版)\n"
#define SEPARATOR "---------------------------------------\n"
#define DATA_CNT 5
#define DATA_MAX_LENGTH 12
#define PRINT_COUNT(cnt) printf("%d つ目の数値を入力してください。\n", cnt)
#define PRINT_NEW_ELEMENT(index, value) printf("リストに要素%dのメモリ領域を確保値：　%s\n", index, value)
#define PRINT_FREE_ELEMENT(index, value) printf("リストから要素%dのメモリ領域を解放値：　%s\n", index, value)
#define PRINT_CALC_RESULT(cnt, type, result) printf("入力した%dつの数値の%sは　%d　です。\n", cnt, type, result)
#define EXISTS_ELEMENT(elem) (elem != NULL ? true: false)
#define FREE(p) {free(p); p = NULL;}

#define RECURSIVE_NOTIFICATION0 "1 : %s\n2 : %s\n"
#define RECURSIVE_NOTIFICATION1 "総和"
#define RECURSIVE_NOTIFICATION2 "総乗"
#define RECURSIVE_NOTIFICATION3 "処理番号を入力してください。\n"
#define RECURSIVE_NOTIFICATION4 "もう一度計算しますか?(y/n)\n"

#define ERROR_NOTIFICATION "数字と負の数以外が入力された。\n"
#define STOP_NOTIFICATION "終了します。\n\n"

//双方向リスト
typedef struct LIST {
	int index;
	char value[DATA_MAX_LENGTH];
	struct LIST* prev;
	struct LIST* next;
} LINKED_LIST;

//計算に用いる5つの数値と処理番号を保持
typedef struct {
	LINKED_LIST* elem;
	char number[DATA_MAX_LENGTH];
} VALUE_LIST;

//selectElement 関数で使用
typedef enum {
	ENUM_HEAD_POS, ENUM_TAIL_POS
};

//入力情報を取得
int getData(VALUE_LIST*);

//入力値の数チェック
bool isNumber(const char*);

//プロセス実行
bool execProcess(VALUE_LIST*);

//再帰的計算総和
int recursiveA(LINKED_LIST*);

//再帰的計算総乗
int recursiveB(LINKED_LIST*);

//リストにデータを追加
LINKED_LIST* addElement(LINKED_LIST*, const char*);

//リストの先頭要素または末尾を選択
LINKED_LIST* selectElement(LINKED_LIST*, int);

//リストの解放
void freeElement(VALUE_LIST*);

int (*func[])(LINKED_LIST*) = {recursiveA, recursiveB };

int getData(VALUE_LIST* value_list) {
	int i;
	char value[DATA_MAX_LENGTH];
	char choice[DATA_MAX_LENGTH];

	printf(TITLE);
	printf(SEPARATOR);
	fflush(stdout);

	for (i = 0; i < DATA_CNT; i++) {
		PRINT_COUNT(i + 1);
		fflush(stdout);
		scanf("%s", value);

		if (true != isNumber(value)) {
			return -1;
		}

		//リストにデータを追加
		value_list->elem = addElement(value_list->elem, value);

		PRINT_NEW_ELEMENT(i + 1, value);
		fflush(stdout);
	}

	do {
		printf(SEPARATOR);
		printf(RECURSIVE_NOTIFICATION0, RECURSIVE_NOTIFICATION1,
		RECURSIVE_NOTIFICATION2);
		printf(SEPARATOR);
		printf(RECURSIVE_NOTIFICATION3);
		fflush(stdout);
		scanf("%s", choice);

		if (true != isNumber(choice)) {
			return -1;
		}

		if ((0 != strncmp(choice, "1", 1)) && (0 != strncmp(choice, "2", 1))) {
			continue;
		}

		strncpy(value_list->number, choice, DATA_MAX_LENGTH);
		break;
	} while (1);

	return 0;
}

bool isNumber(const char* value) {
	int i = 0;

	//負の数字の場合
	if (value[0] == '-') {
		if (1 == strlen(value))
			return false;
		i++;
	}

	for (; value[i] != '\0'; i++) {
		if (value[i] < '0' || value[i] > '9') {
			return false;
		}
	}

	return true;
}

bool execProcess(VALUE_LIST* value_list) {
	char choice[DATA_MAX_LENGTH];
	int result = (*func[atoi(value_list->number) - 1])(value_list->elem);

	//結果を出力する
	int iChoose = (int) strtol(value_list->number, (char**) NULL, 10);

	PRINT_CALC_RESULT(DATA_CNT,
			iChoose == 1 ? RECURSIVE_NOTIFICATION1 : RECURSIVE_NOTIFICATION2,
			result);

	do {
		printf(RECURSIVE_NOTIFICATION4);
		fflush(stdout);
		scanf("%s", choice);

		if ((0 == strncmp(choice, "y", 1)) || (0 == strncmp(choice, "Y", 1))) {
			return true;
		}

		if ((0 == strncmp(choice, "n", 1)) || (0 == strncmp(choice, "N", 1))) {
			return false;
		}
	} while (1);
}

LINKED_LIST* selectElement(LINKED_LIST* linked_list, int choice) {
	if (ENUM_HEAD_POS == choice) {
		while (linked_list->prev != NULL)
			linked_list = linked_list->prev;
	} else if (ENUM_TAIL_POS == choice) {
		while (linked_list->next != NULL)
			linked_list = linked_list->next;
	}
	return linked_list;
}

LINKED_LIST* addElement(LINKED_LIST * pHead, const char* value) {
	//新規要素作成
	LINKED_LIST *newNode = (LINKED_LIST*) malloc(sizeof(LINKED_LIST));
	strncpy(newNode->value, value, DATA_MAX_LENGTH);
	newNode->next = NULL;
	newNode->prev = NULL;

	//リストが空の場合、新規要素を先頭要素にする
	if (pHead == NULL) {
		pHead = newNode;
		pHead->index = 1;
	} else {
		//末尾要素を探して末尾に追加する
		LINKED_LIST *pTail = NULL;
		pTail = selectElement(pHead, ENUM_TAIL_POS);
		pTail->next = newNode;
		newNode->prev = pTail;
		newNode->index = newNode->prev->index + 1;
	}

	return pHead;
}

int recursiveA(LINKED_LIST* pHead) {
	return pHead != NULL ? atoi(pHead->value) + recursiveA(pHead->next) : 0;
}

int recursiveB(LINKED_LIST* pHead) {
	return pHead != NULL ? atoi(pHead->value) * recursiveB(pHead->next) : 1;
}

void freeElement(VALUE_LIST* value_list) {
	LINKED_LIST *pNode;

	while (value_list->elem != NULL) {
		pNode = value_list->elem;
		value_list->elem = value_list->elem->next;
		PRINT_FREE_ELEMENT(pNode->index, pNode->value);
		fflush(stdout);
		FREE(pNode);
	}
}
int main() {
	VALUE_LIST value_list;

	do {
		//初期化
		memset(&value_list, '\0', sizeof(value_list));

		//入力情報取得
		if (-1 == getData(&value_list)) {
			printf(ERROR_NOTIFICATION);
			fflush(stdout);
			break;
		}

		if (true != execProcess(&value_list)) {
			printf(STOP_NOTIFICATION);
			fflush(stdout);
			break;
		}
		//リストの解放
		freeElement(&value_list);
	} while (1);

	//リストの解放
	freeElement(&value_list);

	return 0;
}
