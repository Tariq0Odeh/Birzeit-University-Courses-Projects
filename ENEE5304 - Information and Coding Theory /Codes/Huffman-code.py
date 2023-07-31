import heapq
import random

class Node:
    def __init__(self, symbol, frequency):
        self.symbol = symbol
        self.frequency = frequency
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.frequency < other.frequency

def build_huffman_tree(symbols, probabilities):
    # Step 2: Build the Huffman tree
    heap = []
    for symbol, probability in zip(symbols, probabilities):
        node = Node(symbol, probability)
        heapq.heappush(heap, node)

    while len(heap) > 1:
        node1 = heapq.heappop(heap)
        node2 = heapq.heappop(heap)
        merged_frequency = node1.frequency + node2.frequency
        merged_node = Node(None, merged_frequency)
        merged_node.left = node1
        merged_node.right = node2
        heapq.heappush(heap, merged_node)

    return heap[0]

def build_codewords(node, current_code, codewords):
    if node.symbol:
        codewords[node.symbol] = current_code
        return

    build_codewords(node.left, current_code + "0", codewords)
    build_codewords(node.right, current_code + "1", codewords)

# Step 1: Define the symbols and their respective probabilities
symbols = ['a', 'b', 'c', 'd']
probabilities = [0.4, 0.3, 0.2, 0.1]

# Step 2: Build the Huffman tree
huffman_tree = build_huffman_tree(symbols, probabilities)

# Step 3: Build the codewords dictionary
codewords = {}
build_codewords(huffman_tree, "", codewords)

# Step 4: Print the codewords
print("Huffman Codewords:")
for symbol in codewords:
    print(symbol + ": " + codewords[symbol])

# Step 5: Calculate average bits per character
average_bits_per_character = sum(probabilities[symbols.index(symbol)] * len(codewords[symbol]) for symbol in codewords)

print("Average bits per character (Huffman):", average_bits_per_character)

# Step 6: Generate 100 random symbols
random_symbols = random.choices(symbols, probabilities, k=100)
print(random_symbols)
# Step 7: Calculate the number of bits needed using ASCII code
ascii_bits = 8 * len(random_symbols)

print("Number of bits needed using ASCII code:", ascii_bits)

# Step 8: Encode the sequence using Huffman coding
encoded_sequence = ''.join(codewords[symbol] for symbol in random_symbols)

# Step 9: Calculate the size of the encoded sequence (NB)
encoded_bits = len(encoded_sequence)
encoded_bytes = (encoded_bits + 7) // 8  #The addition of 7 in the expression (encoded_bits + 7) // 8 is to ensure that any remaining bits, after dividing by 8, are properly accounted for.

print("Size of encoded sequence (NB):", encoded_bits, "bits (", encoded_bytes, "bytes)")

# Step 10: Calculate the compression ratio NB/(8*N)
compression_ratio = encoded_bits / (8 * len(random_symbols))

print("Compression ratio (NB/(8*N)):", compression_ratio)

# Step 11: Calculate the number of bits per symbol (NB/N)
bits_per_symbol = encoded_bits / len(random_symbols)

print("Number of bits per symbol (NB/N):", bits_per_symbol)
