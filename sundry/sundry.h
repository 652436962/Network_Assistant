#pragma once

#include <vector>
#include <string>


/**
 * @brief 编码枚举
 * @note 我这里数值为 Windows 对应代码页的数
 */
enum class EncodingEnum
{
    UTF8 = 65001,
    GB18030 = 54936
};

/**
 * @brief 得到本地编码
 * @return 代表编码枚举
 */
EncodingEnum getLocalEncoding(void);

/**
 * @brief 得到对应编码的字符串
 * @param encoding 编码枚举
 * @return 对应的编码字符串
 */
std::string getEncodingStdString(EncodingEnum encoding);


/**
 * @brief 读取CSV表格文件内容
 * @param filePath 文件完整路径
 * @return 表格中的数据
 * @note 此函数只读取数据，不处理编码
 */
std::vector<std::vector<std::string>> readCSVFile(const std::string& filePath);

/**
 * @brief 从 Hex 字符串还原 std::vector<uint8_t>
 * @param hexStr Hex 字符串
 * @return std::vector<uint8_t> 数据
 */
std::vector<uint8_t> hex_string_to_bytes(const std::string& hex_str);

/**
 * @brief 由 std::vector<uint8_t> 得到 Hex 字符串
 * @param data std::vector<uint8_t> 数据
 * @return 对应 Hex 字符串
 */
std::string vectorToHexString(const std::vector<uint8_t>& data);

/**
* @brief 获取 hh:mm:ss.zzz 格式的时间戳字符串
* @return hh:mm:ss.zzz
*/
std::string getTimestamp(void);