#ifndef SFMLTEST_HPP
# define SFMLTEST_HPP

#include <../SFML/include/SFML/Window.hpp>
#include <../SFML/include/SFML/Graphics.hpp>
#include <../SFML/include/SFML/Audio.hpp>
#include "../../inc/Api.class.hpp"

class Graphics : public AGraphics {

	public:

		explicit Graphics(size_t width, size_t height, size_t squareSize);
		virtual ~Graphics(void);	

		void				openWindow(void) override;
		bool				isOpen(void) const override;
		key					keyPress(void) override;
		void				draw(Map map) override;

		libName				name;

	private:

		Graphics(void) = default;
		Graphics(Graphics const &src) = default;
		Graphics			&operator=(Graphics const &rhs) = default;
		void				runSound(void) const;

		sf::RenderWindow						_window;
		sf::Event								_event;
		std::map<sprite, std::string>			_spriteMap;

};

extern "C" {

	Graphics				*create(size_t width, size_t height, size_t squareSize);
	void					del(Graphics *lol);

}

#endif