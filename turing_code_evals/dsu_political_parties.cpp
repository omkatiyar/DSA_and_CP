#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <numeric>
#include <queue>

using namespace std;

// Some probably useful aliases
using t_iii = std::tuple<int, int, int>;
using DisjointSet = std::vector<t_iii>;

class DSU {
public:
    DSU(int n) : parent(n), size(n, 1), party(n, "unaffiliated") {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int a) {
        if (parent[a] != a) {
            parent[a] = find(parent[a]);
        }
        return parent[a];
    }

    void unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA != rootB) {
            if (size[rootA] < size[rootB]) {
                std::swap(rootA, rootB);
            }
            parent[rootB] = rootA;
            size[rootA] += size[rootB];
            // Merge party affiliations
            if (party[rootA] == "unaffiliated" && party[rootB] != "unaffiliated") {
                party[rootA] = party[rootB];
            } else if (party[rootA] != "unaffiliated" && party[rootB] != "unaffiliated") {
                if (party[rootA] != party[rootB]) {
                    party[rootA] = "unaffiliated";  // Conflict in party affiliation
                }
            }
        }
    }

    void changeParty(int a, const std::string &new_party) {
        int rootA = find(a);
        updateParty(rootA, new_party);
    }

    std::unordered_map<std::string, int> countPartyMembers(int n_members) {
        std::unordered_map<std::string, int> partyCount;
        for (int i = 1; i <= n_members; ++i) {
            int root = find(i);
            partyCount[party[root]] += 1;
        }
        return partyCount;
    }

    void setInitialParty(int member, const std::string &party_name) {
        int root = find(member);
        party[root] = party_name;
    }

private:
    std::vector<int> parent;
    std::vector<int> size;
    std::vector<std::string> party;

    void updateParty(int root, const std::string &new_party) {
        std::queue<int> q;
        q.push(root);
        std::unordered_map<int, bool> visited;
        visited[root] = true;
        party[root] = new_party;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int i = 1; i < parent.size(); ++i) { // Start from 1 to handle 1-based indexing
                if (find(i) == node && !visited[i]) {
                    party[i] = new_party;
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }
};

int main() {
    int n_testcases{};
    std::cin >> n_testcases;

    for (int t = 0; t < n_testcases; ++t) {
        int n_members{}, n_parties{}, n_cmd{};
        std::cin >> n_members >> n_parties >> n_cmd;

        std::vector<std::string> partyNames(n_parties);
        for (int i = 0; i < n_parties; ++i) {
            std::cin >> partyNames[i];
        }

        DSU dsu(n_members + 1); // +1 to handle 1-based indexing

        // Set initial party assignments
        for (int i = 1; i <= n_parties; ++i) {
            dsu.setInitialParty(i, partyNames[i - 1]);
        }

        for (int i = 0; i < n_cmd; ++i) {
            std::string cmd;
            std::cin >> cmd;
            if (cmd == "j") {
                int mem_a, mem_b;
                std::cin >> mem_a >> mem_b;
                dsu.unite(mem_a, mem_b);
            } else if (cmd == "c") {
                int mem_a;
                std::string new_party;
                std::cin >> mem_a >> new_party;
                dsu.changeParty(mem_a, new_party);
            }
        }

        auto partyCount = dsu.countPartyMembers(n_members);

        std::string largest_party = "unaffiliated";
        int largest_count = 0;

        for (const auto &p : partyNames) {
            if (partyCount[p] > largest_count) {
                largest_party = p;
                largest_count = partyCount[p];
            }
        }

        if (partyCount["unaffiliated"] > largest_count) {
            largest_party = "unaffiliated";
            largest_count = partyCount["unaffiliated"];
        }

        std::cout << "Community #" << (t + 1) << ": " << largest_party << " " << largest_count << std::endl;
    }

    return 0;
}
