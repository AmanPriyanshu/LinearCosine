# CPP Benchmarks

This benchmark explores the raw cpp implementation across varying mantissa bit precision levels for calculating cosine similarity. The goal is to evaluate the trade-offs between computational speed and accuracy using a low-precision multiplication approach (L-Mul) compared to standard low-precision multiplication.

## Cosine 1d to 1d Performance Analysis

The table below illustrates the performance of cosine similarity calculations using different levels of mantissa precision. The L-Mul approach achieves significant time reduction while maintaining an acceptable mean squared error (_depends on your usecase_), making it a fast and efficient approximation for high-speed computations.

| Mantissa Bits | L-Mul MSE     | L-Mul Time (ns) | Mul MSE       | Mul Time (ns) | Time Reduction (%) |
|---------------|---------------|-----------------|---------------|---------------|--------------------|
| 2             | 9.45862e-06   | 507             | 4.07024e-08   | 670           | 24.3284%           |
| 3             | 1.84347e-05   | 459             | 4.07024e-08   | 597           | 23.1156%           |
| 4             | 1.84347e-05   | 383             | 4.07024e-08   | 516           | 25.7752%           |
| 5             | 4.44707e-05   | 477             | 1.93169e-06   | 629           | 24.1653%           |
| 6             | 1.78036e-05   | 477             | 6.42665e-08   | 625           | 23.68%             |
| 7             | 2.11236e-05   | 498             | 2.21875e-08   | 654           | 23.8532%           |
| 8             | 2.0259e-05    | 442             | 1.28071e-09   | 589           | 24.9576%           |
| 9             | 1.9652e-05    | 460             | 6.87609e-09   | 607           | 24.2175%           |
| 10            | 1.84467e-05   | 444             | 7.4093e-10    | 588           | 24.4898%           |
| 11            | 1.82827e-05   | 506             | 6.00017e-10   | 669           | 24.3647%           |
| 12            | 1.80075e-05   | 433             | 1.11101e-10   | 572           | 24.3007%           |
| 13            | 1.79965e-05   | 487             | 1.01831e-10   | 643           | 24.2613%           |
| 14            | 1.79698e-05   | 494             | 2.53293e-11   | 657           | 24.8097%           |
| 15            | 1.79675e-05   | 460             | 1.13981e-12   | 609           | 24.4663%           |
| 16            | 1.79675e-05   | 386             | 1.02339e-12   | 520           | 25.7692%           |
| 17            | 1.79673e-05   | 435             | 3.19744e-14   | 580           | 25.0%              |
| 18            | 1.79673e-05   | 396             | 3.19744e-14   | 532           | 25.5639%           |
| 19            | 1.79673e-05   | 402             | 1.42109e-14   | 539           | 25.4174%           |
| 20            | 1.79673e-05   | 496             | 0             | 651           | 23.8095%           |
| 21            | 1.79673e-05   | 477             | 0             | 627           | 23.9234%           |
| 22            | 1.79673e-05   | 431             | 0             | 572           | 24.6503%           |
| 23            | 1.79673e-05   | 415             | 0             | 555           | 25.2252%           |

### Summary

- **Average Time Reduction**: 24.55%
- **Average L-Mul MSE**: 1.9184e-05

The average time reduction achieved using the L-Mul approach is **24.55%**, showing that precision reduction can significantly improve computational efficiency while still providing reasonable accuracy for applications like cosine similarity. The average L-Mul MSE is approximately **1.9184e-05**, indicating an acceptable level of error for many practical applications.
