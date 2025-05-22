#include "repo.h"
#include "mediaitem.h"
int main() {


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
	
	return 0;
}