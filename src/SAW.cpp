#include "../include/SAW.hh"
#include <cmath>
#include <iostream>

SAW::SAW(float x, float y, int lattice_size) {
  displayx = x;
  displayy = y;

  latticeN = lattice_size;
  GenerateLattice();
}

void SAW::GenerateLattice(){
  // Define a lattice x lattice Array of Circles
  float radius = 5.0;
  sf::CircleShape point(radius);
  sf::FloatRect temp = point.getLocalBounds();
  point.setOrigin( temp.width/2.0, temp.height/2.0 );
  point.setFillColor( sf::Color(30,22,86) );

  // Calculate size and spacing of lattice in order to center it
  int spacing = (int(displayx)/2) / latticeN; 
  for( int row = 0; row<=latticeN; row++ ) {
    for( int col = 0; col<=latticeN; col++ ) {
      point.setPosition(displayx/4.0 + spacing*row, displayy/4.0 + spacing*col );
      lattice.push_back( point );    
    }
  } 
}

void SAW::draw( sf::RenderTarget& target, sf::RenderStates) const {
  std::vector<sf::CircleShape>::const_iterator cit;
  for( cit=lattice.begin(); cit!=lattice.end(); cit++ ){
    target.draw(*cit);
  }
}

bool SAW::is_perfect_square(int n) {
  if (n < 0)
    return false;
  int root(round(sqrt(n)));
  return n == root * root;
}
