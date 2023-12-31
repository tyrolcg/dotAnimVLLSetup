#include<iostream>
#include<fstream>
#include<string>


bool isAnim(std::string path)
{
    return path.substr(path.length() - 5) == ".anim";
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

    std::cout << "write .anim file path..." << std::endl;
    std::cin >> path;
    std::ifstream ifs(path);
    
    
    
    if(ifs.fail())
    {
        std::cerr << "Failed to open file." << std::endl;
        return -1;
    }
    if(!isAnim(path))
    {
        std::cerr << "Not anim file." << std::endl;
        return -1;
    }
    std::cout << "File opened." << std::endl;
    
    // 出力ファイルはpathのファイル名_fixed.anim
    std::string outputPath = path.erase(path.length() - 5) + "_fixed.anim";
    std::ifstream ifstemp(outputPath);
    // 重複確認
    if(!ifstemp.fail())
    {
        std::cout << "Generate file exists. Do you want to overwrite?" << std::endl;
        std::cout << outputPath << std::endl;
        std::cout << "y/n" << std::endl;
        std::cin >> str;
        if(str != "y")
        {
            std::cerr << "End this program." << std::endl;
            return -1;
        }
    }
    std::ofstream ofs(outputPath);

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
            if(trimLeftSpace(str).rfind("path:", 0) == 0)
            {
                str = str.erase(str.find("path:") + 5);
                ofs << str << std::endl;
            }
        }
        else
        {
            // attributeから始まらなければそのままファイル出力
            ofs << str <<std::endl;
        }
    }
    std::cout << "Completed. >>" + outputPath << std::endl;
    system("PAUSE");
    
    return 0;
}
