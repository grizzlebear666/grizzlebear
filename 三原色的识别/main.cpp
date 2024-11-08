#include <rap.h>
using namespace cv;
using namespace std;
#include <opencv2/opencv.hpp>
#include <iostream>




int main() {
    
    VideoCapture cap(0); // 0代表默认摄像头
    if (!cap.isOpened()) {
        cout << "Error: Unable to open the camera or video file." << endl;
        return -1;
    }
 test01();
 test02(cap);
 test03(cap);
 test04(cap);
 test05();

cap.release();
destroyAllWindows();
return 0;
}
