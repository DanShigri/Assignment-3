#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* ratings;    // Dynamically allocated array for ratings
    int totalScore;  // Total score across all evaluation periods
} Employee;

// Function to input ratings for each employee
void inputEmployees(int** ratings, int numEmployees, int numPeriods) {
    for (int i = 0; i < numEmployees; i++) {
        ratings[i] = (int*)malloc(numPeriods * sizeof(int)); // Allocate memory for ratings
        if (ratings[i] == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }

        printf("Enter ratings for Employee %d (between 1 and 10):\n", i + 1);
        for (int j = 0; j < numPeriods; j++) {
            int valid = 0;
            while (!valid) {
                printf("  Period %d: ", j + 1);
                scanf("%d", &ratings[i][j]);
                if (ratings[i][j] >= 1 && ratings[i][j] <= 10) {
                    valid = 1;
                } else {
                    printf("Invalid rating. Please enter a value between 1 and 10.\n");
                }
            }
        }
    }
}

// Function to display performance ratings
void displayPerformance(int** ratings, int numEmployees, int numPeriods) {
    printf("\nPerformance Ratings:\n");
    for (int i = 0; i < numEmployees; i++) {
        printf("Employee %d: ", i + 1);
        for (int j = 0; j < numPeriods; j++) {
            printf("%d ", ratings[i][j]);
        }
        printf("\n");
    }
}

// Function to find the employee of the year
int findEmployeeOfTheYear(int** ratings, int numEmployees, int numPeriods) {
    int bestEmployee = 0;
    float highestAverage = 0;

    for (int i = 0; i < numEmployees; i++) {
        int total = 0;
        for (int j = 0; j < numPeriods; j++) {
            total += ratings[i][j];
        }
        float average = (float)total / numPeriods;
        if (average > highestAverage) {
            highestAverage = average;
            bestEmployee = i;
        }
    }

    return bestEmployee;
}

// Function to find the highest-rated evaluation period
int findHighestRatedPeriod(int** ratings, int numEmployees, int numPeriods) {
    int bestPeriod = 0;
    float highestAverage = 0;

    for (int j = 0; j < numPeriods; j++) {
        int total = 0;
        for (int i = 0; i < numEmployees; i++) {
            total += ratings[i][j];
        }
        float average = (float)total / numEmployees;
        if (average > highestAverage) {
            highestAverage = average;
            bestPeriod = j;
        }
    }

    return bestPeriod;
}

// Function to find the worst-performing employee
int findWorstPerformingEmployee(int** ratings, int numEmployees, int numPeriods) {
    int worstEmployee = 0;
    float lowestAverage = 10; // Maximum possible rating

    for (int i = 0; i < numEmployees; i++) {
        int total = 0;
        for (int j = 0; j < numPeriods; j++) {
            total += ratings[i][j];
        }
        float average = (float)total / numPeriods;
        if (average < lowestAverage) {
            lowestAverage = average;
            worstEmployee = i;
        }
    }

    return worstEmployee;
}

int main() {
    int numEmployees, numPeriods;

    printf("Enter the number of employees: ");
    scanf("%d", &numEmployees);
    printf("Enter the number of evaluation periods: ");
    scanf("%d", &numPeriods);

    // Dynamically allocate memory for ratings array
    int** ratings = (int**)malloc(numEmployees * sizeof(int*));
    if (ratings == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    // Input ratings
    inputEmployees(ratings, numEmployees, numPeriods);

    // Display ratings
    displayPerformance(ratings, numEmployees, numPeriods);

    // Find and display the employee of the year
    int bestEmployee = findEmployeeOfTheYear(ratings, numEmployees, numPeriods);
    printf("\nEmployee of the Year: Employee %d\n", bestEmployee + 1);

    // Find and display the highest-rated evaluation period
    int bestPeriod = findHighestRatedPeriod(ratings, numEmployees, numPeriods);
    printf("Highest Rated Period: Period %d\n", bestPeriod + 1);

    // Find and display the worst-performing employee
    int worstEmployee = findWorstPerformingEmployee(ratings, numEmployees, numPeriods);
    printf("Worst Performing Employee: Employee %d\n", worstEmployee + 1);

    // Free dynamically allocated memory
    for (int i = 0; i < numEmployees; i++) {
        free(ratings[i]);
    }
    free(ratings);

    return 0;
}
