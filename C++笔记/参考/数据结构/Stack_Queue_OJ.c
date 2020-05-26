1.https://leetcode-cn.com/problems/valid-parentheses/
typedef char STDataType;
typedef struct Stack
{
	STDataType* _a;
	int _top;
	int _capacity;
}Stack;

void StackInit(Stack* ps, int n)
{
	assert(ps);
	ps->_a = (STDataType*)malloc(sizeof(STDataType)*n);
	ps->_top = 0;
	ps->_capacity = n;
}

void StackPush(Stack* ps, STDataType x)
{
	assert(ps);
	if (ps->_top == ps->_capacity)
	{
		ps->_a = (STDataType*)realloc(ps->_a, ps->_capacity * 2*sizeof(STDataType));
		ps->_capacity *= 2;
	}

	ps->_a[ps->_top] = x;
	ps->_top++;
}

void StackPop(Stack* ps)
{
	assert(ps);
	if (ps->_top > 0)
	{
		ps->_top--;
	}
}

STDataType StackTop(Stack* ps)
{
	assert(ps);

	return ps->_a[ps->_top - 1];
}

int StackSize(Stack* ps)
{
	assert(ps);

	return ps->_top;
}

int StackEmpty(Stack* ps)
{
	assert(ps);

	return ps->_top == 0 ? 0 : 1;
}

