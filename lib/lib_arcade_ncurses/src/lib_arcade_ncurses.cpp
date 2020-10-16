/*
** EPITECH PROJECT, 2020
** arcade_temp
** File description:
** lib_arcade_ncurses
*/

#include "lib_arcade_ncurses.hpp"

#include <curses.h>

void LibNCurses::set_pixel(unsigned long x, unsigned long y, unsigned char r, unsigned char g, unsigned char b, char ncurse_char)
{
    int color = NORMAL_COLOR;

    if ((r == 255 || r == 254) && g == 0 && b == 0)
        color = RED_COLOR;
    else if (r == 0 && g == 255 && b == 0)        
        color = GREEN_COLOR;
    else if (r == 0 && g == 0 && b == 255)
        color = BLUE_COLOR;
    else if (r == 255 && (g == 255 || g == 254) && b == 0)
        color = YELLOW_COLOR;
    attron(COLOR_PAIR(color));
    mvaddch(y, x, ncurse_char);
    attroff(COLOR_PAIR(color));
}

void LibNCurses::init()
{
    WINDOW *screen = initscr();
    curs_set(0);
    nodelay(screen, true);
    keypad(screen, true);
    noecho();
    cbreak();
    start_color();
    init_pair(NORMAL_COLOR, COLOR_WHITE, COLOR_BLACK);
    init_pair(RED_COLOR, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN_COLOR, COLOR_GREEN, COLOR_BLACK);
    init_pair(BLUE_COLOR, COLOR_BLUE, COLOR_BLACK);
    init_pair(YELLOW_COLOR, COLOR_YELLOW, COLOR_BLACK);
}

void LibNCurses::deinit()
{
    endwin();
}

bool LibNCurses::update()
{
    refresh();
    return true;
}

void LibNCurses::clear(unsigned char, unsigned char, unsigned char)
{
    curs_set(0);
    erase();
}

int LibNCurses::get_input_pressed()
{
    int ch = getch();
    int ret = arcade::Input::NONE;

    // ESCAPE KEY special handling
    if (ch == 27) {
        if (getch() == ERR)
            return arcade::ESCAPE;
    }
    if (ch >= 'A' && ch <= 'Z')
        ch += 32;
    switch (ch) {
        case 'z':
            ret = arcade::Input::Z;
            break;
        case 's':
            ret = arcade::Input::S;
            break;
        case 'q':
            ret = arcade::Input::Q;
            break;
        case 'd':
            ret = arcade::Input::D;
            break;
        case 'p':
            ret = arcade::Input::P;
            break;
        case KEY_UP:
            ret = arcade::Input::UP_ARROW;
            break;
        case KEY_DOWN:
            ret = arcade::Input::DOWN_ARROW;
            break;
        case KEY_LEFT:
            ret = arcade::Input::LEFT_ARROW;
            break;
        case KEY_RIGHT:
            ret = arcade::Input::RIGHT_ARROW;
            break;
        case KEY_ENTER:
            ret = arcade::Input::RETURN;
            break;
        case KEY_BACKSPACE:
            ret = arcade::Input::BACKSPACE;
            break;
        default:
            ret = arcade::Input::NONE;
            break;
    }
    if (ch >= 'a' && ch <= 'z')
        return ch - ('a' - 1);
    return ret;
}
