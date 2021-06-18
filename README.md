## Chain Maker Problem
Chain Maker is a Algorithmic problem tasked with finding the goal chain from cutting and linking input chains in the most efficient manner. 
- input chains can be circular or non-circular.
- inputs of algorithm is list of entry chains which represented as `ChainSeq` object with two class attributes of `length` and `is_circular`.
#### consider the examples bellow to understand the concept better :
```
// inputs (length, is_circular)
(8,  1)
(12, 0)
(3,  1)

// output
USED CHAINS NO: 2 | CUTS NO: 2 | LINKS NO: 2 | TOTAL COST: 4
using chains below:
(3, 1)
(12, 0)
```