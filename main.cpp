// Alejo: en este archivo debes completar:
//
//Antes de iniciar si tienes los archivos de excel dentro de la carpeta borralos
//Recuerda que apenas acabes, o si quieres probar si funciona o debes correrlo
//Para correrlo presiona Windows+R, escribe cmd, luego pon "cd (espacio) (copia la direccion de tu carpeta de parqueadero y peguala)" 
//Luego pon "g++ main.cpp" y finalmente pon "a.exe". Asi lo corres
//Si tienes alguna duda o no sabes como integrar las funciones al main, preguntale a CHATGPT o a mi
//
//INSTRUCCIONES:
//
// 1) CrearPlaca()
// 2) RegistroDePrecios()
// 3) Guardar la factura de los carros que salen
// 4) la parte de cobrar al sacar un vehículo
// 5) VerImagenDeCarros()
// 6) Eliminar el vehiculo que salió del parqueadero
//
// FLUJO DEL PROGRAMA:
//
// 1. Cuando entra un vehículo:
//    - Llamar CrearPlaca()
//    - Guardar la placa en el parqueadero
//    - Llamar RegistroDePrecios()
//
// 2. Cuando sale un vehículo:
//    - Buscar la placa en RegistroDePrecios.txt
//    - Obtener PrecioTotal
//    - Cobrar
//    - Guardar factura (placa, precio, propina)
//    - Eliminar la placa del registro
//
// IMPORTANTE:
// - Usa solo for, no getline
// - Usa ofstream con modo append cuando sea necesario
// - Trabaja siempre con la variable global "placa"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

char opcion;
char elegirparq;
bool regresarmenu = false;
int preciocarros = 300;
int preciomotos = 175;
int preciobici = 80;
int fila;
int columna;
string placa;
int PrecioTotal;
int precio; 
int propina;

char MostrarElMenu(string NombreParq){
    cout<<"Bienvenido a "<<NombreParq<<"!\n";
    cout<<"Cobramos  a carros $"<<preciocarros<<" COP/min, a motos "<<preciomotos<<" y a bicicletas "<<preciobici<<".\n";
    cout<<"Que desearia hacer?"<<endl;
    cout<<endl;
    cout <<"m - presione m para ver este menu de nuevo\n";
    cout <<"l - ver lista de parqueaderos y disponibilidad\n";
    cout <<"v - agregar o sacar un vehículo al parqueadero\n";
    cout <<"c - consultar placa/id y en que espacio del parqueadero esta\n";
    cout <<"i - ver una imagen con los vehiculos que han entrado/salido del parqueadero\n";
    cout <<"s - salir\n";
    cout <<"Opcion: ";
    cin>>opcion;
    cout<<endl;
    return opcion;

}

bool CrearParqueaderoCarros(string ruta){
    ofstream archivo(ruta);
    if (!archivo.is_open()){
        cout<<"No se pude crear el parqueadero de carros, reinicie el codigo\n";
        return false;
    } else {
        archivo << "Pared Bloqueado ENTRADA ";
        for (int i = 0; i < 4; i++){
            archivo << "Bloqueado Bloqueado Parking ";
        }
        archivo << "Bloqueado SALIDA Pared \n";

        for (int k = 0; k < 2; k++){
            for (int i = 0; i < 6 ;i++){
                archivo << "Pared Parking Via ";
                for (int j = 0; j < 4; j++){
                    archivo << "Parking Parking Via ";
                }
                archivo << "Parking Via Pared \n";
            }
            archivo<<"Pared Parking ";
            for (int i = 0; i < 15; i++){
                archivo<<"Via ";
            }
            archivo<<"Pared \n";
        }
        for (int i = 0; i < 18; i++){
            archivo<<"Pared ";
        }
        cout<<"El parqueadero de carros ha sido creado con exito.\n";
        return true;
    }
}

