#include "cloak_remover.h"

CloakRemover::CloakRemover() {
    cv::Mat _tempImage = cv::imread(
            "/home/red-scule/Desktop/projects/cpp_projects/rubik_cube/assets/2.jpg", 1);

    cv::VideoCapture cap = cv::VideoCapture(0);

    for (int i = 0; i < 30; ++i) {
        cap >> _background;
    }


    while (cv::waitKey(1) != 113) {
        cv::Mat currentFrame;

        cap >> currentFrame;

        cv::Mat hsv;
        cv::cvtColor(currentFrame, hsv, cv::COLOR_BGR2HSV);

        cv::Mat mask1;
        cv::inRange(hsv, cv::Vec3i{0, 120, 70}, cv::Vec3i{10, 255, 255}, mask1);

        cv::Mat mask2;
        cv::inRange(hsv, cv::Vec3i{170, 120, 70}, cv::Vec3i{180, 255, 255}, mask2);

        cv::Mat mask = mask1 + mask2;
        cv::morphologyEx(mask, mask, cv::MORPH_OPEN, cv::Vec3i{5, 5});

        for (int i = 0; i < currentFrame.rows; ++i) {
            for (int j = 0; j < currentFrame.cols; ++j) {
                if (mask.at<uchar>(i, j) == 255) {
                    currentFrame.at<cv::Vec3b>(i, j)[0] = _background.at<cv::Vec3b>(i, j)[0];
                    currentFrame.at<cv::Vec3b>(i, j)[1] = _background.at<cv::Vec3b>(i, j)[1];
                    currentFrame.at<cv::Vec3b>(i, j)[2] = _background.at<cv::Vec3b>(i, j)[2];
                }
            }
        }

        cv::imshow("c", mask);
        cv::imshow("d", currentFrame);
        cv::imshow("b", _background);
    }
}
