def main():
    # get text
    text = input("Text: ")

    # count word
    words = word_count(text)

    # count letter
    letters = letter_count(text)

    # count sentence
    sentences = sentence_count(text)

    # calculate the grade for the text
    grades = cal_index(words, letters, sentences)

    determine_grade(grades)


def word_count(text):
    # split text into each word and know the length of the list of words
    return len(text.split())


def letter_count(text):
    # spliting all element in the text and put it into a temporary list
    temp = list(text)
    # create a list that only include letters from the temp, ord() returns ASCII value
    sp_letter = [letter for letter in temp if ord(letter) >= 65 and ord(
        letter) <= 90 or ord(letter) >= 97 and ord(letter) <= 122]
    return len(sp_letter)


def sentence_count(text):
    # include any ./!/? into a list to count sentence
    sentences = [sentence for sentence in text if sentence ==
                 "." or sentence == "!" or sentence == "?"]
    return len(sentences)


def cal_index(words, letters, sentences):
    L = (letters / words) * 100
    S = (sentences / words) * 100
    coleman_liau_index = round(0.0588 * L - 0.296 * S - 15.8)
    return coleman_liau_index


def determine_grade(grades):
    if grades < 1:
        print("Before Grade 1")
    elif grades >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grades}")


main()
