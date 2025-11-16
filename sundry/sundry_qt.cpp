#include "sundry_qt.h"


QString interfaceTypeToString(QNetworkInterface::InterfaceType type)
{
    switch (type) {
    case QNetworkInterface::Loopback:
        return QStringLiteral("Loopback (虚拟回环)");
    case QNetworkInterface::Virtual:
        return QStringLiteral("Virtual");
    case QNetworkInterface::Ethernet:
        return QStringLiteral("Ethernet (以太网)");
    case QNetworkInterface::Slip:
        return QStringLiteral("SLIP 连接");
    case QNetworkInterface::CanBus:
        return QStringLiteral("CAN Bus");
    case QNetworkInterface::Ppp:
        return QStringLiteral("PPP 拨号连接");
    case QNetworkInterface::Fddi:
        return QStringLiteral("FDDI 网络");
    case QNetworkInterface::Wifi:
        return QStringLiteral("Wi-Fi (无线局域网)");
    case QNetworkInterface::Phonet:
        return QStringLiteral("Phonet");
    case QNetworkInterface::Ieee802154:
        return QStringLiteral("IEEE 802.15.4");
    case QNetworkInterface::SixLoWPAN:
        return QStringLiteral("6LoWPAN 低功耗无线");
    case QNetworkInterface::Ieee80216:
        return QStringLiteral("IEEE 802.16");
    case QNetworkInterface::Ieee1394:
        return QStringLiteral("IEEE 1394 (FireWire)");
    case QNetworkInterface::Unknown:
    default:
        return QStringLiteral("Unknown");
    }
}

QString qByteArrayToHexSpaced(const QByteArray& data)
{
    QString hex = QString::fromLatin1(data.toHex()).toUpper();
    if (hex.isEmpty())
        return hex;

    QString result;
    for (int i = 0; i < hex.length(); i += 2)
    {
        result += hex.mid(i, 2);
        result += ' ';
    }
    return result;
}

QByteArray hexSpacedToQByteArray(const QString& hexStr)
{
    QString cleaned = hexStr.simplified().remove(' '); // 去掉空格
    return QByteArray::fromHex(cleaned.toLatin1());
}

/**
 * @brief 判断一个字符是否为合法的十六进制字符（0-9, A-F, a-f）
 * @param ch 字符
 * @return true 是，false 否
 */
static bool isHexChar(QChar ch)
{
    return (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f');
}

bool isValidHexSequence(const QString& theString)
{
    // 第一步：提取所有非空格字符
    QString cleaned;
    for (QChar ch : theString)
    {
        if (ch != ' ')
        {
            cleaned += ch;
        }
    }

    // 第二步：检查是否为空
    if (cleaned.isEmpty())
    {
        return false;
    }

    // 第三步：检查每个字符是否都是十六进制字符
    for (QChar ch : cleaned)
    {
        if (!isHexChar(ch))
        {
            return false;
        }
    }

    // 第四步：检查字符总数是否为偶数（每个字节2位）
    return (cleaned.length() % 2) == 0;
}

QByteArray getEncodingQByteArray(EncodingEnum e)
{
    QByteArray byteArray = QByteArray::fromStdString(getEncodingString_Std(e));

    return byteArray;
}

QVector<QVector<QByteArray>> readCsvFile_Qt(const QString& filePath)
{
    QVector<QVector<QByteArray>> result;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return result; // 文件打不开，返回空
    }

    // 按行读取（QTextStream 会自动处理 \r\n / \n）
    // 注意：这里我们不指定编码，QTextStream 默认使用本地编码（但我们要的是原始字节！）
    // 所以改用 readLine() 返回 QByteArray 的方式更合适

    // 改为直接读取原始字节流，避免 QTextStream 自动解码
    while (!file.atEnd()) {
        QByteArray line = file.readLine().trimmed(); // 移除行尾换行符和空格

        // 跳过空行
        if (line.isEmpty()) {
            continue;
        }

        // 按逗号分割（注意：不处理引号内的逗号！）
        QList<QByteArray> fields = line.split(',');

        // 将 QByteArray 列表转为 QVector
        QVector<QByteArray> row;
        row.reserve(fields.size());
        for (const QByteArray& field : fields) {
            row.append(field.trimmed()); // 可选：去除字段前后空格
        }

        result.append(row);
    }

    file.close();
    return result;
}
