from LimpelZiv import *

symbols = ['a', 'b', 'c', 'd']
probabilities = [0.4, 0.3, 0.2, 0.1]
summary_output = "***********************************************\n\tN\t  Nb\t\tNb/8*N\t\t\tNb/N\n"
Ns = [20, 50, 100, 200, 400, 800, 1000, 2000]
for N in Ns:
    lz_dict = {}
    generated_sequence = generate_sequence(symbols, probabilities, N)
    parse_sequence(generated_sequence, lz_dict)
    head_bits = math.ceil(math.log2(len(lz_dict.items())))
    codewords = encode_phrases(head_bits, lz_dict)
    encoded_sequence = ''.join([str(item) for item in codewords.values()])
    Nb = calculate_nb(head_bits, 8, len(lz_dict.items()))
    print("N = " + str(N) + "\n" + '-' * len("N = " + str(N)))
    print(
        "Generated sequence: " + generated_sequence + '\n' + "Encoded sequence: " + encoded_sequence + '\n' + '-' * len(
            "Encoded sequence: " + encoded_sequence))
    print("# of phrases: " + str(len(lz_dict.items())))
    print("# of bits per phrase: " + str(head_bits + 8) + ' -> [' + str(head_bits) + ' + 8]')
    print("Nb: " + str(Nb) + ' -> [' + str(head_bits + 8) + ' * ' + str(len(lz_dict.items())) + ']')
    print("-"*len("Nb: " + str(Nb) + ' -> [' + str(head_bits + 8) + ' * ' + str(len(lz_dict.items())) + ']') + '\n')
    summary_output += str(N).rjust(5) + "\t" + str(Nb).rjust(5) + "\t\t" + str(
        "{:.2f}".format(round((Nb / (N * 8)) * 100, 2))) + "%\t\t\t" + str("{:.2f}".format(Nb / N)) + "\n"
print(summary_output)
