#include "../include/SAW.hh"
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

SAW::SAW(float x, float y, int lattice_size) {
  if( x == y ) {
    displayx = x;
    displayy = y;
  } else {
    displayx = 1000;
    displayy = 1000;
  }

  if( lattice_size <= 50 ){latticeN = lattice_size;}
  else latticeN = 9;

  GenerateLattice();

  line = sf::VertexArray(sf::LinesStrip,2);
  sf::Color purple = sf::Color(127,35,219);
  GenerateSAW(purple);
}

void SAW::GenerateLattice(){
  // Define a latticeN x latticeN Array of Circles
  // I have defined a cutoff. Therefore, if I choose
  // a lattice that is greater than 30x30, then I reposition
  // the lattice so that the spacings can be seen more easily.
  float radius = 5.0;
  sf::CircleShape point(radius);
  sf::FloatRect temp = point.getLocalBounds();
  point.setOrigin( temp.width/2.0, temp.height/2.0 );
  point.setFillColor( sf::Color(36,205,240) );

  int lattice_number = 0;
  if( latticeN <= 30 ) {
    int spacing = (int(displayx)/2) / latticeN; 
    a = spacing;
    for( int row = 0; row<=latticeN; row++ ) {
      for( int col = 0; col<=latticeN; col++ ) {
	point.setPosition(displayx/4.0 + spacing*row, displayy/4.0 + spacing*col );
	lattice.push_back( point );
	latticeMap[lattice_number] = point;
	lattice_number++;
      }
    } 
  } else {
    int spacing = (int(displayx) - 50) / latticeN; 
    a = spacing;
    for( int row = 0; row<=latticeN; row++ ) {
      for( int col = 0; col<=latticeN; col++ ) {
	point.setPosition(25.0 + spacing*row, 25.0 + spacing*col );
	lattice.push_back( point );  
  	latticeMap[lattice_number] = point;
	lattice_number++;
      }
    } 
  }
}

void SAW::GenerateSAW(sf::Color col) {
  // Find the starting position (top left)
  srand (time(NULL));

  sf::Vector2f start = latticeMap[0].getPosition();
  erased.insert( 0 );
  //latticeMap.erase( 0 );

  std::map<int,sf::CircleShape> neighbors;
  std::map<int,int> neighbor_lattice_map;
  int count_neighbors=-1;
 
  while( erased.size()<15 ) {

    neighbors.clear();
    neighbor_lattice_map.clear();
    count_neighbors = 0; 

    line[0].position = start;
    line[0].color = col;

    // Search for nearest neighbors. Add to a container to be analyzed.
    for( latit=latticeMap.begin(); latit!=latticeMap.end(); latit++ ) {
      // Ignore erased points
      bool found = false;

      found = erased.find( latit->first ) != erased.end();
      
      if( !found ) {
	sf::Vector2f lPos = latit->second.getPosition();
	sf::Vector2f d = lPos - start;
	double d_mag = sqrt( pow(d.x,2) + pow(d.y,2) );
	
	if( d_mag <= a ) {
	  neighbors[count_neighbors++] = latit->second;
	  neighbor_lattice_map[count_neighbors] = latit->first; 
	  std::cout << "SITE " << latit->first << std::endl;
	  std::cout << "neighbors = " << count_neighbors << " " << latit->first << " " << erased.size() << std::endl;
	}	
      }
    }
    if( neighbors.size() > 0 ) {
      // randomly choose a neighbor
      int nextPosition = rand() % neighbors.size();
      line[1].position = neighbors[nextPosition].getPosition();
      line[1].color = col;
      saw.push_back( line );

      erased.insert( neighbor_lattice_map[nextPosition] );
      //latticeMap.erase( neighbor_lattice_map[nextPosition] );

      std::cout <<  "neighbor_lattice = " << neighbor_lattice_map[nextPosition] << std::endl;
   
      start = neighbors[nextPosition].getPosition();
      std::cout << "erased.size  neighsize " << erased.size() << " " << neighbors.size() << std::endl;
    }
  }
  std::set<int>::iterator sit;
  for(sit=erased.begin(); sit!=erased.end(); sit++) std::cout << *sit << std::endl;
}

void SAW::draw( sf::RenderTarget& target, sf::RenderStates) const {
  std::vector<sf::VertexArray>::const_iterator cit1;
  for( cit1=saw.begin(); cit1!=saw.end(); cit1++ ){
    target.draw(*cit1);
  }
 std::vector<sf::CircleShape>::const_iterator cit;
  for( cit=lattice.begin(); cit!=lattice.end(); cit++ ){
    target.draw(*cit);
  }
}
