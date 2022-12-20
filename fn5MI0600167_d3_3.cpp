/**
*
* Solution to homework assignment 3
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Raya Grigorova
* @idnumber 5MI0600167
* @task 3
*
*/

#include <iostream>

const int HHMM = 4;

void sortTimesInAscendingOrder(char** landingTimes, char** departureTimes, const int N);

void printTwoDimArray(const char** const arr, int n, int m);

int compareTimes(const char* const time1, const char* const time2);
const char* maximalTime(const char* const time1, const char* const time2);
const char* minimalTime(const char* const time1, const char* const time2);

void calculateMinimalNumberOfSites(const char** const departureTimes, const char** const landingTimes, const int N);
bool planesCanBeGrouped(const char** const landingTimes, const char** const departureTimes, const int N, const int i, const int j);
void evaluateBusiestPeriods(const char** const departureTimes, const char** const landingTimes, const int N, const int maxNumberOfPlanesOnAirport);

void freeMemory(char** arr, const int rows);

int main()
{
	int N;
	std::cin >> N;
	if (N <= 0) {
		std::cout << "Incorrect input";
		return 0;
	}

	char** landingTimes = new char*[N]();
	for (int i = 0; i < N; i++) {
		landingTimes[i] = new char[HHMM + 1]();
		for (int j = 0; j < HHMM; j++) {
			std::cin >> landingTimes[i][j];
		}
		landingTimes[i][HHMM] = '\0';
	}

	char** departureTimes = new char* [N]();
	for (int i = 0; i < N; i++) {
		departureTimes[i] = new char[HHMM + 1]();
		for (int j = 0; j < HHMM; j++) {
			std::cin >> departureTimes[i][j];
		}
		departureTimes[i][HHMM] = '\0';
	}
	calculateMinimalNumberOfSites(departureTimes, landingTimes, N);

	freeMemory(landingTimes, N);
	freeMemory(departureTimes, N);
}

void sortTimesInAscendingOrder(char** landingTimes, char** departureTimes, const int N) {
	//In the examples, the 
}

void printTwoDimArray(const char** arr, int n, int m) {
	for (int i = 0; i < n; i++) {
		std::cout << "\n";
		for (int j = 0; j < m; j++) {
			std::cout << arr[i][j];
		}
	}
	std::cout << "\n\n\n";
}

//This function returns:
// -> 1 if time1 > time2
// -> 0 if time1 == time2
// -> -1 if time1 < time2
int compareTimes(const char* const time1, const char* const time2) {
	for (int i = 0; i < HHMM; i++) {
		if (time1[i] > time2[i]) {
			return 1;
		}
		if (time2[i] > time1[i]) {
			return -1;
		}
	}
	return 0;
}

void calculateMinimalNumberOfSites(const char** const departureTimes, const char** const landingTimes, const int N) {
	//My goal is to group each plane with as many as I possibly can
	//in order to find the busiest period at the airport 
	//and from there - the minimal number of sites needed 

	int maxNumberOfPlanesOnAirport = 0;
	int numberOfPlanesInGroup = 0;

	//For each plane
	for (int i = 0; i < N; i++) {
		numberOfPlanesInGroup = 1;
		for (int j = 0; j < N; j++) {
			if (i == j) { continue; }
			if (planesCanBeGrouped(landingTimes, departureTimes, N, i, j)) {
				numberOfPlanesInGroup++;
			}
		}
		if (numberOfPlanesInGroup > maxNumberOfPlanesOnAirport) {
			maxNumberOfPlanesOnAirport = numberOfPlanesInGroup;
		}
	}
	std::cout << maxNumberOfPlanesOnAirport;
	evaluateBusiestPeriods(departureTimes, landingTimes, N, maxNumberOfPlanesOnAirport);
}

bool planesCanBeGrouped(const char** const landingTimes, const char** const departureTimes, const int N, const int i, const int j) {
	//Grouping is possible if the landing time of the second plane is between 
	//the landing and departure times of the first 
	//This means that landingTimeSecond >= landingTimeFirst
	//and landingTimeSecond <= departureTimeFirst
	return((compareTimes(landingTimes[j], landingTimes[i]) >= 0)
		&& (compareTimes(landingTimes[j], departureTimes[i]) <= 0));
}

const char* maximalTime(const char* const time1, const char* const time2) {
	const char* result;
	if (compareTimes(time1, time2) >= 0) {
		result = time1;
	}
	else {
		result = time2;
	}
	return result;
}

const char* minimalTime(const char* const time1, const char* const time2) {
	const char* result;
	if (compareTimes(time1, time2) >= 0) {
		result = time2;
	}
	else {
		result = time1;
	}
	return result;
}

void evaluateBusiestPeriods(const char** const departureTimes, const char** const landingTimes, const int N, const int maxNumberOfPlanesOnAirport) {
	int numberOfPlanesInGroup = 0;
	const char* periodStart = nullptr;
	const char* periodEnd = nullptr; 
	for (int i = 0; i < N; i++) {
		numberOfPlanesInGroup = 1;
		periodStart = landingTimes[i];
		periodEnd = departureTimes[i];
		//For each plane
		for (int j = 0; j < N; j++) {
			if (i == j) { continue; }
			if (planesCanBeGrouped(landingTimes, departureTimes, N, i, j)) {
				numberOfPlanesInGroup++;
				periodStart = maximalTime(periodStart, landingTimes[j]);
				periodEnd = minimalTime(periodEnd, departureTimes[j]);
			}
		}
		if (numberOfPlanesInGroup == maxNumberOfPlanesOnAirport) {
			std::cout << "\n";
			std::cout << periodStart << "-" << periodEnd;
		}
	}
}

void freeMemory(char** arr, const int rows) {
	//For each dub-array
	for (int i = 0; i < rows; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}



