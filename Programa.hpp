#ifndef PROGRAMA_HPP
#define PROGRAMA_HPP
#include "Arreglo.hpp"
#include "usuario.hpp"
#include "tanque.hpp"
class Programa  //Clase que instancia arreglos de tipo Usuario y Tanque.
{
private:
	Arreglo<Usuario> usuarios;
	Arreglo<Tanque> tanques;
public:
	Programa() = default;
};
#endif // !PROGRAMA_HPP
