#include <iostream>
#include <List.h>
#include <fstream>
#include <test.h>

using namespace std;

template <typename T>
bool operator ==(List<T> &lhs, List<T> &rhs){ // перегрузка оператора тождественно равно
    if(lhs.get_length() != rhs.get_length())
        return false;
    for(size_t i = 0; i < lhs.get_length(); i++){
        if(lhs.get_elem(i) != rhs.get_elem(i))
            return false;
    }
    return true;
}

template <typename T>
bool operator !=(List<T> &lhs, List<T> &rhs){ // перегрузка оператора не равно
    if(!(lhs == rhs))
        return true;
    return false;
}

template <typename T>
bool SumTwoElem(List<T> lhs, List<T> rhs, List<T> result){ // функция для тестирования
    auto temp = lhs + rhs;
    if(temp == result)
        return true;
    return false;
}

void StandartTest(){
    Assert(SumTwoElem(List<int>{1,2,3},List<int>{4,5,6},List<int>{1,2,3,4,5,6}), "сумма двух произвольных матриц");// здесь подряд можно указывать подобные тесты
}

int main()
{
    TestRunner unit_testing;
    unit_testing.RunTest(StandartTest," простой набор тестов");//докидай сюда ещё тестов
    return 0;
}
