// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ 4000000
#include <xc.h>

//funciones a utilizar
void puertos(void);
void semaforo(void);
//declaracion de variables
unsigned char x=1;
unsigned int j1=0;
unsigned int j2=0;
void main(void) {
    puertos();//ejecuta la funcion para configurar los puertos
    x=1;
    while(1){
    if (PORTAbits.RA2==0){semaforo();x=0;j1=1;PORTC=1;j2=1; PORTD=1;}//comprueba si se presiona el boton 1 y ejecuta la funcion de semaforo iniciando el juego
    if (PORTAbits.RA0==0 && x==0){//comprueba el segundo boton y el jugador 1 se mueve
        __delay_ms(100);
        if(PORTAbits.RA0==1){
            j1=j1*2;//el valor de j1 se multiplica por 2 y luego el valor se carga en el puerto c
            PORTC=j1;    
        }
        else if(PORTAbits.RA1==0){
         __delay_ms(100);
         if(PORTAbits.RA1==1){
             j2=j2*2;//el valor de j2 se multiplica por 2 y luego el valor se carga en el puerto d
             PORTD=j2;
         }
        }}
    if (PORTAbits.RA1==0 && x==0){
        __delay_ms(100);
        if(PORTAbits.RA1==1){
            j2=j2*2;//el valor de j2 se multiplica por 2 y luego el valor se carga en el puerto d
            PORTD=j2;    
        }
        else if(PORTAbits.RA0==0){
         __delay_ms(100);
         if(PORTAbits.RA0==1){
             j1=j1*2;//el valor de j1 se multiplica por 2 y luego el valor se carga en el puerto c
             PORTC=j1;
         }
        }}
    if(j1==256){PORTB=0B0000110; x=1;PORTAbits.RA3=1;}//comprueba si j1 termino la carrera, si es asi enciende el bit RA3 y en el display muestra el numero 1
    else if (j2==256){PORTB=0B1011011; x=1;PORTAbits.RA4=1;}//comprueba si j2 termino la carrera, si es asi enciende el bit RA4 y en el display muestra el numero  2
    }
    return;
}
//funcion para configurar los puertos
void puertos(void){
    // puerto B,C,D y E como salida, RA0, RA1, RA2 como entrada
    TRISA=0B00000111;
    TRISB=0;
    TRISC=0;
    TRISD=0;
    TRISE=0;
    ANSEL=0; //todos los puertos en digital
    ANSELH=0;
    PORTA=0; // iniciar los puertos en 0
    PORTB=0;
    PORTC=0;
    PORTD=0;
    PORTE=0;
}
//funcion que realiza el conteo y el semaforo
void semaforo(void){
    PORTAbits.RA3=0;
    PORTAbits.RA4=0;
    PORTC=0;
    PORTD=0;
    PORTE=0b001; //led rojo
    PORTB=0B1001111;//numero 3
    __delay_ms(1000);
    PORTE=0B010;// led amarillo
    PORTB=0B1011011;//numero 2
    __delay_ms(1000);
    PORTE=0B100;// led verde
    PORTB=0B0000110;//numero 1
    __delay_ms(1000);
    PORTE=0B000; // apagar todos
    PORTB=0B00111111;// numero 0
    return;
}