/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Client
*/

#include "../../headers/Client/Client.hpp"

Client::Client() {
    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "R-TYPE", sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(60);
    _state = MENU;
    _serverList = new ServerList(this, window);
}

void Client::init() {
    _background = new Background();
    loadState();
    //todo : load network thread
}

void Client::loadState() {
    while(_buttons.size() > 0) {
        _buttons.erase(_buttons.begin());
    }
    _background->clear();
    switch (_state)
    {
        case MENU:
            loadMenu();
            break;
        case SERVER_SELECTION:
            loadServerSelection();
            break;
        case OPTIONS:
            loadGameOptions();
            break;
        case LOBBY:
            loadLobby();
            break;
        case GAME:
            loadGame();
            break;
        case OFFLINE:
            loadOffline();
            break;
        case END:
            //loadEnd();
            break;
    }
}

void Client::loadState(state state) {
    _state = state;
    loadState();
}

void Client::run() {
    while (window->isOpen()) {
        _mousePosition = sf::Mouse::getPosition(*window);
        sf::Event event;
        while (window->pollEvent(event)) {
            handleEvents(event);
        }
        update();
        render();
    }
}

void Client::handleEvents(sf::Event event) {
    if (event.type == sf::Event::Closed)
        return window->close();
    if (event.type == sf::Event::MouseButtonPressed)
        return clickHandler(event);
    if (event.type == sf::Event::KeyPressed)
        return keyHandler(event);
}

void Client::clickHandler(sf::Event event) {
    bool buttonClicked = false;
    if (event.mouseButton.button == sf::Mouse::Left) {
        for (auto button : _buttons) {
            if (button->isMouseOver(_mousePosition)) {
                button->click();
                buttonClicked = true;
                break;
            }
        }
    }
    buttonClicked = (buttonClicked || _serverList->clickCheck(event));
    if (!buttonClicked) {
        /*
            if state == GAME
                shoot
        */
    }
}

void Client::keyHandler(sf::Event event) {
    if (event.key.code == sf::Keyboard::Escape) {
        window->close();
    }
    // controls
    if (this->_state == OFFLINE) {
        if (event.key.code == sf::Keyboard::Z) this->_game->addEvent(MOVE, UP, 1);
        if (event.key.code == sf::Keyboard::Q) this->_game->addEvent(MOVE, LEFT, 1);
        if (event.key.code == sf::Keyboard::S) this->_game->addEvent(MOVE, DOWN, 1);
        if (event.key.code == sf::Keyboard::D) this->_game->addEvent(MOVE, RIGHT, 1);
        if (event.key.code == sf::Keyboard::Space) this->_game->addEvent(SHOOT, RIGHT, 1);

        if (event.key.code == sf::Keyboard::I) this->_game->addEvent(MOVE, UP, 2);
        if (event.key.code == sf::Keyboard::J) this->_game->addEvent(MOVE, LEFT, 2);
        if (event.key.code == sf::Keyboard::K) this->_game->addEvent(MOVE, DOWN, 2);
        if (event.key.code == sf::Keyboard::L) this->_game->addEvent(MOVE, RIGHT, 2);
        if (event.key.code == sf::Keyboard::Enter) this->_game->addEvent(SHOOT, RIGHT, 2);
    }

    if (this->_state == GAME) {
        if (event.key.code == sf::Keyboard::Z) this->_game_server->sendCommand(std::string("action-" + std::to_string(MOVE) + "_" + std::to_string(UP)));
        if (event.key.code == sf::Keyboard::Q) this->_game_server->sendCommand(std::string("action-" + std::to_string(MOVE) + "_" + std::to_string(LEFT)));
        if (event.key.code == sf::Keyboard::S) this->_game_server->sendCommand(std::string("action-" + std::to_string(MOVE) + "_" + std::to_string(DOWN)));
        if (event.key.code == sf::Keyboard::D) this->_game_server->sendCommand(std::string("action-" + std::to_string(MOVE) + "_" + std::to_string(RIGHT)));
        if (event.key.code == sf::Keyboard::Space) this->_game_server->sendCommand(std::string("action-" + std::to_string(SHOOT) + "_" + std::to_string(RIGHT)));
    }
}

void Client::update() {
 //this is where get info from the network thread to be handled
    if (this->_state == GAME || this->_state == OFFLINE) {
        if (!this->_gameEntities.size())
            this->loadState(MENU);
    }
    _serverList->update();
    _movement.x = 2;
    _movement.y = 0;
}

