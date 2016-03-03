// DivideStringEx.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
void DivideStringBySymbol(const string& strIn, const vector<string>& vecSymbol,	vector<string>& vecHasDivide)
{	
	vector<int> vecDivideIndex;			//分割符的下标
	vector<int>::iterator itrDivideIndex;

	vector<string>::const_iterator itrSymbol;	
	int iTempIndex;	

	//;,asfdsafsasd;,adfasdf;ree
	for ( itrSymbol = vecSymbol.begin(); itrSymbol != vecSymbol.end(); itrSymbol++ )//先找第一个符号的下标
	{
		int iFindIndex(0);
		do 
		{
			iTempIndex = strIn.find(*itrSymbol, iFindIndex);
			if ( iTempIndex != string::npos )
			{				
				vecDivideIndex.push_back(iTempIndex);
				iFindIndex = iTempIndex + itrSymbol->size();									
			}
			else
			{
				break;
			}
		} while (1);
	}

	if ( vecDivideIndex.size() > 0 )
	{
		vecDivideIndex.push_back(strIn.size());
		//排序并除重
		sort(vecDivideIndex.begin(), vecDivideIndex.end());
		vector<int>::iterator itNewEnd = unique(vecDivideIndex.begin(), vecDivideIndex.end());//unique只是将不重的放到前面，后面的不管
		vecDivideIndex.erase( itNewEnd, vecDivideIndex.end() );//所以必须删除后面的
		int iIndexDivide(0);
		for ( int i(0); i <= vecDivideIndex.size(); i++ )
		{
			string strHasDivide( strIn, iIndexDivide, vecDivideIndex[i] - iIndexDivide );
			if ( strHasDivide.size() > 0 && strHasDivide != "" && strHasDivide != " " && strHasDivide != "  ")
			{
				bool bIsSameSymbol(false);
				for ( itrSymbol = vecSymbol.begin(); itrSymbol != vecSymbol.end(); itrSymbol++ )
				{
					if ( strHasDivide == *itrSymbol )
					{
						bIsSameSymbol = true;
						break;
					}

				}
				if ( bIsSameSymbol == false  )
				{
					vecHasDivide.push_back(strHasDivide);
				}
			}
			//看分隔符的下标长度

			for ( itrSymbol = vecSymbol.begin(); itrSymbol != vecSymbol.end(); itrSymbol++ )
			{
				int iSymbolIndex = strIn.find(*itrSymbol,  vecDivideIndex[i]);
				if ( iSymbolIndex == vecDivideIndex[i] )
				{
					iIndexDivide = vecDivideIndex[i] + itrSymbol->size();
				}
			}

			if ( iIndexDivide >= strIn.size() )
			{
				break;
			}
		}		
	}
	if ( vecHasDivide.size() == 0 )
	{
		vecHasDivide.push_back(strIn);
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	string strSrc = "***aaaa|dfadsfdas*fafdasd*&2f&";
	vector<string> vecDivideUse;
	vecDivideUse.push_back("|");
	vecDivideUse.push_back("*");
	vecDivideUse.push_back("&");
	vector<string> vecOut;
	DivideStringBySymbol(strSrc, vecDivideUse,  vecOut);
	for ( vector<string>::iterator it = vecOut.begin(); it != vecOut.end(); ++it )
	{
		printf("%s\n", it->c_str());
	}
	system("pause");
	return 0;
}

