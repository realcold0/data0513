#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 20
typedef char element;
typedef struct { // 큐 타입
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} DequeType;

// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 초기화 
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 원형큐 출력 함수
void deque_print(DequeType* q)
{
	printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

// 삽입 함수
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 삭제 함수
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// 삭제 함수
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}

element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[q->rear];
}

int main(void)
{
	while (1)
	{
		DequeType queue;

		init_deque(&queue);
		char exit[] = "exit";
		printf("Enter a string(or input 'exit' : ");
		char s[100];
		scanf_s(" %[^\n]s", s, sizeof(s));

		int len = strlen(s);
		//홀수일때랑 짝수일때
		if (strcmp(s, exit) == 0)
		{
			return 0;
		}

		for (int i = len-1; i >= 0; i--)
		{
			if (s[i] >= 'a' && s[i] <= 'z')
			{

				add_front(&queue, s[i]);

			}
			else if (s[i] >= 'A' && s[i] <= 'Z')
			{
				s[i] = s[i] + 32;
				add_front(&queue, s[i]);
			}

		} //문자만 입력

		int check = 0;

		for (int i = 0; i < strlen(s); i++)
		{
			if (s[i] >= 'a' && s[i] <= 'z')
			{
				char tmp = delete_rear(&queue);
				if (s[i] == tmp)
				{
					check++;
				}
				else {
					check = 0;
					break;
				}
			}


		}
		if (check > 0)
		{
			printf("회문입니다.\n");
		}
		else {
			printf("회문이 아닙니다.\n");

		}



	}

	return 0;
}