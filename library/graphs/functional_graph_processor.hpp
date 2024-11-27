#pragma once
struct func_graph {
  struct node {
    int root_of;
    optional<pii> cyc_pos;
    vi childs;
  };
  vector<node> t;
  vector<vi> cycle;
  func_graph(const vi &a): t(sz(a)) {
    vi state(sz(a));
    rep(i, 0, sz(a)) {
      if (state[i] == 0) {
        int v = i;
        while (state[v] == 0) {
          state[v] = 1;
          v = a[v];
        }
        if (state[v] == 1) {
          cycle.emplace_back();
          while (state[v] == 1) {
            t[v].root_of = v;
            t[v].cyc_pos = {
              sz(cycle) - 1, sz(cycle.back())};
            cycle.back().push_back(v);
            state[v] = 2;
            v = a[v];
          }
        }
        int curr_root_of = t[v].root_of;
        v = i;
        while (state[v] == 1) {
          t[v].root_of = curr_root_of;
          t[a[v]].childs.push_back(v);
          state[v] = 2;
          v = a[v];
        }
      }
    }
  }
};
