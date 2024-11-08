#include "rap.h"

cv::Mat frame, hsv, redMask, blueMask, greenMask;
// 初始化HSV范围
cv::Scalar lower_red(0, 75, 75), upper_red(12, 255, 255);
cv::Scalar lower_blue(100, 43, 46), upper_blue(130, 255, 255);
cv::Scalar lower_green(45, 40, 40), upper_green(90, 255, 255);
cv::Scalar global_lower_red=lower_red, global_upper_red=upper_red;
cv::Scalar global_lower_blue=lower_blue, global_upper_blue=upper_blue;
cv::Scalar global_lower_green=lower_green, global_upper_green=upper_green;




void saveHSVThresholds(const std::string& filename, cv::Scalar lower_red, cv::Scalar upper_red, cv::Scalar lower_blue, cv::Scalar upper_blue, cv::Scalar lower_green, cv::Scalar upper_green) {
    std::ofstream file(filename, std::ios::out);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for writing." <<std::endl;
        return;
    }
    file << lower_red[0] << " " << lower_red[1] << " " << lower_red[2] << std::endl;
    file << upper_red[0] << " " << upper_red[1] << " " << upper_red[2] << std::endl;
    file << lower_blue[0] << " " << lower_blue[1] << " " << lower_blue[2] << std::endl;
    file << upper_blue[0] << " " << upper_blue[1] << " " << upper_blue[2] << std::endl;
    file << lower_green[0] << " " << lower_green[1] << " " << lower_green[2] << std::endl;
    file << upper_green[0] << " " << upper_green[1] << " " << upper_green[2] << std::endl;
    file.close();
}


// 滑动条回调函数
void callBack(int, void*) 
{
   global_lower_red[0] = cv::getTrackbarPos("R Hue Min", "Red HSV调节");
    global_lower_red[1] = cv::getTrackbarPos("R Sat Min", "Red HSV调节");
    global_lower_red[2] = cv::getTrackbarPos("R Val Min", "Red HSV调节");
    global_upper_red[0] = cv::getTrackbarPos("R Hue Max", "Red HSV调节");
    global_upper_red[1] = cv::getTrackbarPos("R Sat Max", "Red HSV调节");
    global_upper_red[2] = cv::getTrackbarPos("R Val Max", "Red HSV调节");
    global_lower_blue[0] = cv::getTrackbarPos("B Hue Min", "Blue HSV调节");
    global_lower_blue[1] = cv::getTrackbarPos("B Sat Min", "Blue HSV调节");
    global_lower_blue[2] = cv::getTrackbarPos("B Val Min", "Blue HSV调节");
    global_upper_blue[0] = cv::getTrackbarPos("B Hue Max", "Blue HSV调节");
    global_upper_blue[1] = cv::getTrackbarPos("B Sat Max", "Blue HSV调节");
    global_upper_blue[2] = cv::getTrackbarPos("B Val Max", "Blue HSV调节");
    global_lower_green[0] = cv::getTrackbarPos("G Hue Min", "Green HSV调节");
    global_lower_green[1] = cv::getTrackbarPos("G Sat Min", "Green HSV调节");
    global_lower_green[2] = cv::getTrackbarPos("G Val Min", "Green HSV调节");
    global_upper_green[0] = cv::getTrackbarPos("G Hue Max", "Green HSV调节");
    global_upper_green[1] = cv::getTrackbarPos("G Sat Max", "Green HSV调节");
    global_upper_green[2] = cv::getTrackbarPos("G Val Max", "Green HSV调节");
    saveHSVThresholds("/home/dzy/Desktop/123/hsv_thresholds.txt", global_lower_red, global_upper_red, global_lower_blue, global_upper_blue, global_lower_green, global_upper_green);
}


