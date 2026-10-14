#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	
	int dia;
	int mes;
	int anio;
	
} Fecha;

typedef struct{
	
	unsigned long long codigo;
	char nombre[50];

} Categoria;

typedef struct{
	
	long long dni;
	char nombre[50];
	
} Persona;

typedef struct{
	
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
	
} Gasto;

typedef struct{
	
	unsigned long long codGasto;
	int medioPago;
	double importe;
	Fecha fechaPago;
	
} Pago;

typedef struct{
	
	unsigned long long codIngreso;
	char concepto[50];
	double monto;
	Fecha fecha;
	Persona persona;
	
} Ingreso;

Ingreso ingreso;
Gasto gasto;
Pago pago;
Fecha fecha;


//1Ros PROTOTIPOS///////////////////////
void cargarGasto();//CARGAR GASTO
void cargarIngreso();//CARGAR INGRESO
void registrarPago();//REGISTRAR PAGO
void listarGastoseIngresos();//LISTAR GASTOS E INGRESOS
void consultasyReportes();//CONSULTAS Y REPORTES
void agregarCategoria();//AGREGAR CATEGORIA


//2Dos PROTOTIPOS*********

//CARGAR GASTO
void guardarGasto(Gasto gasto);
int comprobacion_fecha(int aux_anio,int aux_mes,int aux_dia);
void ver_arch_gastos(); //Unicamente para ver como queda en el archivo gastos.dat
unsigned long long buscar_idGasto();
unsigned long long buscar_idCategoria();
unsigned long long buscar_idIngreso();
void registroCategoria(char*);

//CARGAR INGRESO
void guardarIngreso(Ingreso ingreso);
void ver_arch_ingresos();//Unicamente para ver como queda en el archivo ingresos.dat

void ver_arch_pagos();

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

//3Ros PROTOTIPOS-----------------
void filtroPorMes(int);
int digitos(char*);
long long digitosDNI(char*);
int listaCategorias();


int main(){
	
	char copc[1];
	int opcp,zxxz=1;
	while (zxxz){
		system("cls");
		printf("\nSistema De Gestion De Gastos Personales O Familiares\n--------MENU PRINCIPAL--------\n\n1. Registrar Gasto\n2. Registrar Ingreso\n3. Registrar Pago\n4. Listar Gastos E Ingresos\n5. Consultas y Reportes\n6. Salir\n\nElija Una Opcion: ");
		fflush(stdin);
		gets(copc);
		
		opcp=atoi(copc);
		
		switch (opcp){
			case 1:
				system("cls");
				printf("------------------\n1.REGISTRAR GASTO\n------------------");
				cargarGasto();
				ver_arch_gastos();//quitar luego
				break;
			case 2:
				system("cls");
				printf("---------\n2. REGISTRAR INGRESO\n---------");
			    cargarIngreso();
			    ver_arch_ingresos();//quitar luego
				break;
			case 3:
				system("cls");
				printf("---------\n3. REGISTRAR PAGO\n---------");
				registrarPago();
				ver_arch_pagos();//quitar luego
				break;
			case 4:
				system("cls");
				printf("---------\n4. LISTAR GASTOS E INGRESOS\n---------");
				listarGastoseIngresos();
				break;	
			case 5:
				system("cls");
				printf("---------\n5. CONSULTAS Y REPORTES\n---------");
				consultasyReportes();
				break;	
			case 6:
				system("cls");
				printf("\nSALIENDO .....\n\n");
				zxxz=0;
				break;				
			default:
				printf("\nIngrese Un Numero Valido Del 1-6 De Tipo Entero\n\n");
				system("PAUSE");
		}
	}
	return 0;
}

/////////////////////////////////////////REGISTRAR GASTO//////////////////////////////////////////////////////////////////////////////////////////

