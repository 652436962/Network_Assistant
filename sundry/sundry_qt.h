#pragma once

#include <QNetworkInterface>
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QDataStream>
#include <QVector>

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
 * @return 正常 表格中的数据  空 出现问题
 * @note 逗号分隔符
 * @note 此函数只读取数据，不处理编码
 */
QVector<QVector<QByteArray>> readCsvFile_Qt(const QString& filePath);


/*
* 将多个字符串以二进制文件存储
* 文件结构
* [uint32_t count]                    // 字符串总数（4字节）
* [string 0: uint32_t len + len bytes (UTF-8)]
* [string 1: uint32_t len + len bytes (UTF-8)]
* ……
* [string N-1: ...]
*/

/**
 * @brief 将 QStringList 以二进制格式写入文件
 * @param filePath 文件完整路径
 * @param strings 字符串列表
 * @return true 成功
 * @return false 失败
 */
bool saveQStringList(const QString& filePath, const QStringList& strings);

/** 
 * @brief 从二进制文件读取 QStringList
 * @param filePath 文件完整路径
 * @return 成功：字符串列表
 * @return 失败：空列表
 */
QStringList loadQStringList(const QString& filePath);