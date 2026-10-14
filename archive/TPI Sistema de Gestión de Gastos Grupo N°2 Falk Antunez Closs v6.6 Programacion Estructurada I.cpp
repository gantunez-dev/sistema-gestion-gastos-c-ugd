
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define EPSILON 0.001

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
    double restanteCuota;
    double deudaTotal;
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
Categoria categoria;
Persona persona;

// PROTOTIPOS ///////////////////////
void cargarGasto(); // CARGAR GASTO
void cargarIngreso(); // CARGAR INGRESO
void registrarPago(); // REGISTRAR PAGO
void listarGastoseIngresos(); // LISTAR GASTOS E INGRESOS
void consultasyReportes(); // CONSULTAS Y REPORTES
void administracion(); // ELIMINACION DE DATOS

// PROTOTIPOS *********
void guardarGasto(Gasto gasto);
int comprobacion_fecha(int aux_anio, int aux_mes, int aux_dia);
void ver_arch_gastos(); // Unicamente para ver como queda en el archivo gastos.dat
unsigned long long buscar_idGasto();
unsigned long long buscar_idCategoria();
unsigned long long buscar_idIngreso();
void registroCategoria(char*,unsigned long long,char*);
void guardarIngreso(Ingreso ingreso);
void guardarPago(Pago pago);
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
void top3CategoriasMasCostosas();
void proyeccionMensual();
void resumenGeneral();
void eliminarPersona();
void eliminarGasto();
void eliminarIngreso();
void eliminarPago();
void eliminarCategoria();


// PROTOTIPOS -----------------
double digitos(char*);
long long digitosDNI(char*);
void listaCategorias();
void listaGastos();
int digitosC(char*r);
int gastosExsistentes();
///////////////////////////////////////// main //////////////////////////////////////////////////////////////////////////////////////////

int main() {
	
    char copc[2];// Buffer de entrada de un solo caracter.
    int opcp, zxxz = 1;// 'opcp': opcion del menu, 'zxxz': flag de control (1=ejecutar, 0=salir).
    
    while (zxxz) {
    	
        system("cls");
        printf("\nSistema De Gestion De Gastos Personales O Familiares\n--------MENU PRINCIPAL--------\n\n1. Registrar Gasto\n2. Registrar Ingreso\n3. Registrar Pago\n4. Listar Gastos E Ingresos\n5. Consultas y Reportes\n6. Administracion De Datos Guardados\n7. Salir\n\nElija Una Opcion: ");
        fflush(stdin);
        gets(copc);
        
        opcp = atoi(copc);
        
        switch (opcp) {
            case 1:
                system("cls");
                //printf("------------------\n1.REGISTRAR GASTO\n------------------");
                cargarGasto();
                //ver_arch_gastos(); // quitar luego
                break;
            case 2:
                system("cls");
                //printf("---------------------\n2.REGISTRAR INGRESO\n---------------------");
                cargarIngreso();
                //ver_arch_ingresos(); // quitar luego
                break;
            case 3:
                system("cls");
                //printf("------------------\n3.REGISTRAR PAGO\n------------------");
                registrarPago();
                //ver_arch_pagos(); // quitar luego
                //ver_arch_gastos();
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
                administracion();
                break;     
            case 7:
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
	
    FILE *f2, *fcat;
    int s=1, c, aux_anio, aux_mes,aux_dia,cnt,opc,i,ac,ca,comp_corr, encontrado;
    unsigned long long id,idC,IDaux;
    char Cad2[50000],montox[100],Cad4[50000],Cad8[9],Cad3[50];
    
    while(s){
    	
    	cnt=1;
    	
        if((f2 = fopen("gastos.dat", "ab")) == NULL){
        	
            printf("\nError Al Abrir El Archivo");
            system("PAUSE");
            
        }
		else{
			
        	fread(&gasto,sizeof(Gasto),1,f2);
        	fclose(f2);
        
      
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
            			
					}
					else{
						
						c=0;
						
					}
						
				}
            	
	            system("cls");
	            printf("------------------\n1.REGISTRAR GASTO\n------------------\n");
	            printf("\nID De Gasto: %llu", id); 
	            
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
            	
				}
				else{
					
            		fclose(f2);
            		ac=1;
            		
					while(ac){
						
						listaCategorias();
						fflush(stdin);
						gets(Cad4);
						comp_corr=digitosC(Cad4);
						
						IDaux=atoll(Cad4);
						
	            		if(IDaux==0){
	            			
	            			
	            		
	            			system("cls");
	            			printf("------------------\n1.REGISTRAR GASTO\n------------------\n");
	            			printf("\nID De Gasto: %llu\n", id);
							printf("\nTipo De Gasto: %s",Cad3);
	            			registroCategoria(Cad2,id,Cad3);
                			strcpy(gasto.categoria.nombre,Cad2);
	            			
	            			idC = buscar_idCategoria();
            				gasto.categoria.codigo = idC;
            				
	            			ac=0;
	            			
						}
						else{
							
							if((IDaux<0)||(comp_corr==0)){
								
								system("cls");
								printf("\nIngrese Un ID Valido, Entero Superior A 0, Y No Se Puede Ingresar Caracteres\n");
								system("PAUSE");
								system("cls");
								
							}
							else{
								
								
								ca=1;
								
								if((f2=fopen("gastos.dat","r+b"))==NULL){
									
									printf("\nError al abrir el archivo");
									system("PAUSE");
									
								}
								else{
									
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
				
				if((fcat = fopen("categorias.dat","a+b"))!=NULL){
					
					encontrado = 0;
            		rewind(fcat);
            		fread(&categoria,sizeof(Categoria),1,fcat);
            		
            		while((!feof(fcat))&&(!encontrado)){
            			
            			if(categoria.codigo == idC){            
            				
            				encontrado = 1;
            				
						}
						
						fread(&categoria,sizeof(Categoria),1,fcat);
					}
					
					if(!encontrado){
							
						strcpy(categoria.nombre, Cad2);
						categoria.codigo = idC;
						fseek(fcat,sizeof(Categoria)*(-1),SEEK_CUR);
						fwrite(&categoria,sizeof(Categoria),1,fcat);
							
					}
						
					fclose(fcat);
				}
				else{
					printf("\nError al abrir el archivo.\n");
				}
				
				printf("\nID De Categoria: %llu\n", idC); 
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
						
					}
					else{
						
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
						gasto.deudaTotal=atof(montox);
						//printf("\n\nValor monto %.3lf",gasto.monto);
						//system("PAUSE");
						
					}
					else{
						
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
						printf("\nEl Monto es: $%.3lf\n",gasto.deudaTotal);
						
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
					gasto.cuotasTotales=digitosC(Cad4);
					
					if(gasto.cuotasTotales<1){
						
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
						printf("\nEl Monto es: $%.3lf\n",gasto.deudaTotal);
						printf("\n--------------------Ingresado De Fecha--------------------");
						printf("\nAnio Ingresado: %d",gasto.fechaGasto.anio);
						printf("\nMes Ingresado: %d",gasto.fechaGasto.mes);
						printf("\nDia Ingresado: %d",gasto.fechaGasto.dia);
						printf("\n----------------------------------------------------------\n");	
					}
					else{
						
						c=0;
						
					}
					
				}
  	          
				gasto.cuotaActual=1;//definicion por defecto
				gasto.estadoCuota=1;//definicion por defecto 1 no pagado, 2 parcialmente y 3 pagado
  	          	
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
						printf("\nEl Monto es: $%.3lf\n",gasto.deudaTotal);
						printf("\n--------------------Ingresado De Fecha--------------------");
						printf("\nAnio Ingresado: %d",gasto.fechaGasto.anio);
						printf("\nMes Ingresado: %d",gasto.fechaGasto.mes);
						printf("\nDia Ingresado: %d",gasto.fechaGasto.dia);
						printf("\n----------------------------------------------------------\n");	
						printf("\nCuotas Totales Ingresadas: %d\n",gasto.cuotasTotales);
					}
					else{
						
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
						printf("\nEl Monto es: $%.3lf\n",gasto.deudaTotal);
						printf("\n--------------------Ingresado De Fecha--------------------");
						printf("\nAnio Ingresado: %d",gasto.fechaGasto.anio);
						printf("\nMes Ingresado: %d",gasto.fechaGasto.mes);
						printf("\nDia Ingresado: %d",gasto.fechaGasto.dia);
						printf("\n----------------------------------------------------------\n");	
						printf("\nCuotas Totales Ingresadas: %d\n",gasto.cuotasTotales);
						printf("\nDNI Ingresado es: %lld\n",gasto.persona.dni);
						
					}
					else{
						
						Cad2[strcspn(Cad2, "\n")] = 0;
						strcpy(gasto.persona.nombre, Cad2);
						c=0;
						
					}
					
				}
				//printf("\nID De Categoria: %d\n", i);
				gasto.categoria.codigo=idC;
				gasto.codGasto = id;
				gasto.restanteCuota=(gasto.deudaTotal/gasto.cuotasTotales);
				//printf("\n\nValor restante %.3lf \n\n",gasto.restanteCuota);
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
						printf("\nGasto Anterior Guarado En El ID: %llu\n\n", id);
						
					}
					else{
						
						c=0;
						
					}
				}
					
			}
			else{
				
				printf("\nError al abrir el archivo");
				system("PAUSE");
				
			}
		}
	}
}

/////////////////////////////////////////REGISTRAR INGRESO//////////////////////////////////////////////////////////////////////////////////////////

void cargarIngreso(){
	
	char Cad1[50000],montox[100],Cad4[4],Cad8[9];
	unsigned long long id;
	FILE *f1, *fper;
	int s,c,aux_anio,aux_mes,aux_dia,comp_corr1=0, encontrado;
	long long num;
	
	if((f1=fopen("ingresos.dat","ab"))==NULL){
		
		printf("\nError Al Abrir El Archivo");
		system("PAUSE");
		
	}
	else{
		
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
				
				}
				else{
					
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
					         		
				}
				else{
					
					system("cls");
					printf("\nIngrese Un Monto Valido Mayor A 0 Y Que Sean Unicamente Numeros, Maximo De Tres Decimales\n\n");
					system("PAUSE");
					system("cls");
					
					printf("---------------------\n2. REGISTRAR INGRESO\n---------------------\n");
					printf("\nID De Ingreso: %llu\n", id);
					printf("\nEl Concepto Del Ingreso es: %s\n",ingreso.concepto);
					
				}
			}
			
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
					
				}
				else{
					
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
				//comp_corr1=digitos(Cad8);
				
				if((strlen(Cad8)>8)||(strlen(Cad8)<6)||(ingreso.persona.dni==0)){
					
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
						
				}
				else{
					
					c=0;    //ver si la indentacion no le afecto
				
				}
				
            }
            	
			guardarIngreso(ingreso);
			
			if((fper = fopen("personas.dat","a+b"))!=NULL){
					
				encontrado = 0;
            	rewind(fper);
            	fread(&persona,sizeof(Persona),1,fper);
            	num = ingreso.persona.dni;// DNI numerico
            		
            	while((!feof(fper))&&(!encontrado)){
            			
            			
            			
            		if(persona.dni == num){            
            				
            			encontrado = 1;
            				
					}
						
					fread(&persona,sizeof(Persona),1,fper);
				}
					
				if(!encontrado){
			
					persona.dni = num;
					strcpy(persona.nombre, Cad1);
					fseek(fper,sizeof(Persona)*(-1),SEEK_CUR);
					fwrite(&persona,sizeof(Persona),1,fper);
							
				}
						
				fclose(fper);
				}
				else{
					printf("\nError al abrir el archivo.\n");
				}
				
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
					printf("\nIngreso Anterior Guarado En El ID: %llu\n\n",ingreso.codIngreso);
					
				}
				else{
					
					c=0;
					
				}
			}
		}	
	}	
}

/////////////////////////////////////////REGISTRAR PAGO/////////////////////////////////////////////////////////////////////////////////////////////

void registrarPago(){
	
	FILE *f1;
    int s,i, c, aux_anio, aux_mes, aux_dia,opc,ac,cnt, pagado;
    unsigned long long IDaux;
    char montox[100],Cad3[50],Cad4[50000],CaEst[25];
    double comp_corr, Cuota;
    Gasto gastoa;
    
   
    s=gastosExsistentes();
    //printf("\ns= %d",s);
   

    if(!s){
    	
    	printf("\nNo Existen Gastos Pendientes, Sera Rediriguido Al Menu\n\n");
    	system("PAUSE");
	}
    
    
    
    while(s){
		
        if((f1 = fopen("gastos.dat", "r+b")) != NULL){
        	
			rewind(f1);
            ac=1;
            
			while(ac){
				
				
				
				s=1;
				while(s){
					system("cls");
					pagado = 0;
	                printf("------------------\n3.REGISTRAR PAGO\n------------------");
					listaGastos();
					
					fflush(stdin);
					gets(Cad4);
					
					comp_corr=digitosC(Cad4);
					
					IDaux=atoll(Cad4);
					if((comp_corr==0)||(IDaux<1)){
						system("cls");
						printf("\nError, Tiene Que Ingresar Un Numero Entero Mayor a 0 Y Sin Caracteres, Solo Digitos\n\n");
						system("PAUSE");
					}else{
						s=0;
					}
					
				}
				
				
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
				
				
				rewind(f1);
				c=1;
				fread(&gasto,sizeof(Gasto),1,f1);
				while((c)&&(!feof(f1))){
					
					if(IDaux==gasto.codGasto){
						
						c=0;
						ac=0;
							
					}
					else{
						
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
				else{
					if(gasto.restanteCuota == 0){
					
						ac = 1;                             
						pagado = 1;
						system("cls");
						printf("\nEste Gasto Ya Esta Completamente Pagado. Intentelo Nuevamente\n\n");
						system("PAUSE");
						system("cls");
						
					}
				} 				
					
			}
			
			cnt=1;
			
			gastoa=gasto;
			
			while((cnt)&&(!pagado)){
			
				c=1;
				
				while(c){
            		
					system("cls");
					printf("------------------\n3.REGISTRAR PAGO\n------------------\n");
					printf("\nID De Gasto Seleccionado: %lld",IDaux);
					printf("\n\nCon %d Cuotas En Total La Cuota Actual %s Es La Numero %d\nCon Un Valor De $%.3lf Siendo El Total Monto Restante $%.3lf",gastoa.cuotasTotales,CaEst,gastoa.cuotaActual,gastoa.restanteCuota,gastoa.deudaTotal);
					printf("\n\nIngrese El Medio De Pago\n\n1. Efectivo\n2. Billetera Electronica\n3. Tarjeta\n4. Debito\n\nElija Una Opcion: ");
					
					fflush(stdin);
					gets(Cad4);
					
					
					opc=digitosC(Cad4);
					
					if(opc<1){
						
            			system("cls");
            			printf("\nIngrese Correctamente El Tipo De Medio De Pago, Solo Puede Ser Numeros Enteros\n");
            			system("PAUSE");
            			system("cls");
            			
					}
					else{
						
						c=0;
						
					}
            		
				}
			
				switch(opc){
					case 1:
						strcpy(Cad3,"Efectivo");
						printf("\n\nTipo De Medio De Pago: Efectivo");
						i=1;
						cnt=0;
						break;
					case 2:
						strcpy(Cad3,"Billetera Electronica");
						printf("\n\nTipo De Medio De Pago: Billetera Electronica");
						cnt=0;
						i=2;
						break;
					case 3:
						strcpy(Cad3,"Tarjeta");
						printf("\n\nTipo De Medio De Pago: Tarjeta");
						cnt=0;
						i=3;
						break;
					case 4:
						strcpy(Cad3,"Debito");
						printf("\n\nTipo De Medio De Pago: Debito");
						cnt=0;
						i=4;
						break;					
					default:
						system("cls");
						printf("\nIngrese Un Numero Valido Del 1-4 De Tipo Entero\n\n");
						system("PAUSE");
						system("cls");
						
						
						printf("------------------\n3.REGISTRAR PAGO\n------------------\n");
						printf("\nID De Gasto Seleccionado: %lld\n\n",IDaux);
						printf("Con %d Cuotas En Total La Cuota Actual %s Es La Numero %d\nCon Un Valor De $%.3lf Siendo El Total Monto Restante $%.3lf\n",gastoa.cuotasTotales,CaEst,gastoa.cuotaActual,gastoa.restanteCuota,gastoa.deudaTotal);
				}
				
			}	
			
			system("cls");
			printf("------------------\n3.REGISTRAR PAGO\n------------------\n");
			printf("\nID De Gasto Seleccionado: %lld\n\n",IDaux);
			printf("Tipo De Medio De Pago Seleccionado: %s\n",Cad3);
			printf("\nCon %d Cuotas En Total La Cuota Actual %s Es La Numero %d\nCon Un Valor De $%.3lf Siendo El Total Monto Restante $%.3lf\n",gastoa.cuotasTotales,CaEst,gastoa.cuotaActual,gastoa.restanteCuota,gastoa.deudaTotal);
			
			c=1;
			
			while(c){
				
				printf("\nIngrese El Monto A Abonar: $");
				
				fflush(stdin);
				gets(montox);
				
				comp_corr=digitos(montox);
				
				
				if((comp_corr==0)||(comp_corr>gasto.restanteCuota)){ 
				 
					system("cls");
					printf("\nIngrese Un Monto Valido Mayor A 0 Y Que Sean Unicamente Numeros, Maximo De Tres Decimales, NO Puede Superar El Valor De La Cuota\n\n");
					system("PAUSE");
					system("cls");	
					
						
					printf("------------------\n3.REGISTRAR PAGO\n------------------\n");
					printf("\nID De Gasto Seleccionado: %lld\n\n",IDaux);
					printf("Tipo De Medio De Pago Seleccionado: %s\n\n",Cad3);
					printf("Con %d Cuotas En Total La Cuota Actual %s Es La Numero %d\nCon Un Valor De $%.3lf Siendo El Total Monto Restante $%.3lf\n",gastoa.cuotasTotales,CaEst,gastoa.cuotaActual,gastoa.restanteCuota,gastoa.deudaTotal);
					
				}
				else{
					
					//gasto.restanteCuota=Cuota;
					pago.importe=atof(montox);
					c=0;

					
				
					gasto.restanteCuota=(gasto.restanteCuota-pago.importe);
					gasto.deudaTotal=(gasto.deudaTotal-pago.importe);
					
					
					
				
					if (gasto.restanteCuota > EPSILON) {
						
						gasto.estadoCuota = 2;
						
					}
					else {
						
						gasto.restanteCuota = 0.0;
						
						if (gasto.cuotaActual == gasto.cuotasTotales) {
							
							gasto.estadoCuota = 3; 
							
														
						}
						else {
							
							
							
							gasto.estadoCuota = 1;// Pasa a estar "que adeuda" la proxima cuota
							
							// Calcula el valor de la proxima cuota
							Cuota=(gasto.cuotasTotales-gasto.cuotaActual);
							gasto.restanteCuota=(gasto.deudaTotal/Cuota);
							
						}
						
						if(gasto.cuotaActual<gasto.cuotasTotales){
							
							gasto.cuotaActual++;// Incrementa la cuota actual si no es la ultima
							
						}
					}	
				}
			}
				
			c = 1;
			
			while(c){// Bucle para ingresar y validar la fecha del pago
				
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
					printf("Con %d Cuotas En Total La Cuota Actual %s Es La Numero %d\nCon Un Valor De $%.3lf Siendo El Total Monto Restante $%.3lf\n",gastoa.cuotasTotales,CaEst,gastoa.cuotaActual,gastoa.restanteCuota,gastoa.deudaTotal);
					printf("\nTipo De Medio De Pago Seleccionado: %s\n\n",Cad3);
					printf("Monto Abonado: %.3lf\n",pago.importe);
					
				}
			}
			
			// Almacena la fecha de pago
			pago.fechaPago.anio = aux_anio;
			pago.fechaPago.mes = aux_mes;
			pago.fechaPago.dia = aux_dia;
			
			
			pago.codGasto=IDaux;
			
			printf("----------------------------------------------------------\n");
			
			pago.medioPago=i;
			
			// Escribe la estructura 'gasto' actualizada en el archivo (sobrescribiendo el registro)
			fseek(f1,sizeof(Gasto)*(-1),SEEK_CUR);
			fwrite(&gasto,sizeof(Gasto),1,f1);
			
			guardarPago(pago);// Guarda el registro de pago
			
			
			c=1;
			
			while(c){// Bucle para preguntar si desea registrar otro pago
				
					printf("\nDesea Registrar Otro Pago?\n\n1. Si, Aplicar Seguir\n0. No, Aplicar Y Finalizar\n\nElija Una Opcion: ");
					scanf("%d", &s);
					
					if((s!=0)&&(s!=1)){
						
						system("cls");
						printf("\nIngrese Un Valor Entero Correcto 1/0\n\n");
						system("PAUSE");
						system("cls");
						
						printf("------------------\n3.REGISTRAR PAGO\n------------------\n");
						printf("\nPago Anterior Guarado En El ID: %llu\n\n", IDaux);
						
					}
					else{
						
						c=0;
						
					}
	
				}
				fclose(f1);// Cierra el archivo de gastos
				
				if(s){// Si el usuario quiere continuar, verifica que aun existan gastos pendientes
					s=gastosExsistentes();
					if(!s){
						system("cls");
						printf("\nERROR, No Existe Ningun Gasto Pendiente, Sera Rediriguido Al Menu\n\n");
						system("PAUSE");
					}
				}
				
		}
		else{
			
			printf("\nError al abrir el archivo Gastos");
			system("PAUSE");
			
		}
	}
}

///////////////////////////////////////// LISTAR GASTOS E INGRESOS ///////////////////////////////////////////////////////////////////////////////////

void listarGastoseIngresos() {
	char Cad15[50000];
    int opc, s = 1, seguir=1;
    
    while (s) {
    	
    	system("cls");
        printf("\nEscoja lo que desea listar:\n\n1. Gastos\n2. Ingresos\n3. Volver al Menu Principal\n\nElija una opcion: ");
        fflush(stdin);
        gets(Cad15);
        opc=digitosC(Cad15);
        
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
            	system("cls");
                printf("\nIngrese un numero valido del 1-4 de tipo entero\n\n");
				system("pause");
        }
        
        if (s) {
        	seguir=1;
        	while(seguir){
	        	
                system("cls");
                printf("\nDesea realizar otro listado?\n\n2. Si\n1. No, finalizar : \t ");
                fflush(stdin);
                gets(Cad15);
        		opc=digitosC(Cad15);
	            
	            if((opc<1)||(opc>2)){
	                system("cls");
		            printf("\nIngresar Correctamente La Opcion (2 si, 1 no)\n\n");
		        	
		        	system("PAUSE");
		        	system("cls");
				}else{
					if(opc==2){
						opc=1;
						seguir=0;
					}else{
						if(opc){
			               	s = 0;
			               	seguir=0;
			            }
					}
		            
				}
					
			
            
            }
        	
        }
    }
}

