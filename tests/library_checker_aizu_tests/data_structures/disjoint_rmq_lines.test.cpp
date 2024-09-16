#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/" \
  "queue_operate_all_composite"
#include "../template.hpp"

#include "../../../library/data_structures/uncommon/disjoint_rmq.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  const ll mod = 998'244'353;
  int q;
  cin >> q;
  struct query {
    int type;
    int a, b, x;
  };
  vector<query> queries(q);
  vector<pair<ll, ll>> lines;
  for (int i = 0; i < q; i++) {
    cin >> queries[i].type;
    if (queries[i].type == 0) {
      cin >> queries[i].a >> queries[i].b;
      lines.emplace_back(
        queries[i].a, queries[i].b);
    } else if (queries[i].type == 2)
      cin >> queries[i].x;
  }
  disjoint_rmq rmq(
    lines, [](const auto& a, const auto& b) {
      // f1(x) = a.first * x + a.second
      // f2(x) = b.first * x + b.second
      // f2(f1(x)) = b.first * (a.first * x +
      // a.second) + b.second
      //           = (a.first * b.first) * x +
      //           (b.first * a.second + b.second)
      return pair(a.first * b.first % mod,
        (b.first * a.second + b.second) % mod);
    });
  int le = 0, ri = 0;  // range [le, ri)
  for (const auto& curr : queries) {
    if (curr.type == 0) ri++;
    else if (curr.type == 1) le++;
    else {
      if (le == ri) cout << curr.x << '\n';
      else {
        auto [slope, y_int] = rmq.query(le, ri);
        cout << (slope * curr.x + y_int) % mod
             << '\n';
      }
    }
  }
  return 0;
}
