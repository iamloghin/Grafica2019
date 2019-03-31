#pragma once
class Punct
{
	private:
		int X,Y;
	public:
		Punct(int x, int y);
		int getX() const;
		int getY() const;
		void setX(int x);
		void setY(int y);
		~Punct();
};

