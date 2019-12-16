#include <stdio.h>
#include <stdlib.h>


typedef enum { false, true } bool;
#define TITLE "再帰的計算ツール (双方リスト版)"
#define SEPARATOR "---------------------------------------"
#define DATA_CNT 5
#define DATA_MAX_LENGTH 12
#define PRINT_COUNT(cnt) printf("%d つ目の数値を入力してください。\n", cnt)
#define PRINT_NEW_ELEMENT(index, value) printf("リストに要素%dのメモリ領域を確保値：　%s\n", index, value)
#define PRINT_FREE_ELEMENT(index, value) printf("リストから要素%dのメモリ領域を解放値：　%s\n", index, value)
#define PRINT_CALC_RESULT(cnt, type, result) printf("入力した%dつの数値の%sは　%d　です。\n", cnt, type, result)
#define EXISTS_ELEMENT(elem) (elem != NULL ? true: false)
#define FREE(p) {free(p); p = NULL;}


//双方向リスト
typedef struct LIST {
	int index;
	char value[DATA_MAX_LENGTH];
	struct LIST* prev;
	struct LIST* next;
}LINKED_LIST;

//計算に用いる5つの数値と処理番号を保持
typedef struct {
	LINKED_LIST* elem;
	char number[DATA_MAX_LENGTH];
}VALUE_LIST;

//selectElement 関数で使用
typedef enum {
	ENUM_HEAD_POS,
	ENUM_TAIL_POS
}POS;


//入力情報を取得
int getData(VALUE_LIST* );

//入力値の数チェック
bool isNumber(const char* );

//プロセス実行
bool execProcess(VALUE_LIST* );

//再帰的計算総和
int recursiveA(LINKED_LIST* );

//再帰的計算総乗
int recursiveB(LINKED_LIST* );

//リストにデータを追加
LINKED_LIST* addElement(LINKED_LIST*, const char*);

//リストの先頭要素または末尾を選択
LINKED_LIST* selectElement(LINKED_LIST*, int);

//リストの解放
void freeElement(VALUE_LIST*);

int(*func[])(LINKED_LIST*) = { recursiveA, recursiveB };

//void PrintList(LINKED_LIST *);


int getData(VALUE_LIST* value_list) {
	int i;
	char value[DATA_MAX_LENGTH];
	LINKED_LIST *pTail = NULL;
	char choice[DATA_MAX_LENGTH];
	printf("%s\n", TITLE);
	printf("%s\n", SEPARATOR);

	for (i = 0; i < DATA_CNT; i++) {
		PRINT_COUNT(i + 1);
		scanf("%s", value);
		if (true != isNumber(value)) {
			return -1;
		}
		//リストにデータを追加
		value_list->elem = addElement(value_list->elem, value);
		
		//末尾要素を探してインデクス値を設定
		//pTail = selectElement(value_list->elem, ENUM_TAIL_POS);
		//pTail->index = i + 1;
		PRINT_NEW_ELEMENT(i + 1, value);
	}

	do {
		printf("%s\n", SEPARATOR);
		printf("1 : 総和\n");
		printf("2 : 総乗\n");
		printf("%s\n", SEPARATOR);
		printf("処理番号を入力してください:");
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
	if (value[0] == '-')
	{
		if (1 == strlen(value))
			return false;
		i++;
	}
	for (i; value[i] != '\0'; i++) {
		if (value[i] < '0' || value[i] > '9') {
			return false;
		}
	}
	return true;
}


bool execProcess(VALUE_LIST* value_list) {
	char choice[DATA_MAX_LENGTH];
	char choiceName[7];
	int result = (*func[atoi(value_list->number) - 1])(value_list->elem);

	//結果を出力する
	if (0 == strncmp(value_list->number, "1", 1)) {
		strcpy(choiceName, "総和");
	}else {
		strcpy(choiceName, "総乗");
	}
	PRINT_CALC_RESULT(DATA_CNT, choiceName, result);

	do {
		printf("もうー度計算を実行しますか？(y/n)");
		scanf("%s", choice);
		if ((0 == strncmp(choice, "y", 1)) || (0 == strncmp(choice, "Y", 1)))
		{
			return true;
		}
		if ((0 == strncmp(choice, "n", 1)) || (0 == strncmp(choice, "N", 1)))
		{
			return false;
		}
	} while (1);
}
/*
void PrintList(LINKED_LIST *pHead)
{
	LINKED_LIST *pNode;
	if (pHead == NULL) 
		printf("Khong co du lieu");
	pNode = pHead;
	while (pNode != NULL)
	{
		printf("index: %d\n", pNode->index);
		printf("%s", pNode->value);
		pNode = pNode->next; //pNode tro den node tiep theo
	}
}
*/

LINKED_LIST* selectElement(LINKED_LIST* linked_list, int choice) {

	if ( ENUM_HEAD_POS == choice ) {
		while (linked_list->prev != NULL) linked_list = linked_list->prev;
	}
	else if ( ENUM_TAIL_POS == choice ) {
		while (linked_list->next != NULL) linked_list = linked_list->next;
	}
	return linked_list;
}

LINKED_LIST* addElement(LINKED_LIST * pHead, const char* value) {
	//新規要素作成
	LINKED_LIST *newNode = (LINKED_LIST*)malloc(sizeof(LINKED_LIST));
	strncpy(newNode->value, value, DATA_MAX_LENGTH);
	newNode->next = NULL;
	newNode->prev = NULL;

	//リストが空の場合、新規要素を先頭要素にする
	if (pHead == NULL) {
		pHead = newNode;
		pHead->index = 1;
	}
	else {
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
	if (pHead != NULL)
		return atoi(pHead->value) + recursiveA(pHead->next);
	else
		return 0;
}

int recursiveB(LINKED_LIST* pHead) {
	if (pHead != NULL)
		return atoi(pHead->value)*recursiveB(pHead->next);
	else
		return 1;
}

void freeElement(VALUE_LIST* value_list)
{
	LINKED_LIST *pNode;
	while (value_list->elem != NULL)
	{
		pNode = value_list->elem;
		value_list->elem = value_list->elem->next;
		PRINT_FREE_ELEMENT(pNode->index, pNode->value);
		FREE(pNode);
	}
}
int main()
{
	VALUE_LIST value_list;
	int rtn = 0;
	do {
		//初期化
		memset(&value_list, '\0', sizeof(value_list));
		
		//入力情報取得 
		rtn = getData(&value_list);
		if (-1 == rtn) {
			printf("数字と負の数以外が入力された。\n");
			break;
		}
		if (true != execProcess(&value_list))
		{
			printf("終了。\n");
			break;
		}
		//リストの解放
		freeElement(&value_list);
	} while (1);

	//リストの解放
	freeElement(&value_list);
	
	//PrintList(value_list.elem);
	system("pause");
	return rtn;
}


