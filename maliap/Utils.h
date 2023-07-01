#pragma once
#include <windows.h>
#include "GameVoice.h"
#include<io.h>
#include <vector>
#include<iostream>
#include <string>
using namespace std;

namespace Utils {
    const float EQS = 1e-6;
    struct Rect
    {
        float posx, posy;
        float width, height;        // Point 2
    };

    inline bool CrossLine(Rect r1, Rect r2)
    {

        float w = abs(r1.posx + r1.width / 2 - r2.posx - r2.width / 2);
        float h = abs(r1.posy + r1.height / 2 - r2.posy - r2.height / 2);

        if (w < (r1.width + r2.width) / 2 && h < (r1.height + r2.height) / 2)
            return true;
        else
            return false;
    }

    // 字符转换
    inline void Wchar_tToString(std::string& szDst, const wchar_t* wText)
    {
        DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);//WideCharToMultiByte的运用
        char* psText;  // psText为char*的临时数组，作为赋值给std::string的中间变量
        psText = new char[dwNum];
        WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);//WideCharToMultiByte的再次运用
        szDst = psText;// std::string赋值
        delete[]psText;// psText的清除
    }

    //不要忘记在使用完wchar_t*后delete[]释放内存
    inline wchar_t* multiByteToWideChar(const string& pKey)
    {
        auto pCStrKey = pKey.c_str();
        //第一次调用返回转换后的字符串长度，用于确认为wchar_t*开辟多大的内存空间
        int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
        wchar_t* pWCStrKey = new wchar_t[pSize];
        //第二次调用将单字节字符串转换成双字节字符串
        MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
        return pWCStrKey;
    }

    inline vector<string> FindAllLevel(string path)
    {

        vector<string> rev;
        _finddata64i32_t fileInfo;
        intptr_t hFile = _findfirst((path + "/*.*").c_str(), &fileInfo);
        do
        {
            string check = fileInfo.name;
            int index=check.find(".xlsx");
            if (index < check.length())
            {
                rev.push_back(check.substr(0, index));
                cout << check.substr(0, index) << endl;
            }

        } while (_findnext(hFile, &fileInfo) == 0);
        //关闭文件句柄  
        _findclose(hFile);
        return rev;
    }

}