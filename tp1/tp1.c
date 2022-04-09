 #include<stdlib.h>
 #include<stdio.h>
 #include<string.h>

int definirColumna(char caracter){
    char* cadena0="0"; 
    char* cadena1="1234567";
    char* cadena2="89";
    char* cadena3="abcdefABCDEF";
    char* cadena4="xX";
    int columna;
    char cadenaAux[2];
    cadenaAux[1]='\0';
    cadenaAux[0]=caracter;

   if(strstr(cadena0,cadenaAux)){
       return 0;
   }
   else if (strstr(cadena1,cadenaAux)){
       return 1;
   }
   else if (strstr(cadena2,cadenaAux)){
       return 2;
   }
   else if (strstr(cadena3,cadenaAux)){
       return 3;
   }
   else if (strstr(cadena4,cadenaAux)){
       return 4;
   }
   else{
       return -1;
   }

    return columna;
}


int modificarEstado(int estado, char caracter){
    int columna;
    int matriz[6][5]= {
        {1,2,2,6,6},
        {5,5,6,6,3},
        {2,2,2,6,6},
        {4,4,4,4,6},
        {4,4,4,4,6},
        {5,5,6,6,6}
    };    
    if (estado==6){
        return 6;
    }
    else{
        columna=definirColumna(caracter);
        if(columna!=-1){
            return matriz[estado][columna];
        }
        else{
            return 6;
        }
    }

}



char* definirPalabra(int estado){
    switch(estado){
        case 1: return "OCTAL";break;
        case 2: return "DECIMAL";break;
        case 4: return "HEXADECIMAL";break;
        case 5: return "OCTAL";break;
        default: return "NO RECONOCIDA";
    }
}


 int main(){

    //defino variable para identificar los estados
    int estado=0;
    //defino variable para recolectar los caracteres leidos
    char caracter[2];
    caracter[1]='\0';
    //defino variable para crear la cadena que vamos leyendo
    char cadena[10];
    //asigno memoria al vector
    memset(cadena,0,10);
    //asigno variable para registrar el tipo de palabra encontrada
    char* tipoPalabra;

    //abro el archivo de entrada definiendo el puntero al archivo
    FILE *file;
    file = fopen("entrada.txt", "r");

    //me fijo si el archivo existe
    if (file == NULL)
    {
        printf("Error al abrir el archivo entrada.txt");
        system ("pause");    
        return -1;
    }

    //leo el primer caracter
    caracter[0]=getc(file);
    //mientras no se termine el archivo, sigo leyendo
    while (caracter[0]!=EOF){
        //si el caracter es distinto de ',' hay una transición
        if(caracter[0]!=','){
            //modifico el estado segun el caracter
            estado=modificarEstado(estado,caracter[0]);
            //voy guardando la cadena que estoy formando
            strcat(cadena,caracter);

        }
        //si es una ',' entonces terminé de leer la palabra
        else{
            //identifico el tipo de palabra
            tipoPalabra=definirPalabra(estado);
            //grabo la palabra y el tipo en el archivo de salida
            //grabarEnArchivo(cadena,tipoPalabra);                        TODO
            printf("la palabra %s es %s\n",cadena,tipoPalabra);
            //reseteo todo
            estado=0;
            free(cadena);
            //asigno nuevamente memoria para crear la siguiente cadena
            memset(cadena,0,10);
        }
        caracter[0]=getc(file);
    }
    
  



    //grabo la ultima palabra
    //grabarEnArchivo(cadena,tipoPalabra);    TODO
    free(cadena);
    system ("pause");    
    return 0;
 }