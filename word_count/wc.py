file = open("Strings.txt", "r")

writefile = open("wc.txt", "a")

wordcount = {}

for word in file.read().split():
    word = word.lower()
    if word.isalpha():
        if word not in wordcount:
            wordcount[word] = 1
        else:
            wordcount[word] += 1
wordlist = []
for k, v in wordcount.items():
    wordlist.append((v, k))

wordlist = sorted(wordlist, reverse=True)

for k in wordlist:
    print(f'{k[1]:>16}: {k[0]:>5d}')

file.close()
