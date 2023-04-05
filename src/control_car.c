/*
** EPITECH PROJECT, 2023
** need4stek
** File description:
** need4stek
*/

#include "need4stek.h"

float calculate_wheels_direction(car_t *car)
{
    float wheels_dir_values[10] = {
        0.45f, 0.4f, 0.35f, 0.3f, 0.25f, 0.20f, 0.15f, 0.10f, 0.05f, 0.0f
    };
    int distance[9] = {100, 200, 300, 400, 500, 700, 1020, 1350, 1700};

    for (unsigned int i = 0; car->right > car->left && i < 9; i++) {
        if (car->middle < distance[i])
            return -wheels_dir_values[i];
    }
    if (car->right > car->left)
        return -wheels_dir_values[9];
    for (unsigned int i = 0; i < 9; i++) {
        if (car->middle < distance[i])
            return wheels_dir_values[i];
    }
    return wheels_dir_values[9];
}

float calculate_speed(car_t *car)
{
    float speed[9] = {1.0f, 0.9f, 0.8f, 0.7f, 0.6f, 0.5f, 0.4f, 0.3f, 0.1f};
    int speed_indicator_mid[8] = {2000, 1500, 1000, 800, 600, 400, 200, 100};

    for (unsigned int i = 0; i < 8; i++) {
        if (car->middle > speed_indicator_mid[i])
            return speed[i];
    }
    return speed[8];
}

void check_end(car_t *car)
{
    bool can_stop = true;

    for (unsigned int i = 0; i < 32; i++) {
        if (car->lidar[i] > 100.0f) {
            can_stop = false;
            break;
        }
    }
    if (can_stop)
        end();
}

void control_car(car_t *car)
{
    char *lineptr = NULL;
    float speed = calculate_speed(car);
    float wheels_dir = calculate_wheels_direction(car);
    size_t n = 0;

    check_end(car);
    if (speed != car->current_speed) {
        dprintf(STDOUT_FILENO, "CAR_FORWARD:%.1f\n", (double)speed);
        getline(&lineptr, &n, stdin);
        car->current_speed = speed;
    }
    if (wheels_dir != car->current_wheels_direction) {
        dprintf(STDOUT_FILENO, "WHEELS_DIR:%.2f\n", (double)wheels_dir);
        getline(&lineptr, &n, stdin);
        car->current_wheels_direction = wheels_dir;
    }
}
