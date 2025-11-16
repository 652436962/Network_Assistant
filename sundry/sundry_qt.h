#pragma once

#include <QNetworkInterface>
#include <QString>
#include <QByteArray>
#include <QFile>

#include "sundry.h"

/**
* @brief 得到接口类型对应的字符串
* @param type 接口类型
* @return 字符串
*/
QString interfaceTypeToString(QNetworkInterface::InterfaceType type);

/**
 * @brief 由 QByteArray 得到 Hex 字符串
 * @param data QByteArray 数据
 * @return 对应 Hex 字符串
 */
QString qByteArrayToHexSpaced(const QByteArray& data);

/**
 * @brief 从 Hex 字符串还原 QByteArray
 * @param hexStr Hex 字符串
 * @return QByteArray 数据
 */
QByteArray hexSpacedToQByteArray(const QString& hexStr);

/**
 * @brief 检查一个字符串是否为有效的十六进制字节序列
 * @param theString 待检查的字符串
 * @return true 如果是合法的十六进制序列
 * @note 每个字节必须是两个十六进制字符，如 "00 35 FF"（空格分隔）
 */
bool isValidHexSequence(const QString& theSymbol);

/**
 * @brief 得到对应编码的字符串
 * @param encoding 编码枚举
 * @return 对应的编码Qt字节数组
 */
QByteArray getEncodingQByteArray(EncodingEnum e);

/**
 * @brief 读取CSV表格文件内容
 * @param filePath 文件完整路径
 * @return 表格中的数据
 * @note 此函数只读取数据，不处理编码
 */
QVector<QVector<QByteArray>> readCsvFile_Qt(const QString& filePath);