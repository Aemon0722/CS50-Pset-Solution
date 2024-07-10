import csv
import sys


def main():

    # TODO: Check for command-line usage
    # command line should have file name, dna database, and dna file these 3 command line
    if len(sys.argv) != 3:
        print("Incorrect command!")
        sys.exit(1)

    # TODO: Read database file into a variable
    # create a list to fill with dictionary data type with name and dna_info
    person_dna = []
    try:
        # the 2nd command line should be the name of dna data base, open that file
        # newline="" ensure there will be no empty row within rows
        with open(sys.argv[1], newline="") as dna_database:
            # read rows from the as a dictionary with the first row as fieldnames
            reader = csv.DictReader(dna_database)
            for dna_info in reader:
                # read each rows of dictionary into a list
                person_dna.append(dna_info)
    # if files cannot be found
    except FileNotFoundError:
        print("Database not found.")

    # TODO: Read DNA sequence file into a variable
    try:
        # the 3rd command line should be the name of dna file, open that file to read
        # most txt files use "utf-8" to encode characters
        with open(sys.argv[2], 'r', encoding="utf-8") as dna:
            # read that dna sequence
            sequences = dna.read()
    # if files cannot be found
    except FileNotFoundError:
        print("DNA sequence not found.")

    # TODO: Find longest match of each STR in DNA sequence
    # create a list with STRs only
    str_list = reader.fieldnames[1:]
    # create a dictionary to include the longest_match of each STR for that sequence
    results = {}
    for STR in str_list:
        # as the longest_match function return integer, I need to convert it to str for later comparison
        results[STR] = str(longest_match(sequences, STR))

    # TODO: Check database for matching profiles
    # To check each person in the person_dna database
    for person in person_dna:
        # to count how many STRs it matches
        count = 0
        # each SRT(the keys of dict) in the STR list
        for STR in str_list:
            # if values of both dict are not equal with the same key, means it does not match
            if results[STR] != person[STR]:
                break
            else:
                # increment count if it matches
                count += 1
        # print that person name if all STRs match
        if count == len(str_list):
            print(f"{person['name']}")
            break
    # if no person in the person_dna database matches, print no match
    else:
        print("No match.")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
