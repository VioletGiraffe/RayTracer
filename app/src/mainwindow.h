#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow final : public QMainWindow
{
public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow *ui;
};
