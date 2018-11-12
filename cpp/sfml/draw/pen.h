class Pen{
public:
sf::Sprite penSprite;
sf::RenderTexture pen;
Pen(int brushWidth,sf::Color color){
	pen.create(brushWidth*2,brushWidth*2);

	sf::CircleShape brush;
	brush=sf::CircleShape(brushWidth);
	brush.setFillColor(color);
	pen.draw(brush);

	pen.display();
	const sf::Texture& penTexture=pen.getTexture();
	penSprite=sf::Sprite(penTexture);
	penSprite.setOrigin(
		brush.getLocalBounds().width/2,
		brush.getLocalBounds().height/2
	);
}
};
