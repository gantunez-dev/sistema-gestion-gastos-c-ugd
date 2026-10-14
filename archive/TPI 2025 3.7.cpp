#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int dia;
    int mes;
    int anio;
} Fecha;

typedef struct {
    unsigned long long codigo;
    char nombre[50];
} Categoria;

typedef struct {
    long long dni;
    char nombre[50];
} Persona;

typedef struct {
    unsigned long long codGasto;
    int tipoGasto;
    char desc[50];
    Categoria categoria;
    double monto;
    Fecha fechaGasto;
    int cuotasTotales;
    int cuotaActual;
    Persona persona;
    int estadoCuota;
    double restantanteCuota;
} Gasto;

typedef struct {
    unsigned long long codGasto;
    int medioPago;
    double importe;
    Fecha fechaPago;
} Pago;

typedef struct {
    unsigned long long codIngreso;
    char concepto[50];
    double monto;
    Fecha fecha;
    Persona persona;
} Ingreso;

Ingreso ingreso;
Gasto gasto,gastoaux;
Pago pago;
Fecha fecha;

// PROTOTIPOS ///////////////////////
void cargarGasto(); // CARGAR GASTO
void cargarIngreso(); // CARGAR INGRESO
void registrarPago(); // REGISTRAR PAGO
void listarGastoseIngresos(); // LISTAR GASTOS E INGRESOS
void consultasyReportes(); // CONSULTAS Y REPORTES
void agregarCategoria(); // AGREGAR CATEGORIA

// PROTOTIPOS *********
void guardarGasto(Gasto gasto);
int comprobacion_fecha(int aux_anio, int aux_mes, int aux_dia);
void ver_arch_gastos(); // Unicamente para ver como queda en el archivo gastos.dat
unsigned long long buscar_idGasto();
unsigned long long buscar_idCategoria();
unsigned long long buscar_idIngreso();
void registroCategoria(char*,unsigned long long,char*);
void guardarIngreso(Ingreso ingreso);
void ver_arch_ingresos(); // Unicamente para ver como queda en el archivo ingresos.dat
void ver_arch_pagos();
void listarGastos();
void listarIngresos();
void filtrarPorTipo();
void filtrarPorCategoria();
void filtrarPorMes();
void gastosPorCategoria();
void gastosPorMesYAnio();
void ingresosPorPersona();
void saldoMensual();
void gastosPendientes();
void pagosPorMedioDePago();
void gastosConSaldoIncompleto();
void categoriasMasCostosas();
void proyeccionMensual();
void resumenGeneral();

// PROTOTIPOS -----------------
void filtroPorMes(int);
double digitos(char*);
long long digitosDNI(char*);
void listaCategorias();
void listaGastos();
int digitosC(char*r);

int main() {
    char copc[1];
    int opcp, zxxz = 1;
    
    while (zxxz) {
        system("cls");
        printf("\nSistema De Gestion De Gastos Personales O Familiares\n--------MENU PRINCIPAL--------\n\n1. Registrar Gasto\n2. Registrar Ingreso\n3. Registrar Pago\n4. Listar Gastos E Ingresos\n5. Consultas y Reportes\n6. Salir\n\nElija Una Opcion: ");
        fflush(stdin);
        gets(copc);
        
        opcp = atoi(copc);
        
        switch (opcp) {
            case 1:
                system("cls");
                //printf("------------------\n1.REGISTRAR GASTO\n------------------");
                cargarGasto();
                ver_arch_gastos(); // quitar luego
                break;
            case 2:
                system("cls");
                //printf("---------------------\n2.REGISTRAR INGRESO\n---------------------");
                cargarIngreso();
                ver_arch_ingresos(); // quitar luego
                break;
            case 3:
                system("cls");
                //printf("------------------\n3.REGISTRAR PAGO\n------------------");
                registrarPago();
                ver_arch_pagos(); // quitar luego
                break;
            case 4:
                system("cls");
                //printf("------------------\n4.LISTAR GASTOS E INGRESOS\n------------------");
                listarGastoseIngresos();
                break;    
            case 5:
                system("cls");
                //printf("------------------\n5.CONSULTAS Y REPORTES\n------------------");
                consultasyReportes();
                break;    
            case 6:
                system("cls");
                printf("\nSALIENDO .....\n\n");
                zxxz = 0;
                break;                
            default:
                printf("\nIngrese Un Numero Valido Del 1-6 De Tipo Entero\n\n");
                system("PAUSE");
        }
    }
    return 0;
}

///////////////////////////////////////// REGISTRAR GASTO //////////////////////////////////////////////////////////////////////////////////////////

