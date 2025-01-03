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

int main()
{
    logScreenModes();

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode({1024, 768}, desktop.bitsPerPixel), "SFML Keyboard Interaction");

    sf::Font font("arial.ttf");
    sf::Text text(font);
    text.setString("Hello world");
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::Red);
    text.setPosition(sf::Vector2f(350.0f, 10.0f));
    // text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    // Implement camera movement
    // 1. If the object goes left or fight of the screen we should move the camera with it
    // 2. The ground should be large
    // 3. The ground should be infinite

    // Implement gravity
    // 1. Find a way to change the text in the text object
    // 2. Display the speed of the object while moving it
    // 3. Make the object move on its own
    // 4. Make the object to accelerate
    // 5. Accelerate with the gravity

    // Implement Jump
    // 1. Disable gravity while jumping

    sf::CircleShape player(50);
    player.setFillColor(sf::Color::Yellow);
    player.setPosition(sf::Vector2f(375.0f, 275.0f));

    sf::RectangleShape ground(sf::Vector2f(700.0f, 100.0f));
    ground.setFillColor(sf::Color::Green);
    ground.setPosition(sf::Vector2f(0.0f, 700.0f));

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
        sf::Vector2f originalPosition = player.getPosition();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            offset.x -= 0.5f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            offset.x += 0.5f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            offset.y -= 0.5f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            offset.y += 0.5f;
        }

        // Gravity
        offset.y += 0.1f;

        player.move(offset);

        if (ground.getGlobalBounds().findIntersection(player.getGlobalBounds()))
        {
            int playerBoundsX = player.getGlobalBounds().position.x;
            int playerBoundsY = player.getGlobalBounds().position.y;

            int enemyBoundsX = ground.getGlobalBounds().position.x;
            int enemyBoundsY = ground.getGlobalBounds().position.y;

            std::cout << "Collision Detected:"
                      << "player: X - " << playerBoundsX
                      << "player: Y - " << playerBoundsY
                      << "enemy: X - " << enemyBoundsX
                      << "enemy: Y - " << enemyBoundsY << std::endl;

            player.setPosition(originalPosition);
        }

        window.clear(sf::Color::Blue);

        window.draw(text);
        window.draw(player);
        window.draw(ground);

        window.display();
    }

    return 0;
}