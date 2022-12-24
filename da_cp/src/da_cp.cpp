#include <bits/stdc++.h>

using namespace std;
using ll = long long; 

#define endl '\n';

struct coords {
    double x;
    double y;
};

inline double euclid_dist(ll u, ll v, const vector<coords>& vert) {
    coords v1 = vert[u];
    coords v2 = vert[v];
    
    return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

struct node {
    ll ind;
    double path;
    
    node(const ll _ind, const double _path) {
        ind = _ind;
        path = _path;
    }

    friend bool operator< (const node& v1, const node& v2) {
        if (v1.path != v2.path)
            return v1.path > v2.path;
        return v1.ind < v2.ind;
    }
};

double solve(const ll start, const ll finish, const vector<coords> &vert, const vector<vector<ll>> &graph) {
    vector<double> res(vert.size(), DBL_MAX);//используем вектор расстояний в том числе, как вектор посещенных вершин
    vector<double> dist(vert.size(), DBL_MAX);
    priority_queue<node> pq;

    res[start] = 0; //расстояние до стартовой вершины
    dist[start] = res[start] + euclid_dist(start, finish, vert);
    pq.push(node(start, dist[start]));
    
    while (!pq.empty()) {
        node tmp = pq.top();
        pq.pop();

        if (tmp.ind == finish)//конечная вершина
            break;

        if (tmp.path > dist[tmp.ind])
            continue;

        for (auto next : graph[tmp.ind]){//соседи рассматриваемой вершины

            if (res[next] == DBL_MAX || (res[tmp.ind] + euclid_dist(tmp.ind, next, vert)) < res[next]){
                res[next] = res[tmp.ind] + euclid_dist(tmp.ind, next, vert);
                dist[next] = res[next] + euclid_dist(next, finish, vert);

                pq.push(node(next, dist[next]));
            }
        }
    }
    return res[finish];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<coords> vert(n);
    vector<vector<ll>> graph(n);

    for (ll i = 0; i < n; ++i)
        cin >> vert[i].x >> vert[i].y;

    for (ll i = 0; i < m; ++i) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    ll q;
    cin >> q;

    while(q--) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        double ans = solve(u, v, vert, graph);
        if (ans != DBL_MAX){
            cout << fixed << setprecision(6) << ans << endl;
        }
        else{
            cout << -1 << endl;
        }
    }
    return 0;
}