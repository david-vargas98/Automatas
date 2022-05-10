#ifndef ARREGLO_HPP
#define ARREGLO_HPP
#include <iostream>
#include <stdexcept>
#include <functional>
using namespace std;

template <class T>  //"template" indica que será una plantilla. Entre "<>" va que es una clase "class" y la La "T" va indicar el tipo de dato que va contener la classe arreglo.
class Arreglo
{
protected:  //Se cambia el encapsulamineto para que la clase derivada de esta clase que es "ListaArreglo" pueda acceder a los atributos.
	T* arreglo; //La "T" es el puntero de tipo de dato genérico que va guardar la dirección de memoria dónde está ese arreglo que se definió o se reservó de manera dinámica.
	size_t cont; //Es el contador que comienza en "0", de tipo de dato "size_t".
	size_t tam; //Es el tamaño, que se va asignar de manera externa.
public:
	//Como es un "template", se deben definir los comportamientos en un mismo archivo, en este mismo "hpp" y no en un "cpp".
	//De una vez se le pasa los parámetros, el primer "tam" hace referencia al atributo "tam" declarado de forma privada y el segundo "(tam)" hace referencia a el "(size_t tam)" que se recibe en el constructor.
	Arreglo(size_t tam) :tam(tam) //El constructor va recibir siempre el "tamaño". Como se va usar memoria de forma dinámica, hay que hacer uso de la "rule of three" y declarar los demás.
	{
		arreglo = new T[tam]; //Se reserva memoria para ese "arreglo" que se tiene declarado de forma privada con "new" para reserva un tamaño, en este caso se reserva con "T" y entre "[]" ponemos "tam".
		cont = 0;
	}
	~Arreglo() //Se declara e implementa el destructor para liberar la memoria.
	{
		delete[] arreglo; //DEbido a que se reserva memoria en el constructor, hay que liberarla también, para eso usamos "delete", se pone "[]" porque es un arreglo y se pone el nombre del arreglo.
	}
	Arreglo(const Arreglo<T>& a) //El constructor copia recibe una referencia de manera constante otro "Arreglo" y hay que poner que es un "template" con "<T>" y se pone en la variable "a".
	{
		arreglo = new T[a.tam];  //Reservamos memoria y se usa el "tam" del que queremos copiar, por eso se pone "a.tam".
		for (size_t i = 0; i < a.cont; i++) //Con un "for" copiamos la información hacia nuestro arreglo.
		{
			arreglo[i] = a.arreglo[i]; //Se copia hacia "arreglo[i]" desde el objeto que queremos copiar que es "a.arreglo[i]".
		}
		cont = a.cont;  //Asignamos el contador.
		tam = a.tam;    //Asignamos el tamaño.
	}
	Arreglo<T>& operator =(const Arreglo<T>& a) //La sobrecarga del operador de asignación regresa una referencia a un arreglo que también se debe indicar que es "template <T>" 
	{                                           //y recibe otra referencia del arreglo que también es "template" y se guarda en "a".  
		//Cuando se quiere asignar de un arreglo a otro, lo que se hace es copiar la información que tiene el puntero, porque sino lo hacemos, lo que hace es copiar la dirección de memoria.
		delete[] arreglo; //libera el arreglo que ya tiene, porque lo que va hacer es crear un nuevo.

		arreglo = new T[a.tam];  //Se crea un nuevo arreglo de tipo "T", la información se va copiar desde "a".
		for (size_t i = 0; i < a.cont; i++)  //Se itera desde cero hasta el contador del otro objeto del que queremos estar asignando información.
		{
			arreglo[i] = a.arreglo[i];  //Copiamos esa información con el "for".
		}
		cont = a.cont;  //Al final se actualiza la información que ya teníamos para ese nuevo objeto 
		tam = a.tam;

		return *this;  //Se regresa una referencia.
	}
	Arreglo(initializer_list<T> e)  //Este es como otro constructor, un constructor "inicializador". "e" es una instancia de "initializer_list" que es una clase que ya existe en c++. 
	{
		tam = e.size(); //Aquí se define el tamaño.
		arreglo = new T[tam]; //Creamos nuestro arreglo dinámico con "new" para reservar esa cantidad de elementos que es "tam".
		//Ahora, una vez reservado se necesita copiar la información de la lista. 
		//En c++ este tipo de listas ("initializer_list"), tienen iteradores, entonces para acceder al iterador, en este caso es con "e.begin()", entonces se define de esta manera:
		auto it = e.begin(); //"auto" es como un tipo de dato que se escribe en tiempo de ejecución, lo que hace el compilador es deducir lo que regresa "begin", y "begin()" retorna el primer elemento, por así decrilo.
		for (size_t i = 0; i < tam; i++) //Lo que hará el "for" es ir pasando por cada valor de la lista e irlo copiando al nuevo elemento.
		{
			arreglo[i] = *it;  //Aquí, como el iterador no tiene como el valor real, sino tiene como el puntero donde está el valor ( como si fuiera la dirección de memoria), por eso ya tiene sobrecargado "*" y por eso se usa para acceder a la información que contiene "it". 
			it++; //Lo anterior es para el elemento "1", para el "2", pues estos iteradores tienen sobrecargados el operador "++", que no es que incremente en uno, sino lo que hace es saltar a la siguiente posición.
			cont++; //Entonces como ya pasamos a la siguiente posición, también se incrementa el contador, porque ya se agregó un elemento en una posición. 
		}
	}
	T& operator [] (size_t pos) { return arreglo[pos]; } //Sobrecarga del operador "[]" para mostrar los elementos del arreglo, y realizar una visualización rápida sin depurar.

