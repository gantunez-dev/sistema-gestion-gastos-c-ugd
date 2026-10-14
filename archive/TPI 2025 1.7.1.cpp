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
	
	unsigned long long id;
	long long dni;
	char nombre[50];
	
} Persona;

typedef struct{
	
	unsigned long long codGasto;
	char tipoGasto[50];
	char desc[50];
	Categoria categoria;
	double monto;
	Fecha fechaGasto;
	int cuotasTotales;
	int cuotasPagadas;
	Persona persona;
	
} Gasto;

typedef struct{
	
	unsigned long long codGasto;
	char medioPago[40];
	double importe;
	Fecha fechaPago;
	
} Pago;

typedef struct{
	
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

//CARGAR INGRESO
void guardarIngreso(Ingreso ingreso);
int comprobacion_fecha(int aux_anio,int aux_mes,int aux_dia);
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


int main(){
	
	
	int opc,s=1;
	while (s){
		system("cls");
		printf("\nSistema de Gestion de Gastos Personales o Familiares\n--------MENU PRINCIPAL--------\n\n1. Registrar Gasto\n2. Registrar Ingreso\n3. Registrar Pago\n4. Listar Gastos e Ingresos\n5. Consultas y Reportes\n6. Salir\n\nElija una opcion: ");
		fflush(stdin);
		scanf("%d",&opc);
		switch (opc){
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
				s=0;
				break;				
			default:
				printf("\nIngrese un numero valido del 1-6 de tipo entero\n\n");
				system("PAUSE");
		}
	}
	return 0;
}

/////////////////////////////////////////REGISTRAR GASTO//////////////////////////////////////////////////////////////////////////////////////////

void cargarGasto(){
    FILE *f2;
    int s=1, c=1, aux_anio, aux_mes, aux_dia,opc,cnt=1;
    unsigned long long id;
    char Cad2[50];
    
    while(s){
        if((f2 = fopen("gastos.dat", "ab")) == NULL){
            printf("\nError al abrir el archivo");
        } else {
            // Obtener el próximo ID disponible
            id = buscar_idGasto();
            gasto.codGasto = id;
            
            while(cnt){
            	
            	system("cls");
	            printf("\nIngresar el tipo de gasto\n\n1. Gasto Fijo\n2. Gasto Ocacional\n3. Gasto Temporal\n4. Gasto Anual\n\nElija una opcion: ");
	            fflush(stdin);
	            scanf("%d",&opc);
	            
	            system("cls");
	            printf("\nID de gasto asignado: %llu", id); // Para debug
	            
	            switch (opc){
					case 1:
						strcpy(gasto.tipoGasto,"Fijo");
						cnt=0;
						break;
					case 2:
						strcpy(gasto.tipoGasto,"Ocacional");
						cnt=0;
						break;
					case 3:
						strcpy(gasto.tipoGasto,"Temporal");
						cnt=0;
						break;
					case 4:
						strcpy(gasto.tipoGasto,"Anual");
						cnt=0;
						break;					
					default:
						system("cls");
						printf("\nIngrese un numero valido del 1-4 de tipo entero\n\n");
						system("PAUSE");
				}
            }
			
			printf("\n\nTipo de Gasto: %s", gasto.tipoGasto); // Para debug

            printf("\n\nIngresar una descripcion breve del gasto:");
            fflush(stdin);
            fgets(Cad2, 50, stdin);
            Cad2[strcspn(Cad2, "\n")] = 0;
            strcpy(gasto.desc, Cad2);
            
            printf("\nIngresar el nombre de la categoria del gasto: ");
            fflush(stdin);
            fgets(Cad2, 50, stdin);
            Cad2[strcspn(Cad2, "\n")] = 0;
            strcpy(gasto.categoria.nombre, Cad2);
            
            printf("\nIngresar el monto:");
            scanf("%lf", &gasto.monto);
            
            // Resto del código para fecha, cuotas, persona...
            c = 1;
            while(c){
                printf("\nIngresado de fecha");
                printf("\nIngresar el anio (formato numero largo, ej: 2006):");
                scanf("%d", &aux_anio); 
                
                printf("\nIngresar el mes (formato numero, ej: 11):");
                scanf("%d", &aux_mes);
                
                printf("\nIngresar el dia:");
                scanf("%d", &aux_dia);
                
                c = comprobacion_fecha(aux_anio, aux_mes, aux_dia);
                if(c == 1){
                    printf("\nSe ha ingresado mal la fecha. Por favor, volver a ingresarla");
                }
            }
            
            gasto.fechaGasto.anio = aux_anio;
            gasto.fechaGasto.mes = aux_mes;
            gasto.fechaGasto.dia = aux_dia;
            
            printf("\nIngresar Cuotas totales:");
            scanf("%d", &gasto.cuotasTotales);
            
            printf("\nIngresar cuotas pagadas:");
            scanf("%d", &gasto.cuotasPagadas);
            
            printf("\nIndicar el DNI de la persona:");
            scanf("%llu", &gasto.persona.dni);
            
            printf("\nIngresar el nombre de la persona:");
            fflush(stdin);
            fgets(Cad2, 50, stdin);
            Cad2[strcspn(Cad2, "\n")] = 0;
            strcpy(gasto.persona.nombre, Cad2);
            
            // Escribir el gasto en el archivo
            fwrite(&gasto, sizeof(Gasto), 1, f2);
            fclose(f2);
            
            printf("\nGasto guardado con ID: %llu", id);
            
            printf("\nDesea cargar mas Gastos? (1 si, 0 no):");
            scanf("%d", &s);
        }
    }
}

/////////////////////////////////////////REGISTRAR INGRESO//////////////////////////////////////////////////////////////////////////////////////////
void cargarIngreso(){
	char Cad1[100];
	FILE *f1;
	int N=123,i1,s=1,c=1;
	int aux_anio,aux_mes,aux_dia;
	if((f1=fopen("ingresos.dat","ab"))==NULL){
		printf("\nError al abrir el archivo");
	}else{
		
		fclose(f1);
		
		while(s){
			if((f1=fopen("ingresos.dat","ab"))==NULL){
				printf("\nError al abrir el archivo");
			}else{
				
				
				printf("\nIngresar el concepto del ingreso:");
				fflush(stdin);
				gets(Cad1);
				strcpy(ingreso.concepto,Cad1);
				
				printf("\nIngresar el monto:");
				fflush(stdin);
				scanf("%lf",&ingreso.monto);
				
				c=1;
				while(c){
					printf("\nIngresado de fecha");
					printf("\nIngresar el anio (formato numero largo, ej: 2006):");
					fflush(stdin);
					scanf("%d",&aux_anio); 
					
					printf("\nIngresar el mes (formato numero, ej: 11):");
					fflush(stdin);
					scanf("%d",&aux_mes);
					
					printf("\nIngresar el dia:");
					fflush(stdin);
					scanf("%d",&aux_dia);
					
					c=comprobacion_fecha(aux_anio,aux_mes,aux_dia);
					if(c==1){
						printf("\nSe ha ingresado mal la fecha. Por favor, volver a ingresarla");
					}
				}
				ingreso.fecha.anio=aux_anio;
				ingreso.fecha.mes=aux_mes;
				ingreso.fecha.dia=aux_dia;
				
				printf("\nIngresar el nombre de la persona:");
				fflush(stdin);
				gets(Cad1);
				strcpy(ingreso.persona.nombre,Cad1);
				
				printf("\nIngresar el DNI de la persona:");
				fflush(stdin);
				scanf("%llu",&ingreso.persona.dni);
				
				
				fclose(f1);
				
				guardarIngreso(ingreso);
				
				
				
				printf("\nDesea ingresar mas ingresos? (1 si, 0 no):");
				fflush(stdin);
				scanf("%d",&s);
				
			
				
			}
			
			
		}
		
		printf("\nDatos cargados correctamente");
	}
	
}

/////////////////////////////////////////REGISTRAR PAGO/////////////////////////////////////////////////////////////////////////////////////////////
void registrarPago(){
	int s=1,encontro=1,seguir,vf1,vf2,Cuotas,c;
	int aux_anio,aux_mes,aux_dia;
	unsigned long long aux;
	FILE*arch,*archp;
	int cc=0;
	double aux_1,aux_2;
	while(s){
	    system("cls");
		printf("---------\n1. REGISTRO DE PAGO Y ACTUALIZACION DE GASTO\n---------");
		fflush(stdin);
		printf("---------\n1. Lista De Pagos Pendientes\n---------");
		
		if((arch=fopen("gastos.dat","rb+"))==NULL){
			printf("\nError al abrir el archivo");
		}else{
			cc=0;
			fread(&gasto,sizeof(gasto),1,arch);
			while(!feof(arch)){
			
				if((gasto.cuotasTotales!=gasto.cuotasPagadas)&&(gasto.monto>0)){
					Cuotas=(gasto.cuotasTotales-gasto.cuotasPagadas);
					cc++;
					aux_1= gasto.monto / gasto.cuotasTotales;
					aux_2=(gasto.monto - (gasto.cuotasPagadas*aux_1));
					printf("\n%d.\tCodigo: %llu El Monto A Pagar Restante Es De $%lf, En %d cuotas de %lf, Hecho Por La Persona %lld, Es Un Gasto %s, Con Un Descripcion De %s, Pertenece A La Categoria %s, Tomado En La Fecha %d / %d / %d\n",cc,gasto.codGasto,aux_2,Cuotas,aux_1,gasto.persona.dni,gasto.tipoGasto,gasto.desc,gasto.categoria.nombre,gasto.fechaGasto.dia,gasto.fechaGasto.mes,gasto.fechaGasto.anio);
				}
				fread(&gasto,sizeof(gasto),1,arch);
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
			printf("\n\nIngrese El Id Del Responsable Del Pago: ");
			fflush(stdin);
			scanf("%llu",&aux);
			
			vf2=1;
			while(vf2){
				if(aux<1){
					printf("\n\nNo Ingrese Un Valor Negativo O Igual A 0, Debe Ser Positivo, Mayor Y Entero\n\nIngrese El Id Del Responsable Del Pago: ");
					fflush(stdin);
					scanf("%llu",&aux);
				}else{
					vf2=0;	
				}
			}
			
			system("cls");
			printf("\n\nIngrese El Medio De Pago\n\nTarjeta\nTransferencia\nQR\nEfectivo\nNFC\t: ");
			fflush(stdin);
			gets(pago.medioPago);
		
			vf2=1;
			while(vf2){
				if((strcmp(pago.medioPago,"tarjeta")!=0)&&(strcmp(pago.medioPago,"transferencia")!=0)&&(strcmp(pago.medioPago,"qr")!=0)&&(strcmp(pago.medioPago,"efectivo")!=0)){
					printf("\n\nIngrese El Tipo De Manera Correcta\n\nTarjeta\nTransferencia\nQR\nEfectivo\nNFC\t: ");
					fflush(stdin);
					gets(pago.medioPago);
				}else{
					vf2=0;	
				}
			}
			
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
				gasto.cuotasPagadas+=(int)ceil(pago.importe/(gasto.monto/Cuotas));
				gasto.monto-=pago.importe;
				
				fseek(arch, -(long)sizeof(gasto), SEEK_CUR);
				fwrite(&gasto,sizeof(gasto),1,arch);
				
				archp=fopen("pagos.dat","ab");
				fwrite(&pago,sizeof(pago),1,archp);
				fclose(arch);
				fclose(archp);
			}
			gasto.cuotasPagadas+=(int)ceil(pago.importe/(gasto.monto/Cuotas));
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
//*****************************************BUSCAR ID***********************************************************************************************
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
    }
    // Si el archivo no existe o está vacío, empezar desde 1
    return ret;
}
//***************************************GUARDAR GASTO***************************************************************************************
void guardarGasto(Gasto gasto){
	
	FILE *f4;
	
	if((f4=fopen("gastos.dat","ab"))==NULL){
		printf("\nError al abrir el archivo");
	}else{
		
		fwrite(&gasto,sizeof(gasto),1,f4);
		fclose(f4);
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

    return verif; /* 0 = vÃ¡lido, 1 = invÃ¡lido */
	
}

//***************************************VER GASTOS***********************************************************************************
void ver_arch_gastos(){//Solo para visualizar el archvo de gastos.dat borrar luego
	
	FILE *f;
	system("cls");
	if((f=fopen("gastos.dat","rb"))==NULL){
		printf("Error de apertura de archivo");
	}else{
		fread(&gasto,sizeof(gasto),1,f);
		
		while(!feof(f)){
			
			printf("\nEl codigo gasto: %llu",gasto.codGasto);//hacer para que sea PK (primary key) no hacer asi
			printf("\nEl tipo de gasto es: %s",gasto.tipoGasto);
			printf("\nLa descripcion es: %s",gasto.desc);
			printf("\nEl nombre de la categoria es: %s",gasto.categoria.nombre);
			printf("\nEl monto es: %lf",gasto.monto);
			printf("\nLa fecha es \nanio: %d\nmes: %d\ndia: %d",gasto.fechaGasto.anio,gasto.fechaGasto.mes,gasto.fechaGasto.dia);
			printf("\nLas cuotas totales es: %d",gasto.cuotasTotales);
			printf("\nLas cuotas pagadas es: %d",gasto.cuotasPagadas);
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

/////////////////////////////////////////FIN////////////////////////////////////////////////////////////////////////////////////////////////////////
