/**
 * circularQ.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */


 
#include <stdio.h>
#include <stdlib.h>

int name()
{
char *name = "Kim sieun";
char *id = "2021053007";

printf("-----[%s] [%s]-----\n\n", name, id); //name, id 출력
}

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue(); // 새로운 큐를 생성
int freeQueue(QueueType *cQ); // 동적할당된 큐를 해제
int isEmpty(QueueType *cQ); // 큐가 비어있는지 확인
int isFull(QueueType *cQ); // 큐가 가득 찼는지 확인
void enQueue(QueueType *cQ, element item); // 큐에 데이터를 추가
void deQueue(QueueType *cQ, element* item); // 큐에서 데이터를 삭제한 후 반환
void printQ(QueueType *cQ); // 큐의 모든 데이터를 출력
void debugQ(QueueType *cQ); // 큐의 내부 정보를 출력
element getElement(); // 새로운 데이터를 입력


int main(void)
{
	QueueType *cQ = createQueue(); // 새로운 큐 생성
	element data;

	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 사용자의 입력을 받음

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType)); //메모리 할당 크기
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1; // 큐가 해제되어 있는 경우
    free(cQ); // 동적할당 메모리 해제
    return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item); // 사용자로부터 새로운 입력을 받음
	return item;
}


int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear){
		printf("Circular Queue is empty!");
		return 1; // 큐가 비어있는 경우 1 반환
	}
	else return 0;
}

int isFull(QueueType *cQ)
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {
		printf(" Circular Queue is full!"); // 큐가 가득 차있는 경우
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item) // 큐에 값 삽입
{
	if(isFull(cQ)) return; // 가득찬 경우 실행 취소 
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; // rear를 증가시키고 rear에 값 삽입
		cQ->queue[cQ->rear] = item;
	}
}

void deQueue(QueueType *cQ, element *item) // 큐에서 값 제거
{
	if(isEmpty(cQ)) return; //큐가 비어있다면 실행 취소
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE; // front의 값을 감소시키면 제거
		*item = cQ->queue[cQ->front];
		return;
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) // 큐의 내용, front, rear 출력
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}


