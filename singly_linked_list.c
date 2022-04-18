/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode; //����üŸ�� listNode

typedef struct Head {
	struct Node* first;
}headNode; //����üŸ�� headNode 


/* �Լ� ����Ʈ */
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

/* ���� �Լ� */
int main()
{
	printf("[----- [�̵���] [2019038027] -----]\n\n");
	char command; //��ɾ ��� ����
	int key; 
	headNode* headnode=NULL; //������ headnode �ʱ�ȭ 

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
		case 'z': case 'Z':	//command�� z�� Z�� ���
			headnode = initialize(headnode);	//initialize�Լ� ����
			break;
		case 'p': case 'P': //command�� p�� P�� ���
			printList(headnode); //printList�Լ� ����
			break;
		case 'i': case 'I': //command�� i�� I�� ���
			printf("Your Key = ");	
			scanf("%d", &key); //key�� �Է� �޴´�
			insertNode(headnode, key); //insertNode�Լ� ����
			break;
		case 'd': case 'D': //command�� d�� D�� ���
			printf("Your Key = ");
			scanf("%d", &key); //key�� �Է� �޴´�
			deleteNode(headnode, key); //deleteode�Լ� ����
			break;
		case 'n': case 'N': //command�� n�̳� N�� ���
			printf("Your Key = ");
			scanf("%d", &key); //key�� �Է� �޴´�
			insertLast(headnode, key); //insertLast�Լ� ����
			break;
		case 'e': case 'E': //command�� e�� E�� ���
			deleteLast(headnode); //deleteLast�Լ� ����
			break;
		case 'f': case 'F': //command�� f�� F�� ���
			printf("Your Key = ");
			scanf("%d", &key); //key�� �Է¹޴´�
			insertFirst(headnode, key); //insertFirst�Լ� ����
			break;
		case 't': case 'T': //command�� t�� T�� ���
			deleteFirst(headnode); //deleteFirst�Լ� ����
			break;
		case 'r': case 'R': //command�� r�̳� R�� ���
			invertList(headnode); //invertList�Լ� ����
			break;
		case 'q': case 'Q': //command�� q�� Q�� ���
			freeList(headnode); //freeList�Լ� ����
			break;
		default: //�߸��� �Է� ��
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //Concentration!! �޽��� ���
			break;
		}

	}while(command != 'q' && command != 'Q'); //q�� Q�� �Է� �� �� ���� �ݺ�

	return 1;
}

/* �޸� �Ҵ� �Լ� */
headNode* initialize(headNode* h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL; //temp�� ��� first �ʱ�ȭ
	return temp; //temp����
}

/* �޸� ���� �Լ� */
int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first; //p�� h�� ��� first�� ����

	listNode* prev = NULL; //prev �ʱ�ȭ
	while(p != NULL) { //p�� NULL�� �ƴ϶�� �ݺ�
		prev = p; //prev�� p ����
		p = p->link; //p�� p�Ǹ�� link ����
		free(prev); //prev �޸� ����
	}
	free(h); //h �޸� ����
	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node�� listNode�� ������ ��ŭ�� �޸𸮸� �Ҵ�
	node->key = key; //node�� ��� key�� key�� ����
	node->link = NULL; //node�� ��� link �ʱ�ȭ 

	if (h->first == NULL) //h�� ��� first�� NULL�̶��
	{
		h->first = node; //h�� ��� first�� node ����
		return 0;
	}

	listNode* n = h->first; //n�� h�� ��� first ����
	listNode* trail = h->first; //trail�� h�� ��� first����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) { //n�� NULL�� �ƴ϶�� �ݺ�
		if(n->key >= key) {
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {
				h->first = node; //h�� first�� node ����
				node->link = n; //node�� link�� n ����
			 /* �߰��̰ų� �������� ��� */
			} else {
				node->link = n; //node�� link�� n����
				trail->link = node; //trail�� link�� node ����
			}
			return 0;
		}

		trail = n; //trail�� n ����
		n = n->link; //n�� n�� link ����
	}

	/* ������ ������ ã�� ���� ��� , �������� ���� */
	trail->link = node; //trail�� link�� node ����
	return 0;
}

