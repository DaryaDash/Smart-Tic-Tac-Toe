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
    void drawMenu();


private:
    sf::RenderWindow window;
    sf::Font font;

    float cellSize = 0.f;
    float x_first_cell = 0.f;
    float y_first_cell = 0.f;
    sf::Color BG_COLOR = sf::Color(237, 248, 255);
    sf::Color FIELD_COLOR = sf::Color(19, 19, 19);
    sf::Color X_COLOR = sf::Color(193, 224, 59);
    sf::Color O_COLOR = sf::Color(224, 59, 193);};


class Button{
    public: 
        sf::RectangleShape rectangle;

        Button (float h, float w, float x, float y, std::string ){
            this->rectangle = sf::RectangleShape({h, w});
            rectangle.setOutlineThickness(10);
            rectangle.setOrigin({h/2,w/2});
            rectangle.setPosition({x,y});
        }

        void drawBtn(sf::RenderWindow& window,float m_x,float m_y){
            if (howerBtn(m_x, m_y)) {
                rectangle.setFillColor (sf::Color(200, 224, 59));
                rectangle.setOutlineColor(sf::Color(150, 100, 59));
            } else {
                rectangle.setFillColor (sf::Color(193, 224, 59));
                rectangle.setOutlineColor(sf::Color(100, 100, 59));
            }
            
            window.draw(this->rectangle);
        }
        bool howerBtn(float m_x,float m_y){
            if (m_x > this->rectangle.getOrigin().x - this->rectangle.getSize().x/2
                    && m_x < this->rectangle.getOrigin().x + this->rectangle.getSize().x/2 )
                    {
                        if (m_y > this->rectangle.getOrigin().y - this->rectangle.getSize().y/2
                            && m_y < this->rectangle.getOrigin().y + this->rectangle.getSize().y/2 ){return true;}
                    }
            else {return false;}
            
        }



};