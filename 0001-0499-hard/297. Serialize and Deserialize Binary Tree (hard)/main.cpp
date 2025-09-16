//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

/*
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using pll [[maybe_unused]] = std::pair<ll, ll>;
using pdd [[maybe_unused]] = std::pair<double, double>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vvii [[maybe_unused]] = std::vector<vii>;
using vb [[maybe_unused]] = std::vector<bool>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define F first
#define S second
#define PB push_back
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  explicit TreeNode(const int x) : val(x), left(nullptr), right(nullptr) {}
};

const int NONE = -1e5;

class Codec {
  public:

  // Encodes a tree to a single string.
  static std::string serialize(TreeNode* root) {
    std::vector<int> vals;
    std::vector<int> pars;

    std::function<void(TreeNode*,int)> traverse = [&](TreeNode* node, int parent_id) {
      const auto node_id = vals.size();
      if (node) {
        vals.push_back(node->val);
        pars.push_back(parent_id);
        traverse(node->left, node_id);
        traverse(node->right, node_id);
      } else {
        vals.push_back(NONE);
        pars.push_back(parent_id);
      }
    };
    if (root)
      traverse(root, -1);

    std::stringstream out;
    out << vals.size() << '\n';
    for (const auto v : vals) out << v << ' ';
    out << '\n';
    for (const auto p : pars) out << p << ' ';
    out << '\n';
    return out.str();
  }

  // Decodes your encoded data to tree.
  static TreeNode* deserialize(const std::string& data) {
    std::stringstream cin(data);
    int n;
    cin >> n;

    if (n == 0) return nullptr;
    
    std::vector<int> vals(n);
    for (int i = 0; i < n; ++i) cin >> vals[i];

    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
      int par_id;
      cin >> par_id;
      if (par_id >= 0 && par_id < n)
        g[par_id].push_back(i);
    }
    
    std::function<void(TreeNode*,int)> traverse = [&](TreeNode* node, int node_id) {
      // left
      if (g[node_id].size() >= 1) {
        const auto l_id = g[node_id][0];
        if (vals[l_id] != NONE) {
          node->left = new TreeNode(vals[l_id]);
          traverse(node->left, l_id);
        }
      }
      
      // right
      if (g[node_id].size() >= 2) {
        const auto r_id = g[node_id][1];
        if (vals[r_id] != NONE) {
          node->right = new TreeNode(vals[r_id]);
          traverse(node->right, r_id);
        }
      }
    };
    auto root = new TreeNode(vals[0]);
    traverse(root, 0);
    return root;
  }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

/*
[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    MedianFinder medianFinder;
    medianFinder.addNum(1);    // arr = [1]
    medianFinder.addNum(2);    // arr = [1, 2]
    assert(medianFinder.findMedian() == 1.5); // return 1.5 (i.e., (1 + 2) / 2)
    medianFinder.addNum(3);    // arr[1, 2, 3]
    assert(medianFinder.findMedian() == 2.0); // return 2.0
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}
*/

int main() {
#ifndef NDEBUG
  // TestSolution();
#endif
  return 0;
}
