#include "repo.h"
#include "mediaitem.h"
<<<<<<< HEAD
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	MainWindow Window;
	Window.show();
=======
int main() {


>>>>>>> ddc1a813bae602f09bc354cdbbb25300083f58c8
	Repo r;

	//Repo r1 = Repo(r);
	try { 
		FileRepo fr("media_entries.csv"); 
	}
	catch (const std::exception& e) {
		cout << "Error: " << e.what() << endl;
	}
	catch (...) {
		cout << "Unknown error" << endl;
	}
	
<<<<<<< HEAD
	return app.exec();
=======
	return 0;
>>>>>>> ddc1a813bae602f09bc354cdbbb25300083f58c8
}