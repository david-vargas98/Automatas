#ifndef TANQUE_HPP
#define TANQUE_HPP
class Tanque
{
private:
	float nivel;
	float rpm;
	float temperatura;
	float presion;
public:
	Tanque(){ nivel = 0; rpm = 0; temperatura = 0; presion = 0; }

	void setNivel(float valor) { nivel = valor; }
	float getNivel() const { return nivel; }

	void setRpm(float valor) { rpm = valor; }
	float getRpm() const { return rpm; }

	void setTemperatura(float valor) { temperatura = valor; }
	float getTemperatura() const { return temperatura; }

	void setPresion(float valor) { presion = valor; }
	float getPresion() const { return presion; }
};
#endif // !TANQUE_HPP
