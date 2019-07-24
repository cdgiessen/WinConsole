#include <iostream>
#include <cstdlib>
#include <ctime>
#include "WinConsole.h"

#define PI   3.14159
#define PId2  PI / 2
#define PId3  PI / 3
#define PId4  PI / 4
#define PId6  PI / 6
#define PI2   PI * 2

using namespace std;

namespace bin {
	
	float frand(float min, float max) {
		return (float)(rand()) / (float)(RAND_MAX) * (max - min) + min;
	}
	
	float irand(int min, int max) {
		return rand() % (max - min) + min;
	}
	
	struct Bullet {
		float x;
		float y;
		float theta;
		float speed;
		wc::Map map;
		
		bool todelete;
		unsigned short team;
		
		Bullet(float x, float y, float theta, float speed, unsigned short team) {
			this->theta = theta;
			this->speed = speed;
			this->team = team;
			
			std::vector<char *> m = {
				(char *)(R"( /\ )"),
				(char *)(R"(/||\)"),
				(char *)(R"(\||/)")
			};
			map = wc::Map(3, m.size(), m);

			this->x = x - map.width / 2;
			this->y = y - map.height / 2;
		}
		
		void tick(wc::WinConsole &parent) {
			x += (cos(theta) * speed) * (parent.getElapsed() * 2);
			y += (sin(theta) * speed) * (parent.getElapsed() * 2);
			if(x < -map.width || y < map.height || x > parent.getWidth() || y > parent.getHeight())
				todelete = true;
		}
	};
	
	struct Player {
		float x;
		float y;
		float theta;
		float speed;
		float turnspeed;
		wc::Map map;
		
		bool shootheld;
		
		Player(float x, float y) {
			this->x = x;
			this->y = y;
			this->theta = 0.0f;
			this->speed = 10.0f;
			this->turnspeed = 3.14159 / 6;
			shootheld = false;
			std::vector<char *> m = {
				(char *)(R"(       [']       )"),
				(char *)(R"(       [ ]       )"),
				(char *)(R"(       [ ]       )"),
				(char *)(R"(       [ ]       )"),
				(char *)(R"(       [ ]       )"),
				(char *)(R"(       [ ]       )"),
				(char *)(R"(       [ ]       )"),
				(char *)(R"(       [ ]       )"),
				(char *)(R"(       [ ]       )"),
				(char *)(R"(       [ ]       )"),
				(char *)(R"(  _--_ [ ] _--_  )"),
				(char *)(R"( / `` \[ ]/ `` \ )"),
				(char *)(R"(/ ``^`{[ ]}`^`` \)"),
				(char *)(R"(\`` `_{[ ]}_` ``/)"),
				(char *)(R"(/^  |_{[ ]}_|  ^\)"),
				(char *)(R"((* //'{[ ]}'\\ *))"),
				(char *)(R"({ ::  :[ ]:] :: })"),
				(char *)(R"({::  ''[ ]']  ::})"),
				(char *)(R"({:  / S[ ] ]\  :})"),
				(char *)(R"((* |/'\[ ]YY | *))"),
				(char *)(R"({: |\o/[ ]:  | :})"),
				(char *)(R"({: |: |[ ]| :| :})"),
				(char *)(R"({:  :: \_/ ::  :})"),
				(char *)(R"((*   ::   ::   *))"),
				(char *)(R"({:    ::.::    :})"),
				(char *)(R"({\[_]  ```  [_]/})"),
				(char *)(R"({ \__/\___/\__/ })"),
				(char *)(R"((__ _ _;.;_ _ __))"),
				(char *)(R"( \____/   \____/ )"),
			};
			map = wc::Map(17, m.size(), m);
		}
		
		void tick(wc::WinConsole &parent, std::vector<Bullet> &bulletbuffer) {
			
			if(parent.getKey('A')) {
				theta += turnspeed * parent.getElapsed();
			}
			if(parent.getKey('D')) {
				theta -= turnspeed * parent.getElapsed();
			}
			if(parent.getKey('W')) {
				x += (cos(theta + PId2) * speed) * parent.getElapsed();
				y -= (sin(theta + PId2) * speed) * parent.getElapsed();
			}
			if(parent.getKey('S')) {
				x -= (cos(theta + PId2) * speed) * parent.getElapsed();
				y += (sin(theta + PId2) * speed) * parent.getElapsed();
			}
			if(parent.getKey(' ')) {
				if(!shootheld) {
					shootheld = true;
					float xx = x + map.width / 2 - (cos(theta + PId2) * map.height / 2) * 2,
						  yy = y + map.height / 2 - (sin(theta + PId2) * map.height / 2) * 2;
					Bullet b(
						xx,
						yy,
						-(theta + PId2), 
						64.0f,
						0
					);
					bulletbuffer.push_back(b);
					parent.stringAt(0, 0, "What!");
				}
			} else shootheld = false;
		}
	};
	
