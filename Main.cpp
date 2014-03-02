#include "Main.h"

int main(int argc, char*argv[])
{
    // DECLARATION
    sf::RenderWindow window(sf::VideoMode(LAUNCHER_WIDTH_X, LAUNCHER_HEIGHT_Y), "World of Sea");
    sf::Event event;
    sf::Font fontArial;
    sf::Texture buttonImg, buttonFocImg;
    //

    // INITIALISATION
    fontArial.loadFromFile("resources/fonts/arial.ttf");
    buttonImg.loadFromFile("resources/sprites/button.png");
	buttonFocImg.loadFromFile("resources/sprites/button_focused.png");
    //

    // LABEL
        // Title
        sf::ui::Label labelTitle(fontArial, "World of Sea");
        labelTitle.setFontColor(sf::Color::Black);
        labelTitle.move(LAUNCHER_WIDTH_X/3, 0);
        //

        // Login
        sf::ui::Label labelLogin(fontArial, "Username:");
        labelLogin.setFontColor(sf::Color::Black);
        labelLogin.move(LAUNCHER_WIDTH_X/10, LAUNCHER_HEIGHT_Y/4);
        //

        // Password
        sf::ui::Label labelPassword(fontArial, "Password:");
        labelPassword.setFontColor(sf::Color::Black);
        labelPassword.move(LAUNCHER_WIDTH_X/10, LAUNCHER_HEIGHT_Y/2.5);
        //
    //

    // Text field
        // Username
        sf::ui::TextField textfieldLogin(buttonImg, buttonFocImg, fontArial, "");
        textfieldLogin.setFontSize(30);
        textfieldLogin.move(LAUNCHER_WIDTH_X/3, LAUNCHER_HEIGHT_Y/4);
        textfieldLogin.setFontColor(sf::Color::Black);
        textfieldLogin.setCanBeEmpty(true);
        textfieldLogin.setMaxLength(16);
        //

        // Password
        sf::ui::TextField textfieldPassword(buttonImg, buttonFocImg, fontArial, "");
        textfieldPassword.setFontSize(30);
        textfieldPassword.move(LAUNCHER_WIDTH_X/3, LAUNCHER_HEIGHT_Y/2.5);
        textfieldPassword.setFontColor(sf::Color::Black);
        textfieldPassword.setCanBeEmpty(true);
        textfieldPassword.setMaxLength(16);
        //
    //

    while (window.isOpen())
	{
		window.waitEvent(event);

		if (event.type == sf::Event::Closed)
			window.close();

        //Input
        textfieldLogin.updateEvent(event);
        textfieldPassword.updateEvent(event);
        //

        // Output
        window.clear(sf::Color::White);

        window.draw(labelTitle);
        window.draw(labelLogin);
        window.draw(labelPassword);

        window.draw(textfieldLogin);
        window.draw(textfieldPassword);

        window.display();
        //
	}

    return 0;
}
