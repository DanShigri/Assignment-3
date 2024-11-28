#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Content metadata structure
typedef struct {
    char title[100];
    float rating;         // Rating out of 5.0
    int runtime;          // Runtime in minutes
    char encodingFormats[50];  // Encoding formats (e.g., "HD, 4K, HDR")
} ContentMetadata;

// Device-specific preferences structure
typedef struct {
    char resolution[20];  // Resolution (e.g., "1080p", "4K")
    float bandwidthUsage; // Bandwidth usage in Mbps
    char playbackHistory[100]; // Description of playback history
} DevicePreferences;

// User profile structure
typedef struct {
    double* engagementScores;      // Pointer to user's engagement row in engagement matrix
    DevicePreferences** devices;   // Pointer to device preferences array
} UserProfile;

// Function to initialize the engagement matrix
double** initializeEngagementMatrix(int numUsers, int numCategories) {
    double** matrix = (double**)malloc(numUsers * sizeof(double*));
    for (int i = 0; i < numUsers; i++) {
        matrix[i] = (double*)malloc(numCategories * sizeof(double));
        for (int j = 0; j < numCategories; j++) {
            matrix[i][j] = 0.0; // Initialize engagement scores to 0
        }
    }
    return matrix;
}

// Function to initialize device matrix
DevicePreferences*** initializeDeviceMatrix(int numUsers, int numDevices) {
    DevicePreferences*** matrix = (DevicePreferences***)malloc(numUsers * sizeof(DevicePreferences**));
    for (int i = 0; i < numUsers; i++) {
        matrix[i] = (DevicePreferences**)malloc(numDevices * sizeof(DevicePreferences*));
        for (int j = 0; j < numDevices; j++) {
            matrix[i][j] = (DevicePreferences*)malloc(sizeof(DevicePreferences));
            strcpy(matrix[i][j]->resolution, "1080p");
            matrix[i][j]->bandwidthUsage = 5.0;
            strcpy(matrix[i][j]->playbackHistory, "No playback history");
        }
    }
    return matrix;
}

// Function to initialize content metadata
ContentMetadata*** initializeContentMetadata(int numCategories, int numContentPerCategory) {
    ContentMetadata*** metadata = (ContentMetadata***)malloc(numCategories * sizeof(ContentMetadata**));
    for (int i = 0; i < numCategories; i++) {
        metadata[i] = (ContentMetadata**)malloc(numContentPerCategory * sizeof(ContentMetadata*));
        for (int j = 0; j < numContentPerCategory; j++) {
            metadata[i][j] = (ContentMetadata*)malloc(sizeof(ContentMetadata));
            sprintf(metadata[i][j]->title, "Content_%d_%d", i + 1, j + 1);
            metadata[i][j]->rating = 4.5;
            metadata[i][j]->runtime = 120; // Default runtime
            strcpy(metadata[i][j]->encodingFormats, "HD, 4K");
        }
    }
    return metadata;
}

// Function to display engagement matrix
void displayEngagementMatrix(double** matrix, int numUsers, int numCategories) {
    printf("Engagement Matrix:\n");
    for (int i = 0; i < numUsers; i++) {
        printf("User %d: ", i + 1);
        for (int j = 0; j < numCategories; j++) {
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to display device preferences
void displayDevicePreferences(DevicePreferences*** matrix, int numUsers, int numDevices) {
    printf("\nDevice Preferences:\n");
    for (int i = 0; i < numUsers; i++) {
        printf("User %d:\n", i + 1);
        for (int j = 0; j < numDevices; j++) {
            printf("  Device %d: Resolution: %s, Bandwidth: %.2f Mbps, History: %s\n",
                   j + 1, matrix[i][j]->resolution, matrix[i][j]->bandwidthUsage, matrix[i][j]->playbackHistory);
        }
    }
}

// Function to display content metadata
void displayContentMetadata(ContentMetadata*** metadata, int numCategories, int numContentPerCategory) {
    printf("\nContent Metadata:\n");
    for (int i = 0; i < numCategories; i++) {
        printf("Category %d:\n", i + 1);
        for (int j = 0; j < numContentPerCategory; j++) {
            printf("  Title: %s, Rating: %.1f, Runtime: %d mins, Formats: %s\n",
                   metadata[i][j]->title, metadata[i][j]->rating, metadata[i][j]->runtime, metadata[i][j]->encodingFormats);
        }
    }
}

// Function to free the engagement matrix
void freeEngagementMatrix(double** matrix, int numUsers) {
    for (int i = 0; i < numUsers; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to free device matrix
void freeDeviceMatrix(DevicePreferences*** matrix, int numUsers, int numDevices) {
    for (int i = 0; i < numUsers; i++) {
        for (int j = 0; j < numDevices; j++) {
            free(matrix[i][j]);
        }
        free(matrix[i]);
    }
    free(matrix);
}

// Function to free content metadata
void freeContentMetadata(ContentMetadata*** metadata, int numCategories, int numContentPerCategory) {
    for (int i = 0; i < numCategories; i++) {
        for (int j = 0; j < numContentPerCategory; j++) {
            free(metadata[i][j]);
        }
        free(metadata[i]);
    }
    free(metadata);
}

// Main function
int main() {
    int numUsers = 2;
    int numCategories = 3;
    int numDevices = 2;
    int numContentPerCategory = 2;

    // Initialize structures
    double** engagementMatrix = initializeEngagementMatrix(numUsers, numCategories);
    DevicePreferences*** deviceMatrix = initializeDeviceMatrix(numUsers, numDevices);
    ContentMetadata*** contentMetadata = initializeContentMetadata(numCategories, numContentPerCategory);

    // Populate engagement matrix with sample data
    engagementMatrix[0][0] = 4.5;
    engagementMatrix[0][1] = 3.0;
    engagementMatrix[1][2] = 5.0;

    // Display data
    displayEngagementMatrix(engagementMatrix, numUsers, numCategories);
    displayDevicePreferences(deviceMatrix, numUsers, numDevices);
    displayContentMetadata(contentMetadata, numCategories, numContentPerCategory);

    // Free allocated memory
    freeEngagementMatrix(engagementMatrix, numUsers);
    freeDeviceMatrix(deviceMatrix, numUsers, numDevices);
    freeContentMetadata(contentMetadata, numCategories, numContentPerCategory);

    return 0;
}
