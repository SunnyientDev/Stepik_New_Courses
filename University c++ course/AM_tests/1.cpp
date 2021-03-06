/*
Арифметические операции (запрещено использование условных конструкций и циклов)

Распространённая задача:  Дано четырехзначное число (к примеру 5678), вывести на экран  в обратном порядке цифры из которых это число состоит. То есть мы должны увидеть на экране 8765. Подсказка: чтобы взять из числа отдельные цифры, надо применять  деление по модулю на 10.
*/
#include <iostream>
using namespace std;

void func(int n){
  if(n < 10) cout << n;
  else { cout << n%10; func((n-n%10)/10);}
}

int main() {
  int x; cin >> x;
  if(x > 999) func(x); 
  else cout << "Error";
  return 0;
}
