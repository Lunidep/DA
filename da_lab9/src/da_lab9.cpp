/*
Попов Илья Павлович
M8O-306Б-20
Bариант 4: Поиск кратчайшего пути между парой вершин алгоритмом Дейкстры

Задан взвешенный неориентированный граф, состоящий из n вершин и m ребер. 
Вершины пронумерованы целыми числами от 1 до n. Необходимо найти длину кратчайшего пути из вершины с номером start 
в вершину с номером finish при помощи алгоритма Дейкстры. Длина пути равна сумме весов ребер на этом пути. 
Граф не содержит петель и кратных ребер.
*/

#include <iostream>
#include <queue>
#include <vector>

using ll = long long;
using namespace std;
#define endl '\n';

const int INF = 1e9 + 7;
const ll LINF = 1e18 + 14;

struct Edge {
    int to;
    ll cost;

    Edge(int toParam, ll costParam) : to(toParam), cost(costParam) {}
    
    friend bool operator>(const Edge &d1, const Edge &d2) {
        return d1.cost > d2.cost;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    int n, m, s, f;
    cin >> n >> m >> s >> f;
    s--; f--;

    using Graph = vector<vector<Edge>>;
    Graph graph(n);
    for (int i = 0; i < m; i ++){
        int from, to, cost;
        cin >> from >> to >> cost;
        from--; to--;
        graph[from].push_back(Edge{to, cost});
        graph[to].push_back(Edge{from, cost});
    }

    vector<ll> dist(n, LINF);
    dist[s] = 0;
    vector<bool> used(n, false);

    priority_queue<Edge, vector<Edge>, greater<Edge>> prior;
    prior.push(Edge(s, 0));

    while(!prior.empty()){
        int minDistVert = prior.top().to;
        prior.pop();

        if(used[minDistVert]){
            continue;
        }

        if(minDistVert == LINF){
            break;
        }        

        used[minDistVert] = true;

        for (auto [to, cost]: graph[minDistVert]){
            ll newDist = cost + dist[minDistVert];

            if(dist[to] > newDist){
                dist[to] = newDist;
                prior.push(Edge(to, newDist));
            }
        }

    }

    (dist[f] != LINF ? cout << dist[f] : cout << "No solution");
    cout << endl;
}