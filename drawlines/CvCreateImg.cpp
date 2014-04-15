// Implement of CvCreatImg
#include "StdAfx.h"
#include "CvCreateImg.h"
//#include "stdio.h"


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
	m_CutZ = 0;
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
				m_Xratio = 500/_width;
				m_Yratio = 500/_height;
//			    m_Xratio = 1;
//				m_Yratio = 1;
				m_cvsize.height = 720;
				m_cvsize.width = 1280;
				m_img = cvCreateImage(m_cvsize,  IPL_DEPTH_8U, 3);
				cvZero(m_img); 
				cvSet(m_img, cvScalar(  255 , 255 ,255  ));
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

void CvCreateImg ::init(CZSlice p_slice,int CutZ)
{
	m_CutZ = CutZ;
	CZSlice	m_fixslice = p_slice;
	CZSlice m_slice1=m_fixslice;
	m_RingNum = m_slice1.size();			
	ResetSlice(m_slice1);	
}
BOOL CvCreateImg::ResetSlice(CZSlice m_slice1)
{
	int k =m_slice1.size();
	m_pCvPoint = new CvPoint*[k];
	int *col = new int[k];
	for(int i=0; i<k; i++)
		for(int j=0; j<m_slice1[i].size(); j++)
			{
				if (j == 0)
				{
					m_pCvPoint[i] = new CvPoint[m_slice1[i].size()];
					col[i] = m_slice1[i].size();
				}
				m_pCvPoint[i][j].x = (int)(m_slice1[i][j].x+m_X) * m_Xratio + 60;
 				m_pCvPoint[i][j].y = (int)(m_slice1[i][j].y+m_Y) * m_Yratio + 25;
				m_PointCounts++;
			}
	for (int ii=0; ii<k;ii++)
		{
			int p = m_slice1[ii].size();
			cvPolyLine(m_img, &m_pCvPoint[ii] , &p, 1 , 1 ,cvScalar(  0 , 0 ,0  ), 2 );
		}
	char _bmpfilename[256] ={0} ;
	sprintf(_bmpfilename,"G:\\3Ddata\\figure\\%d.bmp",m_CutZ);
	//const char __filename[256] = _filename;
	cvSaveImage(_bmpfilename,m_img);
	//cvSaveImage("I:\\3Ddata\\a.bmp",m_img);
	char _txtfilename[256] = {0};
	sprintf(_bmpfilename,"G:\\3Ddata\\txt\\%d.txt",m_CutZ);
	SavePoints(m_pCvPoint, m_slice1.size(),col,_bmpfilename);
	//SavePoints(m_pCvPoint, m_slice1.size(),col,"I:\\3Ddata\\points.txt");

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
				outfile<<"Ring:"<<std::endl;
			}
			__tempPoint=__point[i][j];
			outfile<<__tempPoint.x<<","<<" ";
			outfile<<__tempPoint.y<<";"<<"  ";
			//outfile<<endl;
		}
	}
	outfile<<std::endl<<"Ratio:"<<std::endl<<"X缩放率: "<<m_Xratio<<","<<"Y缩放率: "<<m_Yratio<<std::endl;
	outfile<<"最大XY: "<<std::endl<<"X: "<<m_X<<","<<"Y: "<<m_Y<<std::endl;
	outfile<<"切割深度: "<<std::endl<<m_CutZ;
}
BOOL CvCreateImg::Drawlines(void) 
{

	return 0;
}
void CvCreateImg::gDump(ostream &p_os) const
{
	for (int i = 0 ; i<m_fixslice.size(); i++)
	{
		m_fixslice[i].gDump(p_os);
	}
}