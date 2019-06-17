#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
//DE ADAUGAT COMENTARII!!! 
#define OLC_PGEX_SOUND
#include "olcPGEX_Sound.h"

#include "Point.h"
#include <stdio.h>
#include <vector>
#include <chrono>
class FireWurks : public olc::PixelGameEngine
{
public:
	 int sndSampleA;
	 int sndSampleB;
	 int nrOfFireworks = 150;
	std::vector<std::pair<Point*,int>> fireWorks; //Pt fiecare firework avem si un y boundary pt cat de sus este proiectat

	std::vector<Point*> partycles;//vectoru cu particule care trbuie sa explodeze
	FireWurks()
	{
		sAppName = "!!!Fireworks!!!";
	}
public:
	void Explode(const Point* particle)
	{
		olc::Pixel partColour(rand() % 256, rand() % 256, rand() % 256);
		size_t nrOfParticles = rand() % 250; //valoare hard codata pr random
		for (size_t i = 0; i < nrOfParticles; i++)
		{ //generarea unui numar STRICT POZITIV intre0 si o valoare x. Am facut acest lucru ca sa fie particule improsacte pe toate directiile, nu doar pe directii int
			float randomXDir=static_cast <float> (rand()) / static_cast <float> (RAND_MAX/((rand()%10)+1));
			float randomYDir=static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (rand() % 10+1));
			//aici scad 3 ca sa dea si directii negative sa fie un cerc care acopera toate imprejurimile
			Point* part = new Point(particle->GetPosition(), partColour, Vec2(randomXDir-3, randomYDir-3),rand()%5+1);
			//aici generam o positie noua randon,culoare random,velocitate random,lifespan random
			partycles.push_back(part);
		}
	}

	///creca cel mai bine e ca timpurile mele sa fie in int bag pl in float
	bool OnUserCreate() override
	{
		//olc::SOUND::InitialiseAudio(44100, 1, 8, 512);

		//sndSampleA = olc::SOUND::LoadAudioSample("DeploySound.mp3");
	    //sndSampleB = olc::SOUND::LoadAudioSample("ExplosionSound.wav");
		

		CreateParticle();
		//nush daca sa pun cv aici
		return true;
	}
	void CreateParticle()//arunc in aer o particula
	{
		Point* p = new Point();
		int ySpan = rand() % ScreenHeight() + 1;
		p->SpawnParticle();
		p->SetColor(olc::WHITE);
		std::pair<Point*, int> perechea_de_gratie;
		perechea_de_gratie.first = p;
		perechea_de_gratie.second = ySpan;
		fireWorks.push_back(perechea_de_gratie);
		//olc::SOUND::PlaySample(sndSampleA);
	}
		bool OnUserUpdate(float fElapsedTime) override
	{
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);//WE CLEAR THE SCREEN
		if(nrOfFireworks>=0)
		{
			auto p = fireWorks[0];
			if (p.first->GetPosition().y > p.second)
			{
				
				Draw(p.first->GetPosition().x, p.first->GetPosition().y, p.first->GetColor());
				p.first->Project();
				p.first->Fade();
			    Sleep(10);
			}
			if (p.first->GetPosition().y <= p.second)
			{
				if (!(p.first->deployed))
				{
					fireWorks.erase(fireWorks.begin());
					//olc::SOUND::PlaySample(sndSampleB);
					Explode(p.first);
					nrOfFireworks--;
					CreateParticle();

				}
			}

		}
		for (auto& p : partycles)
		{
			
			Draw(p->GetPosition().x, p->GetPosition().y, p->GetColor());
			p->Project();
			p->Fade();
		
		}
		return true;
	}
};
int main()
{
	FireWurks demo;

	std::srand(time(nullptr));

	if (demo.Construct(400, 300, 2, 2))
		demo.Start();
	return 0;
}