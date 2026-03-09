import time
import random
import matplotlib.pyplot as plt

def counting_sort_radix(arr, exp):
    n = len(arr)
    output = [0] * n
    count = [0] * 10
    for i in range(n):
        index = arr[i] // exp
        count[index % 10] += 1
    for i in range(1, 10):
        count[i] += count[i - 1]
    i = n - 1
    while i >= 0:
        index = arr[i] // exp
        output[count[index % 10] - 1] = arr[i]
        count[index % 10] -= 1
        i -= 1
    for i in range(n):
        arr[i] = output[i]

def radix_sort(arr):
    if not arr: return []
    max1 = max(arr)
    exp = 1
    while max1 // exp > 0:
        counting_sort_radix(arr, exp)
        exp *= 10

def counting_sort(arr):
    if not arr: return []
    max_val = max(arr)
    m = max_val + 1
    count = [0] * m
    for a in arr:
        count[a] += 1
    i = 0
    for a in range(m):
        for c in range(count[a]):
            arr[i] = a
            i += 1
    return arr

# Testing large range difference
small_range_arr = [random.randint(0, 10**5) for _ in range(100000)]
large_range_arr = [random.randint(0, 10**8) for _ in range(100000)]

start = time.time()
radix_sort(large_range_arr.copy())
radix_time_large = time.time() - start

try:
    start = time.time()
    counting_sort(large_range_arr.copy())
    counting_time_large = time.time() - start
except MemoryError:
    counting_time_large = "Memory Error"
except Exception as e:
    counting_time_large = f"Error: {e}"

print(f"Radix sort time on 10^8 range: {radix_time_large}s")
print(f"Counting sort time on 10^8 range: {counting_time_large}s")