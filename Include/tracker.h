#pragma once

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

class Tracker {
public:

	//void track(const cv::Mat& input, cv::Mat& rvec, cv::Mat& tvec);
	void track() {
		VideoCapture cap(0);
		Mat frame;
		int count = 0;
		Mat img1 = imread("box.png", IMREAD_GRAYSCALE);
		flip(img1, img1, 1);

		while (cap.read(frame)) {
			Mat greyMat;
			flip(frame, frame, 1);
			cvtColor(frame, greyMat, CV_BGR2GRAY);

			vector<KeyPoint> keypoints_1, keypoints_2;
			Mat descriptors_1, descriptors_2;

			Ptr<FeatureDetector> detector = ORB::create();
			Ptr<DescriptorExtractor> descriptor = ORB::create();

			Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");

			detector->detect(img1, keypoints_1);
			detector->detect(greyMat, keypoints_2);

			descriptor->compute(img1, keypoints_1, descriptors_1);
			descriptor->compute(greyMat, keypoints_2, descriptors_2);

			Mat outimg1;
			drawKeypoints(img1, keypoints_1, outimg1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

			vector<DMatch> matches;

			matcher->match(descriptors_1, descriptors_2, matches);

			double min_dist = 1000, max_dist = 0;

			for (int i = 0; i < descriptors_1.rows; i++)
			{
				double dist = matches[i].distance;
				if (dist < min_dist) min_dist = dist;
				if (dist > max_dist) max_dist = dist;
			}

			vector< DMatch > good_matches;
			for (int i = 0; i < descriptors_1.rows; i++)
			{
				if (matches[i].distance <= max(1.1 * min_dist, 50.0))
				{
					good_matches.push_back(matches[i]);
				}
			}

			Mat img_goodmatch;
			drawMatches(img1, keypoints_1, greyMat, keypoints_2, good_matches, img_goodmatch);
			imshow("Projeto 2 PG", img_goodmatch);
			waitKey(1);
		}
	}

private:
};