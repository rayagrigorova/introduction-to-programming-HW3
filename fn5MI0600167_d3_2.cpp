#include <iostream>

bool MisInRange(const int M, const int MIN_M, const int MAX_M);
bool numIsInRange(const int num, const int MIN_NUM, const int MAX_NUM);

void computeGreatestProjection(int arr[], const int arraySize);
void swapNumbers(int& a, int& b);
void printArray(const int arr[], const int size);
int countDigits(int N);

bool compareNumbers(int num1, int num2);
void fillArray(char* array, int num, const int numberOfDigits);


int main()
{
	const int MIN_NUM = 1;
	const int MAX_NUM = 9999;

	const int MIN_M = 1;
	const int MAX_M = 15;

	int M;
	std::cin >> M;
	if (!MisInRange(M, MIN_M, MAX_M)) {
		std::cout << "-1";
		return 0;
	}

	int* arr = new int[M]();
	int num;

	for (int i = 0; i < M; i++) {
		std::cin >> num;
		if (!numIsInRange(num, MIN_NUM, MAX_NUM)) {
			std::cout << "-1";
			return 0;
		}
		arr[i] = num;

	}
	computeGreatestProjection(arr, M);
	printArray(arr, M);
}

bool MisInRange(const int M, const int MIN_M, const int MAX_M) {
	return (M >= MIN_M && M <= MAX_M);
}

bool numIsInRange(const int num, const int MIN_NUM, const int MAX_NUM) {
	return (num >= MIN_NUM && num <= MAX_NUM);
}

void computeGreatestProjection(int arr[], const int arraySize) {
	for (int i = 0; i < arraySize - 1; i++) {
		for (int j = 0; j < arraySize - 1 - i; j++) {
			//printArray(arr, arraySize);
			//std::cout << "\n\n\n";
			if (!compareNumbers(arr[j], arr[j + 1])) {
				swapNumbers(arr[j], arr[j + 1]);
			}
		}
	}
}

void swapNumbers(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

int countDigits(int N) {
	if (N == 0) { return 1; }

	int ctr = 0;
	while (N != 0) {
		ctr++;
		N /= 10;
	}
	return ctr;
}

void printArray(const int arr[], const int size) {
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << " ";
	}
}

//This function return true if the first number is bigger than the second 
//when comparing their digits, starting from the first one
bool compareNumbers(int num1, int num2) {
	int num1Digits = countDigits(num1);
	int num2Digits = countDigits(num2);

	char* arr1 = new char[num1Digits + 1];
	char* arr2 = new char[num2Digits + 1];

	fillArray(arr1, num1, num1Digits);
	fillArray(arr2, num2, num2Digits);

	int ind1 = num1Digits - 1, ind2 = num2Digits - 1;

	for (; ind1 > 0 && ind2 > 0; ind1--, ind2--) {
		//Once we find one different digit, the function can return a result
		if (arr1[ind1] > arr2[ind2]) {
			return true;
		}
		if (arr1[ind1] < arr2[ind2]) {
			return false;
		}
	}

	//If one of the indices == 0, there are a few possible cases

	if (ind1 == 0 && ind2 == 0) {
		return arr1[ind1] > arr2[ind2];
	}

	//The end of num1 has been reached
	if (ind1 == 0) {
		while (ind2 >= 0) {
			if (arr2[ind2] < arr1[ind1]) { return true; }
			ind2--;
		}
		return false;
	}

	//The end of num2 has been reached
	while (ind1 >= 0) {
		if (arr2[ind2] < arr1[ind1]) { return true; }
		ind1--;
	}
	return false;
	
}

void fillArray(char* array, int num, const int numberOfDigits) {
	for (int i = 0; i < numberOfDigits; i++) {
		array[i] = num % 10;
		num /= 10;
	}
	array[numberOfDigits] = '\0';
}





