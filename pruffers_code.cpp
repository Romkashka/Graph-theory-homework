#include <iostream>
#include <set>
#include <vector>

using namespace std;

set<int> leaves;
vector<int> edges[50];
int x, y, w, n = 1;

int main() {
    freopen("span_tree.in", "r" , stdin);
    freopen("pruffers_code.out", "w", stdout);

    while (cin >> x >> y >> w) {
        n++;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) {
        if (edges[i].size() == 1) {
            leaves.insert(i);
        }
    }
    for (int i = 1; i <= n-2; i++) {
        int current = *leaves.begin();
        leaves.erase(current);
        int parent = edges[current][0];
        cout << parent << ", ";
        for (auto j = edges[parent].begin(); j != edges[parent].end(); j++) {
            if (current == *j) {
                edges[parent].erase(j);
                break;
            }
        }
        if (edges[parent].size() == 1) {
            leaves.insert(parent);
        }
    }
}