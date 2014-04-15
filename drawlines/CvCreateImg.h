#include "SolidDef.h"
#include "TEACDef.h"
#include "cv.h"
#include "highgui.h"
#pragma   comment(lib,"cv.lib")  
#pragma   comment(lib,"highgui.lib")
#include "iostream"
#include <fstream>
//CvCreatImg.h ����OpenCV ͨ��ZSlice/ZRing ����ͼ������
/* **************************** */
/* ******Version 1.0*********** */
/* function:*
	2014.3 ����ʵ�ֽ�Slice�е�ring����ṹ����
	2014.4 ʵ�ֵ���޸��������������ķ�λ���ԣ������ڴ�й¶������
		   ���ӽ��㱣��Ĺ���
		   
/* Author:DengSHuo*/
/* data: 14/4/3*/
////
enum ImgResolution {
	__small,
	__medium,
	__large } ;
class CvCreateImg : public  CZArray<CZRing, true>
{
public:
	//construction/destruction
	CvCreateImg();
	~CvCreateImg(void) ;
	//init
	void init(CZSlice p_slice,int CutZ);
	// calculate min&max of the slice
// 	int minX();
// 	int maxX();
// 	int	minY();
// 	int maxY();
	// ratio
	const CSTLCube& cube(void) { return getSolid().cube(); };
	// set Image Resolution
	//void setRes();
	// reset point
	BOOL ResetSlice(CZSlice fixslice);
	// draw
	BOOL Drawlines(void) ;
	void SavePoints(CvPoint **__point,int __row,int *__col, LPCTSTR lpFileName);
	//IplImage * getImg() {return m_img};
	void gDump(ostream &p_os) const;

private:
	CZSlice m_fixslice;
	float m_Xratio, m_Yratio;
	int m_RingNum;
	float m_minX, m_minY ,m_X,m_Y;
	int m_Paint_wid;
	int m_CutZ;
	ImgResolution m_ImgResolution;
	IplImage* m_img;
	CvSize m_cvsize;
	CvPoint **m_pCvPoint;
	int m_PointCounts;

};
