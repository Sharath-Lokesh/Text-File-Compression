# Text File compression
This project presents a C++ implementation of a file compression algorithm. The core compression technique employed is Huffman coding.

### Huffman coding
Huffman coding is a lossless data compression method that assigns variable-length codes to input symbols based on their frequency of occurrence. By allocating shorter codes to more frequent symbols and longer codes to less frequent ones, it achieves efficient data representation. The algorithm constructs a Huffman tree through iterative merging of nodes with the lowest probabilities. This tree is subsequently used to encode the input data. Huffman coding is recognized for its optimal compression ratio given the input symbol frequencies.