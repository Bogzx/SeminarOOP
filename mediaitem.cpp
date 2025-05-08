#include "mediaitem.h"

MediaItem::MediaItem() {
	title = "";
	url = "";
	duration = -1;
}

MediaItem::MediaItem(string title, string url, int duration) {
	this->title = title;
	this->url = url;
	this->duration = duration;
}
