#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

const float sqrt2 = 1.414213562;
const float windowWidth = 800, windowHeight = 600;

std::vector<sf::Shape *> s;

// Draw O on the screen
void drawO(sf::RenderWindow &window, int xPos, int yPos)
{
  float radius = 25; // The radius of the circle to be drawn
  // Create the circle
  sf::CircleShape *c = new sf::CircleShape(radius);
  c->setOrigin(radius, radius);
  c->setOutlineThickness(10);
  c->setFillColor(sf::Color(0, 0, 0, 0));
  c->move(xPos, yPos);
  // Push the circle to the vector containing all the shapes
  s.push_back(c);
}

// Draw X's on the screen
void drawX(sf::RenderWindow &window, int xPos, int yPos)
{
  // Parameters for the cross
  float width = 30, edgeSize = 7;

  // Create a Cross shape with 12 vertices
  sf::ConvexShape *cross = new sf::ConvexShape(12);

  // Define the vertices
  cross->setPoint(0, sf::Vector2f(xPos, yPos - edgeSize));
  cross->setPoint(1, sf::Vector2f(xPos + (width - edgeSize), yPos - width));
  cross->setPoint(2, sf::Vector2f(xPos + width, yPos - (width - edgeSize)));
  cross->setPoint(3, sf::Vector2f(xPos + edgeSize, yPos));
  cross->setPoint(4, sf::Vector2f(xPos + width, yPos + (width - edgeSize)));
  cross->setPoint(5, sf::Vector2f(xPos + (width - edgeSize), yPos + width));
  cross->setPoint(6, sf::Vector2f(xPos, yPos + edgeSize));
  cross->setPoint(7, sf::Vector2f(xPos - (width - edgeSize), yPos + width));
  cross->setPoint(8, sf::Vector2f(xPos - width, yPos + (width - edgeSize)));
  cross->setPoint(9, sf::Vector2f(xPos - edgeSize, yPos));
  cross->setPoint(10, sf::Vector2f(xPos - width, yPos - (width - edgeSize)));
  cross->setPoint(11, sf::Vector2f(xPos - (width - edgeSize), yPos - width));
  // Push the cross to the vector containing all the shapes
  s.push_back(cross);
}

void drawShape(sf::RenderWindow &window, bool shape, int xPos, int yPos)
{
  shape ? drawX(window, xPos, yPos) : drawO(window, xPos, yPos);
}
// Draw the board from vertical and horizontal lines
void drawBoard(sf::RenderWindow &window)
{
  // The width and height of vertical lines
  float width = 10, height = 300;
  // The gap between each line that makes up the board
  float gap = 100;

  // Create the rectangles
  sf::RectangleShape l(sf::Vector2f(width, height));

  // Draw the Vertical Lines
  l.setFillColor(sf::Color(200, 50, 50));
  l.move(windowWidth / 2 - gap / 2, windowHeight / 2 - height / 2);
  window.draw(l);
  l.move(gap, 0);
  window.draw(l);

  // Draw the Horizontal Lines
  l.setSize(sf::Vector2f(height, width));
  l.setFillColor(sf::Color(50, 50, 200));
  l.setPosition(windowWidth / 2 - height / 2, windowHeight / 2 - gap / 2);
  window.draw(l);
  l.move(0, gap);
  window.draw(l);
}

int main(int argc, char const *argv[])
{
  // Create the main window
  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight, 32), "Testing SFML", sf::Style::Titlebar | sf::Style::Close);
  window.setVerticalSyncEnabled(true);
  // sf::CircleShape r(100.0f);
  // r.setOrigin(r.getPosition().x + r.getRadius(), r.getPosition().y + r.getRadius());

  // Count how many shapes have been placed
  int shapesCount = 1;

  bool currentTurn = true; // true means its X's turn and false means it is O's turn
  bool gridsFilled[9] = {false};
  for (auto &i : gridsFilled)
  {
    std::cout << i << ", ";
  }
  std::cout << std::endl;
  // Main game loop
  while (window.isOpen())
  {
    // Create a event to handle all keyboard and mouse actions
    sf::Event e;

    // Set the background color
    window.clear(sf::Color(120, 140, 160));

    // Draw the board
    drawBoard(window);

    // For all shapes, in 's', draw them one after another
    for (auto &i : s)
    {
      window.draw(*i);
    }

    // Check for events
    while (window.pollEvent(e))
    {
      // If the user closes the window, exit the game
      if (e.type == sf::Event::Closed)
      {
        window.close();
      }
      // Handle key events only if number of shapes is less than or equal to 9
      if (shapesCount <= 9)
      {
        if (e.type == sf::Event::MouseButtonPressed) // Handle mouse presses
        {
          // Get the current mouse position
          float xPos = e.mouseButton.x, yPos = e.mouseButton.y;
          std::cout << xPos << ',' << yPos << std::endl;

          // Check if the click is inside the board
          if (xPos >= 250 and xPos <= 550 and yPos >= 150 and yPos <= 450)
          {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
              // For boxes (0, 0), (0, 1), (0, 2)
              if (yPos <= 250)
              {
                if (xPos <= 350)
                {
                  drawShape(window, currentTurn, 300, 200);
                }
                else if (xPos <= 450)
                {
                  drawShape(window, currentTurn, 405, 200);
                }
                else
                {
                  drawShape(window, currentTurn, 500, 200);
                }
              }
              // For boxes (1, 0), (1, 1), (1, 2)
              else if (yPos <= 350)
              {
                if (xPos <= 350)
                {
                  drawShape(window, currentTurn, 300, 300);
                }
                else if (xPos <= 450)
                {
                  drawShape(window, currentTurn, 405, 300);
                }
                else
                {
                  drawShape(window, currentTurn, 500, 300);
                }
              }
              // For boxes (2, 0), (2, 1), (2, 2)
              else
              {
                if (xPos <= 350)
                {
                  drawShape(window, currentTurn, 300, 400);
                }
                else if (xPos <= 450)
                {
                  drawShape(window, currentTurn, 405, 400);
                }
                else
                {
                  drawShape(window, currentTurn, 500, 400);
                }
              }
              currentTurn = !currentTurn;
              shapesCount++;
            }
          }
        }
      }
    }
    window.display();
  }

  return 0;
}
