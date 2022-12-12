#include <iostream>

const int START_SIZE = 100;

void increaseArraySize(int* arr, int& currentSize, int factor = 1);
void copyOldToNew(const int* oldArr, const int oldSize, int* newArr);
void addNumberToBinaryArray(int decimalNumber, const int ind, int* binaryArray);
bool containsTwoConsecutiveZeros(const int* binaryNumbers, const int ind);
void convertBinaryToDecimal(const int* binaryArr, const int ind, int* decimalArr);
int countCharacters(const int* arr, const int size, const int width);
void drawShape(const int* arr, const int size, const int width, const int numberOfCharacters);
int main()
{
    int width;
    std::cin >> width;

    int ind = 0;
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

        //If the binary number contains 6 consecutive zeros
        //(or 2 zeroes after converting to decimal), 
        //the loop is exited. 
        if (containsTwoConsecutiveZeros(binaryNumbers, ind)) {
            ind++;
            break;
        }
        ind++;
    }
    int binaryToDecimalSize = binaryNumbersSize / 3;
    int* binaryToDecimal = new int[binaryToDecimalSize]();
    convertBinaryToDecimal(binaryNumbers, ind, binaryToDecimal);

    int numberOfCharacters = countCharacters(binaryToDecimal, (ind * 8) / 3, width);
    if (!numberOfCharacters) {
        std::cout << numberOfCharacters << "\n";
        std::cout << "Invalid input";
        return 0;
    }
    drawShape(binaryToDecimal, binaryToDecimalSize, width, numberOfCharacters);
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

bool containsTwoConsecutiveZeros(const int* binaryNumbers, const int ind) {
    int startIndex = ind * 8;
    //If the index > 0, it is possible that there is a pair of zeroes 
    //from the previous number 
    if (ind > 0) {
        startIndex -= 3;
    }
    int endIndex = ind * 8 + 8;
    int zeroesCtr = 0;
    for (int i = startIndex; i < endIndex; i++) {
        if (binaryNumbers[i] == 0) {
            zeroesCtr++;
        }
        else {
            zeroesCtr = 0;
        }
        if (zeroesCtr >= 6) {
            return true;
        }
    }
    return false;
}

int countCharacters(const int* arr, const int size, const int width) {
    //The input is invalid if the number of symbols isn't divisible by
    //width
    int ctr = 0;
    for (int i = 0; i < size; i++) {
        ctr += arr[i];
    }
    if (ctr == 0 || ctr % width != 0) { return 0; }
    return ctr;
}

void convertBinaryToDecimal(const int* binaryArr, const int ind, int* decimalArr) {
    int endIndex = ind * 8;
    int num = 0;
    int decimalIndex = 0;
    for (int i = 0; i + 3 < endIndex; i += 3) {
        num = 1 * binaryArr[i + 2] + 2 * binaryArr[i + 1] + 4 * binaryArr[i];
        decimalArr[decimalIndex++] = num;
    }
}

void drawShape(const int* arr, const int size, const int width, const int numberOfCharacters) {
    const int height = numberOfCharacters / width;
    int arrIndex = 0;

    const char NUMBER_SIGN = '#';
    const char FULL_STOP = '.';

    for (int i = 0; i < height; i++) {
        //For each row, there are a {width} number of digits to
        //be printed. For this count, we will use a for loop 
        //If the current arr[arrInd] = 0, then we increase the arrInd by 1
        //Then, according to the arrInd, we print . or # as many times 
        //as the value of arr[arrInd] is (arrInd is even => '.'
        //arrInd is odd => '#')
        
        std::cout << "\n";
    }
}


