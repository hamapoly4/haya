#include <opencv/opencv.hpp>

int main(){
	cv::Mat img;
	
	cv::VideoCapture cap(0);
	
	while(true){
		
		cap.read(img);
		
		cv::imshow("VideoCapture",img);
		
		unsined char key = cv::waitKey(2);
		if(key == '\x1b') break;
		
	}
	
	return 0;
	
}
