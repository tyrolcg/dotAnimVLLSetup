#include<iostream>
#include<fstream>
#include<string>


bool isFbx(std::string path)
{
    return path.substr(path.length() - 4) == ".fbx";
}

// 左側のスペースを削除
std::string trimLeftSpace(const std::string& string , const char* trimCharacterList = " ")
{
    std::string result;
    std::string::size_type left = string.find_first_not_of(trimCharacterList);

    result = string.substr(left);
    return result;
}

int main(int argc, char* argv[])
{
    std::string path, str;
    
    std::cin >> path;
    std::ifstream ifs(path);
    
    
    if(ifs.fail())
    {
        std::cerr << "Failed to open file." << std::endl;
        return -1;
    }
    if(isFbx(path))
    {
        std::cerr << "Not fbx file." << std::endl;
        return -1;
    }
    std::cout << "File opened." << std::endl;
    // 出力ファイルはpathのファイル名_fixed.anim
    std::ofstream ofs(path.erase(path.length() - 5) + "_fixed.anim");

    // animファイルの中身を1行ずつ取り出して検証
    while(getline(ifs, str))
    {
        // 文字列への処理
        if(trimLeftSpace(str).rfind("attribute", 0) == 0)
        {
            ofs << str << std::endl;

            // attributeから始まっていたら次の行を読む
            getline(ifs, str);
            // attributeの次の行がpathから始まる
            if(trimLeftSpace(str).rfind("path", 0) == 0)
            {
                str = str.erase(str.find("path") + 4);
                ofs << str << std::endl;
            }
        }
        else
        {
            // attributeから始まらなければそのままファイル出力
            ofs << str <<std::endl;
        }
    }
    std::cout << "Completed. >>" + path.erase(path.length() - 5) + "_fixed.anim" << std::endl;;
    return 0;
}
