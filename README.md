# Prefetch Accuracy using Bloom_Filter
## Approximating accuracy of prefetcher using Bloom Filter. 

* Used Murmur hash 3 functions forked from https://github.com/PeterScott/murmur3
* Noted error when using this approach to find prefetch accuracy.
* Bloom filter is used due to its const lookup time.
* Determined false positive probability before hand.

To run, type in shell:
g++ -c  bloom.cpp murmur3.c 
g++  bloom.o murmur3.o
./a.out
