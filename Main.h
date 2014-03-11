#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <SFML/UI.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <cstdlib>

#define LAUNCHER_WIDTH_X 800
#define LAUNCHER_HEIGHT_Y 640

#define LOGIN_PORT 23291
#define LOGIN_IP "cho-patate.zapto.org"

enum LoginPacketId //Stored in sf::Uint8
{
    LOGIN = 0,
    SUCCESS = 1,
    FAIL = 2
};

enum LoginErrorId //Stored in sf::Uint8
{
    NONE = -1,
    INTERNAL_ERROR = 0,
    UNKNOWN_USER = 1,
    BAD_PASSWORD = 2,
    BAD_REQUEST = 3
};


#endif // MAIN_H_INCLUDED
