#include <locale>  //Librería usada para el manejo de caraccteres especiales.
#include "Programa.hpp"  //Se incluye la cabecera "Programa.hpp" creada para poder instanciar los arreglos o listas.
#include "menu_usuario.hpp"  //Se incluye la cabecera "menu_usuario.hpp" creada para poder acceder a la función contenida en ella.
int main()
{
	system("Title Sistema de control y monitoreo de Tanques");  //Se utiliza la función "system("Title")" para darle título a la ventana de la consola.
	setlocale(LC_CTYPE, "Spanish");  //Función para el uso de caracteres propios del español.
	cout << "\t\t\tBienvenido al Sistema de control y monitoreo de Tanques" << endl;
	cout << "\t\t\t\tAdministrador de usuarios: Supervisor" << endl;
	cout << "\t\t\tIngrese la cantidad de usuarios que desea administrar: ";
	size_t usuarios; //Declaración de la cantidad de usuarios.
	cin >> usuarios;  //Asignación de número de usuarios mediante el usuario.
	const size_t nro_tqs = 2;  //Se establece una constante para el tamaño fijo de la cantidad de tanques.
	Arreglo<Usuario> usuarios_(usuarios);  //Se crea el objeto del arreglo de usuarios en main, para no reiniciar los atributos.
	Arreglo<Tanque> t1(nro_tqs);  //Se crea el objeto del arreglo de tanques en main, para no reiniciar los atributos.
	menu_usuario(usuarios_, t1);  //Se pasan ambos arreglos o listas por parámetros.
	return 0;
}