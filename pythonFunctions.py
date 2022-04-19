import re
import string


def FrequencyList(inputString):  # creates dictionary of items with its frequency
    item_dictionary = {}
    with open('CS210_Project_Three_Input_File.txt', 'r') as file:
        for line in file.readlines():
            item = line.strip()
            if item not in item_dictionary:
                item_dictionary[item] = 1
            else:
                item_dictionary[item] += 1

    for item, frequency in item_dictionary.items():  # display item and its frequency from dictionary
        print(item, frequency)
    return 0


def ItemFrequency(inputString):  # prints frequency of item input by user
    item_dictionary = {}
    with open('CS210_Project_Three_Input_File.txt', 'r') as file:
        for line in file.readlines():
            item = line.strip()
            if item not in item_dictionary:
                item_dictionary[item] = 1
            else:
                item_dictionary[item] += 1

    for item, frequency in item_dictionary.items():
        if inputString == item:
            return frequency
    print("No such item...")  # runs if no item found (a kind of input validation) and returns zero
    return 0


def DataFileAndHistogram(inputString):  # reads text file and creates/overwrites .dat file from it
    item_dictionary = {}
    with open('CS210_Project_Three_Input_File.txt', 'r') as file:
        for line in file.readlines():
            item = line.strip()
            if item not in item_dictionary:
                item_dictionary[item] = 1
            else:
                item_dictionary[item] += 1
    with open('frequency.dat', 'w') as datFile:
        lineList = []
        for item, frequency in item_dictionary.items():  # make a list of lines
            line = str(item) + " " + str(frequency) + "\n"
            lineList.append(line)
        datFile.writelines(lineList)  # write list of lines to .dat file
    return 0
