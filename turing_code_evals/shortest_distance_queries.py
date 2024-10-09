# ideal_completion.py

from collections import defaultdict
from heapq import heappop, heappush
from typing import List


def shortestDistanceAfterQueries(n: int, queries: List[List[int]]) -> List[int]:
    graph = [[] for _ in range(n)]
    for u in range(n-1):
        graph[u].append((u + 1, 1))
    
    ans, min_distance = [], [*range(n)]
    for u, v in queries:
        graph[u].append((v, 1))
        heap = [(min_distance[u], u)]
        while heap:
            curr_distance, node = heappop(heap)
            if curr_distance == min_distance[node]:
                for neighbor, distance in graph[node]:
                    distance += curr_distance
                    if distance < min_distance[neighbor]:
                        heappush(heap, (distance, neighbor))
                        min_distance[neighbor] = distance
        ans.append(min_distance[-1])
    return ans


