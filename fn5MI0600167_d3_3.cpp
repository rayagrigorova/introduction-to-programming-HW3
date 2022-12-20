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

//void printTwoDimArray(char** arr, int n, int m);
void printTime(char* time);

int compareTimes(char* time1, char* time2);

void calculateMinimalNumberOfSites(char** landingTimes, char** departureTimes, const int N);
void sortArrays(char** landingTimes, char** departureTimes, const int N);
int calculateNumberOfIntervalsAPointIsIn(char** landingTimes, char** departureTimes, const int N, char* point);
bool pointIsInRange(char* point, char* landingTime, char* departureTime);
void evaluateMaxIntersectionIntervals(char** landingTimes, char** departureTimes, const int N, const int maxIntersectingCount);
bool isInArray(char* element, char** arr, const int N);

void freeMemory(char** arr, const int rows);

int main()
{
	int N;
	std::cin >> N;
	if (N <= 0) {
		std::cout << "Incorrect input";
		return 0;
	}

	char** landingTimes = new char* [N]();
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
	calculateMinimalNumberOfSites(landingTimes, departureTimes, N);

	freeMemory(landingTimes, N);
	freeMemory(departureTimes, N);
}

//This function returns:
// -> 1 if time1 > time2
// -> 0 if time1 == time2
// -> -1 if time1 < time2
int compareTimes(char* time1, char* time2) {
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

void calculateMinimalNumberOfSites(char** landingTimes,  char** departureTimes, const int N) {
	sortArrays(landingTimes, departureTimes, N);

	//For each landingTime (and departureTime), I will calculate the number of intervals it is in
	//The beginning of the max intersection is some landingTime and the end is some departureTime 
	int maxIntersectionsStart = -1, maxIntersectionsEnd = -1;
	int startIndex = -1, endIndex = -1;
	for (int i = 0; i < N; i++) {
		int intervalsLandingTimeIsIn = calculateNumberOfIntervalsAPointIsIn(landingTimes, departureTimes, N, landingTimes[i]);
		int intervalsDepartureTimeIsIn = calculateNumberOfIntervalsAPointIsIn(landingTimes, departureTimes, N, departureTimes[i]);

		if (intervalsLandingTimeIsIn > maxIntersectionsStart) {
			maxIntersectionsStart = intervalsLandingTimeIsIn;
			startIndex = i;
		}
		if (intervalsDepartureTimeIsIn > maxIntersectionsEnd) {
			maxIntersectionsEnd = intervalsDepartureTimeIsIn;
			endIndex = i;
		}
	}
	std::cout << maxIntersectionsStart << "\n";
	evaluateMaxIntersectionIntervals(landingTimes, departureTimes, N, maxIntersectionsStart);
}

void freeMemory(char** arr, const int rows) {
	//For each sub-array
	for (int i = 0; i < rows; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}

void sortArrays(char** landingTimes, char** departureTimes, const int N) {
	//The planes must be sorted in ascending order for the algorithm to work
	//For this purpose, I will not copy the char arrays in landingTimes and departureTimes,
	//instead I will simply change the pointers
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N - i - 1; j++) {
			if (compareTimes(landingTimes[j], landingTimes[j + 1]) > 0) {
				char* ptr = landingTimes[j];
				landingTimes[j] = landingTimes[j + 1];
				landingTimes[j + 1] = ptr;

				ptr = departureTimes[j];
				departureTimes[j] = departureTimes[j + 1];
				departureTimes[j + 1] = ptr;
			}
		}
	}
}

//A point is some char array consisting of 4 characters {H,H,M,M}
int calculateNumberOfIntervalsAPointIsIn(char** landingTimes, char** departureTimes, const int N, char* point) {
	int numberOfIntervals = 0;
	for (int j = 0; j < N; j++) {
		if (pointIsInRange(point, landingTimes[j], departureTimes[j])) {
			numberOfIntervals++;
		}
	}
	return numberOfIntervals;
}

bool pointIsInRange(char* point, char* landingTime, char* departureTime) {
	return (compareTimes(point, landingTime) >= 0 && compareTimes(point, departureTime) <= 0);
}

//Now that we know the maximal number of intersecting intervals, we should print all of them 
void evaluateMaxIntersectionIntervals(char** landingTimes, char** departureTimes, const int N, const int maxIntersectingCount) {
	//For each point, we evaluate the number of intervals it is in. If the number is equal to maxIntersectingCount, 
	//it is the start of the next biggest intersection. 
	
	char** starts = new char*[N]();
	char** ends = new char*[N]();

	int startsInd = 0, endsInd = 0;

	for (int i = 0; i < N; i++) {
		int intervalsLandingTimeIsIn = calculateNumberOfIntervalsAPointIsIn(landingTimes, departureTimes, N, landingTimes[i]);
		int intervalsDepartureTimeIsIn = calculateNumberOfIntervalsAPointIsIn(landingTimes, departureTimes, N, departureTimes[i]);

		if (intervalsLandingTimeIsIn == maxIntersectingCount && !isInArray(landingTimes[i], starts, N)) {
			starts[startsInd++] = landingTimes[i];
		}
		if (intervalsDepartureTimeIsIn == maxIntersectingCount && !isInArray(departureTimes[i], ends, N)) {
			ends[endsInd++] = departureTimes[i];
		}
	}

	for (int i = 0; i < startsInd; i++) {
		printTime(starts[i]);
		std::cout << '-';
		printTime(ends[i]);
		std::cout << '\n';
	}

	delete[]starts;
	delete[]ends;
}

void printTime(char* time) {
	for (int i = 0; i < HHMM; i++) {
		std::cout << time[i];
	}
}

bool isInArray(char* element, char** arr, const int N) {
	for (int i = 0; i < N; i++) {
		if (arr[i] == nullptr) return false;
		if (compareTimes(element, arr[i]) == 0) return true;
	}
	return false;
}