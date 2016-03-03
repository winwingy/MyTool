#pragma once
#include <vector>
#include <algorithm>
using std::vector;
using std::min_element;
inline int absValue( int iTemp )
{	
	return iTemp > 0 ? iTemp:-iTemp; 
}

template<typename T>
class CToolHelp
{
public:

	static bool IsHaveSame(int iTotal, T* aNum)
	{
		for ( int i(0); i < iTotal; i++ )//1 , 2 , 3, 5
		{		
			for ( int j(i+1); j < iTotal; j++ )
			{
				if ( aNum[i] == aNum[j] )
				{
					return true;
				}
			}
		}
		return false;
	};

	static int SameCnt( int iRefer, int iCompareCnt, ... )
	{
		int iReturn(0);
		va_list vags;
		va_start( vags, iCompareCnt );
		for ( int i(0); i< iCompareCnt; i++ )
		{
			int iperCompare = va_arg(vags, int);
			if ( iRefer == iperCompare )
			{
				iReturn++;
			}
		}

		va_end( vags );
		return iReturn;
	}

	static int RectTotalRange( CRect recRefer, int iCompareCnt, ... )
	{
		int iReturn(0);
		va_list vags;
		va_start( vags, iCompareCnt );
		for ( int i(0); i< iCompareCnt; i++ )
		{
			CRect recPerCompare = va_arg(vags, CRect);
			iReturn += absValue(recRefer.left - recPerCompare.left) + absValue( recRefer.top - recPerCompare.top );		
		}
		va_end( vags );
		return iReturn;
	}

	//返回最小的数的下标
	template<typename T>
	static vector<int>  MinValue( int iCnt, T iOne,  ... )
	{		
		va_list vags;
		va_start( vags, iCnt );
		vector<T> vecValue;
		for ( int i(0); i< iCnt; i++ )
		{
			T per = va_arg(vags, T);
			vecValue.push_back(per);		
		}
		va_end( vags );
		vector<T>::iterator iterMin = min_element( vecValue.begin(), vecValue.end() );
		vector<T>::iterator iter = vecValue.begin();
		vector<int> vecRet;
		for ( ; iter != vecValue.end(); iter++ )
		{
			if ( *iter == *iterMin )
			{
				vecRet.push_back(iter - vecValue.begin());
			}
		}
		
		return vecRet;
	}




	CToolHelp(){};
	~CToolHelp(void){};	
};
