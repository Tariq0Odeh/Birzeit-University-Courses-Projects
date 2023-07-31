import math


def calculate_entropy(probability):
    return -sum([prob * math.log2(prob) for prob in probability])


probabilities = [0.4, 0.3, 0.2, 0.1]
entropy = calculate_entropy(probabilities)
entropy_str = "Entropy: " + str(entropy)
print(entropy_str)
print('-' * len(entropy_str) + '\n')
