#ifndef VECTOR_2_H
#define VECTOR_2_H

template <class T>
class Vector2
{
	public:
		Vector2<T>(T valX, T valY) : x(valX),
									 y(valY)
		{
		}
		virtual ~Vector2<T>();
		T x;
		T y;
};

template <>
class Vector2<short>
{
	public:
		Vector2() : x(0),
					y(0)
		{
		}
		Vector2(short valX, short valY) : x(valX),
										  y(valY)
		{
		}
		short x;
		short y;
};

template <>
class Vector2<unsigned short>
{
	public:
		Vector2() : x(0),
					y(0)
		{
		}
		Vector2(unsigned short valX, unsigned short valY) : x(valX),
															y(valY)
		{
		}
		unsigned short x;
		unsigned short y;
};

template <>
class Vector2<int>
{
	public:
		Vector2() : x(0),
					y(0)
		{
		}
		Vector2(int valX, int valY) : x(valX),
									  y(valY)
		{
		}
		int x;
		int y;
};

template <>
class Vector2<unsigned int>
{
	public:
		Vector2() : x(0),
					y(0)
		{
		}
		Vector2(unsigned int valX, unsigned int valY) : x(valX),
														y(valY)
		{
		}
		unsigned int x;
		unsigned int y;
};

template <>
class Vector2<float>
{
	public:
		Vector2() : x(0),
					y(0)
		{
		}
		Vector2(float valX, float valY) : x(valX),
										  y(valY)
		{
		}
		float x;
		float y;
};

template <>
class Vector2<double>
{
	public:
		Vector2() : x(0),
					y(0)
		{
		}
		Vector2(double valX, double valY) : x(valX),
											y(valY)
		{
		}
		double x;
		double y;
};

template <>
class Vector2<long>
{
	public:
		Vector2() : x(0),
					y(0)
		{
		}
		Vector2(long valX, long valY) : x(valX),
										y(valY)
		{
		}
		long x;
		long y;
};

template <>
class Vector2<unsigned long>
{
	public:
		Vector2() : x(0),
					y(0)
		{
		}
		Vector2(unsigned long valX, unsigned long valY) : x(valX),
														  y(valY)
		{
		}
		unsigned long x;
		unsigned long y;
};

#endif