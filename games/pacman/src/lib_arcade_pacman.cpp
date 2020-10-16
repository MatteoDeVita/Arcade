/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** lib_arcade_pacman
*/

#include "lib_arcade_pacman.hpp"
#include "../../../lib/lib_arcade_ncurses/include/lib_arcade_ncurses.hpp"

#include <iostream>
#include <math.h>


void LibPacman::write_scores(const char *username)
{
    FILE *fd = fopen("./utils/score_pacman.txt", "r");
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
    for(x+=1; str[x] != '\0'; x++, i++) {
        str2[i] = str[x];
    }
    if(atoi(str2) < this->score) {
        fclose(fd);
        fd_write = fopen("./utils/score_pacman.txt", "w+");
        if (fd_write != NULL) {
            fprintf(fd_write, "%s : %d\n", username,  this->score);
            fclose(fd_write);
        }
    }
    free(str);
    free(str2);
}

LibPacman::LibPacman() {
    srand(time(NULL));
    this->score = 0;
    this->nb_cols = 25;
    this->nb_rows = 31;
    this->door_status = 1;
    this->active_direction = {0, 0, 0, 0};
    this->ghost1 = {14, 12, 0.5, 1};
    this->ghost2 = {16, 12, 0.5, 1};
    this->init_map();
    this->c_update = clock();
    this->c_player_speed = clock();
    this->c_start_boost_effect_time = clock();
    this->ghost_speed_clock = clock();
    this->spwan_ghost_clock = clock();
    this->playerspeed = 0.1;
    this->player.speed = this->playerspeed;    
    this->player.big_pacball_effect = 0;
}

void LibPacman::init_map() {
    this->map = this->create_2dtab();

    /*countour remplisage*/
    for (int y = 0; y != this->nb_cols; y++) {
        for (int i = 0; i != this->nb_rows; i++) {
            this->map[y][i] = '#';
        }
    }
    /*interieur vide*/
    for (int y = 1; y != this->nb_cols - 1; y++) {
        for (int i = 1; i != this->nb_rows - 1; i++) {
            this->map[y][i] = '.';
        }
    }
    //GROS carre middle remplissage

    for (int y = 8; y != this->nb_cols - 8; y++) {
        for (int i = 8; i != this->nb_rows - 8; i++) {
            this->map[y][i] = '#';
        }
    }
    //GROS carre middle vide interieur
   for (int y = 10; y != this->nb_cols - 9; y++) {
        for (int i = 12; i != this->nb_rows - 12; i++) {
            this->map[y][i] = '.';
        }
    }
    this->map[12][8] = '.';
    this->map[12][9] = '.';
    this->map[12][10] = '.';
    this->map[12][11] = '.';
    this->map[12][19] = '.';
    this->map[12][20] = '.';
    this->map[12][21] = '.';
    this->map[12][22] = '.';
    //MOYEN carre middle remplissage

    for (int y = 11; y != this->nb_cols - 10; y++) {
        for (int i = 13; i != this->nb_rows - 13; i++) {
            this->map[y][i] = '#';
        }
    }
    //MOYEN carre middle vide interieur
  for (int y = 12; y != this->nb_cols - 11; y++) {
        for (int i = 14; i != this->nb_rows - 14; i++) {
            this->map[y][i] = ' ';
        }
    }
    
        /*carre haut gauche*/
    for (int y = 2; y != this->nb_cols - 18; y++) {
        for (int i = 2; i != this->nb_rows - 16; i++) {
            this->map[y][i] = '#';
        }
    }
        /*carre haut droite*/
    for (int y = 2; y != this->nb_cols - 18; y++) {
        for (int i = 16; i != this->nb_rows - 2; i++) {
            this->map[y][i] = '#';
        }
    }
    /*carre bas gauche*/
    for (int y = 18; y != this->nb_cols - 2; y++) {
        for (int i = 2; i != this->nb_rows - 16; i++) {
            this->map[y][i] = '#';
        }
    }
    /*carre bas droite*/
    for (int y = 18; y != this->nb_cols - 2; y++) {
        for (int i = 16; i != this->nb_rows - 2; i++) {
            this->map[y][i] = '#';
        }
    }

    /*left square*/
    for (int y = 8; y != this->nb_cols - 8; y++) {
        for (int i = 2; i != this->nb_rows - 24; i++) {
            this->map[y][i] = '#';
        }
    }

    /*middle empty left square*/
    this->map[12][2] = '.';
    this->map[12][3] = '.';
    this->map[12][4] = '.';
    this->map[12][5] = '.';
    this->map[12][6] = '.';

    /*right square*/
    for (int y = 8; y != this->nb_cols - 8; y++) {
        for (int i = 24; i != this->nb_rows - 2; i++) {
            this->map[y][i] = '#';
        }
    }

    /*middle empty right square*/
    this->map[12][24] = '.';
    this->map[12][25] = '.';
    this->map[12][26] = '.';
    this->map[12][27] = '.';
    this->map[12][28] = '.';

    /*big pacballs*/
    this->map[23][29] = 'O';
    this->map[23][1] = 'O';
    this->map[1][1] = 'O';
    this->map[1][29] = 'O';

    /*player*/
    this->map[17][15] = 'P';
}

