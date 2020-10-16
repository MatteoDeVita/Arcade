/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#include <iostream>
#include <dlfcn.h>
#include <error.h>
#include <math.h>
#include <ncurses.h>
#include <curses.h>
#include <string.h>

#include "Core.hpp"

#define MAP_Y 25
#define MAP_X 81

Core::Core(std::string &graphicalLibFilePath) {    
    if ((this->graphicalLib = dlopen(graphicalLibFilePath.c_str(), RTLD_NOW)) == NULL)
        error(84, 0, "%s", dlerror());        
    if ((this->castedGraphicalLib = reinterpret_cast<std::unique_ptr<IGraphicalsLib> (*) ()>(dlsym(this->graphicalLib, "make_graphics_instance"))) == NULL)
        error(84, 0, "%s", dlerror());
    this->graphicalLibHandler = this->castedGraphicalLib();
    this->gameType = Core::gameType_t::GAME_NONE;    
    if (this->string_ends_with(graphicalLibFilePath, std::string("lib_arcade_ncurses.so")))
        this->libType = Core::libType_t::NCURSES;
    else if (this->string_ends_with(graphicalLibFilePath, std::string("lib_arcade_sfml.so")))
        this->libType = Core::libType_t::SFML;
    else if (this->string_ends_with(graphicalLibFilePath, std::string("lib_arcade_sdl.so")))
        this->libType = Core::libType_t::SDL;
    this->userName = std::string("");
    this->play_game(); 
}

void Core::set_new_graphical_lib(Core::libType_t newLibType) {
    std::string graphicalLibFilePath("./lib/lib_arcade_");

    if (newLibType == Core::libType_t::NCURSES)
        graphicalLibFilePath += "ncurses.so";
    else if (newLibType == Core::libType_t::SFML)
        graphicalLibFilePath += "sfml.so";
    else if (newLibType == Core::libType_t::SDL)
        graphicalLibFilePath += "sdl.so";
    else {
        std::cerr << "Can't change graphical library" << std::endl;
        return;
    }
    if ((this->graphicalLib = dlopen(graphicalLibFilePath.c_str(), RTLD_LAZY)) == NULL)
        error(84, 0, "%s", dlerror());        
    if ((this->castedGraphicalLib = reinterpret_cast<std::unique_ptr<IGraphicalsLib> (*) ()>(dlsym(this->graphicalLib, "make_graphics_instance"))) == NULL)
        error(84, 0, "%s", dlerror());
    this->graphicalLibHandler = this->castedGraphicalLib();
    this->libType = newLibType;
}

void Core::draw_string(int x, int y, unsigned char r, unsigned char g, unsigned char b, const std::string &string) {
    for (size_t i = 0; i < string.length(); i++)
        this->graphicalLibHandler->set_pixel(x + i, y, r, g, b, string[i]);
}

