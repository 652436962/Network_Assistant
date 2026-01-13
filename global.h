#pragma once

#include <string>
#include "sundry.h"

/**
 * @brief 发送模式
 */
enum SendMode
{
	Single = 0,
	Multiple = 1
};

/**
 * @brief 工作模式
 */
enum class WorkMode
{
    TCP_Client,
    TCP_Server,
    UDP,
    UDP_Send_Only
};

/**
 * @brief 得到工作模式对应的字符串
 * @param mode 工作模式
 * @return 对应的字符串
 */
std::string getWorkModeString(WorkMode mode);

/**
* @brief 使用的编码
*/
extern EncodingEnum encodingUsed;