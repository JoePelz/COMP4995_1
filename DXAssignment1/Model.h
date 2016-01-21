#pragma once

#include <d3d9.h>
#include "Defines.h"
#include "Drawable2D.h"
#include "Lines.h"
#include <vector>
#include <memory>

/* This class represents the current state of the program. It stores all game state information 
	and provides accessors and mutators as needed. 
*/
class Model {
	std::vector<std::shared_ptr<Drawable2D>> bgLayers_;
	std::vector<std::shared_ptr<Drawable2D>> fgLayers_;
	std::shared_ptr<Lines> lines_;

	/* The current frame rate, in frames per second. */
	int frameRate_;
	/* The render time in ticks per frame. (1 / fps) */
	INT64 frameTime_;
	/* The number of timing ticks per second. */
	INT64 ticksFrequency_;

	/* The device context width. */
	int width_;
	/* The device context height. */
	int height_;
public:
	Model();
	~Model();

	int getFrameRate() const;
	INT64 getFrameTime() const;
	void setFrameTick();
	int initFrameTimer();
	int getWidth() const;
	int getHeight() const;
	std::shared_ptr<Lines> Model::getLines();

	void addBG(std::shared_ptr<Drawable2D> drawable);
	const std::vector<std::shared_ptr<Drawable2D>>& getBG() const;
	void clearBG();
	void addFG(std::shared_ptr<Drawable2D> drawable);
	const std::vector<std::shared_ptr<Drawable2D>>& getFG() const;
	void clearFG();
};

