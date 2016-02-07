//    ************************************************************
//    *                           SAW                            *
//    *                      February 2015                       *
//    ************************************************************
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <sstream>

#include "../include/SAW.hh"

const float gDisplayx = 1000;
const float gDisplayy = 1000;

int main() {

  sf::RenderWindow window(sf::VideoMode(gDisplayx,gDisplayy), "Self-Avoiding Walk");
  window.setFramerateLimit(60);

  //////////////////////////////////////////////////////
  //                   Initialize                     //
  //////////////////////////////////////////////////////
  // Max Lattice Size is 50x50, 
  SAW saw(gDisplayx,gDisplayy,9);
  
  while( window.isOpen() ) {

    sf::Event event;
    while( window.pollEvent(event) ) {
      if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ) {
	window.close();
      }
    }
    window.clear(sf::Color::Black);
    window.draw(saw); 
    window.display();      
  }
  return 0;
}