void Client::drawButtons() {
    if (_serverList->getShow() == true) {
        _serverList->draw();
    }
    for (auto button : _buttons) {
        button->draw(window);
    }
}

void Client::drawGameSpritesFromGameEntities(std::vector<std::pair<EntityList, std::pair<int, int>>> gameEntities)
{
    sf::Sprite tempSprite;
    sf::Texture texture;
    int nb_missile;

    static sf::Clock animationClock;
    static int animationState = 0;

    if (animationClock.getElapsedTime().asMilliseconds() > 100) {
        animationState = (animationState + 1) % 21;
        animationClock.restart();
    }

    for (int i = 0; gameEntities.size() != i; i++) {
        switch (gameEntities.at(i).first) {
            case SPACESHIP:
                if (i == 0)
                    texture.loadFromFile(std::string("../client/assets/r-type/r-typesheet5.gif"));
                if (i == 1)
                    texture.loadFromFile(std::string("../client/assets/r-type/r-typesheet5b.gif"));
                if (i == 2)
                    texture.loadFromFile(std::string("../client/assets/r-type/r-typesheet5c.gif"));
                if (i == 3)
                    texture.loadFromFile(std::string("../client/assets/r-type/r-typesheet5d.gif"));
                tempSprite = sf::Sprite(texture, sf::IntRect(32 * (animationState % 7), 0, 32, 32));
                tempSprite.setPosition(sf::Vector2f(gameEntities.at(i).second.first - ((animationState % 7) * 2), gameEntities.at(i).second.second));
                tempSprite.setScale(sf::Vector2f(3, 3));
                window->draw(tempSprite);
                break;
            case MISSILE:
                nb_missile++;
                if (nb_missile > this->old_missile_nb) this->shootsThread.push_back(std::thread([this]() { playShotSound(); }));
                texture.loadFromFile(std::string("../client/assets/r-type/r-typesheet30a.gif"));
                tempSprite = sf::Sprite(texture, sf::IntRect(34 * (animationState % 3), 0, 34, 34));
                tempSprite.setPosition(sf::Vector2f(gameEntities.at(i).second.first, gameEntities.at(i).second.second));
                tempSprite.setScale(sf::Vector2f(2, 2));
                window->draw(tempSprite);
                break;
            case ENNEMY:
                texture.loadFromFile(std::string("../client/assets/r-type/r-typesheet26.gif"));
                tempSprite = sf::Sprite(texture, sf::IntRect(65 * (animationState % 3), 0, 65, 50));
                tempSprite.setPosition(sf::Vector2f(gameEntities.at(i).second.first, gameEntities.at(i).second.second));
                tempSprite.setScale(sf::Vector2f(3, 3));
                window->draw(tempSprite);
                break;
            default:
                break;
        }
    }
    for (auto it = shootsThread.begin(); it != shootsThread.end();) {
        if (!it->joinable()) {
            it = shootsThread.erase(it);
        } else {
            ++it;
        }
    }
    this->old_missile_nb = nb_missile;
}

void Client::playShotSound()
{
    sf::Sound sound;
    sound.setBuffer(this->shootBuffer);
    sound.play();
    while (sound.getStatus() == sf::SoundSource::Status::Playing);
}

void Client::render() {
    window->clear(sf::Color::Black);
    _background->draw(window, _movement);

    // draw other stuff
    // last things drawn are on top
    drawButtons();

    if (this->_state == OFFLINE) this->drawGameSpritesFromGameEntities(this->_gameEntities);
    if (this->_state == GAME) {
        this->_gameEntitiesMutex.lock();
        this->drawGameSpritesFromGameEntities(this->_gameEntities);
        this->_gameEntitiesMutex.unlock();
    }

    window->display();
}

Client::~Client()
{
    this->_readServerInfoThread.join();
    delete _background;
}

std::vector<std::pair<EntityList, std::pair<int, int>>> UdpClient::getGameEntitiesViaMessage(std::string message) {
    std::vector<std::pair<EntityList, std::pair<int, int>>> gameEntities;
    std::istringstream ss(message);
    std::string entityInfo;
    int params[3];
    while (std::getline(ss, entityInfo, '_')) {
        std::istringstream entityStream(entityInfo);
        std::string entityName;

        for (int i = 0; i != 3; i++) {
            getline(entityStream, entityName, '.');
            params[i] = std::atoi(entityName.c_str());
        }
        gameEntities.push_back(std::make_pair(EntityList(params[0]), std::make_pair(params[1], params[2])));
    }

    return gameEntities;
}