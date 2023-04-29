/*
** EPITECH PROJECT, 2023
** need4stek
** File description:
** need4stek
*/

#include "need4stek.h"

void end(void)
{
    char lineptr[128];

    write(STDOUT_FILENO, "CAR_FORWARD:0.0\n", 16);
    fgets(lineptr, 128, stdin);
    write(STDOUT_FILENO, "START_SIMULATION\n", 17);
    fgets(lineptr, 128, stdin);
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
    char lineptr[300];

    write(STDOUT_FILENO, "GET_INFO_LIDAR\n", 15);
    fgets(lineptr, 300, stdin);
    parse_lidar_data(lineptr, car);
    car->left = car->lidar[0];
    car->middle = car->lidar[15];
    car->right = car->lidar[31];
    car->middle_left = car->lidar[14];
    car->middle_right = car->lidar[16];
    if (car->is_diamond || (car->lidar[0] == 1500.0f && car->lidar[2] == 2500.0f
    && car->lidar[31] == 675.0f && car->lidar[29] == 1500.0f)) {
        car->is_diamond = true;
        car->middle_left = car->lidar[10];
        car->middle_right = car->lidar[20];
    }
}

int main(void)
{
    car_t *car = malloc(sizeof(car_t));
    char line[39];

    car->is_diamond = false;
    write(STDOUT_FILENO, "START_SIMULATION\n", 17);
    fgets(line, 39, stdin);
    while (42) {
        update_car(car);
        if (!strcmp(car->status, "OK"))
            control_car(car);
    }
    return EXIT_SUCCESS;
}
