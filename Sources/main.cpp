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

	// Start default camera
	VideoCapture video(0);

	// With webcam get(CV_CAP_PROP_FPS) does not work.
	// Let's see for ourselves.

	double fps = video.get(CAP_PROP_FPS);
	// If you do not care about backward compatibility
	// You can use the following instead for OpenCV 3
	// double fps = video.get(CAP_PROP_FPS);
	cout << "Frames per second using video.get(CV_CAP_PROP_FPS) : " << fps << endl;


	// Number of frames to capture
	int num_frames = 120;

	// Start and end times
	time_t start, end;

	// Variable for storing video frames
	Mat frame;

	cout << "Capturing " << num_frames << " frames" << endl;

	// Start time
	time(&start);

	// Grab a few frames
	for (int i = 0; i < num_frames; i++)
	{
		video >> frame;
	}

	// End Time
	time(&end);

	// Time elapsed
	double seconds = difftime(end, start);
	cout << "Time taken : " << seconds << " seconds" << endl;

	// Calculate frames per second
	fps = num_frames / seconds;
	cout << "Estimated frames per second : " << fps << endl;

	// Release video
	video.release();
	return;
}

int main(int argc, char** argv) {
	int choice;
	cout << "- Obrigado Josue, eu nao nasci pra ser corno" << endl << endl;
	cout << "( ._.)   - Josue e GOD ue       (._. )" << endl;
	cout << "/|.|>                        S2--| |>" << endl;
	cout << " | \\                             | |" << endl;
	cout << "------------------------------------------" << endl << endl;
	cout << "Pressione 1 para Calibrar 2 para O outro negocio que eu nao sei o nome" << endl;
	//mainha();
	double fps;
	time_t start, end;
	while (cin >> choice) {
		if (choice == 1) {
			fps = calibrate();
		}
		else if(choice == 2) {
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