/*
** EPITECH PROJECT, 2023
** need4stek
** File description:
** need4stek
*/

#include "need4stek.h"

void end(void)
{
    char *lineptr = NULL;
    size_t n = 0;

    dprintf(STDOUT_FILENO, "CAR_FORWARD:0.0\n");
    getline(&lineptr, &n, stdin);
    sleep(1);
    dprintf(STDOUT_FILENO, "STOP_SIMULATION\n");
    getline(&lineptr, &n, stdin);
    exit(0);
}

void parse_lidar_data(char *line, car_t *car)
{
    char *token = strtok(line, ":");
    unsigned int value_id = (unsigned int)atoi(token);

    if (value_id != 1 && value_id != 2 && value_id != 10)
        end();
    for (unsigned int i = 0; i < 3; i++) {
        if (i == 1)
            car->status = strdup(token);
        token = strtok(NULL, ":");
    }
    for (unsigned int i = 0; i < 32; i++) {
        car->lidar[i] = (float)atof(token);
        token = strtok(NULL, ":");
    }
    if (!strcmp(token, "Track Cleared"))
        end();
}

void update_car(car_t *car)
{
    char *lineptr = NULL;
    size_t n = 0;

    write(STDOUT_FILENO, "GET_INFO_LIDAR\n", 15);
    getline(&lineptr, &n, stdin);
    parse_lidar_data(lineptr, car);
    car->left = car->lidar[0];
    car->middle = car->lidar[15];
    car->right = car->lidar[31];
    free(lineptr);
}

int main(void)
{
    car_t *car = malloc(sizeof(car_t));
    char *lineptr = NULL;
    size_t n = 0;

    write(STDOUT_FILENO, "START_SIMULATION\n", 17);
    getline(&lineptr, &n, stdin);
    free(lineptr);
    while (42) {
        update_car(car);
        if (!strcmp(car->status, "OK"))
            control_car(car);
    }
    return EXIT_SUCCESS;
}
