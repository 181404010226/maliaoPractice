#include "SceneConfig.h"
#include "Player.h"
#include "Bat.h"
#include "coin.h"
#include "ghost.h"
#include "zombie.h"

using namespace libxl;

Sceneconfig::Sceneconfig()
{
}

Sceneconfig* Sceneconfig::GetInstance()
{
	// 饿汉式
	static Sceneconfig m_Instance;
	return &m_Instance;
}


void Sceneconfig::LoadLevel(const wchar_t* fileName)
{
    Book* book = xlCreateXMLBook();
    if (book)
    {
        if (book->load(fileName))
        {
            levelSheet = book->getSheet(0);
        }
        else
        {
            std::cout << "不存在如下路径:" << fileName << std::endl;
        }
    }
    // 预加载列
    for (int i= 0; i < 20; i++) LoadObjects(i);
}

void Sceneconfig::LoadObjects(int column)
{
    if (!levelSheet) cout << "错误!应该先加载表格" << endl;
    for (int i = 0; i < 15; i++)
    {
        const wchar_t* s =levelSheet->readStr(i,column);
        if (s)
        {
            string check;
            Utils::Wchar_tToString(check, s);
            float edge = CellWidth;
            if (check == "地")
            {
                CreateObject<testCube>(Utils::Rect{ (float)column * edge,(float)i * edge,edge-5,edge });
            }
            else if (check == "草")
            {
                CreateObject<Grass>(Utils::Rect{ (float)column * edge,(float)i * edge + 24,edge,36 });
            }
            else if (check == "树")
            {
                CreateObject<Tree>(Utils::Rect{ (float)column * edge,(float)i * edge - 9,edge,69 });
            }
            else if (check == "屋")
            {
                CreateObject<House>(Utils::Rect{ (float)column * edge,(float)i * edge - 13,edge,73 });
            }
            else if (check == "世界地图")
            {
                CreateObject<Wmap>(Utils::Rect{ (float)column * edge,(float)i * edge,360,288 });
            }
            else if (check == "云")
            {
                CreateObject<Cloud>(Utils::Rect{ (float)column * edge,(float)i * edge+24,60,36 });
            }
            else if (check == "主角")
            {
                CreateObject<Player>(Utils::Rect{ (float)column * edge,(float)i* edge,50,58 });
            }
            else if (check == "蝙蝠")
            {
                CreateObject<Bat>(Utils::Rect{ (float)column * edge,(float)i * edge,48,32 });
            }
            else if (check == "金币")
            {
                 CreateObject<coin>(Utils::Rect{ (float)column * edge,(float)i * edge,0,0 });
            }
            else if (check == "幽灵")
            {
                CreateObject<ghost>(Utils::Rect{ (float)column * edge,(float)i * edge-32,64,32 });
            }
            else if (check == "螃蟹")
            {
                CreateObject<zombie>(Utils::Rect{ (float)column * edge,(float)i * edge,64,40 });
            }
        }   
    }
}
