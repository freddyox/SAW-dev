#ifndef SAW_HH
#define SAW_HH

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <set>

class SAW : public sf::Drawable, public sf::Transformable {

private:
  float displayx,displayy;

  // Lattice Attributes
  int latticeN;
  int totalN;
  float a; // lattice dimensions
  std::vector<sf::CircleShape> lattice;
  std::map<int,sf::CircleShape> latticeMap;
  std::map<int,sf::CircleShape>::iterator latit;

  // SAW 
  sf::VertexArray line;
  std::vector<sf::VertexArray> saw;
  std::set<int> erased;
  std::set<int>::iterator erasedit;
  unsigned long int numberoftries;

public:
  SAW(float,float,int);
  ~SAW() {};
  void GenerateLattice();
  void GenerateSAW(sf::Color);

  void draw(sf::RenderTarget&, sf::RenderStates) const;

  int GetNTries() { return numberoftries; }
  int GetLatticeSize() { return latticeN+1; }
};
#endif
