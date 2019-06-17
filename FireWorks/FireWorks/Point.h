#pragma once 
#include "olcPixelGameEngine.h"
#include "Vec2.h"
#include <vector>
#define ScreenW 400 //i m sorry for the define
class Point {///clasa virtuala  care reprez toate particulele din joc
private:
	olc::Pixel color; //culoarea
	Vec2 position; ///positia pct
	Vec2 velocity;
	int lifespan;
	static constexpr size_t yStartingPos=250; //toate pct pleaca din y pe acelasi loc	
	//din nou,e valoare hard codata luata din main de la dimensiunile consolei. chiar nu am ce sa fac .
public:
	bool deployed=false;
	~Point() = default;//afaik nu mi trebuie constructor specific, ca n am mem dinamica
	Point(const Vec2& p = { 0,0 }, const olc::Pixel& colour = olc::Pixel{ 0,0,0 }, const Vec2& newVel = { 0,-1.0f },const int& newLifespan = 0 ) //las by default 0,-1 ca sa ma deplasez perpenducular in sus intai,apoi dupa explozie sa go wild :D
		:
		position(p),
		color(colour),
		velocity(newVel),
		lifespan(newLifespan)
	    {}
	const Vec2 GetPosition() const;	
	
	const olc::Pixel GetColor();

	void SetPos(const Vec2& otherPos);

	void SetColor(const olc::Pixel& newColor);
	
	void SpawnParticle();
	
	void Project();
	
	void Fade(); //particles start to fade as soon as they ve been spawned
    
};
