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

int main(int argc, char** argv) {
	int choice;
	cout << "- Obrigado Josue, eu nao nasci pra ser corno" << endl << endl;
	cout << "( ._.)   - Josue e GOD ue" << endl;
	cout << "/|.|>" << endl;
	cout << " | \\ " << endl << endl << endl;
	cout << "Pressione 1 para Calibrar 2 para O outro negocio que eu nao sei o nome" << endl;
	cin >> choice;
	if (choice == 1) {
		calibrate();
	}
	else {
		//runCalibration();
		Tracker a;
		a.track();
	}

	return 0;
}