#ifndef SPRITE_H
#define SPRITE_H

#include "Vec2.h"
#include "Vec3.h"
#include "AnimSheet.h"
#include <fstream>
#include <vector>
#include <string>
#include "StringProc.h"
#include "Rect.h"
#include "SDLDisplay.h"


class Sprite
{
public:


	Sprite(){} //Only provided for array-building purposes. This constructor will NOT provide an usable Sprite
	Sprite(const std::string& filename); // If the file is of the the type ".sheetlist", then it will be loaded as such.
									// If not, the constructor will understand it to be the instructions to a single
									// sheet and load it as a an AnimSheet loading file.

	void playAnimation(int i); //if i is already being played, next frame, else, first frame. This function updates the sprite
	void Draw();
	void setVel(const Vec2f& v) {vel = v;}
	void setAcc(const Vec2f& a) {accel = a;}
	void setPos(const Vec2f& p);
	const Vec2f& getVel() const {return vel;}
	const Vec2f& getAcc() const {return accel;}
	const Vec2f& getPos() const {return pos;}
	void setCellTime(float secs = 0.04166f); //default = 24fps
	const Rectf& getBox() const {return rect;}
	Vec2i getAnimation() const {return current;}
	bool pixCollision(const Sprite& other) const;
	Rectf intersection(const Rectf& box) const; //though this should live in Rect.h, Templates make it dangerous to be there
	void setTransp(int i = 128) {transpThreshold = i;}
	void setDrawAlpha(int i);
	const AnimSheet& getSheet() const { return *sheets[animations[current.X()].X().X()];}

private:

	Vec2f vel;		//unit: Pixels/Second
	Vec2f accel;	//Speed, Acceleration and Position refer to screen movement and have nothing to do with world position
	Vec2f pos;		//All this are floats for smoothness purposes. The decimal part is cropped when drawing
	std::vector<AnimSheet*> sheets;
	Vec2i baseSize;
	Vec2i current; //(animation, frame)
	Vec2i currentCell;
	Rectf rect;
	float dt;
	std::vector<Vec3<Vec2i> > animations; //{ (sheet, animation) , (startframe) , (endframe) }
	float maxCellTime;
	unsigned int transpThreshold; //pixels with alpha above this value count for collision;



};

#endif // SPRITE_H