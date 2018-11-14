#define WIDTH 1920
#define HEIGHT 1080

//object for creating, manipulating, and displaying layers
class Layer{
public:
int x,y;
sf::Texture image;
sf::Sprite sprite;
sf::RenderTexture layer;
bool isImage=false;

Layer(int x=0,int y=0,std::string filename=""){
	this->x=x;
	this->y=y;
	layer.create(WIDTH,HEIGHT);

	if(filename!=""){
		isImage=true;
		image.loadFromFile(filename);
	}
}
sf::Sprite getSprite(){
	if(isImage){
		sprite.setTexture(image);
		sprite.setPosition(x,y);
	}else{
		layer.display();
		const sf::Texture& texture=layer.getTexture();
		sprite=sf::Sprite(texture);
		sprite.setPosition(x,y);
	}
	return sprite;
}
void move(int dx,int dy){
	x+=dx;
	y+=dy;
}
};

