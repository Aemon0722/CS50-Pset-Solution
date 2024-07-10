from cs50 import get_int


def main():

    height = get_height()
    for i in range(height):
        # print first half of pyramid before the gap
        print(" " * (height - i - 1) + "#" * (i + 1), end="")
        # print second half of pyramid starting with the gap
        print("  " + "#" * (i + 1))


def get_height():
    while True:
        n = get_int("What is the height of the pyramid? ")
        if n > 0 and n < 9:
            return n


main()
