from collections import defaultdict
from heapq import heappop, heappush
from typing import List

class UnionFind:
    def __init__(self, size):
        self.parent = list(range(size))
        self.rank = [1] * size

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        rootX = self.find(x)
        rootY = self.find(y)
        
        if rootX != rootY:
            if self.rank[rootX] > self.rank[rootY]:
                self.parent[rootY] = rootX
            elif self.rank[rootX] < self.rank[rootY]:
                self.parent[rootX] = rootY
            else:
                self.parent[rootY] = rootX
                self.rank[rootX] += 1

def shortestDistanceAfterQueries(n: int, queries: List[List[int]]) -> List[int]:
    edges = [(1, i, i + 1) for i in range(n - 1)]  # Initial edges with weight 1
    uf = UnionFind(n)
    result = []

    def minimum_distance():
        heap = []
        for weight, u, v in edges:
            heappush(heap, (weight, u, v))
        
        min_dist = 0
        connected = 0
        seen = set()
        
        while heap and connected < n - 1:
            weight, u, v = heappop(heap)
            if uf.find(u) != uf.find(v):
                uf.union(u, v)
                min_dist += weight
                connected += 1
                seen.add((u, v))
                seen.add((v, u))
                
                if uf.find(0) == uf.find(n - 1):
                    return min_dist
        
        return min_dist if uf.find(0) == uf.find(n - 1) else -1

    for frm, to in queries:
        edges.append((1, frm, to))
        result.append(minimum_distance())

    return result
