#pragma once

class Dreapta
{
	private:
		int fromX, fromY, toX, toY;
		float m,n;
		int dX, dY, a, b, c;

	public:
		Dreapta();
		Dreapta(int fromX, int fromY, int toX, int toY);
		float getM() const;
		float getN() const;
		int getDX() const;
		int getDY() const;
		int getA() const;
		int getB() const;
		int getC() const;
		void setM(const float val);
		void setN(const float val);
		void setDX(const int val);
		void setDY(const int val);
		void setA(const int val);
		void setB(const int val);
		void setC(const int val);
		~Dreapta();
};

