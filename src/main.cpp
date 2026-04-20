#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
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

//Mostrar la hora actual
string ObtenerHora(){
    time_t ahora = time(0);
    tm* tiempoLocal = localtime(&ahora);

    int horas = tiempoLocal->tm_hour;
    int minutos = tiempoLocal->tm_min;
    int segundos = tiempoLocal->tm_sec;

    string hora = "";
    if (horas < 10) hora += "0";
    hora += to_string(horas) + ":";
    if (minutos < 10) hora += "0";
    hora += to_string(minutos) + ":";
    if (segundos < 10) hora += "0";
    hora += to_string(segundos);

    return hora;
}

//Mostrar el menu (Avance Tomas)
char MostrarElMenu(string NombreParq){
    cout<<"Hora actual: "<<ObtenerHora()<<"\n";
    cout<<"Bienvenido a "<<NombreParq<<"!\n";
    cout<<"Cobramos a carros $"<<preciocarros<<" COP/min, a motos "<<preciomotos<<" y a bicicletas "<<preciobici<<".\n";
    cout<<"Que desearia hacer?"<<endl;
    cout<<endl;
    cout <<"m - presione m para ver este menu de nuevo\n";
    cout <<"l - ver lista de parqueaderos y disponibilidad\n";
    cout <<"v - agregar o sacar un vehiculo al parqueadero\n";
    cout <<"c - consultar placa/id y en que espacio del parqueadero esta\n";
    cout <<"i - ver la factura de los vehiculos que han salido del parqueadero\n";
    cout <<"s - salir\n";
    cout <<"Opcion: ";
    cin>>opcion;
    cout<<endl;
    return opcion;
}

//Crear parqueadero (Avance Tomas)
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

//Crear parqueadero motos (Avance Tomas)
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

//Crear parqueadero bicicletas (Avance Tomas)
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

