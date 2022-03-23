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
int number, edge_number, components, components_init, visited[50];

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

bool is_connected(int erased) {
    for (int i = 1; i < number; i++) {
        visited[i] = -1;
    }
    components = 0;
    for (int i = 1; i < number; i++) {
        if (i != erased && visited[i] == -1) {
            bfs(i, components);
            components++;
        }
    }
    cerr << "components: " << components << endl;
    return components <= components_init;
}

void print(int i) {
    cout << get_name[vertex_name[i].first] << " " << get_name[vertex_name[i].second] << endl;
}

int main() {
    freopen("graph.in", "r", stdin);
    freopen("joints.out", "w", stdout);
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
    cerr << components_init << endl;
    int a, b;
    for (auto current: all) {
        set<int> cpy = vertex_list[current];
        vertex_list[current].clear();
        for (auto i: cpy) {
            vertex_list[i].erase(current);
        }
        cerr << get_name[current] << " ";
        if (!is_connected(current)) {
            result.insert(current);
        }
        for (auto i: cpy) {
            vertex_list[i].insert(current);
        }
        vertex_list[current] = cpy;
    }

    for (auto i: result) {
        cout << get_name[i] << endl;
    }
}