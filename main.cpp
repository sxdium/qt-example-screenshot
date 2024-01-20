#include <QFile>
#include <QPixmap>
#include <QScreen>
#include <QBuffer>
#include <QFileInfo>
#include <QByteArray>
#include <QApplication>

QByteArray GetScreenshot(int screen, const char* format, int quality = -1) {
    QByteArray screenshot_data;

    QScreen* sc = qApp->screens().at(screen);
    QPixmap  px = sc->grabWindow(0);

    QBuffer buffer(&screenshot_data);
    buffer.open(QIODevice::WriteOnly);
    px.save(&buffer, format, quality);

    return screenshot_data;
}

bool WriteToFile(const char* path, const char* name, const QByteArray& data) {
    if(!QFileInfo(path).exists()) {
        return false;
    }

    QString file_path(path);
    if(!file_path.endsWith("/")) {
        file_path += "/";
    }
    file_path.append(name);

    QFile file(file_path);
    file.open(QIODevice::WriteOnly);
    file.write(data);

    return file.waitForBytesWritten(10000);
}

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QByteArray screenshot_data = GetScreenshot(0, "JPG", 30);
    WriteToFile("D:/Projects/Temp/what", "screenshot.png", screenshot_data);
    return 0;
}
