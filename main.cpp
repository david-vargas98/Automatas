#include <locale>  //Librer�a usada para el manejo de caraccteres especiales.
#include "Programa.hpp"  //Se incluye la cabecera "Programa.hpp" creada para poder instanciar los arreglos o listas.
#include "menu_usuario.hpp"  //Se incluye la cabecera "menu_usuario.hpp" creada para poder acceder a la funci�n contenida en ella.
int main()
{
	system("Title Sistema de control y monitoreo de Tanques");  //Se utiliza la funci�n "system("Title")" para darle t�tulo a la ventana de la consola.
	setlocale(LC_CTYPE, "Spanish");  //Funci�n para el uso de caracteres propios del espa�ol.
	cout << "\t\t\tBienvenido al Sistema de control y monitoreo de Tanques" << endl;
	cout << "\t\t\t\tAdministrador de usuarios: Supervisor" << endl;
	cout << "\t\t\tIngrese la cantidad de usuarios que desea administrar: ";
	size_t usuarios; //Declaraci�n de la cantidad de usuarios.
	cin >> usuarios;  //Asignaci�n de n�mero de usuarios mediante el usuario.
	const size_t nro_tqs = 2;  //Se establece una constante para el tama�o fijo de la cantidad de tanques.
	Arreglo<Usuario> usuarios_(usuarios);  //Se crea el objeto del arreglo de usuarios en main, para no reiniciar los atributos.
	Arreglo<Tanque> t1(nro_tqs);  //Se crea el objeto del arreglo de tanques en main, para no reiniciar los atributos.
	menu_usuario(usuarios_, t1);  //Se pasan ambos arreglos o listas por par�metros.
	return 0;
}