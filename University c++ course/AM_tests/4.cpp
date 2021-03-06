/*
Рекурсия (запрещено использовать циклы)

С помощью рекурсивной функции найти число Фибоначчи под номером n, которое вводит пользователь. Напоминаю, что числа Фибоначчи 0 1 1 2 3 5 8 13 21 34 и т. д. образуются путем суммирования двух предыдущих чисел последовательности. 

Рекомендация. Для проверки правильности работы вашей функции, из main() выведите с помощью цикла for на консоль несколько возвращаемых ею значений при различных параметрах, получив ряд чисел, указанных выше.
*/
#include <iostream>
using namespace std;

int fib(int n){
  if(n == 1) return 0;
  else if(n == 2 || n == 3) return 1;
  else return fib(n-1)+fib(n-2);
}

int main() {
int x; cin >> x;
cout << fib(x);
  return 0;
}
