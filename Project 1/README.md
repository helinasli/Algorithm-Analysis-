# Sorting Algorithms Implementation Project

## Overview

In this project, various sorting algorithms were implemented without relying on any external libraries. While external libraries were used for tasks such as reading and writing CSV files, as well as employing vectors and performing mathematical operations, the algorithms themselves were implemented without external dependencies.

## Max-Heapify Procedure

The `max_heapify` procedure maintains the max heap property by comparing a node with its children and swapping if necessary. It is recursive, with a time complexity of \(O(\log n)\), where \(n\) is the number of elements in the heap.

## Build-Max-Heap Procedure

The `build_max_heap` procedure builds a max heap from an unordered array. It starts from the last non-leaf node and calls `max_heapify` on each node. The time complexity of `build_max_heap` is \(O(n)\), where \(n\) is the number of elements in the array.

## Heapsort Procedure

The `heapsort` procedure uses the max heap property to repeatedly extract the maximum element and maintain the heap property. Its time complexity is \(O(n \log n)\).

## Priority Queue Operations

- **Max-Heap-Insert:** Inserts a new element into the max heap with a time complexity of \(O(\log n)\).
  
- **Heap-Extract-Max:** Extracts the maximum element from the max heap with a time complexity of \(O(\log n)\).

- **Heap-Increase-Key:** Increases the key of a specified element with a time complexity of \(O(\log n)\).

- **Heap-Maximum:** Returns the maximum element in the max heap with a time complexity of \(O(1)\).

## Implementation of d-ary Heap Operations

- **Height Calculation:** The height of a d-ary heap is calculated using the formula \(h = \lceil\log_d(n \cdot d - n + 1)\rceil - 1\), with a time complexity of \(O(1)\).

- **Extract-Max Implementation:** The `dary_extract_max` function extracts the maximum element from a d-ary heap with a time complexity of \(O(d \log_d n)\).

- **Insert Implementation:** The `dary_insert_element` function inserts a new element into the d-ary heap with a time complexity of \(O(\log_d n)\).

- **Increase-Key Implementation:** The `dary_increase_key` function increases the key of a specific element in the d-ary heap with a time complexity of \(O(\log_d n)\).

## Comparative Analysis

### (a) Runtime Efficiency

| Algorithm                        | Population1   | Population2   | Population3   | Population4   |
| -------------------------------- | ------------- | ------------- | ------------- | ------------- |
| **Heapsort**                     | 23,524,667 ns | 20,846,542 ns | 19,324,458 ns | 18,365,292 ns |
| **Quicksort (Last Element)**     | 528,143,292   | 10,916,078,881| 4,208,906,752 | 20,818,333    |
| **Quicksort (Random Element)**   | 37,753,584    | 32,562,375    | 36,561,208    | 39,826,459    |
| **Quicksort (Median of 3)**      | 35,503,750    | 36,049,916    | 36,851,500    | 35,385,833    |

### (b) Number of Comparisons

| Algorithm                        | Population1   | Population2   | Population3   | Population4   |
| -------------------------------- | ------------- | ------------- | ------------- | ------------- |
| **Heapsort**                     | 345,114       | 388,152       | 348,976       | 369,362       |
| **Quicksort (Last Element)**     | 9,004,989     | 95,309,721    | 72,827,050    | 234,018       |
| **Quicksort (Random Element)**   | 231,109       | 224,202       | 228,087       | 213,200       |
| **Quicksort (Median of 3)**      | 200,799       | 199,318       | 195,983       | 195,741       |

### (c) Insights into Strengths and Weaknesses

**Heapsort:**

- *Strengths:*
  - Worst-case time complexity is \(O(n \log n)\).
  - In-place sorting with space complexity \(O(1)\).

- *Weaknesses:*
  - Not stable.
  - Slower in practice compared to some other algorithms.

**Quicksort:**

- *Strengths:*
  - Better average-case time complexity (\(O(n \log n)\)).
  - In-place sorting.

- *Weaknesses:*
  - Worst-case time complexity is \(O(n^2)\).
  - Not stable.

**Scenarios:**

- **Heapsort:** Suitable for scenarios where worst-case performance is critical or there are memory constraints.

- **Quicksort:** Effective in scenarios where average-case performance is crucial, and the input data is usually random.

---

*Note: Adjust the formatting and styling as needed for your specific markdown environment.*
