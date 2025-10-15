#include "Game.hpp"
#include <SFML/Window/Event.hpp>
#include <optional>
#include <SFML/Audio.hpp>
#include <iostream>

void Game::run() {
    Game::menu();
}

void Game::menu(){
    while (gui.getWindow().isOpen()) {
        while (const std::optional event = gui.getWindow().pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                gui.getWindow().close();
                continue;
            }
            if (event->is<sf::Event::KeyPressed>()) {
                const auto* key = event->getIf<sf::Event::KeyPressed>();
                if (key && key->scancode == sf::Keyboard::Scancode::Escape) {
                    gui.getWindow().close();
                    continue;
                }
            }
            if (event->is<sf::Event::Resized>()) {
                const auto* resized = event->getIf<sf::Event::Resized>();
                gui.getWindow().setView(sf::View(sf::FloatRect(sf::Vector2f{0.f, 0.f},
                    sf::Vector2f{static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)})));
            }
        }
        const sf::Vector2i mouse = sf::Mouse::getPosition(gui.getWindow());
        gui.drawMenu(mouse.x, mouse.y);
        gui.display();
    }
}
        if (event->is<sf::Event::Resized>()) {
                    const auto* resized = event->getIf<sf::Event::Resized>();
                    gui.getWindow().setView(sf::View(sf::FloatRect(sf::Vector2f{0.f, 0.f},
                        sf::Vector2f{(float)resized->size.x, (float)resized->size.y})));
                }\n\n}\n\n

}
void Game::ticTackToe(){
        sf::Music music("n.mp3");
        sf::Music wmusic("w.mp3");
        Button btn(100.f,100.f, 500.f, 500.f, "test");
        isRun = true;
        gui.drawFileld();
            while (gui.getWindow().isOpen()) {

            while (const std::optional event = gui.getWindow().pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    gui.getWindow().close();
                    
                }
                if (event->is<sf::Event::KeyPressed>()) {
                    const auto* key = event->getIf<sf::Event::KeyPressed>();
                    if (key && key->scancode == sf::Keyboard::Scancode::Escape) {
                        gui.getWindow().close();
                    }
                    if (key && key->scancode == sf::Keyboard::Scancode::Enter && !isRun) {
                        restart();
                    }
                }
                if (event->is<sf::Event::Resized>()) {
                    const auto* resized = event->getIf<sf::Event::Resized>();
                    gui.getWindow().setView(sf::View(sf::FloatRect(sf::Vector2f{0.f, 0.f},
                        sf::Vector2f{(float)resized->size.x, (float)resized->size.y})));
                    gui.drawFileld();
                    gui.drawBoard(board);
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(gui.getWindow());
                    if (isRun){
                        if (gui.drawMove(board, localPosition.x, localPosition.y, plr)) plr = curr(plr);
                        
                        music.play();
                        board.printBaord();
                        int res = board.terminate();
                  
                        if (res != -2){
                            music.stop();
                            wmusic.play();
                            gui.drawBoard(board);
                            gui.winMassage(res);
                            isRun = false ;
                            gui.display();
                       
                        } else {
                            gui.drawBoard(board);
                            gui.display();
                        }\n\n}\n\n            }\n\n}\n\n
void Game::restart(){
        isRun = true;
        board.clear();
        Board::Cell plr = Board::Cell::X;
        gui.drawFileld();
        sf::Music music("n.mp3");
}
Board::Cell Game::curr(Board::Cell who) {
    if (who == Board::Cell::O) return Board::Cell::X;
    if (who == Board::Cell::X) return Board::Cell::O;
    return Board::Cell::X;
}

