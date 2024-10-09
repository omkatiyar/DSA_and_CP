import heapq
from collections import defaultdict
from typing import List

def medianSlidingWindow(nums: List[int], k: int) -> List[float]:
    def addNum(num, max_heap, min_heap):
        if not max_heap or num <= -max_heap[0]:
            heapq.heappush(max_heap, -num)
        else:
            heapq.heappush(min_heap, num)
        balanceHeaps(max_heap, min_heap)

    def removeNum(num, max_heap, min_heap, delayed):
        delayed[num] += 1
        if num <= -max_heap[0]:
            if num == -max_heap[0]:
                prune(max_heap, delayed)
        else:
            if num == min_heap[0]:
                prune(min_heap, delayed)
        balanceHeaps(max_heap, min_heap)

    def prune(heap, delayed):
        while heap and delayed[-heap[0] if heap == max_heap else heap[0]]:
            num = -heapq.heappop(heap) if heap == max_heap else heapq.heappop(heap)
            delayed[num] -= 1

    def balanceHeaps(max_heap, min_heap):
        if len(max_heap) > len(min_heap) + 1:
            heapq.heappush(min_heap, -heapq.heappop(max_heap))
            prune(max_heap, delayed)
        elif len(min_heap) > len(max_heap):
            heapq.heappush(max_heap, -heapq.heappop(min_heap))
            prune(min_heap, delayed)

    def findMedian(max_heap, min_heap):
        if len(max_heap) > len(min_heap):
            return float(-max_heap[0])
        return (-max_heap[0] + min_heap[0]) / 2.0

    max_heap, min_heap = [], []
    delayed = defaultdict(int)
    result = []

    for i in range(len(nums)):
        addNum(nums[i], max_heap, min_heap)
        if i >= k:
            removeNum(nums[i - k], max_heap, min_heap, delayed)
        if i >= k - 1:
            result.append(findMedian(max_heap, min_heap))

    return result
