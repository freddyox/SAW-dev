#include "../include/SAW.hh"
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <iterator>
#include <algorithm>

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

  totalN = (latticeN+1)*(latticeN+1); 

  GenerateLattice();

  line = sf::VertexArray(sf::LinesStrip,2);
  sf::Color purple = sf::Color(127,35,219);
  numberoftries = 0;
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
  // Starting Position is Top Left Node
  // This algorithm searches for a perfect solution, or where
  // the random walker touches all nodes without crossing over itself.
  srand (time(NULL));
 
  erased.insert(0);
  
  while( erased.size() <= totalN-1 ) { 
    erased.clear();
    saw.clear();
    sf::Vector2f start = latticeMap[0].getPosition();
    erased.insert( 0 );

    sf::CircleShape temp(5);
    std::map<int,sf::CircleShape> neighbors;
    neighbors[1] = temp;
    numberoftries++;

    //std::cout << numberoftries << std::endl;
    while( !neighbors.empty() ) {

      neighbors.clear();
      line[0].position = start;
      line[0].color = col;

      // Search for nearest neighbors. Add to a container to be analyzed.
      for( latit = latticeMap.begin(); latit != latticeMap.end(); latit++ ) {
	// Ignore erased points
	bool found = false;
	found = erased.find( latit->first ) != erased.end();

	if( !found ) {
	  sf::Vector2f lPos = latit->second.getPosition();
	  sf::Vector2f d = lPos - start;
	  double d_mag = sqrt( pow(d.x,2) + pow(d.y,2) );
	
	  if( d_mag <= a ) {
	    neighbors[latit->first] = latit->second; 
	  }	
	}
      }
      if( neighbors.size() > 0 ) {
	// Randomly choose a neighbor
	int nextPosition = rand() % neighbors.size();
	std::map<int,sf::CircleShape>::iterator item = neighbors.begin();
	std::advance(item, nextPosition );
	line[1].position = item->second.getPosition();
	line[1].color = col;
	saw.push_back( line );

	erased.insert( item->first );

	start = item->second.getPosition();
      }
    }
    // *******************************************************************************
    // **                                  SPECS                                    **
    // *******************************************************************************
    // The size of container erased = total number of nodes touched by a SAW
    // erased.size()-1 corresponds to the number of lines needed for a given walk
    // "a" is the lattice spacing
    
    //std::cout << erased.size() << std::endl;
    //std::cout << totalN << std::endl;
    //double ratio_of_nodes_hit = erased.size() / pow(latticeN+1,2) ;
    //std::cout << ratio_of_nodes_hit << std::endl;
    // std::cout << "Length of SAW = " << (erased.size() - 1) <<"*a units = " << (erased.size() - 1)*a << "." << std::endl;
    // std::cout << "Therefore, the program hit " << erased.size() - 1 << " out of " 
    // 	      << totalN << " possible nodes, resulting in a ratio of "
    // 	      << ratio_of_nodes_hit << std::endl;
    
  }
  std::cout << "TOTAL #: " <<  numberoftries << std::endl;
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