void cargarGasto(){
    FILE *f2;
    int s=1, c, aux_anio, aux_mes,aux_dia,cnt,opc,i,ac,ca,comp_corr,auxfecha;
    unsigned long long id,idC,IDaux;
    char Cad2[1000],montox[10],Cad4[5],Cad8[9],Cad9[1000],Cad3[50];
    
    while(s){
    	
    	cnt=1;
        if((f2 = fopen("gastos.dat", "ab")) == NULL){
            printf("\nError Al Abrir El Archivo");
            system("PAUSE");
        }else{
        	fread(&gasto,sizeof(Gasto),1,f2);
        	fclose(f2);
            // Obtener el proximo ID disponible
            id = buscar_idGasto();
            gasto.codGasto = id;
            
            while(cnt){
            	
            	c=1;
				while(c){
            		
            		system("cls");
            		printf("------------------\n1.REGISTRAR GASTO\n------------------");
	        		printf("\nIngrese El Tipo De Gasto\n\n1. Gasto Fijo\n2. Gasto Ocasional\n3. Gasto Temporal\n4. Gasto Anual\n\nElija Una Opcion: ");
	        		fflush(stdin);
	        		gets(Cad4);
					comp_corr=digitosC(Cad4);
					opc=atoi(Cad4);
					if((opc<1)||(comp_corr==0)){
						system("cls");
            			printf("\nIngrese Correctamente El Tipo De Gasto, Solo Puede Ser Numeros Enteros\n");
            			system("PAUSE");
            			system("cls");
					}else{
						c=0;
					}	
				}
            	
	            system("cls");
	            printf("------------------\n1.REGISTRAR GASTO\n------------------\n");
	            printf("\nID De Gasto: %llu", id); // Para debug
	            
	            switch(opc){
					case 1:
						strcpy(Cad3,"Fijo");
						printf("\n\nTipo De Gasto: Fijo");
						i=1;
						cnt=0;
						break;
					case 2:
						strcpy(Cad3,"Ocasional");
						printf("\n\nTipo De Gasto: Ocasional");
						cnt=0;
						i=2;
						break;
					case 3:
						strcpy(Cad3,"Temporal");
						printf("\n\nTipo De Gasto: Temporal");
						cnt=0;
						i=3;
						break;
					case 4:
						strcpy(Cad3,"Anual");
						printf("\n\nTipo De Gasto: Anual");
						cnt=0;
						i=4;
						break;					
					default:
						system("cls");
						printf("\nIngrese Un Numero Valido Del 1-4 De Tipo Entero\n\n");
						system("PAUSE");
						system("cls");
				}
            } 
				
            if((f2 = fopen("gastos.dat", "r+b")) != NULL){
            	if(fread(&gasto, sizeof(Gasto), 1, f2)== 0){
                
                fclose(f2);
                registroCategoria(Cad2,id,Cad3);
                strcpy(gasto.categoria.nombre,Cad2);
            	
            	idC = buscar_idCategoria();
            	gasto.categoria.codigo = idC;
            	
            	}else{
            		fclose(f2);
            		ac=1;
					while(ac){
						listaCategorias();
						fflush(stdin);
						scanf("%llu",&IDaux);
						
	            		if(IDaux==0){
	            			//printf("\n\nEntro a 0");
	            			system("cls");
	            			printf("------------------\n1.REGISTRAR GASTO\n------------------\n");
	            			printf("\nID De Gasto: %llu\n", id);
							printf("\nTipo De Gasto: %s",Cad3);
	            			registroCategoria(Cad2,id,Cad3);
                			strcpy(gasto.categoria.nombre,Cad2);
	            			
	            			idC = buscar_idCategoria();
            				gasto.categoria.codigo = idC;
            				
	            			ac=0;
	            			
						}else{
							if(IDaux<0){
								system("cls");
								printf("\nIngrese Un ID Valido, Entero Superior A 0\n");
								system("PAUSE");
								system("cls");
							}else{
								//printf("\n\nEntro a Lista");
								ca=1;
								if((f2=fopen("gastos.dat","r+b"))==NULL){
									printf("\nError al abrir el archivo");
									system("PAUSE");
								}else{
									fread(&gastoaux,sizeof(Gasto),1,f2);
									while((ca)&&(!feof(f2))){
										if(gastoaux.categoria.codigo==IDaux){
											ca=0;
											ac=0;
											strcpy(Cad2,gastoaux.categoria.nombre);
											idC=gastoaux.categoria.codigo;
										}
										fread(&gastoaux,sizeof(Gasto),1,f2);
									}
									fclose(f2);
									system("cls");
									printf("------------------\n1.REGISTRAR GASTO\n------------------\n");
									printf("\nID De Gasto: %llu\n",id);
									printf("\nTipo De Gasto: %s\n",Cad3);
									printf("\nPertenece A La Categoria: %s\n",Cad2);
									if(ca){
										system("cls");
										printf("\nID No Encontrado, Ingrese Correctamente el ID\n\n");
										system("PAUSE");
										system("cls");
										
										printf("------------------\n1.REGISTRAR GASTO\n------------------\n");
										printf("\nID De Gasto: %llu\n", id);
										printf("\nTipo De Gasto: %s",Cad3);
									}
								}
								
							}	
						}	
					}
				}
				gasto.categoria.codigo=idC;
				gasto.tipoGasto=i;
				strcpy(gasto.categoria.nombre,Cad2);
				
				printf("\nID De Categoria: %llu\n", idC); // Para debug
				c=1;
				while(c){
					
					printf("\nIngrese Una Descripcion Del Gasto: ");
					fflush(stdin);
					gets(Cad2);
	 	           
					if((strlen(Cad2)>49)||(Cad2[0]=='\0')||(Cad2[0]==32)){
	 	        
						system("cls");
						printf("\nNo Se Permite Mas De 50 Caracteres En La Descripcion O Con Espacios Al Inicio, Por Favor, Vuelva A Ingresarlo\n\n");
						system("PAUSE");
						system("cls");
						
						printf("------------------\n1.REGISTRAR GASTO\n------------------\n");
						printf("\nID De Gasto: %llu\n", id);
						printf("\nTipo De Gasto: %s\n",Cad3);
						printf("\nPertenece A La Categoria: %s\n",gasto.categoria.nombre);
						printf("\nID De Categoria: %llu\n", idC);
						fflush(stdin);
					}else{
						Cad2[strcspn(Cad2, "\n")] = 0;
						strcpy(gasto.desc, Cad2);
						c=0;
					}
				}
  	          
				c=1;
				while(c){
					printf("\nIngrese El Monto: $");
					fflush(stdin);
					gets(montox);
					comp_corr=digitos(montox);
					if(comp_corr!=0){
						c=0;
						gasto.monto=atof(montox);
						
						printf("\n\nValor monto %.3lf",gasto.monto);
						system("PAUSE");
						
					}else{
						system("cls");
						printf("\nIngrese Un Monto Valido Mayor A 0 Y Que Sean Unicamente Numeros, Maximo De Tres Decimales\n\n");
						system("PAUSE");
						system("cls");
						
						printf("------------------\n1.REGISTRAR GASTO\n------------------\n");
						printf("\nID De Gasto: %llu\n", id);
						printf("\nTipo De Gasto: %s\n",Cad3);
						printf("\nPertenece A La Categoria: %s\n",gasto.categoria.nombre);
						printf("\nID De Categoria: %llu\n", idC);
						printf("\nDescripcion Del Gasto: %s\n",gasto.desc);
					}
				}
				
				// Resto del codigo para fecha, cuotas, persona...
				c = 1;
				while(c){
					printf("\n--------------------Ingresado De Fecha--------------------");
					printf("\nIngrese El Anio En Formato Numero Largo (Ej,2006)\nAnio Ingresado: ");
					fflush(stdin);
					gets(Cad4);
  	              
					aux_anio=digitosC(Cad4);
					//aux_anio=atoi(Cad4);
  	              
					printf("\nIngrese El Mes En Formato Numero\nMes Ingresado: ");
					fflush(stdin);
					gets(Cad4);
  	              
					aux_mes=digitosC(Cad4);
					//aux_mes=atoi(Cad4);
  	              
					printf("\nIngrese El Dia\nDia Ingresado: ");
					fflush(stdin);
					gets(Cad4);
  	              
					aux_dia=digitosC(Cad4);
					//aux_dia=atoi(Cad4);
					c = comprobacion_fecha(aux_anio, aux_mes, aux_dia);
  	              
					if(c == 1){
						system("cls");
						printf("\nSe Ha Ingresado Mal La Fecha. Por Favor, Vuelva A Ingresarla\n\n");
						system("PAUSE");
						system("cls");
						
						printf("------------------\n1.REGISTRAR GASTO\n------------------\n");
						printf("\nID De Gasto: %llu\n", id);
						printf("\nTipo De Gasto: %s\n",Cad3);
						printf("\nPertenece A La Categoria: %s\n",gasto.categoria.nombre);
						printf("\nID De Categoria: %llu\n", idC);
						printf("\nDescripcion Del Gasto: %s\n",gasto.desc);
						printf("\nEl Monto es: $%.3lf\n",gasto.monto);
					}
				}
  	          
				gasto.fechaGasto.anio = aux_anio;
				gasto.fechaGasto.mes = aux_mes;
				gasto.fechaGasto.dia = aux_dia;
  	          
				printf("----------------------------------------------------------\n");
  	          
				c=1;
				while(c){
					printf("\nIngrese Las Cuotas En Total Del Gasto: ");
					fflush(stdin);
					gets(Cad4);
					comp_corr=digitosC(Cad4);
					gasto.cuotasTotales=atoi(Cad4);
					if((gasto.cuotasTotales<1)||(comp_corr==0)){
						system("cls");
						printf("\nSe Ha Ingresado Mal La Cantidad De Cuotas Totales, Debe Ser Entero Superior A 0 Y Que Sean Unicamente Numeros\n\n");
						system("PAUSE");
						system("cls");
						
						printf("------------------\n1.REGISTRAR GASTO\n------------------\n");
						printf("\nID De Gasto: %llu\n", id);
						printf("\nTipo De Gasto: %s\n",Cad3);
						printf("\nPertenece A La Categoria: %s\n",gasto.categoria.nombre);
						printf("\nID De Categoria: %llu\n", idC);
						printf("\nDescripcion Del Gasto: %s\n",gasto.desc);
						printf("\nEl Monto es: $%.3lf\n",gasto.monto);
						printf("\n--------------------Ingresado De Fecha--------------------");
						printf("\nAnio Ingresado: %d",gasto.fechaGasto.anio);
						printf("\nMes Ingresado: %d",gasto.fechaGasto.mes);
						printf("\nDia Ingresado: %d",gasto.fechaGasto.dia);
						printf("\n----------------------------------------------------------\n");	
					}else{
						c=0;
					}
				}
  	          
				gasto.cuotaActual=1;//predeterminado pagar cuota 1
				gasto.estadoCuota=1;//carga predeterminada no pagado1, parcialmente2, pagado3
  	          	
				c=1;
				while(c){
  	          	
					printf("\nIngrese El DNI Del Responsable Del Gasto: ");
					fflush(stdin);
					gets(Cad8);
					//gasto.persona.dni=atoll(Cad8,NULL);
					gasto.persona.dni=digitosDNI(Cad8);
					comp_corr=digitos(Cad8);
					
					if((strlen(Cad8)>8)||(strlen(Cad8)<6)||(comp_corr==0)){
						system("cls");
						printf("\nNo Se Permite Mas De 8 Numeros En El DNI, O Menor A 6 Numeros, Y Que Sean Unicamente Numeros.\nPor Favor, Vuelva A Ingresarlo\n\n");
						system("PAUSE");
						system("cls");
						
						printf("------------------\n1.REGISTRAR GASTO\n------------------\n");
						printf("\nID De Gasto: %llu\n", id);
						printf("\nTipo De Gasto: %s\n",Cad3);
						printf("\nPertenece A La Categoria: %s\n",gasto.categoria.nombre);
						printf("\nID De Categoria: %llu\n", idC);
						printf("\nDescripcion Del Gasto: %s\n",gasto.desc);
						printf("\nEl Monto es: $%.3lf\n",gasto.monto);
						printf("\n--------------------Ingresado De Fecha--------------------");
						printf("\nAnio Ingresado: %d",gasto.fechaGasto.anio);
						printf("\nMes Ingresado: %d",gasto.fechaGasto.mes);
						printf("\nDia Ingresado: %d",gasto.fechaGasto.dia);
						printf("\n----------------------------------------------------------\n");	
						printf("\nCuotas Totales Ingresadas: %d\n",gasto.cuotasTotales);
					}else{
						c=0;
					}
				}
				c=1;
				while(c){
  	          	
					printf("\nIngrese El Nombre Del Responsable: ");
					fflush(stdin);
					gets(Cad2);
					if((strlen(Cad2)>49)||(Cad2[0]=='\0')||(Cad2[0]==32)){
						system("cls");
						printf("\nNo Se Permite Mas De 50 Caracteres En El Nombre O Con Espacios Al Inicio, Por Favor, Vuelva A Ingresarlo\n\n");
						system("PAUSE");
						system("cls");
						
						printf("------------------\n1.REGISTRAR GASTO\n------------------\n");
						printf("\nID De Gasto: %llu\n", id);
						printf("\nTipo De Gasto: %s\n",Cad3);
						printf("\nPertenece A La Categoria: %s\n",gasto.categoria.nombre);
						printf("\nID De Categoria: %llu\n", idC);
						printf("\nDescripcion Del Gasto: %s\n",gasto.desc);
						printf("\nEl Monto es: $%.3lf\n",gasto.monto);
						printf("\n--------------------Ingresado De Fecha--------------------");
						printf("\nAnio Ingresado: %d",gasto.fechaGasto.anio);
						printf("\nMes Ingresado: %d",gasto.fechaGasto.mes);
						printf("\nDia Ingresado: %d",gasto.fechaGasto.dia);
						printf("\n----------------------------------------------------------\n");	
						printf("\nCuotas Totales Ingresadas: %d\n",gasto.cuotasTotales);
						printf("\nDNI Ingresado es: %lld\n",gasto.persona.dni);
					}else{
						Cad2[strcspn(Cad2, "\n")] = 0;
						strcpy(gasto.persona.nombre, Cad2);
						c=0;
					}
				}
				//printf("\nID De Categoria: %d\n", i);
				gasto.categoria.codigo=idC;
				gasto.codGasto = id;
				gasto.restantanteCuota=(gasto.monto/gasto.cuotasTotales);
				printf("\n\nValor restante %.3lf \n\n",gasto.restantanteCuota);
				fclose(f2);
				guardarGasto(gasto);
				printf("\n----------------------------------------------------------\n\n\nGasto Guardado Exitosamente En El ID: %llu\n", id);
				c=1;
				while(c){
					printf("\nDesea Registrar Otro Gasto?\n\n1. Si, Aplicar Seguir\n0. No, Aplicar Y Finalizar\n\nElija Una Opcion: ");
					scanf("%d", &s);
					if((s!=0)&&(s!=1)){
						system("cls");
						printf("\nIngrese Un Valor Entero Correcto 1/0\n\n");
						system("PAUSE");
						system("cls");
						
						printf("------------------\n1.REGISTRAR GASTO\n------------------\n");
						printf("\nGasto Aterior Guarado En El ID: %llu\n\n", id);
					}else{
						c=0;
					}
				}	
			}else{
				printf("\nError al abrir el archivo");
				system("PAUSE");
			}
		}
	}
}

