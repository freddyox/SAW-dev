#include "../include/Screenshot.hh"
#include <iostream>
#include <cmath>
#include <sstream>

Screenshot::Screenshot(float displayX, float displayY) {
  displayx = displayX;
  displayy = displayY;

  // Text
  if( !font.loadFromFile("fonts/arial.ttf")) {
    std::cerr << "ERROR: Font did not load properly." << std::endl;
  }

  shade = sf::VertexArray(sf::Quads, 4);
  MakeButton();
  MakeBoarder(displayx,displayy,5,sf::Color(200,200,200));

  update_button = true;
}

void Screenshot::MakeButton() {
  float x = 150.0;
  float y = 25.0;
  button.setSize(sf::Vector2f(x,y));
  button.setOrigin( 0.5*x, 0.5*y );
  button.setFillColor(sf::Color(200,200,200));
  button.setPosition( displayx/8.0, displayy/10.0 );
  ShadeButton( button.getPosition(), sf::Vector2f(x,y), sf::Color(80,80,80), 4.0 );

  text.setFont(font);
  text.setString("Screenshot");
  text.setCharacterSize(18);
  text.setColor(sf::Color::Black);
  sf::FloatRect temp = text.getLocalBounds();
  text.setPosition( button.getPosition().x - 0.5*temp.width, button.getPosition().y - 0.75*temp.height );
  textvec.push_back(text);
}

void Screenshot::ShadeButton(sf::Vector2f pos,sf::Vector2f size,sf::Color col,float thickness){
  // TOP
  shade[0].position = sf::Vector2f( pos.x - size.x/2.0, pos.y - size.y/2.0 );
  shade[1].position = sf::Vector2f( pos.x - size.x/2.0 + thickness, pos.y - size.y/2.0 - thickness);
  shade[2].position = sf::Vector2f(  pos.x + size.x/2.0 + thickness, pos.y - size.y/2. - thickness );
  shade[3].position = sf::Vector2f( pos.x + size.x/2.0, pos.y - size.y/2.0 );
  shade[0].color =  col;
  shade[1].color =  col;
  shade[2].color =  col;
  shade[3].color =  col;
  shade_vec.push_back( shade );
  // RIGHT
  shade[0].position = sf::Vector2f(  pos.x + size.x/2.0, pos.y - size.y/2.0 );
  shade[1].position = sf::Vector2f( pos.x + size.x/2.0 + thickness, pos.y - size.y/2.0 - thickness );
  shade[2].position = sf::Vector2f( pos.x + size.x/2.0 + thickness, pos.y + size.y/2.0 - thickness);
  shade[3].position = sf::Vector2f( pos.x + size.x/2.0, pos.y + size.y/2.0 );
  shade[0].color =  col;
  shade[1].color =  col;
  shade[2].color =  col;
  shade[3].color =  col;
  shade_vec.push_back( shade );
}

void Screenshot::ButtonGUI( sf::Vector2f mouseP ) {
  //sf::FloatRect tmp = button.getLocalBounds();
  sf::Vector2f position = button.getPosition();
  sf::Vector2f D = mouseP - position;
  if( fabs(D.y) <= 0.5*button.getSize().y && fabs(D.x) <= 0.5*button.getSize().x ) {
    button.setFillColor( sf::Color::White );
  } else {
    button.setFillColor( sf::Color(200,200,200) );
  } 
}

void Screenshot::ClickButton( sf::Vector2f mouseP, sf::Image screenshot) {
  if( sf::Mouse::isButtonPressed(sf::Mouse::Left) ) {
    if( update_button ) {
      sf::Vector2f position = button.getPosition();
      sf::Vector2f D = mouseP - position;
      if( fabs(D.y) <= 0.5*button.getSize().y && fabs(D.x) <= 0.5*button.getSize().x ) {
	std::stringstream filename;
	filename << "SAW_Lattice_" << lattice << "_Total_" << total << ".png";
	screenshot.saveToFile( filename.str() );
      }
    } else
      update_button = true;
  }
}

////////////////////////////////////////////////////
//            AESTHETICS AND DRAWINGS             //
////////////////////////////////////////////////////
void Screenshot::draw( sf::RenderTarget& target, sf::RenderStates) const {
  target.draw(button);
  std::vector<sf::VertexArray>::const_iterator cit1;
  for( cit1=shade_vec.begin(); cit1!=shade_vec.end(); cit1++ ){
    target.draw(*cit1);
  }
  std::vector<sf::Text>::const_iterator cit2;
  for( cit2=textvec.begin(); cit2!=textvec.end(); cit2++ ){
    target.draw(*cit2);
  }
  DrawBoarder( target );
}

void Screenshot::DrawBoarder(sf::RenderTarget& targ) const{
  std::vector<sf::RectangleShape>::const_iterator cit;
  for( cit=boarder.begin(); cit!=boarder.end(); cit++ ){
    targ.draw(*cit);
  }
}

void Screenshot::MakeBoarder(float x, float y, float d, sf::Color color) {
  // Make a "Ceiling"
  sf::Vector2f ceiling_size( x, d );
  ceiling.setSize( ceiling_size );
  ceiling.setOrigin( x/2.0, d/2.0 );
  ceiling.setFillColor( color );
  ceiling.setPosition( x/2.0, d/2.0);
  // Make a bottom
  bottom.setSize( ceiling_size );
  bottom.setOrigin( x/2.0, d/2.0 );
  bottom.setFillColor( color );
  bottom.setPosition( x/2.0, y - d/2.0);
  // Make a Left / Right side
  left.setSize( sf::Vector2f( d, y - 2.0*d) );
  left.setOrigin( d/2.0, (y - 2.0*d)/2.0 );
  left.setFillColor( color );
  left.setPosition( d/2.0, y/2.0 );
  right.setSize( sf::Vector2f( d, y - 2.0*d) );
  right.setOrigin( d/2.0, (y - 2.0*d)/2.0 );
  right.setFillColor( color );
  right.setPosition( x - d/2.0, y/2.0 );
  boarder.push_back( ceiling );
  boarder.push_back( bottom );
  boarder.push_back( left );
  boarder.push_back( right );
}