void test01()
{
    // 创建窗口
    cv::namedWindow("Red Object Detection");
    cv::namedWindow("Red HSV调节");
    cv::namedWindow("Blue Object Detection");
    cv::namedWindow("Blue HSV调节");
    cv::namedWindow("Green Object Detection");
    cv::namedWindow("Green HSV调节");

    // 创建滑动条
    cv::createTrackbar("R Hue Min", "Red HSV调节", NULL, 255, callBack);
    cv::createTrackbar("R Hue Max", "Red HSV调节", NULL, 255, callBack);
    cv::createTrackbar("R Sat Min", "Red HSV调节", NULL, 255, callBack);
   cv:: createTrackbar("R Sat Max", "Red HSV调节", NULL, 255, callBack);
    cv::createTrackbar("R Val Min", "Red HSV调节", NULL, 255, callBack);
    cv::createTrackbar("R Val Max", "Red HSV调节", NULL, 255, callBack);

    cv::createTrackbar("B Hue Min", "Blue HSV调节", NULL, 255, callBack);
    cv::createTrackbar("B Hue Max", "Blue HSV调节", NULL, 255, callBack);
    cv::createTrackbar("B Sat Min", "Blue HSV调节", NULL, 255, callBack);
    cv::createTrackbar("B Sat Max", "Blue HSV调节", NULL, 255, callBack);
    cv::createTrackbar("B Val Min", "Blue HSV调节", NULL, 255, callBack);
    cv::createTrackbar("B Val Max", "Blue HSV调节", NULL, 255, callBack);

    cv::createTrackbar("G Hue Min", "Green HSV调节", NULL, 255, callBack);
    cv::createTrackbar("G Hue Max", "Green HSV调节", NULL, 255, callBack);
    cv::createTrackbar("G Sat Min", "Green HSV调节", NULL, 255, callBack);
    cv::createTrackbar("G Sat Max", "Green HSV调节", NULL, 255, callBack);
    cv::createTrackbar("G Val Min", "Green HSV调节", NULL, 255, callBack);
    cv::createTrackbar("G Val Max", "Green HSV调节", NULL, 255, callBack);

// 设置滑动条的初始位置
    cv::setTrackbarPos("R Hue Min", "Red HSV调节", lower_red[0]);
    cv::setTrackbarPos("R Sat Min", "Red HSV调节", lower_red[1]);
    cv::setTrackbarPos("R Val Min", "Red HSV调节", lower_red[2]);
    cv::setTrackbarPos("B Hue Min", "Blue HSV调节", lower_blue[0]);
    cv::setTrackbarPos("B Sat Min", "Blue HSV调节", lower_blue[1]);
    cv::setTrackbarPos("B Val Min", "Blue HSV调节", lower_blue[2]);
    cv::setTrackbarPos("G Hue Min", "Green HSV调节", lower_green[0]);
    cv::setTrackbarPos("G Sat Min", "Green HSV调节", lower_green[1]);
    cv::setTrackbarPos("G Val Min", "Green HSV调节", lower_green[2]);
    cv::setTrackbarPos("R Hue Max", "Red HSV调节", upper_red[0]);
    cv::setTrackbarPos("R Sat Max", "Red HSV调节", upper_red[1]);
   cv:: setTrackbarPos("R Val Max", "Red HSV调节", upper_red[2]);
    cv::setTrackbarPos("B Hue Max", "Blue HSV调节", upper_blue[0]);
    cv::setTrackbarPos("B Sat Max", "Blue HSV调节", upper_blue[1]);
    cv::setTrackbarPos("B Val Max", "Blue HSV调节", upper_blue[2]);
    cv::setTrackbarPos("G Hue Max", "Green HSV调节", upper_green[0]);
    cv::setTrackbarPos("G Sat Max", "Green HSV调节", upper_green[1]);
    cv::setTrackbarPos("G Val Max", "Green HSV调节", upper_green[2]);
    
}

