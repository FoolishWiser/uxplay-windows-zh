#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QDir>
#include <QProcessEnvironment>
#include <QIcon>

#ifdef _WIN32
#include <windows.h>
#include <cstdio>
#endif

int main(int argc, char *argv[]) {
#ifdef _WIN32
    // 如果进程是从控制台（CMD/PowerShell）启动的，附加到控制台以便查看 qDebug() 输出
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        // 重定向 stdout 和 stderr 到控制台
        FILE* fp;
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stderr);
        freopen_s(&fp, "CONIN$", "r", stdin);
        std::ios::sync_with_stdio();
    }
#endif

    QApplication app(argc, argv);
    app.setOrganizationName("leapbtw");
    app.setApplicationName("uxplay-windows");
    app.setWindowIcon(QIcon(QApplication::applicationDirPath() + "/resources/icon.ico"));
    
    QString appPath = QApplication::applicationDirPath();
    
    QString pluginPath = QDir::toNativeSeparators(appPath + "/lib/gstreamer-1.0");
    qputenv("GST_PLUGIN_PATH", pluginPath.toUtf8());

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QString path = QDir::toNativeSeparators(appPath) + ";" + env.value("PATH");
    qputenv("PATH", path.toUtf8());

    app.setQuitOnLastWindowClosed(false);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(nullptr, "错误", "系统托盘不可用。");
        return 1;
    }

    MainWindow window;
    return app.exec();
}