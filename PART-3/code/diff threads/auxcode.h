#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <pthread.h>

using namespace cv;
using namespace std;
using namespace std::chrono;




Mat colourtransformframe(Mat &image, vector<Point2f>& source, vector<Point2f>& desti, vector<Point2f>& rec) {
	Mat finalimage;
	Mat projectedimage;
	Mat blackimage;
	//image is read in colour
	cvtColor(image, blackimage, COLOR_BGR2GRAY);
	Mat homo = findHomography(source, desti);
	warpPerspective(blackimage, projectedimage, homo, image.size());
	Rect crop_region(rec[0].x, rec[0].y, abs(rec[1].x - rec[0].x), abs(rec[1].y - rec[0].y));
	finalimage = projectedimage(crop_region);
	return finalimage;
}


double queuedensity(Mat &im1,Mat &im2, vector<Point2f>& source, vector<Point2f>& desti, vector<Point2f>& rec) {
	Mat image= colourtransformframe(im1, source, desti, rec);
	Mat image2= colourtransformframe(im2, source, desti, rec);

	int total = 0;
	int whites = 0;
	for (int y = 0; y <image.size().height; y++) {
		for (int x= 0; x<image.size().width; x++) {
			total += 1;
			if (abs(image.at<uchar>(y, x)-image2.at<uchar>(y,x))>30) {
				whites += 1;
			}
		}
	}
	double r = (whites+0.0) / (total+0.0);
	return r;

}


/*double dynamicdensity(Mat &im1,Mat &im2,vector<Point2f>& source, vector<Point2f>& desti, vector<Point2f>& rec) {
	Mat image= colourtransformframe(im1, source, desti, rec);
	Mat image2= colourtransformframe(im2, source, desti, rec);

	int total = 0;
	int vary = 0;
	for (int y = 0; y < image.size().height; y++) {
		for (int x = 0; x < image.size().width; x++) {
			total += 1;
			if (abs(image.at<uchar>(y, x)-image2.at<uchar>(y,x))>5) {
				vary += 1;
			}
		}
	}
	double r = (vary + 0.0) / (total + 0.0);
	return r;

}

double queuedensityresochange(int X,int Y,Mat &im1,Mat &im2, vector<Point2f>& source, vector<Point2f>& desti, vector<Point2f>& rec) {
	Mat imagem= colourtransformframe(im1, source, desti, rec);
	Mat image2m= colourtransformframe(im2, source, desti, rec);
	Size dsz=Size(X,Y);
	Mat image;
	Mat image2;

	resize(imagem,image,dsz,0,0,INTER_LINEAR);
	resize(image2m,image2,dsz,0,0,INTER_LINEAR);

	int total = 0;
	int whites = 0;
	for (int y = 0; y <image.size().height; y++) {
		for (int x= 0; x<image.size().width; x++) {
			total += 1;
			if (abs(image.at<uchar>(y, x)-image2.at<uchar>(y,x))>30) {
				whites += 1;
			}
		}
	}
	double r = (whites+0.0) / (total+0.0);
	return r;

}*/

//void resol(vector<pair<int,double>> &r,int X,int Y,Mat &emptyframe,VideoCapture cap,vector<Point2f>& source, vector<Point2f>& desti, vector<Point2f>& rec) {
	
        

      

        
	

//}