	size_t size() { return cont; } //Lo único que hace es retornar lo que contiene la variable "contador", para no poner "números mágicos" en el ciclo "for" del main.
	size_t max_size() { return tam; } //Es para conocer el tamaño máximo o capacidad que puede tener mi arreglo.

	bool full() { return cont == tam; } //Es para saber si está lleno ese arreglo.
	bool empty() { return cont == 0; } //Es para saber si está vacío ese arreglo.

	void push_back(const T& e) //Permite agregar elementos al arreglo, es como un "insertar al final", aunque "al final" no significa que sea la última posición, sino que significa que es la última posición disponible.
	{                        //Porqué recibe una referencia de tipo "T"? Porque "T" es nuestro "template" y "&" para no crear una copia y "const" para que no pueda ser modificado a lo largo del programa.
							 //La "e" es el elemento que recibe y que vamos a ingresar al arreglo.
		//Debido a que nuestro arreglo se genera de forma dinámica y en tiempo de ejecución, tiene un límite, un límite que está almacenado en la variable "tam", que es el tamaño del arreglo
		//Pero como ya tenemos los métodos de "Full" y "empty", se puede validar de la siguiente forma:
		if (full())   //Si el arreglo está lleno, lo que se hace es lanzar una excepción, es decir cuando truena y no sabe que hacer el programa cuando esté lleno.
		{
			throw out_of_range("Arreglo is full"); //"throw" es la palabra reservada de excepción, "out_of_range" es la excepción que se va lanzar y mandamos un mensaje de lo que pasó.
												   //Como el arreglo está lleno, no sabe que hacer, lanza la excepción y termina el programa, y sino está lleno, contimnúa con la ejecución.
		}
		arreglo[cont] = e; //Lo que hace es copiar el elemento "e" que estemos recibiendo a la posición "cont".
		cont++; //Una vez copiado, incrementamos el contador.
	}

	void push_front(const T& e)  //Permite insertar elementos al inicio del arreglo, es decir, en la primer posición.
	{
		if (full()) //Se debe validar si está lleno, que en caso de estarlo, ya no se puede agregar elementos.
		{
			throw out_of_range("Arreglo is full"); //"throw" es la palabra reservada de excepción, "out_of_range" es la excepción que se va lanzar y mandamos un mensaje de lo que pasó.
												   //Como el arreglo está lleno, no sabe que hacer, lanza la excepción y termina el programa, y sino está lleno, contimnúa con la ejecución.
		}
		//Sino está lleno, lo que debemos hacer es mover la información hacia la derecha, es decir, mover de posición todos los elementos, por lo tanto se implementa un algoritmo de ordenamiento:
		for (size_t i = cont; i > 0; i--) //Se inicia desde la última posición, que es "cont". Y en este caso se va repetir mientras "i" siga siendo mayor a cero, porque es la posición a la que se quiere llegar.
		{                                 //Por tanto que se empieza el la posición de "cont", y se quiere llegar a la posición "0", entonces se gará un decremento "--" y no un incremento.
			arreglo[i] = arreglo[i - 1]; //Arreglo en la posición "i", que está apuntando a contador, va ser igual a lo que tenga arreglo en su posición "i-1"
		}                                //De esta manera se copia el valor en la posición "i-1" a la posición "i", y así es como se mueven los elementos una posición de izquierda a derecha.
										 //Una vez movidos los elementos, entonces ya se puede copiar en la posición "[0]" el objeto contenido en "e".
		arreglo[0] = e; //El caso base, es agregar en la posición cero, que es el frente en nuestro arreglo de nuestra lista y que inserte el elemento "e" en él.
		cont++; //Y  como insertó algo, pues va incrementar el valor del contador.
	}

