#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>

void logScreenModes()
{
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

    for (std::size_t i = 0; i < modes.size(); ++i)
    {
        sf::VideoMode mode = modes[i];
        std::cout << "Mode #" << i << ": "
                  << mode.size.x << "x" << mode.size.y << " - "
                  << mode.bitsPerPixel << " bpp" << std::endl;
    }
}

void logCollision(sf::Vector2f firstObject, sf::Vector2f secondObject)
{
    std::cout << "Collision Detected:"
              << "player: X - " << firstObject.x
              << "player: Y - " << firstObject.y
              << "enemy: X - " << secondObject.x
              << "enemy: Y - " << secondObject.y << std::endl;
}

bool hasCollision(sf::FloatRect mainObject, const std::vector<sf::FloatRect> &collidables)
{
    for (const auto &collidable : collidables)
    {
        if (mainObject.findIntersection(collidable))
        {
            return true;
        }
    }

    return false;
}

// Implement camera movement
// 1. If the object goes left or fight of the screen we should move the camera with it
// 2. The ground should be large
// 3. The ground should be infinite

// Move the object if it is on the ground

// Implement gravity
// [V] 1. Make the object move on its own
// 2. Find a way to change the text in the text object
// 3. Display the speed of the object while moving it
// 4. Make the object to accelerate
// 5. Accelerate with the gravity

// Implement bounce

// Implement Jump
// [V] 1. Disable gravity while jumping

int main()
{
    logScreenModes();

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode({1024, 768}, desktop.bitsPerPixel), "SFML Keyboard Interaction");

    sf::View gameView(sf::FloatRect({0.f, 0.f}, {1024.0f, 768.0f}));

    sf::Font font("arial.ttf");
    sf::Text text(font);
    text.setString("Stats: ");
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::Red);
    text.setPosition(sf::Vector2f(350.0f, 10.0f));

    sf::CircleShape player(40);
    player.setFillColor(sf::Color::Yellow);
    player.setPosition(sf::Vector2f(375.0f, 275.0f));

    sf::RectangleShape ground(sf::Vector2f(2000.0f, 100.0f));
    ground.setFillColor(sf::Color::Green);
    ground.setPosition(sf::Vector2f(0.0f, 700.0f));

    sf::RectangleShape obstacle_1(sf::Vector2f(200.0f, 100.0f));
    obstacle_1.setFillColor(sf::Color::Magenta);
    obstacle_1.setPosition(sf::Vector2f(600.0f, 400.0f));

    sf::RectangleShape obstacle_2(sf::Vector2f(200.0f, 100.0f));
    obstacle_2.setFillColor(sf::Color::Magenta);
    obstacle_2.setPosition(sf::Vector2f(1000.0f, 300.0f));

    sf::RectangleShape obstacle_3(sf::Vector2f(400.0f, 200.0f));
    obstacle_3.setFillColor(sf::Color::Magenta);
    obstacle_3.setPosition(sf::Vector2f(1500.0f, 200.0f));

    while (window.isOpen())
    {
        while (std::optional<sf::Event> eventOpt = window.pollEvent())
        {
            if (eventOpt->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        sf::Vector2f offset(0.0f, 0.0f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            offset.x -= 0.2f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            offset.x += 0.2f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            offset.y -= 0.3f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            offset.y += 0.3f;
        }

        offset.y += 0.2f;

        sf::Vector2f originalPosition = player.getPosition();
        sf::Vector2f originalViewCenter = gameView.getCenter();

        player.move(sf::Vector2f(offset.x, 0));
        gameView.move(sf::Vector2f(offset.x, 0));

        std::vector<sf::FloatRect> collidables = {
            ground.getGlobalBounds(),
            obstacle_1.getGlobalBounds(),
            obstacle_2.getGlobalBounds(),
            obstacle_3.getGlobalBounds(),
        };

        if (hasCollision(player.getGlobalBounds(), collidables))
        {
            player.setPosition(sf::Vector2f(originalPosition.x, player.getPosition().y));
            gameView.setCenter(sf::Vector2f(originalViewCenter.x, gameView.getCenter().y));
        }

        player.move(sf::Vector2f(0, offset.y));
        gameView.move(sf::Vector2f(0, offset.y));

        if (hasCollision(player.getGlobalBounds(), collidables))
        {
            player.setPosition(sf::Vector2f(player.getPosition().x, originalPosition.y));
            gameView.setCenter(sf::Vector2f(gameView.getCenter().x, originalViewCenter.y));
        }

        window.clear(sf::Color::Blue);
        window.setView(gameView);
        window.draw(text);
        window.draw(player);
        window.draw(obstacle_1);
        window.draw(obstacle_2);
        window.draw(obstacle_3);
        window.draw(ground);
        window.display();
    }

    return 0;
}