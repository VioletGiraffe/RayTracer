#pragma once
#include "raytracer.h"

#include <QImage>
#include <QMainWindow>

#include <mutex>

namespace Ui {
class MainWindow;
}

class MainWindow final : public QMainWindow
{
public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

protected:
	bool eventFilter(QObject *watched, QEvent *event);

private:
	RayTracer _rayTracer;
	QImage _renderedImage;

	std::mutex _bufferUpdatedMutex;

	Ui::MainWindow *ui;
};
