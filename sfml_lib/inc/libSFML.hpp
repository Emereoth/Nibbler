#ifndef SFMLTEST_HPP
# define SFMLTEST_HPP

#include <../SFML/include/SFML/Window.hpp>
#include <../SFML/include/SFML/Graphics.hpp>
#include <../SFML/include/SFML/Audio.hpp>
#include "../../inc/Api.class.hpp"

class Graphics : public AGraphics {

	private:

		sf::RenderWindow			_window;
		sf::Event					_event;

	public:

		explicit Graphics(void);
		Graphics(Graphics const &src) = delete;
		virtual ~Graphics(void);

		void				openWindow(size_t w, size_t h) override;
		bool				isOpen(void) const override;
		key					keyPress(void) override;
		void				draw(void) override;

		libName	name;

	private:

		Graphics			&operator=(Graphics const &rhs) = delete;
		void				runSound(void) const;

};

extern "C" {

	Graphics				*create(void);
	void					del(Graphics *lol);

}

#endif