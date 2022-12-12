#include <iostream>

const int START_SIZE = 100;

void increaseArraySize(int* arr, int& currentSize, int factor = 1);
void copyOldToNew(const int* oldArr, const int oldSize, int* newArr);
void addNumberToBinaryArray(int decimalNumber, const int ind, int* binaryArray);
int containsTwoConsecutiveZeros(const int* binaryNumbers, const int ind);
void convertBinaryToDecimal(const int* binaryArr, const int ind, int* decimalArr, const int firstZeroIndex);
int countCharacters(const int* arr, const int size, const int width);
void drawShape(const int* arr, const int ind, const int width, const int numberOfCharacters);
void printCharNTimes(const char ch, const int numberOfTimes, const int width, int& charactersOnRow);

int main()
{
    int width;
    std::cin >> width;

    int ind = 0;
    int firstZeroInd = 0;
    int numbersSize = START_SIZE;
    int binaryNumbersSize = numbersSize * 8;

    int* numbers = new int[numbersSize]();
    int* binaryNumbers = new int[binaryNumbersSize]();

    while (1) {
        if (ind >= numbersSize) {
            increaseArraySize(numbers, numbersSize);
            increaseArraySize(binaryNumbers, binaryNumbersSize, 8);
        }
        std::cin >> numbers[ind];

        //We will add the new number to the binary array
        addNumberToBinaryArray(numbers[ind], ind, binaryNumbers);

        //If the binary number contains 6 consecutive zeros, the loop is exited. 
        firstZeroInd = containsTwoConsecutiveZeros(binaryNumbers, ind);
        if (firstZeroInd) {
            break;
        }
        ind++;
    }
    int binaryToDecimalSize = binaryNumbersSize / 3;
    int* binaryToDecimal = new int[binaryToDecimalSize]();
    convertBinaryToDecimal(binaryNumbers, ind, binaryToDecimal, firstZeroInd);

    int numberOfCharacters = countCharacters(binaryToDecimal, (ind * 8) / 3, width);
    if (!numberOfCharacters) {
        std::cout << "Invalid input";
        return 0;
    }
    drawShape(binaryToDecimal, ind, width, numberOfCharacters);
}

void increaseArraySize(int* arr, int& currentSize, int factor) {
    //First, I will create a new array 
    int* newArr = new int[currentSize + START_SIZE * factor]();

    //Copy everything from oldArr to newArr
    copyOldToNew(arr, currentSize, newArr);

    //Delete the old array
    delete[] arr;

    //And finally, point *arr to *newArr
    arr = newArr;

    //Update size
    currentSize += (START_SIZE * factor);

}

void copyOldToNew(const int* oldArr, const int oldSize, int* newArr) {
    for (int i = 0; i < oldSize; i++) {
        newArr[i] = oldArr[i];
    }
}

void addNumberToBinaryArray(int decimalNumber, const int ind, int* binaryArray) {
    //I will add the binary number in reverse order 
    for (int i = ind * 8 + 7; i >= ind * 8; i--) {
        binaryArray[i] = decimalNumber % 2;
        decimalNumber /= 2;
    }
}

int containsTwoConsecutiveZeros(const int* binaryNumbers, const int ind) {
    int startIndex = ind * 8;

    //If the index > 0, it is possible that there is a pair of zeroes 
    //from the previous number 
    if (ind > 0) {
        startIndex -= 3;
    }

    int endIndex = ind * 8 + 8;
    int zeroesCtr = 0;
    //We should stop drawing after the first zero
    int firstZeroInd = 0;

    for (int i = startIndex; i < endIndex; i++) {
        if (binaryNumbers[i] == 0) {
            if (zeroesCtr == 0) { firstZeroInd = i; }
            zeroesCtr++;
        }
        else {
            zeroesCtr = 0;
        }
        if (zeroesCtr >= 6) {
            return firstZeroInd;
        }
    }
    return 0;
}

//The input is invalid if the number of symbols isn't divisible by
//width. In this case, the number of characters will be marked with zero.
int countCharacters(const int* arr, const int size, const int width) {

    int ctr = 0;

    for (int i = 0; i < size; i++) {
        ctr += arr[i];
    }

    if (ctr == 0 || ctr % width != 0) { return 0; }
    return ctr;

}

void convertBinaryToDecimal(const int* binaryArr, const int ind, int* decimalArr, const int firstZeroIndex) {
    int endIndex = firstZeroIndex;
    int num = 0;
    int decimalIndex = 0;
    for (int i = 0; i + 3 < endIndex; i += 3) {
        num = 1 * binaryArr[i + 2] + 2 * binaryArr[i + 1] + 4 * binaryArr[i];
        decimalArr[decimalIndex++] = num;
    }
}

void drawShape(const int* arr, const int ind, const int width, const int numberOfCharacters) {
    const int height = numberOfCharacters / width;
    int arrIndex = 0;

    const char CHARACTER_1 = '.';
    const char CHARACTER_2 = '#';

    int numberOfCharactersOnRow = 0;

    for (int i = 0; i < (ind * 8) / 3; i++) {
        switch (i % 2) {
        case 0: printCharNTimes(CHARACTER_1, arr[i], width, numberOfCharactersOnRow); break;
        case 1: printCharNTimes(CHARACTER_2, arr[i], width, numberOfCharactersOnRow);
        }
    }

}

void printCharNTimes(const char ch, const int numberOfTimes, const int width, int& charactersOnRow) {
    for (int i = 0; i < numberOfTimes; i++) {
        //If the characters on this row by now are too many, we should start a new line
        if (charactersOnRow >= width) {
            std::cout << "\n";
            charactersOnRow = 0;
        }
        std::cout << ch;
        charactersOnRow++;
    }
}


