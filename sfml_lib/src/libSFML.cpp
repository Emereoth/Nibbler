#include "../inc/libSFML.hpp"
#include <iostream>

Graphics::Graphics(size_t width, size_t height, float squareSize) : name(libName::SFML)
{
	_height = height;
	_width = width;
	_squareSize = squareSize;
	loadTexture(sprite::HEAD_UP, "./texture/headUp.png");
	loadTexture(sprite::HEAD_DOWN, "./texture/headDown.png");
	loadTexture(sprite::HEAD_LEFT, "./texture/headLeft.png");
	loadTexture(sprite::HEAD_RIGHT, "./texture/headRight.png");
	loadTexture(sprite::BODY_H, "./texture/bodyH.png");
	loadTexture(sprite::BODY_V, "./texture/bodyV.png");
	loadTexture(sprite::TAIL_UP, "./texture/tailUp.png");
	loadTexture(sprite::TAIL_DOWN, "./texture/tailDown.png");
	loadTexture(sprite::TAIL_LEFT, "./texture/tailLeft.png");
	loadTexture(sprite::TAIL_RIGHT, "./texture/tailRight.png");
	loadTexture(sprite::BODY_UP_LEFT, "./texture/bodyUpLeft.png");
	loadTexture(sprite::BODY_UP_RIGHT, "./texture/bodyUpRight.png");
	loadTexture(sprite::BODY_DOWN_LEFT, "./texture/bodyDownLeft.png");
	loadTexture(sprite::BODY_DOWN_RIGHT, "./texture/bodyDownRight.png");
	loadTexture(sprite::WALL, "./texture/wall.png");
	loadTexture(sprite::FOOD, "./texture/apple.png");
	_eventMap[sf::Keyboard::Escape] = key::ESCAPE;
	_eventMap[sf::Keyboard::Up] = key::UP;
	_eventMap[sf::Keyboard::Left] = key::LEFT;
	_eventMap[sf::Keyboard::Right] = key::RIGHT;
	_eventMap[sf::Keyboard::Down] = key::DOWN;
	_eventMap[sf::Keyboard::Unknown] = key::NO;
	_eventMap[sf::Keyboard::Num1] = key::ONE;
	_eventMap[sf::Keyboard::Num2] = key::TWO;
	_eventMap[sf::Keyboard::Num3] = key::THREE;
}

Graphics::~Graphics(void)
{

}

void				Graphics::openWindow(void)
{
	_window.create(sf::VideoMode(_width, _height), "Nibbler (SFML)", sf::Style::Titlebar | sf::Style::Close);
	_window.setKeyRepeatEnabled(false);
	runSound();
}

bool				Graphics::isOpen(void) const
{
	return (_window.isOpen());
}

key					Graphics::keyPress(void)
{
	sf::Event		event;

	_window.pollEvent(event);
	if (event.type == sf::Event::Closed)
		return (_eventMap[sf::Keyboard::Escape]);
	else if (event.type == sf::Event::KeyPressed)
		return (_eventMap[event.key.code]);
	return (_eventMap[sf::Keyboard::Unknown]);
}

void				Graphics::loadTexture(sprite sprite, const char *texturePath)
{
	_texture.setSmooth(true);
	_texture.loadFromFile(texturePath);
	_textureList[sprite] = _texture;
}

void				Graphics::loadSprite(float posX, float posY, sprite texture)
{
	float			widthSprite;
	float			heightSprite;
	sf::Sprite		sprite;

	sprite.setTexture(_textureList[texture]);
	sprite.setPosition(posX, posY);
	widthSprite = sprite.getLocalBounds().width;
	heightSprite = sprite.getLocalBounds().height;
	sprite.setScale(_squareSize / widthSprite, _squareSize / heightSprite);
	_spriteList.push_back(sprite);
}

void				Graphics::draw(Map &map)
{
	float			spaceAroundX = (_width / 2) - (_squareSize * 31);
	float			spaceAroundY = (_height / 2) - (_squareSize * 31);
	size_t			size = 62 * 62;
	int				pos = 0;
	float			posX;
	float			posY;

	_window.clear();
	for (size_t i = 0; i < size; i++)
	{
		if (pos == map.offsetMap)
			pos = 0;
		if (map.map[i] != sprite::SOIL)
		{
			posX = spaceAroundX + (pos * _squareSize);
			posY = spaceAroundY + ((i / 62) * _squareSize);
			loadSprite(posX, posY, map.map[i]);
		}
		pos++;
	}
	for (const auto &item : _spriteList) {
		_window.draw(item);
	}
	_spriteList.clear();
	_window.display();
}

void				Graphics::runSound(void)
{
	_music.openFromFile("./music/tetris_hard.wav");
	_music.setLoop(true);
	_music.play();
}

void				Graphics::closeWindow(void)
{
	_window.close();
}

Graphics			*create(size_t width, size_t height, float squareSize)
{
	return new Graphics(width, height, squareSize);
}

void				del(Graphics *test)
{
	delete test;
}
