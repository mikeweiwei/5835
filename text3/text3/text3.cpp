// text3.cpp : �������̨Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cv.h>

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

/// ��������
void thresh_callback(int, void* );

/** @������ */
int main( int argc, char** argv )
{
			  //����IplImageָ��  
			IplImage* pFrame = NULL;   
			IplImage* pFrImg = NULL;  
			IplImage* pBkImg = NULL;  
			CvMat* pFrameMat = NULL;  
			CvMat* pFrMat = NULL;  
			CvMat* pBkMat = NULL;  
			CvCapture* pCapture = NULL;  
			int nFrmNum = 0;  
			//��������  
			cvNamedWindow("video", 1);  
			cvNamedWindow("background",1);  
			cvNamedWindow("foreground",1);  
			//ʹ������������  
			cvMoveWindow("video", 30, 0);  
			cvMoveWindow("background", 360, 0);  
			cvMoveWindow("foreground", 690, 0);  
			pCapture = cvCaptureFromAVI("a.mp4");   //����������Ƶ�ô˾�  
//pCapture = cvCaptureFromCAM(0);           //������ͷ������Ƶ�ô�  
while(pFrame = cvQueryFrame( pCapture ))  
{  
		nFrmNum++;  
		//����ǵ�һ֡����Ҫ�����ڴ棬����ʼ��  
		if(nFrmNum == 1)  
		{  
					pBkImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),IPL_DEPTH_8U,1);  
					pFrImg = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U,1);  
			pBkMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);  
			pFrMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);  
			pFrameMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);  
			//ת���ɵ�ͨ��ͼ���ٴ���  
			cvCvtColor(pFrame, pBkImg, CV_BGR2GRAY);  
			cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);  
			cvConvert(pFrImg, pFrameMat);  
			cvConvert(pFrImg, pFrMat);  
			cvConvert(pFrImg, pBkMat);  
		}  
    else  
    {  
			cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);  
			cvConvert(pFrImg, pFrameMat);  
			//������˹�˲�����ƽ��ͼ��  
			cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);  
			//��ǰ֡������ͼ���  
			cvAbsDiff(pFrameMat, pBkMat, pFrMat);  
			//��ֵ��ǰ��ͼ  
			cvThreshold(pFrMat, pFrImg, 10, 255.0, CV_THRESH_BINARY);  
			//���±���  
			cvRunningAvg(pFrameMat, pBkMat, 0.003, 0);  
			//������ת��Ϊͼ���ʽ��������ʾ  
			cvConvert(pBkMat, pBkImg);  
			pFrame->origin = IPL_ORIGIN_BL;  
			pFrImg->origin = IPL_ORIGIN_BL;  
			pBkImg->origin = IPL_ORIGIN_BL;  
			cvShowImage("video", pFrame);  
			cvShowImage("background", pBkImg);  
			cvShowImage("foreground", pFrImg);  
			//����а����¼���������ѭ��  
			//�˵ȴ�ҲΪcvShowImage�����ṩʱ�������ʾ  
			//�ȴ�ʱ����Ը���CPU�ٶȵ���  
			if( cvWaitKey(2) >= 0 )  
				break;  
    }  
}  
//���ٴ���  
			cvDestroyWindow("video");  
			cvDestroyWindow("background");  
			cvDestroyWindow("foreground");  
			//�ͷ�ͼ��;���  
			cvReleaseImage(&pFrImg);  
			cvReleaseImage(&pBkImg);  
			cvReleaseMat(&pFrameMat);  
			cvReleaseMat(&pFrMat);  
			cvReleaseMat(&pBkMat);  
			cvReleaseCapture(&pCapture); 
}
