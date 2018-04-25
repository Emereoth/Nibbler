#ifndef SFMLTEST_HPP
# define SFMLTEST_HPP

#include "../SFML/include/SFML/Window.hpp"
#include "../../inc/Api.class.hpp"

class Graphics : public test {

	public:

		sf::Window			window;
		virtual ~Graphics(void);

		void				openWindow(size_t w, size_t h);

};

extern "C" {

	Graphics				*create(void);
	void					del(Graphics *lol);

}

#endif