#ifndef SAW_HH
#define SAW_HH

#include <SFML/Graphics.hpp>
#include <vector>

class SAW : public sf::Drawable, public sf::Transformable {

private:
float displayx,displayy;
int latticeN;
std::vector<sf::CircleShape> lattice;

public:
SAW(float,float,int);
~SAW() {};
void GenerateLattice();


bool is_perfect_square(int);
void draw(sf::RenderTarget&, sf::RenderStates) const;
};
#endif
