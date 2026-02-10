#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;
using namespace std;

// Global variables for delta time
Clock _deltaClock;
Time _deltaTime;

Shader _screenEffeectShaders;
Shader _interlaceShader;

// Game resources
Font _font;
SoundBuffer _soundBuffer;
optional<Sound> _sound;
optional<Sprite> _sprite;
optional<Text> _MainMenuText;
Music _music;

//Main menu resources
Texture _DenholmTexture;
optional<Sprite> _DenholmSprite;
Texture _Denholm_FootTapTexture;
optional<Sprite> _Denholm_FootTapSprite; 
optional<Sprite> _RoySprite;
optional<Sprite> _MossSprite;
optional<Sprite> _JenSprite;

optional<Sprite> _PlayAllButtonSprite;
optional<Sprite> _EpisodeSelectButtonSprite;
optional<Sprite> _ExtrasButtonSprite;
optional<Sprite> _SetUPButtonSprite; 

optional<Sound> _MenuMusic;

RenderTexture _renderTexture;

// Resources
Vector2f _MainTitlePosition = {512.f, 50.f};

/// Function prototypes
void DrawMainMenu(RenderTarget &_window);


void Initialize()
{
    /// <summary>
    /// Initializes game resources and states.
    /// Put your initialization code here.
    /// </summary>
    cout << "Game initialized!" << std::endl;
}


void LoadContent()
{
    /// <summary>
    /// Loads game assets such as textures, fonts, and sounds.
    /// Put your asset loading code here.
    /// </summary>

    // Main menu font
    if (!_font.openFromFile("assets/fonts/ITC Machine Regular.otf"))
    {
        cerr << "Failed to load font!" << std::endl;
        return;
    }

    _MainMenuText.emplace(_font);
    _MainMenuText->setString("THE IT CROWD");
    _MainMenuText->setCharacterSize(48);
    _MainMenuText->setPosition(_MainTitlePosition);
    _MainMenuText->setFillColor(Color(254, 140, 18));

    _renderTexture.resize({1024, 576});

    //Screen effect shader
    if (!_screenEffeectShaders.loadFromFile("assets/shaders/Screen_Effect.frag", Shader::Type::Fragment))
    {
        cerr << "Failed to load screen effect shader!" << std::endl;
        return;
    }

    //Main menu Denholm
    if (!_DenholmTexture.loadFromFile("assets/textures/Denholm.png"))
    {
        cerr << "Failed to load Denholm texture!" << std::endl;
        return;
    }
    _DenholmSprite.emplace(_DenholmTexture);
    _DenholmSprite->setOrigin({_DenholmTexture.getSize().x / 2.f, _DenholmTexture.getSize().y / 2.f});
    _DenholmSprite->setScale({5.5f, 5.5f});

    if (!_Denholm_FootTapTexture.loadFromFile("assets/textures/Denholm_FootTap.png"))
    {
        cerr << "Failed to load Denholm Foot Tap texture!" << std::endl;
        return;
    }
    _Denholm_FootTapSprite.emplace(_Denholm_FootTapTexture);
    _Denholm_FootTapSprite->setOrigin({_Denholm_FootTapTexture.getSize().x / 2.f, _Denholm_FootTapTexture.getSize().y / 2.f});
    _Denholm_FootTapSprite->setScale({5.5f, 5.5f});



    _screenEffeectShaders.setUniform("texture", Shader::CurrentTexture);
    _screenEffeectShaders.setUniform("offset", 0.008f);
    _screenEffeectShaders.setUniform("intensity", 0.2f);
    _screenEffeectShaders.setUniform("Scanlines", 2.5f);
    
    cout << "Chromatic aberration shader loaded successfully!" << std::endl;



    cout << "Game content loaded!" << std::endl;
}


void Update()
{
    /// <summary>
    /// Updates game logic and states.
    /// Put your game update code here.
    /// </summary>
    _deltaTime = _deltaClock.restart();

    static float DenholmFootTapTimer = 0.f;
    DenholmFootTapTimer += _deltaTime.asSeconds();

    if (DenholmFootTapTimer >= 0.2f)
    {
        if (_DenholmSprite.has_value() && _Denholm_FootTapSprite.has_value())
        {
            swap(*_DenholmSprite, *_Denholm_FootTapSprite);
        }
        DenholmFootTapTimer = 0.f;
    }

}


