#pragma once
#include <string>
#include <vector>

/// <summary>
/// CSVファイルを読み、セルごとにデータを返します
/// データは、string型、int型、float型で返します
/// 3つの横並びのセルで、VECTOR型を返すこともできます
/// 範囲外を指定した場合は、assertします
/// </summary>
class CsvReader {
public:
	CsvReader(std::string filename);
	~CsvReader();
	int GetLines();
	int GetColumns(int line);
	std::string GetString(int line, int column);
	int GetInt(int line, int column);
	float GetFloat(int line, int column);
private:
	struct LINEREC {
		std::vector<std::string> record;
	};
	std::vector<LINEREC> all;
};
