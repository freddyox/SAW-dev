#ifndef SCREENSHOT_HH
#define SCREENSHOT_HH

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <vector>

class SAW;

class Screenshot : public sf::Drawable, public sf::Transformable {

private:
  float displayx,displayy;

  sf::RectangleShape button;
  sf::VertexArray shade;
  std::vector<sf::VertexArray> shade_vec;
  bool update_button;

  // Text for Button
  sf::Text text;
  sf::Font font;
  std::vector<sf::Text> textvec;

  // Boarder
  sf::RectangleShape ceiling, left, right, bottom;
  std::vector<sf::RectangleShape> boarder;

  unsigned long int total;
  int lattice;
  
public:
  Screenshot(float,float);
  ~Screenshot(){};
  void MakeBoarder(float,float,float,sf::Color);
  void DrawBoarder(sf::RenderTarget&) const;

  void draw(sf::RenderTarget&, sf::RenderStates) const;
  void MakeButton();
  void ShadeButton(sf::Vector2f,sf::Vector2f,sf::Color,float);
  void ButtonGUI(sf::Vector2f);
  void ClickButton(sf::Vector2f, sf::Image );

  int SetTotal(int x) {total=x;}
  int SetLatticeSize(int x) {lattice=x;}
};
#endif
