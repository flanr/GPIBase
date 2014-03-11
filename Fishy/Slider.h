// Slider.h
#pragma once




class Slider
{
public:
	Slider();
	void SetSlider(int p_X, int p_Y, int p_Width, int p_Height);
	void SetPosition(float p_x, float p_y);
	~Slider();
	void SetValue(int value);
	int GetValue();

	void MouseDown(int x, int y);
	void MouseUp();
	void MoveMouse(int x, int y);
	void SetColor(sf::Color);

	
	sf::RectangleShape m_EmptySlider, m_FullSlider, m_SliderBox;
private:
	bool MouseOver(int x, int y);
	int m_x,m_y,m_w,m_h, m_sw;
	int value;
	bool hovered, selected;

};
// Health
// w 259 h 41
// Energy
// w 150 h 25