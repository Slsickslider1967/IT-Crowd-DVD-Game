#ifndef Denholm_Jen_MainMenu_hpp
#define Denholm_Jen_MainMenu_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <optional>

using namespace sf;
using namespace std;

class SpriteSwapAnimation
{
private:
    optional<Sprite>* _DenholmSprite;
    optional<Sprite>* _Denholm_FootTapSprite;

    Clock _animationClock;
    float _animationTimer;
    bool _showFootTap;

    int _currentTapCount;
    int _maxTapCount = 4;
    bool _isTapping;
    float _pauseDuration;
    Clock _pauseClock;

public:
    SpriteSwapAnimation(optional<Sprite> &denholmSprite, optional<Sprite> &denholmFootTapSprite, int maxTapCount = 4, float animationTimer = 0.5f)
    {
        _DenholmSprite = &denholmSprite;
        _Denholm_FootTapSprite = &denholmFootTapSprite;
        _animationTimer = animationTimer;
        _showFootTap = false;
        _currentTapCount = 0;
        _isTapping = false;
        _pauseDuration = 1.0f;
        _pauseClock.restart();
    }

    void Update()
    {
        if (_isTapping)
        {
            if (_pauseClock.getElapsedTime().asSeconds() >= _pauseDuration)
            {
                _isTapping = false;
                _currentTapCount = 0;
                _animationClock.restart();
            }
            return; // Don't animate during pause
        }

        if (_animationClock.getElapsedTime().asSeconds() >= _animationTimer)
        {
            _showFootTap = !_showFootTap;
            _animationClock.restart();
            
            if (_showFootTap)
            {
                _currentTapCount++;
                
                if (_currentTapCount >= _maxTapCount)
                {
                    _isTapping = true;
                    _showFootTap = false;
                    _pauseClock.restart();
                }
            }
        }
    }

    void draw(RenderTarget &target)
    {
        if (_showFootTap && _Denholm_FootTapSprite->has_value())
        {
            target.draw(_Denholm_FootTapSprite->value());
        }
        else if (_DenholmSprite->has_value())
        {
            target.draw(_DenholmSprite->value());
        }
    }

    void setAnimationTimer(float seconds)
    {
        _animationTimer = seconds;
    }
    
    void setMaxTaps(int taps)
    {
        _maxTapCount = taps;
    }
    
    void setPauseDuration(float seconds)
    {
        _pauseDuration = seconds;
    }
};

#endif