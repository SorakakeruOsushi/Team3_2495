#include <sstream>
#include <DxLib.h>
#include "Utility.h"
#include "time.h"

namespace
{
    static const float REPEAT_TIME = 0.1f;      //  キーリピート間隔(sec)

    static bool triggerKeyBufferArray[0xff];    //  トリガーキーバッファ
    static float repeatKeyBufferArray[0xff];    //  リピートキーバッファ
}


/**********************/
/***    KeyUtility  ***/
/**********************/

//  キー関連処理の初期化
void KeyUtility::Init()
{
    for (int i = 0; i < 0xff; i++)
    {
        triggerKeyBufferArray[i] = false;
        repeatKeyBufferArray[i] = 0.0f;
    }
}

//  キー入力のトリガー取得
bool KeyUtility::CheckTrigger(int keyCode)
{
    bool triggerFlag = false;

    //  該当キーが押されている
    if(CheckHitKey(keyCode) != 0)
    {
        //  前フレームで押されていなかった＝トリガー
        if(!triggerKeyBufferArray[keyCode])
        {
            triggerFlag = true;
        }
        //キーバッファに登録
        triggerKeyBufferArray[keyCode] = true;
    }
    else
    {
        //キーバッファに登録
        triggerKeyBufferArray[keyCode] = false;
    }
    
    return triggerFlag;
}

//  キー入力のリピート取得
bool KeyUtility::CheckRepeat(int keyCode)
{
    bool repeatFlag = false;

    //  該当キーが押されている
    if (CheckHitKey(keyCode) != 0)
    {
        //  リピート間隔時間押されていたら、リピート入力とする
        repeatKeyBufferArray[keyCode] += Time::DeltaTime();
        if (repeatKeyBufferArray[keyCode] >= REPEAT_TIME)
        {
            repeatFlag = true;
            repeatKeyBufferArray[keyCode] = 0.0f;
        }
    }
    else
    {
        //キーバッファに登録
        repeatKeyBufferArray[keyCode] = 0.0f;
    }

    return repeatFlag;
}


/*******************/
/***    CSV関連  ***/
/*******************/

//  区切り文字を指定して文字列を分割する
std::vector<std::string> CSV::split(const std::string& text, char delim)
{
    std::vector<std::string> elements;
    std::stringstream ss(text);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        if (!item.empty())
        {
            elements.push_back(item);
        }
    }
    return elements;
}
