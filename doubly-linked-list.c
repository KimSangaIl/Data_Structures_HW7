/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	printf("[----- [Kim Sangil] [2019038041] -----]\n");

	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	if (*h != NULL) freeList(*h);	//리스트가 공백이 아니라면 메모리를 해제하여 공백으로 만든다

	*h = (headNode*)malloc(sizeof(headNode));	//헤드 노드에 메모리를 할당
	(*h)->first = NULL;							//헤드 노드가 처음이자 마지막 노드이므로 링크를 NULL로 초기화

	return 1;
}

int freeList(headNode* h){

	listNode* temp = h->first;	//temp라는 노드를 선언하고 헤드 노드로 초기화
	listNode* pre = NULL;		//pre라는 노드를 선언하고 NULL로 초기화

	while (temp != NULL) {	//temp노드가 NULL이 될때 까지 반복
		pre = temp;			//pre노드를 temp노드로 초기화
		temp = temp->rlink;	//temp노드를 오른쪽(다음) 노드로 이동
		free(pre);			//pre노드의 메모리를 해제
	}	//temp노드는 오른쪽(다음)으로 한칸씩 이동하고 pre노드는 temp노드를 따라 이동하면서 리스트의 모든 메모리를 해제
	free(h);				//헤드 노드의 메모리를 해제

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* new = (listNode*)malloc(sizeof(listNode));	//new라는 노드를 선언하고 메모리를 할당
	new->key = key;		//new노드의 키 값을 입력 받은 키 값으로 초기화
	new->rlink = NULL;
	new->llink = NULL;	//new노드의 좌우 링크를 NULL로 초기화

	if (h->first == NULL) {
		h->first = new;	//공백 리스트라면 헤드 노드를 new노드로 초기화
	}

	else {
		listNode* temp = h->first;		//리스트의 마지막을 찾을 임시 노드를 선언 및 헤드 노드로 초기화
		while (temp->rlink != NULL) {	//temp노드의 오른쪽(다음) 링크가 NULL이 될때까지 반복
			temp = temp->rlink;			//temp노드를 오른쪽(다음) 노드로 이동
		}
		temp->rlink = new;	//new 노드의 주소를 temp노드의 오른쪽 링크에 저장
		new->llink = temp;	//temp 노드의 주소를 new노드의 왼쪽 링크에 저장
	}

	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) printf("Nothing to delete!\n");	//리스트가 공백이라면 경고 메시지 출력

	else {
		listNode* temp = h->first;	//리스트의 마지막을 찾을 임시 노드를 선언 및 헤드 노드로 초기화
		listNode* pre = NULL;		//pre라는 노드를 선언하고 NULL로 초기화

		if (temp->rlink == NULL) {	//리스트에 노드가 하나만 있는 경우
			h->first = NULL;		//헤드 노드 링크를 NULL로 초기화
			free(temp);				//temp노드의 메모리를 해제
		}

		else {
			while (temp->rlink != NULL) {	//temp노드의 오른쪽(다음) 링크가 NULL이 될때까지 반복
				pre = temp;					//pre노드를 temp노드로 초기화
				temp = temp->rlink;			//temp노드를 오른쪽(다음) 노드로 이동
			}

			pre->rlink = NULL;	//pre노드의 오른쪽(다음) 링크를 NULL로 초기화
			free(temp);			//temp노드의 메모리를 해제
		}
	}

	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* new = (listNode*)malloc(sizeof(listNode));	//new라는 노드를 선언하고 메모리를 할당
	new->key = key;		//new노드의 키 값을 입력 받은 키 값으로 초기화
	new->rlink = NULL;
	new->llink = NULL;	//new노드의 좌우 링크를 NULL로 초기화

	if (h->first == NULL) h->first = new;	//리스트가 공백이라면 헤드 노드를 new노드로 초기화
	else {
		new->rlink = h->first;		//new노드의 오른쪽(다음) 링크를 헤드 노드로 초기화
		new->llink = NULL;			//new노드의 왼쪽(이전) 링크를 NULL로 초기화

		listNode* temp = h->first;	//temp라는 노드를 선언하고 헤드 노드로 초기화

		temp->llink = new;			//temp노드의 왼쪽(이전) 링크를 new의 주소 값으로 초기화
		h->first = new;				//헤드 노드를 new노드로 초기화
	}
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) printf("Nothing to delete!\n");	//리스트가 공백이라면 경고 메시지 출력

	else {
		listNode* temp = h->first;	//temp라는 노드를 선언하고 NULL로 초기화
		h->first = temp->rlink;		//헤드 노드를 temp노드의 오른쪽(다음) 링크 값으로 초기화
		free(temp);					//temp노드의 메모리를 해제
	}

	return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	if (h->first == NULL) printf("Nothing to invert!\n");	//리스트가 공백이라면 경고 메시지 출력

	else {
		listNode* temp = h->first;	//리스트의 마지막을 찾을 임시 노드를 선언 및 헤드 노드로 초기화
		listNode* pre = NULL;
		listNode* mid = NULL;		//pre와 mid라는 노드를 선언 및 NULL로 초기화

		while (temp != NULL) {	//temp노드가 NULL이 될때 까지 반복
			pre = mid;			//pre노드를 mid노드로 초기화
			mid = temp;			//mid노드를 temp노드로 초기화
			temp = temp->rlink;	//temp노드를 오른쪽(다음) 노드로 이동
			mid->rlink = pre;	//mid노드의 오른쪽(다음) 링크를 pre노드로 초기화
			mid->llink = temp;	//mid노드의 왼쪽(이전) 링크를 temp노드로 초기화
		}
		h->first = mid;			//헤드 노드를 mid노드로 초기화
	}

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* new = (listNode*)malloc(sizeof(listNode));	//new라는 노드를 선언하고 메모리를 할당
	new->key = key;		//new노드의 키 값을 입력 받은 키 값으로 초기화
	new->rlink = NULL;
	new->llink = NULL;	//new노드의 좌우 링크를 NULL로 초기화

	if (h->first == NULL) h->first = new;	//리스트가 공백이라면 헤드 노드를 new노드로 초기화

	else {
		listNode* temp = h->first;			//키 값을 비교할 임시 노드를 선언하고 헤드 노드로 초기화

		while (temp != NULL) {				//temp노드가 NULL이 될때 까지 반복
			if (temp->key >= key) {			//temp노드의 키 값이 입력 받은 키 값보다 크거나 같은 경우
				if (temp == h->first) {		//temp노드가 첫번째 노드인 경우
					insertFirst(h, key);	//함수를 호출해 맨 앞에 노드를 삽입
				}
				else {							//temp노드가 첫번째 노드가 아닌 경우
					new->rlink = temp;			//new노드의 오른쪽(다음) 링크에 temp노드의 주소 값을 저장
					new->llink = temp->llink;	//new노드의 왼쪽(이전) 링크를 temp노드의 왼쪽(이전) 링크로 초기화
					temp->llink->rlink = new;	//temp노드의 왼쪽(이전) 링크의 오른쪽(다음) 링크에 new노드의 주소 값을 저장
				}
				return 0;		//노드를 삽입했다면 함수를 종료
			}
			temp = temp->rlink;	//temp노드를 오른쪽(다음) 노드로 이동
		}

		insertLast(h, key);		//입력 받은 키 값보다 큰 값이 없다면 함수를 호출해 리스트의 마지막에 노드를 삽입
	}

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) printf("Nothing to delete.\n");	//리스트가 공백이라면 경고 메시지 출력

	else {
		listNode* temp = h->first;	//키 값을 비교할 임시 노드를 선언하고 헤드 노드로 초기화

		while (temp != NULL) {					//temp노드가 NULL이 될때 까지 반복
			if (temp->key == key) {				//temp노드의 키 값이 입력 받은 키 값과 같은 경우
				if (temp == h->first) {			//temp노드가 첫번째 노드일 경우
					deleteFirst(h);				//함수를 호출하여 첫번째 노드를 삭제
				}
				else if (temp->rlink == NULL) {	//temp노드가 마지막 노드일 경우
					deleteLast(h);				//함수를 호출하여 마지막 노드를 삭제
				}
				else {
					temp->llink->rlink = temp->rlink;	//temp노드의 왼쪽(이전) 링크의 오른쪽(다음) 링크를 temp노드의 오른쪽(다음) 링크로 초기화
					temp->rlink->llink = temp->llink;	//temp노드의  오른쪽(다음) 링크의 왼쪽(이전) 링크를 temp노드의 왼쪽(이전) 링크로 초기화
					free(temp);							//temp노드의 메모리를 해제
				}
				return 1;		//노드를 삭제했다면 함수를 종료
			}
			temp = temp->rlink;	//temp노드를 오른쪽(다음) 노드로 이동
		}

		printf("Cannot find the node for key = %d\n", key);	//입력 받은 키 값과 일치하는 노드를 찾지 못한 경우 경고 메시지 출력
	}

	return 1;
}