#ifndef Denholm_Jen_MainMenu_hpp
#define Denholm_Jen_MainMenu_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <optional>

using namespace sf;
using namespace std;

enum class AnimationState
{
    WalkOn,
    Wait,
    WalkOff
};

class SpriteSwapAnimation
{
private:
    optional<Sprite>* _DenholmSprite;
    optional<Sprite>* _Denholm_FootTapSprite;
    optional<Sprite>* _Denholm_BlinkSprite;
    optional<Sprite>* _Denholm_RightMovingSprite;
    optional<Sprite>* _Denholm_RightWalkSprite;

    Clock _animationClock;
    float _animationTimer;
    bool _showFootTap;

    int _currentTapCount;
    int _maxTapCount = 4;
    bool _isTapping;
    float _pauseDuration;
    Clock _pauseClock;

    Clock _blinkClock;
    float _blinkInterval;
    float _blinkDuration;
    bool _isBlinking;
    Clock _blinkTimer;

    AnimationState _currentState;
    Clock _stateClock; 
    bool _showWalkFrame; 
    float _walkFrameInterval;

    Vector2f _offScreenPosition;
    Vector2f _WaitPosition; 
    float _MoveSpeed;


public:
    SpriteSwapAnimation(optional<Sprite> &denholmSprite, optional<Sprite> &denholmFootTapSprite, optional<Sprite> &denholmBlinkSprite, optional<Sprite> &denholmMoveRight, optional<Sprite> &denholmWalkRight,int maxTapCount = 4, float animationTimer = 0.5f)
    {
        cout << "=== SpriteSwapAnimation Constructor Called ===" << endl;
        _DenholmSprite = &denholmSprite;
        _Denholm_FootTapSprite = &denholmFootTapSprite;
        _Denholm_BlinkSprite = &denholmBlinkSprite;
        _Denholm_RightMovingSprite = &denholmMoveRight;
        _Denholm_RightWalkSprite = &denholmWalkRight;
        _animationTimer = animationTimer;

        //Wait phase
        _showFootTap = false;
        _currentTapCount = 0;
        _isTapping = false;
        _pauseDuration = 1.0f;
        _pauseClock.restart();
        _blinkInterval = 3.0f;
        _blinkDuration = 0.2f;
        _isBlinking = false;
        _blinkTimer.restart();

        _currentState = AnimationState::WalkOn;
        _stateClock.restart();
        _showWalkFrame = false;
        _walkFrameInterval = 0.4f;
        _offScreenPosition = {-200.f, 288.f};
        _WaitPosition = {150.f, 288.f};
        _MoveSpeed = 100.f;

        cout << "Animation initialized - offscreen Y: " << _offScreenPosition.y << ", wait Y: " << _WaitPosition.y << endl;

        // Start at off-screen position
        if (_DenholmSprite->has_value())
        {
            _DenholmSprite->value().setPosition(_offScreenPosition);
            cout << "Set sprite position to: " << _offScreenPosition.x << ", " << _offScreenPosition.y << endl;
        }
        if (_Denholm_FootTapSprite->has_value())
        {
            _Denholm_FootTapSprite->value().setPosition(_offScreenPosition);
        }
        if (_Denholm_BlinkSprite->has_value())
        {
            _Denholm_BlinkSprite->value().setPosition(_offScreenPosition);
        }
        if (_Denholm_RightMovingSprite->has_value())
        {
            _Denholm_RightMovingSprite->value().setPosition(_offScreenPosition);
        }
        if (_Denholm_RightWalkSprite->has_value())
        {
            _Denholm_RightWalkSprite->value().setPosition(_offScreenPosition);
        }

    }

    void Update()
    {
        if (!_isBlinking && _blinkTimer.getElapsedTime().asSeconds() >= _blinkInterval)
        {
            _isBlinking = true;
            _blinkTimer.restart();
        }
        else if (_isBlinking && _blinkTimer.getElapsedTime().asSeconds() >= _blinkDuration)
        {
            _isBlinking = false;
            _blinkTimer.restart();
        }

        switch (_currentState)
        {
        case AnimationState::WalkOn:
            UpdateWalkingOn();
            break;
        case AnimationState::Wait:
            UpdateWaiting();
            break;
        case AnimationState::WalkOff:
            UpdateWalkingOff();
            break;
        }
    }

