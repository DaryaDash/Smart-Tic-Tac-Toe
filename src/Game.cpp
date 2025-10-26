#include "Game.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Audio.hpp>
#include <optional>

void Game::run() { menu(); }

void Game::menu() {
    static Button start(400.f, 200.f,
                        static_cast<float>(gui.getWindow().getSize().x) * 0.5f,
                        static_cast<float>(gui.getWindow().getSize().y) * 0.5f,
                        "START");
    while (gui.getWindow().isOpen()) {
        while (const std::optional<sf::Event> e = gui.getWindow().pollEvent()) {
            const sf::Vector2i mp = sf::Mouse::getPosition(gui.getWindow());
            if (e->is<sf::Event::Closed>()) gui.getWindow().close();
            if (const auto* key = e->getIf<sf::Event::KeyPressed>())
                if (key->scancode == sf::Keyboard::Scancode::Escape) gui.getWindow().close();
            if (const auto* r = e->getIf<sf::Event::Resized>()) {
                const auto sz = sf::Vector2f(static_cast<float>(r->size.x), static_cast<float>(r->size.y));
                gui.getWindow().setView(sf::View(sf::FloatRect({0.f, 0.f}, sz)));
            }
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                if (start.hover((float)mp.x,(float)mp.y))
                {
                    ticTackToe();
                }
                
            }


        gui.drawMenu(mp.x, mp.y);
        gui.display();
    }
}
}

void Game::ticTackToe() {
    //sf::Music moveMusic, winMusic;
    //moveMusic.openFromFile("n.mp3");
    //winMusic.openFromFile("w.mp3");

    gui.getWindow().setVerticalSyncEnabled(true);

    isRun = true;
    bool wasMouseDown = false;

    while (gui.getWindow().isOpen()) {
        while (const std::optional<sf::Event> e = gui.getWindow().pollEvent()) {
            if (e->is<sf::Event::Closed>()) gui.getWindow().close();

            if (const auto* key = e->getIf<sf::Event::KeyPressed>()) {
                if (key->scancode == sf::Keyboard::Scancode::Escape) gui.getWindow().close();
                if (key->scancode == sf::Keyboard::Scancode::Enter && !isRun) restart();
            }

            if (const auto* r = e->getIf<sf::Event::Resized>()) {
                const auto sz = sf::Vector2f(static_cast<float>(r->size.x), static_cast<float>(r->size.y));
                gui.getWindow().setView(sf::View(sf::FloatRect({0.f, 0.f}, sz)));
            }
        }

        const bool mouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        if (mouseDown && !wasMouseDown) {
            const sf::Vector2i mp = sf::Mouse::getPosition(gui.getWindow());
            if (isRun) {
                if (gui.drawMove(board, mp.x, mp.y, plr)) {
                    //if (moveMusic.getStatus() == sf::SoundSource::Status::Playing) moveMusic.stop();
                    //moveMusic.play();

                    const int res = board.terminate();
                    if (res != -2) {
                       // if (moveMusic.getStatus() == sf::SoundSource::Status::Playing) moveMusic.stop();
                       // winMusic.play();
                        isRun = false;
                       
                    } else {
                        plr = curr(plr);
                    }
                }
            }
        }
        wasMouseDown = mouseDown;
        gui.drawBoard(board);    
        if (!isRun) gui.winMassage(board.terminate() == -2 ? 0 : board.terminate()); // при необходимости покажи статус
        gui.display();
    }
}

void Game::restart() {
    isRun = true;
    board.clear();
    plr = Board::Cell::X;
}

Board::Cell Game::curr(Board::Cell who) {
    if (who == Board::Cell::O) return Board::Cell::X;
    if (who == Board::Cell::X) return Board::Cell::O;
    return Board::Cell::X;
}