void test02(cv::VideoCapture cap)
{
      while (true) {
       cap >> frame;
        if (frame.empty()) {
            break;
        }
        cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        // 红色对象检测
        int r_h_min = cv::getTrackbarPos("R Hue Min", "Red HSV调节");
        int r_h_max = cv::getTrackbarPos("R Hue Max", "Red HSV调节");
        int r_s_min = cv::getTrackbarPos("R Sat Min", "Red HSV调节");
        int r_s_max = cv::getTrackbarPos("R Sat Max", "Red HSV调节");
        int r_v_min = cv::getTrackbarPos("R Val Min", "Red HSV调节");
        int r_v_max = cv::getTrackbarPos("R Val Max", "Red HSV调节");
        inRange(hsv, cv::Scalar(r_h_min, r_s_min, r_v_min), cv::Scalar(r_h_max, r_s_max, r_v_max), redMask);
        imshow("r",redMask);
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
        morphologyEx(redMask, redMask, cv::MORPH_OPEN, kernel);
        morphologyEx(redMask, redMask, cv::MORPH_CLOSE, kernel);
        Canny(redMask, redMask, 100, 200);
        std::vector<std::vector<cv::Point>> contours;
        findContours(redMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        for (size_t i = 0; i < contours.size(); i++) {
            cv::RotatedRect minRect = cv::minAreaRect(contours[i]);
            cv::Point2f vertices[4];
            minRect.points(vertices);
            for (int j = 0; j < 4; j++) {
                line(frame, vertices[j], vertices[(j + 1) % 4], cv::Scalar(0, 0, 255), 2, 8, 0);
            }
        }
        // 程序退出前保存当前滑动条的位置
    imshow("Red Object Detection",frame);
        if (cv::waitKey(30) == 'q') break;
    }
}

void test03(cv::VideoCapture cap)
{
     while (true) {
       cap >> frame;
        if (frame.empty()) {
            break;
        }
        cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        // 蓝色对象检测
        int b_h_min = cv::getTrackbarPos("B Hue Min", "Blue HSV调节");
        int b_h_max = cv::getTrackbarPos("B Hue Max", "Blue HSV调节");
        int b_s_min = cv::getTrackbarPos("B Sat Min", "Blue HSV调节");
        int b_s_max = cv::getTrackbarPos("B Sat Max", "Blue HSV调节");
        int b_v_min = cv::getTrackbarPos("B Val Min", "Blue HSV调节");
        int b_v_max = cv::getTrackbarPos("B Val Max", "Blue HSV调节");
        inRange(hsv, cv::Scalar(b_h_min, b_s_min, b_v_min), cv::Scalar(b_h_max, b_s_max, b_v_max), blueMask);
        imshow("b",blueMask);
       cv:: Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
        morphologyEx(blueMask, blueMask, cv::MORPH_OPEN, kernel);
        morphologyEx(blueMask, blueMask, cv::MORPH_CLOSE, kernel);
        Canny(blueMask, blueMask, 100, 200);
        std::vector<std::vector<cv::Point>> contours;
        findContours(blueMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        for (size_t i = 0; i < contours.size(); i++) {
            cv::RotatedRect minRect = minAreaRect(contours[i]);
            cv::Point2f vertices[4];
            minRect.points(vertices);
            for (int j = 0; j < 4; j++) {
                line(frame, vertices[j], vertices[(j + 1) % 4], cv::Scalar(255, 0, 0), 2, 8, 0);
            }
        }
        // 程序退出前保存当前滑动条的位置
    imshow("Blue Object Detection",frame);
        if (cv::waitKey(30) == 'q') break;
    }
}


void test04(cv::VideoCapture cap)
{
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }
        cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        // 绿色对象检测
        int g_h_min = cv::getTrackbarPos("G Hue Min", "Green HSV调节");
        int g_h_max = cv::getTrackbarPos("G Hue Max", "Green HSV调节");
        int g_s_min = cv::getTrackbarPos("G Sat Min", "Green HSV调节");
        int g_s_max = cv::getTrackbarPos("G Sat Max", "Green HSV调节");
        int g_v_min = cv::getTrackbarPos("G Val Min", "Green HSV调节");
        int g_v_max = cv::getTrackbarPos("G Val Max", "Green HSV调节");
        inRange(hsv, cv::Scalar(g_h_min, g_s_min, g_v_min), cv::Scalar(g_h_max, g_s_max, g_v_max), greenMask);
        imshow("g",greenMask);
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
        morphologyEx(greenMask, greenMask, cv::MORPH_OPEN, kernel);
        morphologyEx(greenMask, greenMask, cv::MORPH_CLOSE, kernel);
        Canny(greenMask, greenMask, 100, 200);
        std::vector<std::vector<cv::Point>> contours;
        findContours(greenMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        for (size_t i = 0; i < contours.size(); i++) {
            cv::RotatedRect minRect = minAreaRect(contours[i]);
            cv::Point2f vertices[4];
            minRect.points(vertices);
             for (int j = 0; j < 4; j++) {
                line(frame, vertices[j], vertices[(j + 1) % 4], cv::Scalar(255, 0, 0), 2, 8, 0);
            }
            
}

imshow("Green Object Detection", frame);
if (cv::waitKey(30) == 'q') break;

    }
}



void test05()
{
    // 程序退出前保存当前滑动条的位置
    saveHSVThresholds("/home/dzy/Desktop/123/hsv_thresholds.txt", global_lower_red, global_upper_red, global_lower_blue, global_upper_blue, global_lower_green, global_upper_green);

}