bool isValid(char* s) 
{
    struct Stack st;
    StackInit(&st, 10);
    char symbols[][2] = { 
	    { '(', ')' },
	    { '[', ']' },
	    { '{', '}' },
    };
    while (*s)
    {
        int i = 0;
        for (; i < 3; ++i)
        {
            if (*s == symbols[i][0])
            {
                StackPush(&st, *s);
                ++s;
                break;
            }
        }
        
        if(i == 3)
        {
            // 走到这里说明*s不是左括号
            char top = StackTop(&st);
            for (int j = 0; j < 3; ++j)
            {
                if (*s == symbols[j][1])
                {
                    if (top == symbols[j][0])
                    {
                        ++s;
                        StackPop(&st);
                        break;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
           
       
    }

	if (StackEmpty(&st) == 0)
		return true;
	else
		return false;
}

2、
https://leetcode-cn.com/submissions/detail/8224510/
typedef int QUDataType;

typedef struct QueueNode
{
	QUDataType _data;
	struct QueueNode* _next;
}QueueNode;

typedef struct Queue
{
	QueueNode* _front;
	QueueNode* _rear;
}Queue;

void QueueInit(Queue* q)
{
	assert(q);
	q->_front = q->_rear = NULL;
}

void QueueDestory(Queue* q)
{
	assert(q);
	QueueNode* cur = q->_front;
	while (cur)
	{
		QueueNode* next = cur->_next;
		free(cur);
		cur = next;
	}

	q->_front = q->_rear = NULL;
}

QueueNode* BuyQueueNode(QUDataType x)
{
	QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
	node->_data = x;
	node->_next = NULL;
	return node;
}

void QueuePush(Queue* q, QUDataType x)
{
	assert(q);
	if (q->_front == NULL)
	{
		q->_front = q->_rear = BuyQueueNode(x);
	}
	else
	{
		q->_rear->_next = BuyQueueNode(x);
		q->_rear = q->_rear->_next;
	}
}

void QueuePop(Queue* q)
{
	if (q->_front)
	{
		QueueNode* next = q->_front->_next;
		free(q->_front);
		q->_front = next;

		if (q->_front == NULL)
		{
			q->_rear = NULL;
		}
	}
}

int QueueSize(Queue* q)
{
	assert(q);
	int size = 0;
	QueueNode* cur = q->_front;
	while (cur)
	{
		++size;
		cur = cur->_next;
	}

	return size;
}

int QueueEmpty(Queue* q)
{
	assert(q);
	return q->_front == NULL ? 0 : 1;
}

QUDataType QueueFront(Queue* q)
{
	assert(q);
	return q->_front->_data;
}

QUDataType QueueBack(Queue* q)
{
	assert(q);

	return q->_rear->_data;
}

typedef struct {
    Queue q1;
    Queue q2;
    
} MyStack;

/** Initialize your data structure here. */
MyStack* myStackCreate(int maxSize) {
    MyStack* pst = (MyStack*)malloc(sizeof(MyStack));
    QueueInit(&pst->q1);
    QueueInit(&pst->q2);
        
    return pst;
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {
    if(QueueEmpty(&obj->q1) != 0)
    {
        QueuePush(&obj->q1, x);
    }
    else
    {
        QueuePush(&obj->q2, x);
    }
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
    Queue* pEmpty = &obj->q1, *pNonEmpty = &obj->q2;
    if(QueueEmpty(&obj->q1) != 0)
    {
        pEmpty = &obj->q2;
        pNonEmpty = &obj->q1;
    }
    
    while(QueueSize(pNonEmpty) > 1)
    {
        QueuePush(pEmpty, QueueFront(pNonEmpty));
        QueuePop(pNonEmpty);
    }
    
    int top = QueueFront(pNonEmpty);
    QueuePop(pNonEmpty);
    
    return top;
}

/** Get the top element. */
int myStackTop(MyStack* obj) {
    Queue* pEmpty = &obj->q1, *pNonEmpty = &obj->q2;
    if(QueueEmpty(&obj->q1) != 0)
    {
        pEmpty = &obj->q2;
        pNonEmpty = &obj->q1;
    }
    
    return QueueBack(pNonEmpty);
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {
    return !(QueueEmpty(&obj->q1) | QueueEmpty(&obj->q2));
}

void myStackFree(MyStack* obj) {
    QueueDestory(&obj->q1);
    QueueDestory(&obj->q2);
    free(obj);
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * struct MyStack* obj = myStackCreate(maxSize);
 * myStackPush(obj, x);
 * int param_2 = myStackPop(obj);
 * int param_3 = myStackTop(obj);
 * bool param_4 = myStackEmpty(obj);
 * myStackFree(obj);
 */
 
 3、
 https://leetcode-cn.com/submissions/detail/8139810/
 typedef int STDataType;
typedef struct Stack
{
	STDataType* _a;
	int _top;
	int _capacity;
}Stack;

void StackInit(Stack* ps, int n)
{
	assert(ps);
	ps->_a = (STDataType*)malloc(sizeof(STDataType)*n);
	ps->_top = 0;
	ps->_capacity = n;
}

void StackDestroy(Stack* ps)
{
	assert(ps);
    free(ps->_a);
    ps->_a = NULL;
    ps->_top = ps->_capacity = 0;
}

void StackPush(Stack* ps, STDataType x)
{
	assert(ps);
	if (ps->_top == ps->_capacity)
	{
		ps->_a = (STDataType*)realloc(ps->_a, ps->_capacity * 2*sizeof(STDataType));
		ps->_capacity *= 2;
	}

	ps->_a[ps->_top] = x;
	ps->_top++;
}

void StackPop(Stack* ps)
{
	assert(ps);
	if (ps->_top > 0)
	{
		ps->_top--;
	}
}

STDataType StackTop(Stack* ps)
{
	assert(ps);

	return ps->_a[ps->_top - 1];
}

int StackSize(Stack* ps)
{
	assert(ps);

	return ps->_top;
}

int StackEmpty(Stack* ps)
{
	assert(ps);

	return ps->_top == 0 ? 0 : 1;
}


typedef struct {
    Stack pushST;
    Stack popST;
} MyQueue;

/** Initialize your data structure here. */
MyQueue* myQueueCreate(int maxSize) {
    MyQueue* pqueue = (MyQueue*)malloc(sizeof(MyQueue));
    StackInit(&pqueue->pushST, maxSize);
    StackInit(&pqueue->popST, maxSize);
    return pqueue;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
    StackPush(&obj->pushST, x);
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
    if(StackEmpty(&obj->popST) == 0)
    {
        while(StackEmpty(&obj->pushST) != 0)
        {
            StackPush(&obj->popST, StackTop(&obj->pushST));
            StackPop(&obj->pushST);
        }
    }
    
    int front = StackTop(&obj->popST);
    StackPop(&obj->popST);
    return front;
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
       if(StackEmpty(&obj->popST) == 0)
    {
        while(StackEmpty(&obj->pushST) != 0)
        {
            StackPush(&obj->popST, StackTop(&obj->pushST));
            StackPop(&obj->pushST);
        }
    }
    
    return StackTop(&obj->popST);
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
    return StackEmpty(&obj->pushST) == 0
        &&  StackEmpty(&obj->popST) == 0;
}

void myQueueFree(MyQueue* obj) {
    StackDestroy(&obj->pushST);
    StackDestroy(&obj->popST);
    
    free(obj);
}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * struct MyQueue* obj = myQueueCreate(maxSize);
 * myQueuePush(obj, x);
 * int param_2 = myQueuePop(obj);
 * int param_3 = myQueuePeek(obj);
 * bool param_4 = myQueueEmpty(obj);
 * myQueueFree(obj);
 */


//4 
https://leetcode-cn.com/problems/min-stack/
typedef struct {
    int* pst;
    int stTop;
    
    int* pminST;
    int minSTTop;
} MinStack;

/** initialize your data structure here. */
MinStack* minStackCreate() {
	int maxSize = 10000;
    MinStack* pst = (MinStack*)malloc(sizeof(MinStack));
    pst->pst = (int*)malloc(sizeof(int)*maxSize);
    pst->stTop = 0;
    
    pst->pminST = (int*)malloc(sizeof(int)*maxSize);
    pst->minSTTop = 0;
    
    return pst;
}

void minStackPush(MinStack* obj, int x) {
    int* pst = obj->pst;
    int* pminST = obj->pminST;
    
    pst[obj->stTop++] = x;
    if(obj->minSTTop == 0 
       || x <= pminST[obj->minSTTop-1])
    {
       pminST[obj->minSTTop++] = x; 
    }
}

void minStackPop(MinStack* obj) {
    int* pst = obj->pst;
    int* pminST = obj->pminST;
    if(pst[obj->stTop-1] == pminST[obj->minSTTop-1])
    {
        --obj->minSTTop;
    }
    
    --obj->stTop;
}

int minStackTop(MinStack* obj) {
    return obj->pst[obj->stTop-1];
}

int minStackGetMin(MinStack* obj) {
    return obj->pminST[obj->minSTTop-1];
}

void minStackFree(MinStack* obj) {
    free(obj->pst);
    free(obj->pminST);
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * struct MinStack* obj = minStackCreate(maxSize);
 * minStackPush(obj, x);
 * minStackPop(obj);
 * int param_3 = minStackTop(obj);
 * int param_4 = minStackGetMin(obj);
 * minStackFree(obj);
 */
 
 5.
 https://leetcode-cn.com/problems/design-circular-queue/
 typedef struct {
    int* queue;
    int front;
    int rear;
    int k
} MyCircularQueue;

/** Initialize your data structure here. Set the size of the queue to be k. */
MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue* pcq = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
    pcq->queue = (int*)malloc(sizeof(int)*(k+1));
    pcq->front = 0;
    pcq->rear = 0;
    pcq->k = k;
    
    return pcq;
}

/** Insert an element into the circular queue. Return true if the operation is successful. */
bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if((obj->rear+1)%(obj->k+1) == obj->front)
    {
        return false;
    }
    
    obj->queue[obj->rear++] = value;
    if(obj->rear == obj->k+1)
        obj->rear = 0;
    
    return true;
}

/** Delete an element from the circular queue. Return true if the operation is successful. */
bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if(obj->front == obj->rear)
        return false;
    
    ++obj->front;
    if(obj->front == obj->k+1)
        obj->front = 0;
    
    return true;
}

/** Get the front item from the queue. */
int myCircularQueueFront(MyCircularQueue* obj) {
    if(obj->front == obj->rear)
        return -1;
    else
        return obj->queue[obj->front];
}

/** Get the last item from the queue. */
int myCircularQueueRear(MyCircularQueue* obj) {
     if(obj->front == obj->rear)
        return -1;
    
    if(obj->rear == 0)
        return obj->queue[obj->k];
    else
        return obj->queue[obj->rear-1];
}

/** Checks whether the circular queue is empty or not. */
bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    return obj->front == obj->rear;
}

/** Checks whether the circular queue is full or not. */
bool myCircularQueueIsFull(MyCircularQueue* obj) {
    return (obj->rear+1)%(obj->k+1) == obj->front;
}

void myCircularQueueFree(MyCircularQueue* obj) {
    free(obj->queue);
    free(obj);
}

/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * struct MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);
 * bool param_2 = myCircularQueueDeQueue(obj);
 * int param_3 = myCircularQueueFront(obj);
 * int param_4 = myCircularQueueRear(obj);
 * bool param_5 = myCircularQueueIsEmpty(obj);
 * bool param_6 = myCircularQueueIsFull(obj);
 * myCircularQueueFree(obj);
 */
 
 5
 https://leetcode-cn.com/submissions/detail/8144561/
 
 typedef struct {
    int* queue;
    int front;
    int rear;
    int k
} MyCircularQueue;

/** Initialize your data structure here. Set the size of the queue to be k. */
MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue* pcq = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
    pcq->queue = (int*)malloc(sizeof(int)*(k+1));
    pcq->front = 0;
    pcq->rear = 0;
    pcq->k = k;
    
    return pcq;
}

/** Insert an element into the circular queue. Return true if the operation is successful. */
bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if((obj->rear+1)%(obj->k+1) == obj->front)
    {
        return false;
    }
    
    obj->queue[obj->rear++] = value;
    if(obj->rear == obj->k+1)
        obj->rear = 0;
    
    return true;
}

/** Delete an element from the circular queue. Return true if the operation is successful. */
bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if(obj->front == obj->rear)
        return false;
    
    ++obj->front;
    if(obj->front == obj->k+1)
        obj->front = 0;
    
    return true;
}

/** Get the front item from the queue. */
int myCircularQueueFront(MyCircularQueue* obj) {
    if(obj->front == obj->rear)
        return -1;
    else
        return obj->queue[obj->front];
}

/** Get the last item from the queue. */
int myCircularQueueRear(MyCircularQueue* obj) {
     if(obj->front == obj->rear)
        return -1;
    
    if(obj->rear == 0)
        return obj->queue[obj->k];
    else
        return obj->queue[obj->rear-1];
}

/** Checks whether the circular queue is empty or not. */
bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    return obj->front == obj->rear;
}

/** Checks whether the circular queue is full or not. */
bool myCircularQueueIsFull(MyCircularQueue* obj) {
    return (obj->rear+1)%(obj->k+1) == obj->front;
}

void myCircularQueueFree(MyCircularQueue* obj) {
    free(obj->queue);
    free(obj);
}

/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * struct MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);
 * bool param_2 = myCircularQueueDeQueue(obj);
 * int param_3 = myCircularQueueFront(obj);
 * int param_4 = myCircularQueueRear(obj);
 * bool param_5 = myCircularQueueIsEmpty(obj);
 * bool param_6 = myCircularQueueIsFull(obj);
 * myCircularQueueFree(obj);
 */











