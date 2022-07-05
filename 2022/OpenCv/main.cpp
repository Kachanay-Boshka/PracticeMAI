#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace cv;
using namespace std;



void findContrastingColor (Mat image, vector <vector<Point>> &contours){
	Mat hsv;
	Scalar blueMin = Scalar(95, 187, 93);
	Scalar blueMax = Scalar(125, 252, 255);
	Scalar redMin = Scalar(112,141,111);
	Scalar redMax = Scalar(214,222,240);
	Scalar greenMin = Scalar(64,172,23);
	Scalar greenMax = Scalar(91,255,255);
	ofstream fout ("data.txt");
	cvtColor(image, hsv, COLOR_BGR2HSV);
	medianBlur(hsv,hsv,13); 
	Mat clone_source(image.size(), CV_8U);
	 //detect blue
	inRange(hsv, blueMin, blueMax, clone_source);
	imshow("Blue", clone_source);
	findContours(clone_source, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	for(int i = 0; i < contours.size(); i++){
		Rect rect = boundingRect(contours[i]);
		Point pt1, pt2;
		pt1.x = rect.x;
		pt1.y = rect.y;
		pt2.x = rect.x + rect.width;
		pt2.y = rect.y + rect.height;
		if (rect.width >= 50 && rect.width <=500 && rect.height >= 10 && rect.height <=500){
		rectangle(image, pt1, pt2, CV_RGB(255,0,0), 1);
		pt1.x = rect.x + rect.width/2;
		pt1.y = rect.y + rect.height/2;
		rectangle(image, pt1, pt1, CV_RGB(0,255,0), 5);
		fout << "Blue object coordinates  = " << pt1 ;
		}
	}
	
	//detect red
	inRange(hsv, redMin, redMax, clone_source);
	imshow("Red", clone_source);
	findContours(clone_source, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	for(int i = 0; i < contours.size(); i++){
		Rect rect = boundingRect(contours[i]);
		Point pt1, pt2;
		pt1.x = rect.x;
		pt1.y = rect.y;
		pt2.x = rect.x + rect.width;
		pt2.y = rect.y + rect.height;
		if (rect.width >= 50 && rect.width <=500 && rect.height >= 10 && rect.height <=500){
		rectangle(image, pt1, pt2, CV_RGB(255,0,0), 1);
		pt1.x = rect.x + rect.width/2;
		pt1.y = rect.y + rect.height/2;
		rectangle(image, pt1, pt1, CV_RGB(0,255,0), 5);
		fout << endl << "Red object coordinates  = " << pt1;
		}
	}

	//detect green
	inRange(hsv, greenMin, greenMax, clone_source);
	imshow("Green", clone_source);
	findContours(clone_source, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	for(int i = 0; i < contours.size(); i++){
		Rect rect = boundingRect(contours[i]);
		Point pt1, pt2;
		pt1.x = rect.x;
		pt1.y = rect.y;
		pt2.x = rect.x + rect.width;
		pt2.y = rect.y + rect.height;
		if (rect.width >= 50 && rect.width <=500 && rect.height >= 10 && rect.height <=500){
		rectangle(image, pt1, pt2, CV_RGB(255,0,0), 1);
		pt1.x = rect.x + rect.width/2;
		pt1.y = rect.y + rect.height/2;
		rectangle(image, pt1, pt1, CV_RGB(0,255,0), 5);
		fout << endl << "Green object coordinates  = " << pt1;
		}
	}

};


int run() {
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cout << "No camera" << endl;
		return EXIT_FAILURE;
	}
	Mat source;
	namedWindow("source");
	vector <vector<Point>> contours;
	//Scalar blueMin = Scalar(95, 187, 93);
	//Scalar blueMax = Scalar(125, 252, 255);

	while (1) {
		cap >> source;
		findContrastingColor(source, contours);
		if (waitKey(33) == 27) break;
		imshow("source", source);
	};
	return 0;
};

int main(){
	run();
	return 0;
}
