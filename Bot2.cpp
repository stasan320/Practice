#include <iostream>
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <ViZDoom.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

using namespace vizdoom;
using namespace cv;
using namespace std;

int main() {
	DoomGame* game = new DoomGame();
	std::vector<double> actions[3];
	actions[0] = { 1, 0, 0 };
	actions[1] = { 0, 1, 0 };
	actions[2] = { 0, 0, 1 };

	try {
		string path = "C:\\practice\\practice\\vizdoom";
		game->setViZDoomPath(path + "\\vizdoom.exe");
		game->setDoomGamePath(path + "\\freedoom2.wad");
		game->loadConfig(path + "\\scenarios\\basic.cfg");
		game->setWindowVisible(true);
		game->setRenderWeapon(true);
		game->init();
	}
	catch (exception& e) {
		cout << e.what() << endl;
		return 0;
	}

	unsigned int sleepTime = 1000 / DEFAULT_TICRATE;


	auto episodes = 10;
	for (auto i = 0; i < episodes; i++) {
		int time = 0, k = 0;
		clock_t t1, t2;
		game->newEpisode();
		cout << "Episode #" << i + 1 << endl;

		t1 = clock();
		while (!game->isEpisodeFinished()) {
			time++;
			auto gamestate = game->getState();

			BufferPtr screenBuf = gamestate->screenBuffer;
			
			if(time % 5 == 0) game->makeAction(actions[2]);

			game->makeAction(actions[k]);
			Sleep(sleepTime);

			t2 = clock();
			if ((t2 - t1) > 2000) k = (k + 1) % 2;
			if ((t2 - t1) > 2000) t1 = clock();
		}
	}

	game->close();
	delete game;
}