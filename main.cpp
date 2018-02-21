#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
float sqrt2 = 1.414213562;
float windowWidth = 800, windowHeight = 600;
std::vector<sf::Shape*> s;
void drawO(sf::RenderWindow& window, int xPos, int yPos){
  float radius = 25;
  sf::CircleShape *c = new sf::CircleShape(radius);
  c->setOrigin(radius, radius);
  c->setOutlineThickness(10);
  c->setFillColor(sf::Color(0, 0, 0, 0));
  c->move(xPos, yPos);
  s.push_back(c);
}

void drawItems(){}
void drawX(sf::RenderWindow& window, int xPos, int yPos){
  float width = 10, height = 50 * sqrt2;
  sf::RectangleShape* r = new sf::RectangleShape(sf::Vector2f(width, height));
  r->setOrigin(width/2, height/2);
  r->move(xPos, yPos);
  r->rotate(45);
  s.push_back(r);
  sf::RectangleShape* r1 = new sf::RectangleShape(*r);
  r->rotate(-90);
  s.push_back(r1);
}

void drawBoard(sf::RenderWindow& window){
  float width = 10, height = 300;
  float gap = 100;
  sf::RectangleShape l(sf::Vector2f(width, height));

  //Draw the Vertical Lines
  l.setFillColor(sf::Color(200, 50, 50));
  l.move(windowWidth/2 - gap/2 , windowHeight/2 - height/2);
  window.draw(l);
  l.move(gap, 0);
  window.draw(l);
  //Draw the Horizontal Lines
  l.setSize(sf::Vector2f(height, width));
  l.setFillColor(sf::Color(50, 50, 200));
  l.setPosition(windowWidth/2 - height/2 , windowHeight/2 - gap/2);
  window.draw(l);
  l.move(0, gap);
  window.draw(l);
}
int main(int argc, char const *argv[]) {
  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight, 32), "Testing SFML", sf::Style::Titlebar| sf::Style::Close);
  window.setVerticalSyncEnabled(true);
  sf::CircleShape r(100.0f);
  r.setOrigin(r.getPosition().x + r.getRadius(), r.getPosition().y  + r.getRadius());

  while(window.isOpen()){
    sf::Event e;
    window.clear(sf::Color(120, 140, 160));
    drawBoard(window);
    for(auto& i:s){
      window.draw(*i);
    }
    drawItems();
    while(window.pollEvent(e)){
      if(e.type == sf::Event::Closed){
        window.close();
      }else if(e.type == sf::Event::MouseButtonPressed){
          float xPos = e.mouseButton.x, yPos = e.mouseButton.y;
          if(e.mouseButton.button == sf::Mouse::Left){
            std::cout << xPos << ',' << yPos << std::endl;
            drawX(window, xPos, yPos);
          }
          if(e.mouseButton.button == sf::Mouse::Right){
            std::cout << xPos << ',' << yPos << std::endl;
            drawO(window, xPos, yPos);
          }
        }
    }
    window.display();
  }

  return 0;
}

/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
{
    // left key is pressed: move our character
    character.move(1, 0);
}
if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
{
    // left mouse button is pressed: shoot
    gun.fire();
}
*/
