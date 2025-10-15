// src/GUI.cpp
#include "GUI.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

GUI::GUI() {
    const auto mode = sf::VideoMode::getDesktopMode();
    window.create(mode, "provided", sf::State::Windowed);
    (void)font.openFromFile("Comic Jungle.ttf");
    window.clear(BG_COLOR);
}

void GUI::display() {
    window.display();
}

sf::RenderWindow& GUI::getWindow() {
    return window;
}

void GUI::winMassage(int res) {
    sf::Text text(font, "", static_cast<unsigned>(cellSize * 0.5f));
    text.setPosition({ x_first_cell, y_first_cell - cellSize });

    if (res == 1) {
        text.setFillColor(X_COLOR);
        text.setString("X WON");
    } else if (res == -1) {
        text.setFillColor(O_COLOR);
        text.setString("O WON");
    } else {
        text.setFillColor(sf::Color::Black);
        text.setString("DRAW");
    }

    window.draw(text);
}

void GUI::drawMenu(float m_x, float m_y) {
    window.clear(BG_COLOR);
    const auto size = window.getSize();
    const float x_center = static_cast<float>(size.x) * 0.5f;
    const float y_center = static_cast<float>(size.y) * 0.5f;
    Button start(150.f, 300.f, x_center, y_center, "Start");
    start.drawBtn(window, m_x, m_y);
}

void GUI::drawFileld() {
    const sf::Vector2u size = window.getSize();
    const float x_center = static_cast<float>(size.x) * 0.5f;
    const float y_center = static_cast<float>(size.y) * 0.5f;
    const float step     = x_center / 4.f;
    const float length   = x_center * 0.8f;

    sf::RectangleShape line({ length, step / 30.f });
    line.setFillColor(FIELD_COLOR);
    line.setOrigin({ length / 2.f, 2.5f });

    cellSize = step;

    const float x_start = x_center - step * 0.5f;
    const float y_start = y_center - step * 0.4f;
    y_first_cell = y_start - step;
    x_first_cell = x_start - step;

    for (int i = 0; i < 2; ++i) {
        line.setRotation(sf::degrees(0));
        line.setPosition({ x_center, y_start + step * i });
        window.draw(line);
    }
    for (int i = 0; i < 2; ++i) {
        line.setRotation(sf::degrees(90));
        line.setPosition({ x_start + step * i, y_center });
        window.draw(line);
    }
}

bool GUI::drawMove(Board& board, int x, int y, Board::Cell who) {
    const float xMax = x_first_cell + cellSize * 3.f;
    const float yMax = y_first_cell + cellSize * 3.f;
    if (x < x_first_cell || x >= xMax || y < y_first_cell || y >= yMax) return false;

    const int i = static_cast<int>((x - x_first_cell) / cellSize);
    const int j = static_cast<int>((y - y_first_cell) / cellSize);
    if (i < 0 || i >= 3 || j < 0 || j >= 3) return false;

    return board.makeMove(j, i, who);
}

void GUI::drawBoard(const Board& board) {
    sf::Text text(font, "", static_cast<unsigned>(cellSize * 0.8f));

    window.clear(BG_COLOR);
    drawFileld();

    const auto& cells = board.getCells();
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            const auto cell = cells[r * 3 + c];
            if (cell == Board::Cell::O) {
                text.setString("O");
                text.setFillColor(O_COLOR);
            } else if (cell == Board::Cell::X) {
                text.setString("X");
                text.setFillColor(X_COLOR);
            } else {
                continue;
            }
            text.setPosition({
                (x_first_cell + cellSize * c) + cellSize * 0.15f,
                (y_first_cell + cellSize * r) + cellSize * 0.05f
            });
            window.draw(text);
        }
    }
}

Button::Button(float h, float w, float x, float y, const std::string& text)
    : btn_font()
    , btn_text(btn_font, "", 20)
    , rectangle({h, w})
{
    (void)btn_font.openFromFile("Comic Jungle.ttf");
    btn_text.setString(text);
    btn_text.setCharacterSize(static_cast<unsigned>(h * 0.35f));
    btn_text.setFillColor(sf::Color::Black);

    rectangle.setOutlineThickness(10);
    rectangle.setOrigin({ h / 2.f, w / 2.f });
    rectangle.setPosition({ x, y });

    const auto tb = btn_text.getLocalBounds();
    btn_text.setOrigin({ tb.position.x + tb.size.x / 2.f, tb.position.y + tb.size.y / 2.f });
    btn_text.setPosition({ x, y });
}

void Button::drawBtn(sf::RenderWindow& window, float m_x, float m_y) {
    if (hover(m_x, m_y)) {
        rectangle.setFillColor(sf::Color(200, 224, 59));
        rectangle.setOutlineColor(sf::Color(150, 100, 59));
    } else {
        rectangle.setFillColor(sf::Color(193, 224, 59));
        rectangle.setOutlineColor(sf::Color(100, 100, 59));
    }
    window.draw(rectangle);
    window.draw(btn_text);
}

bool Button::hover(float m_x, float m_y) const {
    const sf::Vector2f pos  = rectangle.getPosition();
    const sf::Vector2f size = rectangle.getSize();
    const float halfX = size.x * 0.5f;
    const float halfY = size.y * 0.5f;
    return (m_x >= pos.x - halfX && m_x <= pos.x + halfX &&
            m_y >= pos.y - halfY && m_y <= pos.y + halfY);
}
