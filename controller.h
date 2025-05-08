#pragma once
#include "repo.h"
#include "mediaitem.h"
#include <stack>
class UndoAction {

public:
	virtual void undo() = 0;
	virtual ~UndoAction() {}


};

class UndoAdd : public UndoAction {
public:
	UndoAdd(Repo& repo, MediaItem* item) : repo(repo), item(item) {
	}
	void undo() override {
		repo.delete_item(item->getTitle());
		delete item;
	}
private:
	Repo& repo;
	MediaItem* item;
};

class UndoRemove : public UndoAction {

public:
	UndoRemove(Repo& repo, MediaItem* item) : repo(repo), item(item) {
	}
	void undo() override {
		repo.add(item);
	}

private:
	Repo& repo;
	MediaItem* item;
};

class Controller
{
private:
	Repo& repo;
	std::stack<UndoAction*> undoStack;

public:
	Controller(Repo& repo) :repo(repo) {
	}


};
