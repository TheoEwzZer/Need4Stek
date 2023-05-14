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
        0.45f, 0.4f, 0.35f, 0.3f, 0.25f, 0.20f, 0.15f, 0.10f, 0.05f, 0.01f
    };
    int distance[9] = {100, 200, 300, 400, 500, 600, 1020, 1350, 1700};

    for (unsigned int i = 0; car->right > car->left && i < 9; i++) {
        if (car->middle < distance[i] && car->middle_right < distance[i])
            return -wheels_dir_values[i];
    }
    if (car->right > car->left)
        return -wheels_dir_values[9];
    for (unsigned int i = 0; i < 9; i++) {
        if (car->middle < distance[i] && car->middle_left < distance[i])
            return wheels_dir_values[i];
    }
    return wheels_dir_values[9];
}

float calculate_speed(car_t *car)
{
    float speed[9] = {1.0f, 0.9f, 0.8f, 0.7f, 0.6f, 0.5f, 0.4f, 0.3f, 0.1f};
    int speed_indicator_mid[8] = {2000, 1500, 1000, 800, 600, 400, 200, 100};

    for (unsigned int i = 0; i < 8; i++) {
        if (car->middle > speed_indicator_mid[i]
            && car->middle_left > speed_indicator_mid[i]
            && car->middle_right > speed_indicator_mid[i])
            return speed[i];
    }
    return speed[8];
}

void avoid_wall(car_t *car)
{
    float wheels_dir = 0.0f;
    char lineptr[100];

    for (unsigned int i = 0; i < 32; i++) {
        if (car->lidar[i] < 110.0f) {
            write(STDOUT_FILENO, "CAR_FORWARD:0.00\n", 17);
            fgets(lineptr, 100, stdin);
            write(STDOUT_FILENO, "CAR_BACKWARDS:0.5f\n", 19);
            fgets(lineptr, 100, stdin);
            wheels_dir = (car->right > car->left) ? 0.5f : -0.5f;
            dprintf(STDOUT_FILENO, "WHEELS_DIR:%.2f\n", (double)wheels_dir);
            fgets(lineptr, 100, stdin);
            return;
        }
    }
}

void control_car(car_t *car)
{
    char lineptr[100];
    float speed = 0.0f;
    float wheels_dir = 0.0f;

    avoid_wall(car);
    speed = calculate_speed(car);
    wheels_dir = calculate_wheels_direction(car);
    if (speed != car->current_speed) {
        dprintf(STDOUT_FILENO, "CAR_FORWARD:%.1f\n", (double)speed);
        fgets(lineptr, 100, stdin);
        car->current_speed = speed;
    }
    if (wheels_dir != car->current_wheels_direction) {
        dprintf(STDOUT_FILENO, "WHEELS_DIR:%.2f\n", (double)wheels_dir);
        fgets(lineptr, 100, stdin);
        car->current_wheels_direction = wheels_dir;
    }
}
