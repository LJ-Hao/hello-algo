/**
 * File: array_queue.c
 * Created Time: 2023-01-28
 * Author: Zero (glj0@outlook.com)
 */

#include "../include/include.h"

/* 基于环形数组形成的队列 */
struct ArrayQueue {
    int *nums;       // 用于存储队列元素的数组
    int front;       // 队首指针，指向队首元素
    int queSize;     // 尾指针，指向队尾 + 1
    int queCapacity; // 队列容量
};

typedef struct ArrayQueue ArrayQueue;

/* 构造函数 */
ArrayQueue *newArrayQueue(int capacity) {
    ArrayQueue *queue = (ArrayQueue *) malloc(sizeof(ArrayQueue));
    // 初始化数组
    queue->queCapacity = capacity;
    queue->nums = (int *) malloc(sizeof(int) * queue->queCapacity);
    queue->front = queue->queSize = 0;
    return queue;
}

/* 析构函数 */
void delArrayQueue(ArrayQueue *queue) {
    free(queue->nums);
    queue->queCapacity = 0;
}

/* 获取队列的容量 */
int capacity(ArrayQueue *queue) {
    return queue->queCapacity;
}

/* 获取队列的长度 */
int size(ArrayQueue *queue) {
    return queue->queSize;
}

/* 判断队列是否为空 */
bool empty(ArrayQueue *queue) {
    return queue->queSize == 0;
}

/* 访问队首元素 */
int peek(ArrayQueue *queue) {
  assert(size(queue) != 0);
  return queue->nums[queue->front];
}

/* 入队 */
void push(ArrayQueue *queue, int num) {
    if (size(queue) == capacity(queue)) {
        printf("队列已满\r\n");
        return;
    }
    // 计算队尾指针，指向队尾索引 + 1
    // 通过取余操作，实现 rear 越过数组尾部后回到头部
    int rear = (queue->front + queue->queSize) % queue->queCapacity;
    // 尾结点后添加 num
    queue->nums[rear] = num;
    queue->queSize++;
}

/*  出队 */
void poll(ArrayQueue *queue) {
    int num = peek(queue);
    // 队首指针向后移动一位，若越过尾部则返回到数组头部
    queue->front = (queue->front + 1) % queue->queCapacity;
    queue->queSize--;
}

/* 打印基于环形数组形成的队列 */
void printArrayQueue(ArrayQueue *queue) {
    int arr[queue->queSize];
    // 拷贝
    for (int i = 0, j = queue->front; i < queue->queSize; i++, j++) {
        arr[i] = queue->nums[j % queue->queCapacity];
    }
    printArray(arr, queue->queSize);
}


/* Driver Code */
int main() {
    /* 初始化队列 */
    int capacity = 10;
    ArrayQueue *queue = newArrayQueue(capacity);

    /* 元素入队 */
    push(queue, 1);
    push(queue, 3);
    push(queue, 2);
    push(queue, 5);
    push(queue, 4);
    printf("队列 queue = ");
    printArrayQueue(queue);

    /* 访问队首元素 */
    int peekNum = peek(queue);
    printf("队首元素 peek = %d\r\n", peekNum);

    /* 元素出队 */
    poll(queue);
    printf("出队元素 poll = %d，出队后 queue = ", peekNum);
    printArrayQueue(queue);

    /* 获取队列的长度 */
    int queueSize = size(queue);
    printf("队列长度 size = %d\r\n", queueSize);

    /* 判断队列是否为空 */
    bool isEmpty = empty(queue);
    printf("队列是否为空 = %s\r\n", isEmpty ? "true" : "false");

    /* 测试环形数组 */
    for (int i = 0; i < 10; i++) {
        push(queue, i);
        poll(queue);
        printf("第 %d 轮入队 + 出队后 queue = ", i);
        printArrayQueue(queue);
    }

    // 释放内存
    delArrayQueue(queue);
    return 0;
}