	void insert(const T& e, size_t pos) //Recibe una referencia constante de tipo "T" en "e" y recibe una posición que debe ser válida.
	{
		if (full()) //Se debe validar si está lleno, que en caso de estarlo, ya no se puede agregar elementos.
		{
			throw out_of_range("Arreglo is full"); //"throw" es la palabra reservada de excepción, "out_of_range" es la excepción que se va lanzar y mandamos un mensaje de lo que pasó.
												   //Como el arreglo está lleno, no sabe que hacer, lanza la excepción y termina el programa, y sino está lleno, contimnúa con la ejecución.
		}
		else if (pos >= cont) //Se debe validar también la posición.
		{
			throw out_of_range("Invalid position"); //Si la posición no es válida, se puede mandar una excepción.
		}
		for (size_t i = cont; i > pos; i--) //Se inicia desde la última posición, que es "cont". Y en este caso se va repetir mientras "i" siga siendo mayor a cero, porque es la posición a la que se quiere llegar.
		{                                 //Por tanto que se empieza el la posición de "cont", y se quiere llegar a la posición "0", entonces se gará un decremento "--" y no un incremento.
			arreglo[i] = arreglo[i - 1]; //Arreglo en la posición "i", que está apuntando a contador, va ser igual a lo que tenga arreglo en su posición "i-1"
		}                                //De esta manera se copia el valor en la posición "i-1" a la posición "i", y así es como se mueven los elementos una posición de izquierda a derecha.
										 //Una vez movidos los elementos, entonces ya se puede copiar en la posición "[0]" el objeto contenido en "e".
		arreglo[pos] = e; //Se copia el elemento "e" en la psoición que el usuario indicó del arreglo.
		cont++; //Se incrementa el contador.
	}

	void pop_back() //Elimina el último elemento del arreglo.
	{
		if (empty())  //Si el arreglo está vacío, lanza la excepción.
		{
			throw out_of_range("Arreglo is empty");
		}
		cont--;
	}

	void pop_front() //Elimina el primer elemento del arreglo, es decir, el de la posición "0".
	{
		if (empty())  //Si el arreglo está vacío, lanza la excepción.
		{
			throw out_of_range("Arreglo is empty");
		}
		for (size_t i = 0; i < cont - 1; i++)  //Sino está vacío, se incia el "for" en cero,  hasta llegar a "cont-1", así nos quedará una posición libre, ya que apuntará en la posicióon "5" y no en "6".
		{
			arreglo[i] = arreglo[i + 1];  //Lo que hace es que el elemento siguiente, es decir, "i+1" lo pone en la posición actual "i", de cierta manera los recorre o copia de derecha a izquierda.
		}
		cont--; //Una vez ya movidos los elementos, ya que eliminamos o suprimimos un elemento, contador se disminuye.
	}

	void erase(size_t pos)  ////Se utiliza para eliminar un elemento en cierta posición, recibe una posición válida en "pos".
	{
		if (empty())  //Si el arreglo está vacío, lanza la excepción.
		{
			throw out_of_range("Arreglo is empty");
		}
		else if (pos >= cont)
		{
			throw out_of_range("Invalid position");
		}
		//Sino entra en ninguna excepción, entonces:
		for (size_t i = pos; i < cont - 1; i++)  //Comienza en "pos", la cuál queremos eliminar  hasta "cont-1".
		{
			arreglo[i] = arreglo[i + 1]; //El elemento en la posición "i", va ser igual al elemento en la posición siguiente "i+1". Y moverá los elementos de derecha a izquierda.
		}
		cont--;
	}