void cargarGasto(){
    FILE *f2,arch1;
    int s=1, c=1, aux_anio, aux_mes, aux_dia,opc,cnt,z,x=1,largo=0,z1,cc,ac,ca,i;
    unsigned long long id,idC,IDaux;
    char Cad2[1000],montox[10],Cad3[10],Cad4[5],Cad8[9];
    
    while(s){
    	
    	cnt=1;
        if((f2 = fopen("gastos.dat", "ab")) == NULL){
            printf("\nError Al Abrir El Archivo");
        } else {
        	fread(&gasto,sizeof(Gasto),1,f2);
        	fclose(f2);
            // Obtener el próximo ID disponible
            id = buscar_idGasto();
            gasto.codGasto = id;
            
            while(cnt){
            	
            	system("cls");
	            printf("\nIngrese El Tipo De Gasto\n\n1. Gasto Fijo\n2. Gasto Ocasional\n3. Gasto Temporal\n4. Gasto Anual\n\nElija Una Opcion: ");
	            fflush(stdin);
	            scanf("%d",&opc);
	            
	            system("cls");
	            printf("\nID De Gasto: %llu", id); // Para debug
	            
	            switch (opc){
					case 1:
						gasto.tipoGasto=1;
						printf("\n\nTipo De Gasto: Fijo");
						strcpy(Cad3,"Fijo");
						cnt=0;
						break;
					case 2:
						gasto.tipoGasto=2;
						printf("\n\nTipo De Gasto: Ocasional");
						strcpy(Cad3,"Ocasional");
						cnt=0;
						break;
					case 3:
						gasto.tipoGasto=3;
						printf("\n\nTipo De Gasto: Temporal");
						strcpy(Cad3,"Temporal");
						cnt=0;
						break;
					case 4:
						gasto.tipoGasto=4;
						printf("\n\nTipo De Gasto: Anual");
						strcpy(Cad3,"Anual");
						cnt=0;
						break;					
					default:
						system("cls");
						printf("\nIngrese Un Numero Valido Del 1-4 De Tipo Entero\n\n");
						system("PAUSE");
				}
            } 
            	
            	
            	
            	
            	
            	
            	
            	
            	
            	
            	
            	
            	
            	
            	
            	
            	
            	
            /*if((f2 = fopen("gastos.dat", "r+b")) != NULL){
            	if(fread(&gasto, sizeof(Gasto), 1, f2)== 1){
                
                //printf("\nawdfsefgsdgsdgsg");
                fclose(f2);
                registroCategoria(Cad2);
                strcpy(gasto.categoria.nombre,Cad2);
            	
            	
            	idC = buscar_idCategoria();
            	gasto.categoria.codigo = idC;
            	}else{
            		rewind(f2);
            		ac=1;
					while(ac){
						cc=listaCategorias();
						rewind(f2);
						
						scanf("%llu",IDaux);
						
	            		if(IDaux==0){
	            			//printf("\nawdfsefgsdgsdgsg");
	            			
	            			registroCategoria(Cad2);
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
								rewind(f2);
							}else{
								ca=1;
								i=1;
								while((ca)||(i<=cc)){
									fread(&gasto,sizeof(Gasto),1,f2);
									if(gasto.codGasto==IDaux){
										ca=0;
										ac=0;
										strcpy(gasto.categoria.nombre,Cad2);
										idC=cc;
									}
									fread(&gasto,sizeof(Gasto),1,f2);
									i++;
								}
								if(ca){
									system("cls");
									printf("\nID No Encontrado, Ingrese Correctamente el ID\n");
									system("PAUSE");
									system("cls");
								}
							}	
						}	
					}
 			
				
				}
				
			}else{
				printf("\nError al abrir el archivo");
			}*/
			
			
				
		
				
	
       		
       		
            fclose(f2);
            
            
            
            printf("\nID De Categoria: %llu\n", idC); // Para debug
            
            
            
            x=1;
            while(x){
            	
            	printf("\n\nIngrese Una Descripcion Del Gasto: ");
	            fflush(stdin);
	            gets(Cad2);
	            
	            if((strlen(Cad2)>49)||(Cad2[0]=='\0')||(Cad2[0]==32)){
	            	
	            	system("cls");
	            	printf("\nNo Se Permite Mas De 50 Caracteres En La Descripcion O Con Espacios Al Inicio, Por Favor, Vuelva A Ingresarlo\n\n");
	            	system("PAUSE");
					system("cls");
	            	printf("\nID De Gasto: %llu", id);
	            	printf("\n\nTipo De Gasto: %s",Cad3);
	            	fflush(stdin);
	            	
				}else{
					Cad2[strcspn(Cad2, "\n")] = 0;
	         	  	strcpy(gasto.desc, Cad2);
					x=0;
				}
			}
            
            z=1;
            while(z){
            	printf("\nIngrese El Monto: $");
            	gets(montox);
            	
            	gasto.monto=atof(montox);
            	if(gasto.monto>=1){
					z=0;            		
				}else{
					system("cls");
					printf("\nIngrese Un Monto Valido Mayor A 0\n\n");
					system("PAUSE");
					system("cls");
					
					printf("\nID De Gasto: %llu", id);
					printf("\n\nTipo De Gasto: %s",Cad3);
					printf("\n\nDescripcion Del Gasto: %s",gasto.desc);
					printf("\n\nID De Categoria: %llu\n", idC);
					printf("\nPertenece A La Categoria: %s\n",gasto.categoria.nombre);
				}
			}
            
            
            // Resto del código para fecha, cuotas, persona...
            c = 1;
            while(c){
                printf("\n--------------------Ingresado De Fecha--------------------");
                printf("\nIngrese El Anio En Formato Numero Largo (Ej,2006)\nAnio Ingresado: ");
                fflush(stdin);
                gets(Cad4);
                //aux_anio=atoi(Cad4);
                
                aux_anio=digitos(Cad4);
                
                printf("\nIngrese El Mes En Formato Numero\nMes Ingresado: ");
                fflush(stdin);
                gets(Cad4);
                //aux_mes=atoi(Cad4);
                
                aux_mes=digitos(Cad4);
                
                printf("\nIngrese El Dia\nDia Ingresado: ");
                fflush(stdin);
                gets(Cad4);
                //aux_dia=atoi(Cad4);
                
                aux_dia=digitos(Cad4);
                
                c = comprobacion_fecha(aux_anio, aux_mes, aux_dia);
                
                if(c == 1){
                	system("cls");
                    printf("\nSe Ha Ingresado Mal La Fecha. Por Favor, Vuelva A Ingresarla\n\n");
                    system("PAUSE");
					system("cls");
					
					printf("\nID De Gasto: %llu", id);
					printf("\n\nTipo De Gasto: %s",Cad3);
					printf("\n\nDescripcion Del Gasto: %s",gasto.desc);
					printf("\n\nID De Categoria: %llu\n", idC);
					printf("\nPertenece A La Categoria: %s\n",gasto.categoria.nombre);
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
          		gasto.cuotasTotales=atoi(Cad4);	  
          		
          		if(gasto.cuotasTotales<1){
          			system("cls");
                    printf("\nSe Ha Ingresado Mal La Cantidad De Cuotas Totales, Debe Ser Entero Superior A 0\n\n");
                    system("PAUSE");
					system("cls");
					
					printf("\nID De Gasto: %llu", id);
					printf("\n\nTipo De Gasto: %s",Cad3);
					printf("\n\nDescripcion Del Gasto: %s",gasto.desc);
					printf("\n\nID De Categoria: %llu\n", idC);
					printf("\nPertenece A La Categoria: %s\n",gasto.categoria.nombre);
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
          		gasto.persona.dni=atoi(Cad8);
          		
          		gasto.persona.dni=digitosDNI(Cad8);
          		
          		if(strlen(Cad8)>8||strlen(Cad8)<6){
          			system("cls");
                    printf("\nNo Se Permite Mas De 8 Numeros En El DNI, O Menor A 6 Numeros, Por Favor, Vuelva A Ingresarlo\n\n");
                    system("PAUSE");
					system("cls");
					
					printf("\nID De Gasto: %llu", id);
					printf("\n\nTipo De Gasto: %s",Cad3);
					printf("\n\nDescripcion Del Gasto: %s",gasto.desc);
					printf("\n\nID De Categoria: %llu\n", idC);
					printf("\nPertenece A La Categoria: %s\n",gasto.categoria.nombre);
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
            
            x=1;
            while(x){
            	
            	printf("\nIngrese El Nombre Del Responsable: ");
	            fflush(stdin);
	            gets(Cad2);
	            if((strlen(Cad2)>49)||(Cad2[0]=='\0')||(Cad2[0]==32)){
	            	system("cls");
	            	printf("\nNo Se Permite Mas De 50 Caracteres En El Nombre O Con Espacios Al Inicio, Por Favor, Vuelva A Ingresarlo\n\n");
	            	system("PAUSE");
					system("cls");
					
					printf("\nID De Gasto: %llu", id);
					printf("\n\nTipo De Gasto: %s",Cad3);
					printf("\n\nDescripcion Del Gasto: %s",gasto.desc);
					printf("\n\nID De Categoria: %llu\n", idC);
					printf("\nPertenece A La Categoria: %s\n",gasto.categoria.nombre);
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
					x=0;
				}
			}
            
            // Escribir el gasto en el archivo
            fwrite(&gasto, sizeof(Gasto), 1, f2);
            fclose(f2);
            
            printf("\n----------------------------------------------------------\n\n\nGasto Guardado Exitosamente En El ID: %llu\n", id);
            
            z1=1;
            while(z1){
            	printf("\nDesea Registrar Otro Gasto?\n\n1. Si, Aplicar Seguir\n0. No, Aplicar Y Finalizar\n\nElija Una Opcion: ");
            	scanf("%d", &s);
            	if((s!=0)&&(s!=1)){
            		system("cls");
            		printf("\nIngrese Un Valor Entero Correcto 1/0\n\n");
            		system("PAUSE");
					system("cls");
				}else{
					z1=0;
				}
        
    }
}
}

/////////////////////////////////////////REGISTRAR INGRESO//////////////////////////////////////////////////////////////////////////////////////////

void cargarIngreso(){
	char Cad1[1000],montox[10],Cad4[4],Cad8[9];
	unsigned long long id;
	FILE *f1;
	int s,c,x,z,y,aux_anio,aux_mes,aux_dia,z1;
	if((f1=fopen("ingresos.dat","ab"))==NULL){
		printf("\nError Al Abrir El Archivo");
	}else{
		s=1;
		while(s){

			id = buscar_idIngreso();
            ingreso.codIngreso = id;
				
			system("cls");
	        printf("\nID De Ingreso: %llu\n", id);
				
			x=1;
			while(x){
            	printf("\nIngrese El Concepto Del Ingreso: ");
				fflush(stdin);
				gets(Cad1);
				
				if((strlen(Cad1)>49)||(Cad1[0]=='\0')||(Cad1[0]==32)){
					system("cls");
					printf("\nNo Se Permite Mas De 50 Caracteres En El Concepto O Con Espacios Al Inicio, Por Favor, Vuelva A Ingresarlo\n\n");
					system("PAUSE");
					system("cls");
					printf("\nID De Ingreso: %llu\n", id);
				
				}else{
					x=0;
					//Cad1[strcspn(Cad1,"\n")] = 0;
					strcpy(ingreso.concepto, Cad1);
				}
			}
			z=1;
	        while(z){
	            printf("\nIngrese El Monto: $");
	            gets(montox);
	            	
	            ingreso.monto=atof(montox);
	            if(ingreso.monto>=1){
					z=0;            		
				}else{
					system("cls");
					printf("\nIngrese Un Monto Valido Mayor A 0\n\n");
					system("PAUSE");
					system("cls");
					
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
	            //aux_anio=atoi(Cad4);
	    		
	            aux_anio=digitos(Cad4);
	             
	        	printf("\nIngrese El Mes En Formato Numero\nMes Ingresado: ");
				fflush(stdin);
	            gets(Cad4);
	            //aux_mes=atoi(Cad4);
	            
	            aux_mes=digitos(Cad4);
	        	
	            printf("\nIngrese El Dia\nDia Ingresado: ");
				fflush(stdin);
	            gets(Cad4);
	            //aux_dia=atoi(Cad4);
	    		
	            aux_dia=digitos(Cad4);
	            
	            c = comprobacion_fecha(aux_anio, aux_mes, aux_dia);
	        
	            if(c == 1){
					system("cls");
	                printf("\nSe Ha Ingresado Mal La Fecha. Por Favor, Vuelva A Ingresarla\n\n");
	                system("PAUSE");
					system("cls");
					
					printf("\nID De Ingreso: %llu\n", id);
					printf("\nEl Concepto Del Ingreso es: %s\n",ingreso.concepto);
					printf("\nEl Monto es: $%.3lf\n",ingreso.monto);
	            	}
	            }
	            
	            ingreso.fecha.anio = aux_anio;
	            ingreso.fecha.mes = aux_mes;
	            ingreso.fecha.dia = aux_dia;
            
				printf("----------------------------------------------------------\n");
				
				x=1;
				while(x){
            	
	            	printf("\nIngrese El Nombre De La Persona: ");
		            fflush(stdin);
		            gets(Cad1);
		            
		            if((strlen(Cad1)>49)||(Cad1[0]=='\0')||(Cad1[0]==32)){
		            	system("cls");
		            	printf("\nNo Se Permite Mas De 50 Caracteres En El Nombre O Con Espacios Al Inicio, Por Favor, Volver A Ingresar\n\n");
		            	system("PAUSE");
						system("cls");
						
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
						x=0;
					}
				}
				
				strcpy(ingreso.persona.nombre,Cad1);
				
            	c=1;
            	while(c){
            	
        			printf("\nIngresar el DNI de la persona: ");
          			fflush(stdin);
          			gets(Cad8);
          			ingreso.persona.dni=atoi(Cad8);
          			
          			ingreso.persona.dni=digitosDNI(Cad8);
          		
          			if(strlen(Cad8)>8||strlen(Cad8)<6){
          				system("cls");
                	    printf("\nNo Se Permite Mas De 8 Numeros En El DNI, O Menor A 6 Numeros, Por Favor, Vuelva A Ingresarlo\n\n");
                	    system("PAUSE");
						system("cls");
						
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
            	
            	fclose(f1);
            	
				guardarIngreso(ingreso);
				
          		printf("\n----------------------------------------------------------\n\n\nIngreso Guardado Exitosamente En El ID: %llu\n", ingreso.codIngreso);
				
				
				
				z1=1;
            	while(z1){
					printf("\nDesea Registrar Otro Ingreso?\n\n1. Si, Aplicar Seguir\n0. No, Aplicar Y Finalizar\n\nElija Una Opcion: ");
					scanf("%d",&s);
					if((s!=0)&&(s!=1)){
            			system("cls");
            			printf("\nIngrese Un Valor Entero Correcto 1/0\n\n");
            			system("PAUSE");
						system("cls");
					}else{
						z1=0;
					}
				}
		}
		
		
	}
	
	}

/////////////////////////////////////////REGISTRAR PAGO/////////////////////////////////////////////////////////////////////////////////////////////

void registrarPago(){
	int s=1,encontro=1,seguir,vf1,vf2,Cuotas,c;
	int aux_anio,aux_mes,aux_dia,opc1;
	char Tipo[11];
	unsigned long long aux;
	FILE*arch,*archp;
	int cc=0;
	double aux_1,aux_2;
	while(s){
	    system("cls");
		printf("---------------------------------------------\n1. REGISTRO DE PAGO Y ACTUALIZACION DE GASTO\n---------------------------------------------");
		fflush(stdin);
		printf("\n2. Lista De Pagos Pendientes\n----------------------------");
		//system("PAUSE");
		
		if((arch=fopen("gastos.dat","r+b"))==NULL){
			printf("\nError al abrir el archivo");
		}else{
			rewind(arch);
			cc=0;
			fread(&gasto,sizeof(Gasto),1,arch);
			while(!feof(arch)){
			
				if(gasto.estadoCuota!=3){
					Cuotas=((gasto.cuotasTotales-gasto.cuotaActual)+1);
					cc++;
					//printf("\nCUOTA :%d",Cuotas);
					switch (gasto.tipoGasto){
					case 1:
						printf("\nEl Tipo de Gasto Es Fijo");
						strcpy(Tipo,"Fijo");
						break;
					case 2:
						printf("\nEl Tipo de Gasto Ocasional");
						strcpy(Tipo,"Ocasional");
						break;
					case 3:
						printf("\nEl Tipo de Gasto Temporal");
						strcpy(Tipo,"Temporal");
						break;
					case 4:
						printf("\nEl Tipo de Gasto Anual");
						strcpy(Tipo,"Anual");
						break;
					}	
					aux_1= gasto.monto / gasto.cuotasTotales;
					aux_2=(gasto.monto - (Cuotas*aux_1));
					printf("\n%d.\tCodigo: %llu El Monto A Pagar Restante Es De $%lf, En %d cuotas de %lf, Hecho Por La Persona %lld, Es Un Gasto %s, Con Un Descripcion De %s, Pertenece A La Categoria %s, Tomado En La Fecha %d / %d / %d\n",cc,gasto.codGasto,gasto.monto,Cuotas,aux_1,gasto.persona.dni,Tipo,gasto.desc,gasto.categoria.nombre,gasto.fechaGasto.dia,gasto.fechaGasto.mes,gasto.fechaGasto.anio);
				}
				fread(&gasto,sizeof(Gasto),1,arch);
			}
			
		
			printf("\nIngrese El Codigo De Gasto Que Desea Abonar: ");
			fflush(stdin);
			scanf("%llu",&aux);
			
			vf1=1;
			rewind(arch);
			
			while(vf1){
				fread(&gasto,sizeof(gasto),1,arch);
				while(!feof(arch)&&encontro){
					if(aux==gasto.codGasto){
						encontro=0,vf1=0;	
					}
					else{
						fread(&gasto,sizeof(gasto),1,arch);
					}
				}
				if(encontro){
					printf("\n\nNumero Id de Gasto Inexistente\n\nIngrese Nuevamente El Id De Tipo Entero: ");
					fflush(stdin);
					scanf("%llu",&aux);
				}
			}
			printf("\n\nIngrese El Monto A Abonar: ");
			fflush(stdin);
			scanf("%lf",&pago.importe);
			
			vf2=1;
			while(vf2){
				if(pago.importe<1){
					printf("\n\nNo Ingrese Un Valor Negativo O Igual A 0, Debe Ser Positivo Y Mayor\n\nIngrese El Monto A Abonar: ");
					fflush(stdin);
					scanf("%lf",&pago.importe);
				}
				else{
					if(pago.importe>gasto.monto){
					printf("\n\nNo Ingrese Un Valor Superior A La Deuda Actual, Debe Ser Igual O Inferior\n\nIngrese El Monto A Abonar: ");
					fflush(stdin);
					scanf("%lf",&pago.importe);
					}
					else{
						vf2=0;
					}
				}
			}
			
			system("cls");
			printf("\n\nIngrese El Medio De Pago\n\n1.Efectivo\n2.Debito\n3.Tarjeta\n4.Billetera Electronica\t: ");
			fflush(stdin);
			scanf("%d",opc1);
			
			system("cls");
			c=1;
			while(c){
				printf("\nIngresado de fecha de pago");
				printf("\nIngresar el anio (formato numero largo, ej: 2006):");
				fflush(stdin);
				scanf("%d",&aux_anio); 
				
				printf("\nIngresar el mes de pago(formato numero, ej: 11):");
				fflush(stdin);
				scanf("%d",&aux_mes);
				
				printf("\nIngresar el dia de pago:");
				fflush(stdin);
				scanf("%d",&aux_dia);	
				
				
				
				c=comprobacion_fecha(aux_anio,aux_mes,aux_dia);
				if(c==1){
					printf("\nSe ha ingresado mal la fecha. Por favor, volver a ingresarla");
				}
			}
			gasto.fechaGasto.anio=aux_anio;
			gasto.fechaGasto.mes=aux_mes;
			gasto.fechaGasto.dia=aux_dia;
	
			
			printf("\nDesea registrar otro Pago?\n\n1. Si, aplicar seguir\n0. No, aplicar y finalizar : \t ");
			fflush(stdin);
			scanf("%d", &seguir);
			while((seguir != 1) && (seguir != 0)){
				system("cls");
				printf("\nOpcion invalida. Intentelo de nuevo. Ingrese un numero valido del 1-0 de tipo entero.\n");
				printf("\nDesea registrar otro Pago?\n\n1. Si, aplicar seguir\n0. No, aplicar y finalizar : \t ");
				fflush(stdin);
				scanf("%d", &seguir);
			}
			if(!seguir){
				s = 0;
				gasto.cuotaActual+=(int)ceil(pago.importe/(gasto.monto/Cuotas));
				gasto.monto-=pago.importe;
				
				fseek(arch, -(long)sizeof(gasto), SEEK_CUR);
				fwrite(&gasto,sizeof(gasto),1,arch);
				
				archp=fopen("pagos.dat","ab");
				fwrite(&pago,sizeof(pago),1,archp);
				fclose(arch);
				fclose(archp);
			}
			gasto.cuotaActual+=(int)ceil(pago.importe/(gasto.monto/Cuotas));
			gasto.monto-=pago.importe;
			
			fseek(arch, -(long)sizeof(gasto), SEEK_CUR);
			fwrite(&gasto,sizeof(gasto),1,arch);
			
			pago.fechaPago=gasto.fechaGasto;
			pago.codGasto=1;
			
			fclose(arch);
			if((archp=fopen("pagos.dat","ab"))==NULL){
				printf("\nError al abrir el archivo");
			}else{
				
				
				
				fwrite(&pago,sizeof(pago),1,archp);
				
				fclose(archp);
			}
			
			
			
			
		}
		
	}
}

/////////////////////////////////////////LISTAR GASTOS E INGRESOS///////////////////////////////////////////////////////////////////////////////////

void listarGastoseIngresos(){
	
	int opc, s=1, seguir;
	
	while(s){
		printf("\nEscoja de que forma desea filtrar los datos:\n\n1. Filtrar Por Tipo\n2. Filtrar por Categoria\n3. Filtrar por Mes\n4. Volver al Menu Principal\n\nElija una opcion: ");
		fflush(stdin);
		scanf("%d",&opc);
		switch(opc){
			case 1:
				system("cls");
				printf("---------\n1. FILTRAR POR TIPO\n---------");
				//Filtrar Por Tipo...
				filtrarPorTipo();
				break;
			case 2:
				system("cls");
				printf("---------\n2. FILTRAR POR CATEGORIA\n---------");
				//Filtrar Por Categoria...
				filtrarPorCategoria();
				break;	
			case 3:
				system("cls");
				printf("---------\n3. FILTRAR POR MES\n---------");
				filtrarPorMes();
				break;
			case 4:	
				printf("\nVOLVIENDO .....\n\n");
				s=0;
				break;	
			default:
				printf("\nIngrese un numero valido del 1-4 de tipo entero\n\n");			
		}
		
		if(s){
			if((opc >= 1) && (opc <= 3)){
				system("cls");
				printf("\nDesea realizar otro listado?\n\n1. Si, cargar siguiente\n0. No, finalizar : \t ");
				fflush(stdin);
				scanf("%d", &opc);
				while((opc != 1) && (opc != 0)){
					system("cls");
					printf("\nOpcion invalida. Intentelo de nuevo. Ingrese un numero valido del 1-0 de tipo entero.\n");
					printf("\nDesea realizar otro listado?\n\n1. Si, cargar siguiente\n0. No, finalizar : \t ");
					fflush(stdin);
					scanf("%d", &opc);
				}
				if(!opc){
					s = 0;
				}
			}
		}
		
	}
}

/////////////////////////////////////////CONSULTAS Y REPORTES///////////////////////////////////////////////////////////////////////////////////////

void consultasyReportes(){
		int opc, s=1, seguir;
	while(s){
		printf("\nEscoja la consulta/reporte a realizar:\n\n1. Gastos por Categoria\n2. Gastos Por Mes y Anio\n3. Ingresos Por Persona\n4. Saldo Mensual\n5. Gastos Pendientes\n6. Pagos Por Medio de Pago\n7. Gastos con Saldo Incompleto\n8. Top 3 Categorias Mas Costosas\n9. Proyeccion Mensual\n10. Resumen General\n11. Volver al Menu Principal\n\nElija una opcion: ");
		fflush(stdin);
		scanf("%d",&opc);
		switch(opc){
			case 1:
				system("cls");
				printf("---------\n1. GASTOS POR CATEGORIA\n---------");
				//Gastos por Categoria...
				gastosPorCategoria();
				break;
			case 2:
				system("cls");
				printf("---------\n2. GASTOS POR MES Y ANIO\n---------");
				//Gastos Por Mes y Anio...
				gastosPorMesYAnio();
				break;	
			case 3:
				system("cls");
				printf("---------\n3. INGRESOS POR PERSONA\n---------");
				//Ingresos Por Persona...
				ingresosPorPersona();
				break;
			case 4:
				system("cls");
				printf("---------\n4. SALDO MENSUAL\n---------");
				//Saldo Mensual...
				saldoMensual();
				break;
			case 5:
				system("cls");
				printf("---------\n5. GASTOS PENDIENTES\n---------");
				//Gastos Pendientes...
				gastosPendientes();
				break;
			case 6:
				system("cls");
				printf("---------\n6. PAGOS POR MEDIO DE PAGO\n---------");
				//Pagos por Medio de Pago...
				pagosPorMedioDePago();
				break;
			case 7:
				system("cls");
				printf("---------\n7. GASTOS CON SALDO INCOMPLETO\n---------");
				//Gastos con Saldo Incompleto...
				gastosConSaldoIncompleto();
				break;
			case 8:
				system("cls");
				printf("---------\n8. TOP 3 CATEGORIAS MAS COSTOSAS\n---------");
				//Top 3 Categorias Mas Costosas...
				categoriasMasCostosas();
				break;
			case 9:
				system("cls");
				printf("---------\n9. PROYECCION MENSUAL\n---------");
				//Proyeccion Mensual...
				proyeccionMensual();
				break;
			case 10:
				system("cls");
				printf("---------\n10. RESUMEN GENERAL\n---------");
				//Resumen General...
				resumenGeneral();
				break;
			case 11:	
				printf("\nVOLVIENDO .....\n\n");
				s=0;
				break;	
			default:
				printf("\nIngrese un numero valido del 1-11 de tipo entero\n\n");			
		}
		
		if(s){
			if((opc >= 1) && (opc <= 10)){
				system("cls");
				printf("\nDesea realizar otra consulta/reporte?\n\n1. Si, cargar siguiente\n0. No, finalizar : \t ");
				fflush(stdin);
				scanf("%d", &opc);
				while((opc != 1) && (opc != 0)){
					system("cls");
					printf("\nOpcion invalida. Intentelo de nuevo. Ingrese un numero valido del 1-0 de tipo entero.\n");
					printf("\nDesea realizar otra consulta/reporte?\n\n1. Si, cargar siguiente\n0. No, finalizar : \t ");
					fflush(stdin);
					scanf("%d", &opc);
				}
				if(!opc){
					s = 0;
				}
			}
		}
		
	}
}

/////////////////////////////////////////AGREGAR CATEGORIA//////////////////////////////////////////////////////////////////////////////////////////

void agregarCategoria(){
}

//*****************************************BUSCAR ID GASTO***********************************************************************************************

unsigned long long buscar_idGasto(){
    FILE *arch;
    unsigned long long ret=1 ,max_id = 0;
    Gasto gasto_temp;
    
    if((arch = fopen("gastos.dat", "rb")) != NULL){
        // Buscar el ID máximo en todos los registros
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
    // Si el archivo no existe o está vacío, empezar desde 1
    return ret;
}

//*****************************************BUSCAR ID CATEGORIA***********************************************************************************************

unsigned long long buscar_idCategoria(){
	FILE *arch1;
    unsigned long long ret1=1 ,max_id1 = 0;
    Gasto gasto_temp1;
    
    if((arch1 = fopen("gastos.dat", "rb")) != NULL){
        // Buscar el ID máximo en todos los registros
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
    // Si el archivo no existe o está vacío, empezar desde 1
    return ret1;
}

//*****************************************BUSCAR ID CATEGORIA***********************************************************************************************

unsigned long long buscar_idIngreso(){
	FILE *f6;
    unsigned long long ret2=1 ,max_id2 = 0;
    Ingreso ingreso_temp2;
    
    if((f6 = fopen("ingresos.dat", "rb")) != NULL){
        // Buscar el ID máximo en todos los registros
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
    // Si el archivo no existe o está vacío, empezar desde 1
    return ret2;
}

//***************************************GUARDAR GASTO***************************************************************************************

void guardarGasto(Gasto gasto){
	
	FILE *f4;
	
	if((f4=fopen("gastos.dat","ab"))==NULL){
		printf("\nError al abrir el archivo");
	}else{
		
		fwrite(&gasto,sizeof(gasto),1,f4);
		
		if((f4=fopen("Cuotas.dat","ab"))==NULL){
		
		fclose(f4);
	}
	
	
}
}
//***************************************COMPROBAR FECHA**********************************************************************************

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
    return verif; /* 0 = vÃ¡lido, 1 = invÃ¡lido */
	
}

//***************************************VER GASTOS***********************************************************************************
void ver_arch_gastos(){//Solo para visualizar el archvo de gastos.dat borrar luego
	int auxx;
	FILE *f;
	system("cls");
	if((f=fopen("gastos.dat","rb"))==NULL){
		printf("Error de apertura de archivo");
	}else{
		fread(&gasto,sizeof(gasto),1,f);
		
		while(!feof(f)){
			
			printf("\nEl codigo gasto: %llu",gasto.codGasto);//hacer para que sea PK (primary key) no hacer asi
			auxx=gasto.tipoGasto;
			switch (auxx){
					case 1:
						printf("\nEl Tipo de Gasto Es Fijo");
						auxx=0;
						break;
					case 2:
						printf("\nEl Tipo de Gasto Ocasional");
						auxx=0;
						break;
					case 3:
						printf("\nEl Tipo de Gasto Temporal");
						auxx=0;
						break;
					case 4:
						printf("\nEl Tipo de Gasto Anual");
						auxx=0;
						break;
			}
			printf("\nLa descripcion es: %s",gasto.desc);
			
			printf("\nEl ID De La Categoria es: %llu",gasto.categoria.codigo);
			printf("\nEl monto es: %lf",gasto.monto);
			printf("\nLa fecha es \nanio: %d\nmes: %d\ndia: %d",gasto.fechaGasto.anio,gasto.fechaGasto.mes,gasto.fechaGasto.dia);
			printf("\nLas cuotas totales es: %d",gasto.cuotasTotales);
			printf("\nLa Cuota Actual es: %d",gasto.cuotaActual);
			printf("\nEl DNI de la persona es: %lld\n",gasto.persona.dni);
			printf("\nEl Nombre de la persona es: %s\n",gasto.persona.nombre);
			
			
			fread(&gasto,sizeof(gasto),1,f);
			
		}
		fclose(f);
	}
	system("PAUSE");
}

//***************************************GUARDAR INGRESO**************************************************************************************
void guardarIngreso(Ingreso ingreso){
	FILE *f5;
	if((f5=fopen("ingresos.dat","ab"))==NULL){
		printf("\nError al abrir el archivo");
	}else{
		
		fwrite(&ingreso,sizeof(ingreso),1,f5);
		fclose(f5);
	}
	
}
//***************************************VER INGRESOS**************************************************************************************
void ver_arch_ingresos(){//Solo para visualizar el archvo de ingresos.dat borrar luego
	
	FILE *f1;
	system("cls");
	if((f1=fopen("ingresos.dat","rb"))==NULL){
		printf("Error de apertura de archivo");
		
	}else{
		
		fread(&ingreso,sizeof(ingreso),1,f1);
		while(!feof(f1)){
			
			printf("\nEl ID es: %llu",ingreso.codIngreso);
			printf("\nEl concepto es: %s",ingreso.concepto);
			printf("\nEl monto es: %lf",ingreso.monto);
			printf("\nLa fecha es \nanio: %d\nmes: %d\ndia: %d",ingreso.fecha.anio,ingreso.fecha.mes,ingreso.fecha.dia);
			printf("\nEl DNI de la persona es: %lld\n",ingreso.persona.dni);
			
			
			fread(&ingreso,sizeof(ingreso),1,f1);
			
		}
		
		
		
		fclose(f1);
	}
	system("PAUSE");
}

void ver_arch_pagos(){
	
	FILE *f1;
	system("cls");
	if((f1=fopen("pagos.dat","rb"))==NULL){
		printf("Error de apertura de archivo");
		
	}else{
		
		fread(&pago,sizeof(pago),1,f1);
		while(!feof(f1)){
			
			printf("\nEl codigo del gasto es: %llu",pago.codGasto);
			
			printf("\nEl medio de pago es: %s",pago.medioPago);
			
			printf("\nEl importe es: %lf",pago.importe);
			
			printf("\nLa fecha es \nanio: %d\nmes: %d\ndia: %d",pago.fechaPago.anio,pago.fechaPago.mes,pago.fechaPago.dia);
			
			
			fread(&pago,sizeof(pago),1,f1);
			
		}
		
		
		
		fclose(f1);
	}
	system("PAUSE");
}

//***************************************REGISTRO CATEGORIA*******************************************************************************************

void registroCategoria(char*Cad22){
	int x=1;
	
    while(x){
	   	
        printf("\n\nIngrese Un Nombre De Categoria Para El Gasto: ");
        //printf("\n\nzsdc ");
	    fflush(stdin);
	    gets(Cad22);
	            
	    if((strlen(Cad22)>49)||(Cad22[0]=='\0')||(Cad22[0]==32)){
	            	
	        system("cls");
	        printf("\nNo Se Permite Mas De 50 Caracteres En El Nombre De Categoria O Con Espacios Al Inicio, Por Favor, Vuelva A Ingresarlo\n\n");
	        system("PAUSE");
			system("cls");
			fflush(stdin);
	            	
		}else{
			Cad22[strcspn(Cad22, "\n")] = 0;
			x=0;
		}
	}
}

//***************************************LISTA CATEGORIAS*******************************************************************************************

int listaCategorias(){
	FILE*arch;
	unsigned long long idC1;
	int cc1;
	
	if((arch=fopen("gastos.dat","r+b"))==NULL){
		printf("\nError al abrir el archivo");
	}else{
		rewind(arch);
		cc1=0;
		printf("\n\nSeleccione Una Categoria Con El Numero De Codigo De Categoria, O Ingrese 0 Para Agregar Una Nueva Categoria\n");
		fread(&gasto,sizeof(Gasto),1,arch);
		while(!feof(arch)){
			cc1++;
			printf("\n%d.\tID De Categoria: %llu Categoria: %s\n",cc1,gasto.categoria.codigo,gasto.categoria.nombre);
			fread(&gasto,sizeof(Gasto),1,arch);
		}				
	}
	return cc1;
}


//***************************************FILTRAR POR TIPO*******************************************************************************************
void filtrarPorTipo(){
}

//***************************************FILTRAR POR CATEGORIA**************************************************************************************
void filtrarPorCategoria(){
}

//***************************************FILTRAR POR MES********************************************************************************************
void filtrarPorMes(){
	
	int opc, s=1, seguir;
	
	while(s){
		printf("\nEscoja el mes:\n\n1. Enero\n2. Febrero\n3. Marzo\n4. Abril\n5. Mayo\n6. Junio\n7. Julio\n8. Agosto\n9. Septiembre\n10. Octubre\n11. Noviembre\n12. Diciembre\n13. Salir\n\nElija una opcion: ");
		fflush(stdin);
		scanf("%d",&opc);
		switch(opc){
			case 1:
				system("cls");
				filtroPorMes(1);
				break;
			case 2:
				system("cls");
				filtroPorMes(2);
				break;	
			case 3:
				system("cls");
				filtroPorMes(3);
				break;
			case 4:	
				filtroPorMes(4);
				break;	
			case 5:	
				filtroPorMes(5);
				break;
			case 6:	
				filtroPorMes(6);
				break;
			case 7:	
				filtroPorMes(7);
				break;
			case 8:	
				filtroPorMes(8);
				break;
			case 9:	
				filtroPorMes(9);
				break;
			case 10:	
				filtroPorMes(10);
				break;
			case 11:	
				filtroPorMes(11);
				break;
			case 12:	
				filtroPorMes(12);
				break;
			case 13:
				printf("\nCANCELANDO .....\n\n");
				s=0;
				break;								
			default:
				printf("\nIngrese un numero valido del 1-13 de tipo entero\n\n");			
		}
		
		if(s){
			if((opc >= 1) && (opc <= 12)){
				printf("\nDesea realizar otro filtrado por mes?\n\n1. Si, cargar siguiente\n0. No, finalizar : \t ");
				fflush(stdin);
				scanf("%d", &opc);
				while((opc != 1) && (opc != 0)){
					system("cls");
					printf("\nOpcion invalida. Intentelo de nuevo. Ingrese un numero valido del 1-0 de tipo entero.\n");
					printf("\nDesea realizar otro filtrado por mes?\n\n1. Si, cargar siguiente\n0. No, finalizar : \t ");
					fflush(stdin);
					scanf("%d", &opc);
				}
				if(!opc){
					s = 0;
				}
			}
		}
		
	}
	
}

//***************************************GASTOS POR CATEGORIA***************************************************************************************
void gastosPorCategoria(){
}

//***************************************GASTOS POR MES Y ANIO**************************************************************************************
void gastosPorMesYAnio(){
}

//***************************************INGRESOS POR PERSONA***************************************************************************************
void ingresosPorPersona(){
}

//***************************************SALDO MENSUAL**********************************************************************************************
void saldoMensual(){
}

//***************************************GASTOS PENDIENTES******************************************************************************************
void gastosPendientes(){
}

//***************************************PAGOS POR MEDIO DE PAGO***********************************************************************************
void pagosPorMedioDePago(){
}

//***************************************GASTOS CON SALDO INCOMPLETO********************************************************************************
void gastosConSaldoIncompleto(){
}

//***************************************CATEGORIAS MAS COSTOSAS************************************************************************************
void categoriasMasCostosas(){
}

//***************************************PROYECCION MENSUAL*****************************************************************************************
void proyeccionMensual(){
}

//***************************************RESUMEN GENERAL********************************************************************************************
void resumenGeneral(){
}

//---------------------------------------FILTRO POR MES---------------------------------------------------------------------------------------------
void filtroPorMes(int){
}

//---------------------------------------DIGITOS----------------------------------------------------------------------------------------------------

int digitos(char*r) {
	int i,ret1=0,ccc=0;
	
    // Verificar que TODOS los caracteres sean dígitos
    for (i = 0; r[i] != '\0'; i++) {
        if (r[i] < '0' || r[i] >'9') {
            ccc++; // Carácter no numérico encontrado
        }
    }
    if(ccc==0){
    	ret1=atoi(r);
	}
    fflush(stdin);
    return ret1; // Todos los caracteres son dígitos
}

//---------------------------------------DIGITOS DNI-----------------------------------------------------------------------------------------------------

long long digitosDNI(char*j) {
	int k,ret3=0,con=0;
	
    // Verificar que TODOS los caracteres sean dígitos
    for (k = 0; j[k] != '\0'; k++) {
        if (j[k] < '0' || j[k] > '9') {
            con++; // Carácter no numérico encontrado
        }
    }
    if(con==0){
    	ret3=atoi(j);
	}
    fflush(stdin);
    return ret3; // Todos los caracteres son dígitos
}

/////////////////////////////////////////FIN////////////////////////////////////////////////////////////////////////////////////////////////////////
