#pragma once

#include <opencv2/core/core.hpp>

class Tracker {
public:

    void track(const cv::Mat &input, cv::Mat &rvec, cv::Mat &tvec);

private:
};