///////////////////////////////////////// CONSULTAS Y REPORTES ///////////////////////////////////////////////////////////////////////////////////////

void consultasyReportes() {
	char Cad23[50000];
    int opc, s = 1, seguir,aaa1=1;
    
    while (s) {
    	
    	system("cls"); //ver
        printf("\nEscoja la consulta/reporte a realizar:\n\n1. Gastos por Categoria\n2. Gastos Por Mes y Anio\n3. Ingresos Por Persona\n4. Saldo Mensual\n5. Gastos Pendientes\n6. Pagos Por Medio de Pago\n7. Gastos con Saldo Incompleto\n8. Top 3 Categorias Mas Costosas\n9. Proyeccion Mensual\n10. Resumen General\n11. Volver al Menu Principal\n\nElija una opcion: ");
        fflush(stdin);
        gets(Cad23);
        opc=digitosC(Cad23);
        
        switch (opc) {
            case 1:      
                gastosPorCategoria();
                break;
            case 2:  
                gastosPorMesYAnio();
                break;
            case 3:        
                ingresosPorPersona();
                break;
            case 4:                
                saldoMensual();
                break;
            case 5:
                gastosPendientes();
                break;
            case 6:
                pagosPorMedioDePago();
                break;
            case 7:
                gastosConSaldoIncompleto();
                break;
            case 8:
                top3CategoriasMasCostosas();
                break;
            case 9:
                proyeccionMensual();
                break;
            case 10:
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
            	aaa1=1;
            	while(aaa1){
	            	system("cls");
	                printf("\nDesea realizar otra consulta/reporte?\n\n2. Si\n1. No, finalizar : \t ");
	                fflush(stdin);
	                gets(Cad23);
	        		opc=digitosC(Cad23);
	        		
	        		if ((opc==0)||((opc != 1) && (opc != 2))) {
	                	
	                    system("cls");
	                    printf("\nOpcion invalida. Intentelo de nuevo. Ingrese un numero valido del 2-1 de tipo entero.\n");
	                    system("PAUSE");
	                    
              	  }else{
              	  		aaa1=0;
					}
				}
                
                if(opc==1){
                	opc=0;
				}else{
					if (!opc) {
	                	
	                    s = 0;
	                    
	                }
				}
                
                
                
            }
        }
    }
}

///////////////////////////////////////// administracion ///////////////////////////////////////////////////////////////////////////////////////

void administracion(){
	
	char eli[1],confirmacion_str[10];
    int elim, elvf = 1,s,g,confirmaciones;
    
    while (elvf) {// Bucle de menu de administracion
    	system("cls");
		printf("\n----------------------\n6.MENU DE ELIMINACION\n----------------------");
        
        printf("\nIngrese Una Opcion De Elimando\n\n1. Eliminacion De Gastos\n2. Eliminacion De Ingresos\n3. Eliminacion De Pagos\n4. Eliminacion De Categorias\n5. Eliminacion De Personas\n6. Restablecimiento De Fabrica\n7. Volver Al Menu\n\nElija Una Opcion: ");
        fflush(stdin);
        gets(eli);// Captura la opcion como cadena
        
        elim = atoi(eli);// Convierte la opcion a entero
        
        switch (elim) {
            case 1:
                system("cls");
                eliminarGasto();
                break;
            case 2:
                system("cls");
                eliminarIngreso();
                break;
            case 3:
                system("cls");
                eliminarPago();
                break;
            case 4:
                system("cls");
                eliminarCategoria();
                break;    
            case 5:
                system("cls");
                eliminarPersona();
                break;
			case 6:
                system("cls");// Restablecimiento de Fabrica
                
                s = 1; // Bandera para continuar con las advertencias
                g = 0; // Bandera para ejecutar el borrado
                confirmaciones = 0; // Contador de confirmaciones
                
                
                printf("\n----------------------\n6. RESTABLECIMIENTO DE FABRICA\n----------------------\n");

                // === PRIMERA ADVERTENCIA ===
                if (s) {
                    printf("\n=== ADVERTENCIA 1/3 ===\n");
                    printf("Se Eliminaran PERMANENTEMENTE Todos Los Archivos Del Sistema De Datos\n");
                    printf("\nEsta Seguro Que Desea Continuar Con El Borrado? (si/no): ");
                    fflush(stdin);
                    scanf("%s", confirmacion_str);
                    
                    if (strcmp(confirmacion_str, "si") != 0 && strcmp(confirmacion_str, "SI") != 0) {
                        s = 0; // Cancelar
                    } else {
                        confirmaciones++;
                    }
                }
                
                // === SEGUNDA ADVERTENCIA ===
                if (s) { 
                    printf("\n=== ADVERTENCIA 2/3 ===\n");
                    printf("Esta Accion NO Se Puede Deshacer. Todos Los Datos Seran IRRECUPERABLES\n");
                    printf("\nConfirma La Eliminacion TOTAL? (si/no): ");
                    fflush(stdin);
                    scanf("%s", confirmacion_str);
                    
                    if (strcmp(confirmacion_str, "si") != 0 && strcmp(confirmacion_str, "SI") != 0) {
                        s = 0; // Cancelar
                    } else {
                        confirmaciones++;
                    }
                }
                
                // === TERCERA ADVERTENCIA (CONFIRMACION FINAL) ===
                if (s) { 
                    printf("\n=== ADVERTENCIA 3/3 ===\n");
                    printf("CONFIRMACION FINAL. Escriba 'si' Para Eliminar DEFINITIVAMENTE Todos Los Archivos: ");
                    fflush(stdin);
                    scanf("%s", confirmacion_str);
                    
                    if (strcmp(confirmacion_str, "si") != 0 && strcmp(confirmacion_str, "SI") != 0) {
                        s = 0; // Cancelar
                    } else {
                        confirmaciones++;
                    }
                }
                
                
                if (s && confirmaciones == 3) {
                    g = 1; // Activar la bandera de borrado
                }
                
                if (g == 1) {// Ejecuta el borrado si se confirmo 3 veces
                
                    system("cls");
                    // Logica de borrado
                    remove("categorias.dat");
                    remove("gastos.dat");
                    remove("ingresos.dat");
                    remove("pagos.dat");
                    remove("personas.dat");
                    
                    printf("\n----------------------\n6. RESTABLECIMIENTO DE FABRICA\n----------------------");
                    printf("\n\n\tBORRADO COMPLETO\n\n");
                    system("PAUSE");
                    elvf = 0; // Sale del bucle de administracion
                
                } else {
                    system("cls");
                    printf("\n----------------------\n6. RESTABLECIMIENTO DE FABRICA\n----------------------\n");
                    
                    if (confirmaciones < 3) {
                        printf("\nFallo en la triple confirmacion (solo %d de 3).", confirmaciones);
                    }
                    printf("\n\tOPERACION CANCELADA\n\n");
                    system("PAUSE");
                }
  	  			
                break;     
            case 7:
                elvf = 0;// Sale del bucle
                break;                
            default:
                printf("\nIngrese Un Numero Valido Del 1-7 De Tipo Entero\n\n");
                system("PAUSE");
        }
    }
	
	
	
}

///////////////////////////////////////// eliminarPersona ///////////////////////////////////////////////////////////////////////////////////////

void eliminarPersona(){
	
    FILE *fing, *fgas, *fpag, *ftemp, *fper;
    long long dniEliminar;
    unsigned long long gastosEliminados[1000];
    char confirmacion[10], opcionEliminacion[10], Cad8[9];
    int encontrado = 0, confirmaciones = 0, tipoEliminacion = 0, c, comp_corr,terminarFuncion = 0,i,tieneGastos = 0,salirBucle = 0,existeEnPersonas = 0,pagosEliminados = 0,eliminarPago = 0,personasEliminadas = 0,tieneIngresos=0,registrosEliminados = 0,cantGastosEliminados = 0;
    Persona personaTemp;
    
    system("cls");
    printf("------------------\nELIMINAR PERSONA\n------------------\n");
    
    //Bucle de ingreso y validacion de DNI
    c = 1;
    
    while(c){
        
        printf("\nIngrese El DNI Del Responsable Del Gasto: ");
        fflush(stdin);
        gets(Cad8);
    
        dniEliminar=digitosDNI(Cad8);
        comp_corr=digitos(Cad8);
                    
        if((strlen(Cad8)>8)||(strlen(Cad8)<6)||(comp_corr==0)){
                        
            system("cls");
            printf("\nNo Se Permite Mas De 8 Numeros En El DNI, O Menor A 6 Numeros, Y Que Sean Unicamente Numeros.\nPor Favor, Vuelva A Ingresarlo\n\n");
            system("PAUSE");
            system("cls");
                        
                    
        }
        else{
                
            c=0; // Sale del while
                        
        }
                    
    }
    
    
    tieneIngresos = 0;
    
    // === 2. Busqueda inicial en archivos
    
    // Buscar en gastos
    if ((fgas = fopen("gastos.dat", "rb")) != NULL) {
        salirBucle = 0; 
        while ( (fread(&gasto, sizeof(Gasto), 1, fgas)) && (!salirBucle) ) {
            if (gasto.persona.dni == dniEliminar) {
                tieneGastos = 1;
                encontrado = 1;
                salirBucle = 1;
            }
        }
        fclose(fgas);
    }
    
    
    // Buscar en ingresos
    if ((fing = fopen("ingresos.dat", "rb")) != NULL) {
        salirBucle = 0;
        while ( (fread(&ingreso, sizeof(Ingreso), 1, fing)) && (!salirBucle) ) {
            if (ingreso.persona.dni == dniEliminar) {
                tieneIngresos = 1;
                encontrado = 1;
                salirBucle = 1;
            }
        }
        fclose(fing);
    }
    
    
    // Buscar en personas
    existeEnPersonas = 0;
    if ((fper = fopen("personas.dat", "rb")) != NULL) {
        salirBucle = 0;
        while ( (fread(&personaTemp, sizeof(Persona), 1, fper)) && (!salirBucle) ) {
            if (personaTemp.dni == dniEliminar) {
                existeEnPersonas = 1;
                encontrado = 1;
                salirBucle = 1;
            }
        }
        fclose(fper);
    }
    
    // === 3. Control de 'No encontrado'
    if (!encontrado) {
        printf("\nNo Se Encontraron Registros Con El DNI: %lld\n\n", dniEliminar);
        system("PAUSE");
        // Reemplaza el 'return' de salida inmediata
        terminarFuncion = 1;
    }
    
  
    if (!terminarFuncion) {
        
        printf("\n=== REGISTROS ENCONTRADOS ===\n");
        
        // === 4. Listar Registros Encontrados
        
        if (tieneGastos) {
            printf("\nGASTOS:\n");
            if ((fgas = fopen("gastos.dat", "rb")) != NULL) {
                while (fread(&gasto, sizeof(Gasto), 1, fgas)) {
                    if (gasto.persona.dni == dniEliminar) {
                        printf("- Gasto ID: %llu | Desc: %s | Monto: $%.2lf\n",gasto.codGasto, gasto.desc, gasto.monto);
                    }
                }
                fclose(fgas);
            }
        }
        
        
        if (tieneIngresos) {
            printf("\nINGRESOS:\n");
            if ((fing = fopen("ingresos.dat", "rb")) != NULL) {
                while (fread(&ingreso, sizeof(Ingreso), 1, fing)) {
                    if (ingreso.persona.dni == dniEliminar) {
                        printf("- Ingreso ID: %llu | Concepto: %s | Monto: $%.2lf\n", 
                               ingreso.codIngreso, ingreso.concepto, ingreso.monto);
                    }
                }
                fclose(fing);
            }
        }
        
        
        if (existeEnPersonas) {
            printf("\nREGISTRO EN PERSONAS.DAT:\n");
            if ((fper = fopen("personas.dat", "rb")) != NULL) {
            	
                salirBucle = 0;
                while ( (fread(&personaTemp, sizeof(Persona), 1, fper)) && (!salirBucle) ) {
                    if (personaTemp.dni == dniEliminar) {
                        printf("- Persona: %s | DNI: %lld\n", 
                               personaTemp.nombre, personaTemp.dni);
                        salirBucle = 1;
                    }
                }
                fclose(fper);
            }
        }
        
        // === 5. Seleccion de Tipo de Eliminacion
        
        printf("\n=== TIPO DE ELIMINACION ===\n");
        printf("Que Desea Eliminar?\n");
        printf("1. Eliminacion COMPLETA (Todos Los Gastos E Ingresos)\n");
        printf("2. Eliminar Solo GASTOS (Y Sus Pagos Asociados)\n");
        printf("3. Cancelar Operacion\n");
        printf("\nElija Una Opcion (1-3): ");
        scanf("%s", opcionEliminacion);
        
        if (strcmp(opcionEliminacion, "3") == 0) {
            printf("\nOperacion Cancelada Por El Usuario.\n\n");
            system("PAUSE");
            terminarFuncion = 1;
        }
        
        if (!terminarFuncion) { // Solo si no se cancelo en el paso anterior
            if (strcmp(opcionEliminacion, "1") == 0) {
                tipoEliminacion = 1;
            } else if (strcmp(opcionEliminacion, "2") == 0) {
                tipoEliminacion = 2; 
            } else {
                printf("\nOpcion No Valida. Operacion Cancelada.\n\n");
                system("PAUSE");
                terminarFuncion = 1;
            }
        }
        
        // === 6. Confirmaciones de EliminaciÃƒÂ³n ===
        
        if (!terminarFuncion) { // Continuar solo si no se ha cancelado
            
            if (tipoEliminacion == 1) {
                printf("\n=== ELIMINACION COMPLETA SELECCIONADA ===\n");
                printf("Se Eliminaran TODOS Los Gastos, Ingresos Y Pagos Asociados.\n");
                if (existeEnPersonas) {
                    printf("Tambien Se Eliminara El Registro De personas.dat.\n");
                }
            } else {
                printf("\n=== ELIMINACION DE GASTOS SELECCIONADA ===\n");
                printf("Se Eliminaran SOLO Los Gastos Y Sus Pagos Asociados.\n");
                if (tieneIngresos) {
                    printf("Los Ingresos Se Conservaran.\n");
                }
                if (existeEnPersonas) {
                    printf("El Registro De personas.dat Se Conservara.\n");
                }
            }
            
            // Advertencia 1/3
            printf("\n=== ADVERTENCIA 1/3 ===\n");
            if (tipoEliminacion == 1) {
                printf("Esta Accion Eliminara TODOS Los Gastos E Ingresos De Esta Persona.\n");
                if (existeEnPersonas) {
                    printf("Tambien Se Eliminara El Registro De personas.dat.\n");
                }
            } else {
                printf("Esta Accion Eliminara TODOS Los Gastos De Esta Persona.\n");
            }
            printf("Los Pagos Asociados A Los Gastos Tambien Se Eliminaran.\n");
            printf("Esta Accion NO Se Puede Deshacer.\n");
            printf("\nEsta Seguro Que Desea Continuar? (si/no): ");
            scanf("%s", confirmacion);
            
            if (strcmp(confirmacion, "si") != 0 && strcmp(confirmacion, "SI") != 0) {
                printf("\nOperacion Cancelada Por El Usuario.\n\n");
                system("PAUSE");
                terminarFuncion = 1;
            }
            
            if (!terminarFuncion) {
                confirmaciones++;
                
                // Advertencia 2/3
                printf("\n=== ADVERTENCIA 2/3 ===\n");
                printf("Esta A Punto De Eliminar Permanentemente Los Registros.\n");
                printf("Esta ABSOLUTAMENTE Seguro? (si/no): ");
                scanf("%s", confirmacion);
                
                if (strcmp(confirmacion, "si") != 0 && strcmp(confirmacion, "SI") != 0) {
                    printf("\nOperacion Cancelada Por El Usuario.\n");
                    system("PAUSE");
                    terminarFuncion = 1;
                }
            }
            
            if (!terminarFuncion) {
                confirmaciones++;
                
                // Advertencia 3/3
                printf("\n=== ADVERTENCIA 3/3 ===\n");
                printf("ULTIMA OPORTUNIDAD Para Cancelar.\n");
                printf("CONFIRMA La Eliminacion Definitiva? (si/no): ");
                scanf("%s", confirmacion);
                
                if (strcmp(confirmacion, "si") != 0 && strcmp(confirmacion, "SI") != 0) {
                    printf("\nOperacion Cancelada Por El Usuario.\n\n");
                    system("PAUSE");
                    terminarFuncion = 1;
                }
            }
            
            if (!terminarFuncion) {
                confirmaciones++;
            }
        }
        
  
        
        if (!terminarFuncion) {
            
            if (confirmaciones == 3) {
                registrosEliminados = 0;
                
                // Arrays para guardar los codigos de gasto a eliminar
                cantGastosEliminados = 0;
                
          
                if ((fgas = fopen("gastos.dat", "rb")) != NULL) {
                    if ((ftemp = fopen("gastos_temp.dat", "wb")) != NULL) {
                        while (fread(&gasto, sizeof(Gasto), 1, fgas)) {
                            if (gasto.persona.dni == dniEliminar) {
                                
                                gastosEliminados[cantGastosEliminados++] = gasto.codGasto;
                                registrosEliminados++;
                            } else {
                                fwrite(&gasto, sizeof(Gasto), 1, ftemp);
                            }
                        }
                        fclose(ftemp);
                        fclose(fgas);
                        
                        
                        remove("gastos.dat");
                        rename("gastos_temp.dat", "gastos.dat");
                    }
                }
                
                
               
                if (tipoEliminacion == 1 && tieneIngresos) {
                    if ((fing = fopen("ingresos.dat", "rb")) != NULL) {
                        if ((ftemp = fopen("ingresos_temp.dat", "wb")) != NULL) {
                            while (fread(&ingreso, sizeof(Ingreso), 1, fing)) {
                                if (ingreso.persona.dni != dniEliminar) {
                                    fwrite(&ingreso, sizeof(Ingreso), 1, ftemp);
                                } else {
                                    registrosEliminados++;
                                }
                            }
                            fclose(ftemp);
                            fclose(fing);
                            
                            
                            remove("ingresos.dat");
                            rename("ingresos_temp.dat", "ingresos.dat");
                        }
                    }
                }
                
                
                // 7.3. Eliminacion de Pagos asociados a los gastos eliminados
                if ((fpag = fopen("pagos.dat", "rb")) != NULL) {
                    if ((ftemp = fopen("pagos_temp.dat", "wb")) != NULL) {
                        int pagosEliminados = 0;
                        while (fread(&pago, sizeof(Pago), 1, fpag)) {
                            eliminarPago = 0;
                            
                            i = 0; // Inicializacion de la variable de control 'i'
                            while ((i < cantGastosEliminados) && (!eliminarPago)) { // Condicion
                                if (pago.codGasto == gastosEliminados[i]) {
                                    eliminarPago = 1;
                                    pagosEliminados++;
                                }
                                i++; // Incremento
                            }
                            
                            if (!eliminarPago) {
                                fwrite(&pago, sizeof(Pago), 1, ftemp);
                            }
                        }
                        fclose(ftemp);
                        fclose(fpag);
                        
                        
                        remove("pagos.dat");
                        rename("pagos_temp.dat", "pagos.dat");
                        
                        registrosEliminados += pagosEliminados;
                    }
                }
                
                
               
                if (tipoEliminacion == 1 && existeEnPersonas) {
                    if ((fper = fopen("personas.dat", "rb")) != NULL) {
                        if ((ftemp = fopen("personas_temp.dat", "wb")) != NULL) {
                            personasEliminadas = 0;
                            while (fread(&personaTemp, sizeof(Persona), 1, fper)) {
                                if (personaTemp.dni != dniEliminar) {
                                    fwrite(&personaTemp, sizeof(Persona), 1, ftemp);
                                } else {
                                    personasEliminadas++;
                                }
                            }
                            fclose(ftemp);
                            fclose(fper);
                            
                            
                            remove("personas.dat");
                            rename("personas_temp.dat", "personas.dat");
                            
                            registrosEliminados += personasEliminadas;
                        }
                    }
                }
            
            
                printf("\n=== ELIMINACION COMPLETADA ===\n");
                if (tipoEliminacion == 1) {
                    printf("ELIMINACION COMPLETA Realizada.\n");
                } else {
                    printf("ELIMINACION DE GASTOS Realizada.\n");
                }
                printf("Se Eliminaron %d Registros Asociados Al DNI: %lld\n", registrosEliminados, dniEliminar);
                
            } else {
                // === 9. Mensaje de Error en Confirmaciones ===
                printf("\nError En Las Confirmaciones. Operacion Cancelada.\n");
            }
        }
    }
    
// Pausa final
    if (encontrado || terminarFuncion) {
        system("PAUSE");
    }
    

	
}