void Core::draw_menu() {
    FILE *fd = fopen("./utils/score_nibbler.txt", "r");
    FILE *fd2 = fopen("./utils/score_pacman.txt", "r");
    char *str2 = (char*)malloc(sizeof(char) *1000);
    char *str = (char*)malloc(sizeof(char) *1000);
    
    if (fd != NULL){
        fgets(str, 30, fd);
        fclose(fd);
    }
    if (fd2 != NULL) {
        fgets(str2, 30, fd2);
        fclose(fd2);
    }
    std::string nibbler_str("    Nibbler");
    std::string pacman_str("    Pacman");
    std::string ncurses_str("    NCurses");
    std::string sfml_str("    SFML");
    std::string sdl_str("    SDL");
    for (size_t i = 0; i < 71; i++) {
        this->graphicalLibHandler->set_pixel(i, 0, 0, 0, 0, 'X');
        if (i < 51)
            this->graphicalLibHandler->set_pixel(i, 9, 0, 0, 0, 'X');
        this->graphicalLibHandler->set_pixel(i, 13, 0, 0, 0, 'X');
    }
    for (size_t i = 1; i < 13; i++) {
        if (i < 10)
            this->graphicalLibHandler->set_pixel(25, i, 0, 0, 0, 'X');
        this->graphicalLibHandler->set_pixel(0, i, 0, 0, 0, 'X');
        this->graphicalLibHandler->set_pixel(50, i, i, 0, 0, 'X');
        this->graphicalLibHandler->set_pixel(70, i, i, 0, 0, 'X');
    }
    if (this->gameType == Core::gameType_t::NIBBLER)
        nibbler_str = "--> Nibbler";
    else if (this->gameType == Core::gameType_t::PACMAN)
        pacman_str = "--> Pacman";
    if (this->libType == Core::libType_t::NCURSES)
        ncurses_str = "--> NCurses";
    else if (this->libType == Core::libType_t::SFML)
        sfml_str = "--> SFML";
    else if (this->libType == Core::libType_t::SDL)
        sdl_str = "--> SDL";
    this->draw_string(2, 3, 255, 0, 0, nibbler_str);
    this->draw_string(2, 6, 255, 255, 0, pacman_str);
    this->draw_string(27, 3, 0, 0, 255, ncurses_str);
    this->draw_string(27, 5, 0, 0, 255, sfml_str);
    this->draw_string(27, 7, 0, 0, 255, sdl_str);
    this->draw_string(2, 10, 255, 0, 0, std::string("Type your username :"));
    this->draw_string(6, 11, 0, 255, 0, this->userName);
    this->draw_string(52, 1, 0, 255, 0, std::string("Nibbler HighScore"));
    this->draw_string(52, 3, 0, 255, 0, str);
    this->draw_string(52, 5, 0, 255, 0, std::string("Pacman HighScore"));
    this->draw_string(52, 7, 0, 255, 0, str2);
    this->draw_string(2, 1, 255, 255, 255, std::string("Game :"));
    this->draw_string(27, 1, 255, 255, 255, std::string("Graphical library :"));
    this->draw_string(0, 15, 255, 255, 0, std::string("Press up and down arrow to select your game and right arrow to start playing !"));
}

void Core::play_menu() {  
    int input_pressed = -1;

    this->graphicalLibHandler->init();
    
    while (this->graphicalLibHandler->update()) {
        this->graphicalLibHandler->clear(0, 0, 0);
        this->draw_menu();
        input_pressed = this->graphicalLibHandler->get_input_pressed();
        if (input_pressed == Core::Input::UP_ARROW)
            this->gameType = Core::gameType_t::NIBBLER;
        else if (input_pressed == Core::Input::DOWN_ARROW)
            this->gameType = Core::gameType_t::PACMAN;
        else if (
                (input_pressed >= Core::Input::A && input_pressed <= Core::Input::Z) &&
                this->userName.length() <= 40 
            )
            this->userName += (input_pressed + ('a' - 1));
        else if (input_pressed == Core::Input::BACKSPACE && this->userName.length())
            this->userName.pop_back();
        else if (input_pressed == Core::Input::RETURN || input_pressed == Core::Input::RIGHT_ARROW) {
            this->graphicalLibHandler->clear(255, 255, 255);
            // this->graphicalLibHandler->deinit();        
            return;
        }
        else if(input_pressed == Core::Input::ESCAPE) {
            this->graphicalLibHandler->clear(255, 255, 255);
            this->graphicalLibHandler->deinit();        
            return;
        }
    }
    this->graphicalLibHandler->deinit();
}

void Core::play_game() {
    if (this->gameType != Core::gameType_t::NIBBLER && this->gameType != Core::gameType_t::PACMAN)
        this->play_menu();
    if (this->gameType == Core::gameType_t::NIBBLER)
        this->play_nibbler();
    else if (this->gameType == Core::gameType_t::PACMAN)
        this->play_pacman();
}

