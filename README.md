# Data Structures and Algorithms in C

C code for the undergraduate **Data Structures and Algorithms with C** course at Giresun University, Department of Computer Engineering. Each `ChapterNN` folder holds chapter NN of the course as small, runnable programs. Function, type, variable and macro names are the ones used in the English edition of the course (lecture notes and slides), which follows Horowitz, Sahni and Anderson-Freed; every program runs the worked example from the lecture notes, so its output can be compared directly with the notes. The expected output is at the end of each file.

Course page, lecture notes, slides and study questions: <https://sercankulcu.github.io/teaching/data-structures-and-algorithms-with-c/?lang=en>

The same programs with Turkish identifiers, for the Turkish edition of the course, are in [data-structures-and-algorithms-c](https://github.com/sercankulcu/data-structures-and-algorithms-c). The course builds on [Programming with C](https://github.com/sercankulcu/programming-with-c).

## Chapters

| Folder | Chapter | Programs |
|---|---|---|
| `Chapter01` | Introduction and Algorithm Analysis | Fraction ADT as an opaque type split into `fraction.h`/`fraction.c`/`main.c`, selection sort with the `SWAP` macro, `SWAP` vs. a pointer `swap()`, space complexity, step counting for `sum` and `rsum`, odd magic square, sort timing with `clock()`, sentinel sequential search and its timing, recursive factorial, Fibonacci and binomial coefficients |
| `Chapter02` | Arrays and Structures | Array declaration, `sizeof` and pointer arithmetic, `malloc`'d arrays, a growing dynamic array with `realloc` doubling, 2D arrays of row pointers, address and offset formulas, lower-triangular and band matrix storage, `&&` short-circuit, structures, unions and self-referential structures, array of structures, C strings and a hand-written `length`, matrix multiplication |
| `Chapter03` | Recursion, Binary Search and Backtracking | Recursive, iterative and tail-recursive factorial, iterative and recursive binary search with `COMPARE`, Towers of Hanoi, permutations by swapping, subsets by backtracking, brute-force SAT over a formula tree, n-queens |
| `Chapter04` | Linked Lists | Traversal; insertion at the front, at the back, after a node and in order; deleting the next node and by key; search; freeing; in-place inversion; concatenation; middle node and Floyd cycle detection; circular list; header node; doubly linked circular list; the available space list |
| `Chapter05` | Polynomials and Sparse Matrices | Polynomials as a coefficient array, as a shared term array (`padd` with `COMPARE`/`attach`) and as a linked list (multiplication); sparse matrices as triples: `transpose`, `fast_transpose`, `smult`; CSR matrix-vector product |
| `Chapter06` | Stacks | Stack on a global array, struct-based stack with string reversal, opaque stack type in `stack.h`/`stack.c`, linked stack, several stacks sharing one array |
| `Chapter07` | Queues | Linear array queue, circular queue (aborting and safe versions), counted circular queue, linked queue, deque, round-robin scheduling, queue from two stacks |
| `Chapter08` | Stack and Queue Applications | Maze backtracking with an explicit stack, postfix evaluation, infix-to-postfix with `isp`/`icp`, prefix evaluation, balanced brackets |
| `Chapter09` | List ADT and Generalized Lists | List ADT with an opaque type, array list, linked list, multivariate polynomial as a generalized list, generalized-list routines (copy, equality, depth, inversion), reference counting |
| `Chapter10` | Trees | Binary tree in an array and with linked nodes, recursive and stack-based traversals, level-order traversal, left-child right-sibling general tree, expression-tree evaluation, leaf printing, copy, equality and mirroring |
| `Chapter11` | Search Trees | BST insertion, search and deletion, depth (recursive and iterative), the `MAX` macro double-evaluation trap, AVL rotations and insertion, exam problems (node weight, `SWAP` between recursive calls) |
| `Chapter12` | Threaded Binary Trees | Threaded binary tree with a header node: inorder successor and predecessor, stackless traversals, insertion to the right and left, Morris inorder traversal |
| `Chapter13` | Priority Queues and Heaps | Array-based max heap and min heap, increasing and decreasing a key, bottom-up heap construction, a heap in a dynamically allocated struct |
| `Chapter14` | Hash Tables | Direct addressing, division and multiplication hashing, string hashes, open addressing with linear probing and tombstones, separate chaining, resizing with rehashing |
| `Chapter15` | Graphs | Degree from the adjacency matrix, adjacency lists, the transpose, the sequential representation, the adjacency multilist, weighted graphs, DFS, BFS, connected components, cycle detection |
| `Chapter16` | Sets and Union-Find | Parent-array union-find, weighted union, collapsing find, the Ackermann function, counting components |
| `Chapter17` | Minimum Spanning Trees | Kruskal with `qsort` and union-find, O(n²) Prim, Prim with adjacency lists and a binary min-heap |
| `Chapter18` | Shortest Paths and Activity Networks | Dijkstra with path printing, Bellman-Ford with negative-cycle detection, Floyd-Warshall, topological sort, AoE network earliest/latest times, slack and critical activities |
| `Chapter19` | Basic Sorting Algorithms | Common `SWAP` macros and a test program, selection sort, insertion sort and the sentinel version, bubble sort and the early-exit version, counting sort, Shell sort, bucket sort |
| `Chapter20` | Advanced Sorting Algorithms | Quicksort, quicksort with an explicit stack, median-of-three with a cutoff, `qsort` with `int` and struct comparators, merge sort, linked-list merge sort, heap sort, radix sort on a linked list |

## Running the examples

Every program is standard C11 and uses only the C standard library. A file `ChapterNN/name.c` is one program; a folder `ChapterNN/name/` (an interface split into `.h` and `.c` files) is one program made of all the `.c` files in it. No program reads the keyboard or leaves files behind.

```bash
cd Chapter06
gcc -std=c11 -Wall -Wextra -pedantic struct_stack.c -o struct_stack
./struct_stack

cd opaque_stack
gcc -std=c11 -Wall -Wextra -pedantic *.c -o stack
./stack
```

The timing programs in `Chapter01` and the address printout in `Chapter02/print_array.c` print different values on every run, and `Chapter19/sorting_test.c` prints the numbers of the C library's `rand()` (the expected output shown is glibc's); the comments say so.

`ci/build.sh` compiles and runs every program. GitHub Actions runs it on every push with `gcc` (warnings are errors) and with `clang` under AddressSanitizer and UndefinedBehaviorSanitizer, so a memory leak, an out-of-bounds access or undefined behaviour fails the build.

Where a slide's code uses something it does not show (a type, a helper function, a `main`), the file adds the smallest piece needed, usually from the lecture notes, and marks it with `/* not on the slides */`. Some examples keep the Turkish names and words used in the course (Ali, Ayse, "kedi"), because the output shown in the notes depends on them.

## Contact

For questions or suggestions, contact [Sercan Külcü](https://github.com/sercankulcu) or open an issue on GitHub.
