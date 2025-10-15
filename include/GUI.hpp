// include/GUI.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include "Board.hpp"

class GUI {
public:
    GUI();

    void display();
    sf::RenderWindow& getWindow();

    void drawFileld();
    bool drawMove(Board& board, int x, int y, Board::Cell who);
    void drawBoard(const Board& board);
    void winMassage(int res);
    void drawMenu(float m_x, float m_y);

private:
    sf::RenderWindow window;
    sf::Font font;

    float cellSize = 0.f;
    float x_first_cell = 0.f;
    float y_first_cell = 0.f;
    sf::Color BG_COLOR    = sf::Color(237, 248, 255);
    sf::Color FIELD_COLOR = sf::Color(19, 19, 19);
    sf::Color X_COLOR     = sf::Color(193, 224, 59);
    sf::Color O_COLOR     = sf::Color(224, 59, 193);
};

class Button {
public:
    Button(float h, float w, float x, float y, const std::string& text);

    void drawBtn(sf::RenderWindow& window, float m_x, float m_y);
    bool hover(float m_x, float m_y) const;
private:


    // порядок объявлений важен: font до text
    sf::Font btn_font;
    sf::Text btn_text;
    sf::RectangleShape rectangle;
};
