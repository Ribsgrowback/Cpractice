//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
실습 시험: Section A - 연결 리스트 문제
목적: 문제 3에서 요구하는 함수를 구현하기 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// ListNode 구조체 정의는 변경하면 안 됨

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// LinkedList 구조체 정의는 변경하면 안 됨


//////////////////////// function prototypes /////////////////////////////////////

// 이 함수의 원형(prototype)은 변경하면 안 됨
void moveOddItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	// 연결 리스트를 빈 리스트로 초기화
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveOddItemsToBack(&ll); // 이 함수를 직접 구현해야 함
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void moveOddItemsToBack(LinkedList *ll)
{
	/* 여기에 코드를 작성 */

	int originalSize, i, index, value;
	ListNode *cur;

	// TODO 1. 예외 상황 확인
	// 리스트가 없거나 노드가 0개 또는 1개면 그대로 종료
	if (ll == NULL || ll->size <= 1)
		return;

	// TODO 2. "원래 리스트 길이"를 먼저 저장
	// remove + insert를 하면 size가 다시 같아지므로,
	// 처음 길이만큼만 검사해야 뒤에 붙인 홀수를 다시 보지 않음
	originalSize = ll->size;
	index = 0;

	// TODO 3. 앞에서부터 원래 길이만큼 순회
	for (i = 0; i < originalSize; i++)
	{
		cur = findNode(ll, index);
		value = cur->item;

		// TODO 4. 현재 값이 홀수면
		// 현재 위치 노드를 제거하고 같은 값을 맨 뒤에 다시 삽입
		// index는 증가시키지 않음
		// 이유: 다음 원소가 현재 index 자리로 당겨지기 때문
		if (value % 2 != 0)
		{
			removeNode(ll, index);
			insertNode(ll, ll->size, value);
		}
		// TODO 5. 현재 값이 짝수면
		// 앞쪽에 그대로 두고 다음 위치로 넘어감
		else
		{
			index++;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// 빈 리스트에 삽입하거나 첫 번째 위치에 삽입하면 head 포인터를 갱신해야 함
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// 삽입 위치의 이전 노드를 찾음
	// 새 노드를 만든 뒤 링크를 다시 연결
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// 삭제 가능한 가장 큰 인덱스는 size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// 첫 번째 노드를 삭제하면 head 포인터를 갱신해야 함
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// 삭제할 위치의 이전 노드를 찾음
	// 대상 노드를 해제한 뒤 링크를 다시 연결
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
