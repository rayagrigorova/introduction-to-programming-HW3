#include <iostream>

const int HHMM = 4;

void printTwoDimArray(char** arr, int n, int m);
int compareTimes(char* const time1, char* const time2);
char* maximalTime(char* const time1, char* const time2);
char* minimalTime(char* const time1, char* const time2);

void calculateMinimalNumberOfSites(char** departureTimes, char** landingTimes, const int N);
void sortArraysBasedOnDepartureTimes(char** departureTimes, char** landingTimes, const int N);
bool planesCanBeGrouped(char** const landingTimes, char** const departureTimes, const int N, const int i, const int j);
void evaluateBusiestPeriods(char** departureTimes, char** landingTimes, const int N, const int maxNumberOfPlanesOnAirport);
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
	//printTwoDimArray(landingTimes, N, 4);
	//printTwoDimArray(departureTimes, N, 4);
	calculateMinimalNumberOfSites(departureTimes, landingTimes, N);
}
void printTwoDimArray(char** arr, int n, int m) {
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
int compareTimes(char* const time1, char* const time2) {
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

void calculateMinimalNumberOfSites(char** departureTimes, char** landingTimes, const int N) {
	//My goal is to group each plane with as many as I possibly can
	//in order to find the busiest period at the airport 
	//and from there - the minimal number of sites needed 
	//But for that, I first have to sort the arrays in 
	//ascending order (based on the departureTimes)

	int maxNumberOfPlanesOnAirport = 0;
	int numberOfPlanesInGroup = 0;


	for (int i = 0; i < N; i++) {
		numberOfPlanesInGroup = 1;
		//For each plane
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

void sortArraysBasedOnDepartureTimes(char** departureTimes, char** landingTimes, const int N) {

}

bool planesCanBeGrouped(char** const landingTimes, char** const departureTimes, const int N, const int i, const int j) {
	//Grouping is possible if the landing time of the second plane is between 
	//the landing and departure times of the first 
	//This means that landingTimeSecond >= landingTimeFirst
	//and landingTimeSecond <= departureTimeFirst
	return((compareTimes(landingTimes[j], landingTimes[i]) >= 0)
		&& (compareTimes(landingTimes[j], departureTimes[i]) <= 0));
}

char* maximalTime(char* const time1, char* const time2) {
	char* result;
	if (compareTimes(time1, time2) >= 0) {
		result = time1;
	}
	else {
		result = time2;
	}
	return result;
}

char* minimalTime(char* const time1, char* const time2) {
	char* result;
	if (compareTimes(time1, time2) >= 0) {
		result = time2;
	}
	else {
		result = time1;
	}
	return result;
}

void evaluateBusiestPeriods(char** departureTimes, char** landingTimes, const int N, const int maxNumberOfPlanesOnAirport) {
	int numberOfPlanesInGroup = 0;
	char* periodStart = nullptr;
	char* periodEnd = nullptr; 
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
