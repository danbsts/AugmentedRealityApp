#include <calibration.h>
#include <loader.h>
#include <tracker.h>
#include <renderer.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;
using namespace std;

void mainha()
{
	VideoCapture video(0);
	double fps = video.get(CAP_PROP_FPS);
	cout << "Frames per second using video.get(CV_CAP_PROP_FPS) : " << fps << endl;
	int num_frames = 120;
	time_t start, end;
	Mat frame;
	cout << "Capturing " << num_frames << " frames" << endl;
	time(&start);
	for (int i = 0; i < num_frames; i++)
	{
		video >> frame;
	}

	time(&end);

	
	double seconds = difftime(end, start);
	cout << "Time taken : " << seconds << " seconds" << endl;

	
	fps = num_frames / seconds;
	cout << "Estimated frames per second : " << fps << endl;

	
	video.release();
	return;
}

int main(int argc, char** argv) {
	int choice;
	cout << "Pressione 1 para Calibrar ou 2 para fazer o rastreamento" << endl;
	
	double fps;
	time_t start, end;
	while (cin >> choice) {
		if (choice == 1) {
			fps = calibrate();
		}
		else if(choice == 2) {
			cout << "digite o nome do arquivo a ser rastreado" << endl;
			cout << "arquivos disponiveis:" << endl;
			cout << "box3" << endl;
			cout << "negocio" << endl;
			cout << "livro";
			string s;
			cin >> s;
			Tracker a;
			fps = a.track(s, start, end);
			double seconds = difftime(end, start);
			cout << "Time taken : " << seconds << " seconds" << endl;
			fps = fps / seconds;
			cout << "Estimated frames per second : " << fps << endl;
		}
		else {
			break;
		}
		
	}

	return 0;
}