///////////////////////////////////////// eliminarPersona ///////////////////////////////////////////////////////////////////////////////////////

void eliminarGasto(){
	// Declaracion de archivos
	FILE *fgas, *fpag, *ftemp;
    // Variables de estado y control.
    int estadoGlobal = 1, confirmaciones = 0, encontrado = 0, c, condicion1, condicion2, registrosEliminados = 0, idSeleccionadoEsValido = 0,pagosEliminados = 0;;
    // Codigo del gasto a eliminar y variables de lectura
    unsigned long long codGastoEliminar = 0;
    char Cad4[50], confirmacion[10];
    Gasto gastoWrite;
    Pago pagoTemp;
    
    
    system("cls");
    // Titulo de la operacion
    printf("------------------------------------------\n");
    printf("Gastos Con Estado/Cuota Incompleto/Inconsistente\n");
    printf("------------------------------------------\n\n");
    
    // --- 1. FILTRAR Y LISTAR INCONSISTENCIAS ---
    
    // Intentar abrir el archivo de gastos
    if ((fgas = fopen("gastos.dat", "rb")) == NULL) {
        printf("Error, No Se Pudo Abrir El Archivo De Gastos\n\n");
        system("PAUSE");
        estadoGlobal = 0;
    }
    
    if (estadoGlobal) {
        // Cabecera de la lista de inconsistencias
        printf("Id Gasto | Tipo | Cuota Act/Tot | Monto Total | Deuda Actual | Descripcion\n");
        printf("--------------------------------------------------------------------------------\n");

        // Lectura inicial para el bucle de lectura con feof
        fread(&gasto, sizeof(Gasto), 1, fgas);

        // Recorre el archivo para filtrar los gastos
        while (!feof(fgas)) {
            
            // Condicion 1: Estado 1 (No pagado) Y Cuota 2 (Inconsistencia de cuota)
            condicion1 = (gasto.estadoCuota == 1 && gasto.cuotaActual == 2);
            
            // Condicion 2: Estado 2 (Parcial) Y Cuota 1 (Inconsistencia de cuota/saldo)
            condicion2 = (gasto.estadoCuota == 2 && gasto.cuotaActual == 1);
            
            if (condicion1 || condicion2) {
                // Imprimir el registro inconsistente
                printf("%-8llu | %-4d | %3d/%-3d | $%-11.2lf | $%-12.2lf | %s\n",
                       gasto.codGasto, gasto.tipoGasto, gasto.cuotaActual, gasto.cuotasTotales, 
                       gasto.monto, gasto.deudaTotal, gasto.desc);
                encontrado++; // Contar gastos encontrados
            }
            
            // Lectura del siguiente registro
            fread(&gasto, sizeof(Gasto), 1, fgas);
        }
        
        // Cerrar el archivo despues de la lectura
        if (fgas != NULL) {
            fclose(fgas);
        }
        
        printf("--------------------------------------------------------------------------------\n");

        if (encontrado == 0) {
            printf("No Se Encontraron Gastos Que Cumplan Con Las Condiciones De Saldo Incompleto/Inconsistente.\n\n");
            system("PAUSE");
            estadoGlobal = 0; // Detiene la ejecucion si no hay registros
        }
    }
    
    // --- 2. PEDIR ID DEL GASTO A ELIMINAR (Y VALIDAR CONTRA EL ARCHIVO) ---
    if (estadoGlobal) {
        
        c = 1; // Inicializa el control del bucle de validacion de ID
        while(c){
            printf("\nTotal De Registros: %d\n", encontrado);
            printf("Ingrese El Id Del Gasto Con Error Que Desea Eliminar: ");
            fflush(stdin);
            gets(Cad4); 
        
            codGastoEliminar = atoll(Cad4);
            idSeleccionadoEsValido = 0; // Reiniciar estado de validacion
            
            // Validacion de formato: ID es cero o no son solo digitos.
            if (codGastoEliminar == 0 || digitosC(Cad4) == 0) {
                // El error se maneja en el siguiente if.
            }
            // ********** VALIDACION DE EXISTENCIA Y CONDICION **********
            else if ((fgas = fopen("gastos.dat", "rb")) != NULL) {
                
                fread(&gasto, sizeof(Gasto), 1, fgas);
                while (!feof(fgas) && !idSeleccionadoEsValido) { // Salir si se valida o termina el archivo
                     // Verificar si el ID existe Y cumple las condiciones de inconsistencia
                     if (gasto.codGasto == codGastoEliminar) {
                         condicion1 = (gasto.estadoCuota == 1 && gasto.cuotaActual == 2);
                         condicion2 = (gasto.estadoCuota == 2 && gasto.cuotaActual == 1);
                         
                         if (condicion1 || condicion2) {
                             idSeleccionadoEsValido = 1; // ID VALIDO EN LA LISTA
                         }
                     }
                     fread(&gasto, sizeof(Gasto), 1, fgas);
                }
                if (fgas != NULL) {
                    fclose(fgas);
                }
            } else {
                printf("\nError Critico Al Reabrir El Archivo De Gastos Para Validacion.\n");
                estadoGlobal = 0; // Error fatal
            }

            // Manejo de errores de formato O seleccion de ID no listado
            if (!idSeleccionadoEsValido && estadoGlobal) {
                system("cls");
                printf("\nError, El Id Ingresado Es Invalido O No Corresponde A Un Gasto Listado Con Inconsistencias.\n\n");
                system("PAUSE");
                
                // Regenerar la lista despues del error (usando el patron de lectura exigido)
                printf("------------------------------------------\n");
                printf("Gastos Con Estado/Cuota Incompleto/Inconsistente\n");
                printf("------------------------------------------\n\n");
                
                if ((fgas = fopen("gastos.dat", "rb")) != NULL) {
                    printf("Id Gasto | Tipo | Cuota Act/Tot | Monto Total | Deuda Actual | Descripcion\n");
                    printf("--------------------------------------------------------------------------------\n");
                    
                    fread(&gasto, sizeof(Gasto), 1, fgas);
                    while (!feof(fgas)) {
                         condicion1 = (gasto.estadoCuota == 1 && gasto.cuotaActual == 2);
                         condicion2 = (gasto.estadoCuota == 2 && gasto.cuotaActual == 1);
                         if (condicion1 || condicion2) {
                            printf("%-8llu | %-4d | %3d/%-3d | $%-11.2lf | $%-12.2lf | %s\n",
                            gasto.codGasto, gasto.tipoGasto, gasto.cuotaActual, gasto.cuotasTotales, gasto.monto, gasto.deudaTotal, gasto.desc);
                         }
                         fread(&gasto, sizeof(Gasto), 1, fgas);
                    }

                    if (fgas != NULL) {
                        fclose(fgas);
                    }
                    printf("--------------------------------------------------------------------------------\n");
                }
            }
            // Si el ID es valido y el estado global sigue OK
            else if (idSeleccionadoEsValido && estadoGlobal) {
                c=0; // Sale del bucle de validacion
            }
        }
        
        if (estadoGlobal) {
            printf("\nHa Seleccionado El Gasto Con Id: %llu\n", codGastoEliminar);
        }
    }
    
    // --- 3. TRIPLE CONFIRMACION --- 
    if (estadoGlobal) {
        // Inicializar a 0 antes de la triple confirmacion (ya esta en la declaracion)
        confirmaciones = 0; 
        
        printf("\n\n=== Eliminacion De Gasto Con Inconsistencia ===\n");
        
        // PRIMERA ADVERTENCIA
        printf("\n=== Advertencia 1/3 ===\n");
        printf("Se Procedera A Eliminar Permanentemente El Gasto Id %llu Y Sus Pagos Asociados.\n", codGastoEliminar);
        printf("\nEsta Seguro Que Desea Continuar Con La Eliminacion? (si/no): ");
        scanf("%s", confirmacion);
        
        if (strcmp(confirmacion, "si") == 0 || strcmp(confirmacion, "SI") == 0) {
            confirmaciones++;

            // SEGUNDA ADVERTENCIA 
            printf("\n=== Advertencia 2/3 ===\n");
            printf("Recuerde: Esta Accion No Se Puede Deshacer. Confirma? (si/no): ");
            scanf("%s", confirmacion);
            
            if (strcmp(confirmacion, "si") == 0 || strcmp(confirmacion, "SI") == 0) {
                confirmaciones++;

                // TERCERA ADVERTENCIA
                printf("\n=== Advertencia 3/3 ===\n");
                printf("Confirmacion Final. Eliminar Definitivamente El Gasto Id %llu? (si/no): ", codGastoEliminar);
                scanf("%s", confirmacion);
                
                if (strcmp(confirmacion, "si") == 0 || strcmp(confirmacion, "SI") == 0) {
                    confirmaciones++;
                }
            }
        }
    
        
        // --- 4. EJECUCION DE LA ELIMINACION ---
        if (confirmaciones == 3) { 
            
            // ********************** ELIMINAR GASTO **********************
            // Abrir archivo de gastos en modo lectura binaria
            if ((fgas = fopen("gastos.dat", "rb")) != NULL) {
                // Abrir archivo temporal en modo escritura binaria
                if ((ftemp = fopen("gastos_temp.dat", "wb")) != NULL) {
                    gastoWrite; // Variable temporal para escribir
                    
                    // Lectura con patron exigido
                    fread(&gastoWrite, sizeof(Gasto), 1, fgas);
                    // Copiar todos los gastos excepto el que coincide con el ID a eliminar
                    while (!feof(fgas)) {
                        if (gastoWrite.codGasto != codGastoEliminar) {
                            fwrite(&gastoWrite, sizeof(Gasto), 1, ftemp);
                        } else {
                            registrosEliminados++; // Contar el gasto eliminado
                        }
                        fread(&gastoWrite, sizeof(Gasto), 1, fgas);
                    }
                    
                    // Cerrar archivos
                    if (ftemp != NULL) { fclose(ftemp); }
                    if (fgas != NULL) { fclose(fgas); }
                    
                    // Reemplazar el archivo original con el temporal
                    remove("gastos.dat");
                    rename("gastos_temp.dat", "gastos.dat");
                } else {
                    printf("\nError Al Crear Archivo Temporal Para Gastos. Eliminacion Fallida.\n");
                }
            } else {
                printf("\nError Al Abrir 'gastos.dat' Para Reescritura. Eliminacion Fallida.\n");
            }
            
            // ********************** ELIMINAR PAGOS ASOCIADOS **********************
            // Abrir archivo de pagos en modo lectura binaria
            if ((fpag = fopen("pagos.dat", "rb")) != NULL) {
                // Abrir archivo temporal en modo escritura binaria
                if ((ftemp = fopen("pagos_temp.dat", "wb")) != NULL) {
                    pagoTemp;
                    pagosEliminados = 0; // Contador de pagos eliminados
                    
                    // ELIMINACION PAGOS CON PATRON EXIGIDO
                    fread(&pagoTemp, sizeof(Pago), 1, fpag);
                    // Copiar todos los pagos excepto los asociados al gasto eliminado
                    while (!feof(fpag)) {
                        if (pagoTemp.codGasto != codGastoEliminar) {
                            fwrite(&pagoTemp, sizeof(Pago), 1, ftemp);
                        } else {
                            pagosEliminados++; // Contar el pago eliminado
                        }
                        fread(&pagoTemp, sizeof(Pago), 1, fpag);
                    }
                    
                    // Cerrar archivos
                    if (ftemp != NULL) { fclose(ftemp); }
                    if (fpag != NULL) { fclose(fpag); }
                    
                    // Reemplazar el archivo original con el temporal
                    remove("pagos.dat");
                    rename("pagos_temp.dat", "pagos.dat");
                    
                    registrosEliminados += pagosEliminados;
                } else {
                    printf("\nError Al Crear Archivo Temporal Para Pagos.\n");
                }
            } else {
                printf("\nAdvertencia: No Se Pudo Abrir 'pagos.dat'. Solo Se Elimino El Gasto.\n");
            }
            
            
            printf("\n=== Eliminacion Completada ===\n");
            printf("El Gasto Id: %llu (Con Error De Inconsistencia) Ha Sido Eliminado.\n", codGastoEliminar);
            printf("Total De Registros Eliminados (Gasto + Pagos): %d\n", registrosEliminados);
            
        } else { // Fallo en la triple confirmacion
            printf("\nOperacion De Eliminacion Cancelada Por El Usuario.\n");
            printf("Fallo En La Triple Confirmacion (Solo %d De 3). Operacion Cancelada.\n", confirmaciones);
        }
    }
    
    // Pausa final.
    system("PAUSE");
}

///////////////////////////////////////// eliminarIngreso ///////////////////////////////////////////////////////////////////////////////////////

void eliminarIngreso(){
	
    FILE *fing = NULL, *ftemp = NULL; 
    
    // Buffers para entrada de texto y confirmacion.
    char Cad4[50], confirmacion[10];
    // Variables de estructura para manejo de registros.      
    Ingreso ingresoWrite;   
    // ID del registro a eliminar.
    unsigned long long codIngresoEliminar = 0; 
    // Variables de control y contadores.
    // estadoGlobal: 1: OK, 0: Error/Cancelacion.
    // c: Control de bucle.
    int c = 0, registrosEliminados = 0, encontrado = 0, estadoGlobal = 1, confirmaciones = 0, idSeleccionadoEsValido = 0;
    
    
	system("cls");
    printf("------------------------------------------\nEliminar Registro De Ingreso\n------------------------------------------\n\n");
    
    // --- 1. LISTAR TODOS LOS INGRESOS ---
    
    // Intenta abrir el archivo de ingresos para lectura
    if ((fing = fopen("ingresos.dat", "rb")) == NULL) {
        printf("Error: No Se Pudo Abrir El Archivo De Ingresos ('ingresos.dat').\n");
        system("PAUSE");
        estadoGlobal = 0;
    }
    
    if (estadoGlobal) {
        // Cabecera de la lista
        printf("Id Ingreso | Monto Total | Concepto | Persona | Fecha\n");
        printf("--------------------------------------------------------------------------------\n");

        fread(&ingreso, sizeof(Ingreso), 1, fing); 
        // Recorre el archivo para listar
        while (!feof(fing)) {
            printf("%-10llu | $%-11.2lf | %-20s | %-10s | %d/%d/%d\n",
                   ingreso.codIngreso, ingreso.monto, ingreso.concepto, ingreso.persona.nombre,
                   ingreso.fecha.dia, ingreso.fecha.mes, ingreso.fecha.anio);
            encontrado++; 
            fread(&ingreso, sizeof(Ingreso), 1, fing); 
        }
        
        if (fing != NULL) { fclose(fing); fing = NULL; }
        
        printf("--------------------------------------------------------------------------------\n");

        if (encontrado == 0) {
            printf("No Se Encontraron Registros De Ingresos Para Eliminar.\n\n");
            system("PAUSE");
            estadoGlobal = 0; 
        }
    }
    
    // --- 2. PEDIR ID Y VALIDAR EXISTENCIA ---
    if (estadoGlobal) {
        
        c = 1; // Inicia el bucle de validacion de ID
        while(c){
            printf("\nTotal De Registros Listados: %d\n", encontrado);
            printf("Ingrese El Id Del Ingreso Que Desea Eliminar: ");
            fflush(stdin);
            gets(Cad4); 
        
            codIngresoEliminar = atoll(Cad4);
            idSeleccionadoEsValido = 0; 
            
            // Validacion de formato y existencia del ID
            if (codIngresoEliminar == 0 || digitosC(Cad4) == 0) {
                // Manejo de error abajo.
            }
            else if ((fing = fopen("ingresos.dat", "rb")) != NULL) {
                
                fread(&ingreso, sizeof(Ingreso), 1, fing);
                // Busca el ID
                while (!feof(fing) && !idSeleccionadoEsValido) { 
                     if (ingreso.codIngreso == codIngresoEliminar) {
                         idSeleccionadoEsValido = 1; 
                     }
                     fread(&ingreso, sizeof(Ingreso), 1, fing);
                }
                if (fing != NULL) { fclose(fing); fing = NULL; }
            } else {
                printf("\nError Critico Al Reabrir El Archivo De Ingresos Para Validacion.\n");
                estadoGlobal = 0; 
            }

            // Manejo de errores de ID (Vuelve a listar)
            if (!idSeleccionadoEsValido && estadoGlobal) {
                system("cls");
                printf("\nError: El Id Ingresado Es Invalido O No Existe En Los Registros De Ingreso.\n\n");
                system("PAUSE");
                
                // Regenera la lista despues del error
                printf("------------------------------------------\nEliminar Registro De Ingreso\n------------------------------------------\n\n");
                
                if ((fing = fopen("ingresos.dat", "rb")) != NULL) {
                    printf("Id Ingreso | Monto Total | Concepto | Persona | Fecha\n");
                    printf("--------------------------------------------------------------------------------\n");
                    
                    fread(&ingreso, sizeof(Ingreso), 1, fing);
                    while (!feof(fing)) {
                          printf("%-10llu | $%-11.2lf | %-20s | %-10s | %d/%d/%d\n",
                                 ingreso.codIngreso, ingreso.monto, ingreso.concepto, ingreso.persona.nombre,
                                 ingreso.fecha.dia, ingreso.fecha.mes, ingreso.fecha.anio);
                          fread(&ingreso, sizeof(Ingreso), 1, fing);
                    }

                    if (fing != NULL) { fclose(fing); fing = NULL; }
                    printf("--------------------------------------------------------------------------------\n");
                }
            }
            else if (idSeleccionadoEsValido && estadoGlobal) {
                c=0; // ID valido, sale del bucle
            }
        }
        
        if (estadoGlobal) {
            printf("\nHa Seleccionado El Ingreso Con Id: %llu\n", codIngresoEliminar);
        }
    }
    
    // --- 3. TRIPLE CONFIRMACION --- 
    if (estadoGlobal) {
        
        confirmaciones = 0;
        printf("\n\n=== Eliminacion De Ingreso ===\n");
        
        // Primera advertencia
        printf("\n=== Advertencia 1/3 ===\n");
        printf("Se Procedera A Eliminar Permanentemente El Ingreso Id %llu.\n", codIngresoEliminar);
        printf("\nEsta Seguro Que Desea Continuar Con La Eliminacion (si/no)? ");
        scanf("%s", confirmacion);
        
        if (strcmp(confirmacion, "si") == 0 || strcmp(confirmacion, "SI") == 0) {
            confirmaciones++;

            // Segunda advertencia
            printf("\n=== Advertencia 2/3 ===\n");
            printf("Recuerde: Esta Accion No Se Puede Deshacer. Confirma (si/no)? ");
            scanf("%s", confirmacion);
            
            if (strcmp(confirmacion, "si") == 0 || strcmp(confirmacion, "SI") == 0) {
                confirmaciones++;

                // Tercera advertencia
                printf("\n=== Advertencia 3/3 ===\n");
                printf("Confirmacion Final. Eliminar Definitivamente El Ingreso Id %llu (si/no)? ", codIngresoEliminar);
                scanf("%s", confirmacion);
                
                if (strcmp(confirmacion, "si") == 0 || strcmp(confirmacion, "SI") == 0) {
                    confirmaciones++;
                }
            }
        }
    
        
        // --- 4. EJECUTAR ELIMINACION ---
        
        if (confirmaciones == 3) { 
            
            registrosEliminados = 0; 
            
            if ((fing = fopen("ingresos.dat", "rb")) != NULL) {
                if ((ftemp = fopen("ingresos_temp.dat", "wb")) != NULL) {
                    
                    // Copia registros al archivo temporal, omitiendo el ID a eliminar
                    fread(&ingresoWrite, sizeof(Ingreso), 1, fing);
                    while (!feof(fing)) {
                        if (ingresoWrite.codIngreso != codIngresoEliminar) {
                            fwrite(&ingresoWrite, sizeof(Ingreso), 1, ftemp);
                        } else {
                            registrosEliminados++; 
                        }
                        fread(&ingresoWrite, sizeof(Ingreso), 1, fing);
                    }
                    
                    // Cierra archivos y renombra para reemplazar el original
                    if (ftemp != NULL) { fclose(ftemp); ftemp = NULL; } 
                    if (fing != NULL) { fclose(fing); fing = NULL; } 
                    
                    remove("ingresos.dat");
                    rename("ingresos_temp.dat", "ingresos.dat");
                } else {
                    printf("\nError Al Crear Archivo Temporal Para Ingresos. Eliminacion Fallida.\n");
                }
            } else {
                printf("\nError Al Abrir 'ingresos.dat' Para Reescritura. Eliminacion Fallida.\n");
            }
            
            
            printf("\n=== Eliminacion Completada ===\n");
            printf("El Ingreso Id: %llu Ha Sido Eliminado.\n", codIngresoEliminar);
            printf("Total De Registros Eliminados: %d\n", registrosEliminados);
            
        } else { // Fallo en la triple confirmacion
            printf("\nOperacion De Eliminacion Cancelada Por El Usuario.\n");
            printf("Fallo En La Triple Confirmacion (Solo %d De 3). Operacion Cancelada.\n", confirmaciones);
        }
    }
    
    system("PAUSE");
}

