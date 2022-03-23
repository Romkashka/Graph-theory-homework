#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

map<string, int> get_id;
map<int, string> get_name;
set<int> vertex_list[50], result, all;
set<int> edges;
map<pair<int, int>, int> vertex_id;
map<int, pair<int, int>> vertex_name;
int number, edge_number, components_init, components, visited[50];

void bfs(int start, int color) {
    queue<int> q;
    q.push(start);
    visited[start] = color;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (auto i: vertex_list[current]) {
            if (visited[i] == -1) {
                q.push(i);
                visited[i] = color;
            }
        }
    }
}

bool is_connected() {
    for (int i = 1; i < number; i++) {
        visited[i] = -1;
    }
    components = 0;
    for (int i = 1; i < number; i++) {
        if (visited[i] == -1) {
            bfs(i, components);
            components++;
        }
    }
    return components == components_init;
}

void print(int i) {
    cout << get_name[vertex_name[i].first] << " " << get_name[vertex_name[i].second] << endl;
}

int main() {
    freopen("graph.in", "r", stdin);
    freopen("bridges.out", "w", stdout);
    string x, y;
    number = 1, edge_number = 1;
    for (int i = 1; i <= 93; i++) {
        cin >> x >> y;
        if (!get_id.count(x)) {
            get_id.insert({x, number});
            get_name.insert({number, x});
            all.insert(number);
            number++;
        }
        if (!get_id.count(y)) {
            get_id.insert({y, number});
            get_name.insert({number, y});
            all.insert(number);
            number++;
        }
        vertex_id.insert({{get_id[x], get_id[y]}, edge_number});
        vertex_name.insert({edge_number, {get_id[x], get_id[y]}});
        edges.insert(edge_number);
        edge_number++;
        vertex_list[get_id[x]].insert(get_id[y]);
        vertex_list[get_id[y]].insert(get_id[x]);
    }
    components_init = 0;
    for (int i = 1; i < number; i++) {
        visited[i] = -1;
    }
    for (int i = 1; i < number; i++) {
        if (visited[i] == -1) {
            bfs(i, components_init);
            components_init++;
        }
    }
    int a, b;
    for (auto edge: edges) {
        a = (vertex_name[edge].first);
        b = vertex_name[edge].second;
        vertex_list[a].erase(b);
        vertex_list[b].erase(a);
        if (!is_connected()) {
            print(edge);
        }
        vertex_list[a].insert(b);
        vertex_list[b].insert(a);
    }

}