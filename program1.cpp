/* 
 * File:   main.cpp
 * Author: Ambrose Guo
 *
 * Created on February 14, 2015, 6:00 PM
 */

#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <cmath>
using namespace cv;
using namespace std;
 
int main(int argc, char** argv) {
  if(argc != 3) {
    cout << argv[0] << ": "
	 << "got " << argc-1 << " arguments. Expecting two: width height." 
	 << endl ;
    return(-1);
  }

  int width = atoi(argv[1]);
  int height = atoi(argv[2]);
  int** RED1 = new int*[height];
  int** GREEN1 = new int*[height];
  int** BLUE1 = new int*[height];
  int** RED2 = new int*[height];
  int** GREEN2 = new int*[height];
  int** BLUE2 = new int*[height];

  for(int i = 0 ; i < height ; i++) {
    RED1[i] = new int[width];
    GREEN1[i] = new int[width];
    BLUE1[i] = new int[width];
    RED2[i] = new int[width];
    GREEN2[i] = new int[width];
    BLUE2[i] = new int[width];
  }
  
  for(int i = 0 ; i < height ; i++)
    for(int j = 0 ; j < width ; j++)
      {
	int r1, g1, b1;
	int r2, g2, b2;

	double x = (double)j/(double)width;
	double y = (double)i/(double)height;
	double Y = 1.0;

	double L = 90;
	double u = x * 512 - 255;
	double v = y * 512 - 255;

/*============Change xyY Representation to xyz========*/
        double X = (x/y)*Y;
        double Z = (1-x-y)*Y/y;
        double M[3][3] = {{3.240479,-1.53715,-0.498535},{-0.969256,1.875991,0.041556},{0.055648,-0.204043,1.057311}};

/*============xyz to linear sRGB=======================*/        
        double linearR = X*M[0][0]+Y*M[0][1]+Z*M[0][2];
        double linearG = X*M[1][0]+Y*M[1][1]+Z*M[1][2];
        double linearB = X*M[2][0]+Y*M[2][1]+Z*M[2][2];
       
/*=============clipping=======================*/        
        if (linearR > 1)
            linearR = 1;
        else if(linearR < 0)
            linearR = 0;
        
        if (linearG > 1)
            linearG = 1;
        else if(linearG < 0)
            linearG = 0;
        
        if (linearB > 1)
            linearB = 1;
        else if(linearB < 0)
            linearB = 0;
        
/*==============linear sRGB to nonLinear sRGB======*/
        if(linearR < 0.00304)
            linearR = 12.92 * linearR;
        else {
       
            linearR = 1.055 * pow(linearR,1.0/2.4) - 0.055;
            }
        r1 = 255 * linearR;
        if(linearG < 0.00304)
            linearG = 12.92 * linearG;
        else {
            
            linearG = 1.055 * pow(linearG,1.0/2.4) - 0.055;
        }
        g1 = 255 * linearG;
        if(linearB < 0.00304)
            linearB = 12.92 * linearB;
        else {
            
            linearB = 1.055 * pow(linearB,1.0/2.4) - 0.055;            
        }
        b1 = 255 * linearB;
/*============Change Luv to sRGB==============================*/
	/* Your code should be placed here
	   It should translate xyY to byte sRGB
	   and Luv to byte sRGB
         */
//First Luv to xyz
        float Xw = 0.95,Yw = 1.0,Zw = 1.09;
        float Uw = 4 * Xw / (Xw + 15 * Yw + 3 * Zw);
        float Vw = 9 * Yw/ (Xw + 15 * Yw + 3 * Zw);
        float uu = ( u + 13 * Uw * L )/ 13 * L;
        float vv = ( v + 13 * Vw * L)/ 13* L;
        
        float y2;
        if(L > 7.9996)
       {
            y2 = pow((L + 16.0)/116.0,3.0) * Yw;
        }
        else
            y2 = L * Yw/903.3;
        float x2,z2;
        if(vv == 0)
        {   
            x2 = 0;
            z2 = 0;
        }
        else
        {
            x2 = y2 * 2.25 * uu / vv;
            z2 = y2 * (3 - 0.75 * uu - 5 * vv)/vv;
        }
        double linearR2 = x2*M[0][0]+y2*M[0][1]+z2*M[0][2];
        double linearG2 = x2*M[1][0]+y2*M[1][1]+z2*M[1][2];
        double linearB2 = x2*M[2][0]+y2*M[2][1]+z2*M[2][2];
/*========================Clipping====================================*/           
        if (linearR2 > 1)
            linearR2 = 1;
        else if(linearR2 < 0)
            linearR2 = 0;
        
        if (linearG2 > 1)
            linearG2 = 1;
        else if(linearG2 < 0)
            linearG2 = 0;
        
        if (linearB2 > 1)
            linearB2 = 1;
        else if(linearB2 < 0)
            linearB2 = 0;
        
/*=====================linear sRGB to nonLinear sRGB=======================*/        
        if(linearR2 < 0.00304)
            linearR2 = 12.92 * linearR2;
        else {
       
            linearR2 = 1.055 * pow(linearR2,1.0/2.4) - 0.055;
            }
        r2 = (int) (255 * linearR2);
        if(linearG2 < 0.00304)
            linearG2 = 12.92 * linearG2;
        else {
            
            linearG2 = 1.055 * pow(linearG2,1.0/2.4) - 0.055;
        }
        g2 = (int) (255 * linearG2);
        if(linearB2 < 0.00304)
            linearB2 = 12.92 * linearB2;
        else {
            
            linearB2 = 1.055 * pow(linearB2,1.0/2.4) - 0.055;            
        }
        b2 = (int)(255 * linearB2);
	

	// this is the end of your code

	RED1[i][j] = r1;
	GREEN1[i][j] = g1;
	BLUE1[i][j] = b1;
	RED2[i][j] = r2;
	GREEN2[i][j] = g2;
	BLUE2[i][j] = b2;
      }
                

  Mat R1(height, width, CV_8UC1);
  Mat G1(height, width, CV_8UC1);
  Mat B1(height, width, CV_8UC1);

  Mat R2(height, width, CV_8UC1);
  Mat G2(height, width, CV_8UC1);
  Mat B2(height, width, CV_8UC1);

  for(int i = 0 ; i < height ; i++)
    for(int j = 0 ; j < width ; j++) {

      R1.at<uchar>(i,j) = RED1[i][j];
      G1.at<uchar>(i,j) = GREEN1[i][j];
      B1.at<uchar>(i,j) = BLUE1[i][j];

      R2.at<uchar>(i,j) = RED2[i][j];
      G2.at<uchar>(i,j) = GREEN2[i][j];
      B2.at<uchar>(i,j) = BLUE2[i][j];
    }

  Mat xyY;
  Mat xyY_planes[] = {B1, G1, R1};
  merge(xyY_planes, 3, xyY);
  namedWindow("xyY",CV_WINDOW_AUTOSIZE);
  imshow("xyY", xyY);

  Mat Luv;
  Mat Luv_planes[] = {B2, G2, R2};
  merge(Luv_planes, 3, Luv);
  namedWindow("Luv",CV_WINDOW_AUTOSIZE);
  imshow("Luv", Luv);
   waitKey(0); // Wait for a keystroke
  return(0);
}