char **LibPacman::create_2dtab() {
    char **map = (char **) malloc(sizeof(char *) * this->nb_cols);

    for (int i = 0; i < this->nb_cols; i++)
        map[i] = (char *) malloc(sizeof(char) * this->nb_rows);
    return (map);
}

int LibPacman::spot_win() {
    for (int y = 0; y != this->nb_cols; y++) {
        for (int x = 0; x != this->nb_rows; x++) {
            if (this->map[y][x] == '.' || this->map[y][x] == 'O')
                return (1);
        }
    }
    return (-1);
}

void LibPacman::update_time() {
    this->c_update = clock();
    this->time_player = ((double) (this->c_update - this->c_player_speed) / CLOCKS_PER_SEC);
    this->ghost_door_timer = ((double) (this->c_update - this->spwan_ghost_clock) / CLOCKS_PER_SEC);
    this->time_boost = ((double) (this->c_update - this->c_start_boost_effect_time) / CLOCKS_PER_SEC);
    this->ghost_speed = ((double) (this->c_update - this->ghost_speed_clock) / CLOCKS_PER_SEC);
}

int LibPacman::get_nb_cols() { return this->nb_cols; }

int LibPacman::get_nb_rows() { return this->nb_rows; }

char **LibPacman::get_map() { return this->map; }

int LibPacman::get_door_status() { return this->door_status; }

void LibPacman::open_ghost_door() {
    if (fmod(this->ghost_door_timer, 10) >= 9) {
        this->map[11][14] = ' ';
        this->map[11][15] = ' ';
        this->map[11][16] = ' ';
        this->door_status = 0;
    }
}

void LibPacman::find_player() {
    int x = 0;

    for (int y = 0; y != this->nb_cols; y++) {
        x = 0;
        while (x != this->nb_rows) {
            if (this->map[y][x] == 'P') {
                this->player.x = x;
                this->player.y = y;
                return;
            }
        x++;
        }
    }
}

void LibPacman::active_direction_func(int key) {
    if (key != arcade::Input::NONE) {
        if (key == arcade::Input::UP_ARROW) {
            this->active_direction.up = 1;
            this->active_direction.down = 0;
            this->active_direction.left = 0;
            this->active_direction.right = 0;
        }
        if (key == arcade::Input::DOWN_ARROW) {
            this->active_direction.down = 1;
            this->active_direction.left = 0;
            this->active_direction.right = 0;
            this->active_direction.up = 0;
        }
        if (key == arcade::Input::LEFT_ARROW) {
            this->active_direction.left = 1;
            this->active_direction.right = 0;
            this->active_direction.up = 0;
            this->active_direction.down = 0;
        }
        if (key == arcade::Input::RIGHT_ARROW) {
            this->active_direction.right = 1;
            this->active_direction.up = 0;
            this->active_direction.down = 0;
            this->active_direction.left = 0;
        }
    }
}

double LibPacman::get_time_player() { return this->time_player; }

player_t LibPacman::get_player() { return this->player; }

void LibPacman::update_player() {
    this->active_player_movement();
    this->c_player_speed = clock();
}

