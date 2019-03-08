#ifndef SEQSTACK_H
#define SEQSTACK_H

template <class T>
class SeqStack
{
public:
    SeqStack();
    virtual ~SeqStack();
    void push( const T t) {
        stack[++top] = t;
    }

    T pop() {
        return stack[top--];
    }

    bool getTop(T& t) {
        if( isEmpty() )
            return false;
        t = stack[top];
        return true;
    }

    bool isEmpty() {
       return top == -1;
    }

    bool isFull() {
        return top == max;
    }

    int getSize() {
        return top;
    }

    void clear() {
        top = -1;
    }

private:
    T * stack;
    int top;
    int max;
};


template <class T>
SeqStack<T>::SeqStack():  top(-1), max(50) {
    stack = new T[max];
//    push('#');
}

template <class T>
SeqStack<T>::~SeqStack() {
    delete [] stack;
}

#endif // SEQSTACK_H
