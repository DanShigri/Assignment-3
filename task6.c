#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Structures

typedef struct {
    float temperature;  // Temperature in Celsius
    float rainfall;     // Rainfall in mm
    float windSpeed;    // Wind speed in km/h
} WeatherForecast;

typedef struct {
    char type[50];               // Crop type (e.g., wheat, corn)
    char growthStage[50];        // Growth stage (e.g., germination, maturity)
    float expectedYield;         // Expected yield in kg/hectare
    WeatherForecast* weather;    // Pointer to a weather forecast
} Crop;

typedef struct {
    char name[50];         // Equipment name (e.g., tractor, drone)
    char status[50];       // Operational status (e.g., active, idle)
    float fuelLevel;       // Fuel level as a percentage
    char schedule[100];    // Activity schedule description
} Equipment;

typedef struct {
    float soilNutrients;   // Soil nutrients level
    float pHLevel;         // pH level of the soil
    float pestActivity;    // Pest activity level (scale 0-100)
} Sensor;

typedef struct {
    float latitude;                // Latitude of the field
    float longitude;               // Longitude of the field
    float soilHealth;              // Soil health metric
    float moistureLevel;           // Soil moisture level
    int numCrops;                  // Number of crops in the field
    Crop* crops;                   // Pointer to an array of crops
    int numEquipments;             // Number of equipment in the field
    Equipment* equipments;         // Pointer to an array of equipment
    int numSensors;                // Number of sensors in the field
    Sensor* sensors;               // Pointer to an array of sensors
} Field;

typedef struct {
    char regionName[50];      // Name of the regional hub
    int numFields;            // Number of fields in the region
    Field* fields;            // Pointer to an array of fields
} RegionalHub;

typedef struct {
    int numHubs;                  // Number of regional hubs
    RegionalHub* hubs;            // Pointer to an array of regional hubs
} CentralAnalyticsServer;

// Function to initialize the Central Analytics Server
CentralAnalyticsServer* initializeServer(int numHubs) {
    CentralAnalyticsServer* server = (CentralAnalyticsServer*)malloc(sizeof(CentralAnalyticsServer));
    if (!server) {
        perror("Failed to allocate memory for server");
        exit(EXIT_FAILURE);
    }
    server->numHubs = numHubs;
    server->hubs = (RegionalHub*)malloc(numHubs * sizeof(RegionalHub));
    if (!server->hubs) {
        perror("Failed to allocate memory for hubs");
        free(server);
        exit(EXIT_FAILURE);
    }
    return server;
}

// Function to initialize a Regional Hub
void initializeRegionalHub(RegionalHub* hub, const char* name, int numFields) {
    strcpy(hub->regionName, name);
    hub->numFields = numFields;
    hub->fields = (Field*)malloc(numFields * sizeof(Field));
    if (!hub->fields) {
        perror("Failed to allocate memory for fields");
        exit(EXIT_FAILURE);
    }
}

// Function to initialize a Field
void initializeField(Field* field, int numCrops, int numEquipments, int numSensors) {
    field->crops = (Crop*)malloc(numCrops * sizeof(Crop));
    field->equipments = (Equipment*)malloc(numEquipments * sizeof(Equipment));
    field->sensors = (Sensor*)malloc(numSensors * sizeof(Sensor));

    if (!field->crops || !field->equipments || !field->sensors) {
        perror("Failed to allocate memory for field components");
        exit(EXIT_FAILURE);
    }

    field->numCrops = numCrops;
    field->numEquipments = numEquipments;
    field->numSensors = numSensors;
}

// Function to display all data
void displayData(CentralAnalyticsServer* server) {
    printf("Central Analytics Server\n");
    printf("=========================\n");

    for (int i = 0; i < server->numHubs; i++) {
        RegionalHub* hub = &server->hubs[i];
        printf("Regional Hub: %s\n", hub->regionName);
        printf("-----------------------------\n");

        for (int j = 0; j < hub->numFields; j++) {
            Field* field = &hub->fields[j];
            printf("  Field %d:\n", j + 1);
            printf("    GPS: (%.2f, %.2f)\n", field->latitude, field->longitude);
            printf("    Soil Health: %.2f\n", field->soilHealth);
            printf("    Moisture Level: %.2f\n", field->moistureLevel);

            printf("    Crops:\n");
            for (int k = 0; k < field->numCrops; k++) {
                Crop* crop = &field->crops[k];
                printf("      Crop %d: %s, Stage: %s, Yield: %.2f\n", 
                       k + 1, crop->type, crop->growthStage, crop->expectedYield);
                if (crop->weather) {
                    printf("        Weather: Temp %.2f, Rain %.2f, Wind %.2f\n", 
                           crop->weather->temperature, crop->weather->rainfall, crop->weather->windSpeed);
                }
            }

            printf("    Equipment:\n");
            for (int k = 0; k < field->numEquipments; k++) {
                Equipment* equip = &field->equipments[k];
                printf("      Equipment %d: %s, Status: %s, Fuel: %.2f%%\n", 
                       k + 1, equip->name, equip->status, equip->fuelLevel);
            }

            printf("    Sensors:\n");
            for (int k = 0; k < field->numSensors; k++) {
                Sensor* sensor = &field->sensors[k];
                printf("      Sensor %d: Nutrients %.2f, pH %.2f, Pest %.2f\n", 
                       k + 1, sensor->soilNutrients, sensor->pHLevel, sensor->pestActivity);
            }
        }
        printf("\n");
    }
}

// Function to free all allocated memory
void freeServer(CentralAnalyticsServer* server) {
    for (int i = 0; i < server->numHubs; i++) {
        RegionalHub* hub = &server->hubs[i];
        for (int j = 0; j < hub->numFields; j++) {
            Field* field = &hub->fields[j];
            for (int k = 0; k < field->numCrops; k++) {
                free(field->crops[k].weather);
            }
            free(field->crops);
            free(field->equipments);
            free(field->sensors);
        }
        free(hub->fields);
    }
    free(server->hubs);
    free(server);
}

// Main Function
int main() {
    // Initialize Server
    int numHubs = 1;
    CentralAnalyticsServer* server = initializeServer(numHubs);

    // Initialize Regional Hub
    initializeRegionalHub(&server->hubs[0], "North Region", 1);

    // Initialize Field
    initializeField(&server->hubs[0].fields[0], 1, 1, 1);
    Field* field = &server->hubs[0].fields[0];

    field->latitude = 45.12;
    field->longitude = -93.5;
    field->soilHealth = 80.5;
    field->moistureLevel = 40.0;

    // Add Crop Data
    strcpy(field->crops[0].type, "Corn");
    strcpy(field->crops[0].growthStage, "Mature");
    field->crops[0].expectedYield = 2000.0;
    field->crops[0].weather = (WeatherForecast*)malloc(sizeof(WeatherForecast));
    field->crops[0].weather->temperature = 25.0;
    field->crops[0].weather->rainfall = 30.0;
    field->crops[0].weather->windSpeed = 15.0;

    // Add Equipment Data
    strcpy(field->equipments[0].name, "Tractor");
    strcpy(field->equipments[0].status, "Active");
    field->equipments[0].fuelLevel = 85.0;

    // Add Sensor Data
    field->sensors[0].soilNutrients = 55.0;
    field->sensors[0].pHLevel = 6.5;
    field->sensors[0].pestActivity = 10.0;

    // Display Data
    displayData(server);

    // Free Memory
    freeServer(server);

    return 0;
}
