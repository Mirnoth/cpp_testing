#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

class MakeString
{
   public:
      template <typename T>
      MakeString& operator<< (const T& value)
      {
         myStream << value;
         return *this;
      }
      
      operator std::string() const
      {
         return myStream.str();
      }
      
   private:
      std::stringstream myStream;
}; 

int main() {
	int drawstate=0;
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Window");
	App.SetFramerateLimit(60);
	//sf::Image Image(100, 100, sf::Color(0, 255, 255));
	// Load the sprite image from a file
	sf::Image Image;
	if (!Image.LoadFromFile("textur.png"))
	    return EXIT_FAILURE;
	// Create the sprite
	sf::Sprite Sprite(Image);
	// Change its properties
	Sprite.SetColor(sf::Color(0, 255, 255, 128));
	Sprite.SetPosition(200.f, 100.f);
	Sprite.SetScale(2.f, 2.f);
	Sprite.SetCenter(50.f,50.f);
	sf::Rect<int> SubRect(50,0,100,50);
	Sprite.SetSubRect(SubRect);
	// Build a custom convex shape
	sf::Shape Polygon;
	Polygon.AddPoint(0, -50,  sf::Color(255, 0, 0),     sf::Color(0, 128, 128));
	Polygon.AddPoint(50, 0,   sf::Color(255, 85, 85),   sf::Color(0, 128, 128));
	Polygon.AddPoint(50, 50,  sf::Color(255, 170, 170), sf::Color(0, 128, 128));
	Polygon.AddPoint(0, 100,  sf::Color(255, 255, 255), sf::Color(0, 128, 128));
	Polygon.AddPoint(-50, 50, sf::Color(255, 170, 170), sf::Color(0, 128, 128));
	Polygon.AddPoint(-50, 0,  sf::Color(255, 85, 85),   sf::Color(0, 128, 128));
	// Define an outline width
	Polygon.SetOutlineWidth(10);
	// Disable filling and enable the outline
	Polygon.EnableFill(false);
	Polygon.EnableOutline(true);
	// We can still use the functions common to all SFML drawable objects
	Polygon.SetColor(sf::Color(255, 255, 255, 200));
	Polygon.Move(300, 300);
	Polygon.Scale(3, 2);
	Polygon.Rotate(45);
	// Create a sprite for the background
	sf::Image BackgroundImage;
	if (!BackgroundImage.LoadFromFile("background.jpg"))
		return EXIT_FAILURE;
	sf::Sprite Background(BackgroundImage);
	// Create another sprite for the cursor
	sf::Image CursorImage;
	if (!CursorImage.LoadFromFile("cursor.tga"))
		return EXIT_FAILURE;
	sf::Sprite Cursor(CursorImage);
	// Resize the background, so that it's much bigger than the window
	Background.Resize(2000, 2000);
	// Define a text for displaying some instructions
	sf::String Text("Use the arrow keys to move the camera\nUse the + and - keys to zoom and unzoom");
	Text.Move(10, 500);
	Text.SetColor(sf::Color::White);
	
	// Create a view with the same size as the window, located somewhere in the center of the background
	sf::Vector2f Center(1000, 1000);
	sf::Vector2f HalfSize(400, 300);
	sf::View View(Center, HalfSize);
	// To start, put the cursor at the center
	Cursor.SetCenter(32, 32);
	Cursor.SetPosition(Center);
	
	while (App.IsOpened()) {
		sf::Event Event;
		while (App.GetEvent(Event)) {
			// Window closed
			if (Event.Type == sf::Event::Closed)
				App.Close();
			// Escape key pressed
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
				App.Close();
			if (Event.Key.Code == sf::Key::F1) {
				sf::Image Screen = App.Capture();
				Screen.SaveToFile("screenshot.jpg");
			}
			if (Event.Key.Code == sf::Key::Q) {
				drawstate=0;
			}
			if (Event.Key.Code == sf::Key::W) {
				drawstate=1;
			}
			if (Event.Key.Code == sf::Key::E) {
				drawstate=2;
			}
			//#############################
		}
		// Clear screen
		App.Clear();
		// Get elapsed time
		float ElapsedTime = App.GetFrameTime();
		if(drawstate==0) {
			// Move the sprite
			if (App.GetInput().IsKeyDown(sf::Key::Left))  Sprite.Move(-100 * ElapsedTime, 0);
			if (App.GetInput().IsKeyDown(sf::Key::Right)) Sprite.Move( 100 * ElapsedTime, 0);
			if (App.GetInput().IsKeyDown(sf::Key::Up))    Sprite.Move(0, -100 * ElapsedTime);
			if (App.GetInput().IsKeyDown(sf::Key::Down))  Sprite.Move(0,  100 * ElapsedTime);
			// Rotate the sprite
			if (App.GetInput().IsKeyDown(sf::Key::Add))      Sprite.Rotate(- 100 * ElapsedTime);
			if (App.GetInput().IsKeyDown(sf::Key::Subtract)) Sprite.Rotate(+ 100 * ElapsedTime);
			// Display sprite in our window
			App.Draw(Sprite);
		} else if(drawstate==1) {
			// Draw it
			if (App.GetInput().IsKeyDown(sf::Key::Left))  Polygon.Move(-100 * ElapsedTime, 0);
			if (App.GetInput().IsKeyDown(sf::Key::Right)) Polygon.Move( 100 * ElapsedTime, 0);
			if (App.GetInput().IsKeyDown(sf::Key::Up))    Polygon.Move(0, -100 * ElapsedTime);
			if (App.GetInput().IsKeyDown(sf::Key::Down))  Polygon.Move(0,  100 * ElapsedTime);
			if (App.GetInput().IsKeyDown(sf::Key::Add))      Polygon.Rotate(- 100 * ElapsedTime);
			if (App.GetInput().IsKeyDown(sf::Key::Subtract)) Polygon.Rotate(+ 100 * ElapsedTime);
			App.Draw(Polygon);
		} else {
			// Move the view using arrow keys
			float Offset = 200.f * App.GetFrameTime();
			if (App.GetInput().IsKeyDown(sf::Key::Up))    View.Move( 0,      -Offset);
			if (App.GetInput().IsKeyDown(sf::Key::Down))  View.Move( 0,       Offset);
			if (App.GetInput().IsKeyDown(sf::Key::Left))  View.Move(-Offset,  0);
			if (App.GetInput().IsKeyDown(sf::Key::Right)) View.Move( Offset,  0);
			// Zoom and unzoom using + and - keys
			if (App.GetInput().IsKeyDown(sf::Key::Add))      View.Zoom(1.010f);
			if (App.GetInput().IsKeyDown(sf::Key::Subtract)) View.Zoom(0.990f);
			// Set the view
			App.SetView(View);
			// Clear screen
			App.Clear();
			// Draw background
			App.Draw(Background);
			// Draw predefined shapes
			App.Draw(sf::Shape::Line(10, 10, 710, 100, 15, sf::Color::Red));
			App.Draw(sf::Shape::Circle(200, 200, 100, sf::Color::Yellow, 10, sf::Color::Blue));
			App.Draw(sf::Shape::Rectangle(350, 200, 600, 350, sf::Color::Green));
			// Draw cursor
			sf::Vector2f CursorPos = App.ConvertCoords(App.GetInput().GetMouseX(), App.GetInput().GetMouseY());
			Cursor.SetPosition(CursorPos);
			App.Draw(Cursor);
			// Reset to the default view to draw the interface
			App.SetView(App.GetDefaultView());
			// Draw some instructions
			App.Draw(Text);
		}
		std::string str = MakeString() << "FPS: " << 1/App.GetFrameTime(); 
		sf::String Fps(str);
		Fps.Move(10, 10);
		Fps.SetColor(sf::Color::White);
		App.Draw(Fps);
		// Display window contents on screen
		App.Display();
	}
	return EXIT_SUCCESS;
}