///////////////////////////////////////// eliminarpago ///////////////////////////////////////////////////////////////////////////////////////

void eliminarPago(){
	FILE *fpagos = NULL, *fhistorial = NULL, *fgastos = NULL;
	
    Pago pago_a_borrar; 
    Gasto gasto_a_actualizar;
    
    
    unsigned long long codGasto_a_buscar = 0;
    long pos_gasto = -1;
    int pago_a_borrar_encontrado = 0,gasto_encontrado = 0,pagos_existentes = 0,index_pago_seleccionado = 0,opc_elim = 0,running_op = 1,step = 1,s = 1,read_success = 0,current_index = 0; 
   
   
    double deuda_anterior = 0.0,valorCuotaBase = 0.0,montoPagado = 0.0;
    int ejecutar_borrado = 0,resultado_borrado = 0,gasto_actualizado = 0,continuar_confirmacion = 0,confirmaciones = 0,cuotasCompletamentePagadas = 0;
    
   
    char input_str[20],confirm_str[10],medio[20];


  
    while (running_op) {
        
        if (step == 1) {
            s = 1;
            pagos_existentes = 0;
            current_index = 0;

            while(s) {
                system("cls");
                printf("\n----------------------\n6. MENU DE ELIMINACION\n----------------------");
                printf("\n\t> ANULAR REGISTRO DE PAGO (Seleccione el Pago)\n");
                
                printf("\nPAGOS REGISTRADOS EN EL SISTEMA\n");
                printf("=============================================================================\n");
                printf(" | # | ID Gasto | Fecha      | Importe Pagado | Medio de Pago |\n");
                printf(" |---|----------|------------|----------------|---------------|\n");
                
                if ((fpagos = fopen("pagos.dat", "rb")) != NULL) {
                    
                    read_success = (fread(&pago, sizeof(Pago), 1, fpagos) == 1);
                    while (read_success) {
                        pagos_existentes++;
                        
                        // Uso de 'medio' declarado arriba
                        if (pago.medioPago == 1) strcpy(medio, "Efectivo");
                        else if (pago.medioPago == 2) strcpy(medio, "Billetera");
                        else if (pago.medioPago == 3) strcpy(medio, "Tarjeta");
                        else if (pago.medioPago == 4) strcpy(medio, "Debito");
                        else strcpy(medio, "Desconocido");
                        
                        printf(" | %-1d | %-8llu | %02d/%02d/%4d | $%-12.3lf | %-13s |\n",pagos_existentes, pago.codGasto, pago.fechaPago.dia, pago.fechaPago.mes, pago.fechaPago.anio, pago.importe,medio);
                        read_success = (fread(&pago, sizeof(Pago), 1, fpagos) == 1);
                    }
                    
                    fclose(fpagos);
                    fpagos = NULL;
                } else {
                    system("cls");
                    printf("\nError CRITICO: No se pudo abrir 'pagos.dat'.\n");
                    system("PAUSE");
                    running_op = 0; 
                    s = 0;
                }
                
                printf("=============================================================================\n");

                if (running_op) {
                    if (pagos_existentes == 0) {
                        system("cls");
                        printf("\nNo se encontraron pagos registrados en el sistema.\n");
                        system("PAUSE");
                        running_op = 0;
                        s = 0;
                    } else {
                        printf("\nSeleccione el numero (#) de Pago a eliminar (1-%d, 0 para cancelar): ", pagos_existentes);
                        fflush(stdin);
                        gets(input_str);
                        
                        index_pago_seleccionado = atoi(input_str);
                        
                        if (index_pago_seleccionado == 0) {
                            system("cls");
                            printf("\n----------------------\n6. MENU DE ELIMINACION\n----------------------");
                            printf("\n\tOPERACION CANCELADA\n\n");
                            system("PAUSE");
                            running_op = 0;
                            s = 0;
                        } else if (index_pago_seleccionado >= 1 && index_pago_seleccionado <= pagos_existentes) {
                            s = 0; 
                            step = 2;
                        } else {
                            system("cls");
                            printf("\nNumero de Pago no valido. Por favor, ingrese un numero entre 1 y %d.\n", pagos_existentes);
                            system("PAUSE");
                        }
                    }
                }
            }
        }

   
        if (step == 2) {
            
            pago_a_borrar_encontrado = 0;
            gasto_encontrado = 0;
            current_index = 0;
            
            if ((fpagos = fopen("pagos.dat", "rb")) != NULL) {
                
                read_success = (fread(&pago, sizeof(Pago), 1, fpagos) == 1);
                while (read_success) {
                    current_index++;
                    if (current_index == index_pago_seleccionado) {
                        pago_a_borrar = pago; 
                        codGasto_a_buscar = pago.codGasto; 
                        pago_a_borrar_encontrado = 1;
                    }
                    read_success = (fread(&pago, sizeof(Pago), 1, fpagos) == 1);
                }
                fclose(fpagos);
                fpagos = NULL;
            } 

            if (pago_a_borrar_encontrado) {
                if ((fgastos = fopen("gastos.dat", "r+b")) != NULL) {
                    
                    read_success = (fread(&gasto_a_actualizar, sizeof(Gasto), 1, fgastos) == 1);
                    while (read_success) {
                        if (gasto_a_actualizar.codGasto == codGasto_a_buscar) {
                            pos_gasto = ftell(fgastos) - sizeof(Gasto);
                            gasto_encontrado = 1;
                        }
                        read_success = (fread(&gasto_a_actualizar, sizeof(Gasto), 1, fgastos) == 1);
                    }
                    fclose(fgastos);
                    fgastos = NULL;
                }

                if (gasto_encontrado) {
                    step = 3; 
                } else {
                    system("cls");
                    printf("\nError CRITICO: Pago encontrado, pero Gasto %llu asociado no existe. Operacion cancelada.\n", codGasto_a_buscar);
                    system("PAUSE");
                    running_op = 0;
                }
            } else {
                system("cls");
                printf("\nError interno: No se pudo re-encontrar el pago seleccionado. Operacion cancelada.\n");
                system("PAUSE");
                running_op = 0;
            }
        }
        
 
        if (step == 3) {
            s = 1;
            opc_elim = 0;
            
            while(s) {
                system("cls");
                printf("\n----------------------\n6. MENU DE ELIMINACION\n----------------------");
                printf("\n\t> ELIMINAR REGISTRO DE PAGO: Pago #%d (ID Gasto: %llu, Importe: $%.3lf)\n", index_pago_seleccionado, codGasto_a_buscar, pago_a_borrar.importe);
                printf("\nSeleccione el tipo de eliminacion:\n\n");
                printf("1. Eliminacion COMPLETA (Anula el pago en el Gasto y borra el registro de Pago)\n");
                printf("2. Eliminar solo REGISTRO DE PAGO (Borra solo el historial de Pago)\n");
                printf("3. Cancelar operacion\n\n");
                printf("Elija una Opcion: ");
                
                fflush(stdin);
                gets(input_str);
                opc_elim = atoi(input_str);
                
                if (opc_elim >= 1 && opc_elim <= 3) {
                    s = 0; 
                    if (opc_elim == 3) {
                        system("cls");
                        printf("\n----------------------\n6. MENU DE ELIMINACION\n----------------------");
                        printf("\n\tOPERACION CANCELADA\n\n");
                        system("PAUSE");
                        running_op = 0;
                    } else {
                        step = 4; 
                    }
                } else {
                    system("cls");
                    printf("\nOpcion no valida. Por favor, ingrese 1, 2 o 3.\n");
                    system("PAUSE");
                }
            }
        }

       
        if (step == 4) {
            
   
            if (opc_elim == 1) {
                
                continuar_confirmacion = 1;
                confirmaciones = 0;
                ejecutar_borrado = 0;

          
                while(continuar_confirmacion && (confirmaciones < 3)) {
                    system("cls");
                    printf("\n----------------------\n6. MENU DE ELIMINACION\n----------------------");
                    printf("\n\t> ELIMINACION COMPLETA: Pago #%d (ID Gasto: %llu, Importe: $%.3lf)\n", index_pago_seleccionado, codGasto_a_buscar, pago_a_borrar.importe);
                    printf("\n=== ADVERTENCIA %d/3 ===\n", confirmaciones + 1);
                    printf("Esta accion ELIMINARAÂ el registro de pago Y ANULARAÂ el monto ($%.3lf) de la deuda TOTAL del Gasto.\n", pago_a_borrar.importe);
                    
                    if (confirmaciones == 2) {
                        printf("\nCONFIRMACION FINAL. Escriba 'SI' para proceder: ");
                    } else {
                        printf("\nEsta seguro que desea continuar? (si/no): ");
                    }
                    
                    fflush(stdin);
                    gets(confirm_str);
                    
                    if ((strcmp(confirm_str, "si") == 0) || (strcmp(confirm_str, "SI") == 0)) {
                        confirmaciones++;
                    } else {
                        continuar_confirmacion = 0; 
                    }
                }

                if (confirmaciones == 3) {
                    ejecutar_borrado = 1;
                }

                if (ejecutar_borrado) {
                    
                    // a) ANULACION DEL PAGO EN EL GASTO (gastos.dat)
                    if ((fgastos = fopen("gastos.dat", "r+b")) != NULL) {
                        fseek(fgastos, pos_gasto, SEEK_SET);
                        
                        if (fread(&gasto_a_actualizar, sizeof(Gasto), 1, fgastos) == 1) {
                            
                            deuda_anterior = gasto_a_actualizar.deudaTotal; 
                            
                          
                            if (gasto_a_actualizar.cuotasTotales > 0) {
                                valorCuotaBase = gasto_a_actualizar.monto / gasto_a_actualizar.cuotasTotales;
                            } else {
                                valorCuotaBase = gasto_a_actualizar.monto; 
                            }
                            
                        
                            gasto_a_actualizar.deudaTotal += pago_a_borrar.importe;
                            
                            montoPagado = gasto_a_actualizar.monto - gasto_a_actualizar.deudaTotal; 
                            
                          
                            if (fabs(gasto_a_actualizar.deudaTotal) < EPSILON) {
                                
                                gasto_a_actualizar.estadoCuota = 3; // Pagado
                                gasto_a_actualizar.restanteCuota = 0.0;
                                gasto_a_actualizar.cuotaActual = gasto_a_actualizar.cuotasTotales;
                            } else if (gasto_a_actualizar.deudaTotal > gasto_a_actualizar.monto - EPSILON) {
                                // Caso 2: Deuda total (o casi total). Vuelve a No Pagado.
                                gasto_a_actualizar.estadoCuota = 1; // No Pagado
                                gasto_a_actualizar.restanteCuota = valorCuotaBase; 
                                gasto_a_actualizar.cuotaActual = 1; // Vuelve a la primera cuota
                            } else {
                                // Caso 3: Deuda Parcial.
                                gasto_a_actualizar.estadoCuota = 2; // Parcialmente Pagado
                                
                                if (valorCuotaBase > EPSILON && gasto_a_actualizar.cuotasTotales > 0) {
                                    cuotasCompletamentePagadas = (int)floor(montoPagado / valorCuotaBase);
                                    
                                    gasto_a_actualizar.cuotaActual = cuotasCompletamentePagadas + 1;
                                    
                                    if (gasto_a_actualizar.cuotaActual > gasto_a_actualizar.cuotasTotales) {
                                        gasto_a_actualizar.cuotaActual = gasto_a_actualizar.cuotasTotales;
                                    }
                                    
                                    double montoPagadoCuotaActual = montoPagado - (cuotasCompletamentePagadas * valorCuotaBase);
                                    
                                    gasto_a_actualizar.restanteCuota = valorCuotaBase - montoPagadoCuotaActual;
                                    
                                    if (gasto_a_actualizar.restanteCuota < EPSILON && gasto_a_actualizar.cuotaActual < gasto_a_actualizar.cuotasTotales) {
                                        // Si la cuota actual se paga justo, la restanteCuota es la siguiente cuota completa
                                        gasto_a_actualizar.restanteCuota = valorCuotaBase; 
                                        gasto_a_actualizar.cuotaActual++;
                                    } else if (gasto_a_actualizar.cuotaActual == gasto_a_actualizar.cuotasTotales && gasto_a_actualizar.restanteCuota < EPSILON) {
                                        gasto_a_actualizar.restanteCuota = 0.0; // ultima cuota completa
                                    }
                                } else {
                                    // Pago unico o cuota 0
                                    gasto_a_actualizar.cuotaActual = 1;
                                    gasto_a_actualizar.restanteCuota = gasto_a_actualizar.deudaTotal;
                                }
                                
                                // Asegurar limites
                                if (gasto_a_actualizar.cuotaActual < 1) gasto_a_actualizar.cuotaActual = 1;
                            }

                            fseek(fgastos, pos_gasto, SEEK_SET);
                            if (fwrite(&gasto_a_actualizar, sizeof(Gasto), 1, fgastos) == 1) {
                                gasto_actualizado = 1;
                            }
                        }
                        fclose(fgastos);
                        fgastos = NULL;
                    }
                    
           
                    if (gasto_actualizado) {
                        
                        if ((fpagos = fopen("pagos.dat", "rb")) != NULL) {
                            if ((fhistorial = fopen("pagos_temp.dat", "wb")) != NULL) {
                                
                                current_index = 0;
                                read_success = (fread(&pago, sizeof(Pago), 1, fpagos) == 1);
                                
                                while(read_success) {
                                    current_index++;
                                    
                                    if (current_index != index_pago_seleccionado) {
                                        fwrite(&pago, sizeof(Pago), 1, fhistorial);
                                    }
                                    
                                    read_success = (fread(&pago, sizeof(Pago), 1, fpagos) == 1);
                                }

                                fclose(fhistorial);
                                fhistorial = NULL;
                                fclose(fpagos);
                                fpagos = NULL;
                                
                                remove("pagos.dat");
                                if (rename("pagos_temp.dat", "pagos.dat") == 0) {
                                    resultado_borrado = 1;
                                }

                            }
                        } 
                    }
                    
                    system("cls");
                    printf("\n----------------------\n6. MENU DE ELIMINACION\n----------------------");
                    if (resultado_borrado && gasto_actualizado) {
                        // MOSTRAR SOLO EL RESUMEN DEL GASTO AFECTADO
                        printf("\n\n\ANULACION Y BORRADO DE PAGO EXITOSO...\n\n");
                        printf("=== Gasto Afectado y Actualizado ===\n");
                        printf("Gasto ID: %llu\n", codGasto_a_buscar);
                        printf("Importe del Pago Anulado: $%.3lf\n", pago_a_borrar.importe);
                        printf("---------------------------------------\n");
                        printf("Deuda Anterior del Gasto: $%.3lf\n", deuda_anterior);
                        printf("Deuda Actualizada del Gasto: $%.3lf\n", gasto_a_actualizar.deudaTotal);
                        printf("Cuotas Totales: %d\n", gasto_a_actualizar.cuotasTotales);
                        printf("Cuota Actual (cuotaActual): %d\n", gasto_a_actualizar.cuotaActual);
                        printf("Nuevo Estado (1=No Pagado, 2=Parcial, 3=Pagado): %d\n", gasto_a_actualizar.estadoCuota);
                        printf("Nueva Cuota Restante (restanteCuota): $%.3lf\n", gasto_a_actualizar.restanteCuota);
                        printf("======================================\n");
                        
                    } else {
                        printf("\n\n\tERROR: El registro no pudo ser borrado y/o anulado.\n\n");
                    }
                    system("PAUSE");
                    running_op = 0;
                } else {
                    system("cls");
                    printf("\n----------------------\n6. MENU DE ELIMINACION\n----------------------\n");
                    printf("\n\tOPERACION CANCELADA por fallo en la triple confirmacion.\n\n");
                    system("PAUSE");
                    running_op = 0;
                }

            }
            
          
            else if (opc_elim == 2) {
                
                resultado_borrado = 0;
          
                if ((fpagos = fopen("pagos.dat", "rb")) != NULL) {
                    if ((fhistorial = fopen("pagos_temp.dat", "wb")) != NULL) {
                        
                        current_index = 0;
                        read_success = (fread(&pago, sizeof(Pago), 1, fpagos) == 1);

                        while(read_success) {
                            current_index++;
                            
                            if (current_index != index_pago_seleccionado) {
                                fwrite(&pago, sizeof(Pago), 1, fhistorial);
                            }
                            
                            read_success = (fread(&pago, sizeof(Pago), 1, fpagos) == 1);
                        }

                        fclose(fhistorial);
                        fhistorial = NULL;
                        fclose(fpagos);
                        fpagos = NULL;
                        
                        remove("pagos.dat");
                        if (rename("pagos_temp.dat", "pagos.dat") == 0) {
                            resultado_borrado = 1;
                        }

                    }
                } 
                
                system("cls");
                printf("\n----------------------\n6. MENU DE ELIMINACION\n----------------------");
                if (resultado_borrado) {
                    printf("\n\n\tELIMINACION DE REGISTRO DE PAGO (Historial) EXITOSA...\n");
                    printf("El Gasto %llu no fue modificado.\n\n", codGasto_a_buscar);
                } else {
                    printf("\n\n\tERROR El registro de Pago no pudo ser borrado del historial.\n\n");
                }
                system("PAUSE");
                running_op = 0; 
            }
        }
    }
}

///////////////////////////////////////// eliminarcategoria ///////////////////////////////////////////////////////////////////////////////////////

