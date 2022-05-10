#ifndef MENU_TANQUE_HPP
#define MENU_TANQUE_HPP
#include "tanque.hpp"
#include <iomanip>  //Librer�a que manipula el acomodo de la informaci�n en la salida para realizar el formato tabla "left y setw()".
#include <Windows.h>  //Librer�a de la cu�l se hace uso de la funci�n "Sleep()".
void menu_operaciones_tanque(Usuario* u, Arreglo<Tanque>& t1, int pos)
{
	float volumen_acumulado = 0.0;  //Variable de volumen acumulado para el control del suministro del agua.
	while (true)
	{
		system("cls");
		string opt1;
		cout << "\t\tMen� de Tanque #0" << pos + 1 << endl;
		cout << "\tCondiciones actuales del Tanque #0" << pos + 1 << endl;
		cout << left;
		cout << setw(17) << "Nivel de volumen" << setw(24) << "Revoluciones por minuto" << setw(12) << "Temperatura" << setw(8) << "Presi�n" << endl;
		cout << setw(5) << t1[pos].getNivel() << setw(12) << " Litros" << setw(6) << t1[pos].getRpm() << setw(18) << "RPM"
			<< setw(5) << t1[pos].getTemperatura() << setw(7) << "�C" << setw(4) << t1[pos].getPresion() << setw(4) << "bar" << endl;
		cout << "\n1) Control de volumen de agua" << endl;
		cout << "2) Control de revoluciones por minuto (RPM)" << endl;
		cout << "3) Control de temperatura" << endl;
		cout << "4) Control de Presi�n" << endl;
		cout << "0) Salir" << endl;
		cout << "Elija una opci�n: ";
		getline(cin, opt1);

		if (opt1 == "1")
		{
			while (true)
			{
				system("cls");
				string agua;
				cout << "\tControl de volumen de agua" << endl;
				cout << "1) Llenar" << endl;
				cout << "2) Drenar" << endl;
				cout << "0) Salir" << endl;
				cout << "Elija una opci�n: ";
				getline(cin, agua);
				if (agua < "0" || agua > "2")
				{
					cout << "Usted ha elegido una opci�n no v�lida, vuelva a intentarlo" << endl;
					Sleep(1500);
					continue;
				}
				else if (agua == "0")
				{
					cout << "Regresando al men� del Tanque #0" << pos + 1 << "..." << endl;
					Sleep(1500);
					break;
				}
				else if (agua == "1")
				{
					if (t1[pos].getNivel() == 1000)
					{
						cout << "El Tanque est� a su m�xima capacidad, no se puede agregar m�s agua" << endl;
						Sleep(1500);
						break;
					}
					else
					{
						while (true)
						{
							system("cls");
							float volumen;
							cout << "\tControl de volumen de agua" << endl;
							cout << "Ingrese el volumen de agua que desea adicionar (En litros): ";
							cin >> volumen;
							volumen_acumulado = volumen_acumulado + volumen;
							if (volumen_acumulado > 1000)
							{
								cout << "No se puede agregar m�s de 1000 litros de agua al tanque" << endl;
								volumen_acumulado = volumen_acumulado - volumen;
								cin.ignore();
								Sleep(1500);
								continue;
							}
							if (volumen_acumulado > 1000 || volumen > 1000)
							{
								cout << "No se puede agregar m�s de 1000 litros de agua al tanque" << endl;
								cin.ignore();
								Sleep(1500);
								continue;
							}
							else
							{
								t1[pos].setNivel((volumen_acumulado));
								cout << "Adicionando volumen, espere porfavor..." << endl;
								for (size_t i = 0; i < volumen; i++)
								{
									cout << i << "\b\b\b\b";  //"\b" de este modo despu�s de imprimir un n�mero se mueve una posici�n atr�s y en vez de llenar la pantalla se vuelve a escribir en la misma posici�n en la que estaba 
									Sleep(10);
								}
								cout << "Usted ha adicionado " << volumen << " litros" << endl;
								Sleep(1500);
								break;
							}
						}
					}
					cin.ignore();
					break;
				}
				else if (agua == "2")
				{
					if (t1[pos].getNivel() == 0)
					{
						cout << "No se puede drenar ya que el tanque est� vac�o" << endl;
						Sleep(1500);
					}
					else
					{
						while (true)
						{
							system("cls");
							float volumen_drenar;
							float volumen_total = t1[pos].getNivel();
							int cont = 1;
							cout << "\tControl de volumen de agua" << endl;
							cout << "Ingrese el volumen de agua que desea drenar (En litros): ";
							cin >> volumen_drenar;
							t1[pos].setNivel(t1[pos].getNivel() - volumen_drenar);
							volumen_acumulado = t1[pos].getNivel();  //Se actualiza volumen_acumulado de modo que si se aumenta el nivel, la variable est� actualizada a el volumen que se halla quitado.
							for (float i = volumen_total; i > t1[pos].getNivel(); i--)
							{
								system("cls"); 
								cout << "\tControl de volumen de agua" << endl;
								cout << "Drenando volumen, espere porfavor..." << endl;
								cout << i << "\b\b\b";  //"\b" de este modo despu�s de imprimir un n�mero se mueve una posici�n atr�s y en vez de llenar la pantalla se vuelve a escribir en la misma posici�n en la que estaba 
							}
							cout << "Usted ha drenado " << volumen_drenar << " litros" << endl;
							Sleep(1500);
							break;
						}
						cin.ignore();
					}
				}
				break;
			}

		}
		else if (opt1 == "2")
		{
			if (t1[pos].getNivel() == 0 || t1[pos].getNivel() < 300)
			{
				cout << "No se puede operar el agitador sin un m�nimo del 30% de la capacidad del tanque" << endl;
				Sleep(1500);
			}
			else
			{
				while (true)
				{
					system("cls");
					float rpm;
					cout << "\tControl revoluciones por minuto (RPM)" << endl;
					cout << "Ingrese el n�mero de RPM que desea: ";
					cin >> rpm;
					if (rpm < 80)
					{
						cout << "El agitador solo puede ser operado en un m�nimo de 80 RPM" << endl;
						Sleep(1500);
						continue;
					}
					else if (rpm > 350)
					{
						cout << "El agitador solo puede ser operado en un m�ximo de 350 RPM" << endl;
						Sleep(1500);
						continue;
					}
					else
					{
						t1[pos].setRpm(rpm);
						cout << "Ajustando velocidad de agitador..." << endl;
						while (true)
						{
							for (size_t i = 0; i < rpm; i++)
							{
								cout << i << "\b\b\b";
								Sleep(10);
							}
							break;
						}
						cin.ignore();
						cout << "El agitador se encuentra mezclando a " << rpm << " revoluciones por minuto" << endl;
						Sleep(1500);
						break;
					}
				}
			}
		}
		else if (opt1 == "3")
		{
			while (true)
			{
				system("cls");
				float temperatura;
				cout << "\tControl Temperatura" << endl;
				cout << "Ingrese la temperatura deseada: ";
				cin >> temperatura;
				if (temperatura < 20)
				{
					cout << "La temperatura solo puede ser una m�nima de 20�C" << endl;
					Sleep(1500);
					continue;
				}
				else if (temperatura > 85)
				{
					cout << "La temperatura solo puede ser una m�xima de 85�C" << endl;
					Sleep(1500);
					continue;
				}
				else
				{
					t1[pos].setTemperatura(temperatura);
					cout << "Ajustando temperatura del tanque..." << endl;
					while (true)
					{
						for (size_t i = 0; i < temperatura; i++)
						{
							cout << i << "\b\b";
							Sleep(50);
						}
						break;
					}
					cin.ignore();
					cout << "El tanque se encuentra operando a una temperatura de " << temperatura << "�C" << endl;
					Sleep(1500);
					break;
				}
			}
		}
		else if (opt1 == "4")
		{
			while (true)
			{
				system("cls");
				float presion;
				cout << "\tControl de la Presi�n" << endl;
				cout << "Ingrese la presi�n deseada: ";
				cin >> presion;
				if (presion < 0)
				{
					cout << "La presi�n solo puede ser una m�nima de 0 bar" << endl;
					Sleep(1500);
					continue;
				}
				else if (presion > 4.5)
				{
					cout << "La presi�n solo puede ser una m�xima de 4.5 bar" << endl;
					Sleep(1500);
					continue;
				}
				else
				{
					t1[pos].setPresion(presion);
					cout << "Ajustando presi�n del tanque..." << endl;
					while (true)
					{
						for (size_t i = 0; i < presion; i++)
						{
							cout << i << "\b\b";
							Sleep(1000);
						}
						break;
					}
					cin.ignore();
					cout << "El tanque se encuentra operando a una presi�n de " << presion << " bar" << endl;
					Sleep(1500);
					break;
				}
			}
		}
		else if (opt1 == "0")
		{
			cout << "Regresando al men� de Tanques..." << endl;
			break;
		}
		else if (opt1 < "0" || opt1 > "4")
		{
			cout << "Opci�n no valida, vuelva a intentarlo" << endl;
			Sleep(1500);
		}

	}
}
void menu_tanque(Usuario* u, Arreglo<Tanque>& t1)
{
	while (true)
	{
		system("cls");
		string op;
		cout << "\tMen� de Tanques siendo manipulado por " << u->getNombre() << endl;
		cout << "1) Tanque #01" << endl;
		cout << "2) Tanque #02" << endl;
		cout << "0) Salir" << endl;
		cout << "Elija una opci�n: ";
		getline(cin, op);

		if (op == "1")
		{
			menu_operaciones_tanque(u, t1, 0);  //Se le pasa el arreglo de usuarios, el de tanques y la posici�n en la c�al se va modificar lso par�metros.
		}
		else if (op == "2")
		{
			menu_operaciones_tanque(u, t1, 1);
		}
		else if (op == "0")
		{
			cout << "Regresado al men� principal..." << endl;
			break;
		}
		else if (op < "1" || op > "2")
		{
			cout << "Usted ha elegido una opci�n no v�lida, vuelva a intentarlo" << endl;
		}
		Sleep(1500);
	}
}
#endif // !MENU_TANQUE_HPP
