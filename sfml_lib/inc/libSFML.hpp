#ifndef SFMLTEST_HPP
# define SFMLTEST_HPP

#include <../SFML/include/SFML/Window.hpp>
#include <../SFML/include/SFML/Graphics.hpp>
#include <../SFML/include/SFML/Audio.hpp>
#include "../../inc/Api.class.hpp"
#include <stdexcept>

class Graphics : public AGraphics {

	private:

		Graphics(void) = default;
		Graphics(Graphics const &src) = default;

		Graphics			&operator=(Graphics const &rhs) = default;

		void				runSound(void);
		void				loadTexture(sprite sprite, const char *texturePath);
		void				loadSprite(float posX, float posY, sprite texture);

		sf::RenderWindow						_window;
		sf::Texture								_texture;
		std::map<sprite, sf::Texture>			_textureList;
		std::vector<sf::Sprite>					_spriteList;
		sf::Music 								_music;
		std::map<sf::Keyboard::Key, key>		_eventMap;

	public:

		explicit Graphics(size_t width, size_t height, float squareSize);
		virtual ~Graphics(void);	

		void				openWindow(void) override;
		bool				isOpen(void) const override;
		key					keyPress(void) override;
		void				draw(Map &map) override;
		void				closeWindow(void) override;
		void				changeMusic(void) override;

};

extern "C" {

	Graphics				*create(size_t width, size_t height, float squareSize);
	void					del(Graphics *lol);

}

#endif