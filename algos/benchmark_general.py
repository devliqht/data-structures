import time
import random
import matplotlib.pyplot as plt
import numpy as np
import sys

# Increase recursion depth just in case
sys.setrecursionlimit(2000)

def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]

def selection_sort(arr):
    n = len(arr)
    for i in range(n):
        min_idx = i
        for j in range(i+1, n):
            if arr[min_idx] > arr[j]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]

def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i-1
        while j >= 0 and key < arr[j] :
            arr[j+1] = arr[j]
            j -= 1
        arr[j+1] = key

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

def bucket_sort(arr):
    if not arr: return []
    max_val = max(arr)
    size = (max_val + 1) / len(arr) 
    buckets_list = [[] for _ in range(len(arr))]
    for i in range(len(arr)):
        j = int(arr[i] / size)
        buckets_list[j].append(arr[i])
    for i in range(len(arr)):
        buckets_list[i].sort() # Using built-in to avoid massive slowdowns in pure python insertion sort for large N
    result = []
    for i in range(len(arr)):
        result.extend(buckets_list[i])
    for i in range(len(arr)):
        arr[i] = result[i]

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

def measure_time(sort_func, arr):
    start = time.time()
    sort_func(arr.copy())
    return time.time() - start

# N values from 10k to 1 million
N_values = [10000, 50000, 100000, 500000, 1000000]
MAX_VAL = 1000000 # Max integer value

times = {
    "Bubble Sort": [],
    "Selection Sort": [],
    "Insertion Sort": [],
    "Counting Sort": [],
    "Bucket Sort": [],
    "Radix Sort": []
}

# Calculate C for O(N^2) extrapolations using N=2000
test_arr = [random.randint(0, MAX_VAL) for _ in range(2000)]
t_bubble = measure_time(bubble_sort, test_arr)
t_select = measure_time(selection_sort, test_arr)
t_insert = measure_time(insertion_sort, test_arr)

c_bubble = t_bubble / (2000**2)
c_select = t_select / (2000**2)
c_insert = t_insert / (2000**2)

for n in N_values:
    arr = [random.randint(0, MAX_VAL) for _ in range(n)]
    
    # Extrapolate O(N^2)
    times["Bubble Sort"].append(c_bubble * (n**2))
    times["Selection Sort"].append(c_select * (n**2))
    times["Insertion Sort"].append(c_insert * (n**2))
    
    # Measure O(N)
    times["Counting Sort"].append(measure_time(counting_sort, arr))
    times["Bucket Sort"].append(measure_time(bucket_sort, arr))
    times["Radix Sort"].append(measure_time(radix_sort, arr))

# Plotting: X = Time, Y = N as requested
plt.figure(figsize=(12, 8))

colors = ['red', 'orange', 'yellow', 'green', 'blue', 'purple']
for (name, time_list), color in zip(times.items(), colors):
    plt.plot(time_list, N_values, marker='o', label=name, color=color, linewidth=2)

plt.xscale('log') # Log scale for time to fit O(N^2) and O(N) together
plt.xlabel('Execution Time (seconds) - Log Scale', fontsize=12)
plt.ylabel('Number of Integers (N)', fontsize=12)
plt.title('Time Series Performance: Number of Integers vs Time\n(Bubble, Selection, Insertion are mathematically extrapolated)', fontsize=14)
plt.grid(True, which="both", ls="--", alpha=0.5)
plt.legend()
plt.tight_layout()
plt.savefig('timeseries_sorting.png')

print("Benchmark complete.")
for k, v in times.items():
    print(f"{k}: {v[-1]:.4f}s for 1M items")