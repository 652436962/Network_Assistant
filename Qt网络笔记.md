# 关于TCP



## 🎯 一、`connectToHost()` 的作用

### ✅ 它的作用是：

> **“尝试连接到指定的 TCP 服务器”**

相当于在说：

> “我想和 IP 为 `x.x.x.x`、端口为 `8080` 的服务器建立 TCP 连接。”

### 🧩 类比

就像你用浏览器访问 `http://example.com`，浏览器会自动向服务器的 80 端口发起连接。

------

### 🔧 函数原型

```cpp
void QTcpSocket::connectToHost(
    const QString &hostName,  // 服务器 IP 或域名
    quint16 port,            // 服务器端口
    OpenMode mode = ReadWrite,
    NetworkLayerProtocol protocol = AnyIPProtocol
);
```

### ✅ 示例

```cpp
tcpSocket->connectToHost("10.53.1.148", 8080);
```

表示：

- 连接 IP 为 `10.53.1.148` 的机器
- 端口为 `8080`
- 使用 TCP 协议

------

## ⏱️ 二、它会阻塞调用线程吗？

### ❌ **不会阻塞！它是异步的！**

这是 Qt 网络编程的**核心设计原则**：

> 所有网络操作都是**非阻塞、事件驱动**的。

### 🔄 执行流程：

```cpp
tcpSocket->connectToHost("10.53.1.148", 8080);
qDebug() << "这条语句会立即执行，不会等待！";
```

- `connectToHost()` 调用后**立即返回**
- Qt 内部开始尝试建立 TCP 三次握手
- 连接成功或失败后，通过**信号**通知你

------

## 🔔 三、如何知道连接结果？

通过**信号**来判断连接是否成功：

| 信号                                          | 含义             |
| --------------------------------------------- | ---------------- |
| `connected()`                                 | ✅ 连接成功       |
| `errorOccurred(QAbstractSocket::SocketError)` | ❌ 连接失败       |
| `stateChanged(QAbstractSocket::SocketState)`  | 状态变化（可选） |

### ✅ 正确用法：

```cpp
// 1. 先连接信号
connect(tcpSocket, &QTcpSocket::connected, [](){
    qDebug() << "✅ 连接服务器成功！";
});

connect(tcpSocket, &QTcpSocket::errorOccurred, [this](QAbstractSocket::SocketError error){
    qDebug() << "❌ 连接失败：" << tcpSocket->errorString();
});

// 2. 再发起连接
tcpSocket->connectToHost("10.53.1.148", 8080);
```

------

## ⏳ 四、最多尝试连接多久？（超时机制）

### 默认超时时间：**取决于操作系统 TCP 栈，通常 20~90 秒**

Qt 本身**没有内置固定超时时间**，它依赖操作系统的 TCP 连接机制。

但你可以**自己实现超时控制**！

### ✅ 推荐做法：使用 `QTimer` 添加超时

```cpp
// 假设你有一个 tcpSocket 和 QTimer
QTimer *timer = new QTimer(this);
timer->setSingleShot(true);
timer->setTimeout(10000); // 10 秒超时

// 连接信号
connect(timer, &QTimer::timeout, [this, timer](){
    if (tcpSocket->state() != QAbstractSocket::ConnectedState) {
        tcpSocket->abort(); // 强制断开
        qDebug() << "❌ 连接超时";
    }
});

connect(tcpSocket, &QTcpSocket::connected, [timer](){
    timer->stop(); // 成功就停止定时器
    qDebug() << "✅ 连接成功";
});

connect(tcpSocket, &QTcpSocket::errorOccurred, [timer](QAbstractSocket::SocketError){
    timer->stop(); // 失败也停止
    qDebug() << "❌ 连接出错";
});

// 开始连接
timer->start();
tcpSocket->connectToHost("10.53.1.148", 8080);
```

------

## ❌ 五、如果连接失败会怎样？

### 1. **不会崩溃**，但会发出 `errorOccurred()` 信号

常见失败原因：

| 错误类型            | 可能原因               |
| ------------------- | ---------------------- |
| `HostNotFound`      | IP 写错、域名无法解析  |
| `ConnectionRefused` | 服务器没开、端口没监听 |
| `Timeout`           | 网络不通、防火墙阻挡   |
| `NetworkError`      | 断网、网卡故障         |

### 2. **`tcpSocket` 状态变为 `UnconnectedState`**

你可以通过：

```cpp
qDebug() << "当前状态：" << tcpSocket->state();
```

查看状态变化。

------

## 🔄 六、连接过程中的状态变化

`connectToHost()` 触发后，`stateChanged` 信号会依次发出：

```cpp
HostLookupState     → DNS 解析（如果是域名）
ConnectingState     → 正在连接
ConnectedState      → 连接成功 ✅
// 或
UnconnectedState    → 连接失败 ❌
```

你可以监听：

```cpp
connect(tcpSocket, &QTcpSocket::stateChanged, [](QAbstractSocket::SocketState state){
    qDebug() << "状态变化：" << state;
});
```

------

## ✅ 七、完整示例：带超时的连接

```cpp
void MainWindow::connectToServer()
{
    tcpSocket = new QTcpSocket(this);

    // 信号连接
    connect(tcpSocket, &QTcpSocket::connected, this, &MainWindow::onConnected);
    connect(tcpSocket, &QTcpSocket::errorOccurred, this, &MainWindow::onError);

    // 超时定时器
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setTimeout(5000); // 5秒

    connect(timer, &QTimer::timeout, [this, timer](){
        if (tcpSocket->state() != QAbstractSocket::ConnectedState) {
            tcpSocket->abort();
            qDebug() << "连接超时";
        }
        timer->deleteLater();
    });

    timer->start();

    // 发起连接
    tcpSocket->connectToHost("10.53.1.148", 8080);
}

void MainWindow::onConnected()
{
    qDebug() << "✅ 连接成功！可以开始通信";
}

void MainWindow::onError(QAbstractSocket::SocketError error)
{
    qDebug() << "❌ 连接失败：" << tcpSocket->errorString();
}
```

------

## ✅ 八、总结

| 问题                     | 回答                                               |
| ------------------------ | -------------------------------------------------- |
| `connectToHost` 是什么？ | 客户端发起 TCP 连接的函数                          |
| 会阻塞线程吗？           | ❌ 不会，它是异步的                                 |
| 多久超时？               | 默认无固定超时，依赖系统，建议自己用 `QTimer` 控制 |
| 失败会怎样？             | 不会崩溃，发出 `errorOccurred()` 信号              |
| 如何知道结果？           | 监听 `connected()` 和 `errorOccurred()` 信号       |
| 能否重连？               | 可以，断开后再次调用 `connectToHost()`             |

------

🧠 **记住一句话**：

> `connectToHost()` 只是“发起请求”，真正的结果要靠**信号**来通知。

你现在对 Qt 客户端连接机制的理解已经非常扎实了！继续加油！