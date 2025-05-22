#pragma once
#include <vector>
#include "mediaitem.h"
#include <fstream>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <memory>
using namespace std;
class Repo
{
protected:

	std::vector<shared_ptr<MediaItem>> items;

public:

	Repo() = default;

	void add(shared_ptr<MediaItem> item) {
		items.push_back(item);
	}
	std::vector<shared_ptr<MediaItem>>& getItems() {
		return items;
	}
	virtual ~Repo() = default; 
	Repo(const Repo& other) = delete;

	Repo& operator=(const Repo& other) = delete;

	bool delete_item(shared_ptr<MediaItem> item) {
		auto it = std::find(items.begin(), items.end(), item);
		if (it != items.end()) {
			items.erase(it); // remove the pointer from the vector
			return true;
		}
		return false;
	};

	int find_item(std::string title) {
		for (size_t i = 0; i < items.size(); i++) {
			if (items[i]->getTitle() == title) {
				return i;
			}
		}
		return -1; // not found
	}


	shared_ptr<MediaItem> delete_item(std::string title) {
		int index = find_item(title);
		if (index != -1) {
			shared_ptr<MediaItem> item = items[index];
			items.erase(items.begin() + index);
			return item;
		}
		else {
			return std::shared_ptr<MediaItem> (nullptr);
		}
	}
};

class FileRepo : public Repo {


private:

	string csvPath;

	vector<string> tokenize(string str, char delimiter)
	{
		vector <string> result;
		stringstream ss(str);
		string token;
		while (getline(ss, token, delimiter))
			result.push_back(token);

		return result;
	}

	 shared_ptr<MediaItem> readLine(istream& is) {
		string line;
		getline(is, line);
		vector<string> tokens = tokenize(line, ',');
		if (tokens.size() < 5) // make sure the data we have is ok
			//throw runtime_error("String invalid format");
			return nullptr;
		//Song(string title, string url, int duration, string artist)
		if (tokens[0] == "song") {
			Song* SongPtr = new Song(tokens[1], tokens[3], convertDurationToSeconds(tokens[2]), tokens[4]);
			return shared_ptr<Song>(SongPtr);
		}
		if (tokens[0] == "video") {
			return std::make_shared<Video>(tokens[1], tokens[3], convertDurationToSeconds(tokens[2]), tokens[5], tokens[1]);

		}
		//throw runtime_error("Unknown media type");
		return nullptr;
	}

	 int convertDurationToSeconds(const std::string& duration) {
		 std::istringstream iss(duration);
		 int minutes, seconds;
		 char delimiter;

		 // Parse the string in the format "minutes:seconds"
		 if (!(iss >> minutes >> delimiter >> seconds) || delimiter != ':') {
			 throw std::invalid_argument("Invalid duration format. Expected format: minutes:seconds");
		 }

		 // Convert to total seconds
		 return minutes * 60 + seconds;
	 }



public:
	FileRepo(string csvPath) : csvPath(csvPath) {
		load();
	}

	void save() {
		items.size();
	}

	void load() {

		items.clear(); // clear the current items

		ifstream in(csvPath);

		if (!in.is_open())
			throw runtime_error("not open");

		while (in.good()) {
			auto item = readLine(in);
			if(item)
				items.push_back(item);
		}

		in.close();

		cout << "We loaded " << items.size() << " items from the file" << endl;
	}



};