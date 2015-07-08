#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#define THRES 220
#define GRIDSIZE 8
#define DIST 5
#define NEG 10
using namespace std;
using namespace cv;
void outputcolor(int ,int );
struct coord
{
	int x;
	int y;
}pathmap[GRIDSIZE][GRIDSIZE];
Mat grid;
int main()
{
	int breakflag=0,i,j,previ,prevj,m=0,n=0,firsttimeflag=1;
	grid = imread("colorimg.png", CV_LOAD_IMAGE_COLOR);
	Mat img2(grid.rows, grid.cols, CV_8UC3);
	for(i=0;i<grid.rows;i++)
	{
		for(j=0;j<grid.cols;j++)
		{
			img2.at<Vec3b>(i,j)[0]=0;
			img2.at<Vec3b>(i,j)[1]=0;
			img2.at<Vec3b>(i,j)[2]=0;
		}
	}
	for(i=0;i<grid.rows;i++)
	{
		for(j=0;j<grid.cols;j++)
		{
			if((int)grid.at<Vec3b>(i, j)[0]>THRES && (int)grid.at<Vec3b>(i, j)[1]>THRES && (int)grid.at<Vec3b>(i, j)[2]>THRES && (int)grid.at<Vec3b>(i+1, j)[0]>THRES && (int)grid.at<Vec3b>(i+1, j)[1]>THRES && (int)grid.at<Vec3b>(i+1, j)[2]>THRES && (int)grid.at<Vec3b>(i-1, j)[0]>THRES && (int)grid.at<Vec3b>(i-1, j)[1]>THRES && (int)grid.at<Vec3b>(i-1, j)[2]>THRES && (int)grid.at<Vec3b>(i, j+1)[0]>THRES && (int)grid.at<Vec3b>(i, j+1)[1]>THRES && (int)grid.at<Vec3b>(i, j+1)[2]>THRES && (int)grid.at<Vec3b>(i, j-1)[0]>THRES && (int)grid.at<Vec3b>(i, j-1)[1]>THRES && (int)grid.at<Vec3b>(i, j-1)[2]>THRES)
			{
				if(firsttimeflag==1)
				{
					prevj=j;
					previ=i;
					firsttimeflag=0;
				}

				if(i-previ>DIST)
				{
					m++;
				}

				if(j-prevj>DIST)
				{
					n++;
				}

				if(j-prevj<-NEG)
				{
					n=0;
				}
				img2.at<Vec3b>(i,j)[0]=255;
				img2.at<Vec3b>(i,j)[1]=255;
				img2.at<Vec3b>(i,j)[2]=255;
				pathmap[m][GRIDSIZE-n-1].x=i;
				pathmap[m][GRIDSIZE-n-1].y=j;
			/*
				cout<<"pathmap["<<m<<"]["<<n<<"].x is"<<pathmap[m][n].x<<endl;
				cout<<"pathmap["<<m<<"]["<<n<<"].y is"<<pathmap[m][n].y<<endl;
			
			*/
				previ=i;
				prevj=j;
			}
		}
	}
	for(j=0;j<GRIDSIZE;j++)
	{
		for(i=0;i<GRIDSIZE;i++)
		{
			if(i!=GRIDSIZE-1 && j!=GRIDSIZE-1)
			{
				outputcolor((pathmap[j][i].x+pathmap[j+1][i].x)/2,(pathmap[j][i].y+pathmap[j+1][i].y)/2);
				outputcolor((pathmap[j][i].x+pathmap[j][i+1].x)/2,(pathmap[j][i].y+pathmap[j][i+1].y)/2);
			}
			else if(i==GRIDSIZE-1 && j==GRIDSIZE-1)
			{

			}
			else if(j==GRIDSIZE-1)
			{
				outputcolor((pathmap[j][i].x+pathmap[j][i+1].x)/2,(pathmap[j][i].y+pathmap[j][i+1].y)/2);
			}
			else if(i==GRIDSIZE-1)
			{
				outputcolor((pathmap[j][i].x+pathmap[j+1][i].x)/2,(pathmap[j][i].y+pathmap[j+1][i].y)/2);
			}
		}
	}
	/*namedWindow("transform", CV_WINDOW_NORMAL);
	namedWindow("original", CV_WINDOW_NORMAL);*/
	
	/*while (1)
	{
		imshow("original", grid);
		imshow("transform", img2);
		char a=waitKey(33);
		if (a == 27)
			break;
	}*/

	//cout<<l<<endl;
	return 0;
}
void outputcolor(int xcoord,int ycoord)
{
	/*cout<<"x: "<<xcoord<<"y: "<<ycoord<<endl;*/
	if ((int)grid.at<Vec3b>(xcoord,ycoord)[0]>THRES)
		cout<<"20"<<endl;
	else if ((int)grid.at<Vec3b>(xcoord,ycoord)[1]>THRES && (int)grid.at<Vec3b>(xcoord,ycoord)[2]<THRES)
		cout<<"15"<<endl;
	else if ((int)grid.at<Vec3b>(xcoord,ycoord)[2]>THRES && (int)grid.at<Vec3b>(xcoord,ycoord)[1]<THRES)
		cout<<"25"<<endl;
	else if ((int)grid.at<Vec3b>(xcoord,ycoord)[1]>THRES && (int)grid.at<Vec3b>(xcoord,ycoord)[2]>THRES)
		cout<<"10"<<endl;
	else
	{
		cout<<"x: "<<xcoord<<"y: "<<ycoord<<endl;
		cout<<"unknown"<<endl;
	}
}

