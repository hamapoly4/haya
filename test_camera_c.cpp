#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::VideoCapture cap(0); // カメラデバイスID (0はデフォルトカメラ)

    if (!cap.isOpened()) {
        std::cerr << "カメラが開けません。" << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true) {
        cap >> frame; // フレームを取得

        if (frame.empty()) break;

        cv::imshow("カメラ映像", frame);

        if (cv::waitKey(10) == 27) break; // 'ESC'キーで終了
    }

    return 0;
}
