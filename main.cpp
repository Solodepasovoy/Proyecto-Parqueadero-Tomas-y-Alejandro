#include <iostream>
#include <fstream>
#include <string>
using namespace std;

char opcion;
char elegirparq;
bool regresarmenu = false;
int fila;
int columna;
string placa;

char MostrarElMenu(string NombreParq, int preciocarros, int preciomotos, int preciosbici){
    cout<<"Bienvenido a "<<NombreParq<<"!\n";
    cout<<"Cobramos  a carros $"<<preciocarros<<" COP/min, a motos "<<preciomotos<<" y a bicicletas "<<preciosbici<<".\n";
    cout<<"Que desearia hacer?"<<endl;
    cout<<endl;
    cout <<"m - presione m para ver este menu de nuevo\n";
    cout <<"l - ver lista de parqueaderos y disponibilidad\n";
    cout <<"v - agregar o sacar un vehículo al parqueadero\n";
    cout <<"p - consultar placa/id y en que espacio del parqueadero esta\n";
    cout <<"d - consultar el valor del dinero total del parqueadero para cierto vehículo (se actualiza cada minuto)\n";
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
        //Esto despues lo cambio por una funcion que me de la placa de numeros aleatorios, deja esto aqui
        cout<<"\nPorfavor inserte una nueva placa/id (ej: ABC321)/(ej: 432)\n";
        cout<<"Opcion: ";
        cin>>placa;
        cout<<endl;

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
            cout<<"La placa/id ingresada no coincide con el vehiculo en esa posicion\n";
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
            else {
                arr[f][c] = "Parking";
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
            return true;
        }
    } else {
        cout<<"Porfavor ingrese un comando valido, regresando al menu\n";
        regresarmenu = true;
        return false;
    }
}

bool ConsultarPlaca(){
return true;
}

bool ConsultarValor(){
return true;
}

int main(){
    CrearParqueaderoCarros("ParkingCarros.txt");
    cout<<endl;
    CrearParqueaderoMotos("ParkingMotos.txt");
    cout<<endl;
    CrearParqueaderoBicis("ParkingBicis.txt");
    cout<<endl;

    do{
        cout<<endl;
        MostrarElMenu("Parqueadero Skibidi",300,175,80);

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
        } else if (opcion == 'p'){
            regresarmenu = false;
        } else if (opcion == 'd'){
            regresarmenu = false;
        } else if (opcion == 'i'){
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