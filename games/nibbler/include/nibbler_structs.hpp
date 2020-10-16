/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** matrix_struct
*/

#pragma once

typedef struct nibbler_player {
    int dirX;
    int dirY;
    int speed;
    int snakeLength;
    int headX;
    int headY;
    int bodyX;
    int bodyY;
    int oldX;
    int oldY;
    int nowX;
    int nowY;
    int **snakeArray;
} nibbler_player_t;

typedef struct apple
{
    int x;
    int y;
    int is_eaten;
} apple_t;
