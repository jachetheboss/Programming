class Solution:
    def maxPower(self, stations: List[int], r: int, k: int) -> int:
        left = min(stations)
        right = sum(stations) + k
        answer = -1
        while left <= right:
            mid = (left + right) // 2
            if self.check(mid, stations, r, k):
                answer = mid
                left = mid + 1
            else:
                right = mid - 1
        return answer
    def check(self, target, stations, r, k):
        newStat = stations[:]
        cur = 0
        n = len(stations)
        for i in range(min(r, len(stations))):
            cur += newStat[i]
        for i in range(n):
            if i + r < n:
                cur += newStat[i + r]
            if cur < target:
                if target - cur > k:
                    return False
                newStat[min(i + r, len(stations) - 1)] += target - cur
                k -= target - cur
                cur = target
            if i - r >= 0:
                cur -= newStat[i - r]
        return True