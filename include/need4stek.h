/*
** EPITECH PROJECT, 2023
** need4stek.h
** File description:
** need4stek
*/

#ifndef NEED4STEK_H_

    #define NEED4STEK_H_

    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

typedef struct car_s {
    char *status;
    float current_speed;
    float current_wheels_direction;
    float left;
    float lidar[32];
    float middle;
    float right;
} car_t;

float calculate_speed(car_t *car);
float calculate_wheels_direction(car_t *car);
void check_end(car_t *car);
void control_car(car_t *car);
void end(void) __attribute__((noreturn));
void parse_lidar_data(char *line, car_t *car);
void update_car(car_t *car);

#endif /* NEED4STEK_H_ */