/////////////////////////////////////////REGISTRAR INGRESO//////////////////////////////////////////////////////////////////////////////////////////

void cargarIngreso(){
	char Cad1[1000],montox[10],Cad4[4],Cad8[9];
	unsigned long long id;
	FILE *f1;
	int s,c,aux_anio,aux_mes,aux_dia,comp_corr1=0;
	
	if((f1=fopen("ingresos.dat","ab"))==NULL){
		printf("\nError Al Abrir El Archivo");
		system("PAUSE");
	}else{
		fclose(f1);
		s=1;
		while(s){

			id = buscar_idIngreso();
            ingreso.codIngreso = id;
			system("cls");
			printf("---------------------\n2.REGISTRAR INGRESO\n---------------------");
	        printf("\n\nID De Ingreso: %llu\n", id);
				
			c=1;
			while(c){
            	printf("\nIngrese El Concepto Del Ingreso: ");
				fflush(stdin);
				gets(Cad1);
				
				if((strlen(Cad1)>49)||(Cad1[0]=='\0')||(Cad1[0]==32)){
					system("cls");
					printf("\nNo Se Permite Mas De 50 Caracteres En El Concepto O Con Espacios Al Inicio, Por Favor, Vuelva A Ingresarlo\n\n");
					system("PAUSE");
					system("cls");
					
					printf("---------------------\n2. REGISTRAR INGRESO\n---------------------\n");
					printf("\nID De Ingreso: %llu\n", id);
				
				}else{
					c=0;
					strcpy(ingreso.concepto, Cad1);
				}
			}
			c=1;
	        while(c){
	            printf("\nIngrese El Monto: $");
	            gets(montox);
	            comp_corr1=digitos(montox);
	            
	            if(comp_corr1!=0){
					c=0;
					ingreso.monto=atof(montox);           		
				}else{
					system("cls");
					printf("\nIngrese Un Monto Valido Mayor A 0 Y Que Sean Unicamente Numeros\n\n");
					system("PAUSE");
					system("cls");
					
					printf("---------------------\n2. REGISTRAR INGRESO\n---------------------\n");
					printf("\nID De Ingreso: %llu\n", id);
					printf("\nEl Concepto Del Ingreso es: %s\n",ingreso.concepto);
				}
			}
			// Resto del cÃƒÂ³digo para fecha, cuotas, persona...
			c = 1;
			while(c){
				printf("\n--------------------Ingresado De Fecha--------------------");
				printf("\nIngrese El Anio En Formato Numero Largo (Ej,2006)\nAnio Ingresado: ");
				fflush(stdin);
				gets(Cad4);
  	              
				aux_anio=digitosC(Cad4);
  	              
				printf("\nIngrese El Mes En Formato Numero\nMes Ingresado: ");
				fflush(stdin);
				gets(Cad4);
  	              
				aux_mes=digitosC(Cad4);
  	              
				printf("\nIngrese El Dia\nDia Ingresado: ");
				fflush(stdin);
				gets(Cad4);
  	              
				aux_dia=digitosC(Cad4);
  	              
				c = comprobacion_fecha(aux_anio, aux_mes, aux_dia);
	        
	            if(c == 1){
					system("cls");
	            	printf("\nSe Ha Ingresado Mal La Fecha. Por Favor, Vuelva A Ingresarla\n\n");
	            	system("PAUSE");
					system("cls");
					
					printf("---------------------\n2. REGISTRAR INGRESO\n---------------------\n");
					printf("\nID De Ingreso: %llu\n", id);
					printf("\nEl Concepto Del Ingreso es: %s\n",ingreso.concepto);
					printf("\nEl Monto es: $%.3lf\n",ingreso.monto);
				}
	        }
	            
	        ingreso.fecha.anio = aux_anio;
	        ingreso.fecha.mes = aux_mes;
	        ingreso.fecha.dia = aux_dia;
            
			printf("----------------------------------------------------------\n");
				
			c=1;
			while(c){
            	
	            printf("\nIngrese El Nombre De La Persona: ");
		        fflush(stdin);
		        gets(Cad1);
		            
		        if((strlen(Cad1)>49)||(Cad1[0]=='\0')||(Cad1[0]==32)){
					system("cls");
					printf("\nNo Se Permite Mas De 50 Caracteres En El Nombre O Con Espacios Al Inicio, Por Favor, Volver A Ingresar\n\n");
					system("PAUSE");
					system("cls");
					
					printf("---------------------\n2. REGISTRAR INGRESO\n---------------------\n");
					printf("\nID De Ingreso: %llu\n", id);
					printf("\nEl Concepto Del Ingreso es: %s\n",ingreso.concepto);
					printf("\nEl Monto es: $%.3lf\n",ingreso.monto);
					printf("\n--------------------Ingresado De Fecha--------------------");
					printf("\nAnio Ingresado: %d",ingreso.fecha.anio);
					printf("\nMes Ingresado: %d",ingreso.fecha.mes);
					printf("\nDia Ingresado: %d",ingreso.fecha.dia);
					printf("\n----------------------------------------------------------\n");
					
				}else{
					Cad1[strcspn(Cad1, "\n")] = 0;
					strcpy(ingreso.persona.nombre, Cad1);
					c=0;
				}
			}
				
			strcpy(ingreso.persona.nombre,Cad1);
				
            c=1;
            while(c){
            	
        		printf("\nIngresar el DNI de la persona: ");
				fflush(stdin);
				gets(Cad8);
				//ingreso.persona.dni=atoll(Cad8);
				ingreso.persona.dni=digitosDNI(Cad8);
				comp_corr1=digitos(Cad8);
				
				if((strlen(Cad8)>8)||(strlen(Cad8)<6)||(comp_corr1==0)){
					system("cls");
                	printf("\nNo Se Permite Mas De 8 Numeros En El DNI, O Menor A 6 Numeros, Y Que Sean Unicamente Numeros.\nPor Favor, Vuelva A Ingresarlo\n\n");
                	system("PAUSE");
					system("cls");
					
					printf("---------------------\n2. REGISTRAR INGRESO\n---------------------\n");
					printf("\nID De Ingreso: %llu\n", id);
					printf("\nEl Concepto Del Ingreso es: %s\n",ingreso.concepto);
					printf("\nEl Monto es: $%.3lf\n",ingreso.monto);
					printf("\n--------------------Ingresado De Fecha--------------------");
					printf("\nAnio Ingresado: %d",ingreso.fecha.anio);
					printf("\nMes Ingresado: %d",ingreso.fecha.mes);
					printf("\nDia Ingresado: %d",ingreso.fecha.dia);
					printf("\n----------------------------------------------------------\n");
					printf("\nIngrese El Nombre De La Persona: %s\n",ingreso.persona.nombre);
						
				}else{
				c=0;
				}
            }
            	
			guardarIngreso(ingreso);
				
			printf("\n----------------------------------------------------------\n\n\nIngreso Guardado Exitosamente En El ID: %llu\n", ingreso.codIngreso);
				
				
				
			c=1;
            while(c){
				printf("\nDesea Registrar Otro Ingreso?\n\n1. Si, Aplicar Seguir\n0. No, Aplicar Y Finalizar\n\nElija Una Opcion: ");
				scanf("%d",&s);
				if((s!=0)&&(s!=1)){
            		system("cls");
            		printf("\nIngrese Un Valor Entero Correcto 1/0\n\n");
            		system("PAUSE");
					system("cls");
					
					printf("---------------------\n2. REGISTRAR INGRESO\n---------------------\n");
					printf("\nIngreso Aterior Guarado En El ID: %llu\n\n",ingreso.codIngreso);
				}else{
					c=0;
				}
			}
		}	
	}	
}


