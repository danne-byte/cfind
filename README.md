# cfind #

Finds content in datasources from a specified input. A more advanced find.

## General diff alorithm ##

1. Sort, all files from input and target are sorted depending on file sizes.

2. Analyze, files are compared first on size, then on content only if the content is identical will a match be marked.

3. Print, the results is printed to the user.


## v0.2.0 - feature chunked read ##

Does not read whole file for large files instead reads the file in chunks that are hashed to create a checksum which is compared.

- Chunk size can be configured with setting **--chunk-size=512M**
- Default is 512 Megabytes.

To diff a large file the file is split into chunks by using the configured chunk size.

- A large file is a file that is bigger in size than chunk size.

**Algorithm**

1. If file size is greater than chunk size use chunked diff method.
2. Read chunk size bytes from the beginning of a file.
3. Create hash from chunk.
4. Compare hashes from other files of same size to compare.
5. If they dont diff repeat step 2.
6. If all hashes dont match they are equal