void LibPacman::active_player_movement() {
    if (this->active_direction.right) {
        right_key_action();
        return;
    }
    if (this->active_direction.left) {
        left_key_action();
        return;
    }
    if (this->active_direction.up) {
        up_key_action();
        return;
    }
    if (this->active_direction.down) {
        down_key_action();
        return;
    }
}

void LibPacman::right_key_action() {
    int x = this->player.x;
    int y = this->player.y;

    if (this->map[y][x + 1] == '.') {
        this->map[y][x + 1] = 'P';
        this->map[y][x] = ' ';
        this->score++;
    }
    else if (this->map[y][x + 1] == ' ') {
        this->map[y][x + 1] = 'P';
        this->map[y][x] = ' ';
    }
    else if (this->map[y][x + 1] == 'O') {
        this->map[y][x + 1] = 'P';
        this->map[y][x] = ' ';
        this->player.speed = 0.04;
        this->player.big_pacball_effect = 1;
    }
    else if ((this->map[y][x + 1] == 'g' || this->map[y][x + 1] == 'G')&& this->player.big_pacball_effect == 1) {
        this->map[y][x + 1]   = 'P';
        this->map[y][x] = ' ';
    }
}

void LibPacman::left_key_action() {
    int x = this->player.x;
    int y = this->player.y;

    if (this->map[y][x - 1] == '.') {
        this->map[y][x - 1] = 'P';
        this->map[y][x] = ' ';
        this->score++;
    }
    else if (this->map[y][x - 1] == ' ') {
        this->map[y][x - 1] = 'P';
        this->map[y][x] = ' ';
    }
    else if (this->map[y][x - 1] == 'O') {
        this->map[y][x - 1] = 'P';
        this->map[y][x] = ' ';
        this->player.speed = 0.04;
        this->player.big_pacball_effect = 1;
    }
    else if ((this->map[y][x - 1] == 'g' || this->map[y][x - 1] == 'G') && this->player.big_pacball_effect == 1) {
        this->map[y][x - 1]   = 'P';
        this->map[y][x] = ' ';
    }
}

void LibPacman::down_key_action() {
    int x = this->player.x;
    int y = this->player.y;

    if (this->map[y + 1][x] == '.') {
        this->map[y + 1][x] = 'P';
        this->map[y][x] = ' ';
        this->score++;
    }
    else if (this->map[y + 1][x] == ' ') {
        this->map[y + 1][x] = 'P';
        this->map[y][x] = ' ';
    }
    else if (this->map[y + 1][x] == 'O') {
        this->map[y + 1][x] = 'P';
        this->map[y][x] = ' ';
        this->player.speed = 0.04;
        this->player.big_pacball_effect = 1;
    }
    else if ((this->map[y + 1][x] == 'g' || this->map[y + 1][x] == 'G') && this->player.big_pacball_effect == 1) {
        this->map[y + 1][x]  = 'P';
        this->map[y][x] = ' ';
    }
}

void LibPacman::up_key_action() {
    int x = this->player.x;
    int y = this->player.y;

    if (this->map[y - 1][x] == '.') {
        this->map[y - 1][x] = 'P';
        this->map[y][x] = ' ';
        this->score++;
    }
    else if (this->map[y - 1][x] == ' ') {
        this->map[y - 1][x] = 'P';
        this->map[y][x] = ' ';
    }
    else if (this->map[y - 1][x] == 'O') {
        this->map[y - 1][x] = 'P';
        this->map[y][x] = ' ';
        this->player.speed = 0.04;
        this->player.big_pacball_effect = 1;
    }
    else if ((this->map[y - 1][x] == 'g' || this->map[y - 1][x] == 'G')&& this->player.big_pacball_effect == 1) {
        this->map[y - 1][x] = 'P';
        this->map[y][x] = ' ';
    }
}

void LibPacman::close_ghost_door_after_spawn() {
    if((this->ghost1.y <= 10 || (this->ghost1.y >= 15 && this->ghost1.x <= 12) || this->ghost1.x >= 18)
    && (this->ghost2.y <= 10 || (this->ghost2.y >= 15 && this->ghost2.x <= 12) || this->ghost2.x >= 18)) {
        this->map[11][14] = '#';
        this->map[11][15] = '#';
        this->map[11][16] = '#';
        this->door_status = 0;
    }
}

