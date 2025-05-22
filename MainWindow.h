#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>


class MainWindow : public QWidget
{
	Q_OBJECT // This macro is necessary for all Qt widgets that use signals and slots

private:
	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* updateButton;
	QPushButton* undoButton;
	QPushButton* addPlaylistButton;
	QPushButton* playButton;
	QPushButton* nextButton;

	QTableWidget* allMedia;
	QListWidget* playlist;
	QLineEdit* titleInput;
	QLineEdit* urlInput;
	QLineEdit* durationInput;
	QLineEdit* artistInput;

public:
	MainWindow();
public slots: 
	void addMedia() {
		// Implement the logic to add media
		// For example, you can get the values from the input fields and add them to the repo
		QString title = titleInput->text();
		QString url = urlInput->text();
		QString duration = durationInput->text();
		QString artist = artistInput->text();

		// Call the controller's add method
		// controller->add("song", title.toStdString(), url.toStdString(), duration.toInt(), artist.toStdString());
		// Clear the input fields
		titleInput->clear();
		urlInput->clear();
		durationInput->clear();
		artistInput->clear();
		// new QTableWidgetItem (title, url, duration, artist);
		// Update the table widget

		int row = allMedia->rowCount();
		allMedia->insertRow(row);
		allMedia->setItem(row, 0, new QTableWidgetItem(title));
		allMedia->setItem(row, 1, new QTableWidgetItem(url));
		allMedia->setItem(row, 2, new QTableWidgetItem(duration));
		allMedia->setItem(row, 3, new QTableWidgetItem(artist));


	}

};

