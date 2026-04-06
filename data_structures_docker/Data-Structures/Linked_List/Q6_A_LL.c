//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
실습 시험: Section A - 연결 리스트 문제
목적: 문제 6에서 요구하는 함수를 구현하기 */

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
int moveMaxToFront(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i, j;
	c = 1;

	LinkedList ll;
	// 연결 리스트를 빈 리스트로 초기화
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move the largest stored value to the front of the list:\n");
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
			j=insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveMaxToFront(&(ll.head));  // 이 함수를 직접 구현해야 함
			printf("The resulting linked list after moving largest stored value to the front of the list is: ");
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

////////////////////////////////////////////////////////////////////////

int moveMaxToFront(ListNode **ptrHead)

{
    // 리스트가 비어있거나 노드가 1개면 이동 불필요
    if (*ptrHead == NULL || (*ptrHead)->next == NULL)
        return -1;

    // temp: 리스트를 순회할 포인터
    ListNode *temp = *ptrHead;
    // max: 현재까지 발견한 최댓값 노드 (초기값: 헤드)
    ListNode *max = *ptrHead; 
    // front: max 바로 앞 노드 (max를 끊어내려면 앞 노드가 필요)
    ListNode *front = NULL;

    // 끝까지 순회하며 최댓값 노드와 그 앞 노드를 추적
    while (temp->next != NULL){
        // 다음 노드가 현재 max보다 크면 갱신
        if (temp->next->item > max->item){
            front = temp;       // temp가 새 max의 바로 앞 노드
            max = temp->next;   // temp->next가 새 최댓값 노드
        }
        temp = temp->next;
    }

    // front가 NULL이면 max가 이미 헤드 → 이동 불필요
    if (front == NULL) return 0;

    // max를 리스트 중간에서 끊어냄
    front->next = max->next; 
    // max의 next를 현재 헤드로 연결 (max가 맨 앞을 가리키게)
    max->next = *ptrHead; //  
    // 헤드를 max로 교체
    *ptrHead = max; 

    return 0;

}

//////////////////////////////////////////////////////////////////////////////////

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

ListNode * findNode(LinkedList *ll, int index){

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
