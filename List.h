#ifndef LIST_H
#define LIST_H
#define SIZE 10000000
template<class type>
class List {
    type* list;
    int size;
    int capacity;
public:
    List<type>() {
        capacity = SIZE;
        list = new type[capacity];
        size = 0;
    }
    List<type>(int _capacity) {
        capacity = _capacity;
        list = new type[capacity];
        size = 0;
    }
    void add(type t) {
        list[size] = t;
        size++;
    }
    void append_list(List<type>& list) {
        for (int i = 0; i < list.get_size_list(); i++) {
            add(list.get_value(i));
        }
    }
    type get_value(int index) { return list[index]; }
    void append_value(int index, type value) { list[index] = value; }
    int get_size_list() { return size; }
    void remove() { size--; }
    void clear() { size = 0; }
    void swap(int index, int _index) {
        type index_t = list[index];
        list[index] = list[_index];
        list[_index] = index_t;
    }
    void reverse() {
        for (int i = 0; i < size / 2; i++) {
            type index_t = list[i];
            list[i] = list[size - 1 - i];
            list[size - 1 - i] = index_t;
        }
    }
    type* begin() { return &list[0]; }
    type* end() { return &list[size]; }
    void print() {
        for (int i = 0; i < size; i++) {
            list[i].print();
            printf_s(" ");
        }
    }
};
#endif