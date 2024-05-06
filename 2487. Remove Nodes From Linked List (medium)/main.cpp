#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvii [[maybe_unused]] = std::vector<vii>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;
using vc [[maybe_unused]] = std::vector<char>;
using vvc [[maybe_unused]] = std::vector<vc>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define F first
#define S second

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    explicit ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
    public:
    static ListNode* removeNodes(ListNode* head) {
        const auto vals = GetGoodVals(head);

        int i = 0;
        while (head && !vals.contains({head->val, i})) {
            head = head->next;
            ++i;
        }
        
        ListNode* parent = nullptr;
        auto node = head;
        while (node) {
            if (vals.contains({node->val, i})) {
                parent = node;
                node = node->next;
            } else {
                if (node->next) {
                    parent->next = node->next;
                    node = node->next;
                } else { // remove tail
                    parent->next = node->next;
                    node = node->next;
                }
            }
            ++i;
        }
        return head;
    }

    private:
    static std::set<ii> GetGoodVals(ListNode* head) {
        std::set<ii> vals;
        auto node = head;
        int i = 0;
        while (node) {
            while (!vals.empty() && vals.begin()->F < node->val)
                vals.erase(vals.begin());
            vals.emplace(node->val, i);
            node = node->next;
            ++i;
        }
        return vals;
    }
};

[[maybe_unused]] void TestSolution() {
    /*{
        const auto start_t = std::chrono::high_resolution_clock::now();

        vi people{1,2};
        const auto a_out = Solution::numRescueBoats(people, 3);
        assert(a_out == 1);

        const auto end_t = std::chrono::high_resolution_clock::now();
        const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
        std::cerr << total_t << " ms"sv << std::endl;
    }*/
    std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
    TestSolution();
#endif
    return 0;
}
