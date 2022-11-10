/*
Попов Илья Павлович
M8O-306Б-20
Bариант 4: Игра с числом

Имеется натуральное число n. За один ход с ним можно произвести следующие действия:
    Вычесть единицу
    Разделить на два
    Разделить на три
При этом стоимость каждой операции - текущее значение n. 
Стоимость преобразования - суммарная стоимость всех операций в 
преобразовании. Вам необходимо с помощью последовательностей 
указанных операций преобразовать число n в единицу таким образом, 
чтобы стоимость преобразования была наименьшей. Делить можно только нацело.
*/

#include <iostream>
#include <vector>

using namespace std;
#define endl '\n';

int main(){
	int n; cin >> n;
	vector<int> coast(n + 1), res(n + 1);

    for (int i = 2; i <= n; i++) {
        coast[i] = coast[i - 1] + i; //вычитание единицы
        res[i] = 1;

        if (i % 2 == 0 && coast[i / 2] + i < coast[i]) { //деление на 2
            coast[i] = coast[i / 2] + i;
            res[i] = 2;
        }
        if (i % 3 == 0 && coast[i / 3] + i < coast[i]) { //деление на 3
            coast[i] = coast[i / 3] + i;
            res[i] = 3;
        }

    }    
    cout << coast.back() << endl;
    
    for (int i = n; i > 1;){
        switch (res[i]) {
        case 1:
            cout << "-1";
            i--;
            break;
        case 2:
            cout << "/2";
            i /= 2;
            break;
        case 3:
            cout << "/3";
            i /= 3;
            break;
        default:
            break;
        }
        if (i != 1) cout << " ";
    }
    cout << endl;
	
	return 0;
}