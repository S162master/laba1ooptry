#ifndef ITERATOR_H
#define ITERATOR_H
#include "List.h"
template <typename  T>
class Iterator{ // вообще шляпа, но пусть будет
    private: //непосредственно класс итераторов для реализации правильных итераторов. Особенно нечего коментировать
        T* array;
        int length;
        int index;

    public:
        Iterator(List<T> lst){ //стандартный конструктор
            this->length = lst.get_length();
            this->array = new T[this->length];

            for (int i = 0; i < length; i++){
                this->array[i] = lst.get_elem(i);
            }

            this->index = 0;
        }

        ~Iterator(){// деструктор. Очистка памяти
            delete this->array;
        }

        void next(){// следующий элемент
            if (!this->isEnd()){
                this->index++;
            }

        }

        T value(){// Значение по итератору
            return this->array[this->index];
        }

        bool isEnd(){// последний элемент?
            if ((this->index + 1) == this->length)
                return true;
            else
                return false;
        }

        Iterator<T>& operator++(){//перегрузка унарного сложения
            if (!this->isEnd()){
                this->index++;
            }
            return *this;
        }

        T& operator*(){// перегрузка обращения к значению
            return this->array[this->index];
        }

        bool operator ==(Iterator& b){//тождественно равно
            if (this->array[this->index] == b.value())
                return true;
            else
                return false;
        }

        bool operator !=(Iterator &b){// неравенство
            if (this->array[this->index] == b.value())
                return false;
            else
                return true;
        }

        void iteratorBegin(){// первая ячейка списка
            this->index = 0;
        }

        void iteratorEnd(){// последняя ячейка списка
            this->index = this->length - 1;
        }

};

#endif // ITERATOR_H
