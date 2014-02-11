// Slider.h

#include "stdafx.h"



class Slider
{
public:
	Slider(int p_X, int p_Y, int p_Width, int p_Height);
	~Slider();
	void Draw();
	void SetValue(int value);
	int GetValue();

	void MouseDown(int x, int y);
	void MouseUp();
	void MoveMouse(int x, int y);


private:
	bool MouseOver(int x, int y);
	sf::RectangleShape m_EmptySlider, m_FullSlider;
	int m_x,m_y,m_w,m_h, m_sw;
	int value;
	bool hovered, selected;

};
// Health
// w 259 h 41
// Energy
// w 150 h 25