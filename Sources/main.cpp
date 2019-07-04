#include <calibration.h>
#include <loader.h>
#include <tracker.h>
#include <renderer.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main() {

    cv::VideoCapture cap(1);
    cv::Mat frame;
    int count = 0;

    while (cap.read(frame)) {

        std::vector<cv::Mat> channels;


        if (count % 10 == 0)
        for (int i = 0; i < 200; i++)
            for (int j = 0; j < 200; j++)
                frame.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 255, 255);


        cv::split(frame, channels);

        cv::imshow("ProjetoPG", frame);
        cv::waitKey(1);
        count++;
    }

    return 0;
}