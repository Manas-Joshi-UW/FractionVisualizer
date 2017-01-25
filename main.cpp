#include "constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

void Draw(sf::RenderWindow *window, float x1, float y1, float x2, float y2,
          sf::VertexArray points);

int main() {
  // create the window
  sf::RenderWindow window(sf::VideoMode(2000, 1200), "My window");
  int x_c = 0, y_c = 0;
  float x = 0, y = 0;
  int array_index = 0;
  float x1 = 300, y1 = 300, x2 = 1500, y2 = 900;
  sf::VertexArray points_array =
      sf::VertexArray(sf::Points, ((2 * PI) / 0.01f));

  // start a clock
  sf::Clock clock;
  // run the program as long as the window is open
  while (window.isOpen()) {
    // check all the window's events that were triggered since the last
    // iteration of the loop
    sf::Event event;
    while (window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // clear the window with black color
    window.clear(sf::Color::Black);

    if (x > 2 * PI) {
      x = 0;
      x_c++;
    }

    if (array_index >= points_array.getVertexCount()) {
      points_array.resize(points_array.getVertexCount() * 2);
    }
    if (y > 2 * PI) {
      y = 0;
      y_c++;
    }
    std::cout << y_c << std::endl;
    std::cout << x_c << std::endl;

    // x and y coordinates for the first moving circle
    x1 += orbital_radius * cos(x);
    y1 += orbital_radius * sin(x);

    // x and y coordinates for the second moving circle
    x2 += orbital_radius * cos(y);
    y2 += orbital_radius * sin(y);

    points_array[array_index].position = sf::Vector2f(x2 + 20, y1 + 20);

    Draw(&window, x1, y1, x2, y2, points_array);
    x += .01f;
    y += .01f * 3 / 4;

    ++array_index;
    // x and y coordinates for the first moving circle
    x1 = 300;
    y1 = 300;

    // x and y coordinates for the second moving circle
    x2 = 1500;
    y2 = 900;

    // end the current frame
    window.display();
  }

  return 0;
}

void Draw(sf::RenderWindow *window, float x1, float y1, float x2, float y2,
          sf::VertexArray points) {

  sf::RectangleShape rectangle(sf::Vector2f(280, 280));
  rectangle.setFillColor(sf::Color::Black);
  rectangle.setOutlineColor(sf::Color::White);
  rectangle.setOutlineThickness(1);
  rectangle.setPosition(1380, 180);

  sf::Vertex line[2] = {sf::Vector2f(x1 + 20, y1 + 20),
                        sf::Vector2f(2000, y1 + 20)};

  sf::Vertex line2[2] = {sf::Vector2f(x2 + 20, y2 + 20),
                         sf::Vector2f(x2 + 20, 0)};

  // the first stationary circle
  sf::CircleShape stationary_circle1(STATIONARY_CIRCLE_RADIUS,
                                     CIRCLE_POINT_COUNT);
  stationary_circle1.setFillColor(sf::Color::Green);
  stationary_circle1.setPosition(200, 200);

  // the second stationary circle
  sf::CircleShape stationary_circle2(STATIONARY_CIRCLE_RADIUS,
                                     CIRCLE_POINT_COUNT);
  stationary_circle2.setFillColor(sf::Color::Green);
  stationary_circle2.setPosition(1400, 800);

  // the circle that moves around the first circle
  sf::CircleShape circle1(MOVING_CIRCLE_RADIUS, CIRCLE_POINT_COUNT);
  circle1.setFillColor(sf::Color::Blue);
  circle1.setPosition(x1, y1);

  // the circle that moves around the second circle
  sf::CircleShape circle2(MOVING_CIRCLE_RADIUS, CIRCLE_POINT_COUNT);
  circle2.setFillColor(sf::Color::Blue);
  circle2.setPosition(x2, y2);

  (*window).draw(stationary_circle1);
  (*window).draw(stationary_circle2);
  (*window).draw(circle1);
  (*window).draw(circle2);
  (*window).draw(rectangle);
  (*window).draw(points);
  (*window).draw(line, 2, sf::Lines);
  (*window).draw(line2, 2, sf::Lines);
}