FloatRect GetAspectRatio(VideoMode desktopMode)
{
    float targetAspect = 16.f / 9.f;
    float screenAspect = static_cast<float>(desktopMode.size.x) / static_cast<float>(desktopMode.size.y);

    cout << "Screen resolution: " << desktopMode.size.x << "x" << desktopMode.size.y << endl;
    cout << "Target aspect: " << targetAspect << endl;
    cout << "Screen aspect: " << screenAspect << endl;

    FloatRect viewport;
    if (screenAspect > targetAspect)
    {
        float width = targetAspect / screenAspect;
        viewport = FloatRect({(1.f - width) / 2.f, 0.f}, {width, 1.f});
        cout << "Using pillarbox (vertical bars)" << endl;
        cout << "Viewport: x=" << viewport.position.x << " width=" << viewport.size.x << endl;
    }
    else
    {
        float height = screenAspect / targetAspect;
        viewport = FloatRect({0.f, (1.f - height) / 2.f}, {1.f, height});
        cout << "Using letterbox (horizontal bars)" << endl;
        cout << "Viewport: y=" << viewport.position.y << " height=" << viewport.size.y << endl;
    }
    return viewport;
}


void Draw(RenderWindow &_window)
{
    /// <summary>
    /// Renders game objects to the window.
    /// Put your drawing code here.
    /// </summary>

    _renderTexture.clear(Color::Black);
    DrawMainMenu(_renderTexture);
    _renderTexture.display();

    Sprite renderSprite(_renderTexture.getTexture());
    _window.draw(renderSprite, &_screenEffeectShaders);

    _window.display();
}


void Input(const optional<Event> *event, RenderWindow &_window)
{
    /// <summary>
    /// Handles user input events.
    /// Put your input handling code here.
    /// </summary>
    if (const auto *keyPressed = (*event)->getIf<Event::KeyPressed>())
    {
        if (keyPressed->code == Keyboard::Key::Escape)
            _window.close();

        if (keyPressed->code == Keyboard::Key::Space)
            cout << "Space key pressed!" << std::endl;
    }
}


void UnloadContent()
{
    /// <summary>
    /// Unloads game assets and cleans up resources.
    /// Put your cleanup code here.
    /// </summary>
    cout << "Game content unloaded!" << std::endl;
}


int main()
{
    VideoMode desktopMode = VideoMode::getDesktopMode();
    RenderWindow _window(desktopMode, "IT Crowd DVD Game", State::Fullscreen);
    _window.setFramerateLimit(25);
    FloatRect viewport = GetAspectRatio(desktopMode);

    View view(FloatRect({0.f, 0.f}, {1024.f, 576.f}));
    view.setViewport(viewport);
    _window.setView(view);

    Initialize();
    LoadContent();

    while (_window.isOpen())
    {
        while (auto event = _window.pollEvent())
        {
            if (event->is<Event::Closed>())
                _window.close();

            Input(&event, _window);
        }

        Update();

        _window.clear(Color::Black);
        Draw(_window);
    }

    UnloadContent();
    return 0;
}


void DrawMainMenu(RenderTarget &_window)
{
    RectangleShape background({1024.f, 576.f});
    background.setFillColor(Color(2, 82, 19));
    _window.draw(background);

    if (_MainMenuText.has_value())
    {
        FloatRect textBounds = _MainMenuText->getLocalBounds();
        float textWidth = textBounds.size.x;

        _MainMenuText->setPosition({_MainTitlePosition.x - textWidth / 2.f, _MainTitlePosition.y});

        _window.draw(*_MainMenuText);
    }
    
    if (_DenholmSprite.has_value())
    {
        _DenholmSprite->setPosition({100.f, 288.f});

        _window.draw(*_DenholmSprite);
    }

    //limit colour palette
}
