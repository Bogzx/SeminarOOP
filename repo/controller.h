#pragma once
#include <stack>
#include "mediaitem.h"
#include "repo.h"

class UndoAction {
public:
	virtual void undo() = 0;
	virtual ~UndoAction() = default;
};

class UndoAdd : public UndoAction {
private:
	Repo& repo;
	shared_ptr<MediaItem> item;
public:
	UndoAdd(Repo& repo, shared_ptr<MediaItem> item) : repo(repo), item(item) {}
	void undo() override {
		repo.delete_item(item);
	}
};

class UndoDelete : public UndoAction {
private:
	Repo& repo;
	shared_ptr<MediaItem> item;
public:
	UndoDelete(Repo& repo, shared_ptr<MediaItem> item) : repo(repo), item(item) {}
	void undo() override {
		repo.add(item);
	}
};

class UndoUpdate : public UndoAction {
private:
	Repo& repo;
	shared_ptr<MediaItem> oldItem;
	shared_ptr<MediaItem> newItem;
public:
	UndoUpdate(Repo& repo, shared_ptr<MediaItem> oldItem, shared_ptr<MediaItem> newItem) : repo(repo), oldItem(oldItem), newItem(newItem) {}
	void undo() override {
		repo.delete_item(newItem);
		repo.add(oldItem);
	}
};



class Controller
{
private:
	Repo& repo;
	std::stack<std::unique_ptr<UndoAction>> undoStack;

public:
	Controller(Repo& repo) : repo(repo) {
		// cannnot use this->repo = repo; given it needs to be initialised due to inheritance
	}

	void add(string mediaType, string title, string url, int duration, string artist) {
		shared_ptr<MediaItem> item = nullptr; // initialize item to nullptr


		if (mediaType == "Song") {
			item = shared_ptr<Song>(new Song(title, url, duration, artist));
		}
		else if (mediaType == "Video") {
			item = shared_ptr<Video>(new Video(title, url, duration, artist, "1080p"));
		}
		else {
			throw std::invalid_argument("Unknown media type");

			repo.add(item);
			undoStack.push(make_unique<UndoAdd>(repo, item));
		}
	}

	bool remove(string title) {

		shared_ptr<MediaItem> deletedItem = repo.delete_item(title);
		
		if (deletedItem != nullptr) {
			undoStack.push(make_unique<UndoDelete>(repo, deletedItem));
		}

		return deletedItem != nullptr;
	}

	bool undo() {
		if (undoStack.empty()) {
			return false;
		} // check if undo stack is empty 
		undoStack.top()->undo(); // get the top action
		undoStack.pop();
		return true;
	}

};