/////////////////////////////////////////REGISTRAR PAGO/////////////////////////////////////////////////////////////////////////////////////////////

void registrarPago(){
FILE *f1,*f2;
    int s=1, c, aux_anio, aux_mes, aux_dia,opc,ac,ca,corr,cnt;
    unsigned long long IDaux;
    char montox[10],Cad3[50],Cad4[5];
    double comp_corr, Cuota;
    
    while(s){
		
        if((f1 = fopen("gastos.dat", "a+b")) != NULL){
			//fclose(f1);
            ac=1;
			while(ac){
				system("cls");
                printf("------------------\n3.REGISTRAR PAGO\n------------------");
				listaGastos();
				
				fflush(stdin);
				scanf("%llu",&IDaux);
				rewind(f1);
				c=1;
				fread(&gasto,sizeof(Gasto),1,f1);
				while((c)&&(!feof(f1))){
					if(IDaux==gasto.codGasto){
						c=0;
						ac=0;	
					}else{
						fread(&gasto,sizeof(Gasto),1,f1);
					}
				}
				if(c==1){
				system("cls");
				printf("\nIngrese Un ID Valido, Entero Superior A 0, Y Existente En El Registro\n");
				system("PAUSE");
				system("cls");
				
				printf("------------------\n3.REGISTRAR PAGO\n------------------");
				}				
					
			}
			
			cnt=1;
			while(cnt){
			
				c=1;
				while(c){
            		
					system("cls");
					printf("------------------\n3.REGISTRAR PAGO\n------------------\n");
					printf("\nID De Gasto Seleccionado: %lld",IDaux);
					printf("\n\nIngrese El Medio De Pago\n\n1. Efectivo\n2. Billetera Electronica\n3. Tarjeta\n4. Debito\n\nElija Una Opcion: ");
					
					fflush(stdin);
					gets(Cad4);
					
					comp_corr=digitosC(Cad4);
					opc=atoi(Cad4);
					if((opc<1)||(comp_corr==0)){
            			system("cls");
            			printf("\nIngrese Correctamente El Tipo De Medio De Pago, Solo Puede Ser Numeros Enteros\n");
            			system("PAUSE");
            			system("cls");
					}else{
						c=0;
					}
            		
				}
			
				switch(opc){
					case 1:
						strcpy(Cad3,"Efectivo");
						printf("\n\nTipo De Medio De Pago: Efectivo");
						//i=1;
						cnt=0;
						break;
					case 2:
						strcpy(Cad3,"Billetera Electronica");
						printf("\n\nTipo De Medio De Pago: Billetera Electronica");
						cnt=0;
						//i=2;
						break;
					case 3:
						strcpy(Cad3,"Tarjeta");
						printf("\n\nTipo De Medio De Pago: Tarjeta");
						cnt=0;
						//i=3;
						break;
					case 4:
						strcpy(Cad3,"Debito");
						printf("\n\nTipo De Medio De Pago: Debito");
						cnt=0;
						//i=4;
						break;					
					default:
						system("cls");
						printf("\nIngrese Un Numero Valido Del 1-4 De Tipo Entero\n\n");
						system("PAUSE");
						system("cls");
						
						printf("------------------\n3.REGISTRAR PAGO\n------------------\n");
						printf("\nID De Gasto Seleccionado: %lld\n\n",IDaux);
				}
			}	
			
			system("cls");
			printf("------------------\n3.REGISTRAR PAGO\n------------------\n");
			printf("\nID De Gasto Seleccionado: %lld\n\n",IDaux);
			printf("Tipo De Medio De Pago Seleccionado: %s\n\n",Cad3);
			
			c=1;
			while(c){
				printf("Ingrese El Monto A Abonar: $");
				
				fflush(stdin);
				gets(montox);
				
				comp_corr=digitos(montox);
				if((comp_corr!=0)&&(comp_corr==gasto.restantanteCuota)){
					c=0;
					pago.importe=atof(montox);
					gasto.estadoCuota=3;
					
					if(gasto.cuotasTotales!=gasto.cuotaActual){
						gasto.cuotaActual++;
					}
					
				}else{
					if((comp_corr!=0)&&(comp_corr<gasto.restantanteCuota)){
						c=0;
						pago.importe=atof(montox);
						gasto.estadoCuota=2;
					}else{
						system("cls");
						printf("\nIngrese Un Monto Valido Mayor A 0 Y Que Sean Unicamente Numeros, Maximo De Tres Decimales, NO Puede Superar El Valor De La Cuota\n\n");
						system("PAUSE");
						system("cls");		
						printf("------------------\n3.REGISTRAR PAGO\n------------------\n");
						printf("\nID De Gasto Seleccionado: %lld\n\n",IDaux);
						printf("Tipo De Medio De Pago Seleccionado: %s\n\n",Cad3);
						
					}
					
				}
			}
				
			c = 1;
			while(c){
				printf("\n--------------------Ingresado De Fecha Del Pago--------------------");
				printf("\nIngrese El Anio En Formato Numero Largo (Ej,2006)\nAnio Ingresado: ");
				fflush(stdin);
				gets(Cad4);
  		              
				aux_anio=digitosC(Cad4);
  		              
				printf("\nIngrese El Mes En Formato Numero\nMes Ingresado: ");
				fflush(stdin);
				gets(Cad4);
  		              
				aux_mes=digitosC(Cad4);
  		              
				printf("\nIngrese El Dia\nDia Ingresado: ");
				fflush(stdin);
				gets(Cad4);
  		              
				aux_dia=digitosC(Cad4);
  		              
				c = comprobacion_fecha(aux_anio, aux_mes, aux_dia);
  		              
				if(c == 1){
					system("cls");
					printf("\nSe Ha Ingresado Mal La Fecha. Por Favor, Vuelva A Ingresarla\n\n");
					system("PAUSE");
					system("cls");
							
					printf("------------------\n3.REGISTRAR PAGO\n------------------\n");
					printf("\nID De Gasto Seleccionado: %lld\n\n",IDaux);
					printf("Tipo De Medio De Pago Seleccionado: %s\n\n",Cad3);
					printf("Monto Abonado: %.3lf\n\n",pago.importe);
				}
			}
  		          
			pago.fechaPago.anio = aux_anio;
			pago.fechaPago.mes = aux_mes;
			pago.fechaPago.dia = aux_dia;
  		          
			printf("----------------------------------------------------------\n");
			
			
			
			printf("\nCodigo: %llu", gasto.codGasto);
            printf("\nTipo: %d", gasto.tipoGasto);
            printf("\nDescripcion: %s", gasto.desc);
            printf("\nEl ID De La Categoria es: %llu",gasto.categoria.codigo);
            printf("\nCategoria: %s", gasto.categoria.nombre);
            printf("\nMonto: %.2lf", gasto.monto);
            printf("\nFecha: %d/%d/%d", gasto.fechaGasto.dia, gasto.fechaGasto.mes, gasto.fechaGasto.anio);
            printf("\nCuotas: %d/%d", gasto.cuotaActual, gasto.cuotasTotales);
            printf("\nPersona: %s (DNI: %lld)", gasto.persona.nombre, gasto.persona.dni);
            printf("\nEstado: %d\n", gasto.estadoCuota);
			system("PAUSE");
			
			
			
			
			
			
			
			
			
			
			
			
			
			gasto.monto-=pago.importe;
			gasto.restantanteCuota-=pago.importe;
			
			fseek(f1,sizeof(Gasto)*(-1),SEEK_CUR);
			fwrite(&gasto,sizeof(Gasto),1,f1);
			
			
			
			
			
			
			
			printf("\nCodigo: %llu", gasto.codGasto);
            printf("\nTipo: %d", gasto.tipoGasto);
            printf("\nDescripcion: %s", gasto.desc);
            printf("\nEl ID De La Categoria es: %llu",gasto.categoria.codigo);
            printf("\nCategoria: %s", gasto.categoria.nombre);
            printf("\nMonto: %.2lf", gasto.monto);
            printf("\nFecha: %d/%d/%d", gasto.fechaGasto.dia, gasto.fechaGasto.mes, gasto.fechaGasto.anio);
            printf("\nCuotas: %d/%d", gasto.cuotaActual, gasto.cuotasTotales);
            printf("\nPersona: %s (DNI: %lld)", gasto.persona.nombre, gasto.persona.dni);
            printf("\nEstado: %d\n", gasto.estadoCuota);
			system("PAUSE");
			
			
			
			
			
			
			
			
			
			
			
		}else{
			printf("\nError al abrir el archivo Gastos");
			system("PAUSE");
		}
		
	}
}

