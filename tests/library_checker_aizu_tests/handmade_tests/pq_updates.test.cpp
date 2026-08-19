#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures_[l,r)/uncommon/priority_queue_of_updates.hpp"
int main() {
  for (int max_capacity = 1; max_capacity <= 50;
    max_capacity++) {
    rep(pattern, 0, 5) {
      vi ds_history;
      auto update = [&](int id) {
        ds_history.push_back(id);
      };
      auto rollback = [&](int t) { ds_history.resize(t); };
      pq_updates solver(update, rollback);
      map<pair<int, int>, int> naive_mp;
      int upd_id_counter = 0;
      rep(op, 0, 200) {
        bool do_push =
          empty(naive_mp) ||
          (rnd(0, 1) == 0 && sz(naive_mp) < max_capacity);
        if (do_push) {
          int upd_id = ++upd_id_counter;
          int pri;
          if (pattern == 0) pri = rnd(1, 5);
          else if (pattern == 1) pri = op / 5;
          else if (pattern == 2) pri = 10;
          else if (pattern == 3)
            pri = (op % 2 == 0) ? 1 : 2;
          else pri = rnd(1, 100);
          solver.push(pri, upd_id);
          naive_mp[{pri, upd_id}] = upd_id;
        } else {
          solver.pop();
          auto max_it = prev(end(naive_mp));
          naive_mp.erase(max_it);
        }
        vi active_ds = ds_history;
        sort(all(active_ds));
        vi active_naive(sz(naive_mp));
        int i = 0;
        for (auto [key, id] : naive_mp)
          active_naive[i++] = id;
        sort(all(active_naive));
        assert(active_ds == active_naive);
      }
    }
  }
  cout << "Hello World\n";
  return 0;
}
