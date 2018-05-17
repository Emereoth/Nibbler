#ifndef SFMLTEST_HPP
# define SFMLTEST_HPP

#include "../SFML/include/SFML/Window.hpp"
#include "../SFML/include/SFML/Graphics.hpp"
#include "../../inc/Api.class.hpp"

class Graphics : public Api {

	public:

		sf::RenderWindow			window;
		virtual ~Graphics(void);

		void				run(size_t w, size_t h);

};

extern "C" {

	Graphics				*create(void);
	void					del(Graphics *lol);

}

#endif