bool CrearParqueaderoMotos(string ruta){
    ofstream archivo(ruta);
    if (!archivo.is_open()){
        cout<<"No se pude crear el parqueadero de motos, reinicie el codigo\n";
        return false;
    } else {
        archivo<<"Entrada ";
        for (int i = 0; i < 13; i++){
            archivo<<"Bloqueado ";
        }
        archivo<<"SALIDA \n";
        
        for (int k = 0; k < 3; k++){
            for (int i = 0; i < 15; i++){
                archivo<<"Via ";
            }
            archivo<<endl;
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 5; j++){
                    archivo<<"Via Parking Parking ";
                }
                archivo<<endl;
            }
        }
        cout<<"El parqueadero de motos ha sido creado con exito.\n";
        return true;
    }
}

bool CrearParqueaderoBicis(string ruta){
    ofstream archivo(ruta);
    if (!archivo.is_open()){
        cout<<"No se pude crear el parqueadero de bicicletas, reinicie el codigo\n";
        return false;
    } else {
        archivo<<"Entrada ";
        for (int i = 0; i < 13;i++){
            archivo<<"Bloqueado ";
        }
        archivo<<"Salida ";
        archivo<<endl;
        for (int i = 0; i < 15; i++){
            archivo<<"Via ";
        }
        archivo<<endl;
        for (int i = 0; i < 15; i++){
            archivo<<"Parking ";
        }
        cout << "El parqueadero de bicicletas ha sido creado con exito.\n";
        return true;
}
}

bool VerLista(string ruta, int filas, int columnas){
    ifstream archivo(ruta);
    if (!archivo.is_open()){
        cout<<"No se pudo leer "<<ruta<<" regresando al menu";
        regresarmenu = true;
        return false;
    }

    string arr[100][100]; 

    cout << "   ";

    for (int j = 0; j < columnas; j++) {
        cout << j + 1;
        if (j < columnas - 1) {
            cout << " | ";
        }
    }
    cout << endl;
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            if (!(archivo >> arr[i][j])) {
                return false;
            }
        }
    }

    for (int i = 0; i < filas; i++) {
        cout << i + 1 << " | ";

        for (int j = 0; j < columnas; j++) {
            cout << arr[i][j];
            if (j < columnas - 1) {
                cout << " | ";
            }
        }
        cout << endl;
    }

    return true;
}

char ElegirParq(){
    cout<<"Cual parqueadero quiere elegir para hacer esta accion?\n";
    cout<<"Presione c para carros, m para motos y b para bicicletas\n";
    cout<<"Opcion: ";
    cin>>elegirparq;

    return elegirparq;
}

//(1) Crear Placa
string CrearPlaca(){
    if (elegirparq == 'c'){
        //codigo para crear placa aleatoria de carro ej:ABC123 (asegurate de guardar esa placa nueva que te cree en la variable global "placa")

        //recuerda que debes poner al final que placa = (el numero aletorio que se genero)
    } else if (elegirparq == 'm'){
        //codigo para crear placa aleatoria de moto ej:ABC12D (asegurate de guardar esa placa nueva que te cree en la variable global "placa")

        //recuerda que debes poner al final que placa = (el numero aletorio que se genero)
    } else if (elegirparq == 'b'){
        //codigo para crear placa aleatoria de bicicleta ej:123456 (asegurate de guardar esa placa nueva que te cree en la variable global "placa")

        //recuerda que debes poner al final que placa = (el numero aletorio que se genero)
    }
    return placa;
}

int RegistroDePrecios();