//Ver la tabla del parqueadero seleccionado (Avance Tomas)
bool VerLista(string ruta, int filas, int columnas){
    ifstream archivo(ruta);
    if (!archivo.is_open()){
        cout<<"No se pudo leer "<<ruta<<" regresando al menu";
        regresarmenu = true;
        return false;
    }

    string arr[100][100]; 

    cout << "    ";

    for (int j = 0; j < columnas; j++) {
        cout << j + 1;
        if (j < columnas - 1) {
            cout << "   |   ";
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

//Funcion para elegir parqueadero (Avance Tomas)
char ElegirParq(){
    cout<<"Cual parqueadero quiere elegir para hacer esta accion?\n";
    cout<<"Presione c para carros, m para motos y b para bicicletas\n";
    cout<<"Opcion: ";
    cin>>elegirparq;
    return elegirparq;
}

//Crear Placa (Avance Alejo)
string CrearPlaca(){
    string ruta;
    int filas, columnas;
    if (elegirparq == 'c'){
        ruta = "../data/ParkingCarros.txt";
        filas = 16; columnas = 18;
    } else if (elegirparq == 'm'){
        ruta = "../data/ParkingMotos.txt";
        filas = 16; columnas = 15;
    } else {
        ruta = "../data/ParkingBicis.txt";
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

//Actualizar Precios (Avance Alejo)
void ActualizarPrecios(int* pPrecioCarros, int* pPrecioMotos, int* pPrecioBici){
    string lineas[1000];
    int total = 0;
    ifstream leer("../data/RegistroPrecios.txt");
    string p, tipo, horaGuardada;
    int precio;

    for (int i = 0; i < 1000; i++){
        if (!(leer >> p >> tipo >> precio >> horaGuardada)) break;

        if (tipo == "c") precio += *pPrecioCarros;
        else if (tipo == "m") precio += *pPrecioMotos;
        else if (tipo == "b") precio += *pPrecioBici;
        lineas[total] = p + " " + tipo + " " + to_string(precio) + " " + horaGuardada;
        total++;
    }
    leer.close();

    ofstream escribir("../data/RegistroPrecios.txt");
    for (int i = 0; i < total; i++){
        escribir << lineas[i] << "\n";
    }
    escribir.close();
}

//Hilo de Precios (Avance Alejo)
void HiloPrecios(){
    while (true){
        this_thread::sleep_for(chrono::minutes(1)); // espera 1 minuto
        ActualizarPrecios(&preciocarros, &preciomotos, &preciobici);
    }
}

//RegistroDePrecios (Avance Alejo)
bool RegistroDePrecios(string ruta){
    ofstream archivo(ruta, ios::app);
    if (!archivo.is_open()){
        cout<<"No se pudo abrir el registro de precios\n";
        return false;
    }

    string horaIngreso = ObtenerHora();
    if (elegirparq == 'c'){
        archivo << placa << " c 0 " << horaIngreso <<"\n";
    } else if (elegirparq == 'm'){
        archivo << placa << " m 0 " << horaIngreso << "\n";
    } else if (elegirparq == 'b'){
        archivo << placa << " b 0 " << horaIngreso << "\n";
    }

    archivo.close();
    return true;
}


//Agregar o sacar vehiculo (Avance Tomas y Alejo)
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
    //puse esto para que no se rompa si se ingresa un string o un vacio
    if (!(cin >> fila >> columna)) {
        cout << "\nEntrada invalida. Cerrando programa...\n";
        exit(0);
    }

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
        RegistroDePrecios("../data/RegistroPrecios.txt");

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
        string horaEntrada = ObtenerHora();
        cout << "Vehiculo con placa/id "<<placa<<", ha sido agregado con exito! Entro a las "<<horaEntrada<<". Regresando al menu\n";
        return true;
        
    } else if (accion == 's') {

        cout<<"\nPorfavor inserte la placa/id del vehiculo que quiere sacar (ej: ABC321)/(ej: 654321)\n";
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
            else { //Cobrar al sacar un vehículo (Avance Alejo)
                ifstream regArchivo("../data/RegistroPrecios.txt");
                string regPlaca, regTipo;
                int regPrecio;
                PrecioTotal = 0;
                for (int i = 0; i < 1000; i++){
                    string regHora;
                    if (!(regArchivo >> regPlaca >> regTipo >> regPrecio >> regHora)) break;
                    if (regPlaca == celda){
                        PrecioTotal = regPrecio;
                        break;
                    }
                }
                regArchivo.close();

                cout<<"El precio para sacar su vehiculo del parqueadero es de "<<PrecioTotal<<" COP. Ingrese este precio exacto para sacar su vehiculo o agregue mas dinero si quiere darnos propina. (Porfavor ingrese un numero entero)\n";
                cin>>precio;
                propina = precio - PrecioTotal;
                if (precio < PrecioTotal){
                    cout<<"La cantidad no es suficiente, no puede sacar el vehiculo de parqueadero, regresando al menu\n";
                    regresarmenu = true;
                    return false;
                } else {
                    cout<<"Usted ha depositado $"<<precio<<" COP y nos ha dado una propina de $"<<propina<<" COP, ya puede sacar su vehiculo del parqueadero, hasta luego.\n";
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

            string horaSalida = ObtenerHora();
            cout <<"El vehiculo con placa/id: "<<celda<<", ha salido del parqueadero exitosamente a las "<<horaSalida<<", regresando al menu\n";    
            
            //Guardar factura (Avance Alejo y Tomás)
            ofstream factura("../data/Facturas.txt", ios::app);

            if (elegirparq == 'c'){
                factura << "==================== CARRO ====================\n";
                factura << "       ______\n";
                factura << "      /|_||_|\\`.__\n";
                factura << "     (   _    _ _\\\n";
                factura << "     =`-(_)--(_)-'\n";
                factura << "Placa: " << celda << " Precio Total De Parqueadero: " << PrecioTotal << " Propina: " << propina << " Hora de salida: " << horaSalida <<"\n";
            } else if (elegirparq == 'm'){
                factura << "==================== MOTO ====================\n";
                factura << "           _\n";
                factura << "        __(o)\n";
                factura << "      _ \\<_\n";
                factura << "     (_)/(_)\n";
                factura << "Placa: " << celda << " Precio Total De Parqueadero: " << PrecioTotal << " Propina: " << propina << " Hora de salida: " << horaSalida <<"\n";
            } else if (elegirparq == 'b'){
                factura << "==================== Bici ====================\n";
                factura << "        __o\n";
                factura << "      _ \\<_\n";
                factura << "     (_)/(_)\n";
                factura << "Placa: " << celda << " Precio Total De Parqueadero: " << PrecioTotal << " Propina: " << propina << " Hora de salida: " << horaSalida <<"\n";
            }
            factura.close();

            //Eliminar el vehiculo que salio del parqueadero de la lista RegistroDePrecios (Avance Alejo)
           string lineasRegistro[1000];
         int totalLineas = 0;
         ifstream leerRegistro("../data/RegistroPrecios.txt");
         string rPlaca, rTipo, rHora;
         int rPrecio;
     for (int i = 0; i < 1000; i++){
        if (!(leerRegistro >> rPlaca >> rTipo >> rPrecio >> rHora)) break;
     if (rPlaca != celda){
        lineasRegistro[totalLineas] = rPlaca + " " + rTipo + " " + to_string(rPrecio) + " " + rHora;
        totalLineas++;
    }
}
leerRegistro.close();

ofstream escribirRegistro("../data/RegistroPrecios.txt");
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

//Consultar la placa y en que parte del parqueadero esta (Avance Tomas)
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

//VerImagenDeCarros (Avance Tomas) 
bool VerImagenDeCarros(string ruta) {
    ifstream archivo(ruta);

    if (!archivo.is_open()) {
        cout << "No se puede abrir " << ruta << " regresando al menu";
        regresarmenu = true;
        return false;
    }
    char c;
    while (archivo.get(c)) {
        cout << c;
    }
    return true;
}

//Bloque principal (Avance Tomas y Alejo)
int main(){
    ifstream testc("../data/ParkingCarros.txt");
    if (!testc.good()){
        CrearParqueaderoCarros("../data/ParkingCarros.txt");
    }
    testc.close();
    cout<<endl;

    ifstream testm("../data/ParkingMotos.txt");
    if (!testm.good()){
        CrearParqueaderoMotos("../data/ParkingMotos.txt");
    }
    testm.close();
    cout<<endl;

    ifstream testb("../data/ParkingBicis.txt");
    if (!testb.good()){
        CrearParqueaderoBicis("../data/ParkingBicis.txt");
    }
    testb.close();
    cout<<endl;

    ifstream testreg("../data/RegistroPrecios.txt");
    if (!testreg.good()){
        ofstream crear("../data/RegistroPrecios.txt");
        crear.close();
    }
    testreg.close();

    thread hiloPrecios(HiloPrecios);
    hiloPrecios.detach(); 

    do{
        cout<<endl;
        MostrarElMenu("Parqueadero Sigma");

        if (opcion == 'm'){
            regresarmenu = true;
        }else if (opcion == 'l'){
            regresarmenu = false;
            ElegirParq();
            if (elegirparq == 'c'){
                VerLista("../data/ParkingCarros.txt", 16, 18);
            } else if (elegirparq == 'm'){
                VerLista("../data/ParkingMotos.txt", 16, 15);
            } else if (elegirparq == 'b'){
                VerLista("../data/ParkingBicis.txt", 3, 15);
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
                AddExitVehiculo("../data/ParkingCarros.txt", 16, 18);
            } else if (elegirparq == 'm'){
                AddExitVehiculo("../data/ParkingMotos.txt", 16, 15);
            } else if (elegirparq == 'b'){
                AddExitVehiculo("../data/ParkingBicis.txt", 3, 15); 
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
                ConsultarPlaca("../data/ParkingCarros.txt", 16, 18);
            } else if (elegirparq == 'm'){
                ConsultarPlaca("../data/ParkingMotos.txt", 16, 15);
            } else if (elegirparq == 'b'){
                ConsultarPlaca("../data/ParkingBicis.txt", 3, 15);
            } else {
                cout<<"\nSe ingreso un comando no valido, regresando al menu";
                regresarmenu = true;
            }
            cout<<"\nVolviendo al menu\n";
            regresarmenu = true;
        } else if (opcion == 'i'){
            regresarmenu = false;
            VerImagenDeCarros("../data/Facturas.txt");
            cout<<"\nVolviendo al Menu\n";
            regresarmenu = true;
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