#pragma once
#include <vector>
#include "mediaitem.h"
#include <fstream>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <iostream>
using namespace std;
class Repo
{
protected:

	std::vector<MediaItem*> items;

public:

	Repo() = default;

	void add(MediaItem* item) {
		items.push_back(item);
	}
	std::vector<MediaItem*>& getItems() {
		return items;
	}
	virtual ~Repo() {
		for (size_t i = 0; i < items.size();  i++) {
			delete items[i];
		}
	}
	Repo(const Repo& other) = delete;

	Repo& operator=(const Repo& other) = delete;



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

	 MediaItem* readLine(istream& is) {
		string line;
		getline(is, line);
		if (line.empty()) // check if the line is empty
			return nullptr;
		vector<string> tokens = tokenize(line, ',');
		if (tokens.size() !=7) // make sure the data we have is ok
			throw runtime_error("String invalid format");
		//Song(string title, string url, int duration, string artist)
		if (tokens[0] == "song") {
			return new Song(tokens[1], tokens[3], convertDurationToSeconds(tokens[2]), tokens[4]);
		}
		if (tokens[0] == "video") {
			return new Video(tokens[1], tokens[3], convertDurationToSeconds(tokens[2]), tokens[5], tokens[1]);
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
		// clear the current items
		for (size_t i = 0; i < items.size(); i++) {
			delete items[i];
		}

		items.clear(); // clear the current items

		ifstream in(csvPath);

		if (!in.is_open())
			throw runtime_error("not open");

		while (in.good()) {
			MediaItem* item = readLine(in);
			if(item)
				items.push_back(item);
		}

		in.close();

		cout << "We loaded " << items.size() << " items from the file" << endl;
	}



};