#include <ios>
#include <iostream>
#include <cstring>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

void saveHSVThresholds(const std::string& filename, cv::Scalar lower_red, cv::Scalar upper_red, cv::Scalar lower_blue, cv::Scalar upper_blue, cv::Scalar lower_green, cv::Scalar upper_green);
void callBack(int, void*) ;
void test01();
void test02(cv::VideoCapture cap);
void test03(cv::VideoCapture cap);
void test04(cv::VideoCapture cap);

void test05();