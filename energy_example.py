import numpy as np
import matplotlib.pyplot as plt
from linear_cosine import cosine_similarity
import time
from tqdm import tqdm

def generate_random_vector(size):
    return [np.random.uniform(-10, 10) for _ in range(size)]

def run_comparison(vector_size, mantissa_bits, n=1):
    standard_time = 0.0
    for _ in range(n):
        v1 = generate_random_vector(vector_size)
        v2 = generate_random_vector(vector_size)

        start_time = time.time()
        cosine_similarity(v1, v2, mantissa_bits, use_lmul=True)
        lmul_time = time.time() - start_time

        start_time = time.time()
        cosine_similarity(v1, v2, mantissa_bits, use_lmul=False)
        standard_time += time.time() - start_time
    return lmul_time, standard_time/n

def create_heatmap(data, title, vector_sizes, mantissa_bits):
    plt.figure(figsize=(12, 8))
    plt.imshow(data, cmap='viridis', aspect='auto')
    plt.colorbar(label='CPU Time (seconds)')
    plt.title(title)
    plt.xlabel('Vector Size')
    plt.ylabel('Mantissa Bits')
    
    plt.xticks(range(0, len(vector_sizes), len(vector_sizes)//10), 
               [str(s) for s in vector_sizes[::len(vector_sizes)//10]])
    plt.yticks(range(len(mantissa_bits)), mantissa_bits)
    
    plt.tight_layout()

if __name__ == "__main__":
    vector_sizes = list(range(10, 10001, 20))
    mantissa_bits = list(range(2, 24))

    lmul_times = np.zeros((len(mantissa_bits), len(vector_sizes)))
    standard_times = np.zeros((len(mantissa_bits), len(vector_sizes)))

    for i, bits in enumerate(tqdm(mantissa_bits, desc="Mantissa bits")):
        for j, size in enumerate(tqdm(vector_sizes, desc=f"Vector sizes (mantissa {bits})", leave=False)):
            lmul_time, standard_time = run_comparison(size, bits)
            lmul_times[i, j] = lmul_time
            standard_times[i, j] = standard_time

    create_heatmap(lmul_times, 'L-mul Method CPU Time (Energy Proxy)', vector_sizes, mantissa_bits)
    plt.savefig('./images/lmul_energy_heatmap.png')
    plt.close()

    create_heatmap(standard_times, 'Standard Method CPU Time (Energy Proxy)', vector_sizes, mantissa_bits)
    plt.savefig('./images/standard_energy_heatmap.png')
    plt.close()

    # Create a heatmap of the CPU time difference (L-mul - Standard)
    time_diff = lmul_times - standard_times
    create_heatmap(time_diff, 'CPU Time Difference (L-mul - Standard)', vector_sizes, mantissa_bits)
    plt.savefig('./images/energy_difference_heatmap.png')
    plt.close()

    # Calculate and print the overall energy efficiency gain
    total_lmul_time = np.sum(lmul_times)
    total_standard_time = np.sum(standard_times)
    efficiency_gain = (total_standard_time - total_lmul_time) / total_standard_time * 100

    print(f"Overall estimated energy efficiency gain: {efficiency_gain:.2f}%")
    print("Energy efficiency heatmaps have been saved as 'lmul_energy_heatmap.png', 'standard_energy_heatmap.png', and 'energy_difference_heatmap.png'")