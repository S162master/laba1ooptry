#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;


template<class T, class U>
void AssertEqual(const T& t, const U& u,
    const string& hint) // функция оповещения о результатах тестирования
{
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u
       << " hint: " << hint;
    throw runtime_error(os.str());
  }
}

inline void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);  // упрощение функции выше
}

class TestRunner { // класс для юнит тестирования
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) { // функция запуска тестов. В случае ошибки выведет текст красными буквами и укажет колличество тестов, которые не прошли
    try {
	  func();
	  cerr << test_name << " OK" << endl;
	} catch (runtime_error& e) {
	  ++fail_count;
	  cerr << test_name << " fail: " << e.what() << endl;
	}
  }

  ~TestRunner() { // деструктор, оповещающий об окончании тестирования
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0; // число непрошедших тестов
};