/*
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) { 

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode�� ũ�⸸ŭ �޸𸮸� node�� �Ҵ�
	node->key = key; //node�� key�� key ����
	node->link = NULL; //node�� link NULL�� �ʱ�ȭ

	if (h->first == NULL) //h�� first�� NULL�̶��
	{
		h->first = node; //h�� first�� node ����
		return 0;
	}

	listNode* n = h->first; //n�� h�� first ����
	while(n->link != NULL) { //n�� link�� NULL�� �ƴϸ� �ݺ�
		n = n->link; //n�� n�� link����
	}
	n->link = node; //n�� link�� node ����
	return 0;
}

/*
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode�� ũ�⸸ŭ �޸𸮸� node�� �Ҵ�
	node->key = key; //node�� key�� key ����

	node->link = h->first; //node�� link�� h�� first ����
	h->first = node; //h�� first�� node ����

	return 0;
}

/*
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //h�� first�� NULL�̶��
	{
		printf("nothing to delete.\n"); //����ٴ� �޽��� ���
		return 0;
	}

	listNode* n = h->first; //n�� h�� first ����
	listNode* trail = NULL; //trail NULL�� �ʱ�ȭ

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) { //n�� NULL�� �ƴ϶�� �ݺ�
		if(n->key == key) { //n�� key�� key�� ���ٸ�
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) { //n�� h�� first�� ���ٸ�
				h->first = n->link; //h�� first�� n�� link ����
			} else { /* �߰��� ���ų� �������� ��� */
				trail->link = n->link; //trail�� link�� n�� link ����
			}
			free(n); //n �޸� ����
			return 0;
		}

		trail = n; //trail�� n ����
		n = n->link; //n�� n�� link ����
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key); // ã�� ���ߴٴ� �޽��� ���
	return 0;

}

/*
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) //h�� first�� NULL�̶��
	{
		printf("nothing to delete.\n"); //����ٴ� �޽��� ���
		return 0;
	}

	listNode* n = h->first; //n�� h�� first ����
	listNode* trail = NULL; //trail NULL�� �ʱ�ȭ

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->link == NULL) { //n�� link�� NULL �̶��
		h->first = NULL; //h�� first�� NULL ����
		free(n); //n�޸� ����
		return 0;
	}

	/* ������ ������ �̵� */
	while(n->link != NULL) { //n�� link�� NULL�� �ƴ϶�� �ݺ�
		trail = n; //trail�� n����
		n = n->link; //n�� n�� link����
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->link = NULL; //trail�� link�� NULL ����
	free(n); //n �޸� ����

	return 0;
}
/*
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) //h�� first�� NULL�̶��
	{
		printf("nothing to delete.\n"); //����ٴ� �޽��� ���
		return 0;
	}
	listNode* n = h->first; //n�� h�� first ����

	h->first = n->link; //h�� first�� n�� link ����
	free(n); //n �޸� ����

	return 0;
}


/*
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //h�� first�� NULL�̶��
		printf("nothing to invert...\n"); //����ٴ� �޽��� ���
		return 0;
	}
	listNode *n = h->first; //n�� h�� first ����
	listNode *trail = NULL; //trail NULL�� �ʱ�ȭ
	listNode *middle = NULL; //middle NULL�� �ʱ�ȭ

	while(n != NULL){ //n�� NULL�� �ƴϸ� �ݺ�
		trail = middle; //trail�� middle ����
		middle = n; //middle�� n ����
		n = n->link; //n�� n�� link ����
		middle->link = trail; //middle�� link�� trail ����
	}

	h->first = middle; //h�� first�� middle ����

	return 0;
}

/* ����Ʈ�ϴ� �Լ� */
void printList(headNode* h) {
	int i = 0;
	listNode* p; //p ����

	printf("\n---PRINT\n");

	if(h == NULL) { //h�� NULL�̶��
		printf("Nothing to print....\n"); //����ٴ� �޽��� ���
		return;
	}

	p = h->first; //p�� h�� first ����

	while(p != NULL) { //p�� NULL�� �ƴ϶�� �ݺ�
		printf("[ [%d]=%d ] ", i, p->key); //p�� key���
		p = p->link; //p�� p�� link ����
		i++; //i ����
	}

	printf("  items = %d\n", i);
}

