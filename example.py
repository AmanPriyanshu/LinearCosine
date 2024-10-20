import numpy as np
import matplotlib.pyplot as plt
from linear_cosine import cosine_similarity
import time
import random
from tqdm import tqdm

def generate_random_vector(size):
    return [random.uniform(-10, 10) for _ in range(size)]

def run_comparison(vector_size, mantissa_bits, n=10):
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
    plt.colorbar(label='Time (seconds)')
    plt.title(title)
    plt.xlabel('Vector Size')
    plt.ylabel('Mantissa Bits')
    
    # Set tick labels
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

    create_heatmap(lmul_times, 'L-mul Method Time', vector_sizes, mantissa_bits)
    plt.savefig('./images/lmul_heatmap.png')
    plt.close()

    create_heatmap(standard_times, 'Standard Method Time', vector_sizes, mantissa_bits)
    plt.savefig('./images/standard_heatmap.png')
    plt.close()

    # Create a heatmap of the time difference (L-mul - Standard)
    time_diff = lmul_times - standard_times
    create_heatmap(time_diff, 'Time Difference (L-mul - Standard)', vector_sizes, mantissa_bits)
    plt.savefig('./images/time_difference_heatmap.png')
    plt.close()

    print("Heatmaps have been saved as 'lmul_heatmap.png', 'standard_heatmap.png', and 'time_difference_heatmap.png'")