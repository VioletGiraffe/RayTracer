#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->_renderView->installEventFilter(this);

	_rayTracer.setProgressChangedCallback([this](size_t p){
		ui->_progress->setValue((int)p);
	});

	connect(ui->_btnRender, &QPushButton::clicked, this, [this]{
		if (_rayTracer.inProgress())
			return;

		auto result = _rayTracer.render(ui->_renderView->width(), ui->_renderView->height());
		{
			std::lock_guard lock{_bufferUpdatedMutex};
			_renderedImage = std::move(result.first);
		}
		ui->_renderView->update();
		setWindowTitle(QString::number(result.second * 1e-3f, 'f', 1) + " ms");
	});

	QTimer::singleShot(50, ui->_btnRender, &QPushButton::click);
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
	p.drawImage(
		QRect(ui->_renderView->rect().topLeft(), _renderedImage.size().scaled(ui->_renderView->size(), Qt::KeepAspectRatio)),
		_renderedImage);

	return true; // Event consumed
}
