#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#include "../../../library/data_structures/wavelet_merge/wavelet_tree_updates.hpp"
#define split split_2
#include "../../../library/data_structures/wavelet_merge/merge_sort_tree_updates.hpp"
#undef split

int main() {
	cin.tie(0)->sync_with_stdio(0);
	for (int n = 0; n <= 130; n++) {
		for (int tests = 5; tests--;) {
			int minn = get_rand<int>(-100, 100);
			int maxn = get_rand<int>(-100, 100);
			if (minn > maxn) swap(minn, maxn);
			//values in range [minn, maxn]
			vector<int> arr(n);
			generate(begin(arr), end(arr), [&]() {return get_rand<int>(minn, maxn);});
			vector<bool> active(n);
			generate(begin(active), end(active), [&]() {return get_rand<int>(0, 1);});
			merge_sort_tree_updates mstu(arr, active);
			wavelet_tree_updates wtu(arr, minn, maxn + 1, active);
			for (int operations = 50; operations--;) {
				if (operations % 4 == 0) { //rect_count query
					int le = get_rand<int>(0, n);
					int ri = get_rand<int>(0, n);
					if (le > ri) swap(le, ri);
					int x = get_rand<int>(-100, 100);
					int y = get_rand<int>(-100, 100);
					if (x > y) swap(x, y);
					int count_naive = 0;
					for (int i = le; i < ri; i++)
						count_naive += (active[i] && x <= arr[i] && arr[i] < y);
					auto curr_1 = wtu.rect_count(le, ri, x, y);
					assert(curr_1 == count_naive);
					auto curr_2 = mstu.rect_count(le, ri, x, y);
					assert(curr_2 == count_naive);
				} else if (operations % 4 == 1) { //kth_smallest query
					int le = get_rand<int>(0, n);
					int ri = get_rand<int>(0, n);
					if (le > ri) swap(le, ri);
					vector<int> sorted;
					for (int i = le; i < ri; i++)
						if (active[i]) sorted.push_back(arr[i]);
					sort(begin(sorted), end(sorted));
					for (int k = 1; k <= ssize(sorted); k++) {
						auto curr_res = wtu.kth_smallest(le, ri, k);
						assert(curr_res == sorted[k - 1]);
					}
				} else if (operations % 4 == 2) {
					int x = get_rand<int>(-100, 100);
					int y = get_rand<int>(-100, 100);
					if (x > y) swap(x, y);
					vector<int> idxs;
					for (int i = 0; i < n; i++)
						if (active[i] && x <= arr[i] && arr[i] < y)
							idxs.push_back(i);
					for (int k = 1; k <= ssize(idxs); k++) {
						auto curr_res = mstu.kth_smallest(x, y, k);
						assert(curr_res == idxs[k - 1]);
					}
				} else {//update active status
					assert(operations % 4 == 3);
					if (n == 0) continue;
					int i = get_rand<int>(0, n - 1);
					bool new_val = get_rand<int>(0, 1);
					wtu.set_active(i, new_val);
					mstu.set_active(i, new_val);
					active[i] = new_val;
				}
			}
		}
	}
	cout << "Hello World\n";
	return 0;
}