///////////////////////////////////////// LISTAR GASTOS E INGRESOS ///////////////////////////////////////////////////////////////////////////////////

void listarGastoseIngresos() {
	
    int opc, s = 1, seguir;
    
    while (s) {
    	system("cls");
        printf("\nEscoja lo que desea listar:\n\n1. Gastos\n2. Ingresos\n3. Volver al Menu Principal\n\nElija una opcion: ");
        fflush(stdin);
        scanf("%d", &opc);
        
        switch (opc) {
            case 1:
                system("cls");
                printf("-------------\nFILTRAR GASTOS\n---------\n");
                listarGastos();
                break;
            case 2:
                system("cls");
                listarIngresos();
                break;	
            case 3:	
                printf("\nVOLVIENDO .....\n\n");
                s = 0;
                break;	
            default:
                printf("\nIngrese un numero valido del 1-4 de tipo entero\n\n");			
        }
        
        if (s) {
            if ((opc >= 1) && (opc <= 2)) {
                system("cls");
                printf("\nDesea realizar otro listado?\n\n1. Si, cargar siguiente\n0. No, finalizar : \t ");
                fflush(stdin);
                scanf("%d", &opc);
                
                while ((opc != 1) && (opc != 0)) {
                    system("cls");
                    printf("\nOpcion invalida. Intentelo de nuevo. Ingrese un numero valido del 1-0 de tipo entero.\n");
                    printf("\nDesea realizar otro listado?\n\n1. Si, cargar siguiente\n0. No, finalizar : \t ");
                    fflush(stdin);
                    scanf("%d", &opc);
                }
                
                if (!opc) {
                    s = 0;
                }
            }
        }
    }
}

