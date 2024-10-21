# LinearCosine
## Adding beats multiplying for lower-precision efficient cosine similarity

This repository contains a simple C++ benchmarking experiment inspired by the paper ["Addition is All You Need for Energy-efficient Language Models" by Hongyin Luo and Wei Sun (2024)](https://arxiv.org/abs/2410.00907). The experiment explores the performance of the proposed Linear-complexity Multiplication (L-Mul) algorithm compared to standard low-precision multiplication in the context of cosine similarity calculations.

## Background

Large neural networks, especially language models, consume significant computational resources and energy. The paper proposes L-Mul, an algorithm that approximates floating-point multiplication using integer addition operations. This approach aims to reduce energy consumption and potentially increase computational efficiency. While implementing the full L-Mul algorithm in neural networks was beyond the scope of my experiment, I decided to focus on optimizing cosine similarity calculations, which are crucial for many information retrieval and RAG (Retrieval-Augmented Generation) applications that are already widespread in the AI industry.

## Experiment Overview

Our benchmarking experiment implements L-Mul and standard multiplication for cosine similarity calculations with varying mantissa bit precisions. We compare the performance in terms of computation time and accuracy (measured by Mean Squared Error) for three scenarios:

1. 1D to 1D vector cosine similarity
2. 1D to 2D vector cosine similarity
3. 2D to 2D matrix cosine similarity

## Repository Structure

```
README.md
benchmark/
├── cosine_1d_to_1d.cpp
├── cosine_1d_to_2d.cpp
├── cosine_2d_to_2d.cpp
└── README.md
```

## Key Findings

- L-Mul consistently achieves time reductions compared to standard multiplication across all scenarios.
- The average time reduction for 1D to 1D cosine similarity is approximately 24.55%.
- For 1D to 2D and 2D to 2D scenarios, time reductions range from about 16.8% to 23.12%.
- L-Mul maintains acceptable levels of accuracy (measured by MSE) for most practical applications.

## Limitations and Notes

- This experiment focuses on raw C++ implementations and may not directly reflect hardware-level efficiency.
- Time efficiency gains observed here don't necessarily equate to compute or energy efficiency in real-world scenarios.
- The implementation is a simplified version of the concepts presented in the original paper and is intended for educational purposes.

## Running the Benchmarks

To run the benchmarks, compile and execute each C++ file separately. For example:

```bash
g++ -O3 -std=c++11 cosine_1d_to_1d.cpp -o cosine_1d_to_1d
./cosine_1d_to_1d
```

Repeat for the other benchmark files.

## Acknowledgments

This experiment is based on the concepts presented in:

```
@misc{luo2024additionneedenergyefficientlanguage,
      title={Addition is All You Need for Energy-efficient Language Models}, 
      author={Hongyin Luo and Wei Sun},
      year={2024},
      eprint={2410.00907},
      archivePrefix={arXiv},
      primaryClass={cs.CL},
      url={https://arxiv.org/abs/2410.00907}, 
}
```

## Disclaimer

This is an educational project and a simplified implementation of the concepts presented in the original paper. It is not intended for production use and may not accurately represent the full potential of the L-Mul algorithm in real-world scenarios.

## Future Work

Potential areas for future exploration include:
- Implementing L-Mul in actual neural network architectures
- Exploring hardware-level implementations for more accurate efficiency measurements
- Investigating the impact of L-Mul on model accuracy for various NLP tasks

Feel free to contribute, suggest improvements, or use this as a starting point for further research!
