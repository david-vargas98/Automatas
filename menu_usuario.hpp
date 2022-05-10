#ifndef MENU_USUARIO_HPP  //Se definen las directivas, y en caso de no estarlo se definirán.
#define MENU_USUARIO_HPP
#include <iostream> //Para el uso de los flujos de entrada y salida.
#include <string>  //Para el uso de "getline()".
#include "menu_tanque.hpp"  //Se incluye la cabecera "menu_tanque.hpp" creada para poder acceder a la función contenida en ella.
using namespace std;  //Se declara para acceder al espacio de nombres dónde se encuentra toda la librería estandar, con tal de no escribir "std::" para cada función del estandar.
void menu_usuario(Arreglo<Usuario>& usuario, Arreglo<Tanque>& t1)  //Recibe por parámetro dos referencias, una instancia de Arreglo de tipo usuario y otra de tipo tanque.
{
	cin.ignore();  //Se utiliza ya que previamente se ingresó un entero.
	string opcion;
	while (true)  //Se usan los ciclos "infinitos" para repetir el menú siempre.
	{
		system("cls");
		cout << "\tMenú de usuarios" << endl;
		cout << "1) Agregar usuario" << endl;
		cout << "2) Mostrar usuarios" << endl;
		cout << "3) Borrar usuario por posición" << endl;
		cout << "0) Salir" << endl;
		cout << "Elije una opción: ";
		getline(cin, opcion);

		if (opcion == "1")
		{
			if (usuario.full())  //Se valida si etá lleno el arreglo de usuarios.
			{
				cout << "Ya no se puede agregar más usuarios :/" << endl;
				Sleep(1500);
				continue;  //Hace que el ciclo se reinice y vuelva al inicio, es decir, al menú y no ejecute el código siguiente.
			}
			//Se instancia un objeto de tipo usuario.
			Usuario u;
			//Se pide los datos del usuario:
			string nombre;
			cout << "Ingresa un nombre de usuario: ";
			getline(cin, nombre);

			string contrasena;
			cout << "Ingresa tu contraseña: ";
			getline(cin, contrasena);

			//Se asignan los atributos al objeto:
			u.setNombre(nombre);
			u.setContrasena(contrasena);

			//Se agrega el objeto al Arreglo.
			usuario.push_back(u);

			//Mensaje de confirmación.
			cout << "¡Usuario agregado con éxito!" << endl;
			Sleep(2000);
		}
		else if (opcion == "2")
		{
			if (usuario.empty())  //Validación para usar la opción solo en caso de que halla usuarios registrados.
			{
				while (true)
				{
					system("cls");
					size_t no_usuario;
					cout << "No hay usuarios registrados :/" << endl;
					cout << "¿Desea ingresar como Supervisor?" << endl;
					cout << "1) Si" << endl;
					cout << "2) No" << endl;
					cout << "Elije una opción: ";
					cin >> no_usuario;
					cin.ignore();
					if (no_usuario == 2)
					{
						cout << "Regresando al menú principal..." << endl;
						break;
					}
					else if (no_usuario == 1)
					{
						string sup;
						cout << "Ingrese la contraseña del Supervisor: ";
						getline(cin, sup);
						if (sup == "12345")
						{
							//Entonces se crea el puntero "*u" que almacenará la dirección de memoria del usuario en la ubicación "0".
							//Esto con la intención de tener un objeto temporal que acceda al siguiente menú, es decir,
							//sin agregarlo al arreglo o lista de usuarios que administra "Programa.hpp.
							Usuario* u = &usuario[0];  //Se usa "&" porque no queremos una copia.
							u->setNombre("Supervisor");  //Se le asigna el nombre "Supervisor" al objeto temporal para mostrarlo en pantalla.
							cout << "Ingresó con éxito el usuario: " << u->getNombre() << endl; //Se utiliza "->" ya que estamos trabajando con un puntero.
							cout << "¡Bienvenido " << u->getNombre() << ", ten un excelente día!" << endl;
							Sleep(1500);
							menu_tanque(u, t1);  //Se manda el usuario y tanques a usar por argumento.
							break;
						}
						else
						{
							cout << "Ha ingresado una contraseña erronea" << endl;
							Sleep(1500);
							continue;
						}

					}
					else if (no_usuario < 1 || no_usuario > 2)
					{
						cout << "Usted ha elegido una opción no válida, vuelva a intentarlo" << endl;
						Sleep(1500);
					}
				}
			}
			else
			{
				while (true)
				{
					system("cls");
					cout << "\tLista de usuarios" << endl;
					size_t cont{ 0 };  //Se utiliza para mostrar el número de opción con los usuarios.
					size_t op_usuario;  //Se utiliza para ingresar el número de opción de usuario.
					for (size_t i = 0; i < usuario.size(); i++)
					{
						cout << cont + 1 << ") " << usuario[i].getNombre() << endl;  //Se muestra el usuario y número de opción.
						cont++;  //Se aumenta el contador, para aumentar el número de opción dependiendo de los usuarios agregados.
					}
					cout << "0) Salir" << endl;
					cout << "Seleccione un usuario: ";
					cin >> op_usuario;
					cin.ignore();  //Se utiliza ya que previamente se ingresó un entero. 
					if (op_usuario == 0)
					{
						cout << "Regresando al menú principal..." << endl;
						break;
					}
					else if (op_usuario > usuario.size())
					{
						cout << "Opción no valida, vuelva a intentarlo" << endl;
						Sleep(1500);
						continue;
					}
					string acceso;
					cout << "Usuario: " << usuario[op_usuario - 1].getNombre() << endl;
					cout << "Ingrese su contraseña: ";
					getline(cin, acceso);
					if (acceso != usuario[op_usuario - 1].getContrasena())
					{
						cout << "Ha ingresado una contraseña erronea" << endl;
						Sleep(1500);
						continue;
					}
					//Se usa "&" porque no queremos una copia.
					//Entonces se crea el puntero "*u" que almacenará la dirección de memoria del usuario en la ubicación "op_sel-1".
					Usuario* u = &usuario[op_usuario - 1];   //Se usa el -1 ya que se aumentó previamente en "cont + 1" para mostrar las opcines en el menú anterior.
					cout << "Ingresó con éxito el usuario: " << u->getNombre() << endl; //Se utiliza "->" ya que estamos trabajando con un puntero.
					cout << "¡Bienvenido " << u->getNombre() << ", ten un excelente día!" << endl;
					Sleep(1500);
					menu_tanque(u, t1);  //Se manda el usuario y tanques a usar por argumento.
					break;
				}
				
			}
			Sleep(1500);
		}
		else if (opcion == "3")
		{
			if (usuario.empty())  //Validación para usar la opción solo en caso de que halla usuarios registrados.
			{
				cout << "No hay usuarios registrados :/" << endl;
			}
			else
			{
				while (true)
				{
					system("cls");
					string supervisor;
					cout << "\tAdvertencia: Solo el supervisor puede realizar esta acción, sino es uno, salga del menú" << endl;
					cout << "1) Soy supervisor" << endl;
					cout << "0) Salir" << endl;
					cout << "Elija una opción: " << endl;
					getline(cin, supervisor);
					if (supervisor == "0")
					{
						cout << "Regresando al menú principal..." << endl;
						break;
					}
					else if (supervisor == "1")
					{
						string usuario_sup;
						string contrasena_sup;
						cout << "Ingrese su usuario: ";
						getline(cin, usuario_sup);
						cout << "Ingrese su contraseña: ";
						getline(cin, contrasena_sup);

						if (usuario_sup != "Supervisor" || contrasena_sup != "12345")
						{
							cout << "Usted ha ingresado un usuario o contraseña incorrectos o inexistentes, vuelva a intentarlo" << endl;
							Sleep(1500);
						}
						if (usuario_sup == "Supervisor" && contrasena_sup == "12345")
						{
							while (true)
							{
								system("cls");
								cout << "\tUsuarios actualmente registrados y su posición:" << endl;
								for (size_t i = 0; i < usuario.size(); i++)
								{
									//Se muestra el usuario, contraseña y número de opción.
									cout << "Usuario: " << usuario[i].getNombre() << endl << "Contraseña: " << usuario[i].getContrasena() << endl << "Posición: " << i << endl << endl;
								}
								size_t posicion;
								cout << "¿Cuál es la posición del usuario que desea eliminar?" << endl;
								cin >> posicion;
								if (posicion < 0 || posicion > usuario.size() - 1) //Se pone "-1" ya que "size()" regresa la siguiente posición disponible y no una válida.
								{
									cout << "Usted ha elegido una posición a eliminar no válida, intentelo de nuevo" << endl;
									Sleep(1500);
								}
								else
								{
									cout << "El usuario " << usuario[posicion].getNombre() << " en la posición " << posicion << " ha sido borrado con éxito!" << endl;
									usuario.erase(posicion);
									break;
								}
							}
							cin.ignore();
							break;
						}
					}
					else if (supervisor < "0" || supervisor > "1")
					{
						cout << "Usted ha ingresado una opción no válida, vuelva a intentarlo" << endl;
						Sleep(1500);
					}
				}
			}
			Sleep(1500);
		}
		else if (opcion == "0")
		{
			cout << "Usted ha salido del programa" << endl;
			Sleep(1500);
			break;
		}
		else if (opcion < "0" || opcion > "3")
		{
			cout << "Usted ha elegido una opción no válida, vuelva a intentarlo" << endl;
			Sleep(1500);
		}
	}
}
#endif // !MENU_USUARIO_HPP
