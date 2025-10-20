#pragma once

#include <QNetworkInterface>
#include <QString>

/**
* @brief 得到接口类型对应的字符串
* @param type 接口类型
* @return 字符串
*/
QString interfaceTypeToString(QNetworkInterface::InterfaceType type);