void Core::play_nibbler() {
    int key = -1;
    char *score = (char *) malloc(sizeof(char) * 1000);
    char *str_int = (char*) malloc(sizeof(char)*1000);
    char str[] = "appuyez sur la touche Q pour quitter";

    if ((this->gameLib = dlopen("./games/lib_arcade_nibbler.so", RTLD_NOW)) == NULL)
        error(84, 0 , "%s", dlerror());
    if ((this->castedNibblerLib = reinterpret_cast<std::unique_ptr<INibblerLib> (*) ()>(dlsym(this->gameLib, "make_nibbler_instance"))) == NULL)
        error(84, 0 , "%s", dlerror());
    this->nibblerLibHandler = this->castedNibblerLib();
    while (!this->nibblerLibHandler->collision(this->nibblerLibHandler->get_snake_array_ptr())) {
        this->graphicalLibHandler->clear('s', 's', 's');
        this->nibblerLibHandler->handle_apple_life();
        this->nibblerLibHandler->move_snake_head(this->nibblerLibHandler->get_snake_array_ptr());
        this->nibblerLibHandler->eat_apple(this->nibblerLibHandler->get_snake_array_ptr());
        this->print_nibbler_game(this->nibblerLibHandler->get_snake_array_ptr());
        if (this->nibblerLibHandler->kbhit()) {
            key = this->graphicalLibHandler->get_input_pressed();
            if (key == arcade::Input::G || key == arcade::Input::H) {
                dlclose(this->gameLib);            
                this->play_pacman();
            }
            this->nibblerLibHandler->handle_input_pressed(key);
        }
        this->graphicalLibHandler->update();
    }
    this->graphicalLibHandler->clear('s', 's', 's');
    strcpy(score, "GAME OVER, YOUR SCORE WAS : ");
    sprintf(str_int, "%d", this->nibblerLibHandler->get_player().snakeLength);
    strcat(score, str_int);
    for(int x = 0; score[x] != '\0'; x++)
        this->graphicalLibHandler->set_pixel(x,0, 255,255, 255, score[x]);//appel graphique
    for(int x = 0; str[x] != '\0'; x++)
        this->graphicalLibHandler->set_pixel(x,4, 255, 255, 255, str[x]);//appel graphique
     this->graphicalLibHandler->update();
    this->nibblerLibHandler->write_scores(this->userName.c_str());
    while(1) {
        key = this->graphicalLibHandler->get_input_pressed();

        if (key == arcade::Input::Q) {
            this->graphicalLibHandler->deinit();
	        return;
        }
    }
    free(score);
    free(str_int);
}

void Core::play_pacman() {
    int key = 0;

    if ((this->gameLib = dlopen("./games/lib_arcade_pacman.so", RTLD_NOW)) == NULL)
        error(84, 0 , "%s", dlerror());
    if ((this->castedPacmanLib = reinterpret_cast<std::unique_ptr<IPacmanLib> (*) ()>(dlsym(this->gameLib, "make_pacman_instance"))) == NULL)
        error(84, 0 , "%s", dlerror());
    this->pacmanLibHandler = this->castedPacmanLib();
    while (this->pacmanLibHandler->spot_win() != -1) {
        this->graphicalLibHandler->clear(255, 255, 255);
        this->pacmanLibHandler->update_time();
        this->print_pacman_game();
        if (this->pacmanLibHandler->get_door_status() == 1)
            this->pacmanLibHandler->open_ghost_door();
        this->pacmanLibHandler->find_player();
        key = this->graphicalLibHandler->get_input_pressed();
        if (key == arcade::Input::G || key == arcade::Input::H) {
            dlclose(this->gameLib);            
            this->play_nibbler();
        }
        if (key == arcade::Input::T) {
            this->graphicalLibHandler->deinit();
            dlclose(this->graphicalLib);
            this->set_new_graphical_lib((Core::libType_t) (this->libType == Core::libType_t::NCURSES ? Core::libType_t::SDL : this->libType - 1));
        }
        else if (key == arcade::Input::Y) {
            this->graphicalLibHandler->deinit();
            dlclose(this->graphicalLib);
            this->set_new_graphical_lib((Core::libType_t) (this->libType == Core::libType_t::SDL ? Core::libType_t::NCURSES : this->libType + 1));
        }
        else if (key == arcade::Input::G || key == arcade::Input::H) {
            this->gameType = Core::gameType_t::NIBBLER;
            this->play_game();
        }
        this->pacmanLibHandler->active_direction_func(key);
        if (fmod(this->pacmanLibHandler->get_time_player(), 0.2) >= this->pacmanLibHandler->get_player().speed) {
            this->pacmanLibHandler->update_player();
        }
        this->pacmanLibHandler->close_ghost_door_after_spawn();
        this->pacmanLibHandler->handle_player_super_mode();
        this->pacmanLibHandler->find_player();
        if (this->pacmanLibHandler->handle_ghost() == -1) {
            this->pacmanLibHandler->write_scores(this->userName.c_str());
            this->graphicalLibHandler->deinit();
            this->gameType = Core::gameType_t::GAME_NONE;
            this->play_game();
        }
        if (!this->graphicalLibHandler->update())
            exit(0);
    }
    this->pacmanLibHandler->write_scores(this->userName.c_str());
    this->graphicalLibHandler->deinit();
}