bool AddExitVehiculo(string ruta, int filas, int columnas){
        ifstream archivo_in(ruta);

        if (!archivo_in.is_open()){
            cout<<"No se pudo leer "<<ruta<<" regresando al menu";
            regresarmenu = true;
            return false;
        }

    string arr[100][100]; 
        
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            if (!(archivo_in >> arr[i][j])) {
                return false;
            }
        }
    }

    archivo_in.close();

    char accion;
    cout<<"Quiere ingresar un vehiculo al parqueadero o sacarlo? Presione i/s respectivamente\n";
    cout<<"Opcion: ";
    cin>>accion;

    cout<<"\nPorfavor inserte la fila y la columna, donde esta la celda en la que quiere realizar la accion (ej: 3 4)\n";
    cout<<"Opcion: ";
    cin>>fila>>columna;

    int f = fila -1;
    int c = columna -1;
    
    if (f < 0 || f >= filas || c < 0 || c >=columnas){
        cout << "\nLa coordenada esta fuera del rango del parqueadero, volviendo al menu\n";
        regresarmenu = true;
        return false;
    }

    string celda = arr[f][c];

    if (accion == 'i'){
        bool libre = false;
        for (int i = 0; i < filas && !libre; i++){
            for (int j = 0; j < columnas; j++){
                if (arr[i][j] == "Parking"){
                    libre = true;
                    break;
                }
            }
        }
        if (libre == false){
            cout<<"No hay cupo en el parqueadero, regresando al menu\n";
            regresarmenu = true;
            return false;
        }
       
        // Antes de lo siguiente debes llamar:
        // placa = CrearPlaca();
        // RegistroDePrecios("RegistroPrecios.txt");
        if (celda == "Parking"){
            arr[f][c] = placa;
        } 
        else if (celda == "Via" || celda == "Pared" || celda == "Bloqueado" || celda == "SALIDA" || celda == "ENTRADA"){
            cout<<"No puede parquearse en esa celda ("<<celda<<"), escoja un Parking valido, regresando al menu\n";
            regresarmenu = true;
            return false;
        }
        else {
            cout<<"Ese lugar ya esta ocupado por el vehiculo con placa/id "<<celda<<", regresando al menu\n";
            regresarmenu = true;
            return false;
        }

        ofstream archivo_out(ruta);
        if (!archivo_out.is_open()){
            cout<<"No se pudo modificar "<<ruta<<" regresando al menu";
            regresarmenu = true;
            return false;
        }

        for (int i = 0; i < filas; i++){
            for (int j = 0; j < columnas; j++){
                archivo_out << arr[i][j];
                if (j < columnas - 1){
                    archivo_out << " ";
                }
            }
            archivo_out << "\n";
        }

        archivo_out.close();

        cout << "Vehiculo con placa/id "<<placa<<", ha sido agregado con exito! Regresando al menu\n";
        
        return true;
        
    } else if (accion == 's') {

        cout<<"\nPorfavor inserte la placa/id del vehiculo que quiere sacar (ej: ABC321)/(ej: 432)\n";
        cout<<"Opcion: ";
        cin>>placa;
        cout<<endl;

        if (celda != placa){
            cout<<"No hay ningun vehiculo en esta celda con la placa/id "<<placa<<".\n";
            regresarmenu = true;
            return false;
        } else {
            if (celda == "Parking"){
                cout<<"No hay ningun vehiculo en este parqueadero, regresando al menu\n";
                regresarmenu = true;
                return false;
            } 
            else if (celda == "Via" || celda == "Pared" || celda == "Bloqueado" || celda == "SALIDA" || celda == "ENTRADA"){
                cout<<"No se pueden quitar vehiculos de esta celda ("<<celda<<"), escoja un Parking ocupado valido, regresando al menu\n";
                regresarmenu = true;
                return false;
            }
            else { //4) la parte de cobrar al sacar un vehículo

                //Lee la funcion RegistroDePrecios que esta mas abajo
                //Aqui tienes que llamar a la funcion registro de precios y poner con ifstream que lea el archivo que creaste en RegistroDePrecios.
                //Que lea linea por linea (Usando solamente for no getline), y si se encuentra la placa elegida, cambiar el valor de preciototal por el valor que esta a la derecha de la placa (Osea el precio)

                cout<<"El precio para sacar su vehiculo del parqueadero es de "<<PrecioTotal<<" COP. Ingrese este precio exacto para sacar su vehículo o agregue mas dinero si quiere darnos propina. (El precio total se actualiza cada minuto, apurese.)\n";
                cin>>precio;
                propina = precio - PrecioTotal;
                if (precio < PrecioTotal){
                    cout<<"La cantidad no es suficiente, no puede sacar el vehiculo de parqueadero, regresando al menu\n";
                    regresarmenu = true;
                    return false;
                } else {
                    cout<<"Usted ha depositado "<<precio<<" COP y nos ha dado una propina de "<<propina<<" COP, ya puede sacar su vehiculo del parqueadero, hasta luego.\n";
                    arr[f][c] = "Parking";
                }
            }

            ofstream archivo_out(ruta);
            if (!archivo_out.is_open()){
                cout<<"No se pudo modificar "<<ruta<<" regresando al menu";
                regresarmenu = true;
                return false;
            }

            for (int i = 0; i < filas; i++){
                for (int j = 0; j < columnas; j++){
                    archivo_out << arr[i][j];
                    if (j < columnas - 1){
                        archivo_out << " ";
                    }
                }
                archivo_out << "\n";
            }

            archivo_out.close();

            cout <<"El vehiculo con placa/id: "<<celda<<", ha salido del parqueadero exitosamente, regresando al menu\n";
            
            //(3)Crear la imagen de carros

            //Pon aqui que cree un archivo nuevo con ofstream y que por cada renglon se guarde la placa que salio (espacio) precio total (espacio) propina y luego ponle cout<<endl;
            //Usa aqui tambien el modo append para que se guarde
            //Deberia quedar asi:
            //ABC123 1000 30
            //ABC12D 800 0
            //Y asi sucesivamente

            //(6)Eliminar el vehiculo que salió del parqueadero de la lista RegistroDePrecios
            //Ponle aqui en ofstream que edite el archivo RegistroDePrecios y que la placa que se eligio junto con el precio de la derecha, esa linea se borre del archivo
            //Asegurate de que el archivo se guarde con todos los cambios de las placas anteriores que han sido borradas

            return true;
        }
    } else {
        cout<<"Porfavor ingrese un comando valido, regresando al menu\n";
        regresarmenu = true;
        return false;
    }
}

