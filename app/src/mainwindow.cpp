#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->_renderView->installEventFilter(this);

	_rayTracer.setProgressChangedCallback([this](int p){
		ui->_progress->setValue(p);
	});

	connect(ui->_btnRender, &QPushButton::clicked, this, [this]{
		auto result = _rayTracer.render(ui->_renderView->width(), ui->_renderView->height());
		{
			std::lock_guard lock{_bufferUpdatedMutex};
			_renderedImage = std::move(result.first);
		}
		ui->_renderView->update();
		setWindowTitle(QString::number(result.second * 1e-3f, 'f', 1) + " ms");
	});
}

MainWindow::~MainWindow()
{
	delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
	if (watched != ui->_renderView || event->type() != QEvent::Paint)
		return QMainWindow::eventFilter(watched, event);

	QPainter p{ui->_renderView};

	std::lock_guard lock{_bufferUpdatedMutex};
	p.drawImage(QPoint{0, 0}, _renderedImage);

	return true; // Event consumed
}
