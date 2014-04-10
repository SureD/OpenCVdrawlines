// Implement of CvCreatImg
#include "StdAfx.h"
#include "CvCreateImg.h"


CvCreateImg :: CvCreateImg()
{

	m_img = NULL;
	m_pCvPoint = NULL;
	m_PointCounts = 0;
	float _width, _height;
	//float m_midX = cube().w()/2;
	//float m_midY = cube().h()/2;
	_width = cube().w();
	_height = cube().h();
	m_X = _width/2;
	m_Y = _height/2;
	//_wh.height = int(_height/5000);
	//_wh.width = int(_width/5000);
	//m_img = cvCreateImage(_wh,  IPL_DEPTH_8U, 3);
	//cvZero(m_img);
	m_minX = cube().min.x;
	m_minY = cube().min.y;
	m_ImgResolution = __medium;
	switch (m_ImgResolution)
	{
	case __small:
		   {
				
		   }
		break;
	case __medium:
		  {
				m_Xratio = 1280/_width;
				m_Yratio = 720/_height;
				m_cvsize.height =2000;
				m_cvsize.width = 2000;
				m_img = cvCreateImage(m_cvsize,  IPL_DEPTH_8U, 3);
				cvZero(m_img); 
		  }
		break;
	case __large:
		  {

		  }
	}
}
CvCreateImg :: ~CvCreateImg()
{
	cvReleaseImage( &m_img);
	for ( int i=0;i<m_RingNum;i++)
	{
		delete  m_pCvPoint[i];
	}
	delete []  m_pCvPoint;


}

void CvCreateImg ::init(CZSlice p_slice)
{
	CZSlice	m_fixslice = p_slice;
	CZSlice m_slice1=m_fixslice;
	m_RingNum = m_slice1.size();			
	ResetSlice(m_slice1);	
}
BOOL CvCreateImg::ResetSlice(CZSlice m_slice1)
{
		m_pCvPoint = new CvPoint*[m_slice1.size()];
		int *col = new int[m_slice1.size()];
		for(int i=0; i<m_slice1.size(); i++)
			for(int j=0; j<m_slice1[i].size(); j++)
			{
				if (j == 0)
				{
					m_pCvPoint[i] = new CvPoint[m_slice1[i].size()];
					col[i] = m_slice1[i].size();
				}
// 				m_slice1[i][j].x= m_fixslice[i][j].x * m_Xratio;
// 				m_slice1[i][j].y= m_fixslice[i][j].y * -m_Yratio;
// 				__tenx = m_slice1[i][j].x;
// 				__teny = m_slice1[i][j].y;
// 				m_pCvPoint[i][j].x = (int)m_slice1[i][j].x+640;
// 				m_pCvPoint[i][j].y = (int)m_slice1[i][j].y+360;
				m_pCvPoint[i][j].x = (int)(m_slice1[i][j].x+m_X) * m_Xratio+500;
 				m_pCvPoint[i][j].y = (int)(m_slice1[i][j].y+m_Y) * m_Yratio+500;
				m_PointCounts++;
			}
	for (int k=0; k<m_slice1.size();k++)
	{
		int p = m_slice1[k].size();
		cvPolyLine(m_img, &m_pCvPoint[k] , &p, 1 , 1 ,cvScalar(  255 , 255 ,255  ), 2 );
	}
// 		for (i=0;i<m_slice1[0].size()-1;i++)
// 		{		
// // 			if (i==m_slice1[0].size())
// // 					{
// // 						cvLine(m_img,m_pCvPoint[0][i],m_pCvPoint[0][0],cvScalar(  255 , 255 ,0  ));
// // 					}
// 			cvLine(m_img,m_pCvPoint[0][i],m_pCvPoint[0][i+1],cvScalar(  255 , 255 ,0  ));
// 		}
// cvLine(m_img,m_pCvPoint[0][m_slice1[0].size()-1],m_pCvPoint[0][0],cvScalar(  255 , 255 ,0  ));
	
	cvSaveImage("I:\\3Ddata\\a.bmp",m_img);
//	cvSave("point.txt",m_pCvPoint);

	SavePoints(m_pCvPoint, m_slice1.size(),col,"I:\\3Ddata\\points.txt");

	//m_pCvPoint1 =NULL;
	delete [] col;
	return 1;
	
	
	//cvShowImage( "多边形", m_img ); 
}
VOID CvCreateImg::SavePoints(CvPoint **__point,int __row,int* __col,LPCTSTR lpFileName)
{
	CvPoint __tempPoint;
	std::ofstream outfile(lpFileName);
	for(int i=0;i<__row; i++)
	{
		for(int j=0; j<__col[i]; j++)
		{
			if (j==0)
			{
				outfile<<std::endl;
				outfile<<"Ring"<<std::endl;
			}
			__tempPoint=__point[i][j];
			outfile<<__tempPoint.x<<","<<" ";
			outfile<<__tempPoint.y<<";"<<"  ";
			//outfile<<endl;
		}
	}
	outfile<<std::endl<<"Ratio"<<std::endl<<m_Xratio<<","<<m_Yratio<<std::endl;
	outfile<<"最大XY"<<std::endl<<m_X<<","<<m_Y;
}
BOOL CvCreateImg::Drawlines(void) 
{

	return 0;
}