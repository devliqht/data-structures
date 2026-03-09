import time
import random
import sys
import gc
import matplotlib.pyplot as plt

sys.setrecursionlimit(2000000)

# --- Slow O(N^2) Sorts ---
def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        swapped = False
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
                swapped = True
        if not swapped:
            break

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

def gnome_sort(arr):
    index = 0
    n = len(arr)
    while index < n:
        if index == 0:
            index = index + 1
        if arr[index] >= arr[index - 1]:
            index = index + 1
        else:
            arr[index], arr[index - 1] = arr[index - 1], arr[index]
            index = index - 1

# --- Intermediate Sorts ---
def shell_sort(arr):
    n = len(arr)
    gap = n // 2
    while gap > 0:
        for i in range(gap, n):
            temp = arr[i]
            j = i
            while j >= gap and arr[j - gap] > temp:
                arr[j] = arr[j - gap]
                j -= gap
            arr[j] = temp
        gap //= 2

def get_next_gap(gap):
    gap = (gap * 10) // 13
    if gap < 1: return 1
    return gap

def comb_sort(arr):
    n = len(arr)
    gap = n
    swapped = True
    while gap != 1 or swapped == True:
        gap = get_next_gap(gap)
        swapped = False
        for i in range(0, n - gap):
            if arr[i] > arr[i + gap]:
                arr[i], arr[i + gap] = arr[i + gap], arr[i]
                swapped = True

def heapify(arr, n, i):
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2
    if l < n and arr[i] < arr[l]: largest = l
    if r < n and arr[largest] < arr[r]: largest = r
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)

def heap_sort(arr):
    n = len(arr)
    for i in range(n//2 - 1, -1, -1):
        heapify(arr, n, i)
    for i in range(n-1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)

# --- Fast Sorts ---
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
        pivot_idx = random.randint(low, high)
        arr[high], arr[pivot_idx] = arr[pivot_idx], arr[high]
        pivot = arr[high]
        i = low - 1
        for j in range(low, high):
            if arr[j] < pivot:
                i += 1
                arr[i], arr[j] = arr[j], arr[i]
        arr[i + 1], arr[high] = arr[high], arr[i + 1]
        pi = i + 1
        
        if pi - low < high - pi:
            quick_sort_inplace(arr, low, pi - 1)
            low = pi + 1
        else:
            quick_sort_inplace(arr, pi + 1, high)
            high = pi - 1

def quick_sort(arr):
    if arr:
        quick_sort_inplace(arr, 0, len(arr) - 1)

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

def radix_sort_base_256(arr):
    n = len(arr)
    output = [0] * n
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
    best_time = float('inf')
    for _ in range(3):
        test_arr = arr.copy()
        gc.disable()
        start = time.time()
        sort_func(test_arr)
        t = time.time() - start
        gc.enable()
        if t < best_time:
            best_time = t
    return best_time

if __name__ == "__main__":
    # We use a mix of small and medium N. O(N^2) sorts will take real time to execute here natively!
    N_values = [1000, 2000, 5000, 10000, 20000]
    MAX_VAL = 1000000
    
    sorts = {
        "Bubble Sort": bubble_sort,
        "Gnome Sort": gnome_sort,
        "Selection Sort": selection_sort,
        "Insertion Sort": insertion_sort,
        "Shell Sort": shell_sort,
        "Comb Sort": comb_sort,
        "Heap Sort": heap_sort,
        "Merge Sort": merge_sort,
        "Quick Sort": quick_sort,
        "Counting Sort": counting_sort,
        "Radix Base 2^8": radix_sort_base_256,
        "Radix Base 2^16": radix_sort_base_65536
    }
    
    times = {name: [] for name in sorts}
    
    for n in N_values:
        arr = [random.randint(0, MAX_VAL) for _ in range(n)]
        print(f"Benchmarking N={n} natively...")
        
        for name, func in sorts.items():
            # For O(N^2) sorts, Native execution for 20,000 might take ~15-30 secs each.
            t = measure_time(func, arr)
            times[name].append(t)
            print(f"  {name}: {t:.5f}s")
            
    plt.figure(figsize=(14, 10))
    # Distinct colormap for 12 lines
    cmap = plt.cm.get_cmap('tab20', len(sorts))
    colors = [cmap(i) for i in range(len(sorts))]
    
    for i, (name, time_list) in enumerate(times.items()):
        plt.plot(N_values, time_list, marker='o', label=name, color=colors[i], linewidth=2.5)
    
    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Number of Integers (N) - Log Scale', fontsize=12)
    plt.ylabel('Execution Time (seconds) - Log Scale', fontsize=12)
    plt.title('The Ultimate Sorting Showdown: 12 Algorithms natively executed (GC Disabled, Best of 3)', fontsize=16)
    plt.grid(True, which="both", ls="--", alpha=0.5)
    
    # Put legend outside the plot so it doesn't cover data
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0.)
    plt.tight_layout()
    plt.savefig('timeseries_all_sorts.png')
    print("Benchmark complete! Graph saved as timeseries_all_sorts.png")
