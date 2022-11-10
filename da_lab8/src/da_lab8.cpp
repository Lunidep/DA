/*
Попов Илья Павлович
M8O-306Б-20
Bариант 4: Откорм бычков

Бычкам дают пищевые добавки, чтобы ускорить их рост. 
Каждая добавка содержит некоторые из N действующих веществ. Соотношения количеств веществ в добавках могут отличаться.

Воздействие добавки определяется как c1a1 + c2a2 +· · ·+cNaN, где ai — количество i-го вещества в добавке, ci – неизвестный коэффициент, 
связанный с веществом и не зависящий от добавки. Чтобы найти неизвестные коэффициенты ci, Биолог может измерить воздействие любой добавки, 
использовав один её мешок. Известна цена мешка каждой из M ( ) различных добавок. Нужно помочь Биологу подобрать самый дешевый наобор добавок, 
позволяющий найти коэффициенты ci. Возможно, соотношения веществ в добавках таковы, что определить коэффициенты нельзя.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define endl '\n';

const int DEFAULT_MINIMAL_PRICE = 100;
const int DEFAULT_VALUE = -1;

int main() {
    int M, N;
    cin >> M >> N;

    vector<vector<double>> mtx(M, vector<double>(N + 2)); //M строк, N + 2 - считываем также цену добавки и записываем номер считанной строки в 1-индексации
    vector<int> answer;
    
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N + 1; ++j) {
            cin >> mtx[i][j];
        }
        mtx[i][N + 1] = i + 1; //номер считанной строки
    }

    
    for (int i = 0; i < N; ++i) {
        int minimal_price = DEFAULT_MINIMAL_PRICE; //недостижимая цена
        int row = DEFAULT_VALUE; //строка с минимальной стоимостью
        int mtx_line_number = DEFAULT_VALUE; //номер считанной строки
        int price = N;
        for (int j = i; j < M; ++j) {
            if (mtx[j][i] != 0 && mtx[j][price] < minimal_price) {
                minimal_price = mtx[j][price];
                row = j;
            }
        }
        if (row == -1) {
            cout << -1 << endl;
            return 0;
        }
        mtx_line_number = mtx[row][price + 1];
        answer.push_back(mtx_line_number);
        mtx[i].swap(mtx[row]);
        for (int k = i + 1; k < M; ++k) {
            double m = mtx[k][i] / mtx[i][i];
            for (int v = i; v < N; ++v) {
                mtx[k][v] -= mtx[i][v] * m;
            }
        }
    }

    if (answer.size() == 0) {
        cout << -1 << "\n";
        return 0;
    }

    sort(answer.begin(), answer.end());
    for (int& i : answer) {
        cout << i << " ";
    } cout << endl;
    return 0;
}