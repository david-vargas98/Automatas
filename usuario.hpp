#ifndef USUARIO_HPP
#define USUARIO_HPP
#include <iostream>
#include "tanque.hpp"
using namespace std;
class Usuario
{
private:
	string nombre;
	string contrasena;
public:
	Usuario() = default;
	Usuario(const string& nombre, const string& contrasena) :nombre{ nombre }, contrasena{ contrasena } {};

	void setNombre(const string& valor) { nombre = valor; }
	string getNombre() const { return nombre; }

	void setContrasena(const string& valor) { contrasena = valor; }
	string getContrasena() const { return contrasena; }
};
#endif // !USUARIO_HPP