//(2) RegistroDePrecios
bool RegistroDePrecios(string ruta){
    //Usando ofstream pon que cree y edite el archivo de registro de precios para hacer un registro de placas con su dinero que esten dentro del parqueadero
    //Pon que guarde cada placa creada y despues en la misma linea pon que si el elegirparq == 'c' o 'm' o 'b', se ponga (espacio) un valor total por cada placa, este
    //Se debe inicar en 0 y se sume + PrecioCarros, PrecioMotos o PrecioBicis respectivamente, luego pon un cout<<endl; para escribir en la siguiente linea
    //Usa el modo append en el archivo(Toma la estructura para crear el archivo como lo cree en cada uno de los CrearParqueaderos)
    //Deberia quedar asi:

    // FORMATO DEL ARCHIVO RegistroPrecios.txt:
    // ABC123 300
    // XYZ456 175
    //
    // Donde:
    // izquierda = placa
    // derecha = precio acumulado
}

bool ConsultarPlaca(string ruta, int filas, int columnas){
    ifstream archivo(ruta);
    if (!archivo.is_open()){
        cout<<ruta<<" No se pudo abrir correctamente el parqueadero, regresando al menu\n";
        regresarmenu = true;
        return false;
    }

    cout<<"\nPorfavor digite la placa/id que quiere buscar en el parqueadero\n";
    cin>>placa;

    string arr[100][100];

    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            if (!(archivo >> arr[i][j])){
                return false;
            }
        }
    }
    archivo.close();

    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            if (arr[i][j] == placa){
                cout<<"La placa/id "<<placa<<" esta en la fila "<<i+1<<" y columna "<<j+1<<".\n";
                return true;
            }
        }
    }

    cout<<"No se encontro el vehiculo con la placa/id "<<placa<<" en el parqueadero\n";
    regresarmenu = true;
    return false;
}
//5) VerImagenDeCarros()
bool VerImagenDeCarros(){
    //En esta variable debes leer el archivo de los vehiculos que saliero y luego en cout debe hacer un dibujito del vehiculo y abajo poner la placa del vehiculo que salio, el precio total y la propina (los valores del documento)
    //Asegurate que el sistema sepa si esa placa es un carro, moto o bici y hacer su dibujito, te deberia salir en consola algo como esto:
    //Debe quedarte algo asi:

    // ==================== CARRO ====================
    //        ______
    //       /|_||_\`.__
    //      (   _    _ _\
    //      =`-(_)--(_)-'
    // 
    // Placa: ABC123, Valor Total: 1000, Propina: 200


    // ==================== MOTO ====================
    //        __(o)
    //      _ \<_
    //     (_)/(_)
    // 
    // Placa: ABC12D, Valor Total: 800, Propina: 100


    // ==================== BICICLETA ====================
    //      __o
    //    _ \<_
    //   (_)/(_)
    // 
    // Placa: 123456, Valor Total: 300, Propina: 50


return true;
}