///////////////////////////////////////// CONSULTAS Y REPORTES ///////////////////////////////////////////////////////////////////////////////////////

void consultasyReportes() {
    int opc, s = 1, seguir;
    
    while (s) {
        printf("\nEscoja la consulta/reporte a realizar:\n\n1. Gastos por Categoria\n2. Gastos Por Mes y Anio\n3. Ingresos Por Persona\n4. Saldo Mensual\n5. Gastos Pendientes\n6. Pagos Por Medio de Pago\n7. Gastos con Saldo Incompleto\n8. Top 3 Categorias Mas Costosas\n9. Proyeccion Mensual\n10. Resumen General\n11. Volver al Menu Principal\n\nElija una opcion: ");
        fflush(stdin);
        scanf("%d", &opc);
        
        switch (opc) {
            case 1:
                system("cls");
                printf("---------\n1. GASTOS POR CATEGORIA\n---------");
                gastosPorCategoria();
                break;
            case 2:
                system("cls");
                printf("---------\n2. GASTOS POR MES Y ANIO\n---------");
                gastosPorMesYAnio();
                break;
            case 3:
                system("cls");
                printf("---------\n3. INGRESOS POR PERSONA\n---------");
                ingresosPorPersona();
                break;
            case 4:
                system("cls");
                printf("---------\n4. SALDO MENSUAL\n---------");
                saldoMensual();
                break;
            case 5:
                system("cls");
                printf("---------\n5. GASTOS PENDIENTES\n---------");
                gastosPendientes();
                break;
            case 6:
                system("cls");
                printf("---------\n6. PAGOS POR MEDIO DE PAGO\n---------");
                pagosPorMedioDePago();
                break;
            case 7:
                system("cls");
                printf("---------\n7. GASTOS CON SALDO INCOMPLETO\n---------");
                gastosConSaldoIncompleto();
                break;
            case 8:
                system("cls");
                printf("---------\n8. TOP 3 CATEGORIAS MAS COSTOSAS\n---------");
                categoriasMasCostosas();
                break;
            case 9:
                system("cls");
                printf("---------\n9. PROYECCION MENSUAL\n---------");
                proyeccionMensual();
                break;
            case 10:
                system("cls");
                printf("---------\n10. RESUMEN GENERAL\n---------");
                resumenGeneral();
                break;
            case 11:	
                printf("\nVOLVIENDO .....\n\n");
                s = 0;
                break;	
            default:
                printf("\nIngrese un numero valido del 1-11 de tipo entero\n\n");			
        }
        
        if (s) {
            if ((opc >= 1) && (opc <= 10)) {
                system("cls");
                printf("\nDesea realizar otra consulta/reporte?\n\n1. Si, cargar siguiente\n0. No, finalizar : \t ");
                fflush(stdin);
                scanf("%d", &opc);
                
                while ((opc != 1) && (opc != 0)) {
                    system("cls");
                    printf("\nOpcion invalida. Intentelo de nuevo. Ingrese un numero valido del 1-0 de tipo entero.\n");
                    printf("\nDesea realizar otra consulta/reporte?\n\n1. Si, cargar siguiente\n0. No, finalizar : \t ");
                    fflush(stdin);
                    scanf("%d", &opc);
                }
                
                if (!opc) {
                    s = 0;
                }
            }
        }
    }
}

///////////////////////////////////////// FUNCIONES AUXILIARES ///////////////////////////////////////////////////////////////////////////////////////

void guardarGasto(Gasto gasto){
	
	FILE *f4;
	
	if((f4=fopen("gastos.dat","ab"))==NULL){
		printf("\nError al abrir el archivo");
		system("PAUSE");
	}else{
		fwrite(&gasto,sizeof(Gasto),1,f4);
		fclose(f4);
	}
	
	
}


int comprobacion_fecha(int aux_anio1,int aux_mes1,int aux_dia1){
	
	int verif = 1;
	
    if ((aux_anio1<3000)&&(aux_anio1>2000)){
        if ((aux_mes1<=12)&&(aux_mes1>=1)){

            if ((aux_mes1 == 1) && (aux_dia1 >= 1) && (aux_dia1 <= 31)) { /* enero */
                verif = 0;
            } else if ((aux_mes1 == 2) && (aux_dia1 >= 1) && (aux_dia1 <= 28)) { /* febrero (sin bisiestos) */
                verif = 0;
            } else if ((aux_mes1 == 3) && (aux_dia1 >= 1) && (aux_dia1 <= 31)) { /* marzo */
                verif = 0;
            } else if ((aux_mes1 == 4) && (aux_dia1 >= 1) && (aux_dia1 <= 30)) { /* abril */
                verif = 0;
            } else if ((aux_mes1 == 5) && (aux_dia1 >= 1) && (aux_dia1 <= 31)) { /* mayo */
                verif = 0;
            } else if ((aux_mes1 == 6) && (aux_dia1 >= 1) && (aux_dia1 <= 30)) { /* junio */
                verif = 0;
            } else if ((aux_mes1 == 7) && (aux_dia1 >= 1) && (aux_dia1 <= 31)) { /* julio */
                verif = 0;
            } else if ((aux_mes1 == 8) && (aux_dia1 >= 1) && (aux_dia1 <= 31)) { /* agosto */
                verif = 0;
            } else if ((aux_mes1 == 9) && (aux_dia1 >= 1) && (aux_dia1 <= 30)) { /* septiembre */
                verif = 0;
            } else if ((aux_mes1 == 10) && (aux_dia1 >= 1) && (aux_dia1 <= 31)) { /* octubre */
                verif = 0;
            } else if ((aux_mes1 == 11) && (aux_dia1 >= 1) && (aux_dia1 <= 30)) { /* noviembre */
                verif = 0;
            } else if ((aux_mes1 == 12) && (aux_dia1 >= 1) && (aux_dia1 <= 31)) { /* diciembre */
                verif = 0;
            } else{
                verif = 1;
            }

        } else{
            verif = 1;
        }
    } else{
        verif = 1;
    }
	fflush(stdin);
    return verif; /* 0 = valido, 1 = invalido */
	
}

void ver_arch_gastos() {
    FILE *f2;
	char Charx[15];
    
    if ((f2 = fopen("gastos.dat", "rb")) == NULL) {
        printf("\nError Al Abrir El Archivo");
        system("PAUSE");
    } else {
        printf("\n\nContenido Del Archivo Gastos:\n");
        while (fread(&gasto, sizeof(Gasto), 1, f2)) {
            printf("\nCodigo: %llu", gasto.codGasto);
            printf("\nTipo: %d", gasto.tipoGasto);
            printf("\nDescripcion: %s", gasto.desc);
            printf("\nEl ID De La Categoria es: %llu",gasto.categoria.codigo);
            printf("\nCategoria: %s", gasto.categoria.nombre);
            printf("\nMonto: %.2lf", gasto.monto);
            printf("\nFecha: %d/%d/%d", gasto.fechaGasto.dia, gasto.fechaGasto.mes, gasto.fechaGasto.anio);
            printf("\nCuotas: %d/%d", gasto.cuotaActual, gasto.cuotasTotales);
            printf("\nPersona: %s (DNI: %lld)", gasto.persona.nombre, gasto.persona.dni);
            printf("\nEstado: %d\n", gasto.estadoCuota);
            printf("------------------------\n");
        }
        fclose(f2);
    }
    system("PAUSE");
    
    
    
    
    
}

