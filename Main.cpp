#include "Main.h"

bool login(false);
sf::String username, password, session;
LoginErrorId error(NONE);
int loopLeft(10);

void connect()
{
    sf::TcpSocket socket;
    std::cout << "Connecting to the login server ..." << std::endl;
    
    if (socket.connect(LOGIN_IP, LOGIN_PORT) == sf::Socket::Done)
    {
        sf::Packet packet;
        packet << (sf::Uint8) LOGIN << username << password;
        socket.send(packet);
        
        sf::Packet loginResponse;
        socket.receive(loginResponse);
        sf::Uint8 packetId;
        loginResponse >> packetId;
        
        if (packetId == SUCCESS)
        {
            login = true;
            loginResponse >> session;
            std::cout << "Logged in !" << std::endl;
        }
        else if (packetId == FAIL)
        {
            sf::Uint8 errorId;
            loginResponse >> errorId;
            error = static_cast<LoginErrorId>(errorId);
            std::cout << "Login fail, error : " << (short) errorId << std::endl;
        } 
        else
        {
            error = BAD_REQUEST;
        }
    }
    else
    {
        error = INTERNAL_ERROR;
        std::cout << "Can't connect to the server" << std::endl;
    }
}

void launch()
{
    //TODO
    std::cout << "Launching world-of-sea-client with session : " << session.toAnsiString() << std::endl;
}

sf::String getErrorMessage()
{
    switch(error)
    {
    case NONE:
        return "";
    case INTERNAL_ERROR:
        return "An error has occured, is the server running ?";
    case UNKNOWN_USER:
        return "Uknown username, are you registered ?";
    case BAD_PASSWORD:
        return "The given password is wrong";
    case BAD_REQUEST:
        return "Bad request sent/received, is the launcher up to date ?";
    default:
        return "Unknown error";
    }
}

int main(int argc, char*argv[])
{
    // DECLARATION
    sf::RenderWindow window(sf::VideoMode(LAUNCHER_WIDTH_X, LAUNCHER_HEIGHT_Y), "World of Sea", sf::Style::Titlebar | sf::Style::Close);
    sf::Event event;
    sf::Font fontArial, fontCaribbean, fontFlogged;
    sf::Texture textureTextfield, textureTextfieldFocus, textureBackground, textureButton, textureButtonFocus;
    //

    // INITIALISATION
    fontArial.loadFromFile("resources/fonts/arial.ttf");
    fontCaribbean.loadFromFile("resources/fonts/Caribbean.ttf");
    fontFlogged.loadFromFile("resources/fonts/Flogged.ttf");

    textureBackground.loadFromFile("resources/sprites/background.jpg");

    textureTextfield.loadFromFile("resources/sprites/textfield.png");
	textureTextfieldFocus.loadFromFile("resources/sprites/textfieldFocus.png");

	textureButton.loadFromFile("resources/sprites/button.png");
	textureButtonFocus.loadFromFile("resources/sprites/buttonFocus.png");
    //

    // LABEL
    // Background
    sf::ui::Label labelBackground(textureBackground);
    //

    // Title
    sf::ui::Label labelTitle(fontFlogged, "World of Sea");
    labelTitle.setFontColor(sf::Color::Black);
    labelTitle.move(LAUNCHER_WIDTH_X/3, LAUNCHER_HEIGHT_Y/12);
    labelTitle.setFontSize(75);
    //

    // Login
    sf::ui::Label labelLogin(fontCaribbean, "Username:");
    labelLogin.setFontColor(sf::Color::Black);
    labelLogin.move(LAUNCHER_WIDTH_X/10, LAUNCHER_HEIGHT_Y/3.5);
    //

    // Password
    sf::ui::Label labelPassword(fontCaribbean, "Password:");
    labelPassword.setFontColor(sf::Color::Black);
    labelPassword.move(LAUNCHER_WIDTH_X/10, LAUNCHER_HEIGHT_Y/2);
    //
    //

    // Text field
    // Username
    sf::ui::TextField textfieldLogin(textureTextfield, textureTextfieldFocus, fontArial, "");
    textfieldLogin.setFontSize(30);
    textfieldLogin.move(LAUNCHER_WIDTH_X/2.5, LAUNCHER_HEIGHT_Y/3.5);
    textfieldLogin.setFontColor(sf::Color::Black);
    textfieldLogin.setCanBeEmpty(false);
    textfieldLogin.setMaxLength(16);
    //

    // Password
    sf::ui::TextField textfieldPassword(textureTextfield, textureTextfieldFocus, fontArial, "");
    textfieldPassword.setFontSize(30);
    textfieldPassword.move(LAUNCHER_WIDTH_X/2.5, LAUNCHER_HEIGHT_Y/2);
    textfieldPassword.setFontColor(sf::Color::Black);
    textfieldPassword.setCanBeEmpty(false);
    textfieldPassword.setMaxLength(16);
    //
    //

    // Button
    sf::ui::Button button(connect, textureButton, textureButtonFocus, textureButtonFocus);
	button.move(LAUNCHER_WIDTH_X/2.5, LAUNCHER_HEIGHT_Y/1.5);
	//
	
	//Result label
	sf::ui::Label result(fontCaribbean, "");
    result.move(LAUNCHER_WIDTH_X/3, LAUNCHER_HEIGHT_Y/1.5 + 60);
    result.setFontSize(18);

    while (window.isOpen())
	{
		window.waitEvent(event);

		if (event.type == sf::Event::Closed)
			window.close();

        //Input
        textfieldLogin.updateEvent(event);
        textfieldPassword.updateEvent(event);

        button.updateEvent(event);
        //
        
        username = textfieldLogin.getText();
        password = textfieldPassword.getText();

        // Output
        window.clear(sf::Color::White);

        window.draw(labelBackground);
        window.draw(labelTitle);
        window.draw(labelLogin);
        window.draw(labelPassword);

        window.draw(textfieldLogin);
        window.draw(textfieldPassword);

        window.draw(button);
        
        window.draw(result);

        window.display();
        //
        
        if (login)
        {
            result.setFontColor(sf::Color::Green);
            result.setText("Logged in successfully");
            window.display();
            
            if (loopLeft <= 0)
                window.close();
            else
                loopLeft--;
        }
        else
        {
            result.setFontColor(sf::Color::Red);
            result.setText(getErrorMessage());
        }
	}
	
	if (login)
	    launch();

    return 0;
}
