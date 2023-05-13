#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 20
typedef char element;
typedef struct { // ť Ÿ��
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} DequeType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// �ʱ�ȭ 
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ����ť ��� �Լ�
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

// ���� �Լ�
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// ���� �Լ�
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// ���� �Լ�
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}

element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
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
		//Ȧ���϶��� ¦���϶�
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

		} //���ڸ� �Է�

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
			printf("ȸ���Դϴ�.\n");
		}
		else {
			printf("ȸ���� �ƴմϴ�.\n");

		}



	}

	return 0;
}