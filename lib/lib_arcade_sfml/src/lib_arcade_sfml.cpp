/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** lib_arcade_sfml
*/

#include "lib_arcade_sfml.hpp"

#include <memory>
#include <iostream>

void LibSFML::init()
{
    this->window = new sf::RenderWindow(sf::VideoMode(850, 800), "Arcade sfml window");
    this->font.loadFromFile("./utils/arcade_i.ttf");
    this->text.setFont(this->font);
    this->text.setCharacterSize(11);
    this->borderRectangle.setSize(sf::Vector2f(11, 11));
    this->borderRectangle.setFillColor(sf::Color(125, 125, 125));
    this->key = sf::Keyboard::Unknown;
    this->pacmanBorderRectangle.setSize(sf::Vector2f(25, 25));
    this->pacmanBorderRectangle.setFillColor(sf::Color::Blue);
    this->pacmanBorderRectangle.setOutlineColor(sf::Color(0, 0, 44));
    this->pacmanBorderRectangle.setOutlineThickness(1);
    this->nibblerBorderRectangle.setSize(sf::Vector2f(10, 10));
    this->nibblerBorderRectangle.setFillColor(sf::Color::Blue);
    this->nibblerBorderRectangle.setOutlineColor(sf::Color(0, 0, 44));
    this->nibblerBorderRectangle.setOutlineThickness(1);
    this->texture.loadFromFile("./utils/texture.png");
    this->sprite.setTexture(this->texture);
    this->player_dir = LibSFML::player_dir_t::RIGHT;
}

void LibSFML::deinit()
{    
    this->window->close();
}

void LibSFML::set_pixel(unsigned long x, unsigned long y, unsigned char r, unsigned char g, unsigned char b, char c)
{
    if (c == 'X') {
        this->borderRectangle.setPosition(sf::Vector2f(11 * x, 11 * y));
        this->window->draw(this->borderRectangle);
    }    
    else if (c == '#' && b != 254) {
        this->pacmanBorderRectangle.setPosition(sf::Vector2f(25 * x, 25 * y));
        this->window->draw(this->pacmanBorderRectangle);
    }
    else if(c == '#' && b == 254) {
        this->nibblerBorderRectangle.setPosition(sf::Vector2f(10 * x, 10 * y));
        this->window->draw(this->nibblerBorderRectangle);
    }
    else if (c == 'S' && r == 254) {
        this->sprite.setTextureRect(sf::IntRect(46, 56, 17, 16));
        this->sprite.setPosition(sf::Vector2f(10 * x, 10 * y));
        this->window->draw(this->sprite);
    }
    else if (c == 'O' && r == 254) {
        this->sprite.setTextureRect(sf::IntRect(65, 56, 19, 18));
        this->sprite.setPosition(sf::Vector2f(10 * x, 10 * y));
        this->window->draw(this->sprite);
    }
    else if (c == 'A' && r != 255) {
        this->sprite.setTextureRect(sf::IntRect(86, 56, 16, 19));
        this->sprite.setPosition(sf::Vector2f(10 * x, 10 * y));
        this->window->draw(this->sprite);
    }
    else if (c == '.') {
        this->sprite.setTextureRect(sf::IntRect(0, 0, 37, 37));
        this->sprite.setPosition(sf::Vector2f(25.5 * x, 25.5 * y));
        this->sprite.setScale(sf::Vector2f(0.45, 0.45));
        this->window->draw(this->sprite);
    }
    else if (c == 'O' && r != 255) {
        this->sprite.setTextureRect(sf::IntRect(37, 0, 20, 20));
        this->sprite.setPosition(sf::Vector2f(25 * x, 25 * y));
        this->sprite.setScale(sf::Vector2f(1.14, 1.14));
        this->window->draw(this->sprite);
    }
    else if (c == 'P' && g != 255) {
        if (this->player_dir == LibSFML::player_dir_t::UP)
            this->sprite.setTextureRect(sf::IntRect(154, 5, 37, 31));
        if (this->player_dir == LibSFML::player_dir_t::RIGHT)
            this->sprite.setTextureRect(sf::IntRect(57, 0, 30, 38));
        if (this->player_dir == LibSFML::player_dir_t::DOWN)
            this->sprite.setTextureRect(sf::IntRect(87, 3, 37, 30));
        if (this->player_dir == LibSFML::player_dir_t::LEFT)
            this->sprite.setTextureRect(sf::IntRect(124, 0, 30 , 38));
        this->sprite.setPosition(sf::Vector2f(25 * x, 25 * y));
        this->sprite.setScale(sf::Vector2f(0.68, 0.68));
        this->window->draw(this->sprite);
    }
    else if (c == 'g') {
        this->sprite.setTextureRect(sf::IntRect(193, 0, 38, 39));
        this->sprite.setPosition(25 * x, 25 * y);
        this->sprite.setScale(sf::Vector2f(0.68, 0.68));
        this->window->draw(this->sprite);
    }
    else if (c == 'G' && b == 255 && r == 0 && g == 0) {
        this->sprite.setTextureRect(sf::IntRect(231, 0, 37, 38));
        this->sprite.setPosition(25 * x, 25 * y);
        this->sprite.setScale(sf::Vector2f(0.68, 0.68));
        this->window->draw(this->sprite);
    }
    else {
        this->text.setPosition(sf::Vector2f(11 * x, 11 * y));
        this->text.setFillColor(sf::Color(r, g, b));
        this->text.setString(std::string(1, c));
        this->window->draw(this->text);
    }
}

void LibSFML::clear(unsigned char r, unsigned char g, unsigned char b)
{
    window->clear(sf::Color{r, g, b});
}

int LibSFML::get_input_pressed()
{
    int key = -1;

    if (this->key != sf::Keyboard::Unknown) {      
        key = this->key + 1;
        this->key = sf::Keyboard::Unknown;
        return key;
    }             
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        key = arcade::Input::P;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->player_dir = LibSFML::player_dir_t::UP;
        key = arcade::Input::UP_ARROW;        
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        this->player_dir = LibSFML::player_dir_t::DOWN;
        key = arcade::Input::DOWN_ARROW;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        this->player_dir = LibSFML::player_dir_t::LEFT;
        key = arcade::Input::LEFT_ARROW;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        this->player_dir = LibSFML::player_dir_t::RIGHT;
        key = arcade::Input::RIGHT_ARROW;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        key = arcade::Input::RETURN;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        key = arcade::Input::ESCAPE;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
        key = arcade::Input::BACKSPACE;
    // else {
    //     for (sfKey = sf::Keyboard::A; sfKey <= sf::Keyboard::Z; sfKey = (sf::Keyboard::Key) (sfKey + 1))
    //         if (sf::Keyboard::isKeyPressed(sfKey))
    //             return sfKey + 1;

    // }
    return key;
}

bool LibSFML::update()
{
    while (window->pollEvent(this->event)) {
        if (event.type == sf::Event::Closed)
            this->deinit();
        if (event.type == sf::Event::KeyPressed)
            this->key = event.key.code;
    }
    window->display();
    return this->window->isOpen();
}
