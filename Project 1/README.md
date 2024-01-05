# QuickSort Implementation and Hybrid Algorithm - README

## QuickSort with Different Pivoting Strategies

### Implementation Overview
This repository contains an implementation of the QuickSort algorithm with three different strategies for choosing the pivot element: last element, random element, and median of three. The code includes details on the implementation, recurrence relations, and time/space complexity for each pivoting strategy.

### Experimental Results
The code was tested with various input data populations, and the execution times (in nanoseconds) were recorded. The results are summarized in Table 1.

#### Table 1: Comparison of Pivoting Strategies
| Pivoting Strategy  | Population1 | Population2 | Population3 | Population4 |
|-------------------|--------------|--------------|--------------|--------------|
| Last Element      | 528143292    | 10916078881  | 4208906752   | 20818333     |
| Random Element    | 37753584     | 32562375     | 36561208     | 39826459     |
| Median of Three   | 35503750     | 36049916     | 36851500     | 35385833     |

The experimental results align with theoretical expectations, showcasing the impact of different pivoting strategies on the performance of QuickSort.

## Hybrid Implementation of QuickSort and Insertion Sort

### Implementation Overview
In addition to the basic QuickSort implementation, this repository includes a hybrid algorithm that switches between QuickSort and Insertion Sort based on a threshold value (k). The code utilizes the same pivoting strategies as the basic QuickSort.

### Experimental Results
The hybrid algorithm was tested with varying threshold values, and the execution times (in nanoseconds) were recorded. Results are presented in Tables 2, 3, and 4 for last element, random element, and median of three pivoting strategies, respectively.

#### Table 2: Hybrid Algorithm with Last Element Pivoting
| Threshold (k) | 2          | 10         | 20         | $10^2$     | $10^3$     | $10^4$      | $10^5$      |
|---------------|------------|------------|------------|------------|------------|-------------|-------------|
| Population4    | 24541583   | 23295125   | 25555833   | 19683875   | 60794625   | 526963375   | 1034100458  |

#### Table 3: Hybrid Algorithm with Random Element Pivoting
| Threshold (k) | 2          | 10         | 20         | $10^2$     | $10^3$     | $10^4$      | $10^5$      |
|---------------|------------|------------|------------|------------|------------|-------------|-------------|
| Population4    | 32915584   | 30033000   | 21834875   | 26031917   | 71181958   | 543093667   | 1042884875  |

#### Table 4: Hybrid Algorithm with Median of Three Pivoting
| Threshold (k) | 2          | 10         | 20         | $10^2$     | $10^3$     | $10^4$      | $10^5$      |
|---------------|------------|------------|------------|------------|------------|-------------|-------------|
| Population4    | 36845375   | 27282583   | 22247875   | 18728417   | 69028583   | 523113708   | 1046404292  |

## Conclusion

The experiments demonstrate the impact of different pivoting strategies and threshold values on the performance of the QuickSort algorithm. Users can refer to these results to make informed decisions based on their specific use cases and datasets.

Feel free to explore the code and experiment with different configurations to further understand the behavior of the implemented algorithms.
