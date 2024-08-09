/**
 * @param i index
 * @returns deq[i]
 * @time O(1)
 * @space O(1)
 */
T operator[](int i) {
  return (i < (int)size(le) ? le[(int)size(le) - i - 1] : ri[i - (int)size(le)])[0];
}
