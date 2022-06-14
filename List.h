#ifndef LIST_H
#define LIST_H

#include <cstdlib>
#include <iostream>

template <typename T>
class List{ // нужный класс список
private:
    T* array; // массив элементов
    size_t length = 0; // размер массива

public:

    explicit List(std::initializer_list<T> lst); // явный конструктор со списком инициализации

    template<typename Y>
    friend List<Y> operator +( List<Y>& l1, List<Y>& l2); // бинарный оператор суммирования. Дружественная функция, не принадлежит классу список

    template<typename Y>
    friend std::ostream& operator <<(std::ostream& os, List<Y>& lst); // оператор ввода-вывода. Дружественная функция


    List(){ // стандартный конструктор
        length = 0;
        array = new T[1];
    }

    ~List(){ // стандартный деструктор
        delete[] array; // освобождение памяти
    }

    List(const List<T>& list){ //перегрузка конструктора. Нужно по условию
       this->length = list.get_length();
        array = new T[length];
        for (int i = 0; i < length; i++){
            array[i] = list.get_elem(i);
        }
    }

    List<T>& operator =(const List<T>& lst){ // перегрузка бинарного оператора присвоения
        length = lst.get_length();
        array = (T*)realloc(array, length * sizeof(T));
        for (int i = 0; i < length; i++){
            array[i] = lst.get_elem(i);
        }
        return *this;
    }

    int get_length() const { //вернуть размер списка
        return length;
    }

    void clear(){ // метод очистки списка
        length = 0;
        delete[] array;
        array = new T;
        if(array == NULL)
            std::cout<<"Error\n";
    }

    T& get_elem(int index) const { // возвращение элемента по индексу
        if (index < length){
            return *(array + index);
        }
    }

    void set_elem(int index, T& elem){ // установление значения элемента по его индексу
        if (index < length){
            *(array + index) = elem;
        }
    }

    void add(T& elem){ // добавление в конец списка ещё одного элемента
        length++;
        array = (T*)realloc(array, length * sizeof(T));
        array[length - 1] = elem;
    }

    void add_range(List<T>& list){ //добавить список элементов в конец
        for (int i = 0; i < list.get_length(); i++){
            add(list.get_elem(i));
        }
    }

    void add_range(T* arr, int size){ // добавить массив элементов в конец
        for (int i = 0; i < size; i++){
            add(arr[i]);
        }
    }

    void remove_elem(int index){ // удалить элемент по индексу
        if (index < length){
            T* temp = new T[length - 1];
            int j = 0;
            for (int i = 0; i < length; i++){
                if (i != index){
                    temp[j] = array[i];
                    j++;
                }
            }
            length--;
            array = (T*)realloc(array, length * sizeof(T));
            for (int i = 0; i < length; i++){
                array[i] = temp[i];
            }
            delete[] temp;
        }
    }

    List<T>& combine(List<T>& list){ //объединение списков
        add_range(list);
        return *this;
    }

    void sort(int (*comp)(T& r1, T& r2)){ // сортировочка
        for (int i = 0; i < length - 1; i++){
            for (int j = i + 1; j < length; j++){
                if (comp(array[i], array[j])){
                    auto temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }
    }

    int get_index(T& elem){ //поиск элемента по индексу
        int ind = -1;
        for (int i = 0; i < length; i++){
            if (array[i] == elem){
                ind = i;
                break;
            }
        }
        return ind;
    }

    T* to_array(){ //перейти к указателю на 0 элемент
        return array;
    }

    T& operator[](int index){ // обращение через квадратные скобки
        return get_elem(index);
    }

    List<T>& operator+=( List<T>& list){ // переопределение бинарного оператора сложения
        add_range(list);
        return *this;
    }


};

template <typename T>
List<T>::List(std::initializer_list<T> lst){ //реализация явного конструктора со списком инициализации
    length = lst.size();
    array = new T[length];
    int j = 0;
    for (T elem: lst){
        array[j] = elem;
        j++;
    }
}

template <typename T>
List<T> operator +(List<T>& lhs, List<T>& rhs){ // перегрузка оператора суммирования
    List<T> newList(lhs);
    newList.combine(rhs);
    return newList;
}


template<typename T>
std::ostream& operator <<(std::ostream& os, List<T>& lst){ // перегрузка оператора вывода в консоль
    for (int i = 0; i < lst.length; i++){
        os << lst.array[i] << " ";
    }
    return os;
}

#endif // LIST_H
