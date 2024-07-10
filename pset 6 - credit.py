import re


def main():
    card_no = input("Credit Card Number: ")
    # check checksum
    if cal_checksum(card_no) == False:
        print("INVALID")
    else:
        # check card length
        if len(card_no) == 13:
            # if the card_no header is not 4
            if re.match("^4", card_no) == None:
                print("INVALID")
            else:
                print("VISA")

        elif len(card_no) == 15:
            # if the card_no header is not 34 or 37
            if re.match("^(34|37)", card_no) == None:
                print("INVALID")
            else:
                print("AMEX")

        elif len(card_no) == 16:
            # if the card_no header is not 4 or from 51 - 55
            if re.match("^4|5[1-5]", card_no) == None:
                print("INVALID")
            else:
                # check whether the card is master or visa
                if card_no[0] == "4":
                    print("VISA")
                else:
                    print("MASTERCARD")
        # if the card_no length does not match above length
        else:
            print("INVALID")


def cal_checksum(card_no):
    # create empty list for storing all the digit of the card no.
    products = []
    for i in range(len(card_no)):
        # starting the end of the string, which the index is -1
        digit = int(card_no[-i - 1])
        # if it is even digit
        if i % 2 == 1:
            digit *= 2
            # if the product of digit is greater than 9
            if digit > 9:
                # turn it become str, sum the first and second digit, add the sum into the list
                digit = str(digit)
                digit_sum = int(digit[0]) + int(digit[1])
                products.append(digit_sum)
            # add the digit to the list
            else:
                products.append(digit)
        # add odd digit to the list
        else:
            products.append(digit)

    # if the sum of card_no can be divided by 10
    if sum(products) % 10 == 0:
        return True
    else:
        return False


main()
