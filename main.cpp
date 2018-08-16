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

// Check horizontally for game end
int checkHoriz(int *grids)
{
  // If the first element is 0, it means the space has not been filled yet. So there is no possibility for a vertical game to exist in this row.
  if (grids[0] != 0)
    if ((grids[0] == grids[1]) and (grids[0] == grids[2])) // See if game has occured
    {
      return grids[0]; // Game occured
    }
  return 0; // Game has not occured
}

// Check vertically for game end
int checkVert(int grids[3][3], int i)
{
  // If the first element is 0, it means the space has not been filled yet. So there is no possibility for a vertical game to exist in this column.
  if (grids[0][i] != 0)
    if ((grids[0][i] == grids[1][i]) and (grids[0][i] == grids[2][i])) // Check for game ended
    {
      return grids[0][i]; // Game ended
    }
  return 0; // Game not won
}

int checkDiag(int grids[][3], bool reverse = false)
{
  // reverse is a flag. If reverse == true, reverse diagonal is checked.
  if (!reverse)
  {
    // Check the diagonal elements
    if (grids[0][0] != 0)
      if ((grids[0][0] == grids[1][1]) and (grids[0][0] == grids[2][2]))
      {
        return grids[0][0];
      }
  }
  else
  {
    // Check the reverse diagonal elements
    if (grids[0][2] != 0)
      if ((grids[0][2] == grids[1][1]) and (grids[0][2] == grids[2][0]))
      {
        return grids[0][2];
      }
  }
  return 0;
}

// Find out if the game has ended
int isGameWon(int grids[3][3])
{
  // Initially, assume noone has won
  int win = 0;
  // Check for horizontal and vertical wins in one pass
  for (int i = 0; i < 3; i++)
  {
    // See if a horizontal game has occured
    win = checkHoriz(grids[i]);
    // If yes, return win. 'win = 1' means player X won and 'win = 2' means player O won.
    if (win)
      return win;

    // Check for vertical game
    // Note that whole array is passed to this function and the variable i denotes the column number to check for game
    win = checkVert(grids, i);
    if (win)
      return win;
  }

  // Check if a diagonal game has occured
  win = checkDiag(grids);
  if (win)
    return win;

  // Check if a reverse diagonal game has occured
  win = checkDiag(grids, true);
  if (win)
    return win;
  return false;
}

void printGrid(int grids[][3])
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
      std::cout << grids[i][j] << '\t';
    std::cout << std::endl;
  }
}

void clearGrid(int grids[][3])
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
      grids[i][j] = 0;
  }
}

int main(int argc, char const *argv[])
{
  // Create the main window
  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight, 32), "Testing SFML", sf::Style::Titlebar | sf::Style::Close);
  window.setVerticalSyncEnabled(true);

  // Keep track of whose turn it is
  bool currentTurn = true; // true means its X's turn and false means it is O's turn

  // The state of the board
  int grids[3][3] = {0}; // 0 is for not filled, 1 is for filled by X and 2 is for filled by O

  // Store the number of moves made
  int movesMade = 0;

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

      if (e.type == sf::Event::MouseButtonPressed) // Handle mouse presses
      {
        // Get the current mouse position
        float xPos = e.mouseButton.x, yPos = e.mouseButton.y;
        // std::cout << xPos << ',' << yPos << std::endl;

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
                if (grids[0][0] == 0)
                {
                  drawShape(window, currentTurn, 300, 200);
                  grids[0][0] = !currentTurn + 1;
                  currentTurn = !currentTurn;
                  movesMade++;
                }
              }
              else if (xPos <= 450)
              {
                if (grids[0][1] == 0)
                {
                  drawShape(window, currentTurn, 405, 200);
                  grids[0][1] = !currentTurn + 1;
                  currentTurn = !currentTurn;
                  movesMade++;
                }
              }
              else
              {
                if (grids[0][2] == 0)
                {
                  drawShape(window, currentTurn, 500, 200);
                  grids[0][2] = !currentTurn + 1;
                  currentTurn = !currentTurn;
                  movesMade++;
                }
              }
            }
            // For boxes (1, 0), (1, 1), (1, 2)
            else if (yPos <= 350)
            {
              if (xPos <= 350)
              {
                if (grids[1][0] == 0)
                {
                  drawShape(window, currentTurn, 300, 300);
                  grids[1][0] = !currentTurn + 1;
                  currentTurn = !currentTurn;
                  movesMade++;
                }
              }
              else if (xPos <= 450)
              {
                if (grids[1][1] == 0)
                {
                  drawShape(window, currentTurn, 405, 300);
                  grids[1][1] = !currentTurn + 1;
                  currentTurn = !currentTurn;
                  movesMade++;
                }
              }
              else
              {
                if (grids[1][2] == 0)
                {
                  drawShape(window, currentTurn, 500, 300);
                  grids[1][2] = !currentTurn + 1;
                  currentTurn = !currentTurn;
                  movesMade++;
                }
              }
            }
            // For boxes (2, 0), (2, 1), (2, 2)
            else
            {
              if (xPos <= 350)
              {
                if (grids[2][0] == 0)
                {
                  drawShape(window, currentTurn, 300, 400);
                  grids[2][0] = !currentTurn + 1;
                  currentTurn = !currentTurn;
                  movesMade++;
                }
              }
              else if (xPos <= 450)
              {
                if (grids[2][1] == 0)
                {
                  drawShape(window, currentTurn, 405, 400);
                  grids[2][1] = !currentTurn + 1;
                  currentTurn = !currentTurn;
                  movesMade++;
                }
              }
              else
              {
                if (grids[2][2] == 0)
                {
                  drawShape(window, currentTurn, 500, 400);
                  grids[2][2] = !currentTurn + 1;
                  currentTurn = !currentTurn;
                  movesMade++;
                }
              }
            }
          }
        }
        // printGrid(grids);
      }
    }
    window.display();

    // If 9 moves have been made, the game is a draw
    if (movesMade == 9)
    {
      // Reset the states of the game
      movesMade = 0;    // 0 moves have been made after draw
      clearGrid(grids); // Clear the grid
      s.clear();        // Clear all shapes

      std::cout << "Game draw. Play Again" << std::endl;
    }
    // Check if the game is won
    if (isGameWon(grids))
    {
      // The variable currentTurn denotes whose turn it is.
      // Note that since currentTurn is inverted on every grid clicked, we need to invert it again.
      currentTurn = !currentTurn;
      char winner = currentTurn ? 'X' : 'O';
      std::cout << "Game Won by " << winner << std::endl;
      return -1;
    }
  }

  return 0;
}