unsigned long long buscar_idGasto(){
    FILE *arch;
    unsigned long long ret=1 ,max_id = 0;
    Gasto gasto_temp;
    
    if((arch = fopen("gastos.dat", "rb")) != NULL){
    	rewind(arch);
        // Buscar el ID mÃƒÂ¡ximo en todos los registros
        while(fread(&gasto_temp, sizeof(Gasto), 1, arch) == 1){
            if(gasto_temp.codGasto > max_id){
                max_id = gasto_temp.codGasto;
            }
        }
        fclose(arch);
        
        // Si encontramos registros, devolver el siguiente ID
        if(max_id > 0){
            ret=max_id + 1;
        }
    }else{
    	printf("\n\nError, No Se Pudo Abrir El Archivo\n\n");
    	system("PAUSE");
	}
    // Si el archivo no existe o estÃƒÂ¡ vacÃƒÂ­o, empezar desde 1
    return ret;
}

unsigned long long buscar_idCategoria(){
	FILE *arch1;
    unsigned long long ret1=1 ,max_id1 = 0;
    Gasto gasto_temp1;
    
    if((arch1 = fopen("gastos.dat", "rb")) != NULL){
    	rewind(arch1);
        // Buscar el ID mÃƒÂ¡ximo en todos los registros
        while(fread(&gasto_temp1, sizeof(Gasto), 1, arch1) == 1){
            if(gasto_temp1.categoria.codigo > max_id1){
                max_id1 = gasto_temp1.categoria.codigo;
            }
        }
        fclose(arch1);
        
        // Si encontramos registros, devolver el siguiente ID
        if(max_id1 > 0){
            ret1=max_id1 + 1;
        }
    }else{
    	printf("\n\nError, No Se Pudo Abrir El Archivo\n\n");
    	system("PAUSE");
	}
    // Si el archivo no existe o estÃƒÂ¡ vacÃƒÂ­o, empezar desde 1
    return ret1;
}

unsigned long long buscar_idIngreso(){
	FILE *f6;
    unsigned long long ret2=1 ,max_id2 = 0;
    Ingreso ingreso_temp2;
    
    if((f6 = fopen("ingresos.dat", "rb")) != NULL){
    	rewind(f6);
        // Buscar el ID mÃƒÂ¡ximo en todos los registros
        while(fread(&ingreso_temp2,sizeof(Ingreso), 1, f6) == 1){
            if(ingreso_temp2.codIngreso > max_id2){
                max_id2 = ingreso_temp2.codIngreso;
            }
        }
        fclose(f6);
        
        // Si encontramos registros, devolver el siguiente ID
        if(max_id2 > 0){
            ret2=max_id2 + 1;
        }
    }else{
    	printf("\n\nError, No Se Pudo Abrir El Archivo\n\n");
    	system("PAUSE");
	}
    // Si el archivo no existe o estÃƒÂ¡ vacÃƒÂ­o, empezar desde 1
    return ret2;
}

void guardarIngreso(Ingreso ingreso){
	FILE *f5;
	if((f5=fopen("ingresos.dat","ab"))==NULL){
		printf("\nError al abrir el archivo");
		system("PAUSE");
	}else{
		fwrite(&ingreso,sizeof(ingreso),1,f5);
		fclose(f5);
	}
	
}

void ver_arch_ingresos() {
    FILE *f1;
    
    if ((f1 = fopen("ingresos.dat", "rb")) == NULL) {
        printf("\nError Al Abrir El Archivo");
        system("PAUSE");
    } else {
        printf("\n\nContenido Del Archivo Ingresos:\n");
        while (fread(&ingreso, sizeof(Ingreso), 1, f1)) {
            printf("\nCodigo: %llu", ingreso.codIngreso);
            printf("\nConcepto: %s", ingreso.concepto);
            printf("\nMonto: %.3lf", ingreso.monto);
            printf("\nFecha: %d/%d/%d", ingreso.fecha.dia, ingreso.fecha.mes, ingreso.fecha.anio);
            printf("\nPersona: %s (DNI: %lld)\n", ingreso.persona.nombre, ingreso.persona.dni);
            printf("------------------------\n");
        }
        fclose(f1);
    }
    
    system("PAUSE");
}

void ver_arch_pagos() {
    FILE *f3;
    char Cadx[30];
    
    if ((f3 = fopen("pagos.dat", "rb")) == NULL) {
        printf("\nError Al Abrir El Archivo");
        system("PAUSE");
    } else {
    	if(pago.medioPago==1){
    		strcpy(Cadx,"No Pagado");
		}else{
			if(pago.medioPago==2){
				strcpy(Cadx,"Parcialmente Pagado");
			}else{
				strcpy(Cadx,"Pagado");
			}
		}
        printf("\n\nContenido Del Archivo Pagos:\n");
        while (fread(&pago, sizeof(Pago), 1, f3)) {
            printf("\nCodigo Gasto: %llu", pago.codGasto);
            printf("\nMedio Pago: %s",Cadx);
            printf("\nImporte: %.2lf", pago.importe);
            printf("\nFecha: %d/%d/%d\n", pago.fechaPago.dia, pago.fechaPago.mes, pago.fechaPago.anio);
            printf("------------------------\n");
        }
        fclose(f3);
    }
    
    system("PAUSE");
}

double digitos(char *r) {
    double ret1 = 0;
    int i, ccc = 0, punto_encontrado = 0;
    
    for (i = 0; r[i] != '\0'; i++) {
        if (r[i] == '.') {
            ccc++;
            punto_encontrado = i; // Guardar posiciÃƒÂ³n del punto
        } else if (r[i] < '0' || r[i] > '9') {
            // Caracter no numÃƒÂ©rico ni punto encontrado
            ccc=2;
        }
    }
    
    // Verificar mÃƒÂ¡ximo un punto y hasta 3 decimales
    if (ccc <= 1) {
        if (punto_encontrado > 0) {
            // Contar dÃƒÂ­gitos despuÃƒÂ©s del punto
            int decimales = 0;
            for (i = punto_encontrado + 1; r[i] != '\0'; i++) {
                decimales++;
            }
            if (decimales <= 3) {
                ret1 = atof(r);
            }
        } else {
            // No hay punto, es entero
            ret1 = atof(r);
        }
    }
    
    return ret1;
}

long long digitosDNI(char*j) {
	int k,ret3=0,con=0;
	
    // Verificar que TODOS los caracteres sean digitos
    for (k = 0; j[k] != '\0'; k++) {
        if (j[k] < '0' || j[k] > '9') {
            con++; // Caracter no numerico encontrado
        }
    }
    if(con==0){
    	ret3=atoll(j);
	}
    fflush(stdin);
    return ret3; // Todos los caracteres son digitos
}

// Funciones de filtrado y reportes (implementaciones b sicas)

void listarIngresos(){
	
	printf("\nFuncion listarIngresos - En desarrollo\n");
    system("PAUSE");
}

