#include <stdio.h>
#include <list>
#include <memory>

#define PI 3.14159265358;

class IShape
{
public://�����o�֐�
	//�R���X�g���N�^�A�f�X�g���N�^
	IShape(){};
	~IShape(){};
	virtual float size() = 0;
	virtual void draw() = 0;
};

class Circle : public IShape
{
public://�����o�֐�
	Circle(float r) { Circle::r = r; }
	~Circle(){};
	float size() override { return r * r * PI; };
	void draw() override { printf("���̉~�̖ʐς�%f\n", size()); }
private:
	//���a
	float r;
};

class Rectangle : public IShape
{
public://�����o�֐�
	Rectangle(float x, float y) { Rectangle::x = x; Rectangle::y = y; }
	~Rectangle() {};
	float size() override { return x * y; };
	void draw() override { printf("���̋�`�̖ʐς�%f\n", size()); }
private:
	//���Əc�̒���
	float x,y;
};

int main()
{

	std::unique_ptr<Circle>circle = std::make_unique<Circle>(4);
	std::unique_ptr<Rectangle>rectangle = std::make_unique<Rectangle>(4,5);

	circle->draw();
	rectangle->draw();

	system("pause");

	return 0;
}