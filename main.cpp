// Alejo: en este archivo debes completar:
//
//Antes de iniciar si tienes los archivos de excel dentro de la carpeta borralos
//Recuerda que apenas acabes, o si quieres probar si funciona o debes correrlo
//Para correrlo presiona Windows+R, escribe cmd, luego pon "cd (espacio) (copia la direccion de tu carpeta de parqueadero y pegala)" 
//Luego pon "g++ main.cpp" y finalmente pon "a.exe". Asi lo corres
//Si tienes alguna duda o no sabes como integrar las funciones al main, preguntale a CHATGPT o a mi
//
//INSTRUCCIONES:
//
// 1) CrearPlaca()          <- HECHO
// 2) RegistroDePrecios()   <- HECHO
// 3) Guardar la factura de los carros que salen  <- HECHO
// 4) la parte de cobrar al sacar un vehículo     <- HECHO
// 5) VerImagenDeCarros()   <- PENDIENTE
// 6) Eliminar el vehiculo que salió del parqueadero <- PENDIENTE
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
#include <cstdlib>
#include <ctime>
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
    cout <<"v - agregar o sacar un vehiculo al parqueadero\n";
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
    string ruta;
    int filas, columnas;
    if (elegirparq == 'c'){
        ruta = "ParkingCarros.txt";
        filas = 16; columnas = 18;
    } else if (elegirparq == 'm'){
        ruta = "ParkingMotos.txt";
        filas = 16; columnas = 15;
    } else {
        ruta = "ParkingBicis.txt";
        filas = 3; columnas = 15;
    }

    string placasExistentes[500];
    int totalPlacas = 0;
    ifstream archivo(ruta);
    if (archivo.is_open()){
        string celda;
        for (int i = 0; i < filas; i++){
            for (int j = 0; j < columnas; j++){
                if (archivo >> celda){
                    if (celda != "Parking" && celda != "Pared" && celda != "Via" && 
                        celda != "Bloqueado" && celda != "ENTRADA" && celda != "SALIDA" && 
                        celda != "Entrada" && celda != "Salida"){
                        placasExistentes[totalPlacas] = celda;
                        totalPlacas++;
                    }
                }
            }
        }
        archivo.close();
    }

    srand(time(0));
    string nuevaPlaca;
    bool duplicada = true;

    while (duplicada){
        nuevaPlaca = "";

        if (elegirparq == 'c'){
            for (int i = 0; i < 3; i++)
                nuevaPlaca += (char)('A' + rand() % 26);
            for (int i = 0; i < 3; i++)
                nuevaPlaca += (char)('0' + rand() % 10);
        } else if (elegirparq == 'm'){
            for (int i = 0; i < 3; i++)
                nuevaPlaca += (char)('A' + rand() % 26);
            for (int i = 0; i < 2; i++)
                nuevaPlaca += (char)('0' + rand() % 10);
            nuevaPlaca += (char)('A' + rand() % 26);
        } else {
            for (int i = 0; i < 6; i++)
                nuevaPlaca += (char)('0' + rand() % 10);
        }

        duplicada = false;
        for (int i = 0; i < totalPlacas; i++){
            if (placasExistentes[i] == nuevaPlaca){
                duplicada = true;
                break;
            }
        }
    }

    placa = nuevaPlaca;
    cout<<"Placa generada: "<<placa<<endl;
    return placa;
}

//(2) RegistroDePrecios
bool RegistroDePrecios(string ruta){
    ofstream archivo(ruta, ios::app);
    if (!archivo.is_open()){
        cout<<"No se pudo abrir el registro de precios\n";
        return false;
    }

    if (elegirparq == 'c'){
        archivo << placa << " " << preciocarros << "\n";
    } else if (elegirparq == 'm'){
        archivo << placa << " " << preciomotos << "\n";
    } else if (elegirparq == 'b'){
        archivo << placa << " " << preciobici << "\n";
    }

    archivo.close();
    return true;
}

bool RegistroDePrecios(string ruta);

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
       
        placa = CrearPlaca();
        RegistroDePrecios("RegistroPrecios.txt");

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
            else { //4) Cobrar al sacar un vehículo
                ifstream regArchivo("RegistroPrecios.txt");
                string regPlaca;
                int regPrecio;
                PrecioTotal = 0;
                for (int i = 0; i < 1000; i++){
                    if (!(regArchivo >> regPlaca >> regPrecio)) break;
                    if (regPlaca == celda){
                        PrecioTotal = regPrecio;
                        break;
                    }
                }
                regArchivo.close();

                cout<<"El precio para sacar su vehiculo del parqueadero es de "<<PrecioTotal<<" COP. Ingrese este precio exacto para sacar su vehiculo o agregue mas dinero si quiere darnos propina.\n";
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
            
            //(3) Guardar factura
            ofstream factura("Facturas.txt", ios::app);
            factura << celda << " " << PrecioTotal << " " << propina << "\n";
            factura.close();

            //(6) Eliminar el vehiculo que salio del parqueadero de la lista RegistroDePrecios
           string lineasRegistro[1000];
         int totalLineas = 0;
         ifstream leerRegistro("RegistroPrecios.txt");
         string rPlaca;
         int rPrecio;
     for (int i = 0; i < 1000; i++){
        if (!(leerRegistro >> rPlaca >> rPrecio)) break;
     if (rPlaca != celda){
        lineasRegistro[totalLineas] = rPlaca + " " + to_string(rPrecio);
        totalLineas++;
    }
}
leerRegistro.close();

ofstream escribirRegistro("RegistroPrecios.txt");
for (int i = 0; i < totalLineas; i++){
    escribirRegistro << lineasRegistro[i] << "\n";
}
escribirRegistro.close();

            return true;
        }
    } else {
        cout<<"Porfavor ingrese un comando valido, regresando al menu\n";
        regresarmenu = true;
        return false;
    }
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

//5) VerImagenDeCarros() - Pendiente
bool VerImagenDeCarros(){
    return true;
}

int main(){
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

    ifstream testreg("RegistroPrecios.txt");
    if (!testreg.good()){
        ofstream crear("RegistroPrecios.txt");
        crear.close();
    }
    testreg.close();

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
