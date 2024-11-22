#include <stdio.h>
#include <string.h>
#include <time.h>

struct Employee {
    int employeeCode;
    char employeeName[100];
    struct tm dateOfJoining; // Use struct tm to store the date
};

void assignEmployeeDetails(struct Employee *emp) {
    printf("Enter Employee Code: ");
    scanf("%d", &emp->employeeCode);
    getchar(); // To consume the newline left by scanf
    printf("Enter Employee Name: ");
    fgets(emp->employeeName, sizeof(emp->employeeName), stdin);
    emp->employeeName[strcspn(emp->employeeName, "\n")] = '\0';  // Remove newline character
    printf("Enter Date of Joining (YYYY MM DD): ");
    scanf("%d %d %d", &emp->dateOfJoining.tm_year, &emp->dateOfJoining.tm_mon, &emp->dateOfJoining.tm_mday);
    // Adjust tm_year and tm_mon to match the standard struct tm format
    emp->dateOfJoining.tm_year -= 1900;  // Years since 1900
    emp->dateOfJoining.tm_mon -= 1;      // Months from 0 to 11
}

void calculateTenureAndDisplay(struct Employee emp[], int n, int currentYear, int currentMonth, int currentDay) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        int tenureYears = currentYear - emp[i].dateOfJoining.tm_year;
        int tenureMonths = currentMonth - emp[i].dateOfJoining.tm_mon;
        int tenureDays = currentDay - emp[i].dateOfJoining.tm_mday;

        if (tenureMonths < 0 || (tenureMonths == 0 && tenureDays < 0)) {
            tenureYears--;
        }

        if (tenureYears > 3) {
            count++;
            printf("\nEmployee Code: %d\n", emp[i].employeeCode);
            printf("Employee Name: %s\n", emp[i].employeeName);
            printf("Date of Joining: %d-%d-%d\n", emp[i].dateOfJoining.tm_year + 1900, emp[i].dateOfJoining.tm_mon + 1, emp[i].dateOfJoining.tm_mday);
            printf("Tenure: %d years\n", tenureYears);
        }
    }
    printf("\nTotal number of employees with more than 3 years of tenure: %d\n", count);
}

int main() {
    struct Employee employees[4];

    // Assign details to 4 employees
    for (int i = 0; i < 4; i++) {
        printf("\nEnter details for Employee %d:\n", i + 1);
        assignEmployeeDetails(&employees[i]);
    }

    // Input current date
    int currentYear, currentMonth, currentDay;
    printf("\nEnter current date (YYYY MM DD): ");
    scanf("%d %d %d", &currentYear, &currentMonth, &currentDay);

    // Calculate tenure and display employees with more than 3 years of tenure
    calculateTenureAndDisplay(employees, 4, currentYear, currentMonth, currentDay);

    return 0;
}
