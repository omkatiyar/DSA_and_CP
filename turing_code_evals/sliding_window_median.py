# ideal_completion.py

from heapq import heappop, heappush, heappushpop
from typing import List

# Custom pairwise implementation for Python versions < 3.10
def pairwise(iterable):
    it = iter(iterable)
    a = next(it)
    for b in it:
        yield a, b

# Function to find the median in a sliding window of size k
def medianSlidingWindow(nums: List[int], k: int) -> List[float]:
    if k == 1:
        return nums
    if k == 2:
        return [(p + q) / 2 for p, q in pairwise(nums)]
    
    kodd = k % 2  # Check if window size is odd
    ref = sorted(nums[:k])
    hl = [-x for x in ref[:k//2]]  # Max heap (negated values)
    hl.reverse()
    hr = ref[k//2:]  # Min heap
    
    out = [hr[0]] if kodd else [(hr[0] - hl[0]) / 2]
    
    hrd = []  # Track deletions in right heap
    hld = []  # Track deletions in left heap

    def cleanr():
        while hrd and hrd[0] == hr[0]:
            heappop(hrd)
            heappop(hr)
    
    def cleanl():
        while hld and hld[0] == hl[0]:
            heappop(hld)
            heappop(hl)

    for idx, x in enumerate(nums[k:]):
        y = nums[idx]  # Element leaving the window
        mid = hr[0]  # Current median
        
        if y >= mid:
            if x < mid:
                x = -heappushpop(hl, -x)  # Balance heaps
                cleanl()
            heappush(hr, x)
            heappush(hrd, y)
            cleanr()
        else:
            if x >= mid:
                x = heappushpop(hr, x)
                cleanr()
            heappush(hl, -x)
            heappush(hld, -y)
            cleanl()
        
        # Append the median to the result list
        out.append(hr[0] if kodd else (hr[0] - hl[0]) / 2)
    
    return out
