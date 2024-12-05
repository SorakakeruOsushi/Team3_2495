#pragma once

#include <vector>

/// <summary>
/// キー入力のクラス
/// </summary>
/// <author>HORIKOSHI Masahiro</author>
namespace KeyUtility
{
    void Init();
    bool CheckTrigger(int keyCode);     //  キー入力のトリガー取得
    bool CheckTriggerAll(int keyCode);     //  キー入力のトリガー取得
    bool CheckRepeat(int keyCode);      //  キー入力のリピート取得

    //bool CheckTriggerPad( );     //  パッド入力のトリガー取得
}

/// <summary>
/// csvのクラス
/// </summary>
/// <author>HORIKOSHI Masahiro</author>
namespace CSV
{
    std::vector<std::string> split(const std::string& text, char delim);    //  区切り文字を指定して文字列を分割する
}
