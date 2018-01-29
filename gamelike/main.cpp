#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

sf::Window * window;

unsigned int screen_width;
unsigned int screen_height;
sf::Vector2f camera_pos;
float camera_speed;

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glTranslatef(-camera_pos.x,-camera_pos.y,0.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(60.0,1.0,0.0,0.0);
	glRotatef(45.0,0.0,0.0,1.0);
	int tile_width = 64; //this should end up roughly the pixel length actually!
	int side_length = 8;

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

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	window->display();
}

void init(){
	srand(time(NULL));
	glClearColor(0.0,0.0,0.0,1.0);
	glViewport(0.0,0.0,1024,576);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,screen_width,0.0,screen_height,-1000.0,1000.0);
	glTranslatef(screen_width/2,screen_height/2,0.0);
}

void handle_arrow_keys(){
	bool arrow_key_pressed = false;
	sf::Vector2f camera_movement = sf::Vector2f(0.0,0.0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		camera_movement.x -= 1;
		arrow_key_pressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		camera_movement.x += 1;
		arrow_key_pressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		camera_movement.y += 1;
		arrow_key_pressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		camera_movement.y -= 1;
		arrow_key_pressed = true;
	}
	if (arrow_key_pressed){
		float magnitude = sqrt(camera_movement.x*camera_movement.x+camera_movement.y*camera_movement.y);
		if (magnitude != 0){
			camera_movement = camera_speed*camera_movement/magnitude;
			camera_pos = camera_pos + camera_movement;
		}
	}

}

int main(int argc, char **argv) {
	camera_pos = sf::Vector2f(0,0);
	camera_speed = 2.0;
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
                printf("Screen width after resize: %d\n",screen_width);
                printf("Screen height after resize: %d\n",screen_height);
                glViewport(0,0,screen_width,screen_height);
                glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glOrtho(0.0,screen_width,0.0,screen_height,-1000.0,1000.0);

				glTranslatef(screen_width/2,screen_height/2,0.0);
            }
        }

        handle_arrow_keys();

    	display();
    }
	return 1;
}
