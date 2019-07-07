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


	void getCameraSettings(Mat& cameraMatrix, Mat& distCoefficients) {
		FileStorage fs("out_camera_data.xml", FileStorage::READ);
		fs["Camera_Matrix"] >> cameraMatrix;
		fs["Distortion_Coefficients"] >> distCoefficients;
	}

	void track(const cv::Mat& input, cv::Mat& rvec, cv::Mat& tvec);
	int track(string& filename, time_t& start, time_t& end) {
		Mat cameraMatrix, distCoef;
		getCameraSettings(cameraMatrix, distCoef);
		VideoCapture cap(0);
		Mat frame;
		int count = 0;
		//Mat img1 = imread("box.png", IMREAD_GRAYSCALE);
		Mat imginha = imread(filename+".png");
		flip(imginha, imginha, 1);
		Mat img1;
		cvtColor(imginha, img1, CV_BGR2GRAY);
		int cont = 0;
		time(&start);
		while (cap.read(frame)) {
			cont++;
			Mat aux = frame.clone();
			undistort(aux, frame, cameraMatrix, distCoef);
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
			if (keypoints_1.empty() || keypoints_2.empty()) {
				imshow("Projeto 2 PG", frame);
				waitKey(1);
				continue;
			}
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
				if (matches[i].distance <= max(min_dist*1.1, 50.0))
				{
					good_matches.push_back(matches[i]);
				}
			}

			Mat img_goodmatch;
			drawMatches(imginha, keypoints_1, frame, keypoints_2, good_matches, img_goodmatch, Scalar::all(-1), Scalar::all(-1),
				vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
			
			//-- Localize the object
			std::vector<Point2f> obj;
			std::vector<Point2f> scene;
			for (size_t i = 0; i < good_matches.size(); i++)
			{
				//-- Get the keypoints from the good matches
				obj.push_back(keypoints_1[good_matches[i].queryIdx].pt);
				scene.push_back(keypoints_2[good_matches[i].trainIdx].pt);
			}
			Mat H = findHomography(obj, scene, RANSAC);

			if (H.empty()) {
				imshow("Projeto 2 PG", img_goodmatch);
				waitKey(1);
				continue;
			}
			//-- Get the corners from the image_1 ( the object to be "detected" )
			std::vector<Point2f> corner(4);
			corner[0] = cvPoint(0, 0);
			corner[1] = cvPoint(img1.cols, 0);
			corner[2] = cvPoint(img1.cols, img1.rows);
			corner[3] = cvPoint(0, img1.rows);

			vector<Point2f> scene_corners(4);
			perspectiveTransform(corner, scene_corners, H);
			//-- Draw lines between the corners (the mapped object in the scene - image_2 )
			line(img_goodmatch, scene_corners[0] + Point2f((float)img1.cols, 0),
				scene_corners[1] + Point2f((float)img1.cols, 0), Scalar(0, 255, 0), 4);
			line(img_goodmatch, scene_corners[1] + Point2f((float)img1.cols, 0),
				scene_corners[2] + Point2f((float)img1.cols, 0), Scalar(0, 255, 0), 4);
			line(img_goodmatch, scene_corners[2] + Point2f((float)img1.cols, 0),
				scene_corners[3] + Point2f((float)img1.cols, 0), Scalar(0, 255, 0), 4);
			line(img_goodmatch, scene_corners[3] + Point2f((float)img1.cols, 0),
				scene_corners[0] + Point2f((float)img1.cols, 0), Scalar(0, 255, 0), 4);

			imshow("Projeto 2 PG", img_goodmatch);
			//waitKey(1);
			char c = (char)waitKey(1);
			if (c == 27 || c == 'q' || c == 'Q') {
				time(&end);
				destroyAllWindows();
				return cont;
			}
		}
	}

private:
};