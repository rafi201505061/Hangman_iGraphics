#include "texture.h"

texture smurfTexture;
texture character;
texture pic;
texture pic2;
texture hang0;
texture hang1;
texture hang2;
texture hang3;
texture hang4;
texture hang5;
texture goback;
texture goback2;
texture help;
texture wrong;
texture correct;



void textureInit()
{
	smurfTexture.Create("Nets_court_2.bmp");
	character.Create("Flappy_Bird.bmp");
	pic.Create("Starter.bmp");
	pic2.Create("files//Home.bmp");
	hang0.Create("files//hang0.bmp");
	hang1.Create("files//hang1.bmp");
	hang2.Create("files//hang2.bmp");
	hang3.Create("files//hang3.bmp");
	hang4.Create("files//hang4.bmp");
	hang5.Create("files//hang5.bmp");
	goback.Create("files//back.bmp");
	goback2.Create("files//back2.bmp");
	help.Create("files//help.bmp");
	correct.Create("files//correct.bmp");
	wrong.Create("files//wrong.bmp");

}