void LibPacman::handle_player_super_mode() {
    if (this->player.big_pacball_effect == 1) {
        if (fmod(this->time_boost, 10) >= 9) {
            this->player.big_pacball_effect = 0;
            this->player.speed = playerspeed;
            this->ghost1.speed = 0.3;
            this->ghost2.speed = 0.3;
            this->c_start_boost_effect_time = clock();
        }
    }
}

int LibPacman::handle_ghost() {
    if (fmod(this->ghost_speed, this->ghost1.speed) >= 0.2) {
        if (this->ghost_move_ia1() == -1 || this->ghost_move_ia2() == -1)
            return -1;
        this->ghost_speed_clock = clock();
    }
    //if player eat a ghost
    if(this->ghost1.x == this->player.x && this->ghost1.y == this->player.y && this->player.big_pacball_effect == 1) {
        this->ghost1.x = 14;
        this->ghost1.y = 12;
        this->door_status = 1;
        this->ghost_door_timer = 0;
    }
    if(this->ghost2.x == this->player.x && this->ghost2.y == this->player.y && this->player.big_pacball_effect == 1) {
        this->ghost2.x = 16;
        this->ghost2.y = 12;
        this->door_status = 1;
        this->ghost_door_timer = 0;
    }
    return 0;
}

int LibPacman::random_nb(int max, int min) {
    return (rand() % (max - min) + min);
}

int LibPacman::right_ghost(struct ghost *ghost, int *move_order) {
    int x = ghost->x;
    int y = ghost->y;

    if (map[y][x + 1] == '.') {
        map[y][x + 1] = this->player.big_pacball_effect ? 'G' : 'g';
        map[y][x] = '.';
        ghost->x  = ghost->x + 1;
        *move_order = 4;
        return (1);
    }
    else if (map[y][x + 1]== 'O') {
        map[y][x + 1] = this->player.big_pacball_effect ? 'G' : 'g';
        map[y][x] = 'O';
        ghost->x  = ghost->x + 1;
        *move_order = 4;
        return (1);
    }
    else if (map[y][x + 1]== ' ') {
        map[y][x + 1] = this->player.big_pacball_effect ? 'G' : 'g';
        map[y][x] = ' ';
        ghost->x  = ghost->x + 1;
        *move_order = 4;
        return (1);
    }
    else if (map[y][x + 1] == 'g' || map[y][x + 1] == 'G'){
        return (0);
    }
    else if (map[y][x + 1] == 'P' && this->player.big_pacball_effect == 0){
        return -1;
    }
    return (0);
}

int LibPacman::left_ghost(struct ghost *ghost, int *move_order) {
    int x = ghost->x;
    int y = ghost->y;

    if (map[y][x - 1] == '.') {
        map[y][x - 1] = this->player.big_pacball_effect ? 'G' : 'g';
        map[y][x] = '.';
        ghost->x  = ghost->x - 1;
        *move_order = 3;
        return (1);
    }
    else if (map[y][x - 1]== 'O') {
        map[y][x - 1] = this->player.big_pacball_effect ? 'G' : 'g';
        map[y][x] = 'O';
        ghost->x  = ghost->x - 1;
        *move_order = 3;
        return (1);
    }
    else if (map[y][x - 1]== ' ') {
        map[y][x - 1] = this->player.big_pacball_effect ? 'G' : 'g';
        map[y][x] = ' ';
        ghost->x  = ghost->x - 1;
        *move_order = 3;
        return (1);
    }
    else if (map[y][x - 1] == 'g' || map[y][x - 1] == 'G'){
        return (0);
    }
    else if (map[y][x - 1] == 'P' && this->player.big_pacball_effect == 0){
        return -1;
    }
    return (0);
}