void eliminarCategoria(){
	
	FILE *fcat = NULL, *fgas = NULL, *fpag = NULL, *ftemp = NULL;
    unsigned long long idCategoriaEliminar = 0;
    

    Categoria categorias[100];
    
    
    char confirmacion[10] = "", opcionEliminacion[10] = "", nombreCategoria[50] = "";
    
   
    int running_op = 1, step = 1, s = 1, execution_ok = 1, confirmaciones = 0, tipoEliminacion = 0, categoriaExiste = 0, numCategorias = 0, i = 0, gastosEncontrados = 0, totalCategorias = 0, totalGastos = 0, totalPagos = 0, registrosEliminados = 0, gastosEliminados = 0;

    
    while (running_op) {
        
    
        if (step == 1) {
            system("cls");
            printf("--------------------\nELIMINAR CATEGORIAS\n--------------------\n");
            
            
            if ((fcat = fopen("categorias.dat", "rb")) == NULL) {
                printf("\nNo existen categorias registradas en el sistema (Error de apertura).\n");
                execution_ok = 0;
            } 
            
          
            if (execution_ok) {
                fseek(fcat, 0, SEEK_END);
                if (ftell(fcat) == 0) {
                    printf("\nNo existen categorias registradas en el sistema.\n");
                    execution_ok = 0;
                }
                rewind(fcat);
            }

            if (!execution_ok) {
                if (fcat != NULL) {
                    fclose(fcat);
                    fcat = NULL;
                }
                step = 6; // Ir al final
            } else {
                step = 2;
            }
        }

        
        if (step == 2) {
            printf("\n=== TIPO DE ELIMINACION ===\n");
            printf("Que desea eliminar?\n");
            printf("1. Eliminar UNA categoria especifica\n");
            printf("2. Eliminar TODAS las categorias\n");
            printf("3. Cancelar operacion\n");
            printf("\nElija una opcion (1-3): ");
            scanf("%s", opcionEliminacion);
            
            if (strcmp(opcionEliminacion, "3") == 0) {
                printf("\nOperacion cancelada por el usuario.\n");
                step = 6; // Ir al final
            } else if (strcmp(opcionEliminacion, "1") == 0) {
                tipoEliminacion = 1; 
                step = 3;
            } else if (strcmp(opcionEliminacion, "2") == 0) {
                tipoEliminacion = 2; 
                step = 4;
            } else {
                printf("\nOpcion no valida. Operacion cancelada.\n");
                step = 6; // Ir al final
            }

            if (step == 6 && fcat != NULL) {
                fclose(fcat);
                fcat = NULL;
            }
        }


        if (step == 3) {
            s = 1; 

         
            numCategorias = 0;
            while (fread(&categoria, sizeof(Categoria), 1, fcat) && numCategorias < 100) {
                categorias[numCategorias] = categoria;
                numCategorias++;
            }
            if (fcat != NULL) {
                fclose(fcat); 
                fcat = NULL;
            }
            
            printf("\n=== CATEGORIAS REGISTRADAS ===\n");
            for (i = 0; i < numCategorias; i++) {
                printf("ID: %llu | Nombre: %s\n", categorias[i].codigo, categorias[i].nombre);
            }
            
         
            printf("\nIngrese el ID de la categoria a eliminar: ");
            scanf("%llu", &idCategoriaEliminar);
            
          
            categoriaExiste = 0;
            i = 0;
            while (i < numCategorias) {
                if (categorias[i].codigo == idCategoriaEliminar) {
                    categoriaExiste = 1;
                    strcpy(nombreCategoria, categorias[i].nombre);
                }
                i++;
            }
            
            if (!categoriaExiste) {
                printf("\nNo existe una categoria con el ID: %llu\n", idCategoriaEliminar);
                step = 6; // Ir al final
            }
            
           
            if (categoriaExiste) {
                printf("\n=== GASTOS QUE SERAN ELIMINADOS ===\n");
                gastosEncontrados = 0;
                if ((fgas = fopen("gastos.dat", "rb")) != NULL) {
                    while (fread(&gasto, sizeof(Gasto), 1, fgas)) {
                        if (gasto.categoria.codigo == idCategoriaEliminar) {
                            printf("- Gasto ID: %llu | Desc: %s | Monto: $%.2lf\n", 
                                   gasto.codGasto, gasto.desc, gasto.monto);
                            gastosEncontrados++;
                        }
                    }
                    if (fgas != NULL) {
                        fclose(fgas);
                        fgas = NULL;
                    }
                }
                if (gastosEncontrados == 0) {
                    printf("No hay gastos asociados a esta categoria.\n");
                }
            }


           
            if (categoriaExiste) {
                confirmaciones = 0;
                i = 0;
                s = 1;
                while (s) { 
                    system("cls");
                    printf("\n--------------------\nELIMINAR CATEGORIAS\n--------------------\n");
                    printf("\n\t> Eliminando: %s (ID: %llu)\n", nombreCategoria, idCategoriaEliminar);
                    printf("\n=== ADVERTENCIA %d/3 ===\n", i + 1);

                    if (i == 0) {
                        printf("Esta accion eliminara la categoria: %s (ID: %llu)\n", nombreCategoria, idCategoriaEliminar);
                        printf("Se eliminaran %d gastos asociados y sus pagos.\n", gastosEncontrados);
                        printf("Esta accion NO se puede deshacer.\n");
                        printf("\nEsta seguro que desea continuar? (si/no): ");
                    } else if (i == 1) {
                        printf("Esta a punto de eliminar permanentemente la categoria y sus gastos.\n");
                        printf("Esta ABSOLUTAMENTE seguro? (si/no): ");
                    } else { // i == 2
                        printf("ULTIMA OPORTUNIDAD para cancelar.\n");
                        printf("CONFIRMA la eliminacion definitiva? (si/no): ");
                    }
                    
                    scanf("%s", confirmacion);
                    
                    if (strcmp(confirmacion, "si") == 0 || strcmp(confirmacion, "SI") == 0) {
                        confirmaciones++;
                        i++;
                    } else {
                        s = 0; // Salir del bucle interno
                    }

                    if (i == 3) {
                        s = 0;
                    }
                } 
            } 
            

            
            if (categoriaExiste && confirmaciones == 3) {
                
                gastosEliminados = 0;
                
                
                if ((fgas = fopen("gastos.dat", "rb")) != NULL) {
                    if ((ftemp = fopen("gastos_temp.dat", "wb")) != NULL) {
                        while (fread(&gasto, sizeof(Gasto), 1, fgas)) {
                            if (gasto.categoria.codigo != idCategoriaEliminar) {
                                fwrite(&gasto, sizeof(Gasto), 1, ftemp);
                            } else {
                                gastosEliminados++;
                            }
                        }
                        if (ftemp != NULL) { fclose(ftemp); ftemp = NULL; }
                        if (fgas != NULL) { fclose(fgas); fgas = NULL; }
                        remove("gastos.dat");
                        rename("gastos_temp.dat", "gastos.dat");
                    }
                }
                
                
                if ((fcat = fopen("categorias.dat", "wb")) != NULL) {
                    i = 0;
                    while (i < numCategorias) {
                        if (categorias[i].codigo != idCategoriaEliminar) {
                            fwrite(&categorias[i], sizeof(Categoria), 1, fcat);
                        }
                        i++;
                    }
                    if (fcat != NULL) { fclose(fcat); fcat = NULL; }
                }
                
                
                printf("\n=== ELIMINACION COMPLETADA ===\n");
                printf("Se eliminaron la categoria '%s' y %d gastos asociados\n", 
                       nombreCategoria, gastosEliminados);
            } else if (categoriaExiste) {
                printf("\nOperacion cancelada por el usuario.\n");
            }
            step = 6; // Ir al final
        }

     
        if (step == 4) {
            
            
            totalCategorias = 0;
            totalGastos = 0;
            totalPagos = 0;
            
            
            if (fcat != NULL) {
                rewind(fcat); 
            }
            
           
            if ((fcat = fopen("categorias.dat", "rb")) != NULL) {
                while (fread(&categoria, sizeof(Categoria), 1, fcat)) {
                    totalCategorias++;
                }
                fclose(fcat);
                fcat = NULL;
            }


            if ((fgas = fopen("gastos.dat", "rb")) != NULL) {
                while (fread(&gasto, sizeof(Gasto), 1, fgas)) {
                    totalGastos++;
                }
                fclose(fgas);
                fgas = NULL;
            }

            if ((fpag = fopen("pagos.dat", "rb")) != NULL) {
                while (fread(&pago, sizeof(Pago), 1, fpag)) {
                    totalPagos++;
                }
                fclose(fpag);
                fpag = NULL;
            }
            
     
            confirmaciones = 0;
            i = 0;
            s = 1;
            while (s) { 
                system("cls");
                printf("\n--------------------\nELIMINAR CATEGORIAS\n--------------------\n");
                printf("\n\t> Eliminacion TOTAL de todos los datos\n");
                printf("\n=== ADVERTENCIA %d/3 ===\n", i + 1);

                if (i == 0) {
                    printf("Esta accion eliminara TODAS las categorias (%d categorias)\n", totalCategorias);
                    printf("Se eliminaran TODOS los gastos (%d gastos) y sus pagos asociados.\n", totalGastos);
                    printf("El sistema quedara completamente vacio de categorias y gastos.\n");
                    printf("Esta accion NO se puede deshacer.\n");
                    printf("\nEsta seguro que desea continuar? (si/no): ");
                } else if (i == 1) {
                    printf("Esta a punto de BORRAR COMPLETAMENTE todas las categorias y gastos.\n");
                    printf("Esta ABSOLUTAMENTE seguro? (si/no): ");
                } else { // i == 2
                    printf("ULTIMA OPORTUNIDAD para cancelar.\n");
                    printf("CONFIRMA la eliminacion TOTAL y DEFINITIVA? (si/no): ");
                }
                
                scanf("%s", confirmacion);
                
                if (strcmp(confirmacion, "si") == 0 || strcmp(confirmacion, "SI") == 0) {
                    confirmaciones++;
                    i++;
                } else {
                    s = 0; // Salir del bucle interno
                }

                if (i == 3) {
                    s = 0;
                }
            } 
            
           
            if (confirmaciones == 3) {
                
                registrosEliminados = 0;
                
                // 4.3.1 Eliminar gastos.dat
                if (remove("gastos.dat") == 0) {
                   
                    fgas = fopen("gastos.dat", "wb");
                    if (fgas != NULL) {
                        fclose(fgas);
                        fgas = NULL;
                    }
                }
                registrosEliminados += totalGastos;


                // 4.3.2 Eliminar pagos.dat
                if (remove("pagos.dat") == 0) {
                    
                }
                registrosEliminados += totalPagos;
                
                // 4.3.3 Eliminar categorias.dat
                remove("categorias.dat");
                registrosEliminados += totalCategorias;
                
                // 4.3.4 Mostrar Resumen
                printf("\n=== ELIMINACION COMPLETA REALIZADA ===\n");
                printf("Se eliminaron %d registros en total:\n", registrosEliminados);
                printf("- %d categorias\n", totalCategorias);
                printf("- %d gastos\n", totalGastos);
                printf("- %d pagos\n", totalPagos);
                printf("\nEl sistema ha sido reiniciado (sin categorias, gastos ni pagos).\n");
            } else {
                printf("\nOperacion cancelada por el usuario.\n");
            }
            step = 6; // Ir al final
        }
        
       
        if (step == 6) {
            system("PAUSE");
            running_op = 0;
        }
    } // Fin del bucle principal
}

///////////////////////////////////////// FUNCIONES AUXILIARES ///////////////////////////////////////////////////////////////////////////////////////

void guardarGasto(Gasto gasto){
	
	FILE *f4 = NULL;
    
   
    int exito_apertura = 0; // 1 si el archivo se abre correctamente

    // Apertura del archivo
	if((f4=fopen("gastos.dat","ab"))!=NULL){
		exito_apertura = 1;
	}
	
    
    if(exito_apertura == 0){
		printf("\nError al abrir el archivo");
		system("PAUSE");
    }
	
    // Escribir y cerrar solo si la apertura fue exitosa
	if(exito_apertura == 1){
		
		fwrite(&gasto,sizeof(Gasto),1,f4);
		fclose(f4);
		
	}
}

///////////////////////////////////////// comprobacion_fecha ///////////////////////////////////////////////////////////////////////////////////////

int comprobacion_fecha(int aux_anio1,int aux_mes1,int aux_dia1){
	
	int verif = 1;
	
    if ((aux_anio1<3000)&&(aux_anio1>1900)){
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

        } 
		else{
			
            verif = 1;
            
        }
        
    } 
	else{
		
        verif = 1;
        
    }
    
	fflush(stdin);
    return verif; /* 0 = valido, 1 = invalido*/
	
}

///////////////////////////////////////// ver_arch_gastos ///////////////////////////////////////////////////////////////////////////////////////

