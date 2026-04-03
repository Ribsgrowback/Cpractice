//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
실습 시험: Section A - 연결 리스트 문제
목적: 문제 1의 required function 구현 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>   // printf, scanf 사용
#include <stdlib.h>  // malloc, free 사용

//////////////////////////////////////////////////////////////////////////////////

// 연결 리스트의 각 노드를 나타내는 구조체
typedef struct _listnode{
	int item;                // 노드가 저장하는 정수 값
	struct _listnode *next;  // 다음 노드를 가리키는 포인터
} ListNode;			// ListNode 구조체 정의는 변경하면 안 됨

// 연결 리스트 전체를 관리하는 구조체
typedef struct _linkedlist{
	int size;        // 현재 리스트에 들어 있는 노드 개수
	ListNode *head;  // 첫 번째 노드를 가리키는 포인터
} LinkedList;			// LinkedList 구조체 정의는 변경하면 안 됨


///////////////////////// function prototypes ////////////////////////////////////

// 이 함수 원형은 변경하면 안 됨
int insertSortedLL(LinkedList *ll, int item);

// 아래 함수들은 이미 제공된 보조 함수들
void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;  // 실제로 사용할 연결 리스트 변수
	int c, i, j;    // c: 메뉴 선택, i: 입력값, j: 삽입 결과 인덱스
	c = 1;          // while 루프를 시작하기 위해 1로 초기화

	// 연결 리스트를 빈 상태로 초기화
	ll.head = NULL;
	ll.size = 0;

	// 사용자 메뉴 출력
	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	// 사용자가 0을 입력할 때까지 반복
	while (c != 0)
	{
		// 메뉴 선택 입력 안내
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		// 메뉴 번호에 따라 분기
		switch (c)
		{
		case 1:
			// 새 정수를 입력받음
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);

			// 정렬 상태를 유지하면서 삽입하고, 삽입 인덱스를 j에 저장
			j = insertSortedLL(&ll, i);

			// 삽입 후 현재 리스트 상태 출력
			printf("The resulting linked list is: ");
			printList(&ll);
			break;

		case 2:
			// 마지막으로 입력한 값 i가 어느 인덱스에 들어갔는지 출력
			// 중복이라 삽입 실패한 경우 j는 -1일 수 있음
			printf("The value %d was added at index %d\n", i, j);
			break;

		case 3:
			// 현재 정렬 리스트를 출력
			printf("The resulting sorted linked list is: ");
			printList(&ll);

			// 문제 템플릿상 출력 후 전체 노드를 해제
			removeAllItems(&ll);
			break;

		case 0:
			// 종료 전 메모리 해제
			removeAllItems(&ll);
			break;

		default:
			// 정의되지 않은 메뉴 번호 처리
			printf("Choice unknown;\n");
			break;
		}
	}

	// 프로그램 종료
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	// 해야 할 일:
	// 1. ll이 NULL인지 확인
	// 2. 리스트를 앞에서부터 순회
	// 3. 같은 값이 있으면 중복이므로 -1 반환
	// 4. 현재 값이 item보다 처음 커지는 위치를 삽입 인덱스로 결정
	// 5. 끝까지 가면 맨 뒤에 삽입
	// 6. insertNode()로 삽입하고 인덱스를 반환

	//연결 리스트 자체가 없으면 작업 불가 (basecase 처리하기)
	if (ll == NULL)
		return -1;

	// 삽입될 위치를 저장할 인덱스
	int index = 0;

	// 현재 노드를 가리키며 순회할 포인터 (current)
	ListNode *cur = ll->head;

	// 리스트 끝까지 차례대로 확인
	while (cur != NULL){
		// 같은 값이 이미 존재하면 중복 허용 안 하므로 실패
		if (cur->item == item)
			return -1;

		// 현재 값이 새 값보다 크면,
		// 그 자리가 새 값이 들어갈 첫 위치이므로 반복 종료
		else if (cur->item > item)
			break;

		// 아직 삽입 위치가 아니면 다음 노드로 이동
		cur = cur->next;

		// 한 칸 이동했으므로 인덱스도 1 증가
		index++;
	}

	// 계산한 index 위치에 item 삽입
	// insertNode()는 성공 시 0, 실패 시 -1을 반환하므로
	// 여기서는 성공하면 index를 반환하고 실패하면 -1을 반환
	if (insertNode(ll, index, item) == 0)
		return index;

	return -1;
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;  // 순회용 포인터

	// 잘못된 포인터가 들어오면 그냥 종료
	if (ll == NULL)
		return;

	// 첫 노드부터 출력 시작
	cur = ll->head;

	// 빈 리스트면 Empty 출력
	if (cur == NULL)
		printf("Empty");

	// 끝까지 순회하며 각 item 출력
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}

	// 줄바꿈
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	// 현재 노드를 가리키는 포인터
	ListNode *cur = ll->head;

	// 다음 노드를 잠시 저장할 포인터
	ListNode *tmp;

	// 모든 노드를 순서대로 free
	while (cur != NULL){
		tmp = cur->next;  // 다음 노드 주소 저장
		free(cur);        // 현재 노드 해제
		cur = tmp;        // 다음 노드로 이동
	}

	// 모두 삭제되었으므로 빈 리스트 상태로 복구
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;  // 찾는 동안 이동할 포인터

	// 잘못된 리스트이거나 index 범위가 틀리면 NULL 반환
	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	// head부터 탐색 시작
	temp = ll->head;

	// 빈 리스트이거나 index가 음수면 실패
	if (temp == NULL || index < 0)
		return NULL;

	// index번째 노드까지 한 칸씩 이동
	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	// 찾은 노드 주소 반환
	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;  // pre: 삽입 위치 이전 노드, cur: 현재 노드

	// 잘못된 리스트이거나 잘못된 인덱스면 실패
	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// 빈 리스트에 삽입하거나 맨 앞에 삽입하는 경우
	// head가 바뀌므로 별도 처리 필요
	if (ll->head == NULL || index == 0){
		cur = ll->head;                     // 기존 첫 노드 저장
		ll->head = malloc(sizeof(ListNode)); // 새 head 노드 생성
		ll->head->item = value;             // 값 저장
		ll->head->next = cur;               // 기존 리스트 앞에 연결
		ll->size++;                         // 크기 증가
		return 0;
	}

	// 삽입 위치 바로 이전 노드를 찾음
	// 예: index가 3이면 index-1인 2번째 노드를 찾음
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;                    // 원래 index 위치 노드 저장
		pre->next = malloc(sizeof(ListNode)); // 새 노드 생성
		pre->next->item = value;            // 새 값 저장
		pre->next->next = cur;              // 새 노드를 중간에 끼워 넣음
		ll->size++;                         // 크기 증가
		return 0;
	}

	// 이전 노드를 못 찾았으면 실패
	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;  // pre: 삭제 전 노드, cur: 삭제할 노드

	// 삭제 가능한 최대 인덱스는 size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// 첫 번째 노드를 삭제하는 경우
	// head 포인터 자체를 바꿔야 함
	if (index == 0){
		cur = ll->head->next; // 두 번째 노드를 임시 저장
		free(ll->head);       // 기존 첫 노드 삭제
		ll->head = cur;       // head를 다음 노드로 변경
		ll->size--;           // 크기 감소

		return 0;
	}

	// 삭제할 노드의 이전 노드를 찾음
	if ((pre = findNode(ll, index - 1)) != NULL){

		// 이전 노드 다음이 없으면 삭제 불가
		if (pre->next == NULL)
			return -1;

		cur = pre->next;      // 실제 삭제할 노드
		pre->next = cur->next; // 삭제 노드를 건너뛰도록 연결
		free(cur);            // 노드 메모리 해제
		ll->size--;           // 크기 감소
		return 0;
	}

	// 이전 노드를 못 찾았으면 실패
	return -1;
}
