#include "Model.h"

Model::Model() : bgLayers_(), fgLayers_(), lines_(new Lines()), frameRate_(0), frameTime_(0), width_(DEFAULT_WIDTH), height_(DEFAULT_HEIGHT) {
	addFG(lines_);
}

Model::~Model() {
}

int Model::getFrameRate() const {
	return frameRate_;
}
void Model::setFrameRate(int r) {
	frameRate_ = r;
}

double Model::getFrameTime() const {
	return frameTime_;
}
void Model::setFrameTime(double t) {
}

int Model::getWidth() const {
	return width_;
}

int Model::getHeight() const {
	return height_;
}

void Model::addBG(std::shared_ptr<Drawable2D> drawable) {
	bgLayers_.push_back(drawable);
}
const std::vector<std::shared_ptr<Drawable2D>>& Model::getBG() const {
	return bgLayers_;
}
void Model::clearBG() {
	bgLayers_.clear();
}
void Model::addFG(std::shared_ptr<Drawable2D> drawable) {
	fgLayers_.push_back(drawable);
}
const std::vector<std::shared_ptr<Drawable2D>>& Model::getFG() const {
	return fgLayers_;
}
void Model::clearFG() {
	bgLayers_.clear();
}