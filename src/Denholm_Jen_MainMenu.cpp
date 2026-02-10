#ifndef Denholm_Jen_MainMenu_hpp
#define Denholm_Jen_MainMenu_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <optional>

using namespace sf;
using namespace std;

// class SpriteSwapAnimation
// {
//     private:
//     Texture _DenholmTexture;
//     optional<Sprite> _DenholmSprite;
//     Texture _Denholm_FootTapTexture;
//     optional<Sprite> _Denholm_FootTapSprite;

//     public:
//     SpriteSwapAnimation()
// }
// {
//     if (!_DenholmTexture.loadFromFile("assets/Main Menu Assets/Denholm.png"))
//     {
//         cerr << "Failed to load Denholm texture!" << std::endl;
//         return;
//     }
//     _DenholmSprite.emplace(_DenholmTexture);
//     _DenholmSprite->setOrigin({_DenholmTexture.getSize().x / 2.f, _DenholmTexture.getSize().y / 2.f});
//     _DenholmSprite->setScale({5.5f, 5.5f});

//     if (!_Denholm_FootTapTexture.loadFromFile("assets/Main Menu Assets/Denholm_FootTap.png"))
//     {
//         cerr << "Failed to load Denholm Foot Tap texture!" << std::endl;
//         return;
//     }
//     _Denholm_FootTapSprite.emplace(_Denholm_FootTapTexture);
//     _Denholm_FootTapSprite->setOrigin({_Denholm_FootTapTexture.getSize().x / 2.f, _Denholm_FootTapTexture.getSize().y / 2.f});
//     _Denholm_FootTapSprite->setScale({5.5f, 5.5f});
// }


#endif