n, k = map(int, input().split())
segments = [tuple(map(int, input().split())) for _ in range(n)]
segments.sort()

d = []
for i in range(1, n):
    d.append(segments[i][0] - segments[i - 1][1])

d.sort()

res = n

for dist in d:
    if k >= dist:
        k -= dist
        res -= 1
    else:
        break

print(res)
