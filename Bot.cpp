
#include <windows.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <ViZDoom.h>
#include <ctime>


using namespace vizdoom;
using namespace cv;
using namespace std;


int main()
{
	DoomGame* game = new DoomGame();

	try
	{
		string path = "C:\\practice\\vizdoom";
		game->setViZDoomPath(path + "\\vizdoom.exe");
		game->setDoomGamePath(path + "\\freedoom2.wad");
		game->loadConfig(path + "\\scenarios\\basic.cfg");
		game->setWindowVisible(true);
		game->setRenderWeapon(true);
		game->setRenderCrosshair(true);
		game->init();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		return 0;
	}

	namedWindow("control Window", WINDOW_AUTOSIZE);
	auto image = Mat(480, 640, CV_8UC3);

	unsigned int sleepTime = 1000 / DEFAULT_TICRATE;

	auto episodes = 10;

	std::vector<double> actions[3];
	actions[0] = { 1, 0, 0 };
	actions[1] = { 0, 1, 0 };
	actions[2] = { 0, 0, 1 };

	//game->setAvailableGameVariables(std::vector<POSITION_X> variables);
	int skiprate = 2;

	for (auto i = 0; i < episodes; i++) 
	{
		int t = 0;
		game->newEpisode();
		cout << "Episode #" << i + 1 << endl;

		while (!game->isEpisodeFinished())
		{
			auto gamestate = game->getState();
			auto screenBuf = gamestate->screenBuffer;
			//image.data = screenBuf->data();
			game->makeAction(actions[std::rand() % (game->getAvailableButtonsSize() - 1)], skiprate);
			if (t % 47 == 0)
				game->makeAction(actions[2]);
			t++;
			//cout << CAMERA_POSITION_X << '\n';

			//double reward = game->makeAction(actions[std::rand() % game->getAvailableButtonsSize()]);
			Sleep(sleepTime);
		}
	}

	game->close();
	delete game;
}