    void UpdateWalkingOn()
    {
        // Animate walking frames
        if (_animationClock.getElapsedTime().asSeconds() >= _walkFrameInterval)
        {
            _showWalkFrame = !_showWalkFrame;
            _animationClock.restart();
        }

        // Move the sprite
        float deltaTime = _stateClock.getElapsedTime().asSeconds();
        _stateClock.restart();
        
        if (_DenholmSprite->has_value())
        {
            Vector2f currentPos = _DenholmSprite->value().getPosition();
            currentPos.x += _MoveSpeed * deltaTime;

            UpdateAllSpritesPosition(currentPos);

            if (currentPos.x >= _WaitPosition.x)
            {
                UpdateAllSpritesPosition(_WaitPosition);
                _currentState = AnimationState::Wait;
                _currentTapCount = 0;
                _showFootTap = false;
                _isTapping = false;
                _animationClock.restart();
                _stateClock.restart();
            }
        }
    }

    void UpdateWaiting()
    {
        if (_isTapping)
        {
            if (_pauseClock.getElapsedTime().asSeconds() >= _pauseDuration)
            {
                // Tapping complete, move to walking off
                _currentState = AnimationState::WalkOff;
                _stateClock.restart();
                _animationClock.restart();
                _showWalkFrame = false;
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

    void UpdateWalkingOff()
    {
        // Animate walking frames
        if (_animationClock.getElapsedTime().asSeconds() >= _walkFrameInterval)
        {
            _showWalkFrame = !_showWalkFrame;
            _animationClock.restart();
        }

        // Move sprite to the left (back off screen)
        float deltaTime = _stateClock.getElapsedTime().asSeconds();
        _stateClock.restart();
        
        if (_DenholmSprite->has_value())
        {
            Vector2f currentPos = _DenholmSprite->value().getPosition();
            currentPos.x -= _MoveSpeed * deltaTime;  // Subtract to move left
            
            // Update all sprite positions
            UpdateAllSpritesPosition(currentPos);

            // Check if off screen left
            if (currentPos.x <= _offScreenPosition.x)
            {
                // Reset to beginning
                UpdateAllSpritesPosition(_offScreenPosition);
                _currentState = AnimationState::WalkOn;
                _animationClock.restart();
                _stateClock.restart();
                _showWalkFrame = false;
            }
        }
    }

    void UpdateAllSpritesPosition(const Vector2f& position)
    {
        if (_DenholmSprite->has_value())
            _DenholmSprite->value().setPosition(position);
        if (_Denholm_FootTapSprite->has_value())
            _Denholm_FootTapSprite->value().setPosition(position);
        if (_Denholm_BlinkSprite->has_value())
            _Denholm_BlinkSprite->value().setPosition(position);
        if (_Denholm_RightMovingSprite->has_value())
            _Denholm_RightMovingSprite->value().setPosition(position);
        if (_Denholm_RightWalkSprite->has_value())
            _Denholm_RightWalkSprite->value().setPosition(position);
    }

    void draw(RenderTarget &target)
    {
        if (_isBlinking && _Denholm_BlinkSprite->has_value())
        {
            target.draw(_Denholm_BlinkSprite->value());
            return;
        }

        // Draw based on current state
        switch (_currentState)
        {
            case AnimationState::WalkOn:
            case AnimationState::WalkOff:
                if (_showWalkFrame && _Denholm_RightWalkSprite->has_value())
                {
                    target.draw(_Denholm_RightWalkSprite->value());
                }
                else if (_Denholm_RightMovingSprite->has_value())
                {
                    target.draw(_Denholm_RightMovingSprite->value());
                }
                break;
                
            case AnimationState::Wait:
                if (_showFootTap && _Denholm_FootTapSprite->has_value())
                {
                    target.draw(_Denholm_FootTapSprite->value());
                }
                else if (_DenholmSprite->has_value())
                {
                    target.draw(_DenholmSprite->value());
                }
                break;
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

    void setBlinkInterval(float seconds)
    {
        _blinkInterval = seconds;
    }

    void setBlinkDuration(float seconds)
    {
        _blinkDuration = seconds;
    }

    void setMoveSpeed(float speed)
    {
        _MoveSpeed = speed;
    }

    void setPositions(Vector2f offscreen, Vector2f wait)
    {
        _offScreenPosition = offscreen;
        _WaitPosition = wait;
    }
};

#endif