	void mostrar()  //Se utiiliza para mostrar los elementos del arreglo.
	{
		cout << "\tJugadores agregados" << endl;
		for (size_t i = 0; i < cont; i++)
		{
			cout << arreglo[i] << endl;
		}
		cout << endl;
	}

	//Implementanción de los métodos faltantes:
	//Como serán métodos como si fueran unos "get" para obtener nada más la información que está al inicio y al final, entonces deben retornar alguna referencia, es decir "T&".
	T& front() { return arreglo[0]; } //Retorna lo que hay al inicio de nuestro arreglo.
	T& back() { return arreglo[size() - 1]; } //Retorna lo que hay al final de nuestro arreglo.
	//Lo que hace es retornarnos un puntero, un puntero que nos va a decir la dirección de memoria dónde están los elementos o dónde hay información.
	  //Pasa por cada posición del arreglo que tenemos y ya que lo encontró (o la primer coincidencia), nos va retornar la dirección de memoria, en caso de no encontrar el valor, se retorna "NULL" ya que se quiere hacer algo con el valor 
	  //encontrado, en caso de que no se quisiese hacer nada, se puede retornar un "-1".
	T* find(function<bool(const T& e1, const T& e2)> cmp, const T& element)  //Regresa un puntero y se debe poner el "T" de "template". "Find()" recibe el elemento a buscar, es decir, recibe una referencia constante porque únicamente se va a leer, no vamos a crear una copia.
	{
		for (size_t i = 0; i < size(); i++)  //La última posición es "size()-1", porque "size()" por sí solo es la siguiente posición válida, que no es la última posición dónde hay un elemento.
		{
			if (cmp(element, arreglo[i]))   //Si el elemento es igual a el elemento que está en mi arreglo y justo en esa posición, quiere decir que ya lo encontré.
			{
				return &arreglo[i];  //Si ya se encontró, ahí se debe terminar, pero se debe retornar la dirección de memoria de ese elemento. Se le agrega "&" para que devuelva el puntero y no una copia.
			}
		}
		return nullptr;  //Si el "for" fue por todas las posiciones y nunca encontró el elemento que se buscaba, y cuando termine el "for", se le dice al usuario que no lo encontró devolviendo un "nullptr".   
	}

	//Todo esto: (function<bool(const T& e1, const T& e2)>, es el tipo de dato y quiere decir que se va a recibir una función y "cmp" es el objeto.
	void sort(function<bool(const T& e1, const T& e2)> cmp, bool ascendente = true)  //Método para ordenamiento por el método burbuja. Sino se manda nada, por "default" es "true", pero si se manda un "false", ahí cambia.
	{  //Entonces sort recibe toda esa función "function<bool(const T& e1, const T& e2)> cmp" que es como una función prototipo que pueda ser cualquier cosa y regresa un booleano.
		for (size_t j = size() - 1; j > 0; j--)  //Este "for", desplaza "j" desde la última posición del arreglo hasta "0".
		{
			for (size_t i = 0; i < j; i++)  //Este "for" se va realizar una vez desde "0" hasta la posición "J".
			{
				if (ascendente)  //En caso de ser "tru" hace el ascendente.
				{ //Se modifica el código para que se acople a la función "cmp".
					if (cmp(arreglo[i], arreglo[i + 1]))
					{
						T temp = arreglo[i];  //Se crea como una copia del elemento en la posición "i".
						swap(arreglo[i], arreglo[i + 1]);  //Se mandann los argumentos a "swap", es decir, se hace el intercambio.
					}
				}
				else
				{
					if (!cmp(arreglo[i], arreglo[i + 1]))  //Se pone lo mismo que en el ascendente, solo que al inicio lo negamos con un "!".
					{
						swap(arreglo[i], arreglo[i + 1]);  //Se mandann los argumentos a "swap".
					}
				}

			}
		}

	}

	void swap(T& e1, T& e2)  //Método que realiza el intercambio. No se coloca "const" porque estamos modificando información.
	{
		T temp = e1;  //Se crea como una copia del elemento en la posición "i".
		e1 = e2;  //Como ya se tiene la copia, se puede hacer el intercambio de los elementos de derecha a izquierda.
		e2 = temp;  //Se pasa el elemento copiado de de la izquierda de "arreglo[i]" que se almacenó en "temp" a la derecha en "arreglo[i+1]".
	}
};
#endif // !ARREGLO_HPP
