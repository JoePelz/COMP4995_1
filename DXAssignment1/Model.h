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
	/* The render time in seconds per frame. (1 / fps) */
	double frameTime_;
	/* The device context width. */
	int width_;
	/* The device context height. */
	int height_;
public:
	Model();
	~Model();

	int getFrameRate() const;
	void setFrameRate(int r);
	double getFrameTime() const;
	void setFrameTime(double t);
	int getWidth() const;
	int getHeight() const;

	void addBG(std::shared_ptr<Drawable2D> drawable);
	const std::vector<std::shared_ptr<Drawable2D>>& getBG() const;
	void clearBG();
	void addFG(std::shared_ptr<Drawable2D> drawable);
	const std::vector<std::shared_ptr<Drawable2D>>& getFG() const;
	void clearFG();
};

