#pragma once
//! @returns deq[0]
//! @time O(1)
//! @space O(1)
T front() { return (empty(le) ? ri[0] : le.back())[0]; }
