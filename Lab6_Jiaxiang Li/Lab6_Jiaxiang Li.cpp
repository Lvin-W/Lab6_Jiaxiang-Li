#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

int contrast(int x, int factor) {
	int ans = x + factor;
	if (ans > 255 || ans < 0) {
		if (ans > 255) return 255;
		else if (ans < 0) return 0;
	}
	else return ans;
}

int main() {
	string background = "../images1/backgrounds/prague.png";
	string foreground = "../images1/characters/yoda.png";

	Texture backgroundTex;
	if (!backgroundTex.loadFromFile(background)) {
		cout << "Couldn't Load Image" << endl;
		exit(1);
	}
	Texture foregroundTex;
	if (!foregroundTex.loadFromFile(foreground)) {
		cout << "Couldn't Load Image" << endl;
		exit(1);
	}

	Image backgroundImage;
	backgroundImage = backgroundTex.copyToImage();

	Image foregroundImage;
	foregroundImage = foregroundTex.copyToImage();

	Image character;
	character = backgroundTex.copyToImage();

	Vector2u sz = backgroundImage.getSize();
	for (int y = 0; y < sz.y; y++) {
		for (int x = 0; x < sz.x; x++) {
			
			Color pixel = foregroundImage.getPixel(x, y);
			Color black(0, 0, 0);

			if (pixel.r > 150 || pixel.g < 210 || pixel.b > 150) {
				pixel = foregroundImage.getPixel(x, y);

				float factor = -0.25;
				int r = contrast(pixel.r, (pixel.r) * factor);
				int g = contrast(pixel.g, (pixel.g) * factor);
				int b = contrast(pixel.b, (pixel.b) * factor);

				Color alter(r, g, b);
				character.setPixel(x, y, alter);
			}
			//else character.setPixel(x, y, black);
		}
	}

	Texture tex;
	Texture tex1;
	tex.loadFromImage(character);
	//tex1.loadFromImage(backgroundImage);

	RenderWindow window(VideoMode(1024, 768), "Here's the composition");
	Sprite sprite;
	sprite.setTexture(tex);
	//sprite.setPosition(0, 100);

	window.clear();
	window.draw(sprite);
	window.display();
	while (true);

}