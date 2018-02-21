#include <iostream>
#include <SFML/Graphics.hpp>
float windowWidth = 800, windowHeight = 600;
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
  window.clear(sf::Color(120, 140, 160));
  drawBoard(window);
  while(window.isOpen()){

    sf::Event e;
    while(window.pollEvent(e)){
      if(e.type == sf::Event::Closed){
        window.close();
      }else if(e.type == sf::Event::MouseButtonPressed){
          if(e.mouseButton.button == sf::Mouse::Left){
            std::cout << e.mouseButton.x << ',' << e.mouseButton.y << std::endl;
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
