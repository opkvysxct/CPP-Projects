// VYSX 2024
#include <iostream>

class Spring
{
private:
    double Speed = 1;
    double Damping = 1;
    double Constant = 1;
    double Mass = 1;
public:
    double Velocity = 0;
    double Target = 1;
    double Position = 0;

    double Update(double deltaTime) ;
	void AddForce(double force);
	Spring(double speed, double damping, double constant, double mass, double velocity, double target, double position);
	~Spring();
};

double Spring::Update(double deltaTime)
{
    double acceleration = (((-this->Damping * this->Velocity - this->Constant * (this->Position - this->Target)) / this->Mass) * this->Speed) * deltaTime;
    this->Velocity += acceleration;
    this->Position += this->Velocity;
    return this->Position;
}

void Spring::AddForce(double force)
{
	this->Velocity += force;
}

Spring::Spring(double speed, double damping, double constant, double mass, double velocity, double target, double position)
{
	std::cout << "Spring Created" << std::endl;
    this->Speed = speed;
	this->Damping = damping;
	this->Constant = constant;
	this->Mass = mass;
    this->Velocity = velocity;
    this->Target = target;
    this->Position = position;
}

Spring::~Spring()
{
	std::cout << "Spring Destroyed" << std::endl;
}

int main(int argc, char const *argv[])
{
	Spring spring = Spring(1, 0.1, 0.05,1,0,10,0);
	spring.AddForce(1);
	for (int i = 0; i < 650; i++)
	{
		std::cout << "Position: " << spring.Update(0.16) << std::endl;
	}
	return 0;
}