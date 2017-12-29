#ifndef RECT_H
#define RECT_H

#include <cmath>

template <class T>
class Rect
{
	public:
		Rect<T>(T valLeft, T valTop, T valWidth, T valHeight) : left(valLeft),
																top(valTop),
																width(valWidth),
																height(valHeight)
		{
		}
		virtual ~Rect<T>()
		{
		}
		bool intersects(const Rect<T>& rect)
		{
			return (left < (rect.left + rect.width) && (left + width) > rect.left &&
					top < (rect.top + rect.height) && (top + height) > rect.top);
		}
		T left;
		T top;
		T width;
		T height;
};

template <>
class Rect<short>
{
	public:
		Rect() : left(0),
				 top(0),
				 width(0),
				 height(0)
		{
		}
		Rect(short valLeft, short valTop, short valWidth, short valHeight) : left(valLeft),
																			 top(valTop),
																			 width(valWidth),
																			 height(valHeight)
		{
		}
		virtual ~Rect()
		{
		}
		bool intersects(const Rect<short>& rect)
		{
			return (left < (rect.left + rect.width) && (left + width) > rect.left &&
					top < (rect.top + rect.height) && (top + height) > rect.top);
		}
		short left;
		short top;
		short width;
		short height;
};

template <>
class Rect<unsigned short>
{
	public:
		Rect() : left(0),
				 top(0),
				 width(0),
				 height(0)
		{
		}
		Rect(unsigned short valLeft, unsigned short valTop, unsigned short valWidth, unsigned short valHeight) : left(valLeft),
																												 top(valTop),
																												 width(valWidth),
																												 height(valHeight)
		{
		}
		virtual ~Rect()
		{
		}
		bool intersects(const Rect<unsigned short>& rect)
		{
			return (left < (rect.left + rect.width) && (left + width) > rect.left &&
					top < (rect.top + rect.height) && (top + height) > rect.top);
		}
		unsigned short left;
		unsigned short top;
		unsigned short width;
		unsigned short height;
};

template <>
class Rect<int>
{
	public:
		Rect() : left(0),
				 top(0),
				 width(0),
				 height(0)
		{
		}
		Rect(int valLeft, int valTop, int valWidth, int valHeight) : left(valLeft),
																	 top(valTop),
																	 width(valWidth),
																	 height(valHeight)
		{
		}
		virtual ~Rect()
		{
		}
		bool intersects(const Rect<int>& rect)
		{
			return (left <= (rect.left + rect.width) && (left + width) >= rect.left &&
					top <= (rect.top + rect.height) && (top + height) >= rect.top);
		}
		int left;
		int top;
		int width;
		int height;
};

template <>
class Rect<unsigned int>
{
	public:
		Rect() : left(0),
				 top(0),
				 width(0),
				 height(0)
		{
		}
		Rect(unsigned int valLeft, unsigned int valTop, unsigned int valWidth, unsigned int valHeight) : left(valLeft),
																										 top(valTop),
																										 width(valWidth),
																										 height(valHeight)
		{
		}
		virtual ~Rect()
		{
		}
		bool intersects(const Rect<unsigned int>& rect)
		{
			return (left < (rect.left + rect.width) && (left + width) > rect.left &&
					top < (rect.top + rect.height) && (top + height) > rect.top);
		}
		unsigned int left;
		unsigned int top;
		unsigned int width;
		unsigned int height;
};

template <>
class Rect<float>
{
	public:
		Rect() : left(0),
				 top(0),
				 width(0),
				 height(0)
		{
		}
		Rect(float valLeft, float valTop, float valWidth, float valHeight) : left(valLeft),
																			 top(valTop),
																			 width(valWidth),
																			 height(valHeight)
		{
		}
		virtual ~Rect()
		{
		}
		bool intersects(const Rect<float>& rect)
		{
			return (left < (rect.left + rect.width) && (left + width) > rect.left &&
					top < (rect.top + rect.height) && (top + height) > rect.top);
		}
		float left;
		float top;
		float width;
		float height;
};

template <>
class Rect<double>
{
	public:
		Rect() : left(0),
				 top(0),
				 width(0),
				 height(0)
		{
		}
		Rect(double valLeft, double valTop, double valWidth, double valHeight) : left(valLeft),
																				 top(valTop),
																				 width(valWidth),
																				 height(valHeight)
		{
		}
		virtual ~Rect()
		{
		}
		bool intersects(const Rect<double>& rect)
		{
			return (left < (rect.left + rect.width) && (left + width) > rect.left &&
					top < (rect.top + rect.height) && (top + height) > rect.top);
		}
		double left;
		double top;
		double width;
		double height;
};

template <>
class Rect<long>
{
	public:
		Rect() : left(0),
				 top(0),
				 width(0),
				 height(0)
		{
		}
		Rect(long valLeft, long valTop, long valWidth, long valHeight) : left(valLeft),
																		 top(valTop),
																		 width(valWidth),
																		 height(valHeight)
		{
		}
		virtual ~Rect()
		{
		}
		bool intersects(const Rect<long>& rect)
		{
			return (left < (rect.left + rect.width) && (left + width) > rect.left &&
					top < (rect.top + rect.height) && (top + height) > rect.top);
		}
		long left;
		long top;
		long width;
		long height;
};

template <>
class Rect<unsigned long>
{
	public:
		Rect() : left(0),
				 top(0),
				 width(0),
				 height(0)
		{
		}
		Rect(unsigned long valLeft, unsigned long valTop, unsigned long valWidth, unsigned long valHeight) : left(valLeft),
																											 top(valTop),
																											 width(valWidth),
																											 height(valHeight)
		{
		}
		virtual ~Rect()
		{
		}
		bool intersects(const Rect<unsigned long>& rect)
		{
			return (left < (rect.left + rect.width) && (left + width) > rect.left &&
					top < (rect.top + rect.height) && (top + height) > rect.top);
		}
		unsigned long left;
		unsigned long top;
		unsigned long width;
		unsigned long height;
};

#endif