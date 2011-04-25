#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Window");
	App.SetFramerateLimit(60);
	while (App.IsOpened()) {
		sf::Event Event;
		while (App.GetEvent(Event)) {
			// Window closed
			if (Event.Type == sf::Event::Closed)
				App.Close();
			// Escape key pressed
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
				App.Close();
		}
		// Clear the screen (fill it with black color)
       App.Clear(sf::Color(200, 200, 0));

        // Display window contents on screen
        App.Display();
	}
	return EXIT_SUCCESS;
}
