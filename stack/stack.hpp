#include <iostream>
#include <utility>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class Stack{
    private: 
        int current;
        int size;
        T * array;

    public:
        Stack<T> (int _size = 16)
        {   
            current = -1;
            size = _size;
            array = new T[_size];
        }
        ~Stack()
        {
            delete[] array;
        }    

        bool isEmpty() const;
        bool isFull() const;
        T top() const;
        T pop();
        void push(const T& item);
};

template <typename T>
bool Stack<T>::isEmpty() const{
    //TODO
    return (current == -1);
}

template <typename T>
bool Stack<T>::isFull() const{
    //TODO
    return (current == size - 1);
}

template <typename T>
T Stack<T>::top() const{
    //TODO
    // 비어있을 때 고려해야 하나?
    return array[current];
}

template <typename T>
T Stack<T>::pop(){
    //TODO
    T value = array[current];
    array[current] = 0;
    current--;
    return value;
}

template <typename T>
void Stack<T>::push(const T& item){
    //TODO
    if (isFull())
    {
        return;
    } else {
        current++;
        array[current] = item;
    }
    
    return;
}

bool checkParentheses(const string& line, const vector<pair<char,char>>& pairs);
float calculate(const string& line);