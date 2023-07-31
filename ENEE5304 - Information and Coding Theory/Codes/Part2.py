from LimpelZiv import *
import pandas as pd

summary_output = "-----------------------\n\t \t   N\t  NB\n"
symbols = ['a', 'b', 'c', 'd']
probabilities = [0.4, 0.3, 0.2, 0.1]
locations = []
content = []
codeword = []
i = 0
Nb_avg = 0
N = 20
for i in range(5):
    lz_dict = {}
    generated_sequence = generate_sequence(symbols, probabilities, N)
    parse_sequence(generated_sequence, lz_dict)
    head_bits = math.ceil(math.log2(len(lz_dict.items())))
    codewords = encode_phrases(head_bits, lz_dict)
    encoded_sequence = ''.join([str(item) for item in codewords.values()])
    Nb = calculate_nb(head_bits, 8, len(lz_dict.items()))
    Nb_avg += Nb
    print("N = " + str(N) + "\n" + '-' * len("N = " + str(N)))
    print(
        "Generated sequence: " + generated_sequence + '\n' + "Encoded sequence: " + encoded_sequence + '\n' + '-' * len(
            "Encoded sequence: " + encoded_sequence))
    for key, value in lz_dict.items():
        locations.append(
            str(key).rjust(3) + " " + str(bin(key).replace("0b", "")).rjust(head_bits - 1, '0') + " " * 7)
        content.append(str(value).rjust(15) + " " * 8)
        codeword.append("<" + str(int(codewords[value][:len(codewords[value]) - 1], 2)) + "," + codewords[value][
            len(codewords[value]) - 1] + ">")
        data = {
            "Dictionary Location": locations,
            "Dictionary Contents": content,
            "Codeword": codeword
        }
        df = pd.DataFrame(data)
    print(df.to_string(index=False))
    print("-" * 80)
    print("# of phrases: " + str(len(lz_dict.items())))
    print("# of bits per phrase: " + str(head_bits + 8) + ' -> [' + str(head_bits) + ' + 8]')
    print("Nb: " + str(Nb) + ' -> [' + str(head_bits + 8) + ' * ' + str(len(lz_dict.items())) + ']')
    print('\n\n')
    summary_output += str(i + 1).rjust(5) + "\t" + str(N).rjust(5) + "\t" + str(Nb).rjust(5) + "\n"
    locations = []
    content = []
    codeword = []
print(summary_output)
print("Average NB = " + str(Nb_avg / 5))
