#ifndef STACK_H
#define STACK_H
class Stack {
    int* stack_;
    int capacity;
    int size;
    int top;
public:
    Stack() {
        capacity = SIZE;
        stack_ = new int[capacity];
        top = -1;
        size = 0;
    }
    Stack(int _capacity) {
        capacity = _capacity;
        stack_ = new int[capacity];
        top = -1;
        size = 0;
    }
    void push(int elem) {
        try {
            if (size == capacity) { throw std::logic_error("Stack overflow"); }
            top++;
            size++;
            stack_[top] = elem;
        }
        catch (const char* msg) {
            printf("%ñ\n", msg);
            exit(0);
        }
    }
    int pop() {
        try {
            if (size == 0) { throw std::logic_error("Stack pop"); }
            top--;
            size--;
            return stack_[top + 1];
        }
        catch (const char* msg) {
            printf("%ñ\n", msg);
            exit(0);
        }
    }
    int peek() {
        try {
            if (size == 0) { throw std::logic_error("Stack peek"); }
            return stack_[top];
        }
        catch (const char* msg) {
            printf("%ñ\n", msg);
            exit(0);
        }
    }
    int get_size_stack() { return size; }
    bool empty() { return size == 0; }
    int next_to_top() {
        try {
            if (size == 1) { throw std::logic_error("Stack undeflow"); }
            return stack_[top - 1];
        }
        catch (const char* msg) {
            printf("%ñ\n", msg);
            exit(0);
        }
    }
    void print() {
        for (int i = 0; i < size; i++) {
            printf("%d ", stack_[i]);
        }
        printf("\n");
    }
};
#endif
