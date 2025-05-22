#include "MainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

MainWindow::MainWindow() {
	setWindowTitle("Media Player");
	setMinimumSize(400, 400);
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	// Create the input fields
	titleInput = new QLineEdit(this);
	urlInput = new QLineEdit(this);
	durationInput = new QLineEdit(this);
	artistInput = new QLineEdit(this);
	// Create the buttons
	addButton = new QPushButton("Add", this);
	deleteButton = new QPushButton("Delete", this);
	updateButton = new QPushButton("Update", this);
	undoButton = new QPushButton("Undo", this);
	addPlaylistButton = new QPushButton("Add to Playlist", this);
	playButton = new QPushButton("Play", this);
	nextButton = new QPushButton("Next", this);
	// Create the table and list widgets
	allMedia = new QTableWidget(0, 4, this);
	allMedia->setHorizontalHeaderLabels(QStringList() << "Title" << "URL" << "Duration" << "Artist");
	playlist = new QListWidget(this);
	// Set up the layout
	QFormLayout* formLayout = new QFormLayout();
	formLayout->addRow("Title:", titleInput);
	formLayout->addRow("URL:", urlInput);
	formLayout->addRow("Duration:", durationInput);
	formLayout->addRow("Artist:", artistInput);
	mainLayout->addLayout(formLayout);
	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(addButton);
	buttonLayout->addWidget(deleteButton);
	buttonLayout->addWidget(updateButton);
	buttonLayout->addWidget(undoButton);
	buttonLayout->addWidget(addPlaylistButton);
	buttonLayout->addWidget(playButton);
	buttonLayout->addWidget(nextButton);
	mainLayout->addLayout(buttonLayout);

	mainLayout->addWidget(allMedia);

	mainLayout->addWidget(playlist);

	connect(addButton, &QPushButton::clicked, this, &MainWindow::addMedia);
}