bool Core::string_ends_with(const std::string &string, const std::string &end) {
    return (end.size() > string.size()) ? 
    false : std::equal(end.rbegin(), end.rend(), string.rbegin());
}

void Core::print_pacman_game() {
    int i = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    char **map = this->pacmanLibHandler->get_map();

    this->graphicalLibHandler->clear('s','s','s');
    for (int y = 0; y != this->pacmanLibHandler->get_nb_cols(); y++) {
        for (; i != this->pacmanLibHandler->get_nb_rows(); i++) {
            if (map[y][i] == 'P') {
                r = 255;
                g = 254;
                b = 0;
            }
            else if (map[y][i] == 'G' || map[y][i] == 'g') {
                r = 0;
                g = 0;
                b = 255;
            }
            else if (map[y][i] == 'O')      {
                r = 0;
                g = 255;
                b = 0;
            }
            else if (map[y][i] == '.') {
                r = 255;
                g = 0;
                b = 0;
            }
            this->graphicalLibHandler->set_pixel(i, y, r, g, b, map[y][i]);
            if (r != 0 || g != 0 || b != 0) {
                r = 0;
                g = 0;
                b = 0;
            }
        }
        i = 0;
    }
    this->graphicalLibHandler->update();
}

void Core::print_nibbler_game(int *snakeArray) {
    apple_t apple = this->nibblerLibHandler->get_apple();
    nibbler_player_t *player_ptr = this->nibblerLibHandler->get__player_ptr();

    for (int y = 0; y < MAP_Y + 2; y++) {
        this->graphicalLibHandler->set_pixel(0, y, 0, 0, 254, '#');
        this->graphicalLibHandler->set_pixel(MAP_X, y, 0, 0, 254, '#');
    }
    for (int x = 0; x < MAP_X; x++) {
        this->graphicalLibHandler->set_pixel(x, 0, 0, 0, 254, '#');
        this->graphicalLibHandler->set_pixel(x, MAP_Y + 1, 0, 0, 254, '#');
    }
    
//print apple
    this->graphicalLibHandler->set_pixel(apple.x, apple.y, 0,255,0, 'A');//appel graphique
//print SNAKE head
    this->graphicalLibHandler->set_pixel(player_ptr->headX, player_ptr->headY, 254,0,0, 'O');//appel graphique
//print SNAKE body
    for (int i = 2; i < player_ptr->snakeLength * 2; i += 2){
        this->nibblerLibHandler->move_Snake_Body(snakeArray, player_ptr , i);
        player_ptr = this->nibblerLibHandler->get__player_ptr();
        this->graphicalLibHandler->set_pixel(player_ptr->bodyX, player_ptr->bodyY, 254,0,0, 'S');
    }
}
