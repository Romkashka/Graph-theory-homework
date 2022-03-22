#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

map<string, int> get_id;
map<int, string> get_name;
set<int> edge_list[100], result, all;
set<int> edges;
map<pair<int, int>, int> vertex_id;
map<int, pair<int, int>> vertex_name;

void branch_and_bound(set<int> current, set<int> candidate) {
    while (!candidate.empty()) {
        auto vertex = candidate.begin();
        set<int> cleaned({});
        set<int> tmp({*vertex});
        set_difference(candidate.begin(), candidate.end(),
                       edge_list[*vertex].begin(), edge_list[*vertex].end(),
                       inserter(cleaned, cleaned.begin()));
        cleaned.erase(*vertex);
        if (current.size() + cleaned.size() > result.size()) {
            current.insert(*vertex);
            branch_and_bound(current, cleaned);
            current.erase(*vertex);
        }
        candidate.erase(*vertex);
    }
    if (current.size() > result.size()) {
        result = current;
        cerr << "Solution updated! New size is " << result.size() << endl;
    }
}

void print(int i) {
    cout << get_name[vertex_name[i].first] << " " << get_name[vertex_name[i].second] << endl;
}

int main() {
    freopen("graph.in", "r", stdin);
    freopen("matching.out", "w", stdout);
    string x, y;
    int number = 1, edge_number = 1;
    for (int i = 1; i <= 92; i++) {
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
//        vertex_list[get_id[x]].insert(get_id[y]);
//        vertex_list[get_id[y]].insert(get_id[x]);
    }
    for (auto i: edges) {
        for (auto j: edges) {
            if (i != j && (vertex_name[i].first == vertex_name[j].first ||
                            vertex_name[i].first == vertex_name[j].second ||
                            vertex_name[i].second == vertex_name[j].first ||
                            vertex_name[i].second == vertex_name[j].second)) {
                edge_list[i].insert(j);
                edge_list[j].insert(i);
            }
        }
    }
    /*for (int i = 1; i < edge_number; i++) {
        cout << "Current: ";
        print(i);
        for (auto j: edge_list[i]) {
            print(j);
        }
    }*/
    branch_and_bound(set<int>(), edges);
    for (auto i: result) {
        print(i);
    }

}