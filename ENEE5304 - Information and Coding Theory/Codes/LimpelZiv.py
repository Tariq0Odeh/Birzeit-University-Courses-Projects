import math
import random


def generate_sequence(symbols, probabilities, length):
    return ''.join(random.choices(symbols, probabilities, k=length))


def parse_sequence(sequence, dictionary):
    index = 1
    phrase = ''
    for character in sequence:
        if phrase in dictionary.values() or phrase == '':
            phrase = phrase + character
            continue
        dictionary[index] = phrase
        index += 1
        phrase = character
    dictionary[index] = phrase


def encode_phrases(num_of_head_bits, dictionary):
    encoded_phrases = {}
    for present_value in dictionary.values():
        if present_value in encoded_phrases.keys():
            prev_index = list(dictionary.keys())[list(dictionary.values()).index(present_value)]
            encoded_phrases[present_value + "0"] = str(bin(prev_index).replace("0b", "")).rjust(num_of_head_bits,
                                                                                                '0') + 'x'
        elif len(present_value) == 1:
            encoded_phrases[present_value] = '0'.rjust(num_of_head_bits, '0') + present_value[0]
        else:
            for past_key, past_value in dictionary.items():
                if present_value[:len(present_value) - 1] == past_value:
                    encoded_phrases[present_value] = str(bin(past_key).replace("0b", "")).rjust(num_of_head_bits, '0') + \
                                                     present_value[len(present_value) - 1]
                    break
    return encoded_phrases


def calculate_nb(head, tail, num_of_phrases):
    return (head + tail) * num_of_phrases


def calculate_average_nb(iterations, n):
    average_nb = 0
    for i in range(iterations):
        temp_lz_dict = {}
        sequence = generate_sequence(n)
        parse_sequence(sequence, temp_lz_dict)
        head = math.ceil(math.log2(len(temp_lz_dict.items())))
        nb = calculate_nb(head, 8, len(temp_lz_dict.items()))
        average_nb += nb
    return average_nb / iterations
