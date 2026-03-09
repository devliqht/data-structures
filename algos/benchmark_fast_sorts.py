import time
import random
import matplotlib.pyplot as plt
import sys

# Increase recursion depth for Quick Sort
sys.setrecursionlimit(2000000)

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

def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        L = arr[:mid]
        R = arr[mid:]

        merge_sort(L)
        merge_sort(R)

        i = j = k = 0
        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1

        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1

        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1

def quick_sort_inplace(arr, low, high):
    while low < high:
        pi = partition(arr, low, high)
        # Tail call optimization
        if pi - low < high - pi:
            quick_sort_inplace(arr, low, pi - 1)
            low = pi + 1
        else:
            quick_sort_inplace(arr, pi + 1, high)
            high = pi - 1

def partition(arr, low, high):
    pivot_idx = random.randint(low, high)
    arr[high], arr[pivot_idx] = arr[pivot_idx], arr[high]
    pivot = arr[high]
    i = low - 1
    for j in range(low, high):
        if arr[j] < pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1

def quick_sort(arr):
    if arr:
        quick_sort_inplace(arr, 0, len(arr) - 1)

def radix_sort_base_256(arr):
    n = len(arr)
    output = [0] * n
    # Four passes for 32-bit integers (8 bits each pass)
    for shift in (0, 8, 16, 24):
        count = [0] * 256
        for i in range(n):
            count[(arr[i] >> shift) & 0xFF] += 1
        for i in range(1, 256):
            count[i] += count[i - 1]
        for i in range(n - 1, -1, -1):
            val = (arr[i] >> shift) & 0xFF
            output[count[val] - 1] = arr[i]
            count[val] -= 1
        arr[:] = output

def radix_sort_base_65536(arr):
    n = len(arr)
    output = [0] * n
    # Two passes for 32-bit integers (16 bits each pass)
    for shift in (0, 16):
        count = [0] * 65536
        for i in range(n):
            count[(arr[i] >> shift) & 0xFFFF] += 1
        for i in range(1, 65536):
            count[i] += count[i - 1]
        for i in range(n - 1, -1, -1):
            val = (arr[i] >> shift) & 0xFFFF
            output[count[val] - 1] = arr[i]
            count[val] -= 1
        arr[:] = output

def measure_time(sort_func, arr):
    start = time.time()
    sort_func(arr.copy())
    return time.time() - start

if __name__ == "__main__":
    N_values = [10000, 50000, 100000, 200000, 500000]
    MAX_VAL = 10000000 # 10 million range
    
    times = {
        "Counting Sort": [], 
        "Merge Sort": [], 
        "Quick Sort": [], 
        "Radix Base 2^8": [], 
        "Radix Base 2^16": []
    }
    
    for n in N_values:
        arr = [random.randint(0, MAX_VAL) for _ in range(n)]
        print(f"Benchmarking N={n}...")
        
        times["Counting Sort"].append(measure_time(counting_sort, arr))
        times["Merge Sort"].append(measure_time(merge_sort, arr))
        times["Quick Sort"].append(measure_time(quick_sort, arr))
        times["Radix Base 2^8"].append(measure_time(radix_sort_base_256, arr))
        times["Radix Base 2^16"].append(measure_time(radix_sort_base_65536, arr))
    
    plt.figure(figsize=(12, 8))
    colors = ['red', 'blue', 'green', 'purple', 'orange']
    
    for (name, time_list), color in zip(times.items(), colors):
        plt.plot(N_values, time_list, marker='o', label=name, color=color, linewidth=2)
    
    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Number of Integers (N) - Log Scale', fontsize=12)
    plt.ylabel('Execution Time (seconds) - Log Scale', fontsize=12)
    plt.title('Advanced Sort Benchmark: Counting vs Merge vs Quick vs Radix\n(Random Integers 0-10,000,000)', fontsize=14)
    plt.grid(True, which="both", ls="--", alpha=0.5)
    plt.legend()
    plt.tight_layout()
    plt.savefig('timeseries_fast_sorts.png')
    print("Benchmark complete! Graph saved as timeseries_fast_sorts.png")