	struct Enemy {
		float x;
		float y;
		float theta;
		unsigned int type;
		unsigned int team;
		wc::Map map;
		
		bool todelete;
		bool killedbyplayer;
		enum AI_MODES {
			TURNING,
			MOVING
		};
		unsigned short mode;
		
		Enemy(float x, float y) {
			theta = frand(0, PI2);
			type = 0; //type = irand(0, 4);
			todelete = false;
			std::vector<char *> m;
			int w = 0;
			switch(type) {
				default:
				case 0:
					w = 17;
					m = {
						(char *)(R"(       ._.       )"),
						(char *)(R"(      /   \      )"),
						(char *)(R"(      '- -'      )"),
						(char *)(R"(       / \       )"),
						(char *)(R"(       \ /       )"),
						(char *)(R"(       / \       )"),
						(char *)(R"(       \ /       )"),
						(char *)(R"(       / \       )"),
						(char *)(R"(       \ /       )"),
						(char *)(R"(       / \       )"),
						(char *)(R"(  _--_ \ / _--_  )"),
						(char *)(R"( / __ \/ \/ __ \ )"),
						(char *)(R"(/''  ''\ /''  ''\)"),
						(char *)(R"(\ __   / \   __ /)"),
						(char *)(R"(/I  \_o\ /o_/  I\)"),
						(char *)(R"(\I _/ \/I\/ \_ I/)"),
						(char *)(R"(/:/    \I/ ===\:\)"),
						(char *)(R"(>:|/'\ /I\ ===|:<)"),
						(char *)(R"(\:|[=]| I |===|:/)"),
						(char *)(R"(/:|\ /:.I.:===|:\)"),
						(char *)(R"(\:|_+_|| ||===|:/)"),
						(char *)(R"(>:\   :\./:===/:<)"),
						(char *)(R"(/: \  \___/  / :\)"),
						(char *)(R"(\:  \_/   \_/  :/)"),
						(char *)(R"(/:   \_____/   :\)"),
						(char *)(R"(> \_         _/ <)"),
						(char *)(R"(\   --_____--   /)"),
						(char *)(R"( \     /-\     / )"),
						(char *)(R"(  \___/   \___/  )"),
					};
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
			}
			map = wc::Map(w, m.size(), m);
			this->x = x - map.width / 2;
			this->y = y - map.height / 2;
			mode = TURNING;
		}
	};
	
	void tick(wc::WinConsole *parent) {
		
	}
}

class WinDemo : public wc::WinConsole {
	private:
		bin::Player *player;
		vector<bin::Bullet> bullets;
		vector<bin::Enemy> enemies;
	public:
		WinDemo() {
			player = NULL;
		}
		~WinDemo() {
			delete player;
		}
	public:
		
		virtual bool init() {
			player = new bin::Player(getWidth() / 2, getHeight() / 2);
			enemies.push_back(bin::Enemy(64, 64));
			bullets = vector<bin::Bullet>();
			return true;			
		}
		
		virtual bool tick(float elapsed) {

			player->tick(*this, bullets);
			for(short i = bullets.size() - 1; i >= 0; i--) {
				bullets[i].tick(*this);
				if(bullets[i].todelete)
					bullets.erase(bullets.begin() + i);
			}
			
			stringAt(0, 0, " ");
			return true;
		}
		
		virtual bool render() {
			translate(player->x + player->map.width / 2, player->y + player->map.height / 2);
			rotate(player->theta);
			updateTransform();
			drawMap(-player->map.width / 2, -player->map.height / 2, player->map, true);
			resetTransform();
			
			for(bin::Bullet b : bullets) {
				translate(b.x + b.map.width / 2, b.y + b.map.height / 2);
				rotate(b.theta);
				updateTransform();
				drawMap(-b.map.width / 2, -b.map.height / 2, b.map, true);
				resetTransform();			
			}
			
			for(bin::Enemy e : enemies) {
				translate(e.x + e.map.width / 2, e.y + e.map.height / 2);
				rotate(e.theta);
				updateTransform();
				drawMap(-e.map.width / 2, -e.map.height / 2, e.map, true);
				resetTransform();			
			}
			 
			return true;
		}
	
};

int main() {
	srand((unsigned int)time( NULL ));
	float fuckyou = bin::frand(0, 100);  // For srand is bugged if I do not call this.
	
	
	WinDemo dem;
	if(dem.build(200, 200, 4, 4)) {
		dem.start();
	}
	else {
		cout << "Well %@?$!" << endl;
		
	}
	
	cout << "Done." << endl;
	return 0;
}


