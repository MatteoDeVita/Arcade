/*
** EPITECH PROJECT, 2020
** $
** File description:
** lib_arcade_nibbler
*/

#include <fstream>
#include <error.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "lib_arcade_nibbler.hpp"

#define MAP_Y 25
#define MAP_X 81

LibNibbler::LibNibbler() {
    this->apple = (apple_t) {.x = 0, .y = 0, .is_eaten = 1};
    this->player.dirX = 1;
    this->player.dirY = 0;
    this->player.speed = 20;
    this->player.snakeLength = 4;
    this->player.snakeArray = init_snake_tab();
    this->score = 0;
    this->key = 0;
    this->str_int = (char*) malloc(sizeof(char)*1000);    
}

int **LibNibbler::init_snake_tab() {
    int **snakeArray = this->create_2dtab(100, 2);

    for (int y = 0; y < 100; y++) {
        for (int x = 0; x < 2; x++)
            snakeArray[y][x] = 0;
    }
    snakeArray[0][1] = 3;
    snakeArray[0][0] = 3;
    return (snakeArray);
}

int **LibNibbler::create_2dtab(int nb_cols, int nb_rows) {
    int **map = (int **) malloc(sizeof(int *) * nb_cols);

    for (int i = 0; i < nb_cols; i++)
        map[i] = (int *) malloc(sizeof(int) * nb_rows);
    return (map);
}

int LibNibbler::collision(int *snakeArray) {
    
    int x = *snakeArray;
    int y = *(snakeArray + 1);

    if (x > MAP_X - 2 || x < 1)
        return (1);
    else if (y < 1 || y > MAP_Y)
        return (1);
    for (int i = 2; i < this->player.snakeLength * 2 + 2; i += 2) {
        if (x == *(snakeArray+i) && y == *(snakeArray + i + 1))
            return (1);
    }
    return (0);
}

void LibNibbler::handle_apple_life() {
    if (this->apple.is_eaten) {
        srand(time(NULL));
        this->apple.y = (rand() % MAP_Y - 1) + 1;
        this->apple.x = (rand() % MAP_X - 1) + 1;
        this->apple.is_eaten = 0;
    }
}

void LibNibbler::move_Snake_Body(int *snakeArray, nibbler_player_t *player, int i) {
    player->oldX = player->nowX;
    player->oldY = player->nowY;
    player->nowX = *(snakeArray+i);
    player->nowY = *(snakeArray+i+1);
    *(snakeArray + i) = player->oldX;
    *(snakeArray + i + 1) = player->oldY;
    player->bodyX = *(snakeArray+i);
    player->bodyY = *(snakeArray+i+1);
}

void LibNibbler::move_snake_head(int *snakeArray) {
    
    this->player.oldX = 0;
    this->player.oldY = 0;
    this->player.nowX = *snakeArray;
    this->player.nowY = *(snakeArray + 1);

    *(snakeArray) = this->player.nowX + this->player.dirX;
    *(snakeArray+1) = this->player.nowY + this->player.dirY;
    this->player.headX = *(snakeArray) ;
    this->player.headY = *(snakeArray + 1);
    if (this->player.dirY != 0)
        usleep(500000 / this->player.speed);
    usleep(1000000 / this->player.speed);
}

int *LibNibbler::get_snake_array_ptr() { return &this->player.snakeArray[0][0]; }

void LibNibbler::eat_apple(int *snakeArray) {
    if (*snakeArray == this->apple.x && *(snakeArray+1) == this->apple.y) {
        this->apple.is_eaten = 1;
        this->score++;
        this->player.snakeLength += 1;
        *(snakeArray +  this->player.snakeLength * 2) = *(snakeArray + this->player.snakeLength * 2 - 2);
        *(snakeArray +  this->player.snakeLength * 2 + 1) = *(snakeArray + this->player.snakeLength * 2 - 2 + 1);
    }
}

char	*my_revstr(char *str)
{
  int	num;
  int	lenght;
  char	opmet;

  num = 0;
  lenght = strlen(str) - 1;
  while (num < lenght)
    {
      opmet = str[num];
      str[num] = str[lenght];
      str[lenght] = opmet;
      num++;
      lenght--;
    }
  return (str);
}

void LibNibbler::write_scores(const char *username)
{
    FILE *fd = fopen("./utils/score_nibbler.txt", "r");
    FILE *fd_write;
    int x = 0;
    int i = 0;
    char *str = (char*)malloc(sizeof(char) *1000);
    char *str2 = (char*)malloc(sizeof(char) *1000);
    
    if (fd != NULL){
        fgets(str, 30, fd);
        fclose(fd);
    }

    for(; str[x] != ':'; x++);
    for(x+=1; str[x] != '\0'; x++, i++)
        str2[i] = str[x];

    if(atoi(str2) < this->score) {
         fclose(fd);
        fd_write = fopen("./utils/score_nibbler.txt", "w+");
        if (fd_write != NULL) {
            fprintf(fd_write, "%s : %d\n", username,  this->score);
            fclose(fd_write);
        }
    }
    free(str);
    free(str2);
}

apple_t LibNibbler::get_apple() { return this->apple; }

nibbler_player_t LibNibbler::get_player() { return this->player; }

nibbler_player_t *LibNibbler::get__player_ptr() { return &this->player; }

int LibNibbler::kbhit() {
    struct timeval tv = {0,0};
    fd_set read_fd;
    
    FD_ZERO(&read_fd);
    FD_SET(0, &read_fd);
    if (FD_ISSET(0,&read_fd))
        return (1);
    if (select(1, &read_fd, NULL, NULL, &tv) == -1)
        return (0);
    return (0);
}

void LibNibbler::handle_input_pressed(int key) {
    if (!(this->player.dirY == 0 && this->player.dirX == 1) && key == arcade::Input::LEFT_ARROW) {
        this->player.dirY = 0;
        this->player.dirX = -1;
    }
    if (!(this->player.dirY == 0 && this->player.dirX == -1) && key == arcade::Input::RIGHT_ARROW) {
        this->player.dirY = 0;
        this->player.dirX = 1;
    }
    if (!(this->player.dirY == 1 && this->player.dirX == 0) && key == arcade::Input::UP_ARROW) {
        this->player.dirY = -1;
        this->player.dirX = 0;
    }   
    if (!(this->player.dirY == -1 && this->player.dirX == 0) && key ==  arcade::Input::DOWN_ARROW ) {
        this->player.dirY = 1;
        this->player.dirX = 0;
    }
}

