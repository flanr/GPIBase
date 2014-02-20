// Slider.cpp
#include "stdafx.h"

#include "Slider.h"


Slider::Slider()
{

}


void Slider::SetSlider(int p_X, int p_Y, int p_Width, int p_Height)
{
	m_x = p_X;
	m_y = p_Y;
	m_w = p_Width;
	m_h = p_Height;

	hovered = false;
	selected = true;

	m_sw = p_Width/* - p_Width/5*/;


	m_EmptySlider.setSize(sf::Vector2f(p_Width,p_Height));
	m_EmptySlider.setPosition(p_X,p_Y);
	m_FullSlider = m_EmptySlider;
	m_EmptySlider.setFillColor(sf::Color::Red);
	m_FullSlider.setFillColor(sf::Color::Transparent);
	SetValue(100);
}

void Slider::SetPosition(int p_X, int p_Y)
{
	m_EmptySlider.setPosition(p_X,p_Y);
	m_FullSlider = m_EmptySlider;
}



Slider::~Slider()
{
}

bool Slider::MouseOver(int x, int y)
{
	return (x > m_x && x <m_x + m_w) && (y > m_y && y < m_y + m_h);
}




void Slider::SetValue(int v)
{
	
	value = v % 101;				// emptySlider.w = sw*value/100;
	m_EmptySlider.setSize(sf::Vector2f((m_sw*v)/100,m_h));
	printf("SliderValue changed to: %d \r\n", value);
}

int Slider::GetValue()
{
	return value;
}


void Slider::MouseDown(int x, int y)
{
	if (MouseOver(x,y))
	{
		selected = true;
		printf("X:[%d] Y:[%d]\r\n", x, y);
		MoveMouse(x,y);
	}
}

void Slider::MouseUp()
{
	selected = false;
}
void Slider::MoveMouse(int x, int y)
{
	if (MouseOver(x,y))
	{
		hovered = true;
	}else
	{
		hovered = false;
		selected = false;
	}

	if (selected)
	{
		int offsetX = m_x - m_FullSlider.getPosition().x;
		if (offsetX <= 0)
		{
			SetValue(0);
		}
		else if (offsetX > m_sw)
		{
			SetValue(100);
		}else
		{
			SetValue((offsetX*100) / m_sw);
		}
	}


}

void Slider::SetColor(sf::Color color)
{
	m_EmptySlider.setFillColor(color);
}
