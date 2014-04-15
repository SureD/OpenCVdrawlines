#include "SolidDef.h"
#include "TEACDef.h"
#include "cv.h"
#include "highgui.h"
#pragma   comment(lib,"cv.lib")  
#pragma   comment(lib,"highgui.lib")
#include "iostream"
#include <fstream>
//CvCreatImg.h 利用OpenCV 通过ZSlice/ZRing 产生图像数据
/* **************************** */
/* ******Version 1.0*********** */
/* function:*
	2014.3 初步实现将Slice中的ring导入结构体中
	2014.4 实现点的修改与调整，但坐标的方位不对，存在内存泄露的问题
		   增加将点保存的功能
		   
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
