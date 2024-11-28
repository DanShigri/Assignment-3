#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

// Function to initialize the inventory
char*** initializeInventory(int numSpecies, int** numSupplies) {
    char*** speciesSupplies = (char***)malloc(numSpecies * sizeof(char**));
    if (speciesSupplies == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    *numSupplies = (int*)calloc(numSpecies, sizeof(int)); // Number of supplies for each species
    if (*numSupplies == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    return speciesSupplies;
}

// Function to add supplies for a species
void addSupplies(char*** speciesSupplies, int* numSupplies, int speciesIndex, int count) {
    printf("Adding %d supplies for species %d:\n", count, speciesIndex + 1);
    speciesSupplies[speciesIndex] = (char**)realloc(speciesSupplies[speciesIndex], 
                                                    (numSupplies[speciesIndex] + count) * sizeof(char*));
    if (speciesSupplies[speciesIndex] == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        printf("  Enter supply name: ");
        char buffer[MAX_NAME_LENGTH];
        scanf("%s", buffer);
        speciesSupplies[speciesIndex][numSupplies[speciesIndex]] = strdup(buffer);
        if (speciesSupplies[speciesIndex][numSupplies[speciesIndex]] == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }
        numSupplies[speciesIndex]++;
    }
}

// Function to update a supply
void updateSupply(char*** speciesSupplies, int* numSupplies, int speciesIndex, int supplyIndex) {
    if (speciesIndex < 0 || supplyIndex < 0 || supplyIndex >= numSupplies[speciesIndex]) {
        printf("Invalid indices provided.\n");
        return;
    }
    printf("Current supply: %s\n", speciesSupplies[speciesIndex][supplyIndex]);
    printf("Enter new supply name: ");
    char buffer[MAX_NAME_LENGTH];
    scanf("%s", buffer);

    free(speciesSupplies[speciesIndex][supplyIndex]);
    speciesSupplies[speciesIndex][supplyIndex] = strdup(buffer);
    if (speciesSupplies[speciesIndex][supplyIndex] == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
}

// Function to remove a species
void removeSpecies(char*** speciesSupplies, int* numSupplies, int* numSpecies, int speciesIndex) {
    if (speciesIndex < 0 || speciesIndex >= *numSpecies) {
        printf("Invalid species index.\n");
        return;
    }

    // Free supplies for the species
    for (int i = 0; i < numSupplies[speciesIndex]; i++) {
        free(speciesSupplies[speciesIndex][i]);
    }
    free(speciesSupplies[speciesIndex]);

    // Shift remaining species up
    for (int i = speciesIndex; i < *numSpecies - 1; i++) {
        speciesSupplies[i] = speciesSupplies[i + 1];
        numSupplies[i] = numSupplies[i + 1];
    }

    (*numSpecies)--;

    printf("Species %d removed successfully.\n", speciesIndex + 1);
}

// Function to display the inventory
void displayInventory(char*** speciesSupplies, int* numSupplies, int numSpecies) {
    printf("\nCurrent Inventory:\n");
    for (int i = 0; i < numSpecies; i++) {
        printf("Species %d:\n", i + 1);
        for (int j = 0; j < numSupplies[i]; j++) {
            printf("  - %s\n", speciesSupplies[i][j]);
        }
    }
}

int main() {
    int numSpecies;
    printf("Enter the number of species: ");
    scanf("%d", &numSpecies);

    int* numSupplies;
    char*** speciesSupplies = initializeInventory(numSpecies, &numSupplies);

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Add Supplies\n");
        printf("2. Update Supply\n");
        printf("3. Remove Species\n");
        printf("4. Display Inventory\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            int speciesIndex, count;
            printf("Enter species index (1 to %d): ", numSpecies);
            scanf("%d", &speciesIndex);
            speciesIndex--; // Convert to 0-based index
            if (speciesIndex < 0 || speciesIndex >= numSpecies) {
                printf("Invalid species index.\n");
                break;
            }
            printf("Enter the number of supplies to add: ");
            scanf("%d", &count);
            addSupplies(speciesSupplies, numSupplies, speciesIndex, count);
            break;
        }
        case 2: {
            int speciesIndex, supplyIndex;
            printf("Enter species index (1 to %d): ", numSpecies);
            scanf("%d", &speciesIndex);
            speciesIndex--; // Convert to 0-based index
            if (speciesIndex < 0 || speciesIndex >= numSpecies) {
                printf("Invalid species index.\n");
                break;
            }
            printf("Enter supply index (1 to %d): ", numSupplies[speciesIndex]);
            scanf("%d", &supplyIndex);
            supplyIndex--; // Convert to 0-based index
            updateSupply(speciesSupplies, numSupplies, speciesIndex, supplyIndex);
            break;
        }
        case 3: {
            int speciesIndex;
            printf("Enter species index (1 to %d): ", numSpecies);
            scanf("%d", &speciesIndex);
            speciesIndex--; // Convert to 0-based index
            removeSpecies(speciesSupplies, numSupplies, &numSpecies, speciesIndex);
            break;
        }
        case 4:
            displayInventory(speciesSupplies, numSupplies, numSpecies);
            break;
        case 5:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    // Free all allocated memory
    for (int i = 0; i < numSpecies; i++) {
        for (int j = 0; j < numSupplies[i]; j++) {
            free(speciesSupplies[i][j]);
        }
        free(speciesSupplies[i]);
    }
    free(speciesSupplies);
    free(numSupplies);

    return 0;
}
