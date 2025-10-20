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
