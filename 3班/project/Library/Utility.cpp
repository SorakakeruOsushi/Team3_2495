#include <sstream>
#include <DxLib.h>
#include "Utility.h"
#include "time.h"

namespace
{
    static const float REPEAT_TIME = 0.1f;      //  キーリピート間隔(sec)

    static bool triggerKeyBufferArray[0xff];    //  トリガーキーバッファ
    static bool triggerKeyBufferAllArray[0xff]; //  トリガーキーallバッファ(新しく加えたやつ)
    static float repeatKeyBufferArray[0xff];    //  リピートキーバッファ

    static bool triggerPadBufferArray[0xff];    //  トリガーパッドバッファ
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

    for (int i = 0; i < 0xff; i++)
    {
        triggerPadBufferArray[i] = false;
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

//  キー入力のallトリガー取得
bool KeyUtility::CheckTriggerAll(int keyCode)
{
    //
    bool triggerAllFlag = false;

    //  該当キーが押されている
    if (CheckHitKeyAll(keyCode) != 0)
    {
        //  前フレームで押されていなかった＝トリガー
        if (!triggerKeyBufferAllArray[keyCode])
        {
            triggerAllFlag = true;
        }
        //キーバッファに登録
        triggerKeyBufferAllArray[keyCode] = true;
    }
    else
    {
        //キーバッファに登録
        triggerKeyBufferAllArray[keyCode] = false;
    }

    return triggerAllFlag;
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

/*
//パッド操作入力

//  パッド入力のトリガー取得
bool KeyUtility::CheckTriggerPad(input.Buttons[XINPUT_BUTTON_B])
{
    bool triggerPadFlag = false;

    //  該当キーが押されている
    if (CheckHitKey(keyCode) != 0)
    {
        //  前フレームで押されていなかった＝トリガー
        if (!triggerPadBufferArray[keyCode])
        {
            triggerPadFlag = true;
        }
        //キーバッファに登録
        triggerPadBufferArray[keyCode] = true;
    }
    else
    {
        //キーバッファに登録
        triggerPadBufferArray[keyCode] = false;
    }

    return triggerPadFlag;
}
*/


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
