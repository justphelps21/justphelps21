import random
import itertools


def shuffle_word(word):
    word = list(word)
    random.shuffle(word)
    return ''.join(word)


def is_subset_anagram(str1, str2):
    list2 = list(str2)
    try:
        for char in str1:
            list2.remove(char)
    except ValueError:
        return False
    return True


file = open("words.txt", 'r')

words = file.read()

word_list = words.splitlines()


max_length = len(max(word_list, key=len))
word = word_list[5]
perm_of_word = list(itertools.permutations(word))
string_of_perms = []


for i in range(len(perm_of_word)):
    perm_of_word[i] = shuffle_word(perm_of_word[i])
    string_of_perms.append(perm_of_word[i])


length_input = input('Enter the range of word lengths (low,high): ')
length_tuple = eval(length_input)

min_word_length = length_tuple[0]
max_word_length = length_tuple[1]

length_words = [word for word in word_list if len(word) == max_word_length]
random_length_word = random.choice(length_words)
print(shuffle_word(random_length_word), ':')


correct_guesses = []


correct_answers = [word for word in word_list
                   if is_subset_anagram(word, random_length_word)
                   and word in word_list and len(word) <= len(random_length_word)]


while True:
    if correct_guesses == correct_answers:
        print('You guessed them all! Good job!')
        break
    guess = input('Enter a guess: ')
    if guess == 'q':
        correct_answers.sort(key=len)
        print(correct_answers)
        break
    if guess in correct_guesses:
        print('you already guessed that!')
    if guess in correct_answers and guess not in correct_guesses:
        print("Correct!")
        print()
        print(shuffle_word(random_length_word), ':')
        print()
        correct_guesses.append(guess)
        correct_guesses.sort(key=len)
        print(correct_guesses)
    else:
        print('Sorry! Try again: ')
        print()
        print(shuffle_word(random_length_word), ':')
        print()