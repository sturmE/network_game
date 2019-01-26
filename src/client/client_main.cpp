//
//  main.cpp
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <json.hpp>
#include <string>
#include <fstream>
#include <streambuf>
using json = nlohmann::json;

const uint32_t kWindowWidth = 1600.f * 2.f;
const uint32_t kWindowHeight = 900.f * 2.f;
const std::string kWindowName = "dirty";

Game game;

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(kWindowWidth, kWindowHeight), kWindowName,  sf::Style::Titlebar  | sf::Style::Close);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    
    sf::Clock frameClock;
    sf::Clock gameClock;
    
    
//    std::ifstream t("settings.json");
//    std::string json_str((std::istreambuf_iterator<char>(t)),
//                    std::istreambuf_iterator<char>());
//    json settings = json::parse(json_str);
    
    
    game.onStart(&window);
    
    while (window.isOpen()) {
        sf::Event event;
        
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    window.close();
                    break;
                }
                case sf::Event::Resized: {
                    game.onWindowResize();
                    break;
                }
                case sf::Event::KeyPressed: {
                    if (event.key.code == sf::Keyboard::Key::Escape) {
                        window.close();
                    }
                    
                    break;
                }
                case sf::Event::KeyReleased: {
                    break;
                }
                case sf::Event::LostFocus: {
                    break;
                }
                case sf::Event::GainedFocus: {
                    break;
                }
                default: {
                    break;
                }
            }
        }
        
        sf::Time frameTime = frameClock.restart();
        sf::Time gameTime = gameClock.getElapsedTime();
        
        window.clear(sf::Color::Black);
        game.onFrame(frameTime.asSeconds());
        window.display();
    }
    game.onShutdown();
    
    return 0;
}

