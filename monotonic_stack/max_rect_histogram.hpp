/**
 * @code{.cpp}
       vector<ll> a;
       vi le = mono_st(a, less()); // greater(), less_equal(), greater_equal()
 * @endcode
 * @param a array
 * @param cmp transitive compare operator
 * @returns vector le where le[i] = max index such that: le[i] < i and
 *          cmp(a[le[i]], a[i]). If no index exists, le[i] = -1
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T, class F> vector<int> mono_st(const vector<T>& a, F cmp) {
  vector<int> le((int)size(a));
  for (int i = 0; i < ((int)size(a)); i++)
    for (le[i] = i - 1; le[i] >= 0 && !cmp(a[le[i]], a[i]);) le[i] = le[le[i]];
  return le;
}
/**
 * @code{.cpp}
       vector<ll> a;
       auto le = mono_st(a, less()), ri = mono_range(le); // greater(), less_equal(), greater_equal()
 * @endcode
 * @param le monotonic stack array of a
 * @returns vector ri where ri[i] = min index such that: i < ri[i] and
 *          !cmp(a[i], a[ri[i]]). If no index exists, ri[i] = n
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
vector<int> mono_range(const vector<int>& le) {
  vector<int> ri((int)size(le), (int)size(le));
  for (int i = 0; i < ((int)size(le)); i++)
    for (int j = i - 1; j != le[i]; j = le[j]) ri[j] = i;
  return ri;
}
/**
 * @param a contains positive integers
 * @returns largest integer x such that there exists a subarray a[le,ri)
 * with: (ri-le) * min(a[le,ri)) == x
 * @time O(n)
 * @space besides O(n) param `a`, O(n) extra space is allocated temporarily
 */
int64_t max_rect_histogram(const vector<int>& a) {
  vector<int> le(mono_st(a, less())), ri(mono_range(le));
  int64_t max_area = 0;
  for (int i = 0; i < ((int)size(a)); i++)
    max_area = max(max_area, int64_t(a[i]) * (ri[i] - le[i] - 1));
  return max_area;
}