void ver_arch_gastos(){
	

	FILE *f2 = NULL;
	char Charx[15];
	int archivo_abierto = 0; // Control de flujo

	// 1. Intentar abrir el archivo y establecer la variable de estado
	if ((f2 = fopen("gastos.dat", "rb")) != NULL){
		archivo_abierto = 1;
	}


	if (archivo_abierto == 0){
		printf("\nError Al Abrir El Archivo");
	}


	if (archivo_abierto == 1){
		
		printf("\n\nContenido Del Archivo Gastos:\n");
		
		// Lectura secuencial del archivo, el bucle termina por fread
		while (fread(&gasto, sizeof(Gasto), 1, f2)){
			
			printf("\nCodigo: %llu", gasto.codGasto);
			printf("\nTipo: %d", gasto.tipoGasto);
			printf("\nDescripcion: %s", gasto.desc);
			printf("\nEl ID De La Categoria es: %llu", gasto.categoria.codigo);
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
	
	// Pausa al final (se ejecuta siempre)
	system("PAUSE");
	
}

///////////////////////////////////////// buscar_idGasto ///////////////////////////////////////////////////////////////////////////////////////

unsigned long long buscar_idGasto(){
	

	FILE *arch;
	unsigned long long ret=1,max_id=0;
	Gasto gasto_temp; // Estructura temporal para leer cada registro de gasto.
	
	// Intenta abrir el archivo de gastos en modo lectura binaria ("rb")
	if((arch=fopen("gastos.dat","rb"))!=NULL){
		
		//rewind(arch); // Posiciona el puntero del archivo al inicio..
		
		// Buscar el ID maximo en todos los registros
		// Lee registro por registro hasta el final del archivo
		while(fread(&gasto_temp,sizeof(Gasto),1,arch)==1){
			
			// Comprueba si el codigo del gasto actual es mayor al maximo encontrado hasta ahora
			if(gasto_temp.codGasto>max_id){
				
				max_id=gasto_temp.codGasto; 	
			}
		}
		
		fclose(arch); // Cierra el archivo despues de la lectura
		
		
		if(max_id>0){
			
			ret=max_id+1; // Establece el nuevo ID
			
		}
		// Si max_id sigue siendo 0, 'ret' conserva su valor inicial de 1.
	}
	else{
		
		// Bloque de error si el archivo no se pudo abrir
		printf("\n\nError, No Se Pudo Abrir El Archivo\n\n");
		system("PAUSE");
		
	}
	
	
	return ret;
}

///////////////////////////////////////// buscar_idCategoria ///////////////////////////////////////////////////////////////////////////////////////

unsigned long long buscar_idCategoria(){
	
	// Declaracion de variables: arch1 para el archivo, ret1 para el valor de retorno, max_id1 para el ID maximo encontrado.
	FILE *arch1;
	unsigned long long ret1=1,max_id1=0;
	Gasto gasto_temp1; // Estructura temporal para leer cada registro de gasto.
	
	// Intenta abrir el archivo de gastos en modo lectura binaria ("rb")
	if((arch1=fopen("gastos.dat","rb"))!=NULL){
		
		rewind(arch1); // Posiciona el puntero del archivo al inicio.
		
		
		while(fread(&gasto_temp1,sizeof(Gasto),1,arch1)==1){
			
		
			if(gasto_temp1.categoria.codigo>max_id1){
				
				max_id1=gasto_temp1.categoria.codigo; 
				
			}
			
		}
		
		fclose(arch1); // Cierra el archivo despues de la lectura
		
	
		if(max_id1>0){
			
			ret1=max_id1+1; // Establece el nuevo ID de categoria
			
		}
		// Si max_id1 sigue siendo 0 (archivo error de lectura), 'ret1' conserva su valor inicial de 1.
	}
	else{
		
		// Bloque de error si el archivo no se pudo abrir
		printf("\n\nError, No Se Pudo Abrir El Archivo\n\n");
		system("PAUSE");
		
	}
	

	return ret1;
}

///////////////////////////////////////// buscar_idIngreso ///////////////////////////////////////////////////////////////////////////////////////

unsigned long long buscar_idIngreso(){
	
	// Declaracion de variables: f6 para el archivo, ret2 para el valor de retorno, max_id2 para el ID mÃƒÂ¡ximo encontrado.
	FILE *f6;
	unsigned long long ret2=1,max_id2=0;
	Ingreso ingreso_temp2; // Estructura temporal para leer cada registro de ingreso.
	
	// Intenta abrir el archivo de ingresos en modo lectura binaria ("rb")
	if((f6=fopen("ingresos.dat","rb"))!=NULL){
		
		rewind(f6); // Posiciona el puntero del archivo al inicio.
		
	
		while(fread(&ingreso_temp2,sizeof(Ingreso),1,f6)==1){
			
			
			if(ingreso_temp2.codIngreso>max_id2){
				
				max_id2=ingreso_temp2.codIngreso; 
				
			}
			
		}
		
		fclose(f6); 
		

		if(max_id2>0){
			
			ret2=max_id2+1; // Establece el nuevo ID de ingreso
			
		}
		// Si max_id2 sigue siendo 0 (archivo vacÃƒÂ­o o error de lectura), 'ret2' conserva su valor inicial de 1.
	}
	else{
		
		// Bloque de error si el archivo no se pudo abrir
		printf("\n\nError, No Se Pudo Abrir El Archivo\n\n");
		system("PAUSE");
		
	}
	

	return ret2;
}

///////////////////////////////////////// guardarIngreso ///////////////////////////////////////////////////////////////////////////////////////

void guardarIngreso(Ingreso ingreso){
	

	FILE *f5;
	
	// Intenta abrir el archivo en modo append binario ("ab")
	if((f5 = fopen("ingresos.dat", "ab")) == NULL){
		
		// Bloque de error: El archivo no pudo abrirse.
		printf("\nError al abrir el archivo");
		system("PAUSE");
		
	}
	else{
		
	
		
		// Escribe la estructura 'ingreso' en el archivo
		fwrite(&ingreso, sizeof(ingreso), 1, f5);
		
		// Cierra el archivo
		fclose(f5);
		
	}
	
}

///////////////////////////////////////// guardarPago ///////////////////////////////////////////////////////////////////////////////////////

void guardarPago(Pago pago){
	
	
	FILE *fpp = NULL;
	int exito_apertura = 0; 

	// 1. Intenta abrir el archivo en modo append binario ("ab")
	if((fpp = fopen("pagos.dat", "ab")) != NULL){
		exito_apertura = 1;
	}

	
	if(exito_apertura == 0){
		
		printf("\nError al abrir el archivo");
		system("PAUSE");
		
	}

	
	if(exito_apertura == 1){
		
		// Escribe la estructura 'pago' en el archivo
		fwrite(&pago, sizeof(Pago), 1, fpp); 
		
		// Cierra el archivo
		fclose(fpp);
		
	}
	
}

///////////////////////////////////////// ver_arch_ingresos ///////////////////////////////////////////////////////////////////////////////////////

void ver_arch_ingresos(){
	

	FILE *f1=NULL;
	int archivo_abierto=0; 

	// 1. Intenta abrir el archivo y establece la variable de estado
	if((f1=fopen("ingresos.dat","rb"))!=NULL){
		archivo_abierto=1;
	}


	if(archivo_abierto==0){
		
		printf("\nError Al Abrir El Archivo");
		
	}

	
	if(archivo_abierto==1){
		
		printf("\n\nContenido Del Archivo Ingresos:\n");
		
		// Lectura secuencial del archivo, el bucle termina por fread
		while(fread(&ingreso,sizeof(Ingreso),1,f1)){
			
			printf("\nCodigo: %llu",ingreso.codIngreso);
			printf("\nConcepto: %s",ingreso.concepto);
			printf("\nMonto: %.3lf",ingreso.monto);
			printf("\nFecha: %d/%d/%d",ingreso.fecha.dia,ingreso.fecha.mes,ingreso.fecha.anio);
			printf("\nPersona: %s (DNI: %lld)\n",ingreso.persona.nombre,ingreso.persona.dni);
			printf("------------------------\n");
			
		}
		
		fclose(f1); 
	}
	

	system("PAUSE");
}

///////////////////////////////////////// ver_arch_pagos ///////////////////////////////////////////////////////////////////////////////////////

void ver_arch_pagos(){
	

	FILE *f3;
	char Cadx[30];


	if((f3=fopen("pagos.dat","rb"))==NULL){
		
		
		printf("\nError Al Abrir El Archivo");
		
	}
	else{
		
		printf("\n\nContenido Del Archivo Pagos:\n");
		
	
		while(fread(&pago,sizeof(Pago),1,f3)){
		
			if(pago.medioPago==1){
				
				strcpy(Cadx,"Efectivo");
				
			}
			else{
				
				if(pago.medioPago==2){
					
					strcpy(Cadx,"Billetera Electronida");
					
				}
				else{
					
					if(pago.medioPago==3){
						
						strcpy(Cadx,"Tarjeta");
						
					}
					else{
						
						strcpy(Cadx,"Debito");
						
					}
					
				}
			}
			
				printf("\nCodigo Gasto: %llu",pago.codGasto);
				printf("\nMedio Pago: %s",Cadx);
				printf("\nImporte: %.2lf",pago.importe);
				
				printf("\nFecha: %d/%d/%d\n",pago.fechaPago.dia,pago.fechaPago.mes,pago.fechaPago.anio);
				printf("------------------------\n");
				
		}
			
		fclose(f3);
	}
	

	system("PAUSE");
}

///////////////////////////////////////// digitos ///////////////////////////////////////////////////////////////////////////////////////

double digitos(char *r){
	
	
	double ret1=0;
	int i,ccc=0,punto_encontrado=0;
	
	
	for(i=0;r[i]!='\0';i++){
		
		
		if(r[i]=='.'){
			
			ccc++; // Incrementa el contador de puntos
			punto_encontrado=i; 
			
		}
		
		else if(r[i]<'0'||r[i]>'9'){
			
			
			ccc=2;
			
		}
	}
	

	if(ccc<=1){
		
		
		if(punto_encontrado>0){
			
			
			int decimales=0;
			for(i=punto_encontrado+1;r[i]!='\0';i++){
				
				decimales++;
				
			}
			
			// Si la cantidad de decimales es <= 3, convierte la cadena a double
			if(decimales<=3){
				
				ret1=atof(r);
				
			}
		}
	
		else{
			
			// Convierte la cadena a double (es un entero)
			ret1=atof(r);
		}
	}

	
	
	return ret1;
}

///////////////////////////////////////// digitosDNI ///////////////////////////////////////////////////////////////////////////////////////

long long digitosDNI(char*j){
	

	int k,ret3=0,con=0;
	
	
	for(k=0;j[k]!='\0';k++){
		
		
		if(j[k]<'0'||j[k]>'9'){
			con++; 
		}
	}
	

	if(con==0){
		ret3=atoll(j); // Convierte la cadena 'j' a un valor long long
	}
	
	
	fflush(stdin);
	
	
	return ret3;
}

///////////////////////////////////////// listarIngresos ///////////////////////////////////////////////////////////////////////////////////////

void listarIngresos(){
	

	FILE *fing=NULL;
	
	
	
	if((fing=fopen("ingresos.dat","rb"))!=NULL){
		
		printf("\n////////////////LISTADO DE INGRESOS////////////////////\n");
		

		fread(&ingreso,sizeof(Ingreso),1,fing);
		
		
		while(!feof(fing)){
			
			printf("\nCodigo: %llu\n",ingreso.codIngreso);
			printf("Concepto: %s\n",ingreso.concepto);
			printf("Monto: %.2lf\n",ingreso.monto);
			printf("Fecha: %d/%d/%d\n",ingreso.fecha.dia,ingreso.fecha.mes,ingreso.fecha.anio);
			printf("Persona que percibio: %s",ingreso.persona.nombre);
			printf("\n");
			
	
			fread(&ingreso,sizeof(Ingreso),1,fing);
		}
		
		fclose(fing); 
	}
	else{
		
		
		system("cls");
		printf("\nNo se ha registrado ningun ingreso hasta el momento.\n");
		system("pause"); 
	}
	

	system("pause");

}

///////////////////////////////////////// listarGastos ///////////////////////////////////////////////////////////////////////////////////////

void listarGastos(){
	char Cad16[50000];
	int opc, s = 1, seguir=1;
    
    while (s) {
    	system("cls");
        printf("\nEscoja el criterio por el cual filtrar:\n\n1. Filtrar Por Categoria\n2. Filtrar Por Tipo\n3. Filtrar Por Mes\n4. Volver\n\nElija una opcion: ");
        fflush(stdin);
        gets(Cad16);
        opc=digitosC(Cad16);
        switch (opc) {
            case 1:
                filtrarPorCategoria();
                break;
            case 2:
                filtrarPorTipo();
                break;
            case 3:
                filtrarPorMes();
                break;
            case 4:	
                system("cls");
                printf("\nVOLVIENDO .....\n\n");
                s = 0;
                system("pause");
                break;	
            default:
            	system("cls");
                printf("\nIngrese un numero valido del 1-4 de tipo entero\n\n");
				system("pause");
        }
        
        if (s) {
        	seguir=1;
        	while(seguir){
	        	
                system("cls");
                printf("\nDesea realizar otro listado de gastos?\n\n2. Si\n1. No, finalizar : \t ");
                fflush(stdin);
                gets(Cad16);
        		opc=digitosC(Cad16);
	            
	            if((opc==0)||(opc<0)||(opc>2)){
	                system("cls");
		            printf("\nIngresar Correctamente La Opcion (2 si, 1 no)\n\n");
		        	
		        	system("PAUSE");
		        	system("cls");
				}
				if(opc==2){
					opc=1;
					seguir=0;
				}
	            if (opc) {
					s = 0;
					seguir=0;
	            }	
			
            
            }
        }
    }

}

///////////////////////////////////////// filtrarPorTipo ///////////////////////////////////////////////////////////////////////////////////////

void filtrarPorTipo() {
	char Cad18[50000];
    FILE *fgas;
	int continuar = 1, opc, existe = 0,yy1=1;
	char tipo[10], tipoMayus[10], estado[15];
	
	if((fgas = fopen("gastos.dat","rb"))!=NULL){
		
		while(continuar){
			system("cls");
			printf("\nIngrese El Tipo De Gasto a Filtrar\n\n1. Gastos Fijos\n2. Gastos Ocasionales\n3. Gastos Temporales\n4. Gastos Anuales\n5. Volver\n\nElija Una Opcion: ");
			gets(Cad18);
       		opc=digitosC(Cad18);
			switch(opc){
				case 1:
					strcpy(tipo,"Fijo");
					break;
				case 2:
					strcpy(tipo,"Ocasional");
					break;
				case 3:
					strcpy(tipo,"Temporal");
					break;
				case 4:
					strcpy(tipo,"Anual");
					break;
				case 5:
					continuar = 0;
					printf("\nVOLVIENDO...\n");
					break;
				default:
					system("cls");
					printf("\nError: respuesta invalida. Intentelo de nuevo.\n");
					system("pause");
			}
			
			if((opc >=1) && (opc <= 4)){
				
				strcpy(tipoMayus,tipo);
				system("cls");
				printf("\n///////////LISTADO DE GASTOS DE TIPO %s////////////\n\n",strupr(tipoMayus));
				
				rewind(fgas); //casi me lo como, practicar..
				fread(&gasto,sizeof(Gasto),1,fgas);
				
				while(!feof(fgas)){
						
					if(gasto.tipoGasto == opc){
						
						switch(gasto.estadoCuota){
								case 1:
									strcpy(estado,"No Pagado");
									break;
								case 2:
									strcpy(estado,"Parcialmente");
									break;
								case 3:
									strcpy(estado,"Pagado");
									break;		
							}
						
						existe = 1;
						printf("Codigo: %llu\n",gasto.codGasto);
						printf("Tipo de Gasto: %s\n", tipo);
						printf("Descripcion: %s\n", gasto.desc);
						printf("Categoria: %s\n",gasto.categoria.nombre);
						printf("Monto: $%.2lf\n",gasto.monto);
						printf("Fecha del Gasto: %d/%d/%d\n",gasto.fechaGasto.dia,gasto.fechaGasto.mes,gasto.fechaGasto.anio);
						printf("Cuotas Totales: %d\n", gasto.cuotasTotales);
						printf("Cuota Actual: %d\n",gasto.cuotaActual);
						printf("Persona Responsable: %s\n",gasto.persona.nombre);
						printf("Estado: %s", estado);
						printf("\n\n");
						
					}
					
					fread(&gasto,sizeof(Gasto),1,fgas);
				}
				system("pause");
				system("cls");
				
				yy1=1;
                while(yy1){
                	printf("\nDesea continuar? (2 si, 1 no): \t");
	                fflush(stdin);
	                gets(Cad18);
		            continuar=digitos(Cad18);
	                
                	if(((continuar==0)||(continuar<0)||(continuar>2))){
                		system("cls");
	                	printf("\nIngresar Correctamente La Opcion (2 si, 1 no)\n\n");
	                	system("PAUSE");
	                	system("cls");
				
					}else{
						yy1=0;
						if(continuar==1){
							continuar=0;
						}
						if(continuar==2){
							continuar=1;
						}
					}
				}
				
				
			}
			
		}
		
		fclose(fgas);
	}
	else{
		system("cls");
		printf("\nError: no se cargaron gastos hasta el momento.\n");
		system("pause");
	}
	
}

///////////////////////////////////////// filtrarPorCategoria ///////////////////////////////////////////////////////////////////////////////////////

void filtrarPorCategoria() {
	char Cad17[50000];
    char nombreCategoria[50], tipo[10], estado[15];
    int encontrado = 0,y=1,yy=1;
    unsigned long long cod;
    int continuar = 1, encontrados;  
    FILE *fcat, *fgas;
    
    
    
    if((fcat = fopen("categorias.dat","rb"))==NULL){
        system("cls");
        printf("\nNo se han cargado categorias hasta el momento.\n");
        system("pause");
        
    }
    
    fseek(fcat, 0, SEEK_END);
    if(ftell(fcat) == 0) {
        fclose(fcat);
        system("cls");
        printf("\nNo se han cargado categorias hasta el momento.\n");
        system("pause");
        
    }
    rewind(fcat);
    
    if((fgas = fopen("gastos.dat","rb"))!=NULL){
        
        while(continuar == 1){
            
            encontrado = 0;  
            rewind(fcat);
            fread(&categoria,sizeof(Categoria),1,fcat);
            system("cls");
            printf("\n//////CATEGORIAS EXISTENTES///////\n");
            encontrados = 0;
            while(!feof(fcat)){
                encontrados = 1;
                printf("Codigo: %llu\tNombre: %s\n",categoria.codigo,categoria.nombre);
                fread(&categoria,sizeof(Categoria),1,fcat);
            }
            
            if(!encontrados){
                printf("\nNo se encontraron categorias cargadas.\n");
                continuar = 0;
            }
            else{
                
                y=1;
                while(y){
                	printf("\nIngrese el codigo de la categoria a escoger:\t");
	                fflush(stdin);
	                gets(Cad17);
	                cod=digitos(Cad17);
	                
                	if(cod==0){
                		
	                	printf("\nIngresar Correctamente El Codigo, Solo Puede Ser Un Digito\n\n");
	                	system("PAUSE");
				
					}else{
						y=0;
					}
				}
                
                
                rewind(fcat);
                fread(&categoria,sizeof(Categoria),1,fcat);            
                while((!feof(fcat))&&(encontrado == 0)){
                    if(cod == categoria.codigo){
                        encontrado = 1;
                        strcpy(nombreCategoria,categoria.nombre);
                        fseek(fcat,sizeof(Categoria)*(-1),SEEK_CUR); 
                    }
                    else{
                        fread(&categoria,sizeof(Categoria),1,fcat);
                    }
                    
                }                                        
                
                if(!encontrado){
                    printf("\nNo se encontro la categoria buscada.\n");
                }
                else{
                    system("cls");
                    printf("\n//////GASTOS POR CATEGORIA SELECCIONADA//////\n\n");
                    encontrados = 0;
                    rewind(fgas);
                    fread(&gasto,sizeof(Gasto),1,fgas);
                    while(!feof(fgas)){
                        if(strcmp(gasto.categoria.nombre,nombreCategoria) == 0 ){
                            
                            switch(gasto.tipoGasto){
                            case 1:
                                strcpy(tipo,"Fijo");
                                break;
                            case 2:
                                strcpy(tipo,"Ocasional");
                                break;    
                            case 3:
                                strcpy(tipo,"Temporal");
                                break;
                            case 4:
                                strcpy(tipo,"Anual");
                                break;    
                            }
                    
                            switch(gasto.estadoCuota){
                                case 1:
                                    strcpy(estado,"No Pagado");
                                    break;
                                case 2:
                                    strcpy(estado,"Parcialmente");
                                    break;
                                case 3:
                                    strcpy(estado,"Pagado");
                                    break;        
                            }
                            
                            encontrados = 1;
                            printf("Codigo: %llu\n",gasto.codGasto);
                            printf("Tipo de Gasto: %s\n", tipo);
                            printf("Descripcion: %s\n", gasto.desc);
                            printf("Categoria: %s\n",gasto.categoria.nombre);
                            printf("Monto: $%.2lf\n",gasto.monto);
                            printf("Fecha del Gasto: %d/%d/%d\n",gasto.fechaGasto.dia,gasto.fechaGasto.mes,gasto.fechaGasto.anio);
                            printf("Cuotas Totales: %d\n", gasto.cuotasTotales);
                            printf("Cuota Actual: %d\n",gasto.cuotaActual);
                            printf("Persona Responsable: %s\n",gasto.persona.nombre);
                            printf("Estado: %s", estado);
                            printf("\n\n");
                        }
                        fread(&gasto,sizeof(Gasto),1,fgas);
                    }
                
                }
                
                if(!encontrados){
                    printf("\nNo se encontraron gastos de la categoria seleccionada.\n");
                }
                system("pause");
                system("cls");
                
                
                yy=1;
                while(yy){
                	printf("\nDesea buscar otra categoria? (2 si, 1 no): \t");
	                fflush(stdin);
	                gets(Cad17);
		            continuar=digitosC(Cad17);
	                
	                
	                
                	if(((continuar==0)||(continuar<0)||(continuar>2))){
                		system("cls");
	                	printf("\nIngresar Correctamente La Opcion (2 si, 1 no)\n\n");
	                	system("PAUSE");
	                	system("cls");
				
					}else{
						yy=0;
						if(continuar==1){
							continuar=0;
						}
						if(continuar==2){
							continuar=1;
						}
					}
				}
                
            }
            
        }
        
        fclose(fgas);
    }
    else{
        system("cls");
        printf("\nNo se han cargado gastos hasta el momento.\n");
        system("pause");
    }
    fclose(fcat);
	
}

///////////////////////////////////////// filtrarPorMes ///////////////////////////////////////////////////////////////////////////////////////

void filtrarPorMes() {
	char Cad19[50000];
    FILE *fgas;
	int continuar = 1, opc, encontrados, mes, anio,a=1,yy2=1;
	char tipo[10], estado[15];

	if((fgas = fopen("gastos.dat","rb"))!=NULL){
	
	    while(continuar){
	    	a=1;
			while(a){
				system("cls");
		    	printf("\nEscoja el mes: \t");
				fflush(stdin);
				gets(Cad19);
        		mes=digitosC(Cad19);
        		if(mes==0){
        			system("cls");
        			printf("\nSolo se puede ingresar Numeros Enteros\n\n");
        			system("PAUSE");
				}else{
					a=0;
					if((mes < 1)||(mes > 12)){
						system("cls");
						printf("\nMes invalido. Intente de vuelta.\n");
						system("PAUSE");
						a=1;
					}
				}
			}
			
			a=1;
			while(a){
				
		    	printf("\nEscoja el anio:\t");
				fflush(stdin);
				gets(Cad19);
        		anio=digitosC(Cad19);
        		if(anio==0){
        			system("cls");
        			printf("\nSolo se puede ingresar Numeros Enteros\n\n");
        			system("PAUSE");
				}else{
					a=0;
					if((anio < 1900)||(anio > 3000)){
						system("cls");
						printf("\nAnio invalido. Intente de vuelta.\n");
						system("PAUSE");
						a=1;
					}
				}
			}
			
			system("cls");
			printf("\n/////LISTADO DE GASTOS DEL MES SELECCIONADO/////\n\n");
			encontrados = 0;
			rewind(fgas);
			fread(&gasto,sizeof(Gasto),1,fgas);
			while(!feof(fgas)){
				if((gasto.fechaGasto.mes == mes) && (gasto.fechaGasto.anio == anio)){
					
					switch(gasto.tipoGasto){
						case 1:
							strcpy(tipo,"Fijo");
							break;
						case 2:
							strcpy(tipo,"Ocasional");
							break;	
						case 3:
							strcpy(tipo,"Temporal");
							break;
						case 4:
							strcpy(tipo,"Anual");
							break;	
					}
			
					switch(gasto.estadoCuota){
						case 1:
							strcpy(estado,"No Pagado");
							break;
						case 2:
							strcpy(estado,"Parcialmente");
							break;
						case 3:
							strcpy(estado,"Pagado");
							break;		
					}
					
					encontrados = 1;
					printf("Codigo: %llu\n",gasto.codGasto);
					printf("Tipo de Gasto: %s\n", tipo);
					printf("Descripcion: %s\n", gasto.desc);
					printf("Categoria: %s\n",gasto.categoria.nombre);
					printf("Monto: $%.2lf\n",gasto.monto);
					printf("Fecha del Gasto: %d/%d/%d\n",gasto.fechaGasto.dia,gasto.fechaGasto.mes,gasto.fechaGasto.anio);
					printf("Cuotas Totales: %d\n", gasto.cuotasTotales);
					printf("Cuota Actual: %d\n",gasto.cuotaActual);
					printf("Persona Responsable: %s\n",gasto.persona.nombre);
					printf("Estado: %s", estado);
					printf("\n\n");
				}
				fread(&gasto,sizeof(Gasto),1,fgas);
			}
			if(!encontrados){
				printf("\nNo se encontraron registros con las caracteristicas seleccionadas.\n\n");
			}
			
			
			yy2=1;
            while(yy2){
            	printf("\nDesea continuar? (2 si, 1 no): \t");
                fflush(stdin);
                gets(Cad19);
	            continuar=digitosC(Cad19);
                
            	if(((continuar==0)||(continuar<0)||(continuar>2))){
            		system("cls");
                	printf("\nIngresar Correctamente La Opcion (2 si, 1 no)\n\n");
                	system("PAUSE");
                	system("cls");
			
				}else{
					yy2=0;
					if(continuar==1){
						continuar=0;
					}
					if(continuar==2){
						continuar=1;
					}
				}
			}
		
		
		}	
		    
		
		fclose(fgas);
	}
	else{
		system("cls");
		printf("\nError: no se cargaron gastos hasta el momento.\n");
		system("pause");
	}
	
}

///////////////////////////////////////// gastosPorCategoria ///////////////////////////////////////////////////////////////////////////////////////

void gastosPorCategoria() {
	char Cad20[50000];
    char nombreCategoria[50], tipo[10], estado[15];
    int encontrado = 0,yy3=1;
    unsigned long long cod;
    int continuar = 1, encontrados;  
    FILE *fcat, *fgas;
    
 
    if((fcat = fopen("categorias.dat","rb"))==NULL){
        system("cls");
        printf("--------------------\nGASTOS POR CATEGORIA\n--------------------\n");
        printf("\nNo se han cargado categorias hasta el momento.\n");
        system("pause");
        
    }
    
    fseek(fcat, 0, SEEK_END);
    if(ftell(fcat) == 0) {
        fclose(fcat);
        system("cls");
        printf("--------------------\nGASTOS POR CATEGORIA\n--------------------\n");
        printf("\nNo se han cargado categorias hasta el momento.\n");
        system("pause");
        
    }
    rewind(fcat);
    
    if((fgas = fopen("gastos.dat","rb"))!=NULL){
        
        while(continuar == 1){
            
            encontrado = 0;  
            rewind(fcat);
            fread(&categoria,sizeof(Categoria),1,fcat);
            system("cls");
            printf("--------------------\nGASTOS POR CATEGORIA\n--------------------\n");
            printf("\n//////CATEGORIAS EXISTENTES///////\n\n");
            encontrados = 0;
            while(!feof(fcat)){
                encontrados = 1;
                printf("Codigo: %llu\tNombre: %s\n",categoria.codigo,categoria.nombre);
                fread(&categoria,sizeof(Categoria),1,fcat);
            }
            
            if(!encontrados){
                printf("\nNo se encontraron categorias cargadas.\n");
                continuar = 0;
            }
            else{
                
                yy3=1;
                while(yy3){
                	printf("\nIngrese el codigo de la categoria a escoger:\t");
	                fflush(stdin);
	                gets(Cad20);
	                cod=digitos(Cad20);
	                
                	if(cod==0){
                		
	                	printf("\nIngresar Correctamente El Codigo, Solo Puede Ser Un Digito\n\n");
	                	system("PAUSE");
				
					}else{
						yy3=0;
					}
				}
                
                
                rewind(fcat);                                        
                fread(&categoria,sizeof(Categoria),1,fcat);            
                while((!feof(fcat))&&(encontrado == 0)){
                    if(cod == categoria.codigo){
                        encontrado = 1;
                        strcpy(nombreCategoria,categoria.nombre);
                        fseek(fcat,sizeof(Categoria)*(-1),SEEK_CUR); 
                    }
                    else{
                        fread(&categoria,sizeof(Categoria),1,fcat);
                    }
                    
                }                                        
                
                if(!encontrado){
                    printf("\nNo se encontro la categoria buscada.\n");
                }
                else{
                    system("cls");
                    printf("\n//////GASTOS POR CATEGORIA SELECCIONADA//////\n\n");
                    encontrados = 0;
                    rewind(fgas);
                    fread(&gasto,sizeof(Gasto),1,fgas);
                    while(!feof(fgas)){
                        if(strcmp(gasto.categoria.nombre,nombreCategoria) == 0 ){
                            
                            switch(gasto.tipoGasto){
                            case 1:
                                strcpy(tipo,"Fijo");
                                break;
                            case 2:
                                strcpy(tipo,"Ocasional");
                                break;    
                            case 3:
                                strcpy(tipo,"Temporal");
                                break;
                            case 4:
                                strcpy(tipo,"Anual");
                                break;    
                            }
                    
                            switch(gasto.estadoCuota){
                                case 1:
                                    strcpy(estado,"No Pagado");
                                    break;
                                case 2:
                                    strcpy(estado,"Parcialmente");
                                    break;
                                case 3:
                                    strcpy(estado,"Pagado");
                                    break;        
                            }
                            
                            encontrados = 1;
                            printf("Codigo: %llu\n",gasto.codGasto);
                            printf("Tipo de Gasto: %s\n", tipo);
                            printf("Descripcion: %s\n", gasto.desc);
                            printf("Categoria: %s\n",gasto.categoria.nombre);
                            printf("Monto: $%.2lf\n",gasto.monto);
                            printf("Fecha del Gasto: %d/%d/%d\n",gasto.fechaGasto.dia,gasto.fechaGasto.mes,gasto.fechaGasto.anio);
                            printf("Cuotas Totales: %d\n", gasto.cuotasTotales);
                            printf("Cuota Actual: %d\n",gasto.cuotaActual);
                            printf("Persona Responsable: %s\n",gasto.persona.nombre);
                            printf("Estado: %s", estado);
                            printf("\n\n");
                        }
                        fread(&gasto,sizeof(Gasto),1,fgas);
                    }
                
                }
                
                if(!encontrados){
                    system("cls");
                    printf("\nNo se encontraron gastos de la categoria seleccionada.\n");
                }
                
                system("pause");
                system("cls");
                
                yy3=1;
                while(yy3){
                	printf("\nDesea buscar otra categoria? (2 si, 1 no): \t");
	                fflush(stdin);
	                gets(Cad20);
		            continuar=digitosC(Cad20);
	                
                	if(((continuar==0)||(continuar<0)||(continuar>2))){
                		system("cls");
	                	printf("\nIngresar Correctamente La Opcion (2 si, 1 no)\n\n");
	                	system("PAUSE");
	                	system("cls");
				
					}else{
						yy3=0;
						if(continuar==1){
							continuar=0;
						}
						if(continuar==2){
							continuar=1;
						}
					}
				}
                
                
            }
            
        }
        
        fclose(fgas);
    }
    else{
        system("cls");
        printf("--------------------\nGASTOS POR CATEGORIA\n--------------------\n");
        printf("\nNo se han cargado gastos hasta el momento.\n");
        system("pause");
    }
    fclose(fcat);
	
}

///////////////////////////////////////// gastosPorMesYAnio ///////////////////////////////////////////////////////////////////////////////////////

void gastosPorMesYAnio() {
	char Cad21[50000];
    int mes, anio, encontrados;
	int eleccion;
	int continuar = 1,a2=1,yy4=1;
	FILE *fgas;
	char tipo[10], estado[15];
	
	if((fgas = fopen("gastos.dat","rb"))!=NULL){
		
		while(continuar){
			system("cls");
			
			a2=1;
			while(a2){
				printf("---------\n2. GASTOS POR MES Y ANIO\n---------");
				
				printf("\nVa a elegir mes o anio? (1 mes, 2 anio, 3 volver): \t");
				fflush(stdin);
				gets(Cad21);
				eleccion=digitosC(Cad21);
				
				if((eleccion != 1)&&(eleccion != 2)&&(eleccion != 3)){
					system("cls");
					printf("\nError: opcion invalida.\n");
					system("pause");
					system("cls");
					
				}else{
					a2=0;
				}
					
				
			}
            
			if(eleccion == 3){
				continuar = 0;
				printf("\nVOLVIENDO...\n");
			}
			else if(eleccion == 1){
				
				a2=1;
				while(a2){
					system("cls");
			    	printf("\nEscoja el mes: \t");
					fflush(stdin);
					gets(Cad21);
	        		mes=digitosC(Cad21);
	        		if(mes==0){
	        			system("cls");
	        			printf("\nSolo se puede ingresar Numeros Enteros\n\n");
	        			system("PAUSE");
					}else{
						a2=0;
						if((mes < 1)||(mes > 12)){
							system("cls");
							printf("\nMes invalido. Intente de vuelta.\n");
							system("PAUSE");
							a2=1;
						}
					}
				}
				
				a2=1;
				while(a2){
					
			    	printf("\nEscoja el anio:\t");
					fflush(stdin);
					gets(Cad21);
	        		anio=digitosC(Cad21);
	        		if(anio==0){
	        			system("cls");
	        			printf("\nSolo se puede ingresar Numeros Enteros\n\n");
	        			system("PAUSE");
					}else{
						a2=0;
						if((anio < 1900)||(anio > 3000)){
							system("cls");
							printf("\nAnio invalido. Intente de vuelta.\n");
							system("PAUSE");
							a2=1;
						}
					}
				}
				
				printf("\n/////GASTOS DEL MES SELECCIONADO/////\n");
				encontrados = 0;
				rewind(fgas);
				fread(&gasto,sizeof(Gasto),1,fgas);
				while(!feof(fgas)){
					if((gasto.fechaGasto.mes == mes) && (gasto.fechaGasto.anio == anio)){
						
						switch(gasto.tipoGasto){
								case 1:
									strcpy(tipo,"Fijo");
									break;
								case 2:
									strcpy(tipo,"Ocasional");
									break;	
								case 3:
									strcpy(tipo,"Temporal");
									break;
								case 4:
									strcpy(tipo,"Anual");
									break;	
							}
					
							switch(gasto.estadoCuota){
								case 1:
									strcpy(estado,"No Pagado");
									break;
								case 2:
									strcpy(estado,"Parcialmente");
									break;
								case 3:
									strcpy(estado,"Pagado");
									break;		
							}
							
						encontrados = 1;
						printf("Codigo: %llu\n",gasto.codGasto);
						printf("Tipo de Gasto: %s\n", tipo);
						printf("Descripcion: %s\n", gasto.desc);
						printf("Categoria: %s\n",gasto.categoria.nombre);
						printf("Monto: $%.2lf\n",gasto.monto);
						printf("Fecha del Gasto: %d/%d/%d\n",gasto.fechaGasto.dia,gasto.fechaGasto.mes,gasto.fechaGasto.anio);
						printf("Cuotas Totales: %d\n", gasto.cuotasTotales);
						printf("Cuota Actual: %d\n",gasto.cuotaActual);
						printf("Persona Responsable: %s\n",gasto.persona.nombre);
						printf("Estado: %s", estado);
						printf("\n\n");
						
					}
					fread(&gasto,sizeof(Gasto),1,fgas);
				}
				if(!encontrados){
					system("cls");
					printf("\nNo se encontraron registros con las caracteristicas seleccionadas.\n");
					
				}
				system("pause");
				system("cls");
				
				yy4=1;
                while(yy4){
                	printf("\nDesea buscar otra categoria? (2 si, 1 no): \t");
	                fflush(stdin);
	                gets(Cad21);
		            continuar=digitosC(Cad21);
	                
                	if(((continuar==0)||(continuar<0)||(continuar>2))){
                		system("cls");
	                	printf("\nIngresar Correctamente La Opcion (2 si, 1 no)\n\n");
	                	system("PAUSE");
	                	system("cls");
				
					}else{
						yy4=0;
						if(continuar==1){
							continuar=0;
						}
						if(continuar==2){
							continuar=1;
						}
					}
				}
				
				
			}
			else if(eleccion == 2){
				
				a2=1;
				while(a2){
					
			    	printf("\nEscoja el anio:\t");
					fflush(stdin);
					gets(Cad21);
	        		anio=digitosC(Cad21);
	        		if(anio==0){
	        			system("cls");
	        			printf("\nSolo se puede ingresar Numeros Enteros\n\n");
	        			system("PAUSE");
					}else{
						a2=0;
						if((anio < 1900)||(anio > 3000)){
							system("cls");
							printf("\nAnio invalido. Intente de vuelta.\n");
							system("PAUSE");
							a2=1;
						}
					}
				}
				
				printf("\n/////GASTOS DEL ANIO SELECCIONADO/////\n");
				encontrados = 0;
				rewind(fgas);
				fread(&gasto,sizeof(Gasto),1,fgas);
				while(!feof(fgas)){
					if(gasto.fechaGasto.anio == anio){
						
						switch(gasto.tipoGasto){
								case 1:
									strcpy(tipo,"Fijo");
									break;
								case 2:
									strcpy(tipo,"Ocasional");
									break;	
								case 3:
									strcpy(tipo,"Temporal");
									break;
								case 4:
									strcpy(tipo,"Anual");
									break;	
							}
					
							switch(gasto.estadoCuota){
								case 1:
									strcpy(estado,"No Pagado");
									break;
								case 2:
									strcpy(estado,"Parcialmente");
									break;
								case 3:
									strcpy(estado,"Pagado");
									break;		
							}
							
						encontrados = 1;
						printf("Codigo: %llu\n",gasto.codGasto);
						printf("Tipo de Gasto: %s\n", tipo);
						printf("Descripcion: %s\n", gasto.desc);
						printf("Categoria: %s\n",gasto.categoria.nombre);
						printf("Monto: $%.2lf\n",gasto.monto);
						printf("Fecha del Gasto: %d/%d/%d\n",gasto.fechaGasto.dia,gasto.fechaGasto.mes,gasto.fechaGasto.anio);
						printf("Cuotas Totales: %d\n", gasto.cuotasTotales);
						printf("Cuota Actual: %d\n",gasto.cuotaActual);
						printf("Persona Responsable: %s\n",gasto.persona.nombre);
						printf("Estado: %s", estado);
						printf("\n\n");
						
					}
					fread(&gasto,sizeof(Gasto),1,fgas);
				}
				if(!encontrados){
					system("cls");
					printf("\nNo se encontraron registros con las caracteristicas seleccionadas.\n");
					system("pause");
				}
				system("pause");
				system("cls");
				
				yy4=1;
                while(yy4){
                	printf("\nDesea buscar otra categoria? (2 si, 1 no): \t");
	                fflush(stdin);
	                gets(Cad21);
		            continuar=digitosC(Cad21);
	                
                	if(((continuar==0)||(continuar<0)||(continuar>2))){
                		system("cls");
	                	printf("\nIngresar Correctamente La Opcion (2 si, 1 no)\n\n");
	                	system("PAUSE");
	                	system("cls");
				
					}else{
						yy4=0;
						if(continuar==1){
							continuar=0;
						}
						if(continuar==2){
							continuar=1;
						}
					}
				}
			}
			
		}
		fclose(fgas);
	}
	else{
		system("cls");
		printf("\nNo se han cargado gastos hasta el momento.\n");
		system("pause");
	}
	
}

///////////////////////////////////////// ingresosPorPersona ///////////////////////////////////////////////////////////////////////////////////////

void ingresosPorPersona() { 
	char Cad22[50000];
    FILE *fper, *fing;
	int continuar = 1,yy5=1,a3=1;
	int encontrados, existePers, existeIng;
	long long dni;
	
	if((fper = fopen("personas.dat","rb"))!=NULL){
		if((fing = fopen("ingresos.dat","rb"))!=NULL){
			
			while(continuar){
				
				rewind(fper);
				fread(&persona,sizeof(Persona),1,fper);
				system("cls");
				printf("---------\nINGRESOS POR PERSONA\n---------\n"); //ver estetica cuando se pueda cargar el personas.dat
				printf("\n/////PERSONAS REGISTRADAS////////\n");
				while(!feof(fper)){
					encontrados = 1;
					printf("Dni: %lld\tNombre: %s\n",persona.dni,persona.nombre);
					fread(&persona,sizeof(Persona),1,fper);
				}
				if(!encontrados){
					printf("\nNo se encontraron personas registradas.\n");
				}
			
				if(encontrados){
					a3=1;
					while(a3){
						printf("\nIngrese el dni de la persona deseada: \t");
						fflush(stdin);
						gets(Cad22);
		            	dni=digitosDNI(Cad22);
						if((dni == 0)||(dni>100000000)||(dni<1000000)){
							printf("\nDni invalido. Intentelo nuevamente.\n");
							
					    }else{
					    	a3=0;
						}
					}
					
				    
				    existePers = 0;
				    rewind(fper);
				    fread(&persona,sizeof(Persona),1,fper);
				    while((!feof(fper))&&(existePers == 0)){
				    	if(dni == persona.dni){
				    		existePers = 1;
				    		fseek(fper,sizeof(Persona)*(-1),SEEK_CUR);
						}
						else{
							fread(&persona,sizeof(Persona),1,fper);
						}
						
					}

					if(!existePers){
						printf("\nNo se encontro ni una persona con el dni ingresado.\n");
					}
					else{
						
						printf("\n//////INGRESOS DE LA PERSONA DADA//////\n");
						existeIng = 0;
						rewind(fing);
						fread(&ingreso,sizeof(Ingreso),1,fing);
						while(!feof(fing)){
							if(ingreso.persona.dni == dni){
								existeIng = 1;
								printf("Codigo: %llu\n",ingreso.codIngreso);
								printf("Concepto: %s\n", ingreso.concepto);
								printf("Monto: $%.2lf\n", ingreso.monto);
								printf("Fecha del Ingreso: %d/%d/%d\n",ingreso.fecha.dia,ingreso.fecha.mes,ingreso.fecha.anio);
								printf("Persona Responsable: %s\n",ingreso.persona.nombre);								
								printf("\n\n");
							}
							fread(&ingreso,sizeof(Ingreso),1,fing);
						}
						
						if(!existeIng){
							printf("\nNo se encontraron ingresos de esa persona.\n");
						}
					}
				}
				yy5=1;
                while(yy5){
                	printf("\nDesea Continuar? (2 si, 1 no): \t");
	                fflush(stdin);
	                gets(Cad22);
		            continuar=digitosC(Cad22);
	                
                	if(((continuar==0)||(continuar<0)||(continuar>2))){
                		system("cls");
	                	printf("\nIngresar Correctamente La Opcion (2 si, 1 no)\n\n");
	                	system("PAUSE");
	                	system("cls");
				
					}else{
						yy5=0;
						if(continuar==1){
							continuar=0;
						}
						if(continuar==2){
							continuar=1;
						}
					}
				}
			}
			fclose(fing);
		}
		else{
			system("cls");
			printf("\nNo hay ingresos cargados hasta el momento.\n");
			system("pause");
		}
		fclose(fper);
	}
	else{
		system("cls");
		printf("\nNo hay personas cargadas hasta el momento.\n");
		system("pause");
	}
}

///////////////////////////////////////// saldoMensual ///////////////////////////////////////////////////////////////////////////////////////

void saldoMensual() {
	char Cad22[50000];
    int mes,anio, continuar = 1,a4=1,yy5=1;
	double total_ingresos, total_gastos, saldo;
	FILE *fing, *fgas;
	
	if((fing = fopen("ingresos.dat","rb"))!=NULL){
		if((fgas = fopen("gastos.dat","rb"))!=NULL){
			
			while(continuar){
				system("cls");
				printf("-------------\nSALDO MENSUAL\n-------------");
				
				
				
				a4=1;
				while(a4){
					
			    	printf("\nEscoja el mes:\t");
					fflush(stdin);
					gets(Cad22);
	        		mes=digitosC(Cad22);
	        		if(mes==0){
	        			system("cls");
	        			printf("\nSolo se puede ingresar Numeros Enteros\n\n");
	        			system("PAUSE");
					}else{
						a4=0;
						if((mes < 1)||(mes > 12)){
							system("cls");
							printf("\nMes invalido. Intente de vuelta.\n");
							system("PAUSE");
							a4=1;
						}
					}
				}
				
				
				
				
				a4=1;
				while(a4){
					
			    	printf("\nEscoja el anio:\t");
					fflush(stdin);
					gets(Cad22);
	        		anio=digitosC(Cad22);
	        		if(anio==0){
	        			system("cls");
	        			printf("\nSolo se puede ingresar Numeros Enteros\n\n");
	        			system("PAUSE");
					}else{
						a4=0;
						if((anio < 1900)||(anio > 3000)){
							system("cls");
							printf("\nAnio invalido. Intente de vuelta.\n");
							system("PAUSE");
							a4=1;
						}
					}
				}
				
				
				total_ingresos = 0;
				rewind(fing);
				fread(&ingreso,sizeof(Ingreso),1,fing);
				while(!feof(fing)){
					if((ingreso.fecha.anio == anio)&&(ingreso.fecha.mes == mes)){
						total_ingresos += ingreso.monto;
					}
					fread(&ingreso,sizeof(Ingreso),1,fing);
				}
				//dividir monto por cuotas totales //al registrar gastos, que no pueda quedar cuotas en 0
				total_gastos = 0;
				rewind(fgas);
				fread(&gasto,sizeof(Gasto),1,fgas);
				while(!feof(fgas)){
					if((gasto.fechaGasto.anio == anio)&&(gasto.fechaGasto.mes == mes)){
						total_gastos += gasto.monto / gasto.cuotasTotales;
					}
					fread(&gasto,sizeof(Gasto),1,fgas);
				}
				
				saldo = total_ingresos - total_gastos;
				system("cls");
				printf("\n//////SALDO MENSUAL DEL MES DADO//////\n");
				printf("\nIngresos Totales: $%.2lf\n",total_ingresos);
				printf("\nGastos Totales: $%.2lf\n", total_gastos);
				printf("\n-------------------------\n");
				printf("\nSaldo Final: $%.2lf\n",saldo);
				printf("\n\n");
				
				system("pause");
				system("cls");
				
				
				
				yy5=1;
                while(yy5){
                	printf("\nDesea buscar otro saldo mensual? (2 si, 1 no): \t");
	                fflush(stdin);
	                gets(Cad22);
		            continuar=digitosC(Cad22);
	                
                	if(((continuar==0)||(continuar<0)||(continuar>2))){
                		system("cls");
	                	printf("\nIngresar Correctamente La Opcion (2 si, 1 no)\n\n");
	                	system("PAUSE");
	                	system("cls");
				
					}else{
						yy5=0;
						if(continuar==1){
							continuar=0;
						}
						if(continuar==2){
							continuar=1;
						}
					}
				}
				
			}
			fclose(fgas);
		}
		else{
			system("cls");
			printf("\nNo se registraron gastos hasta el momento.\n");
			system("pause");
		}
		fclose(fing);
	}
	else{
		system("cls");
		printf("\nNo se registraron ingresos hasta el momento.\n");
		system("pause");
	}
	
}

///////////////////////////////////////// gastosPendientes ///////////////////////////////////////////////////////////////////////////////////////

void gastosPendientes() {
	
    FILE *fgas;
	int cuotasPendientes;
	double saldoPendiente;
	int existe = 0;
	
	if((fgas = fopen("gastos.dat","rb"))!=NULL){
		    system("cls");
			printf("\n//////////GASTOS TEMPORALES PENDIENTES DE PAGO//////////\n");
			rewind(fgas);
			fread(&gasto,sizeof(Gasto),1,fgas);
			while(!feof(fgas)){
				if(gasto.tipoGasto == 3){
					if(gasto.cuotasTotales != gasto.cuotaActual){
						cuotasPendientes = gasto.cuotasTotales - gasto.cuotaActual;
						saldoPendiente = (cuotasPendientes * gasto.monto) / gasto.cuotasTotales;
						printf("\n%s (%d de %d cuotas)\n",gasto.desc,gasto.cuotaActual,gasto.cuotasTotales);
						printf("Pendiente: %d cuotas. Monto Pendiente: $%.2lf\n",cuotasPendientes,saldoPendiente);
						printf("Iniciado: %d/%d/%d\n",gasto.fechaGasto.dia,gasto.fechaGasto.mes,gasto.fechaGasto.anio);
						existe = 1;
						printf("\n");
					}
				}
				fread(&gasto,sizeof(Gasto),1,fgas);
			}
			
			if(!existe){
				system("cls");
				printf("\nNo se encuentran gastos temporales pendientes de pago.\n\n");
			}
			
		fclose(fgas);
	}
	else{
		system("cls");
		printf("\nNo se han cargado gastos hasta el momento.\n\n");
	}
	
	printf("\n\n");
	system("pause");
	
}

///////////////////////////////////////// pagosPorMedioDePago ///////////////////////////////////////////////////////////////////////////////////////

void pagosPorMedioDePago() {
	char Cad24[50000];
    int continuar = 1, opc, existe,a5=1,yy6=1;
	FILE *fpag;
	
	if((fpag = fopen("pagos.dat","rb"))!=NULL){
		
		while(continuar){
			
			
			a5=1;
			while(a5){
				system("cls");
				printf("---------\n6. PAGOS POR MEDIO DE PAGO\n---------");
				printf("\nSeleccione el medio de pago:\n\n1. Efectivo\n2. Billetera Electronica\n3. Tarjeta\n4. Debito\n5. Volver\n\nElija una opcion: \t");
				fflush(stdin);
				
				gets(Cad24);
	       		opc=digitosC(Cad24);
	       		if((opc<1)||(opc>5)){
	       			system("cls");
	       			printf("\nIngrese Un Numero Valido Del 1-5 De Tipo Entero\n\n");
	       			system("PAUSE");
				}else{
					a5=0;
				}
			}
			
            
       		
       		
       		system("cls");
			switch(opc){
				
				case 1:
					printf("\n///////PAGOS EN EFECTIVO////////\n");
					existe = 0;
					rewind(fpag);
					fread(&pago,sizeof(Pago),1,fpag);
					while(!feof(fpag)){
						if(pago.medioPago == 1){
							existe = 1;
							printf("\nGasto #%llu - $%.2lf\n",pago.codGasto,pago.importe);
							printf("Fecha: %d/%d/%d",pago.fechaPago.dia,pago.fechaPago.mes,pago.fechaPago.anio);
							printf("\n\n");
						}
						fread(&pago,sizeof(Pago),1,fpag);
					}
					
					if(!existe){
						printf("\nNo hay pagos registrados con el metodo seleccionado.\n");
					}
					break;
					
				case 2:
						
					printf("\n///////PAGOS CON BILLETERA ELECTRONICA////////\n");
					existe = 0;
					rewind(fpag);
					fread(&pago,sizeof(Pago),1,fpag);
					while(!feof(fpag)){
						if(pago.medioPago == 2){
							existe = 1;
							printf("\nGasto #%llu - $%.2lf\n",pago.codGasto,pago.importe);
							printf("Fecha: %d/%d/%d",pago.fechaPago.dia,pago.fechaPago.mes,pago.fechaPago.anio);
							printf("\n\n");
						}
						fread(&pago,sizeof(Pago),1,fpag);
					}
					
					if(!existe){
						printf("\nNo hay pagos registrados con el metodo seleccionado.\n");
					}
					break;		
				
					
				case 3:
					
					printf("\n///////PAGOS CON TARJETA////////\n");
					existe = 0;
					rewind(fpag);
					fread(&pago,sizeof(Pago),1,fpag);
					while(!feof(fpag)){
						if(pago.medioPago == 3){
							existe = 1;
							printf("\nGasto #%llu - $%.2lf\n",pago.codGasto,pago.importe);
							printf("Fecha: %d/%d/%d",pago.fechaPago.dia,pago.fechaPago.mes,pago.fechaPago.anio);
							printf("\n\n");
						}
						fread(&pago,sizeof(Pago),1,fpag);
					}
				
					if(!existe){
						printf("\nNo hay pagos registrados con el metodo seleccionado.\n");
					}
					break;
					
				case 4:
					
					printf("\n///////PAGOS CON DEBITO////////\n");
					existe = 0;
					rewind(fpag);
					fread(&pago,sizeof(Pago),1,fpag);
					while(!feof(fpag)){
						if(pago.medioPago == 4){
							existe = 1;
							printf("\nGasto #%llu - $%.2lf\n",pago.codGasto,pago.importe);
							printf("Fecha: %d/%d/%d",pago.fechaPago.dia,pago.fechaPago.mes,pago.fechaPago.anio);
							printf("\n\n");
						}
						fread(&pago,sizeof(Pago),1,fpag);
					}
				
					if(!existe){
						system("cls");
						printf("\nNo hay pagos registrados con el metodo seleccionado.\n\n");
						system("pause");
					}
					break;
					
					
				case 5:
					
					continuar = 0;
					printf("\nVOLVIENDO...\n\n");
					
					break;
					
				default:
					
					printf("\nOpcion invalida. Intentelo nuevamente.\n\n");	
						
			}
			
			if(continuar){
				system("pause");
				system("cls");
				
				yy6=1;
                while(yy6){
                	printf("\nDesea continuar? (2 si, 1 no): \t");
	                fflush(stdin);
	                gets(Cad24);
		            continuar=digitosC(Cad24);
	                
                	if(((continuar==0)||(continuar<0)||(continuar>2))){
                		system("cls");
	                	printf("\nIngresar Correctamente La Opcion (2 si, 1 no)\n\n");
	                	system("PAUSE");
	                	system("cls");
				
					}else{
						yy6=0;
						if(continuar==1){
							continuar=0;
						}
						if(continuar==2){
							continuar=1;
						}
					}
				}
				
			}
		}
		fclose(fpag);
	}
	else{
		system("cls");
		printf("\nNo hay pagos cargados hasta el momento.\n");
		system("pause");
	}
	
}

///////////////////////////////////////// gastosConSaldoIncompleto ///////////////////////////////////////////////////////////////////////////////////////

void gastosConSaldoIncompleto() {
	
    FILE *fpag, *fgas;
	double total_pagado, pendiente;
	int existe = 0;
	
	if((fpag = fopen("pagos.dat","rb"))!=NULL){
		if((fgas = fopen("gastos.dat","rb"))!=NULL){
			system("cls");	
			printf("\n////////GASTOS CON SALDO INCOMPLETO///////////\n");
			rewind(fgas);
			fread(&gasto,sizeof(Gasto),1,fgas);
			while(!feof(fgas)){
				total_pagado = 0;
				rewind(fpag);
				fread(&pago,sizeof(Pago),1,fpag);
				while(!feof(fpag)){
					if(gasto.codGasto == pago.codGasto){
						total_pagado += pago.importe;
					}
					fread(&pago,sizeof(Pago),1,fpag);
				}
				if(total_pagado < gasto.monto){
					pendiente = gasto.monto - total_pagado;
					printf("\n%s\n",gasto.desc);
					printf("Total: $%.2lf\n",gasto.monto);
					printf("Pagado: $%.2lf\n",total_pagado);
					printf("Pendiente: $%.2lf\n",pendiente);
					printf("Categoria: %s",gasto.categoria.nombre);
					existe = 1;
					printf("\n");
				}
				fread(&gasto,sizeof(Gasto),1,fgas);
			}
			
			if(!existe){
				system("cls");
				printf("\nNo se encuentran gastos con saldo incompleto.\n");
			}
								
			fclose(fgas);
		}
		else{
			system("cls");
			printf("\nNo se han cargado gastos hasta el momento.\n");
		}
		
		fclose(fpag);
	}
	else{
		system("cls");
		printf("\nNo se han cargado pagos hasta el momento.\n");
		
	}
	
	printf("\n");
	system("pause");
	
}

///////////////////////////////////////// top3CategoriasMasCostosas ///////////////////////////////////////////////////////////////////////////////////////

void top3CategoriasMasCostosas(){
	
	// Archivos y Estructuras (Se asume 'Gasto gasto' es global por el uso en el codigo original)
	FILE *fcat=NULL,*fgas=NULL;
	Categoria cat;
	
	// Variables de Tiempo
	time_t t;
	struct tm *f=NULL;
	int mes_actual,anio_actual,mes_anterior,anio_anterior;
	
	// Variables de Archivo y Contadores
	long tam; // Almacena el tamano del archivo de categorias
	int cantCategorias,i,top,existe=0,indice=0,pos_max=-1;
	// i: contador, top: rank, existe: bandera, Cantidad total de categorias,Indice para llenar los arrays,Posicion del maximo encontrado
	
	// Variables de Calculo
	double max; // Almacena el monto maximo encontrado
	
	// 1. Obtener la fecha actual y calcular el mes/anio anterior
	t=time(NULL);
	f=localtime(&t);
	mes_actual=f->tm_mon+1;
	anio_actual=f->tm_year+1900;
	
	mes_anterior=mes_actual-1;
	anio_anterior=anio_actual;
	
	// Ajusta el cambio de anio si el mes anterior es Diciembre
	if(mes_anterior==0){
		mes_anterior=12;
		anio_anterior=anio_actual-1;
	}
	
	system("cls");
	printf("\n=== Top 3 Categorias Mas Costosas - %d/%d ===\n",mes_anterior,anio_anterior);
	
	// 2. Abrir archivo de Categorias
	if((fcat=fopen("categorias.dat","rb"))!=NULL){
		
		// 3. Abrir archivo de Gastos (anidado)
		if((fgas=fopen("gastos.dat","rb"))!=NULL){
			
			// Contar cantidad de categorias para dimensionar los arrays paralelos (VLA)
			fseek(fcat,0,SEEK_END);
			tam=ftell(fcat);
			cantCategorias=tam/sizeof(Categoria);
			rewind(fcat); // Vuelve al inicio del archivo
			
			// Declaracion de VLA's (Arrays de longitud variable).
			double totales[cantCategorias];
			unsigned long long codigos[cantCategorias];
			char nombres[cantCategorias][50];
			
			// Inicializar arrays con datos de categorias
			fread(&cat,sizeof(Categoria),1,fcat);
			
			// Bucle para leer todas las categorias y preparar los arrays
			while(!feof(fcat)){
				
				codigos[indice]=cat.codigo;
				strcpy(nombres[indice],cat.nombre);
				totales[indice]=0; // Inicializa el total de gastos a 0 para esta categoria
				indice++;
				
				fread(&cat,sizeof(Categoria),1,fcat);
			}
			
			// 4. Procesar gastos del mes anterior
			fread(&gasto,sizeof(Gasto),1,fgas); // Lectura anticipada
			
			// Bucle para acumular los gastos en los totales por categoria
			while(!feof(fgas)){
				
				// Filtra por gastos del mes y anio anterior
				if((gasto.fechaGasto.mes==mes_anterior)&&(gasto.fechaGasto.anio==anio_anterior)){
					
					// Busca la categoria y acumula el monto
					for(i=0;i<cantCategorias;i++){
						
						if(gasto.categoria.codigo==*(codigos+i)){
							
							*(totales+i)+=gasto.monto;
							
						}
					}
				}
				
				fread(&gasto,sizeof(Gasto),1,fgas); // Siguiente lectura
			}
			
			// 5. Buscar y mostrar el TOP 3
			for(top=1;top<=3;top++){
				
				max=-1;
				pos_max=-1;
				
				// Busca el maximo total no "eliminado" (-1)
				for(i=0;i<cantCategorias;i++){
					
					if(*(totales+i)>max){
						
						max=*(totales+i);
						pos_max=i;
						
					}
				}
				
				// Si se encontro un maximo valido (monto > 0)
				if((pos_max!=-1)&&(max>0)){
					
					printf("%d. %s: $%.2lf\n",top,nombres[pos_max],max);
					existe=1; // Marca que se encontro al menos una categoria en el TOP
					totales[pos_max]=-1; // "Elimina" la categoria para la siguiente busqueda
				}
				
			}
			
			// 6. Mensaje si no hay gastos registrados
			if(!existe){
				printf("\nNinguna Categoria Registrada Registra Gastos Hasta El Momento En El Mes Anterior.\n");
				printf("\n");
			}
			
			printf("\n===============================================");
			printf("\n");
			system("pause");
			
			fclose(fgas); // Cierra el archivo de gastos
		}
		else{
			// Error: No se pudo abrir gastos.dat
			system("cls");
			printf("\nNo Se Cargaron Gastos Hasta El Momento.\n");
			system("pause");
		}
		
		fclose(fcat); // Cierra el archivo de categorias
	}
	else{
		// Error: No se pudo abrir categorias.dat
		system("cls");
		printf("\nNo Se Cargaron Categorias Hasta El Momento.\n");
		system("pause");
	}
	
}

///////////////////////////////////////// proyeccionMensual ///////////////////////////////////////////////////////////////////////////////////////

void proyeccionMensual(){
	
	// Archivos y Estructuras (Se asume 'Gasto gasto' es global o conocido)
	FILE *fgas=NULL;
	
	// Variables de Tiempo
	time_t t;
	struct tm *f=NULL;
	int mes_actual,anio_actual;
	
	// Variables de Arreglos y Contadores
	int meses[3],anios[3],meses_con_datos=0,i; // Cuenta cuantos meses tienen gastos > 0 // Almacena los 3 meses y anios anteriores
	
	// Variables de Calculo
	double totales[3]={0,0,0},suma=0,proyeccion=0; // Suma total de los gastos de los meses analizados, Suma de gastos para cada uno de los 3 meses
	
	 // Resultado final de la proyeccion (promedio)
	
	// 1. Obtener la fecha actual
	t=time(NULL);
	f=localtime(&t);
	mes_actual=f->tm_mon+1;
	anio_actual=f->tm_year+1900;
	
	// 2. Calcular los 3 meses anteriores (SIN incluir el actual)
	for(i=0;i<3;i++){
		// Calcula el mes y anio correspondiente
		*(meses+i)=mes_actual-(i+1); 
		*(anios+i)=anio_actual;
		
		// Manejo del cambio de anio (si pasa de Enero a Diciembre)
		if(*(meses+i)<=0){
			*(meses+i)+=12;
			*(anios+i)-=1;
		}
	}
	
	system("cls");
	printf("\n=== Proyeccion Mensual - %d/%d ===\n",mes_actual,anio_actual);
	printf("Basado En: %d/%d, %d/%d, %d/%d\n\n",meses[2],anios[2],meses[1],anios[1],meses[0],anios[0]);
	
	// 3. Abrir el archivo de gastos y procesar
	if((fgas=fopen("gastos.dat","rb"))!=NULL){
		
		fread(&gasto,sizeof(Gasto),1,fgas); // Lectura anticipada (patron feof)
		
		// Recorre todos los gastos del archivo
		while(!feof(fgas)){
			
			// Compara el gasto con los 3 meses anteriores
			for(i=0;i<3;i++){
				// Si coincide la fecha, acumula el monto
				if(gasto.fechaGasto.mes==*(meses+i)&&gasto.fechaGasto.anio==*(anios+i)){
					*(totales+i)+=gasto.monto;
				}
			}
			
			fread(&gasto,sizeof(Gasto),1,fgas); // Siguiente lectura
		}
		
		fclose(fgas); // Cierra el archivo de gastos
		
		// 4. Muestra los totales de los meses y calcula la suma para la proyeccion
		// Itera de i=2 a 0 para mostrar los meses en orden cronologico
		for(i=2;i>=0;i--){
			
			printf("Gasto Total %d/%d: $%.2lf\n",*(meses+i),*(anios+i),*(totales+i));
			
			// Solo suma los meses que tuvieron un gasto > 0
			if(*(totales+i)>0){
				suma+=*(totales+i);
				meses_con_datos++; // Cuenta los meses que seran utilizados para el promedio
			}
			
		}
		
		// 5. Calcula la proyeccion (promedio)
		if(meses_con_datos>0){
			proyeccion=suma/meses_con_datos;
		}
		
		printf("\nProyeccion Total: $%.2lf\n",proyeccion);
	}
	else{
		
		// Bloque de error si el archivo no existe
		system("cls");
		printf("\nNo Se Cargaron Gastos Hasta El Momento.\n");
	}
	
	// 6. Pausa final
	printf("\n");
	system("pause");
	
}

///////////////////////////////////////// resumenGeneral ///////////////////////////////////////////////////////////////////////////////////////

void resumenGeneral(){
	
	// Variables de Archivo y Estructuras
	FILE *fcat=NULL,*fgas=NULL,*fres=NULL,*fcont=NULL;
	Categoria cat;
	Gasto g;
	
	// Variables de Cadenas Auxiliares
	char nombreArchivo[50],tipo[10]; // 'estado' fue eliminado por ser innecesario
	
	// Variables de Indices y Contadores
	int numArchivo=1,i,indiceCat=0,cantGastosCat=0,cantCategorias;
	long tam; // Tamano del archivo de categorias
	
	// numArchivo: Contador de resumenes, i: Contador de bucles,Indice actual para llenar los arrays de estadisticas
	// Contador de gastos por categoria en el bucle interno
	
	// Variables de Acumulacion y Calculo,Cantidad total de categorias
	
	double totalGeneral=0,totalCat=0,promedio,porcentaje;
	
	//Acumulador de gastos por categoria en el bucle interno,Acumulador del total de gastos de todas las categorias,Variables auxiliares para calculo de estadisticas
	
	// 1. Manejo y lectura del archivo de contador (contador.txt)
	if((fcont=fopen("contador.txt","r"))!=NULL){
		
		fscanf(fcont,"%d",&numArchivo);
		fclose(fcont);
		
	}
	else{
		
		// Si no existe, intenta crearlo e inicializarlo
		if((fcont=fopen("contador.txt","w"))!=NULL){
		
			fprintf(fcont,"%d",numArchivo);
			fclose(fcont);
		
		}
		else{
			printf("\nError Al Abrir El Archivo Contador.\n"); // Mensaje sin acentos
		}	
	
	}
	
	// 2. Intenta abrir el archivo de categorias
	if((fcat=fopen("categorias.dat","rb"))!=NULL){
		
		// 3. Intenta abrir el archivo de gastos
		if((fgas=fopen("gastos.dat","rb"))!=NULL){
			
			// Genera el nombre del archivo de resumen (ej: resumen_general1.txt)
			sprintf(nombreArchivo,"resumen_general%d.txt",numArchivo);
			
			
			// 4. Intenta abrir el archivo de resumen para escritura
			if((fres=fopen(nombreArchivo,"w"))!=NULL){
				
				// Determina la cantidad de categorias para dimensionar los arrays (VLA)
				fseek(fcat,0,SEEK_END);
				tam=ftell(fcat);
				cantCategorias=tam/sizeof(Categoria);
				rewind(fcat);
				
				// Declaracion de VLA's para almacenar estadisticas
				double totalesPorCat[cantCategorias];
				int cantGastosPorCat[cantCategorias];
				char nombresCat[cantCategorias][50];
				
				// Inicializa los arrays de estadisticas
				for(i=0;i<cantCategorias;i++){
					
					*(totalesPorCat+i)=0;
					*(cantGastosPorCat+i)=0;
					nombresCat[i][0]='\0';
					
				}
				
				
				// Escribe el encabezado del listado detallado
				fprintf(fres,"===== RESUMEN GENERAL DE GASTOS =====\n\n");
				fprintf(fres,"Fecha        Categoria                 Tipo          Monto\n");
				fprintf(fres,"----------------------------------------------------------\n");
				
				// 5. Bucle principal: Procesa cada categoria
				fread(&cat,sizeof(Categoria),1,fcat);
				
				while(!feof(fcat)){
					
					strcpy(nombresCat[indiceCat],cat.nombre);
					totalCat=0;
					cantGastosCat=0;
					
					rewind(fgas); // Vuelve al inicio del archivo de gastos para el bucle interno
					fread(&g,sizeof(Gasto),1,fgas);
					
					// 6. Bucle interno: Recorre los gastos buscando coincidencias con la categoria actual
					while(!feof(fgas)){
						
						if(g.categoria.codigo==cat.codigo){
							
							// Traduce el codigo de tipo de gasto a una cadena
							switch(g.tipoGasto){
								case 1:
									strcpy(tipo,"Fijo");
									break;
								case 2:
									// El codigo original tiene 2=Ocasional y 3=Temporal. Se mantiene la logica.
									strcpy(tipo,"Ocasional");
									break;	
								case 3:
									strcpy(tipo,"Temporal");
									break;
								case 4:
									strcpy(tipo,"Anual");
									break;	
							}
					
							// Escribe el detalle del gasto en el archivo de resumen
							fprintf(fres,"%02d/%02d/%d   %-20s   %-12s   $%9.2f\n",g.fechaGasto.dia,g.fechaGasto.mes,g.fechaGasto.anio,g.categoria.nombre,tipo,g.monto);

							totalCat+=g.monto;
							cantGastosCat++;
							
						}
						
						fread(&g,sizeof(Gasto),1,fgas);
					}
					
					// Acumula los totales y contadores de la categoria actual
					totalesPorCat[indiceCat]=totalCat;
					cantGastosPorCat[indiceCat]=cantGastosCat;
					totalGeneral+=totalCat;
					indiceCat++;
					
					fread(&cat,sizeof(Categoria),1,fcat);
					
				}
				
				// 7. Escribe la seccion de estadisticas generales
				fprintf(fres,"\n\n===== ESTADISTICAS GENERALES =====\n"); // Sin acentos
				fprintf(fres,"Categoria               Total($)   Promedio($)   %% Del Total\n");
				fprintf(fres,"----------------------------------------------------------\n");
				
				// 8. Bucle para escribir las estadisticas por categoria
				for(i=0;i<indiceCat;i++){
					
					// Solo calcula si la categoria tuvo al menos 1 gasto
					if(cantGastosPorCat[i]>0){
						
						promedio=totalesPorCat[i]/cantGastosPorCat[i];
						porcentaje=(totalesPorCat[i]/totalGeneral)*100;
						fprintf(fres,"%-23s   $%9.2f   $%9.2f   %6.2f%%\n",nombresCat[i],totalesPorCat[i],promedio,porcentaje);
					}
					
				}
				
				fprintf(fres,"\nTOTAL GENERAL: $%.2f\n",totalGeneral);
				
				fclose(fres); // Cierra el archivo de resumen
				
				// 9. Actualiza el numero de contador
				if((fcont=fopen("contador.txt","w"))!=NULL){
					
					fprintf(fcont,"%d",numArchivo+1);
					fclose(fcont);
				}
				else{
					printf("\nError Al Abrir El Archivo Contador Para Actualizar.\n");
				}
				
				// 10. Muestra mensaje de exito al usuario
				system("cls");
				printf("---------\n10. Resumen General\n---------");
				printf("\nResumen Generado Con Exito!\n");
				system("pause");
				
			}
			else{
				printf("\nError Al Abrir El Archivo De Resumen.\n");
			}
			
			fclose(fgas); // Cierra el archivo de gastos
		}
		else{
			// Error: No se pudo abrir gastos.dat
			system("cls");
			printf("\nNo Se Cargaron Gastos Hasta El Momento.\n");
			system("pause");
		}
		
		fclose(fcat); // Cierra el archivo de categorias
	}
	else{
		// Error: No se pudo abrir categorias.dat
		system("cls");
		printf("\nNo Se Cargaron Categorias Hasta El Momento.\n");
		system("pause");
	}
	
}

///////////////////////////////////////// listaCategorias ///////////////////////////////////////////////////////////////////////////////////////

void listaCategorias(){
	
	
	FILE*arch=NULL;
	unsigned long long idaux=0; 
	int cc1=0; 
	
	
	if((arch=fopen("gastos.dat","r+b"))==NULL){
		
		
		printf("\nError al abrir el archivo");
		system("PAUSE");
		
	}
	else{
		
		rewind(arch); 
		
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

///////////////////////////////////////// listaGastos ///////////////////////////////////////////////////////////////////////////////////////

void listaGastos(){
	
	
	FILE*arch=NULL;
	unsigned long long idaux=0;
	int cc1=0; 
	char CaTip[10],CaEst[25]; 
	
	
	if((arch=fopen("gastos.dat","r+b"))==NULL){
		
		
		printf("\nError al abrir el archivo");
		system("PAUSE");
		
	}else{
		
		rewind(arch); 
		
		printf("\n\nSeleccione Un Gasto Con El Numero De Codigo De Gasto\n------------------------------------------------------------------------------------------------------------------------");
		
		fread(&gasto,sizeof(Gasto),1,arch); 
		
	
		while(!feof(arch)){
			
			
			if(gasto.estadoCuota!=3){
				
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
				
			
				printf("\n%d.\tID De Gasto Numero: %llu    Descripcion De Gasto: %s    Tipo De Gasto: %s    Monto Restante $%.3lf\n",cc1,gasto.codGasto,gasto.desc,CaTip,gasto.deudaTotal);
				
			
				printf("\n\tID De Categoria Numero: %llu    Pertence A La Categoria: %s    Gasto Generado Por %s, DNI: %ld\n",gasto.categoria.codigo,gasto.categoria.nombre,gasto.persona.nombre,gasto.persona.dni);
				
			
				printf("\n\tCon %d Cuotas En Total    La Cuota Actual %s Es La Numero %d Con Un Valor De $%.3lf\n",gasto.cuotasTotales,CaEst,gasto.cuotaActual,gasto.restanteCuota);
				printf("\n------------------------------------------------------------------------------------------------------------------------\n");
			}
			
			fread(&gasto,sizeof(Gasto),1,arch); 
		}
		
		fclose(arch); 
		printf("\nIngrese Una Opcion: ");				
	}
}

///////////////////////////////////////// registroCategoria ///////////////////////////////////////////////////////////////////////////////////////

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
			printf("\nID De Gasto: %llu\n",IX);
			printf("\nTipo De Gasto: %s\n",Tip);
			
		}else{
			
			x=0;
		}
	}
}

///////////////////////////////////////// digitosC ///////////////////////////////////////////////////////////////////////////////////////

int digitosC(char*r){
	
	
	int ret1=0,i,con=0;
	

	for(i=0;i[r]!='\0';i++){
		
		
		if(r[i]<'0'||r[i]>'9'){
			con++; 
		}
	}
	
	
	if(con==0){
		ret1=atoi(r); 
	}
	
	fflush(stdin);
	
	
	return ret1;
}

///////////////////////////////////////// gastosExsistentes ///////////////////////////////////////////////////////////////////////////////////////

int gastosExsistentes(){

	int ret=0; 
	FILE *fgE=NULL;
	

	if((fgE=fopen("gastos.dat","rb"))==NULL){
		
		
		printf("\nNo Se Pudo Abrir El Archivo Gastos Y No Existen Gastos\n\n");
		system("PAUSE");
		
	}else{
		
		Gasto gasto; 
		fread(&gasto,sizeof(Gasto),1,fgE); 
		
		
		while((!feof(fgE))&&(!ret)){
			
			
			if(gasto.estadoCuota!=3){
				ret=1; 
			}
			
			fread(&gasto,sizeof(Gasto),1,fgE); 
		}
		
		fclose(fgE); 
	}

	
	return ret;
}

///////////////////////////////////////// fin ///////////////////////////////////////////////////////////////////////////////////////
