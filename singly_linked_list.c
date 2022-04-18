/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode; //구조체타입 listNode

typedef struct Head {
	struct Node* first;
}headNode; //구조체타입 headNode 


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

/* 메인 함수 */
int main()
{
	printf("[----- [이동현] [2019038027] -----]\n\n");
	char command; //명령어를 담는 변수
	int key; 
	headNode* headnode=NULL; //포인터 headnode 초기화 

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
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
		case 'z': case 'Z':	//command가 z나 Z일 경우
			headnode = initialize(headnode);	//initialize함수 실행
			break;
		case 'p': case 'P': //command가 p나 P일 경우
			printList(headnode); //printList함수 실행
			break;
		case 'i': case 'I': //command가 i나 I일 경우
			printf("Your Key = ");	
			scanf("%d", &key); //key를 입력 받는다
			insertNode(headnode, key); //insertNode함수 실행
			break;
		case 'd': case 'D': //command가 d나 D일 경우
			printf("Your Key = ");
			scanf("%d", &key); //key를 입력 받는다
			deleteNode(headnode, key); //deleteode함수 실행
			break;
		case 'n': case 'N': //command가 n이나 N인 경우
			printf("Your Key = ");
			scanf("%d", &key); //key를 입력 받는다
			insertLast(headnode, key); //insertLast함수 실행
			break;
		case 'e': case 'E': //command가 e나 E인 경우
			deleteLast(headnode); //deleteLast함수 실행
			break;
		case 'f': case 'F': //command가 f나 F인 경우
			printf("Your Key = ");
			scanf("%d", &key); //key를 입력받는다
			insertFirst(headnode, key); //insertFirst함수 실행
			break;
		case 't': case 'T': //command가 t나 T인 경우
			deleteFirst(headnode); //deleteFirst함수 실행
			break;
		case 'r': case 'R': //command가 r이나 R인 경우
			invertList(headnode); //invertList함수 실행
			break;
		case 'q': case 'Q': //command가 q나 Q인 경우
			freeList(headnode); //freeList함수 실행
			break;
		default: //잘못된 입력 시
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //Concentration!! 메시지 출력
			break;
		}

	}while(command != 'q' && command != 'Q'); //q나 Q가 입력 될 떄 까지 반복

	return 1;
}

/* 메모리 할당 함수 */
headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL; //temp의 멤버 first 초기화
	return temp; //temp리턴
}

/* 메모리 해제 함수 */
int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //p에 h의 멤버 first값 저장

	listNode* prev = NULL; //prev 초기화
	while(p != NULL) { //p가 NULL이 아니라면 반복
		prev = p; //prev에 p 저장
		p = p->link; //p에 p의멤버 link 저장
		free(prev); //prev 메모리 해제
	}
	free(h); //h 메모리 해제
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node에 listNode의 사이즈 만큼의 메모리를 할당
	node->key = key; //node의 멤버 key에 key를 저장
	node->link = NULL; //node의 멤버 link 초기화 

	if (h->first == NULL) //h의 멤버 first가 NULL이라면
	{
		h->first = node; //h의 멤버 first에 node 저장
		return 0;
	}

	listNode* n = h->first; //n에 h의 멤버 first 저장
	listNode* trail = h->first; //trail에 h의 멤버 first저장

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { //n이 NULL이 아니라면 반복
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = node; //h의 first에 node 저장
				node->link = n; //node의 link에 n 저장
			 /* 중간이거나 마지막인 경우 */
			} else {
				node->link = n; //node의 link에 n저장
				trail->link = node; //trail의 link에 node 저장
			}
			return 0;
		}

		trail = n; //trail에 n 저장
		n = n->link; //n에 n의 link 저장
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node; //trail의 link에 node 저장
	return 0;
}

/*
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) { 

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode의 크기만큼 메모리를 node에 할당
	node->key = key; //node의 key에 key 저장
	node->link = NULL; //node의 link NULL로 초기화

	if (h->first == NULL) //h의 first가 NULL이라면
	{
		h->first = node; //h의 first에 node 저장
		return 0;
	}

	listNode* n = h->first; //n에 h의 first 저장
	while(n->link != NULL) { //n의 link가 NULL이 아니면 반복
		n = n->link; //n에 n의 link저장
	}
	n->link = node; //n의 link에 node 저장
	return 0;
}

/*
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode의 크기만큼 메모리를 node에 할당
	node->key = key; //node의 key에 key 저장

	node->link = h->first; //node의 link에 h의 first 저장
	h->first = node; //h의 first에 node 저장

	return 0;
}

/*
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //h의 first가 NULL이라면
	{
		printf("nothing to delete.\n"); //비었다는 메시지 출력
		return 0;
	}

	listNode* n = h->first; //n에 h의 first 저장
	listNode* trail = NULL; //trail NULL로 초기화

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { //n이 NULL이 아니라면 반복
		if(n->key == key) { //n의 key와 key가 같다면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { //n이 h의 first와 같다면
				h->first = n->link; //h의 first에 n의 link 저장
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link; //trail의 link에 n의 link 저장
			}
			free(n); //n 메모리 해제
			return 0;
		}

		trail = n; //trail에 n 저장
		n = n->link; //n에 n의 link 저장
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key); // 찾지 못했다는 메시지 출력
	return 0;

}

/*
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) //h의 first가 NULL이라면
	{
		printf("nothing to delete.\n"); //비었다는 메시지 출력
		return 0;
	}

	listNode* n = h->first; //n에 h의 first 저장
	listNode* trail = NULL; //trail NULL로 초기화

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) { //n의 link가 NULL 이라면
		h->first = NULL; //h의 first에 NULL 저장
		free(n); //n메모리 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) { //n의 link가 NULL이 아니라면 반복
		trail = n; //trail에 n저장
		n = n->link; //n에 n의 link저장
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL; //trail의 link에 NULL 저장
	free(n); //n 메모리 해제

	return 0;
}
/*
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) //h의 first가 NULL이라면
	{
		printf("nothing to delete.\n"); //비었다는 메시지 출력
		return 0;
	}
	listNode* n = h->first; //n에 h의 first 저장

	h->first = n->link; //h의 first에 n의 link 저장
	free(n); //n 메모리 해제

	return 0;
}


/*
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //h의 first가 NULL이라면
		printf("nothing to invert...\n"); //비었다는 메시지 출력
		return 0;
	}
	listNode *n = h->first; //n에 h의 first 저장
	listNode *trail = NULL; //trail NULL로 초기화
	listNode *middle = NULL; //middle NULL로 초기화

	while(n != NULL){ //n이 NULL이 아니면 반복
		trail = middle; //trail에 middle 저장
		middle = n; //middle에 n 저장
		n = n->link; //n에 n의 link 저장
		middle->link = trail; //middle의 link에 trail 저장
	}

	h->first = middle; //h의 first에 middle 저장

	return 0;
}

/* 프린트하는 함수 */
void printList(headNode* h) {
	int i = 0;
	listNode* p; //p 선언

	printf("\n---PRINT\n");

	if(h == NULL) { //h가 NULL이라면
		printf("Nothing to print....\n"); //비었다는 메시지 출력
		return;
	}

	p = h->first; //p에 h의 first 저장

	while(p != NULL) { //p가 NULL이 아니라면 반복
		printf("[ [%d]=%d ] ", i, p->key); //p의 key출력
		p = p->link; //p에 p의 link 저장
		i++; //i 증가
	}

	printf("  items = %d\n", i);
}

