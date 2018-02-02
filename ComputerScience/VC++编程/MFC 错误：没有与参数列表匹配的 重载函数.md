# MFC 错误：没有与参数列表匹配的 重载函数

转载自[MFC 错误：没有与参数列表匹配的 重载函数](http://blog.csdn.net/xiaopang1122/article/details/53813956)



CString str;

str.Format("Fuck %d",count);//这句话报错

m_static.SetWindowTextW(str):


错误是： 2 IntelliSense: 没有与参数列表匹配的 重载函数 "ATL::CStringT<BaseType, StringTraits>::Format [其中 BaseType=wchar_t, StringTraits=StrTraitMFC<wchar_t, ATL::ChTraitsCRT<wchar_t>>]" 实例

            参数类型为: (const char [8], int)
            对象类型是: CString g:\C++\Static\Static\StaticDlg.cpp 99 5 Static
解决方案：
str.Format(_T("Fuck %d"),count);或str.Format(L"Fuck %d",count);
解释:

注意字符（串）有两种类型，char(*)和wchar_t(*)型，分别用于多字节字符和unicode字符，两种类型分别有一套对应的字符串处理函数（包括C/C++标准库，WindowsAPI，MFC等）。MFC的类和函数会根据工程设置（默认为wchar_t）自动匹配，因此这时Format要求的字符串参数为wchar_t*，所以要在字符串前加上“L”表示是wchar_t型字符串，或者加上_T()，_T同样会根据工程设置自动匹配char或wchar_t。

下面一句也建议写成m_static.SetWindowText(str):（去掉W），SetWindowText其实也有两个函数SetWindowTextA（用于char）和SetWindowTextW（用于wchar_t），而SetWindowText本身会根据工程设置自动匹配使用A或W