/*
Группа школьников едет на олимпиаду и будет всю дорогу крутить спиннеры.
Поэтому им нужно купить места в нескольких подряд идущих купе вместе с прилегающими
боковыми местами. Даны номера свободных мест в поезде. Определите, какое наибольшее
число подряд идущих купе полностью свободны.
Программа получает на вход число N – количество свободных мест в вагоне
(0 ≤ N ≤ 54). Следующие N строк содержат номера свободных мест – различные числа от 1
до 54 в произвольном порядке, по одному числу в строке.
Программа должна вывести одно целое число – максимальное число подряд идущих
свободных купе (купе – 4 места слева от прохода и 2 боковых места) в этом вагоне.
*/
#include <bits/stdc++.h>
using namespace std;

//номер купе по номеру свободного места
int section(int n){
  if(n <= 36) return (n+3)/4;
  else return 10+(n-37)/2;
}

int max(vector <int> a, int n, int i){
  if(a.size() == 0) return 0;
  else {
    if(n < a[i] && i != a.size()-1) return max(a, a[i], i+1);
    else if(i == a.size()-1) return n;
  }
}

int main(){
//inputs
  int n; cin >> n;
  //Массив свободных мест (перемешанных)
  int a[n]; for(int i = 0; i < n; i++) cin >> a[i];
  //"Пустой" массив, показывающий "занятость" мест
  int b[18]; for(int i = 0; i < 18; i++) b[i] = 0;

//Показатель занятости мест
  for(int i = 0; i < n; i++){
    for(int j = 0; j < 18; j++){
    if(section(a[i]) == j+1) b[j] += 1;
    }
  }

  for(int i = 0; i < 18; i++) cout << i+1 << " " << b[i] << "\n";

vector <int> c;
for(int i = 0; i < 18; i++){
  if(i <= 8 && b[i] == 4) c.push_back(i+1);
  else if(i > 8 && b[i] ==2) c.push_back(i+1);
}

int cnt=0, max=0, maxid=0;
for(int i=1; i < c.size(); ++i){
  ++cnt;
  if  (c[i] < c[i-1])
    if (cnt > max){
      max=cnt;
      maxid=i-1;
      cnt=0;
    }
}
cout << cnt;
return 0;
}
