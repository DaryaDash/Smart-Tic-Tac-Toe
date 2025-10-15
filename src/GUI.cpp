#include "GUI.hpp"



GUI::GUI() {
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    window.create(mode, "provided", sf::State::Windowed);
    font.openFromFile("Comic Jungle.ttf");
    window.clear(BG_COLOR);
}

void GUI::display() { window.display(); }

sf::RenderWindow& GUI::getWindow() { return window; }

void GUI::winMassage(int res){
    sf::Text text (font,"",10);
    text.setFont(font);
    text.setCharacterSize(static_cast<unsigned>(cellSize * 0.5f));
    text.setPosition({ x_first_cell , y_first_cell - cellSize});
    if (res == 1) {text.setFillColor(X_COLOR); text.setString("X WON");}
    if (res == -1) {text.setFillColor(O_COLOR); text.setString("0 WON");}
    if (res == 0) {text.setFillColor(sf::Color::Black);text.setString("DRAW");}
    window.draw(text) ;
}

void GUI::drawMenu(){
    window.clear(BG_COLOR);

}

void GUI::drawFileld() {
    sf::Vector2u size = window.getSize();
    float x_center = static_cast<float>(size.x) * 0.5f;
    float y_center = static_cast<float>(size.y) * 0.5f;
    float step = x_center / 4;
    float leight = x_center * 0.8f;
    sf::RectangleShape line({ leight, step / 30.f });
    line.setFillColor(FIELD_COLOR);
    line.setOrigin({ leight / 2, 2.5f });
    this->cellSize = step;
    float x_start = x_center - step * 0.5f;
    float y_start = y_center - step * 0.4f;
    y_first_cell = y_start - step;
    x_first_cell = x_start - step;

    for (int i = 0; i < 2; ++i) {
        line.setPosition({ x_center, y_start + step * i });
        window.draw(line);
    }
    for (int i = 0; i < 2; ++i) {
        line.setRotation(sf::degrees(90));
        line.setPosition({ x_start + step * i, y_center });
        window.draw(line);
    }
    window.display();
}

bool GUI::drawMove(Board& board, int x, int y, Board::Cell who) {
    bool isMoved = false;
    drawFileld();
    float xBoardSize = x_first_cell + cellSize * 3.f;
    float yBoardSize = y_first_cell + cellSize * 3.f;
    if (x < x_first_cell || x > xBoardSize || y < y_first_cell || y > yBoardSize)
    { return false;}
    int i = static_cast<int>((x - x_first_cell) / cellSize);
    int j = static_cast<int>((y - y_first_cell) / cellSize);
    if (i < 0 || i >= 3 || j < 0 || j >= 3) 
    { return false;}

    if (board.makeMove(j, i, who)) {
        isMoved = true;
    }

    
    window.display();
    return isMoved;
}

void GUI::drawBoard(const Board& board) {
    sf::Text text (font,"",10);
    text.setFont(font);
    text.setCharacterSize(static_cast<unsigned>(cellSize * 0.8f));
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
