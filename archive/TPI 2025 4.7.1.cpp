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

// PROTOTIPOS -----------------
void filtroPorMes(int);
double digitos(char*);
long long digitosDNI(char*);
void listaCategorias();
void listaGastos();
int digitosC(char*r);

///////////////////////////////////////// main //////////////////////////////////////////////////////////////////////////////////////////

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
                ver_arch_gastos();
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
	
    FILE *f2, *fcat;
    Categoria categoria;
    int s=1, c, aux_anio, aux_mes,aux_dia,cnt,opc,i,ac,ca,comp_corr,auxfecha, encontrado;
    unsigned long long id,idC,IDaux;
    char Cad2[50000],montox[10],Cad4[50000],Cad8[9],Cad9[50000],Cad3[50];
    
    while(s){
    	
    	cnt=1;
    	
        if((f2 = fopen("gastos.dat", "ab")) == NULL){
        	
            printf("\nError Al Abrir El Archivo");
            system("PAUSE");
            
        }
		else{
			
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
            			
					}
					else{
						
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
	            			
						}
						else{
							
							if((IDaux<0)||(comp_corr==0)){
								
								system("cls");
								printf("\nIngrese Un ID Valido, Entero Superior A 0, Y No Se Puede Ingresar Caracteres\n");
								system("PAUSE");
								system("cls");
								
							}
							else{
								
								//printf("\n\nEntro a Lista");
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
						printf("\nEl Monto es: $%.3lf\n",gasto.monto);
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
						printf("\nEl Monto es: $%.3lf\n",gasto.monto);
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
				gasto.restanteCuota=(gasto.monto/gasto.cuotasTotales);
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
	
	char Cad1[1000],montox[10],Cad4[4],Cad8[9];
	unsigned long long id;
	FILE *f1, *fper;
	Persona persona;
	int s,c,aux_anio,aux_mes,aux_dia,comp_corr1=0, encontrado;
	
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
			// Resto del cÃƒÆ’Ã‚Â³digo para fecha, cuotas, persona...
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
            		long long num = atoll(Cad8);
            		
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
	
	FILE *f1,*f2;
    int s=1,i, c, aux_anio, aux_mes, aux_dia,opc,ac,ca,corr,cnt, pagado;
    unsigned long long IDaux;
    char montox[10],Cad3[50],Cad4[50000],CaEst[25];
    double comp_corr, Cuota;
    Gasto gastoa;
    
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
					printf("\n\nCon %d Cuotas En Total La Cuota Actual %s Es La Numero %d\nCon Un Valor De $%.3lf Siendo El Total Monto Restante $%.3lf",gastoa.cuotasTotales,CaEst,gastoa.cuotaActual,gastoa.restanteCuota,gastoa.monto);
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
						printf("Con %d Cuotas En Total La Cuota Actual %s Es La Numero %d\nCon Un Valor De $%.3lf Siendo El Total Monto Restante $%.3lf\n",gastoa.cuotasTotales,CaEst,gastoa.cuotaActual,gastoa.restanteCuota,gastoa.monto);
				}
				
			}	
			
			system("cls");
			printf("------------------\n3.REGISTRAR PAGO\n------------------\n");
			printf("\nID De Gasto Seleccionado: %lld\n\n",IDaux);
			printf("Tipo De Medio De Pago Seleccionado: %s\n",Cad3);
			printf("\nCon %d Cuotas En Total La Cuota Actual %s Es La Numero %d\nCon Un Valor De $%.3lf Siendo El Total Monto Restante $%.3lf\n",gastoa.cuotasTotales,CaEst,gastoa.cuotaActual,gastoa.restanteCuota,gastoa.monto);
			
			c=1;
			
			while(c){
				
				printf("\nIngrese El Monto A Abonar: $");
				
				fflush(stdin);
				gets(montox);
				
				comp_corr=digitos(montox);
				
				
				if((comp_corr==0)||(comp_corr>gasto.restanteCuota)){ //aca ver
				 
					system("cls");
					printf("\nIngrese Un Monto Valido Mayor A 0 Y Que Sean Unicamente Numeros, Maximo De Tres Decimales, NO Puede Superar El Valor De La Cuota\n\n");
					system("PAUSE");
					system("cls");		
					printf("------------------\n3.REGISTRAR PAGO\n------------------\n");
					printf("\nID De Gasto Seleccionado: %lld\n\n",IDaux);
					printf("Tipo De Medio De Pago Seleccionado: %s\n\n",Cad3);
					printf("Con %d Cuotas En Total La Cuota Actual %s Es La Numero %d\nCon Un Valor De $%.3lf Siendo El Total Monto Restante $%.3lf\n",gastoa.cuotasTotales,CaEst,gastoa.cuotaActual,gastoa.restanteCuota,gastoa.monto);
					
				}
				else{
					
					//gasto.restanteCuota=Cuota;
					pago.importe=atof(montox);
					c=0;
					//printf("pago.importe vale: %f\n\n",pago.importe);
					//system("PAUSE");
					
					gasto.restanteCuota=(gasto.restanteCuota-pago.importe);
					gasto.monto=(gasto.monto-pago.importe);
					
					//gasto.restanteCuota -= pago.importe;
					
					//printf("gasto.restanteCuota: %f\n\n",gasto.restanteCuota);
					//system("PAUSE");
					
					if (gasto.restanteCuota > EPSILON) {
						
						gasto.estadoCuota = 2;
						
						
						//printf("pago.importe vale dentro del if EPSILON: %f\n\n",pago.importe);
						//system("PAUSE");
						
						//printf("gasto.restanteCuota dentro del if EPSILON: %f\n\n",gasto.restanteCuota);
						//system("PAUSE");
							
						
						
					}
					else {
						
						gasto.restanteCuota = 0.0;
						//printf("pago.importe vale dentro del else EPSILON: %f\n\n",pago.importe);
						//system("PAUSE");
						
						//printf("gasto.restanteCuota dentro del else EPSILON: %f\n\n",gasto.restanteCuota);
						//system("PAUSE");
						
						if (gasto.cuotaActual == gasto.cuotasTotales) {
							
							gasto.estadoCuota = 3; // Pagado (Finalizado)
							
							//printf("pago.importe vale dentro del Pagado: %f\n\n",pago.importe);
							//system("PAUSE");
							
							//printf("gasto.restanteCuota dentro del Pagado: %f\n\n",gasto.restanteCuota);
							//system("PAUSE");
														
						}
						else {
							
							//printf("pago.importe vale dentro del estado y resto antes: %f\n\n",pago.importe);
							//system("PAUSE");
							
							//printf("gasto.restanteCuota dentro del estado y resto antes: %f\n\n",gasto.restanteCuota);
							//system("PAUSE");
							
							
							
							gasto.estadoCuota = 1;
							
							Cuota=(gasto.cuotasTotales-gasto.cuotaActual);
							gasto.restanteCuota=(gasto.monto/Cuota);
							
							
							//printf("pago.importe vale dentro del estado y resto despues: %f\n\n",pago.importe);
							//system("PAUSE");
							
							//printf("gasto.restanteCuota dentro del estado y resto despues: %f\n\n",gasto.restanteCuota);
							//system("PAUSE");
							
							
						}
						
						if(gasto.cuotaActual<gasto.cuotasTotales){
							
							gasto.cuotaActual++;
							
						}
						
						
						//printf("pago.importe vale suma cuota act: %f\n\n",pago.importe);
						//system("PAUSE");
						
						//printf("gasto.restanteCuota suma cuota act: %f\n\n",gasto.restanteCuota);
						//system("PAUSE");
						
						//printf("gasto.cuotaActual suma cuota act: %f\n\n",gasto.cuotaActual);
						//system("PAUSE");
						
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
					printf("Con %d Cuotas En Total La Cuota Actual %s Es La Numero %d\nCon Un Valor De $%.3lf Siendo El Total Monto Restante $%.3lf\n",gastoa.cuotasTotales,CaEst,gastoa.cuotaActual,gastoa.restanteCuota,gastoa.monto);
					printf("\nTipo De Medio De Pago Seleccionado: %s\n\n",Cad3);
					printf("Monto Abonado: %.3lf\n",pago.importe);
					
				}
			}
  		          
			pago.fechaPago.anio = aux_anio;
			pago.fechaPago.mes = aux_mes;
			pago.fechaPago.dia = aux_dia;
			
			
			pago.codGasto=IDaux;
			
			printf("----------------------------------------------------------\n");
			
			
			
			/*printf("\nCodigo: %llu", gasto.codGasto);
            printf("\nTipo: %d", gasto.tipoGasto);
            printf("\nDescripcion: %s", gasto.desc);
            printf("\nEl ID De La Categoria es: %llu",gasto.categoria.codigo);
            printf("\nCategoria: %s", gasto.categoria.nombre);
            printf("\nMonto: %.2lf", gasto.monto);
            printf("\nFecha: %d/%d/%d", gasto.fechaGasto.dia, gasto.fechaGasto.mes, gasto.fechaGasto.anio);
            printf("\nCuotas: %d/%d", gasto.cuotaActual, gasto.cuotasTotales);
            printf("\nPersona: %s (DNI: %lld)", gasto.persona.nombre, gasto.persona.dni);
            printf("\nRestante Cuota: %f",gasto.restanteCuota);
            printf("\nMedio pago: %s",Cad3);//ver su queda
            printf("\nEstado: %d\n", gasto.estadoCuota);
			system("PAUSE");*/
			
			pago.medioPago=i;
			
			
			fseek(f1,sizeof(Gasto)*(-1),SEEK_CUR);
			fwrite(&gasto,sizeof(Gasto),1,f1);
			
			guardarPago(pago);
			
			
			c=1;
			
			while(c){
				
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
				
			fclose(f1);	
			
		}
		else{
			
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
            	system("cls");
                printf("\nIngrese un numero valido del 1-4 de tipo entero\n\n");
				system("pause");
        }
        
        if (s) {
        	
            if ((opc >= 1) && (opc <= 2)) {
            	
                system("cls");
                printf("\nDesea realizar otro listado?\n\n1. Si\n0. No, finalizar : \t ");
                fflush(stdin);
                scanf("%d", &opc);
                
                while ((opc != 1) && (opc != 0)) {
                	
                    system("cls");
                    printf("\nOpcion invalida. Intentelo de nuevo. Ingrese un numero valido del 1-0 de tipo entero.\n");
                    printf("\nDesea realizar otro listado?\n\n1. Si\n0. No, finalizar : \t ");
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
    	
    	system("cls"); //ver
        printf("\nEscoja la consulta/reporte a realizar:\n\n1. Gastos por Categoria\n2. Gastos Por Mes y Anio\n3. Ingresos Por Persona\n4. Saldo Mensual\n5. Gastos Pendientes\n6. Pagos Por Medio de Pago\n7. Gastos con Saldo Incompleto\n8. Top 3 Categorias Mas Costosas\n9. Proyeccion Mensual\n10. Resumen General\n11. Volver al Menu Principal\n\nElija una opcion: ");
        fflush(stdin);
        scanf("%d", &opc);
        
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
            	
                system("cls");
                printf("\nDesea realizar otra consulta/reporte?\n\n1. Si\n0. No, finalizar : \t ");
                fflush(stdin);
                scanf("%d", &opc);
                
                while ((opc != 1) && (opc != 0)) {
                	
                    system("cls");
                    printf("\nOpcion invalida. Intentelo de nuevo. Ingrese un numero valido del 1-0 de tipo entero.\n");
                    printf("\nDesea realizar otra consulta/reporte?\n\n1. Si\n0. No, finalizar : \t ");
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
		
	}
	else{
		
		fwrite(&gasto,sizeof(Gasto),1,f4);
		fclose(f4);
		
	}
		
}

///////////////////////////////////////// comprobacion_fecha ///////////////////////////////////////////////////////////////////////////////////////

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

        } 
		else{
			
            verif = 1;
            
        }
        
    } 
	else{
		
        verif = 1;
        
    }
    
	fflush(stdin);
    return verif; /* 0 = valido, 1 = invalido */
	
}

///////////////////////////////////////// ver_arch_gastos ///////////////////////////////////////////////////////////////////////////////////////

void ver_arch_gastos() {
	
    FILE *f2;
	char Charx[15];
    
    if ((f2 = fopen("gastos.dat", "rb")) == NULL) {
    	
        printf("\nError Al Abrir El Archivo");
        system("PAUSE");
        
    } 
	else {
		
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

///////////////////////////////////////// buscar_idGasto ///////////////////////////////////////////////////////////////////////////////////////

unsigned long long buscar_idGasto(){
	
    FILE *arch;
    unsigned long long ret=1 ,max_id = 0;
    Gasto gasto_temp;
    
    if((arch = fopen("gastos.dat", "rb")) != NULL){
    	
    	rewind(arch);
        // Buscar el ID mÃƒÆ’Ã‚Â¡ximo en todos los registros
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
        
    }
	else{
		
    	printf("\n\nError, No Se Pudo Abrir El Archivo\n\n");
    	system("PAUSE");
    	
	}
    // Si el archivo no existe o estÃƒÆ’Ã‚Â¡ vacÃƒÆ’Ã‚Â­o, empezar desde 1
    return ret;
}

///////////////////////////////////////// buscar_idCategoria ///////////////////////////////////////////////////////////////////////////////////////

unsigned long long buscar_idCategoria(){
	
	FILE *arch1;
    unsigned long long ret1=1 ,max_id1 = 0;
    Gasto gasto_temp1;
    
    if((arch1 = fopen("gastos.dat", "rb")) != NULL){
    	
    	rewind(arch1);
        // Buscar el ID mÃƒÆ’Ã‚Â¡ximo en todos los registros
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
        
    }
	else{
		
    	printf("\n\nError, No Se Pudo Abrir El Archivo\n\n");
    	system("PAUSE");
    	
	}
    // Si el archivo no existe o estÃƒÆ’Ã‚Â¡ vacÃƒÆ’Ã‚Â­o, empezar desde 1
    return ret1;
}

///////////////////////////////////////// buscar_idIngreso ///////////////////////////////////////////////////////////////////////////////////////

unsigned long long buscar_idIngreso(){
	
	FILE *f6;
    unsigned long long ret2=1 ,max_id2 = 0;
    Ingreso ingreso_temp2;
    
    if((f6 = fopen("ingresos.dat", "rb")) != NULL){
    	
    	rewind(f6);
        // Buscar el ID mÃƒÆ’Ã‚Â¡ximo en todos los registros
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
        
    }
	else{
		
    	printf("\n\nError, No Se Pudo Abrir El Archivo\n\n");
    	system("PAUSE");
    	
	}
    // Si el archivo no existe o estÃƒÆ’Ã‚Â¡ vacÃƒÆ’Ã‚Â­o, empezar desde 1
    return ret2;
}

///////////////////////////////////////// guardarIngreso ///////////////////////////////////////////////////////////////////////////////////////

void guardarIngreso(Ingreso ingreso){
	
	FILE *f5;
	if((f5=fopen("ingresos.dat","ab"))==NULL){
		
		printf("\nError al abrir el archivo");
		system("PAUSE");
		
	}
	else{
		
		fwrite(&ingreso,sizeof(ingreso),1,f5);
		fclose(f5);
		
	}
	
}

///////////////////////////////////////// guardarPago ///////////////////////////////////////////////////////////////////////////////////////

void guardarPago(Pago pago){
	
	FILE *fpp;
	if((fpp=fopen("pagos.dat","ab"))==NULL){
		
		printf("\nError al abrir el archivo");
		system("PAUSE");
		
	}
	else{
		
		fwrite(&pago,sizeof(Pago),1,fpp);
		fclose(fpp);
		
	}
}

///////////////////////////////////////// ver_arch_ingresos ///////////////////////////////////////////////////////////////////////////////////////

void ver_arch_ingresos() {
	
    FILE *f1;
    
    if ((f1 = fopen("ingresos.dat", "rb")) == NULL) {
    	
        printf("\nError Al Abrir El Archivo");
        system("PAUSE");
        
    } 
	else {
		
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

///////////////////////////////////////// ver_arch_pagos ///////////////////////////////////////////////////////////////////////////////////////

void ver_arch_pagos() {
	
    FILE *f3;
    char Cadx[30];
    
    if ((f3 = fopen("pagos.dat", "rb")) == NULL) {
    	
        printf("\nError Al Abrir El Archivo");
        system("PAUSE");
        
    } 
	else {
		
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

///////////////////////////////////////// digitos ///////////////////////////////////////////////////////////////////////////////////////

double digitos(char *r) {
	
    double ret1 = 0;
    int i, ccc = 0, punto_encontrado = 0;
    
    for (i = 0; r[i] != '\0'; i++) {
    	
        if (r[i] == '.') {
        	
            ccc++;
            punto_encontrado = i; // Guardar posiciÃƒÆ’Ã‚Â³n del punto
            
        } else if (r[i] < '0' || r[i] > '9') {
        	
            // Caracter no numÃƒÆ’Ã‚Â©rico ni punto encontrado
            ccc=2;
            
        }
    }
    
    // Verificar mÃƒÆ’Ã‚Â¡ximo un punto y hasta 3 decimales
    if (ccc <= 1) {
    	
        if (punto_encontrado > 0) {
            // Contar dÃƒÆ’Ã‚Â­gitos despuÃƒÆ’Ã‚Â©s del punto
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

///////////////////////////////////////// digitosDNI ///////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////// listarIngresos ///////////////////////////////////////////////////////////////////////////////////////

void listarIngresos(){
	
	FILE *fing;
	Ingreso ingreso;
	
	if((fing = fopen("ingresos.dat","rb"))!=NULL){
		
		printf("\n////////////////LISTADO DE INGRESOS////////////////////\n");
		
		fread(&ingreso,sizeof(Ingreso),1,fing);
		
		while(!feof(fing)){
			printf("\nCodigo: %llu\n", ingreso.codIngreso);
			printf("Concepto: %s\n", ingreso.concepto);
			printf("Monto: %.2lf\n", ingreso.monto);
			printf("Fecha: %d/%d/%d\n", ingreso.fecha.dia, ingreso.fecha.mes, ingreso.fecha.anio);
			printf("Persona que percibio: %s", ingreso.persona.nombre);
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
	
	int opc, s = 1, seguir;
    
    while (s) {
    	system("cls");
        printf("\nEscoja el criterio por el cual filtrar:\n\n1. Filtrar Por Categoria\n2. Filtrar Por Tipo\n3. Filtrar Por Mes\n4. Volver\n\nElija una opcion: ");
        fflush(stdin);
        scanf("%d", &opc);
        
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
            if ((opc >= 1) && (opc <= 3)) {
                system("cls");
                printf("\nDesea realizar otro listado de gastos?\n\n1. Si\n0. No, finalizar : \t ");
                fflush(stdin);
                scanf("%d", &opc);
                
                while ((opc != 1) && (opc != 0)) {
                    system("cls");
                    printf("\nOpcion invalida. Intentelo de nuevo. Ingrese un numero valido del 1-0 de tipo entero.\n");
                    printf("\nDesea realizar otro listado?\n\n1. Si\n0. No, finalizar : \t ");
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

///////////////////////////////////////// filtrarPorTipo ///////////////////////////////////////////////////////////////////////////////////////

void filtrarPorTipo() {
	
    FILE *fgas;
	Gasto gasto;
	int continuar = 1, opc, existe = 0;
	char tipo[10], tipoMayus[10], estado[15];
	
	if((fgas = fopen("gastos.dat","rb"))!=NULL){
		
		while(continuar){
			system("cls");
			printf("\nIngrese El Tipo De Gasto a Filtrar\n\n1. Gastos Fijos\n2. Gastos Ocasionales\n3. Gastos Temporales\n4. Gastos Anuales\n5. Volver\n\nElija Una Opcion: ");
			scanf("%d",&opc);
			
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
				printf("\nDesea continuar? (1 si, 0 no): \t");
				scanf("%d", &continuar);
				while((continuar != 1) && (continuar != 0)){
					system("cls");
					printf("\nError: respuesta invalida. Intentelo de nuevo.\n");
					printf("\nDesea continuar? (1 si, 0 no): \t");
					scanf("%d", &continuar);
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
	
    char nombreCategoria[50], tipo[10], estado[15];
	int encontrado = 0;
	unsigned long long cod;
	int continuar = 1, encontrados;  
	FILE *fcat, *fgas;
	Categoria categoria;
	Gasto gasto;
	
	if((fcat = fopen("categorias.dat","rb"))!=NULL){
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
				}
				else{
					
					printf("\nIngrese el codigo de la categoria a escoger:\t");
					fflush(stdin);
					scanf("%llu",&cod);
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
					printf("\nDesea buscar otra categoria? (1 si, 0 no): \t");
					fflush(stdin);
					scanf("%d", &continuar);
					while((continuar != 0) &&(continuar != 1)){
						system("cls");
						printf("\nError. Respuesta invalida.\n");
						system("pause");
						system("cls");
					    printf("\nDesea buscar otra categoria? (1 si, 0 no): \t");
						fflush(stdin);
						scanf("%d", &continuar);
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
	else{
		system("cls");
		printf("\nNo se han cargado categorias hasta el momento.\n");
		system("pause");
	}
	
}

///////////////////////////////////////// filtrarPorMes ///////////////////////////////////////////////////////////////////////////////////////

void filtrarPorMes() {
	
    FILE *fgas;
	Gasto gasto;
	int continuar = 1, opc, encontrados, mes, anio;
	char tipo[10], estado[15];

	if((fgas = fopen("gastos.dat","rb"))!=NULL){
	
	    while(continuar){
	    	system("cls");
	    	printf("\nEscoja el mes: \t");
					fflush(stdin);
					scanf("%d", &mes);
					while((mes < 1)||(mes > 12)){
						printf("\nMes invalido. Intente de vuelta.\n");
						printf("\nEscoja el mes: \t");
						fflush(stdin);
						scanf("%d", &mes);
					}
					printf("\nEscoja el anio: \t");
					fflush(stdin);
					scanf("%d", &anio);
					while((anio < 1900)||(anio > 9999)){
						printf("\nAnio invalido. Intente de vuelta.\n");
						printf("\nEscoja el anio: \t");
						fflush(stdin);
						scanf("%d", &anio);
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
					
					system("pause");
					system("cls");
					printf("\nDesea continuar? (1 si, 0 no): \t");
					fflush(stdin);
					scanf("%d", &continuar);
					while((continuar != 1)&&(continuar != 0)){
						printf("\nError: opcion invalida.\n");
						printf("\nDesea continuar? (1 si, 0 no): \t");
						fflush(stdin);
						scanf("%d", &continuar);
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
	
    char nombreCategoria[50], tipo[10], estado[15];
	int encontrado = 0;
	unsigned long long cod;
	int continuar = 1, encontrados;  
	FILE *fcat, *fgas;
	Categoria categoria;
	Gasto gasto;
	
	if((fcat = fopen("categorias.dat","rb"))!=NULL){
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
				}
				else{
					
					printf("\nIngrese el codigo de la categoria a escoger:\t");
					fflush(stdin);
					scanf("%llu",&cod);
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
					printf("\nDesea buscar otra categoria? (1 si, 0 no): \t");
					fflush(stdin);
					scanf("%d", &continuar);
					while((continuar != 0) &&(continuar != 1)){
						system("cls");
						printf("\nError. Respuesta invalida.\n");
						system("pause");
						system("cls");
					    printf("\nDesea buscar otra categoria? (1 si, 0 no): \t");
						fflush(stdin);
						scanf("%d", &continuar);
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
	else{
		system("cls");
		printf("\nNo se han cargado categorias hasta el momento.\n");
		system("pause");
	}
	
}

///////////////////////////////////////// gastosPorMesYAnio ///////////////////////////////////////////////////////////////////////////////////////

void gastosPorMesYAnio() {
	
    int mes, anio, encontrados;
	int eleccion;
	int continuar = 1;
	FILE *fgas;
	Gasto gasto;
	char tipo[10], estado[15];
	
	if((fgas = fopen("gastos.dat","rb"))!=NULL){
		
		while(continuar){
			system("cls");
            printf("---------\n2. GASTOS POR MES Y ANIO\n---------");
			printf("\nVa a elegir mes o anio? (1 mes, 2 anio, 3 volver): \t");
			fflush(stdin);
			scanf("%d", &eleccion);
			while((eleccion != 1)&&(eleccion != 2)&&(eleccion != 3)){
				system("cls");
				printf("\nError: opcion invalida.\n");
				system("pause");
				system("cls");
				printf("\nVa a elegir mes o anio? (1 mes, 2 anio, 3 salir): \t");
				fflush(stdin);
				scanf("%d", &eleccion);
			}
			if(eleccion == 3){
				continuar = 0;
				printf("\nVOLVIENDO...\n");
			}
			else if(eleccion == 1){
				printf("\nEscoja el mes: \t");
				fflush(stdin);
				scanf("%d", &mes);
				while((mes < 1)||(mes > 12)){
					printf("\nMes invalido. Intente de vuelta.\n");
					printf("\nEscoja el mes: \t");
					fflush(stdin);
					scanf("%d", &mes);
				}
				printf("\nEscoja el anio: \t");
				fflush(stdin);
				scanf("%d", &anio);
				while((anio < 1900)||(anio > 9999)){
					printf("\nAnio invalido. Intente de vuelta.\n");
					printf("\nEscoja el anio: \t");
					fflush(stdin);
					scanf("%d", &anio);
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
					system("pause");
				}
				system("pause");
				system("cls");
				printf("\nDesea continuar? (1 si, 0 no): \t");
				fflush(stdin);
				scanf("%d", &continuar);
				while((continuar != 1)&&(continuar != 0)){
					system("cls");
					printf("\nError: opcion invalida.\n");
					system("pause");
					system("cls");
					printf("\nDesea continuar? (1 si, 0 no): \t");
					fflush(stdin);
					scanf("%d", &continuar);
				}
				
			}
			else if(eleccion == 2){
				
				printf("\nEscoja el anio: \t");
				fflush(stdin);
				scanf("%d", &anio);
				while((anio < 1900)||(anio > 9999)){
					printf("\nAnio invalido. Intente de vuelta.\n");
					printf("\nEscoja el anio: \t");
					fflush(stdin);
					scanf("%d", &anio);
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
				printf("\nDesea continuar? (1 si, 0 no): \t");
				fflush(stdin);
				scanf("%d", &continuar);
				while((continuar != 1)&&(continuar != 0)){
					system("cls");
					printf("\nError: opcion invalida.\n");
					system("pause");
					system("cls");
					printf("\nDesea continuar? (1 si, 0 no): \t");
					fflush(stdin);
					scanf("%d", &continuar);
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
	
    FILE *fper, *fing;
	int continuar = 1;
	int encontrados, existePers, existeIng;
	long long dni;
	Persona persona;
	Ingreso ingreso;
	
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
					
					printf("\nIngrese el dni de la persona deseada: \t");
					scanf("%lld",&dni);
					while(dni <= 0){
						printf("\nDni invalido. Intentelo nuevamente.\n");
						printf("\nIngrese el dni de la persona deseada: \t");
						scanf("%llu",&dni);
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
				printf("\nDesea continuar? (1 si, 0 no):\t");
				fflush(stdin);
				scanf("%d",&continuar);
				while((continuar != 0)&&(continuar != 1)){
					printf("\nOpcion invalida. Intentelo de nuevo.\n");
					printf("\nDesea continuar? (1 si, 0 no):\t");
					fflush(stdin);
					scanf("%d",&continuar);
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
	
    int mes,anio, continuar = 1;
	double total_ingresos, total_gastos, saldo;
	FILE *fing, *fgas;
	Ingreso ingreso;
	Gasto gasto;
	
	if((fing = fopen("ingresos.dat","rb"))!=NULL){
		if((fgas = fopen("gastos.dat","rb"))!=NULL){
			
			while(continuar){
				system("cls");
				printf("-------------\nSALDO MENSUAL\n-------------");
				printf("\nIngrese el mes deseado:\t");
				fflush(stdin);
				scanf("%d",&mes);
				while((mes < 1)||(mes > 12)){
					printf("\nMes invalido. Intentelo nuevamente.\n");
					printf("\nIngrese el mes deseado:\t");
					fflush(stdin);
					scanf("%d",&mes);
				}
				printf("\nIngrese el anio deseado:\t");
				fflush(stdin);
				scanf("%d",&anio);
				while((anio < 1900)||(anio > 9999)){
					printf("\nAnio invalido. Intentelo nuevamente.\n");
					printf("\nIngrese el anio deseado:\t");
					fflush(stdin);
					scanf("%d",&anio);
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
				printf("\nDesea continuar (1 si, 0 no): \t");
				fflush(stdin);
				scanf("%d", &continuar);
				while((continuar != 0)&&(continuar != 1)){
					printf("\nError: entrada invalida.\n");
					printf("\nDesea continuar (1 si, 0 no): \t");
					fflush(stdin);
					scanf("%d", &continuar);
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
	Gasto gasto;
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
	
    int continuar = 1, opc, existe;
	FILE *fpag;
	Pago pago;
	
	if((fpag = fopen("pagos.dat","rb"))!=NULL){
		
		while(continuar){
			
			system("cls");
            printf("---------\n6. PAGOS POR MEDIO DE PAGO\n---------");
			printf("\nSeleccione el medio de pago:\n\n1. Efectivo\n2. Billetera Electronica\n3. Tarjeta\n4. Debito\n5. Volver\n\nElija una opcion: \t");
			fflush(stdin);
			scanf("%d", &opc);
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
				printf("\nDesea continuar? (1 si, 0 no):\t");
				fflush(stdin);
				scanf("%d", &continuar);
				while((continuar != 0)&&(continuar != 1)){
					printf("\nError: opcion invalida. Intente de nuevo\n");
					printf("\nDesea continuar? (1 si, 0 no):\t");
					fflush(stdin);
					scanf("%d", &continuar);
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
	Gasto gasto;
	Pago pago;
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

void top3CategoriasMasCostosas() {
	
    FILE *fcat, *fgas;
	Categoria cat;
	Gasto gasto;
	int i, top, existe = 0;
	
	//obtener fecha actual
	time_t t = time(NULL);
	struct tm *f = localtime(&t);
	int mes_actual = f->tm_mon + 1;
    int anio_actual = f->tm_year + 1900;
    
    // calcular mes y año anterior
    int mes_anterior = mes_actual - 1;
    int anio_anterior = anio_actual;
    if(mes_anterior == 0) {
        mes_anterior = 12;
        anio_anterior = anio_actual - 1;
    }
    system("cls");
    printf("\n=== TOP 3 CATEGORIAS MAS COSTOSAS - %d/%d ===\n", mes_anterior, anio_anterior);
    
    if((fcat = fopen("categorias.dat","rb"))!=NULL){
    	if((fgas = fopen("gastos.dat","rb"))!=NULL){
    		
    		//contar cantidad de categorias
    		fseek(fcat,0,SEEK_END);
    		long tam = ftell(fcat);
    		int cantCategorias = tam / sizeof(Categoria);
    		rewind(fcat);
    		
    		double totales[cantCategorias];
    		unsigned long long codigos[cantCategorias];
    		char nombres[cantCategorias][50];
    		
    		int indice = 0;
    		
    		fread(&cat, sizeof(Categoria),1,fcat);
    		
    		while(!feof(fcat)){
    			
    			codigos[indice] = cat.codigo;
    			strcpy(nombres[indice],cat.nombre);
    			totales[indice] = 0;
    			indice++;
    			
    			fread(&cat,sizeof(Categoria),1,fcat);
			}
			
			//procesar gastos del mes anterior
			fread(&gasto,sizeof(Gasto),1,fgas);
			
			while(!feof(fgas)){
				
				if((gasto.fechaGasto.mes == mes_anterior) && (gasto.fechaGasto.anio == anio_anterior)){
					
					for(i = 0; i < cantCategorias; i++){
						
						if(gasto.categoria.codigo == *(codigos + i)){
							
							*(totales + i) += gasto.monto;
							
						}
					}
				}
				
				fread(&gasto,sizeof(Gasto),1,fgas);
			}
			
			//buscar las 3 mayores
			for(top = 1; top <= 3; top++){
				
				double max = -1;
				int pos_max = -1;
				
				for(i = 0; i < cantCategorias; i++){
					
					if(*(totales + i) > max){
						
						max = *(totales + i);
						pos_max = i;
						
					}
				}
				
				if((pos_max != -1) && (max > 0)){
					
					printf("%d. %s: $%.2lf\n", top, nombres[pos_max], max);
					existe = 1;
					totales[pos_max] = -1; // "eliminar" para siguiente búsqueda
				}
				
			}
			if(!existe){
				printf("\nNinguna categoria registrada registra gastos hasta el momento.\n");
				printf("\n");
			}
			printf("\n===============================================");
			printf("\n");
			system("pause");
			
    		fclose(fgas);
		}
		else{
			system("cls");
			printf("\nNo se cargaron gastos hasta el momento.\n");
			system("pause");
		}
    	fclose(fcat);
	}
	else{
		system("cls");
		printf("\nNo se cargaron categorias hasta el momento.\n");
		system("pause");
	}
	
}

///////////////////////////////////////// proyeccionMensual ///////////////////////////////////////////////////////////////////////////////////////

void proyeccionMensual() {
	
    FILE *fgas;
    Gasto gasto;
    
    // obtener fecha actual
    time_t t = time(NULL);
    struct tm *f = localtime(&t);
    int mes_actual = f->tm_mon + 1;
    int anio_actual = f->tm_year + 1900;
    
    // calcular los 3 meses anteriores (SIN incluir el actual)
    int meses[3], anios[3];
    
    for(int i = 0; i < 3; i++){
        *(meses + i) = mes_actual - (i + 1);  // +1 para excluir actual
        *(anios + i) = anio_actual;
        if(*(meses + i) <= 0){
            *(meses + i) += 12;
            *(anios + i) -= 1;
        }
    }
    system("cls");
    printf("\n=== PROYECCION MENSUAL - %d/%d ===\n", mes_actual, anio_actual);
    printf("BASADO EN: %d/%d, %d/%d, %d/%d\n\n", meses[2], anios[2], meses[1], anios[1], meses[0], anios[0]);
    
    double totales[3] = {0,0,0};
    int contadores[3] = {0,0,0};
    
    if((fgas = fopen("gastos.dat", "rb")) != NULL){
    	
        fread(&gasto, sizeof(Gasto), 1, fgas);
        while(!feof(fgas)){
            
            for(int i = 0; i < 3; i++){
                if(gasto.fechaGasto.mes == *(meses + i) && gasto.fechaGasto.anio == *(anios + i)){
                    *(totales + i) += gasto.monto;
                    *(contadores + i) += 1;
                }
            }
            fread(&gasto, sizeof(Gasto), 1, fgas);
        }
        fclose(fgas);
        
        double suma = 0;
        int meses_con_datos = 0;
        
        for(int i = 2; i >= 0; i--){ 
        
            printf("GASTO TOTAL %d/%d: $%.2lf\n", *(meses + i), *(anios + i), *(totales + i));
            
            if(*(totales + i) > 0){
                suma += *(totales + i);
                meses_con_datos++;
            }
            
        }
        
        double proyeccion = 0;
        if(meses_con_datos > 0){
            proyeccion = suma / meses_con_datos;
        }
        
        printf("\nPROYECCION TOTAL: $%.2lf\n", proyeccion);
    }
    else{
    	system("cls");
        printf("\nNo se cargaron gastos hasta el momento.\n");
    }
	
	printf("\n");
	system("pause");
	
}

///////////////////////////////////////// resumenGeneral ///////////////////////////////////////////////////////////////////////////////////////

void resumenGeneral() {
	
    FILE *fcat, *fgas, *fres, *fcont;
	Categoria cat;
	Gasto g;
	char nombreArchivo[50], tipo[10], estado[15];
	int numArchivo = 1, i;
	
	if((fcont = fopen("contador.txt","r"))!=NULL){
		
		fscanf(fcont,"%d",&numArchivo);
		fclose(fcont);
		
	}
	else{
		
		if((fcont = fopen("contador.txt","w"))!=NULL){
		
		fprintf(fcont, "%d", numArchivo);
		fclose(fcont);
		
		}
		
		else{
			printf("\nError al abrir el archivo.\n");
		}	
	
	}
	
	if((fcat = fopen("categorias.dat","rb"))!=NULL){
		if((fgas = fopen("gastos.dat","rb"))!=NULL){
			
			sprintf(nombreArchivo,"resumen_general%d.txt",numArchivo);
			
			
			if((fres = fopen(nombreArchivo,"w"))!=NULL){ 
				
				// calcular cantidad real de categorías en el archivo
				fseek(fcat,0,SEEK_END);
				long tam = ftell(fcat);
				int cantCategorias = tam / sizeof(Categoria);
				rewind(fcat);
				
				double totalesPorCat[cantCategorias];
				int cantGastosPorCat[cantCategorias];
				char nombresCat[cantCategorias][50];
				
				for(i = 0; i < cantCategorias; i++){
					
					*(totalesPorCat + i) = 0;
					*(cantGastosPorCat + i) = 0;
					nombresCat[i][0] = '\0';
					
				}
				
				
				fprintf(fres, "===== RESUMEN GENERAL DE GASTOS =====\n\n");
				fprintf(fres, "Fecha       Categoria               Tipo          Monto\n");
				fprintf(fres, "----------------------------------------------------------\n");
				
				
				double totalGeneral = 0;
				int indiceCat = 0;
				
				fread(&cat,sizeof(Categoria),1,fcat);
				
				while(!feof(fcat)){
					
					strcpy(nombresCat[indiceCat], cat.nombre);
					double totalCat = 0;
					int cantGastosCat = 0;
					
					rewind(fgas); //casi me lo olvide
					fread(&g,sizeof(Gasto),1,fgas);
					
					while(!feof(fgas)){
						
						if(g.categoria.codigo == cat.codigo){
							
	                        switch(g.tipoGasto){
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
					
							
							fprintf(fres, "%02d/%02d/%d   %-20s   %-12s   $%9.2f\n", g.fechaGasto.dia, g.fechaGasto.mes, g.fechaGasto.anio, g.categoria.nombre, tipo, g.monto);

							totalCat += g.monto;
							cantGastosCat++;
							
						}
						
						fread(&g,sizeof(Gasto),1,fgas);
					}
					
					totalesPorCat[indiceCat] = totalCat;
					cantGastosPorCat[indiceCat] = cantGastosCat;
					totalGeneral += totalCat;
					indiceCat++;
					
					fread(&cat,sizeof(Categoria),1,fcat); //casi me lo olvide, tengo un problemita
					
				}
				
				fprintf(fres, "\n\n===== ESTADÍSTICAS GENERALES =====\n");
				fprintf(fres, "Categoria                 Total($)    Promedio($)   %% del Total\n");
				fprintf(fres, "----------------------------------------------------------\n");
				
				for(i = 0; i < indiceCat; i++){
					
					if(cantGastosPorCat[i] > 0){
						
						double promedio = totalesPorCat[i] / cantGastosPorCat[i];
						double porcentaje = (totalesPorCat[i] / totalGeneral) * 100;
						fprintf(fres, "%-23s   $%9.2f   $%9.2f   %6.2f%%\n", nombresCat[i], totalesPorCat[i], promedio, porcentaje);
					}
					
				}
				
				fprintf(fres, "\nTOTAL GENERAL: $%.2f\n",totalGeneral);
				
				fclose(fres);
				
				 if((fcont = fopen("contador.txt","w"))!=NULL){
				 	
                    fprintf(fcont, "%d", numArchivo + 1);
                    fclose(fcont);
                }
                else{
                	printf("\nError al abrir el archivo.\n");
				}
				system("cls");
				printf("---------\n10. RESUMEN GENERAL\n---------");
				printf("\nResumen generado con exito!\n");
				system("pause");
                
				
			}
			else{
				printf("\nError al abrir el archivo.\n"); 
			}
			fclose(fgas);
		}
		else{
			system("cls");
			printf("\nNo se cargaron gastos hasta el momento.\n");
			system("pause");
		}
		fclose(fcat);
	}
	else{
		system("cls");
		printf("\nNo se cargaron categorias hasta el momento.\n");
		system("pause");
	}
	
}

///////////////////////////////////////// listaCategorias ///////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////// listaGastos ///////////////////////////////////////////////////////////////////////////////////////

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
				auxf=gasto.restanteCuota;
				
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
			printf("\nID De Gasto: %llu\n", IX);
			printf("\nTipo De Gasto: %s\n",Tip);
			
	            	
		}else{
			Cad22[strcspn(Cad22, "\n")] = 0;
			x=0;
		}
	}
}

///////////////////////////////////////// digitosC ///////////////////////////////////////////////////////////////////////////////////////

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