int main(){
    // Crear archivos solo si no existen
    ifstream testc("ParkingCarros.txt");
    if (!testc.good()){
        CrearParqueaderoCarros("ParkingCarros.txt");
    }
    testc.close();
    cout<<endl;

    ifstream testm("ParkingMotos.txt");
    if (!testm.good()){
        CrearParqueaderoMotos("ParkingMotos.txt");
    }
    testm.close();
    cout<<endl;

    ifstream testb("ParkingBicis.txt");
    if (!testb.good()){
        CrearParqueaderoBicis("ParkingBicis.txt");
    }
    testb.close();
    cout<<endl;

    // Crear o revisar el archivo de registro de precios
    // TODO: aquí debe ir la función que cree RegistroPrecios.txt si no existe


    do{
        cout<<endl;
        MostrarElMenu("Parqueadero Skibidi");

        if (opcion == 'm'){
            regresarmenu = true;
        }else if (opcion == 'l'){
            regresarmenu = false;
            ElegirParq();
            if (elegirparq == 'c'){
                VerLista("ParkingCarros.txt", 16, 18);
            } else if (elegirparq == 'm'){
                VerLista("ParkingMotos.txt", 16, 15);
            } else if (elegirparq == 'b'){
                VerLista("ParkingBicis.txt", 3, 15);
            } else {
                cout<<"\nSe ingreso un comando no valido, regresando al menu";
                regresarmenu = true;
            }
            cout<<"\nVolviendo al menu\n";
            regresarmenu = true;
        }else if (opcion == 'v'){
            regresarmenu = false;
            ElegirParq();
            if (elegirparq == 'c'){
                AddExitVehiculo("ParkingCarros.txt", 16, 18);
            } else if (elegirparq == 'm'){
                AddExitVehiculo("ParkingMotos.txt", 16, 15);
            } else if (elegirparq == 'b'){
                AddExitVehiculo("ParkingBicis.txt", 3, 15); 
            } else {
                cout<<"\nSe ingreso un comando no valido, regresando al menu";
                regresarmenu = true;
            }
            cout<<"\nVolviendo al menu\n";
            regresarmenu = true;
        } else if (opcion == 'c'){
            regresarmenu = false;
             ElegirParq();
            if (elegirparq == 'c'){
                ConsultarPlaca("ParkingCarros.txt", 16, 18);
            } else if (elegirparq == 'm'){
                ConsultarPlaca("ParkingMotos.txt", 16, 15);
            } else if (elegirparq == 'b'){
                ConsultarPlaca("ParkingBicis.txt", 3, 15);
            } else {
                cout<<"\nSe ingreso un comando no valido, regresando al menu";
                regresarmenu = true;
            }
            cout<<"\nVolviendo al menu\n";
            regresarmenu = true;
        } else if (opcion == 'i'){
            VerImagenDeCarros();
            regresarmenu = false;
        } else if (opcion == 's'){
            regresarmenu = false;
            cout<<"Adios\n";
        } else {
            cout<<"Ingrese un comando valido, regresando al menu\n";
            regresarmenu = true;
        }
    }while (regresarmenu == true);

    return 0;
}