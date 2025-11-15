#pragma once

#include <string>
#include "sundry.h"

/**
 * @brief 支持的发送区类型
 */
enum class SendOptions
{
    single,//单项发送
    multiple//多项发送
};

/**
 * @brief 工作模式
 */
enum class WorkMode
{
    TCP_Client,
    TCP_Server,
    UDP
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