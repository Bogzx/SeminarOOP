#pragma once
#include <string>
using std::string;

class MediaItem
{
	protected:
		string title, url;
		int duration;

	public:

		MediaItem();

		MediaItem(string title, string url, int duration);

		string getTitle() {
			return title;
		};
};

class Song : public MediaItem {

	private:
	string artist;

	public:

		Song(string title, string url, int duration, string artist) : MediaItem(title, url, duration), artist(artist) {

		}



};

class Video : public MediaItem {

private:
	string director,resolution;

public:

	Video(string title, string url, int duration, string director, string resolution) : MediaItem{ title, url, duration }, director(director), resolution(resolution) {

	}

};

