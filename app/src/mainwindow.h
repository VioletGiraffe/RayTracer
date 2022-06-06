#pragma once
#include "raytracer.h"
#include "compiler/compiler_warnings_control.h"

DISABLE_COMPILER_WARNINGS
#include <QImage>
#include <QMainWindow>
RESTORE_COMPILER_WARNINGS

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
