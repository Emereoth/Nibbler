#ifndef SFMLTEST_HPP
# define SFMLTEST_HPP

#include <../SFML/include/SFML/Window.hpp>
#include <../SFML/include/SFML/Graphics.hpp>
#include <../SFML/include/SFML/Audio.hpp>
#include "../../inc/Api.class.hpp"

class Graphics : public Api {

	private:

		sf::RenderWindow			_window;

	public:

		virtual ~Graphics(void);

		void				run(size_t w, size_t h) override;

	private:

		void				openWindow(size_t w, size_t h);

};

extern "C" {

	Graphics				*create(void);
	void					del(Graphics *lol);

}

#endif