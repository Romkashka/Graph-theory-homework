#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

map<string, int> get_id;
map<int, string> get_name;
set<int> vertex_list[50], result, all;

void branch_and_bound(set<int> current, set<int> candidate) {
    while (!candidate.empty()) {
        auto vertex = candidate.begin();
        set<int> cleaned({});
        set<int> tmp({*vertex});
        set_difference(candidate.begin(), candidate.end(),
                       vertex_list[*vertex].begin(), vertex_list[*vertex].end(),
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

int main() {
    freopen("graph.in", "r", stdin);
    freopen("stable_set.out", "w", stdout);
    string x, y;
    int number = 1;
    for (int i = 1; i <= 92; i++) {
        cin >> x >> y;
        if (!get_id.count(x)) {
            get_id.insert({x, number});
            get_name.insert({number, x});
            number++;
        }
        if (!get_id.count(y)) {
            get_id.insert({y, number});
            get_name.insert({number, y});
            number++;
        }
        vertex_list[get_id[x]].insert(get_id[y]);
        vertex_list[get_id[y]].insert(get_id[x]);
    }
    for (int i = 1; i < number; i++) {
        all.insert(i);
    }
    branch_and_bound(set<int>(), all);
    for (auto i: result) {
        cout << get_name[i] << " ";
    }

}