# Red-Black Tree vs Binary Search Tree (BST) Implementation Project

## Differences between BST and RBT

### 1. Balancing:
- **BST:** In a standard Binary Search Tree (BST), the height of the tree depends on the order of node insertion. It can degenerate into a linked list in the worst case.
- **RBT:** Red-Black Trees (RBT) are self-balancing binary search trees. Specific rules ensure the tree remains balanced, preventing degeneration.

### 2. Coloring:
- **BST:** No notion of node color; structure relies only on the order of insertion.
- **RBT:** Each node in a Red-Black Tree is assigned a color (red or black), aiding in balancing during insertions and deletions.

### 3. Insertion and Deletion Fixup:
- **BST:** No specific operations for maintaining balance during insertions or deletions.
- **RBT:** Utilizes `rbInsertFixup` and `rbDeleteFixup` procedures to ensure the tree remains balanced.

## Impact of Red-Black Tree Rules on Tree Structure

The set of Red-Black Tree rules, including coloring and rotation operations, ensures a balanced structure, preventing excessive height growth.

## Advantages of Red-Black Trees

1. **Balanced Structure:** Guarantees a balanced structure, leading to more predictable and efficient search times.
2. **Worst-Case Height:** Limits the worst-case height to O(log n), ensuring faster operations.
3. **Dynamic Operations:** Efficient support for dynamic operations such as insertions and deletions.

## Impact of Population Data on Tree Height

|            | Population1 | Population2 | Population3 | Population4 |
|------------|--------------|--------------|--------------|--------------|
| **RBT**     | 21           | 24           | 24           | 16           |
| **BST**     | 835          | 13806        | 12204        | 65           |

Different versions of data affect the height due to the balancing mechanisms. RBT maintains balance, resulting in logarithmic heights, while BST heights can vary based on insertion order.

## Maximum Height of RBTrees

A red-black tree with internal nodes has a height at most \(2 \cdot \log_2(n + 1)\). The proof ensures the logarithmic height based on the black-height-balanced property.

## Time Complexity

### In Worst Case:

| Operation          | RBT           | BST           |
|--------------------|---------------|---------------|
| Inorder Traversal  | O(n)          | O(n)          |
| Search             | O(log n)      | O(n)          |
| Successor          | O(log n)      | O(n)          |
| Predecessor        | O(log n)      | O(n)          |
| Insert             | O(log n)      | O(n)          |
| Delete Node        | O(log n)      | O(n)          |
| Get Height         | O(log n)      | O(n)          |
| Get Maximum        | O(log n)      | O(n)          |
| Get Minimum        | O(log n)      | O(n)          |
| Get Total Nodes    | O(n)          | O(n)          |

## Brief Implementation Details

1. **Ensuring Red-Black Tree (RBT) Rules:**
   - Red-Black Tree rules are maintained through careful handling during insertions and deletions.
   - The `rbInsertFixup` function corrects the tree to satisfy red-black properties after standard BST insertion.
   - Deletion involves the `rbDeleteFixup` function to handle cases and ensure balance.

2. **Handling Different Cases in BST Deletion:**
   - The `deleteNode` function in BST handles different cases:
     - No or one child: Simple removal and adjustment of parent's pointer.
     - Two children: Finds successor, replaces node's value, and recursively deletes the successor.
   - The `transplant` function replaces one subtree with another to maintain tree structure.

In summary, both operations are designed to handle specific scenarios, ensuring adherence to the respective set of properties (red-black or binary search tree).
