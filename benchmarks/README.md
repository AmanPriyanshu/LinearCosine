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

## Cosine 1d to 2d Performance Analysis

The table below illustrates the performance of different mantissa precision levels when using L-Mul and standard multiplication approaches for cosine similarity. The L-Mul method shows consistent time reductions while maintaining acceptable levels of mean squared error (MSE).

| Mantissa Bits | L-Mul MSE     | L-Mul Time (ns) | Mul MSE       | Mul Time (ns) | Time Reduction (%) |
|---------------|---------------|-----------------|---------------|---------------|--------------------|
| 2             | 4.67427e-05   | 1676            | 4.55376e-07   | 2017          | 16.9063%           |
| 3             | 7.48827e-05   | 1677            | 4.55376e-07   | 2016          | 16.8155%           |
| 4             | 7.48827e-05   | 1710            | 4.55376e-07   | 2091          | 18.2209%           |
| 5             | 9.02946e-05   | 1773            | 6.61553e-07   | 2165          | 18.1062%           |
| 6             | 7.6781e-05    | 1794            | 8.51294e-08   | 2200          | 18.4545%           |
| 7             | 7.59022e-05   | 1748            | 2.00377e-08   | 2134          | 18.0881%           |
| 8             | 7.49402e-05   | 1760            | 2.28993e-09   | 2148          | 18.0633%           |
| 9             | 7.32966e-05   | 1730            | 2.9637e-09    | 2116          | 18.242%            |
| 10            | 7.24353e-05   | 1775            | 5.58836e-10   | 2162          | 17.9001%           |
| 11            | 7.19966e-05   | 1721            | 2.21817e-10   | 2093          | 17.7735%           |
| 12            | 7.17846e-05   | 1739            | 4.44593e-11   | 2122          | 18.049%            |
| 13            | 7.14999e-05   | 1641            | 3.42347e-11   | 2008          | 18.2769%           |
| 14            | 7.1498e-05    | 1708            | 8.72289e-12   | 2083          | 18.0029%           |
| 15            | 7.15258e-05   | 1610            | 3.84912e-13   | 1972          | 18.357%            |
| 16            | 7.15262e-05   | 1661            | 3.46476e-13   | 2035          | 18.3784%           |
| 17            | 7.15261e-05   | 1663            | 1.53951e-14   | 2034          | 18.2399%           |
| 18            | 7.15261e-05   | 1646            | 1.53951e-14   | 2013          | 18.2315%           |
| 19            | 7.15261e-05   | 1598            | 4.73695e-15   | 1963          | 18.594%            |
| 20            | 7.15256e-05   | 1727            | 1.18424e-15   | 2110          | 18.1517%           |
| 21            | 7.15261e-05   | 1634            | 5.92119e-15   | 1997          | 18.1773%           |
| 22            | 7.15256e-05   | 1653            | 4.73695e-15   | 2023          | 18.2897%           |
| 23            | 7.15256e-05   | 1693            | 0             | 2068          | 18.1335%           |

The L-Mul approach demonstrates consistent time savings, with reductions ranging from approximately 16.8% to 18.6% as the mantissa precision increases.

## Cosine 2d to 2d Performance Analysis

The table below presents the performance metrics for different levels of mantissa precision in 2D to 2D multiplication calculations for cosine similarity. The L-Mul method consistently achieves time reductions while maintaining a manageable mean squared error (MSE), demonstrating its effectiveness for fast computations in higher-dimensional scenarios.

| Mantissa Bits | L-Mul MSE     | L-Mul Time (ns) | Mul MSE       | Mul Time (ns) | Time Reduction (%) |
|---------------|---------------|-----------------|---------------|---------------|--------------------|
| 2             | 2.95e-04      | 6048            | 2.00e-06      | 7742          | 21.88%             |
| 3             | 4.25e-04      | 6022            | 2.00e-06      | 7723          | 22.03%             |
| 4             | 4.48e-04      | 6138            | 2.00e-06      | 7931          | 22.61%             |
| 5             | 5.03e-04      | 6140            | 1.00e-06      | 7934          | 22.61%             |
| 6             | 4.74e-04      | 6341            | 0.00e+00      | 8162          | 22.31%             |
| 7             | 4.80e-04      | 6194            | 0.00e+00      | 8003          | 22.60%             |
| 8             | 4.81e-04      | 5761            | 0.00e+00      | 7482          | 23.00%             |
| 9             | 4.77e-04      | 5752            | 0.00e+00      | 7447          | 22.76%             |
| 10            | 4.74e-04      | 6243            | 0.00e+00      | 8059          | 22.53%             |
| 11            | 4.74e-04      | 6241            | 0.00e+00      | 8075          | 22.71%             |
| 12            | 4.74e-04      | 5728            | 0.00e+00      | 7447          | 23.08%             |
| 13            | 4.74e-04      | 5950            | 0.00e+00      | 7720          | 22.93%             |
| 14            | 4.74e-04      | 6217            | 0.00e+00      | 8029          | 22.57%             |
| 15            | 4.74e-04      | 5809            | 0.00e+00      | 7541          | 22.97%             |
| 16            | 4.74e-04      | 6322            | 0.00e+00      | 8163          | 22.55%             |
| 17            | 4.74e-04      | 5939            | 0.00e+00      | 7681          | 22.68%             |
| 18            | 4.74e-04      | 5900            | 0.00e+00      | 7649          | 22.87%             |
| 19            | 4.74e-04      | 5774            | 0.00e+00      | 7491          | 22.92%             |
| 20            | 4.74e-04      | 5687            | 0.00e+00      | 7397          | 23.12%             |
| 21            | 4.74e-04      | 5875            | 0.00e+00      | 7628          | 22.98%             |
| 22            | 4.74e-04      | 6026            | 0.00e+00      | 7815          | 22.89%             |
| 23            | 4.74e-04      | 5916            | 0.00e+00      | 7645          | 22.62%             |

The time reduction percentages indicate a consistent gain in time efficiency (_which may not be the same as compute efficiency but I personally can't operate on hardware_), with values ranging from approximately 21.88% to 23.12%, depending on the mantissa precision used.