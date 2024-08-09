/** @file */
#pragma once
/**
 * @returns deq.back()
 * @time O(1)
 * @space O(1)
 */
T back() {
  return (empty(ri) ? le[0] : ri.back())[0];
}