int LibPacman::down_ghost(struct ghost *ghost, int *move_order) {
    int x = ghost->x;
    int y = ghost->y;

    if (map[y + 1][x] == '.') {
        map[y + 1][x] = this->player.big_pacball_effect ? 'G' : 'g';
        map[y][x] = '.';
        ghost->y  = ghost->y + 1;
        *move_order = 2;
        return (1);
    }
    else if (map[y + 1][x] == 'O') {
        map[y + 1][x] = this->player.big_pacball_effect ? 'G' : 'g';
        map[y][x] = 'O';
        ghost->y  = ghost->y + 1;
        *move_order = 2;
        return (1);
    }
    else if (map[y + 1][x] == ' ') {
        map[y + 1][x] = this->player.big_pacball_effect ? 'G' : 'g';
        map[y][x] = ' ';
        ghost->y  = ghost->y + 1;
        *move_order = 2;
        return (1);
    }
    else if (map[y + 1][x] == 'g' || map[y + 1][x] == 'G'){
        return (0);
    }
    else if (map[y + 1][x] == 'P' && this->player.big_pacball_effect == 0){
        return -1;
    }
    return (0);
}

int LibPacman::up_ghost(struct ghost *ghost, int *move_order) {
     int x = ghost->x;
    int y = ghost->y;

    if (map[y - 1][x] == '.') {
        map[y - 1][x] = this->player.big_pacball_effect ? 'G' : 'g';
        map[y][x] = '.';
        ghost->y  = ghost->y - 1;
        *move_order = 1;
        return (1);
    }
    else if (map[y - 1][x] == 'O') {
        map[y - 1][x] = this->player.big_pacball_effect ? 'G' : 'g';
        map[y][x] = 'O';
        ghost->y  = ghost->y - 1;
        *move_order = 1;
        return (1);
    }
    else if (map[y - 1][x] == ' ') {
        map[y - 1][x] = this->player.big_pacball_effect ? 'G' : 'g';
        map[y][x] = ' ';
        ghost->y  = ghost->y - 1;
        *move_order = 1;
        return (1);
    }
    else if (map[y - 1][x] == 'g' || map[y - 1][x] == 'G'){
        return (0);
    }
    else if (map[y - 1][x] == 'P' && this->player.big_pacball_effect == 0){
        return -1;
    }
    return (0);
}

int LibPacman::ghost_move_ia1() {
    int rand = this->random_nb(4, 0);
    int ok = 0;

    ok = this->right_ghost(&this->ghost1, &this->ghost_move_order1);
    if ((rand == 1 && ok == 0) || (rand == 0 && ok == 0  && this->ghost_move_order1 == 3)){
       ok = this->left_ghost(&this->ghost1, &this->ghost_move_order1);
       return ok;
    }
    else if ((rand == 2 && ok == 0) || (rand == 1 && ok == 0) || (rand == 0 && ok == 0  && this->ghost_move_order1 == 2)){
        ok = this->down_ghost(&this->ghost1, &this->ghost_move_order1);
        return ok;
    }
    else if ((rand == 3 && ok == 0 )|| (rand == 2 && ok == 0) || (rand == 1 && ok == 0) || (rand == 0 && ok == 0  && this->ghost_move_order1 == 1)){
        ok = this->up_ghost(&this->ghost1, &this->ghost_move_order1);
        return ok;
    }
    return ok;
}

int LibPacman::ghost_move_ia2() {
    int rand  = random_nb(4, 0);
    int ok = 0;

    ok = left_ghost(&this->ghost2, &this->ghost_move_order2);
    if ((rand == 1 && ok == 0) || (rand == 0 && ok == 0 && this->ghost_move_order2 == 4)){
       ok = right_ghost(&this->ghost2, &this->ghost_move_order2);
       return ok;
    }
    else if ((rand == 2 && ok == 0) || (rand == 1 && ok == 0) || (rand == 0 && ok == 0 && this->ghost_move_order2 == 2)){
        ok = down_ghost(&this->ghost2, &this->ghost_move_order2);
        return ok;
    }
    else if ((rand == 3 && ok == 0) || (rand == 2 && ok == 0) || (rand == 1 && ok == 0) || (rand == 0 && ok == 0  && this->ghost_move_order2 == 1)){
        ok = up_ghost(&this->ghost2, &this->ghost_move_order2);
        return ok;
    }
   return ok;
}
