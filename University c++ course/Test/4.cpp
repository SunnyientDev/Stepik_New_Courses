/*
4. Рекурсия (запрещено использовать циклы)

С помощью рекурсивной функции найти число Фибоначчи под номером n, которое вводит пользователь. Напоминаю, что числа Фибоначчи 0 1 1 2 3 5 8 13 21 34 и т. д. образуются путем суммирования двух предыдущих чисел последовательности.

Рекомендация. Для проверки правильности работы вашей функции, из main() выведите с помощью цикла for на консоль несколько возвращаемых ею значений при различных параметрах, получив ряд чисел, указанных выше.
*/

#include <iostream>
#include <string>
using namespace std;

int fib(int x){
  if(x == 1 or x == 2) return 1;
  else return fib(x-1) + fib(x-2);
}

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int x; cin >> x;
  cout << fib(x);
  return 0;
}