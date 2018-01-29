#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

sf::Window * window;

unsigned int screen_width;
unsigned int screen_height;

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,screen_width,0.0,screen_height,-1000.0,1000.0);
	glTranslatef(screen_width/2,screen_height/2,0.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(60.0,1.0,0.0,0.0);
	glRotatef(45.0,0.0,0.0,1.0);
	int tile_width = 20;
	int side_length = 16;

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	for (int x = 0; x < side_length; x++){
		for (int y = 0; y < side_length; y++){
			(x+y)%2 == 0 ? glColor3f(1.0,1.0,1.0) : glColor3f(0.4,0.4,0.4);
			glBegin(GL_QUADS);
			glVertex3f(-(tile_width*side_length)/2+tile_width*x,-(tile_width*side_length)/2+tile_width*y,0);
			glVertex3f(-(tile_width*side_length)/2+tile_width*x,-(tile_width*side_length)/2+tile_width*(y+1),0);
			glVertex3f(-(tile_width*side_length)/2+tile_width*(x+1),-(tile_width*side_length)/2+tile_width*(y+1),0);
			glVertex3f(-(tile_width*side_length)/2+tile_width*(x+1),-(tile_width*side_length)/2+tile_width*y,0);
			glEnd();
		}
	}

	glPopMatrix();
	glPopMatrix();
	window->display();
}

void init(){
	srand(time(NULL));
	glClearColor(0.0,0.0,0.0,1.0);
	glViewport(0.0,0.0,1024,576);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

int main(int argc, char **argv) {
	screen_width = 1024;
	screen_height = 576;
	window = new sf::Window(sf::VideoMode(screen_width,screen_height),"GameLike");

    window->setVerticalSyncEnabled(true);
    window->setActive(true);
    init();

    bool running = true;
    while (running){
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
                window->close();
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust these stored values
                screen_width = event.size.width;
                screen_height = event.size.height;
            }
        }
    	display();
    }
	return 1;
}
