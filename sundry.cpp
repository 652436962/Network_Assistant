#include "sundry.h"

#include <Windows.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cctype>
#include <algorithm>

std::string getProtocolTypeString(ProtocolType type)
{
    std::string typeString = "";
    switch (type)
    {
    case ProtocolType::TCP_Server:
        typeString = "TCP Server";
        break;
    case ProtocolType::TCP_Client:
        typeString = "TCP Client";
        break;
    case ProtocolType::UDP:
        typeString = "UDP";
        break;
    default:
        break;
    }
    return typeString;
}

EncodingEnum getLocalEncoding()
{
    EncodingEnum encoding = EncodingEnum::UTF8;
    UINT acp = GetACP(); // 返回 Windows 系统的 "ANSI Code Page"
    switch (acp)
    {
    case 936: // GBK
        encoding = EncodingEnum::GB18030;
        break;
    case 54936: // GB18030
        encoding = EncodingEnum::GB18030;
        break;
    case 65001: // UTF-8
        encoding = EncodingEnum::UTF8;
        break;
    default: // 其它默认为UTF-8
        encoding = EncodingEnum::UTF8;
        break;
    }
    return encoding;
}

std::string getEncodingString(EncodingEnum encoding)
{
    std::string result = "UTF-8";
    switch (encoding)
    {
    case EncodingEnum::GB18030:
        result = "GB18030";
        break;
    case EncodingEnum::UTF8:
        result = "UTF-8";
        break;
    default:
        result = "UTF-8";
        break;
    }
    return result;
}

std::vector<std::vector<std::string>> readCSVFile(const std::string& filePath)
{
    std::vector<std::vector<std::string>> data;

    // 1. 打开文件
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cout << "无法打开文件: " << filePath << std::endl;
        return data; // 返回空向量
    }

    std::string line;

    // 2. 逐行读取
    while (std::getline(file, line))
    {
        // 跳过空行
        if (line.empty())
        {
            continue;
        }

        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        // 3. 按逗号分割每行
        while (std::getline(ss, cell, ','))
        {
            row.push_back(cell);
        }

        // 4. 添加到数据向量
        data.push_back(row);
    }

    // 5. 关闭文件
    file.close();
    // std::cout << "读取到" << data.size() << "行 " << data[0].size() << "列" << std::endl;

    return data;
}



/**
 * @brief 判断字符是否为合法的十六进制字符
 * @param c 要判断的字符
 * @return true 是 false 否
 */
bool is_hex_char(char c)
{
    return (c >= '0' && c <= '9') ||
        (c >= 'A' && c <= 'F') ||
        (c >= 'a' && c <= 'f');
}


/**
 * @brief 将单个十六进制字符转换为数值
 * @param c 字符
 * @return 对应数值
 * @note 0b0000 - 0b1111 (0-15)
 */
uint8_t hex_char_value(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else if (c >= 'A' && c <= 'F')
    {
        return c - 'A' + 10;
    }
    else if (c >= 'a' && c <= 'f')
    {
        return c - 'a' + 10;
    }
    // 可选：抛出异常或返回错误值
    return 0; // 或 throw std::invalid_argument("Invalid hex char");
}

/**
 * @brief 将两个十六进制字符转换为一个 uint8_t 字节
 * @param high 前面的字符
 * @param low 后面的字符
 * @return 对应的字节
 */
uint8_t hex_char_to_byte(char high, char low)
{
    return (hex_char_value(high) << 4) | hex_char_value(low);
}

std::vector<uint8_t> hex_string_to_bytes(const std::string& hex_str) {
    std::vector<uint8_t> result;
    std::string cleaned;

    // 提取十六进制字符
    for (char c : hex_str)
    {
        if (is_hex_char(c))
        {
            cleaned += c;
        }
    }

    if (cleaned.size() % 2 != 0) {
        return {}; // 返回空向量
    }

    for (size_t i = 0; i < cleaned.size(); i += 2)
    {
        result.push_back(hex_char_to_byte(cleaned[i], cleaned[i + 1]));
    }

    return result;
}

std::string vectorToHexString(const std::vector<uint8_t>& data)
{
    std::ostringstream oss;
    for (size_t i = 0; i < data.size(); ++i) {
        if (i > 0) {
            oss << " "; // 字节之间用空格分隔
        }
        oss << std::uppercase << std::setfill('0') << std::setw(2)
            << std::hex << static_cast<int>(data[i]);
    }
    return oss.str();
}
