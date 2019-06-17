#include "Point.h"

const Vec2 Point::GetPosition() const
{

	return position;
}

const olc::Pixel Point::GetColor()
{
	return color;
}

void Point::SetPos(const Vec2& otherPos)
{

	position = otherPos;

}

void Point::SetColor(const olc::Pixel& newColor)
{
	color = newColor;
}

void Point::SpawnParticle()
{
	const int newX = rand() % ScreenW; //genneram o pozitie random pe x
	SetPos(Vec2(newX, yStartingPos));
}

void Point::Project() //se mai poate modifica putin
{//ideea la functia asta e ca proiectez particula random intr o anumita directie
	if(position.y>0)
	this->position+=velocity;
}

void Point::Fade() //pur si simplu n am idee asa ca o sa fac o soutie neportabila, anume cresc nuanta de negru din 
{
	//culoare cu fiecare update. Nu's mandru da merge
	int r, g, b;
	r = GetColor().r;


	g = GetColor().g;


	b = GetColor().b;
	if (r != 0)
	{
		if (r >= 1)
			r -= 1;
		else
			if (r < 1)
				r = 0;
	}
	if (g != 0)
	{
		if (g >= 1)
			g -= 1;
		else
			if (g < 1)
				g = 0;
	}
	if (b != 0)
	{
		if (b >= 1)
			b -= 1;
		else
			if (b < 1)
				b = 0;
	}
		this->SetColor(olc::Pixel(r, g, b));
}