void listarGastos(){
	
	int opc, s = 1, seguir;
    
    while (s) {
        printf("\nEscoja el criterio por el cual filtrar:\n\n1. Filtrar Por Categoria\n2. Filtrar Por Tipo\n3. Filtrar Por Mes\n4. Volver\n\nElija una opcion: ");
        fflush(stdin);
        scanf("%d", &opc);
        
        switch (opc) {
            case 1:
                system("cls");
                filtrarPorCategoria();
                break;
            case 2:
                system("cls");
                filtrarPorTipo();
                break;	
            case 3:
                system("cls");
                filtrarPorMes();
                break;
            case 4:	
                printf("\nVOLVIENDO .....\n\n");
                s = 0;
                break;	
            default:
                printf("\nIngrese un numero valido del 1-4 de tipo entero\n\n");			
        }
        
        if (s) {
            if ((opc >= 1) && (opc <= 3)) {
                system("cls");
                printf("\nDesea realizar otro listado?\n\n1. Si, cargar siguiente\n0. No, finalizar : \t ");
                fflush(stdin);
                scanf("%d", &opc);
                
                while ((opc != 1) && (opc != 0)) {
                    system("cls");
                    printf("\nOpcion invalida. Intentelo de nuevo. Ingrese un numero valido del 1-0 de tipo entero.\n");
                    printf("\nDesea realizar otro listado?\n\n1. Si, cargar siguiente\n0. No, finalizar : \t ");
                    fflush(stdin);
                    scanf("%d", &opc);
                }
                
                if (!opc) {
                    s = 0;
                }
            }
        }
    }

}
void filtrarPorTipo() {
    printf("\nFuncion filtrarPorTipo - En desarrollo\n");
    system("PAUSE");
}

void filtrarPorCategoria() {
    printf("\nFuncion filtrarPorCategoria - En desarrollo\n");
    system("PAUSE");
}

void filtrarPorMes() {
    printf("\nFuncion filtrarPorMes - En desarrollo\n");
    system("PAUSE");
}

void gastosPorCategoria() {
    printf("\nFuncion gastosPorCategoria - En desarrollo\n");
    system("PAUSE");
}

void gastosPorMesYAnio() {
    printf("\nFuncion gastosPorMesYAnio - En desarrollo\n");
    system("PAUSE");
}

void ingresosPorPersona() {
    printf("\nFuncion ingresosPorPersona - En desarrollo\n");
    system("PAUSE");
}

void saldoMensual() {
    printf("\nFuncion saldoMensual - En desarrollo\n");
    system("PAUSE");
}

void gastosPendientes() {
    printf("\nFuncion gastosPendientes - En desarrollo\n");
    system("PAUSE");
}

void pagosPorMedioDePago() {
    printf("\nFuncion pagosPorMedioDePago - En desarrollo\n");
    system("PAUSE");
}

void gastosConSaldoIncompleto() {
    printf("\nFuncion gastosConSaldoIncompleto - En desarrollo\n");
    system("PAUSE");
}

void categoriasMasCostosas() {
    printf("\nFuncion categoriasMasCostosas - En desarrollo\n");
    system("PAUSE");
}

void proyeccionMensual() {
    printf("\nFuncion proyeccionMensual - En desarrollo\n");
    system("PAUSE");
}

void resumenGeneral() {
    printf("\nFuncion resumenGeneral - En desarrollo\n");
    system("PAUSE");
}

void filtroPorMes(int mes) {
    printf("\nFuncion filtroPorMes - En desarrollo\n");
}

void listaCategorias(){
	FILE*arch;
	unsigned long long idaux=0;
	int cc1;
	
	if((arch=fopen("gastos.dat","r+b"))==NULL){
		printf("\nError al abrir el archivo");
		system("PAUSE");
	}else{
		rewind(arch);
		cc1=0;
		printf("\n\nSeleccione Una Categoria Con El Numero De Codigo De Categoria, O Ingrese 0 Para Agregar Una Nueva Categoria\n-----------------------------------------------------------------------------------------------------------");
		fread(&gasto,sizeof(Gasto),1,arch);
		while(!feof(arch)){
			if((idaux!=gasto.categoria.codigo)&&(idaux<gasto.categoria.codigo)){
				cc1++;
				printf("\n%d.\tID De Categoria: %llu\tCategoria: %s\n",cc1,gasto.categoria.codigo,gasto.categoria.nombre);
				idaux=gasto.categoria.codigo;	
			}
			fread(&gasto,sizeof(Gasto),1,arch);	
		}
		fclose(arch);
		printf("-----------------------------------------------------------------------------------------------------------\n\nIngrese Una Opcion: ");				
	}
	

}

void listaGastos(){
	FILE*arch;
	unsigned long long idaux=0;
	int cc1;
	char CaTip[10],CaEst[25];
	double auxf;
	
	if((arch=fopen("gastos.dat","r+b"))==NULL){
		printf("\nError al abrir el archivo");
		system("PAUSE");
	}else{
		rewind(arch);
		cc1=0;
		printf("\n\nSeleccione Un Gasto Con El Numero De Codigo De Gasto\n------------------------------------------------------------------------------------------------------------------------");
		fread(&gasto,sizeof(Gasto),1,arch);
		while(!feof(arch)){
			if(gasto.estadoCuota!=3){
				auxf=gasto.restantanteCuota;
				
				cc1++;
				switch(gasto.estadoCuota){
					case 1:
						strcpy(CaEst,"Que Adeuda");
						break;
					case 2:
						strcpy(CaEst,"Esta Parcialmente Pagada");
						break;
					case 3:
						strcpy(CaEst,"Esta Pagada");
						break;
				}
				
				switch(gasto.tipoGasto){
    				case 1:
    					strcpy(CaTip,"Fijo");
    				break;
    				case 2:
    					strcpy(CaTip,"Temporal");
    					break;
    				case 3:
    					strcpy(CaTip,"Ocasional");
    					break;
    				case 4:
    					strcpy(CaTip,"Anual");
    					break;
				}
				printf("\n%d.\tID De Gasto Numero: %llu   Descripcion De Gasto: %s   Tipo De Gasto: %s   Monto Restante $%.3lf\n",cc1,gasto.codGasto,gasto.desc,CaTip,gasto.monto);
				printf("\n\tID De Categoria Numero: %llu   Pertence A La Categoria: %s   Gasto Generado Por %s, DNI: %ld\n",gasto.categoria.codigo,gasto.categoria.nombre,gasto.persona.nombre,gasto.persona.dni);
				printf("\n\tCon %d Cuotas En Total   La Cuota Actual %s Es La Numero %d Con Un Valor De $%.3lf\n",gasto.cuotasTotales,CaEst,gasto.cuotaActual,auxf);
				printf("\n------------------------------------------------------------------------------------------------------------------------\n");
			}
			fread(&gasto,sizeof(Gasto),1,arch);	
		}
		fclose(arch);
		printf("\nIngrese Una Opcion: ");				
	}
}


void registroCategoria(char*Cad22,unsigned long long IX,char*Tip){
	int x=1;
	
    while(x){
	   	
        printf("\n\nIngrese Un Nombre De Categoria Para El Gasto: ");
	    fflush(stdin);
	    gets(Cad22);
	            
	    if((strlen(Cad22)>49)||(Cad22[0]=='\0')||(Cad22[0]==32)){
	            	
	        system("cls");
	        printf("\nNo Se Permite Mas De 50 Caracteres En El Nombre De Categoria O Con Espacios Al Inicio, Por Favor, Vuelva A Ingresarlo\n\n");
	        system("PAUSE");
			system("cls");
			fflush(stdin);
			
			printf("------------------\n1.REGISTRAR GASTO\n------------------\n");
			printf("\nID De Gasto: %llu\n", IX);
			printf("\nTipo De Gasto: %s\n",Tip);
			
	            	
		}else{
			Cad22[strcspn(Cad22, "\n")] = 0;
			x=0;
		}
	}
}

int digitosC(char*r){
	int ret1 = 0,i,con=0;
	
    // Verificar que TODOS los caracteres sean digitos
    for (i = 0; i[r] != '\0'; i++) {
        if (r[i] < '0' || r[i] > '9') {
            con++; // Caracter no numerico encontrado
        }
    }
    if(con==0){
    	ret1=atoi(r);
	}
    fflush(stdin);
    return ret1; // Todos los caracteres son digitos

}
