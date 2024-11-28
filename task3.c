#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to validate the email address
int validateEmail(char* email) {
    if (email == NULL || strlen(email) == 0) {
        return 0; // Email is empty or null
    }

    char* atSymbol = strchr(email, '@');
    if (atSymbol == NULL) {
        return 0; // No @ symbol found
    }

    // Ensure only one @ symbol exists
    if (strchr(atSymbol + 1, '@') != NULL) {
        return 0; // More than one @ symbol
    }

    // Ensure there's at least one dot (.) after the @ symbol
    if (strchr(atSymbol + 1, '.') == NULL) {
        return 0;
    }

    return 1; // Email is valid
}

int main() {
    char* email;
    size_t bufferSize = 0;

    printf("Enter an email address: ");
    getline(&email, &bufferSize, stdin);

    // Remove the newline character if present
    size_t length = strlen(email);
    if (length > 0 && email[length - 1] == '\n') {
        email[length - 1] = '\0';
    }

    // Validate the email
    if (validateEmail(email)) {
        printf("Valid Email\n");
    } else {
        printf("Invalid Email\n");
    }

    // Free dynamically allocated memory
    free(email);

    return 0;
}
