import time
import random
import gc
import matplotlib.pyplot as plt

def radix_sort_base_2(arr):
    n = len(arr)
    output = [0] * n
    for shift in range(32): # 32 passes
        count = [0] * 2
        for i in range(n):
            count[(arr[i] >> shift) & 1] += 1
        count[1] += count[0]
        for i in range(n - 1, -1, -1):
            val = (arr[i] >> shift) & 1
            output[count[val] - 1] = arr[i]
            count[val] -= 1
        arr[:] = output

def radix_sort_base_8(arr):
    n = len(arr)
    output = [0] * n
    for shift in range(0, 33, 3): # 11 passes
        count = [0] * 8
        for i in range(n):
            count[(arr[i] >> shift) & 7] += 1
        for i in range(1, 8):
            count[i] += count[i - 1]
        for i in range(n - 1, -1, -1):
            val = (arr[i] >> shift) & 7
            output[count[val] - 1] = arr[i]
            count[val] -= 1
        arr[:] = output

def radix_sort_base_10(arr):
    n = len(arr)
    output = [0] * n
    if not arr: return
    max_val = max(arr)
    exp = 1
    # Division by 10 per pass
    while max_val // exp > 0:
        count = [0] * 10
        for i in range(n):
            index = arr[i] // exp
            count[index % 10] += 1
        for i in range(1, 10):
            count[i] += count[i - 1]
        for i in range(n - 1, -1, -1):
            index = arr[i] // exp
            output[count[index % 10] - 1] = arr[i]
            count[index % 10] -= 1
        arr[:] = output
        exp *= 10

def radix_sort_base_16(arr):
    n = len(arr)
    output = [0] * n
    for shift in range(0, 32, 4): # 8 passes
        count = [0] * 16
        for i in range(n):
            count[(arr[i] >> shift) & 15] += 1
        for i in range(1, 16):
            count[i] += count[i - 1]
        for i in range(n - 1, -1, -1):
            val = (arr[i] >> shift) & 15
            output[count[val] - 1] = arr[i]
            count[val] -= 1
        arr[:] = output

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

def measure_smooth_time(sort_func, arr, trials=5):
    best_time = float('inf')
    for _ in range(trials):
        test_arr = arr.copy()
        
        # Disable Garbage Collection to prevent OS spikes during the run
        gc.disable()
        start = time.time()
        
        sort_func(test_arr)
        
        t = time.time() - start
        gc.enable() # Re-enable after measuring
        
        if t < best_time:
            best_time = t
    return best_time

if __name__ == "__main__":
    N_values = [1000, 5000, 10000, 50000, 100000, 500000]
    MAX_VAL = 10000000
    
    sorts = {
        "Base 2 (32 passes)": radix_sort_base_2,
        "Base 8 (11 passes)": radix_sort_base_8,
        "Base 10 (Math, ~8 passes)": radix_sort_base_10,
        "Base 16 (8 passes)": radix_sort_base_16,
        "Base 2^8 (256, 4 passes)": radix_sort_base_256,
        "Base 2^16 (65536, 2 passes)": radix_sort_base_65536
    }

    times = {name: [] for name in sorts}
    
    for n in N_values:
        arr = [random.randint(0, MAX_VAL) for _ in range(n)]
        print(f"Benchmarking N={n} (3 trials, GC Disabled)...")
        # Reduced to 3 trials so you don't have to wait to see the plot
        for name, func in sorts.items():
            t = measure_smooth_time(func, arr, trials=3)
            times[name].append(t)
            print(f"  {name}: {t:.5f}s")
        
    plt.figure(figsize=(12, 8))
    
    colors = ['#1f77b4', '#ff7f0e', '#d62728', '#2ca02c', '#9467bd', '#e377c2']
    
    for (name, time_list), color in zip(times.items(), colors):
        plt.plot(N_values, time_list, marker='o', label=name, color=color, linewidth=2.5)
    
    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Number of Integers (N) - Log Scale', fontsize=12)
    plt.ylabel('Best Execution Time (seconds) - Log Scale', fontsize=12)
    plt.title('Radix Showdown: Small Bases and Math vs Large Bitwise Bases\n(Garbage Collector Disabled, Best of 3 Trials)', fontsize=14)
    plt.grid(True, which="both", ls="--", alpha=0.5)
    
    plt.legend()
    plt.tight_layout()
    plt.savefig('timeseries_radix_smooth.png')
    print("Benchmark complete! Graph saved as timeseries_radix_smooth.png")
