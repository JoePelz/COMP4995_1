#include "Model.h"

Model::Model() : bgLayers_(), fgLayers_(), lines_(new Lines()), frameRate_(0), frameTime_(0), width_(DEFAULT_WIDTH), height_(DEFAULT_HEIGHT) {
	addFG(lines_);
}

Model::~Model() {
}

UINT Model::getFrameRate() const {
	return frameRate_;
}

INT64 Model::getFrameTime() const {
	return frameTime_;
}
void Model::setFrameTick() {
	static INT64 lastTime = 0;
	INT64 newTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&newTime);
	frameTime_ = newTime - lastTime;
	frameRate_ = (frameRate_ * 29 + ticksFrequency_ / frameTime_) / 30; //running average of last 30 values.
	lastTime = newTime;
}

int Model::initFrameTimer() {
	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksFrequency_);

	if (ticksFrequency_ == 0) {
		Errors::SetError(TEXT("The system does not support high resolution timing"));
		return E_FAIL;
	}

	return S_OK;
}

int Model::getWidth() const {
	return width_;
}

int Model::getHeight() const {
	return height_;
}

std::shared_ptr<Lines> Model::getLines() {
	return lines_;
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