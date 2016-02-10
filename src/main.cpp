//    ************************************************************
//    *                           SAW                            *
//    *                      February 2015                       *
//    ************************************************************
//      Self-Avoiding random Walk in two dimensions, written by 
//      Freddy Obrecht during the first week of February of 2016.
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <sstream>

#include "../include/SAW.hh"
#include "../include/Screenshot.hh"

const float gDisplayx = 1000;
const float gDisplayy = 1000;

int main() {

  sf::RenderWindow window(sf::VideoMode(gDisplayx,gDisplayy), "Self-Avoiding Walk");
  window.setFramerateLimit(60);

  //////////////////////////////////////////////////////
  //                   Initialize                     //
  //////////////////////////////////////////////////////
  // Max Lattice Size is 50x50. 
  SAW saw(gDisplayx,gDisplayy,4);
  Screenshot screenshot_gui(gDisplayx,gDisplayy);
  screenshot_gui.SetTotal( saw.GetNTries() );
  screenshot_gui.SetLatticeSize( saw.GetLatticeSize() );

  while( window.isOpen() ) {

    sf::Event event;
    while( window.pollEvent(event) ) {
      if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ) {
	window.close();
      }
    }
    window.clear(sf::Color::Black);
    window.draw(saw);
    window.draw(screenshot_gui);
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    screenshot_gui.ButtonGUI( window.mapPixelToCoords(mouse) );
    screenshot_gui.ClickButton( window.mapPixelToCoords(mouse), window.capture());

    window.display();      
  }
  return 0;
}
