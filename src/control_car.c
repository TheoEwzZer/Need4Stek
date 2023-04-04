/*
** EPITECH PROJECT, 2023
** need4stek
** File description:
** need4stek
*/

#include "need4stek.h"

float calculate_wheels_direction(car_t *car)
{
    float wheels_dir_values[6] = {0.25f, 0.20f, 0.15f, 0.10f, 0.05f, 0.01f};
    int distance[5] = {400, 500, 700, 1020, 1350};

    for (unsigned int i = 0; car->right > car->left && i < 5; i++) {
        if (car->middle < distance[i])
            return -wheels_dir_values[i];
    }
    if (car->right > car->left)
        return -wheels_dir_values[5];
    for (unsigned int i = 0; i < 5; i++) {
        if (car->middle < distance[i])
            return wheels_dir_values[i];
    }
    return wheels_dir_values[5];
}

float calculate_speed(car_t *car)
{
    float speed[9] = {1.0f, 0.9f, 0.8f, 0.7f, 0.6f, 0.5f, 0.4f, 0.3f, 0.1f};
    int speed_indicator_mid[8] = {2500, 2000, 1500, 1000, 500, 400, 300, 100};

    for (unsigned int i = 0; i < 8; i++)
        if (car->middle > speed_indicator_mid[i]) {
            return speed[i];
    }
    return speed[8];
}

void control_car(car_t *car)
{
    char *lineptr = NULL;
    float speed = calculate_speed(car);
    float wheels_dir = calculate_wheels_direction(car);
    size_t n = 0;

    if (speed != car->current_speed) {
        dprintf(STDOUT_FILENO, "CAR_FORWARD:%.1f\n", (double)speed);
        getline(&lineptr, &n, stdin);
        car->current_speed = speed;
    }
    if (wheels_dir != car->current_wheels_direction) {
        dprintf(STDOUT_FILENO, "WHEELS_direction:%.2f\n", (double)wheels_dir);
        getline(&lineptr, &n, stdin);
        car->current_wheels_direction = wheels_dir;
    }
}
