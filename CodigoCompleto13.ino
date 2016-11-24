#include <LCD5110_Basic.h> //LCD5110
#include <avr/pgmspace.h> //PROGMEM
#include <EEPROM.h> //EEPROM
#include <DS3231.h>
DS3231  rtc(SDA, SCL);
Time  t;


// Provisoria
// Provisoria
byte roteiro0[]={3,4,4,4,3,3,3,3,4};//{3,3,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
//byte roteiro1[]={3,4,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4,3,4}; //alfabeto - usa todos caracteres e vai até t
//byte roteiro2[]={3,4,4,3,4,3,4,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4};
//byte roteiro3[]={3,4,4,3,3,4,3,3,3,3,3,3,3,4,2,2,2,2,2,2,2,2,4,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,}; //bia
// Provisoria
// Provisoria

 //teclado
 //teclado
     byte botao = 0; // qual botao foi apertado
    float tecladotensao = 0; // valor de tensao da leitura 0-5V (valor da leitura do teclado 0-1024)
    #define tecladodelay 300 // tempo que a pessoa segura um botao ao apertar, passando esse tempo o botao aperta 2x
    #define tecladopino A1    // pino que esta ligado o teclado
    #define tecladobotao1 3.5 // valor medido de tensao para o botao 1 - sem resistencia
    #define tecladobotao2 2.5 // valor medido de tensao para o botao 2 - 3R terra e 1R botao
    #define tecladobotao3 1.5 // valor medido de tensao para o botao 3 - 1R terra e 1R botao
    #define tecladobotao4 0.50 // valor medido de tensao para o botao 4 - 1R terra e 3R botao
    byte mouse = 0; int tempomouseon = 500; int tempomouseoff = 1400; unsigned long tempomouse=0;
    static const char caracteres[] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@,.-_0123456789 "};
    byte posicaoteclado = 0;
    byte posicaocaracteres = 0;
    char buffer[200];
        //Iniciando variaveis dos menus
        byte menu = 0;
        byte submenu = 0;
        byte subsubmenu = 0;
        byte subsubsubmenu = 0;

    const char cor_0[] PROGMEM = "Sem cor";  
    const char cor_1[] PROGMEM = "Vermelho";
    const char cor_2[] PROGMEM = "Azul";
    const char cor_3[] PROGMEM = "Verde";
    const char cor_4[] PROGMEM = "Branco";
    const char cor_5[] PROGMEM = "Preto";

    const char* const tabelacores[] PROGMEM = {cor_0,cor_1,cor_2,cor_3,cor_4,cor_5};
 //teclado
 //teclado

 // variaveis gerais
 // variaveis gerais

struct PET{char nome[21]; char raca[21]; byte anivdia; byte anivmes; int anivano; byte tag; char dono[6]; byte vez1; byte vez2; byte vez3; byte minuto1; byte minuto2; byte minuto3; byte hora1; byte hora2; byte hora3; int dia1; int dia2; int dia3; int semana1; int semana2; int semana3; int mes1; int mes2; int mes3;};
PET PET0 = {"Nome do seu PET","Raca do seu PET",01,01,1950,0,"",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // Para usar quando carregar coisas do EEPROM
struct DONO{char nome[21]; char celular[12]; char email1[31]; char email2[31]; byte anivdia; byte anivmes; byte anivano; char pet[6];};
DONO DONO0 = {"Nome de um dono","","","",0,0,0,"12345"}; // Para usar quando carregar coisas do EEPROM

struct  HORARIO{byte hora; byte minuto;}; // ate 10 horarios**pode deixar uma constante pra definir isso
HORARIO HORARIO0 = {0,0};
struct AJUSTES{byte npets; byte ndonos; byte nhorarios; byte parar; byte encher; char ip[16]; char senha[30]; byte brilho; byte contraste;};
AJUSTES AJUSTES0 = {5,5,5,80,20,"","",60,255};

                  
// LCD5110
// LCD5110
    #define LCD5110_BL 6 // ligado com 220R
    #define LCD5110_CLK 7
    #define LCD5110_DIN 8
    #define LCD5110_DC 9
    #define LCD5110_CE 10
    #define LCD5110_RST 11
    int LCD5110_contraste = AJUSTES0.contraste; //60 é um bom balor
    int LCD5110_backlight_value = AJUSTES0.brilho; // 0-255 onde 255 Ã© 5V
    // LCD5110_VCC -> 5V
    // LCD5110_GND -> TERRA
    LCD5110 tela(LCD5110_CLK,LCD5110_DIN,LCD5110_DC,LCD5110_RST,LCD5110_CE);
    //Obtendo as fontes
        extern uint8_t SmallFont[];
        extern uint8_t MediumNumbers[];
        extern uint8_t BigNumbers[];
        extern uint8_t kidpet_logo[];
        extern uint8_t flechas[];
//LCD5110
//LCD5110

//RELOGIO
//RELOGIO
const byte totaldiasmes[] PROGMEM ={31,28,31,30,31,30,31,31,30,31,30,31};
//RELOGIO
//RELOGIO

byte totalhoras = 0;
byte totalsubmenu[]={7,8,8,8,8,8,5,5,5,5,5,1,1};
byte totalsubsubmenu0[]={4,4,4,4,1,AJUSTES0.npets,1,AJUSTES0.ndonos};//verificar
byte totalsubsubmenu15[]={sizeof(PET0.nome),sizeof(PET0.raca)};
byte totalsubsubmenu610[]={sizeof(DONO0.nome),sizeof(DONO0.celular),sizeof(DONO0.email1),sizeof(DONO0.email2)};
/*byte totalsubsubmenu11[]={8,3};
byte totalsubsubmenu12[]={1,1};
byte totalsubsubsubmenu110[]={1,9,1,totalhoras,4,4,4,4,4};
byte totalsubsubsubmenu111[]={1,1,9,9};
byte totalsubsubsubmenu120[]={19,29};
byte totalsubsubsubmenu121[]={19,19};*/
 // variaveis gerais
 // variaveis gerais
 byte flag=0;
 
void setup()
{

  
//teclado
//teclado
      Serial.begin(9600);
//teclado
//teclado

// Pegando o nome dos Cachorros da memoria interna
salvarajustes();//retirar na versão final
carregarajustes();


// LCD5110
// LCD5110
  
   // Outros
      pinMode(LCD5110_BL, OUTPUT); // usa resistor de 220 ohm
      analogWrite(LCD5110_BL,LCD5110_backlight_value);
  // Iniciando
      tela.InitLCD(LCD5110_contraste); //Inicializando o display com um valor de contraste
      tela.clrScr();
      tela.setFont(SmallFont);
      tela.print(F("1.0"),RIGHT,0);
      tela.print(F("My"),LEFT,0);
      tela.drawBitmap(0, 16, kidpet_logo, 84, 24);
      delay(4000);
      tela.clrScr();
  // Inicia tela
    rodamenu();
    tela.print(F("BEM-VINDO AO"),CENTER,0);
    tela.print(F("Escolha um Pet"),CENTER,40);


// LCD5110
// LCD5110

// TESTE
//for(byte k=0;k<sizeof(caracteres);k++){Serial.print("[k] = ");Serial.print(k);Serial.print(" caracteres[k] = "); Serial.println(caracteres[k]);}
 //for(int i=0;i<sizeof(roteiro0);i++){ Serial.print(" \\ i = ");Serial.print(i); botao=roteiro0[i];imprimir();delay(1000);}
}
  
void loop(){
apertarbotao();
tecladobotao();
mudamouse();
if(flag==1){EEprint2();flag=0;}
}

//********************************************************************** FUNCOES: DISPLAY**********************************************************************************
//********************************************************************** FUNCOES: BOTAO ***********************************************************************************


void apertarbotao(){
  float tecladotensao = 5*(analogRead(tecladopino))/1024;  
  if (tecladotensao > tecladobotao1) {botao = 1; imprimir();delay(tecladodelay);}
  else if (tecladotensao > tecladobotao2) {botao = 2; imprimir();delay(tecladodelay);}
  else if (tecladotensao > tecladobotao3) {botao = 3; imprimir();delay(tecladodelay);}
  else if (tecladotensao > tecladobotao4) {botao = 4; imprimir();delay(tecladodelay);}
 //    if(tecladotensao>0.3){Serial.print("AnalogRead: "); Serial.print(tecladotensao*1024/5); Serial.print("  //Tensao: ");Serial.print(tecladotensao); Serial.print("  //Botao: ");Serial.println(botao);}
if(botao!=0){flag=1;}
} //apertarbotao

void tecladobotao(){
  char botaoficticio=0;
  botao=0;
  if(Serial.available()>0){botaoficticio=Serial.read();   
  if (botaoficticio=='q'||botaoficticio=='Q') {botao = 1; delay(300);}
  else if (botaoficticio=='w'||botaoficticio=='W') {botao = 2; delay(300);}
  else if (botaoficticio=='e'||botaoficticio=='E') {botao = 3; delay(300);}
  else if (botaoficticio=='r'||botaoficticio=='R') {botao = 4; delay(300);}
  if(botao!=0){ Serial.print("botaoficticio: "); Serial.print(botaoficticio); Serial.print("  //botao: "); Serial.println(botao);}
}
if(botao!=0){flag=1;}
} 
//********************************************************************** FUNCOES: MOUSE PISCANDO  ***********************************************************************************

void mudamouse(){
static boolean i;
if(i==0&&(millis()-tempomouse)>tempomouseon){
switch(mouse){
             case 0: 
             case 1: tela.print(F(" "),0,8); break;
             case 2: if((menu>0&&menu<6&&submenu<2)||(menu>4&&menu<11&&submenu<4)){
                                                                                   tela.clrScr();
                                                                                   printmenu(menu,0);
                                                                                   printsubmenu(menu,submenu,1);
                                                                                   if(posicaoteclado<14){for(byte i=0;i<14;i++){tela.print(String(buffer[i]),i*6,16);}}
                                                                                   else if(posicaoteclado<28){for(byte i=0;i<14;i++){tela.print(String(buffer[14+i]),i*6,16);}}
                                                                                   else if(posicaoteclado<(sizeof(buffer)-1)){for(byte i=0;i<3;i++){tela.print(String(buffer[28+i]),i*6,16);}}
                                                                                  }
                     if(mouse==2&&((menu>0&&menu<6&&submenu==4)||(menu>5&&menu<11&&submenu==5))){tela.print(F(" "),0,16);} 
             break;
             }
//Serial.print("mouseoff"); Serial.print("  // tempomouse: "); 
tempomouse=millis(); i = !i; 
//Serial.println(tempomouse);             
}
if(i==1&&(millis()-tempomouse)>tempomouseoff){
switch(mouse){
              case 0: 
              case 1: tela.print(F("\\"),0,8); break;
              case 2: if((menu>0&&menu<6&&submenu<2)||(menu>4&&menu<11&&submenu<4)){
                                                                                   tela.clrScr();
                                                                                   printmenu(menu,0);
                                                                                   printsubmenu(menu,submenu,1);
                                                                                   if(posicaoteclado<14){for(byte i=0;i<14;i++){tela.print(String(buffer[i]),i*6,16);} tela.print(F("\\"),posicaoteclado*6,16);}
                                                                                   else if(posicaoteclado<28){for(byte i=0;i<14;i++){tela.print(String(buffer[14+i]),i*6,16);}tela.print(F("\\"),(posicaoteclado-14)*6,16);}
                                                                                   else if(posicaoteclado<(sizeof(buffer)-1)){for(byte i=0;i<3;i++){tela.print(String(buffer[28+i]),i*6,16);}tela.print(F("\\"),(posicaoteclado-28)*6,16);}
                                                                                    }
                      if(mouse==2&&((menu>0&&menu<6&&submenu==4)||(menu>5&&menu<11&&submenu==5))){tela.print(F("\\"),0,16);}
              break;
              }
//Serial.print("mouseon"); Serial.print("  // tempomouse: "); 
tempomouse=millis(); i = !i;  
//Serial.println(tempomouse);            
}
}

void informacoes(){
              //INFORMACOES
 /*             Serial.println("");
              Serial.print("INFORMACOES");
              Serial.print("  //BOTAO: "); Serial.print(botao); 
              Serial.print("  //Menu: "); Serial.print(menu); 
              Serial.print("  //Submenu: "); Serial.print(submenu); 
              Serial.print("  //Subsubmenu: "); Serial.print(subsubmenu);
              Serial.print("  //Mouse: "); Serial.print(mouse);
              Serial.print("  //Posicaocaracteres: "); Serial.print(posicaocaracteres);
              Serial.print("  //caracteres[posicaocaracteres]: "); Serial.print(caracteres[posicaocaracteres]);
              Serial.print("  //Posicaoteclado: "); Serial.print(posicaoteclado);
              Serial.print("  //buffer[posicaoteclado]: "); Serial.print(buffer[posicaoteclado]);
              Serial.print("  //Buffer: "); Serial.print(buffer);
              Serial.println("  //PET0.nome: "); Serial.println(PET0.nome);Serial.println("0123456789112345678921234567893");
              Serial.println("  //PET0.raca: "); Serial.println(PET0.raca);Serial.println("0123456789112345678921234567893");
              Serial.print("  //sizeof(PET0.nome): ");Serial.println(sizeof(PET0.nome));
              Serial.print("  //strlen(PET0.nome): ");Serial.println(strlen(PET0.nome));
              Serial.print("  //sizeof(PET0.raca): ");Serial.println(sizeof(PET0.raca));
              Serial.print("  //strlen(PET0.raca): ");Serial.println(strlen(PET0.raca));            
               Serial.print("  //sizeof(caracteres): "); Serial.print(sizeof(caracteres));
//              Serial.print("  //: "); Serial.print();*/
              Serial.println("");

  /*Serial.println(""); 
  Serial.println("AJUSTANDO POSICAO TEXTO Antes");
  Serial.print("posicao teclado : "); Serial.println(posicaoteclado);
  Serial.print("buffer[posicaoteclado] "); Serial.println(buffer[posicaoteclado]);
  Serial.print("strchr(caracteres,buffer[posicaoteclado]): "); Serial.println(strchr(caracteres,buffer[posicaoteclado]));
  Serial.print("int(strchr(caracteres,buffer[posicaoteclado])): "); Serial.println(int(strchr(caracteres,buffer[posicaoteclado])));
  Serial.print("&caracteres: "); Serial.println(&caracteres[0]);
  Serial.print("int(&caracteres: )"); Serial.println(int(&caracteres[0]));
  Serial.print("int(strchr(caracteres,buffer[posicaoteclado]))-int(&caracteres): ");   Serial.println(int(strchr(caracteres,buffer[posicaoteclado]))-int(&caracteres)); 
  Serial.print("posicaocaracters: "); Serial.println(posicaocaracteres);*/
}


//********************************************************************** FUNCOES: IMPRESSAO ***********************************************************************************
void imprimir(){
 Serial.println("");Serial.print("*********************************** BOTAO"); Serial.print(botao);Serial.println("**********************************************");
if(mouse==0){
            tela.clrScr(); rodamenu();tela.drawBitmap(0, 40, flechas, 84, 8); 
            return;
            }
if(mouse==1){tela.clrScr(); rodasubmenu();tela.drawBitmap(0, 40, flechas, 84, 8); return;}
if(mouse==2){tela.clrScr(); rodasubsubmenu();tela.drawBitmap(0, 40, flechas, 84, 8); return;}
}

//*********************************************************************** FUNCOES: IMPRESSAO MENU PRINCIPAL *******************************************************************
void rodamenu(){
Serial.println("  **RODAMENU-INICIO**  ");  
tela.clrScr();
tela.print(F("MENU PRINCIPAL"),CENTER,0);
for(byte i=0;i<4;i++){printmenu(menu+i,i+1);}
switch(botao){
              case 2: if(menu>0){menu--;}else{menu=12;} break;
              case 3: if(menu<12){menu++;}else{menu=0;}break;
              case 4: tela.clrScr();
                      botao=0;
                      mouse++;
                      rodasubmenu();
                      return;                                 
              break;
              }

tela.clrScr();
tela.print(F("MENU PRINCIPAL"),CENTER,0);              
for(byte i=0;i<4;i++){printmenu(menu+i,i+1);}
informacoes(); botao=0;
Serial.println("  **RODAMENU-FIM**  "); 
}
//**************************************************
void printmenu(byte nmenu, byte nlinha){
byte espaco; if(mouse==0&&nlinha==1){espaco=6;}else{espaco=0;}

tela.setFont(SmallFont); 
switch(nmenu){
case 0: 
case 13:tela.print(F("My KidPet"),espaco,nlinha*8); break;
case 14: 
case 15: carregar(nmenu-13,0); tela.print(PET0.nome,espaco,nlinha*8); break;
case 1: 
case 2: 
case 3: 
case 4: 
case 5: carregar(nmenu,0); tela.print(PET0.nome,espaco,nlinha*8); break;
case 6: 
case 7: 
case 8: 
case 9: 
case 10: carregar(0,nmenu-5); tela.print(DONO0.nome,espaco,nlinha*8); break;
case 11: tela.print(F("FUNCIONAMENTO"),espaco,nlinha*8); break;
case 12: tela.print(F("AJUSTES"),espaco,nlinha*8); break;
default: tela.print(F("ERRO"),espaco,nlinha*8); break;
} 
}
//*********************************************************************** FUNCOES: IMPRESSAO SUBMENU ****************************************************************************
void rodasubmenu(){
Serial.println("  **RODASUBMENU-INICIO**  ");

tela.clrScr();
printmenu(menu,0);
if(mouse==1){for(byte i=0;i<4;i++){if(submenu+i<totalsubmenu[menu]+1){printsubmenu(menu,submenu+i,i+1);}else{printsubmenu(menu,submenu+i-totalsubmenu[menu]-1,i+1);}}}else{printsubmenu(menu,submenu,1);} 

switch(botao){
              case 1: botao=0; mouse=0; submenu=0; rodamenu();return; break;
              case 2: if(submenu>0){submenu--;}else{submenu=totalsubmenu[menu];} break;
              case 3: if(submenu<totalsubmenu[menu]){submenu++;}else{submenu=0;} break;
              case 4: 
                      if(menu>0&&menu<6){
                                        switch(submenu){
                                                        case 0: carregar(menu,0); limpabuffer(); strcpy(buffer,PET0.nome); break;
                                                        case 1: carregar(menu,0); limpabuffer(); strcpy(buffer,PET0.raca); break;
//                                                      case 2: carregar(menu,0); strcpy(buffer,String(PET0.anivdia)); strcat(buffer,String(PET0.anivmes)); strcat(buffer,String(PET0.anivano)); break;                                                
                                                        }
                                        }
                       else if(menu<11){
                                        switch(submenu){
                                                        case 0: carregar(0,menu-5); limpabuffer(); strcpy(buffer,DONO0.nome); break;
                                                        case 1: carregar(0,menu-5); limpabuffer(); strcpy(buffer,DONO0.celular); break;
                                                        case 2: carregar(0,menu-5); limpabuffer(); strcpy(buffer,DONO0.email1); break;
                                                        case 3: carregar(0,menu-5); limpabuffer(); strcpy(buffer,DONO0.email2); break;
//                                                      case 2: carregar(menu,0); strcpy(buffer,String(PET0.anivdia)); strcat(buffer,String(PET0.anivmes)); strcat(buffer,String(PET0.anivano)); break;                                                
                                                        }
                                       }                       
                      botao=0; mouse++; rodasubsubmenu(); return;                                                       
              break;
              }
tela.clrScr();
printmenu(menu,0);
if(mouse==1){for(byte i=0;i<4;i++){if(submenu+i<totalsubmenu[menu]+1){printsubmenu(menu,submenu+i,i+1);}
                                                                 else{printsubmenu(menu,submenu+i-totalsubmenu[menu]-1,i+1);}}}
        else{printsubmenu(menu,submenu,1);}

informacoes(); botao=0;
Serial.println("  **RODASUBMENU-FIM**  ");
}

//**************************************************
void printsubmenu(byte nmenu, byte nsubmenu, byte nlinha){
byte espaco; if(mouse==1&&nlinha==1){espaco=6;}else{espaco=0;}

tela.setFont(SmallFont);
switch(nmenu){
case 0: 
case 13:
      switch(nsubmenu){
      case 0: tela.print(F("mlTotal/hora"),espaco,nlinha*8); break; //submenu=0
      case 1: tela.print(F("mlTotal/dia"),espaco,nlinha*8); break; //submenu=1
      case 2: tela.print(F("mlTotal/semana"),espaco,nlinha*8); break; //submenu=2
      case 3: tela.print(F("mlTotal/mes"),espaco,nlinha*8); break; //submenu=3    
      case 4: tela.print(F("Adiciona Pet"),espaco,nlinha*8); break; //submenu=4
      case 5: tela.print(F("Apaga Pet"),espaco,nlinha*8); break; //submenu=5
      case 6: tela.print(F("Adiciona Dono"),espaco,nlinha*8); break; //submenu=6
      case 7: tela.print(F("Apaga Dono"),espaco,nlinha*8); break; //submenu=7
      default: tela.print(F("Erro"),espaco,nlinha*8); break; //erro no submenu0   
      }
break;

case 14:
case 1:
case 15:
case 2:
case 3:
case 4:
case 5:
      switch(nsubmenu){
      case 0: tela.print(F("Nome:"),espaco,nlinha*8); if(mouse==1){tela.print(PET0.nome,36,nlinha*8);} break; //submenu=0
      case 1: tela.print(F("Raca:"),espaco,nlinha*8); if(mouse==1){tela.print(PET0.raca,36,nlinha*8);} break; //submenu=1
      case 2: if(mouse==1){tela.print(String("Aniv:"+String(PET0.anivdia)+"/"+String(PET0.anivmes)+"/"+String(PET0.anivano)),espaco,nlinha*8);}else{tela.print(F("Aniversario:"),LEFT,nlinha*8);} break; //submenu=2
      case 3: tela.print(F("Tag:"),espaco,nlinha*8);  if(mouse==1||mouse==2){cores(PET0.tag); tela.print(buffer,30,nlinha*8); } break; //submenu=3   **pode melhorar essa parte tirando o if 
      case 4: tela.print(F("Dono:"),espaco,nlinha*8); if(mouse==1||mouse==2){tela.print(PET0.dono,36,nlinha*8);}break; //submenu=4 **pode melhorar essa parte tirando o if
      case 5: tela.print(F("Volume[ml/vez]"),espaco,nlinha*8); break; //submenu=5
      case 6: tela.print(F("Volume[ml/dia]"),espaco,nlinha*8); break; //submenu=6
      case 7: tela.print(F("Volume[ml/sem]"),espaco,nlinha*8); break; //submenu=7
      case 8: tela.print(F("Volume[ml/mes]"),espaco,nlinha*8); break; //submenu=8
      default: tela.print(F("Erro"),espaco,nlinha*8); break; //erro no submenu1    
      }

break;


case 6:
case 7: 
case 8: 
case 9: 
case 10: 
      switch(nsubmenu){
      case 0: tela.print(F("Dono:"),espaco,nlinha*8); if(mouse==1){tela.print(String(DONO0.nome),36,nlinha*8);} break; //submenu=0
      case 1: tela.print(F("Cel:"),espaco,nlinha*8); if(mouse==1){tela.print(String(DONO0.celular),30,nlinha*8);} break; //submenu=1
      case 2: tela.print(F("Email1:"),espaco,nlinha*8); if(mouse==1){tela.print(String(DONO0.email1),42,nlinha*8);}  break; //submenu=2
      case 3: tela.print(F("Email2:"),espaco,nlinha*8); if(mouse==1){tela.print(String(DONO0.email2),42,nlinha*8);}  break; //submenu=3    
      case 4: if(mouse==1){tela.print(String("Aniv.:"+String(DONO0.anivdia)+"/"+String(DONO0.anivmes)+"/"+String(DONO0.anivano)),espaco,nlinha*8);} else{tela.print(F("Aniversario:"),LEFT,nlinha*8);} break; //submenu=2
      case 5: tela.print(F("Pets:"),espaco,nlinha*8);if(mouse==1||mouse==2){tela.print(DONO0.pet,36,nlinha*8);}break; //submenu=5 **pode melhorar essa parte tirando o if
      default: tela.print(F("Erro"),espaco,nlinha*8); break; //erro    
      }
break;


case 11: /**************************************************************************************************************************************************************************** ******************************************************/
      switch(nsubmenu){
      case 0: tela.print(F("Volume:"),espaco,nlinha*8); break; //submenu=0
      case 1: tela.print(F("Hora:"),espaco,nlinha*8); break; //submenu=1
      case 2: tela.print(F("Enviar SMS:"),espaco,nlinha*8);  break; //submenu=2
      case 3: tela.print(F("Enviar email:"),espaco,nlinha*8);  break; //submenu=3    
      case 4: tela.print(F("Rede:"),espaco,nlinha*8);  break; //submenu=4
      default: tela.print(F("Erro"),espaco,nlinha*8); break; //erro  
      }
break;

case 12: 
      switch(nsubmenu){
      case 0: tela.print(F("Brilho:"),espaco,nlinha*8); if(mouse==1){tela.print(String(AJUSTES0.brilho),RIGHT,nlinha*8);} break; //submenu=0
      case 1: tela.print(F("Contraste:"),espaco,nlinha*8); if(mouse==1){tela.print(String(AJUSTES0.contraste),RIGHT,nlinha*8);} break; //submenu=1
      default: tela.print(F("Erro"),espaco,nlinha*8); break; //erro   
      }
break;
default: tela.print(F("Erro"),espaco,nlinha*8); break;
} 
}



//****************************************************************************************************** FUNCOES: IMPRESSAO SUBSUBMENU *************************************************************************************************************************************************************************

void rodasubsubmenu(){
  Serial.println("  **RODASUBSUBMENU-INICIO**  ");
printmenu(menu,0);
printsubmenu(menu,submenu,1);
if(mouse==2&&menu>0&&menu<6&&submenu<2){                             
                                        if(editortexto(totalsubsubmenu15[submenu],2)){   Serial.print("Dentro if"); informacoes();
                                                                                      switch(submenu){
                                                                                                      case 0: strncpy(PET0.nome,buffer,sizeof(PET0.nome)); salvar(menu,0); break;
                                                                                                      case 1: strncpy(PET0.raca,buffer,sizeof(PET0.raca)); salvar(menu,0); break;
                                                                                                      } 
                                                                                      mouse--; botao=0;  rodasubmenu();                             
                                                                                      }
                                        }
if(mouse==2&&menu>0&&menu<6&&submenu==3){escolhecor();}
if(mouse==2&&menu>0&&menu<6&&submenu==4){escolhedono();}

if(mouse==2&&menu>5&&menu<11&&submenu<4){
                                         if(editortexto(totalsubsubmenu610[submenu],2)){   Serial.print("Dentro if"); informacoes();
                                                                                       switch(submenu){
                                                                                                      case 0: strncpy(DONO0.nome,buffer,sizeof(DONO0.nome)); salvar(0,menu-5); break;
                                                                                                      case 1: strncpy(DONO0.celular,buffer,sizeof(DONO0.celular)); salvar(0,menu-5); break;
                                                                                                      case 2: strncpy(DONO0.email1,buffer,sizeof(DONO0.email1)); salvar(0,menu-5); break;
                                                                                                      case 3: strncpy(DONO0.email2,buffer,sizeof(DONO0.email2)); salvar(0,menu-5); break;
                                                                                                      }                                                                          
                                                                                       mouse--; botao=0;  rodasubmenu();                                
                                                                                       } 
                                        }
if(mouse==2&&menu>5&&menu<11&&submenu==5){escolhepet();}

informacoes(); botao=0;
Serial.println("  **RODASUBSUBMENU-FIM**  ");
}
//****************************************************************************************************************FUNCOES DE SUBSUBMENU******************************************************************************************************************************************************************************************
boolean editortexto(byte lenght, byte linha){
  Serial.println(" *******EDITOR TEXTO-INICIO******* "); 

 //                                    for(byte i=0;i<14;i++){tela.print(String(buffer[i]),i*6,16);} 
  char *pointer = &buffer[0];

  informacoes(); 


if(posicaoteclado==0){posicaocaracteres=int(strchr(caracteres,buffer[posicaoteclado]))-int(&caracteres); constrain(posicaocaracteres,0,sizeof(caracteres)-2);}

  switch(botao){
    case 1: 
          if(posicaoteclado==0){posicaocaracteres=0; mouse=1; botao=0; rodasubmenu(); return false;}
          else{posicaoteclado--; posicaocaracteres=int(strchr(caracteres,buffer[posicaoteclado]))-int(&caracteres);}
          posicaocaracteres=int(strchr(caracteres,buffer[posicaoteclado]))-int(&caracteres);
    break;
    
    case 3: 
            if(menu>5&&menu<11&&submenu==1){
                                            if(posicaocaracteres==(sizeof(caracteres)-2)){posicaocaracteres=(sizeof(caracteres)-1-11);}else{posicaocaracteres++;}                                            
                                           }
            else{
                if(posicaocaracteres==(sizeof(caracteres)-2)){posicaocaracteres=0;}else{posicaocaracteres++;}
                } 
            *(pointer+posicaoteclado)=caracteres[posicaocaracteres];  
    break;//botao para cima que fazem as caracteres a-->b
    
    case 2: 
            if(menu>5&&menu<11&&submenu==1){
                                           if(posicaocaracteres==(sizeof(caracteres)-1-11)){posicaocaracteres=(sizeof(caracteres)-2);}else{posicaocaracteres--;}              
                                           }
            else{
                if(posicaocaracteres==0){posicaocaracteres=(sizeof(caracteres)-2);}else{posicaocaracteres--;}
                } 
            *(pointer+posicaoteclado)=caracteres[posicaocaracteres]; 
    break;//botao para baixo que fazem as caracteres b-->a
    
    case 4: 
            
            posicaoteclado++; 
            posicaocaracteres=int(strchr(caracteres,buffer[posicaoteclado]))-int(&caracteres);
            constrain(posicaocaracteres,0,sizeof(caracteres)-2);
            if(posicaoteclado==(lenght)){
                                            Serial.print("  **TRUESP**  "); 
                                            *(pointer+(lenght))='\0'; 
                                            posicaoteclado=0; 
                                            posicaocaracteres=0;
                                            return true;
                                            } 
            else if((*(pointer+posicaoteclado-2))==' '&&(*(pointer+posicaoteclado-1))==' '){
                                                                                            while(posicaoteclado<(lenght-1)){
                                                                                                                             *(pointer+posicaoteclado)=' '; 
                                                                                                                             posicaoteclado++;
                                                                                                                             }
                                                                                           *(pointer+(lenght-1))='\0'; 
                                                                                           posicaoteclado=0; 
                                                                                           posicaocaracteres=0;
                                                                                           Serial.print("  **TRUEFIM**  ");
                                                                                           return true; 
                                                                                            }
    break;
  }
  botao=0; informacoes(); 
    Serial.println(" *******EDITOR TEXTO-FIM******* "); 
    return false;
  }


//**********************************************************************************************************FUNCOES RELOGIO******************************************************************************************************************************************************

void ajustahora(byte hora){ //ajusta hora-> ajustahora(1) // ajusta data -> ajustahora(0)
t=rtc.getTime();
int data[3]={t.hour*hora+t.mon*(1-hora),t.min*hora+t.date*(1-hora),t.sec*hora+t.year*(1-hora)};  

//if(hora==1){data={t.hour,t.min,t.sec};}else{data={t.mon,t.date,t.year};}// hora,minuto,segundo
switch(botao){
              case 1: if(posicaoteclado==0){mouse--;}else{posicaoteclado--;}break;
              case 2: data[posicaoteclado]++; break;//if(hora==0&&posicaoteclado==1&&(byte)data[1]==pgm_read_byte_near(totaldiasmes + data[0]-1)){}else{data[posicaoteclado]++;} break;
              case 3: data[posicaoteclado]--; break;
              case 4: if(posicaoteclado==2){mouse--;posicaoteclado=0;}else{posicaoteclado++;}break;
             }
if(hora==0/*&&posicaoteclado==0*/&&data[1]>(pgm_read_byte_near(totaldiasmes + data[0]-1))){data[1]=pgm_read_byte_near(totaldiasmes + data[0]-1);}

if(hora==1){rtc.setTime(data[0],data[1],data[2]);Serial.println("      HORA -        MIN -      SEG");Serial.print("t.hour: "); Serial.print(t.hour, DEC);  Serial.print("  //t.min: "); Serial.print(t.min, DEC); Serial.print("  //t.sec: "); Serial.print(t.sec, DEC); }
else{rtc.setDate(data[1],data[0],data[2]);Serial.println("      MES -          DIA -         ANO");Serial.print("t.mon: "); Serial.print(t.mon, DEC); Serial.print("  //t.date: "); Serial.print(t.date, DEC); Serial.print("  //t.year: "); Serial.print(t.year, DEC); }
Serial.print(" // // //mouse: "); Serial.print(mouse); Serial.print("  //posicaoteclado: "); Serial.print(posicaoteclado); Serial.print("  //botao: "); Serial.println(botao);                   


         
}  
//***************************************************************************FUNCOES ESCOLHEDONO E ESCOLHEPET******************************************************************************************************************************************************
void escolhedono(){ //feita dentro de um PET (1<=menu<=5)
//Serial.println("***EscolhendoDono-Inicio***");informacoes(); 
static byte dono;
tela.clrScr();
printmenu(menu,0);
printsubmenu(menu,submenu,1);

/*Serial.println(""); 
Serial.print(" //Dono: "); Serial.print(dono); Serial.print(" //DONO0.pet: "); Serial.print(DONO0.pet); Serial.print(" //DONO0.pet[menu-1]: "); Serial.println(DONO0.pet[menu-1]); 
Serial.print(" //menu: "); Serial.print(menu); Serial.print(" //sizeof(menu): "); Serial.print(sizeof(menu)); Serial.print(" //char(menu): "); Serial.print(char(menu)); Serial.print(" //sizeof(char(menu):) "); Serial.println(sizeof(char(menu))); 
Serial.print(" //PET0.dono: "); Serial.print(PET0.dono); Serial.print(" //PET0.dono[dono]: "); Serial.print(PET0.dono[dono]); Serial.print(" //sizeof(PET0.dono[dono]): "); Serial.println(sizeof(PET0.dono[dono]));
Serial.print(" //DONO0.pet: "); Serial.print(DONO0.pet);// Serial.print(" //DONO0.pet[menu-1]: "); Serial.print(DONO0.pet[menu-1]); Serial.print(" //sizeof(DONO0.pet[menu-1]): "); Serial.println(sizeof(DONO0.pet[menu-1]));
Serial.println(""); */

switch(botao){
              case 1: /*Serial.println("*********case1***********");*/mouse--; dono=0; botao=0; rodasubmenu(); return; break;
              case 2: /*Serial.println("*********case2***********");*/if(dono==0){dono=4;}else{dono--;} break;
              case 3: /*Serial.println("*********case3**********");*/ if(dono==4){dono=0;}else{dono++;} break;
              case 4: /*Serial.println("*********case4***********");*/
                     carregar(0,dono+1); if(DONO0.pet[menu-1]==' '){DONO0.pet[menu-1]=(menu+48);}else{DONO0.pet[menu-1]=' ';} salvar(0,dono+1);
                     carregar(menu,0);   if(PET0.dono[dono]==' '){PET0.dono[dono]=(48+dono+1);}else{PET0.dono[dono]=' ';} salvar(menu,0);
              break;
             }
//Serial.println("*********FOR***********"); 


printsubmenu(menu,submenu,1);
for (byte linha=2;linha<5;linha++){                        
                                   if(dono+linha>6){carregar(0,dono+linha-6); if(linha==2){tela.print(String(dono+linha-6),6,16);}else{tela.print(String(dono+linha-6),0,linha*8);}}
                                   else{carregar(0,dono+1+linha-2);           if(linha==2){tela.print(String(dono+1+linha-2),6,16);}else{tela.print(String(dono+1+linha-2),0,linha*8);}}

                                   limpabuffer(); strcpy(buffer,DONO0.nome);
                                   if(linha==2){for (byte pos=0;pos<8;pos++){tela.print(String(buffer[pos]),(2+pos)*6,16);}}else{for (byte pos=0;pos<10;pos++){tela.print(String(buffer[pos]),(1+pos)*6,linha*8);}}
                                   if(DONO0.pet[menu-1]==(menu+48)){tela.print(F(":Sim"),60,linha*8);}else{tela.print(F(":Nao"),60,linha*8);}
                                  }
/*Serial.print(" //Dono: "); Serial.print(dono); Serial.print(" //DONO0.pet: ");  Serial.print(" //PET0.dono: "); Serial.print(PET0.dono); Serial.print(" //PET0.dono[dono]: "); Serial.print(PET0.dono[dono]);
Serial.println(""); Serial.print(" ///////////////////DONO0.nome: "); Serial.println(DONO0.nome);
Serial.println(""); Serial.print(DONO0.pet); Serial.print(" //DONO0.pet[menu-1]: "); Serial.print(DONO0.pet[menu-1]); Serial.print(" //menu: "); Serial.print(menu);
Serial.println("");            
for(byte i=1;i<6;i++){carregar(i,0);Serial.print("PET["); Serial.print(i); Serial.print("].dono: "); Serial.print(PET0.dono); carregar(0,i);Serial.print("   //  DONO["); Serial.print(i); Serial.print("].pet: "); Serial.println(DONO0.pet);}*/
//Serial.println("***EscolhendoDono-Fim***");
}

//***************************************************************************
void escolhepet(){ //feita dentro de um DONO (6<=menu<=10)
//Serial.println("***EscolhendoPet-Inicio***");informacoes(); 
static byte pet;
tela.clrScr();
printmenu(menu,0);
printsubmenu(menu,submenu,1);

/*Serial.println(""); 
Serial.print(" //Dono: "); Serial.print(dono); Serial.print(" //DONO0.pet: "); Serial.print(DONO0.pet); Serial.print(" //DONO0.pet[menu-1]: "); Serial.println(DONO0.pet[menu-1]); 
Serial.print(" //menu: "); Serial.print(menu); Serial.print(" //sizeof(menu): "); Serial.print(sizeof(menu)); Serial.print(" //char(menu): "); Serial.print(char(menu)); Serial.print(" //sizeof(char(menu):) "); Serial.println(sizeof(char(menu))); 
Serial.print(" //PET0.dono: "); Serial.print(PET0.dono); Serial.print(" //PET0.dono[dono]: "); Serial.print(PET0.dono[dono]); Serial.print(" //sizeof(PET0.dono[dono]): "); Serial.println(sizeof(PET0.dono[dono]));
Serial.print(" //DONO0.pet: "); Serial.print(DONO0.pet);// Serial.print(" //DONO0.pet[menu-1]: "); Serial.print(DONO0.pet[menu-1]); Serial.print(" //sizeof(DONO0.pet[menu-1]): "); Serial.println(sizeof(DONO0.pet[menu-1]));
Serial.println(""); */

switch(botao){
              case 1: /*Serial.println("*********case1***********");*/mouse--; pet=0; botao=0; rodasubmenu(); return; break;
              case 2: /*Serial.println("*********case2***********");*/ if(pet==0){pet=4;}else{pet--;} break;
              case 3: /*Serial.println("*********case3**********");*/  if(pet==4){pet=0;}else{pet++;} break;
              case 4: /*Serial.println("*********case4***********");*/
                     carregar(pet+1,0);  if(PET0.dono[menu-5-1]==' '){PET0.dono[menu-5-1]=(menu-5+48);}else{PET0.dono[menu-5-1]=' ';} salvar(pet+1,0);
                   //carregar(0,dono+1); if(DONO0.pet[menu-1]==' '){DONO0.pet[menu-1]=(menu+48);}else{DONO0.pet[menu-1]=' ';} salvar(0,dono+1);
                     carregar(0,menu-5); if(DONO0.pet[pet]==' '){DONO0.pet[pet]=(48+pet+1);}else{DONO0.pet[pet]=' ';} salvar(0,menu-5);
                   //carregar(menu,0);   if(PET0.dono[dono]==' '){PET0.dono[dono]=(48+dono+1);}else{PET0.dono[dono]=' ';} salvar(menu,0);
              break;
             }
//Serial.println("*********FOR***********"); 


printsubmenu(menu,submenu,1);
for (byte linha=2;linha<5;linha++){                        
                                   if(pet+linha>6){carregar(pet+linha-6,0); if(linha==2){tela.print(String(pet+linha-6),6,16);}else{tela.print(String(pet+linha-6),0,linha*8);}}
                                   else{carregar(pet+1+linha-2,0);           if(linha==2){tela.print(String(pet+1+linha-2),6,16);}else{tela.print(String(pet+1+linha-2),0,linha*8);}}

                                   limpabuffer(); strcpy(buffer,PET0.nome);
                                   if(linha==2){for (byte pos=0;pos<8;pos++){tela.print(String(buffer[pos]),(2+pos)*6,16);}}else{for (byte pos=0;pos<10;pos++){tela.print(String(buffer[pos]),(1+pos)*6,linha*8);}}
                                   if(PET0.dono[menu-5-1]==(menu-5+48)){tela.print(F(":Sim"),60,linha*8);}else{tela.print(F(":Nao"),60,linha*8);}
                                  }

/*Serial.print(" //Dono: "); Serial.print(dono); Serial.print(" //DONO0.pet: ");  Serial.print(" //PET0.dono: "); Serial.print(PET0.dono); Serial.print(" //PET0.dono[dono]: "); Serial.print(PET0.dono[dono]);
Serial.println(""); Serial.print(" ///////////////////DONO0.nome: "); Serial.println(DONO0.nome);
Serial.println(""); Serial.print(DONO0.pet); Serial.print(" //DONO0.pet[menu-1]: "); Serial.print(DONO0.pet[menu-1]); Serial.print(" //menu: "); Serial.print(menu);
Serial.println("");            
for(byte i=1;i<6;i++){carregar(i,0);Serial.print("PET["); Serial.print(i); Serial.print("].dono: "); Serial.print(PET0.dono); carregar(0,i);Serial.print("   //  DONO["); Serial.print(i); Serial.print("].pet: "); Serial.println(DONO0.pet);}*/
//Serial.println("***EscolhendoPet-Fim***");
}
//********************************************************************************************************************* FUNCOES: PALAVRAS *****************************************************************************************************************************************************
void escolhecor(){
static byte tag; 
static byte entrada;
tela.clrScr();
printmenu(menu,0);
printsubmenu(menu,submenu,1);
if(entrada==0){carregar(menu,0); tag=PET0.tag; entrada=1;}

switch(botao){
            case 1: mouse--; entrada=0; tag=0; botao=0; rodasubmenu(); return; break;
            case 2: if(tag==0){tag=5;}else{tag--;} break;
            case 3: if(tag==5){tag=0;}else{tag++;} break;
            case 4: for(byte i=1;i<6;i++){carregar(i,0); if(tag==PET0.tag){PET0.tag=0; salvar(i,0);}} carregar(menu,0); PET0.tag=tag; salvar(menu,0); mouse--; entrada=0; tag=0; botao=0; rodasubmenu(); return; break; 
            }

limpabuffer(); cores(tag); 
tela.print(buffer,CENTER,16);
if(tag!=0){tela.print(F("esta          "),0,24); tela.print(F("disponivel!  "),0,32);}
for(byte i=1;i<6;i++){carregar(i,0); if(tag==PET0.tag&&tag!=0){tela.print(F("tag usada por:"),0,24); tela.print(PET0.nome,0,32); tela.print(String(i),6*13,32);}}
}


void cores(byte cor){strcpy_P(buffer, (char*)pgm_read_word(&(tabelacores[cor])));} //cores variam de 0 a 5 sendo 0 sem cor

//******************************************************************************************************************** FUNCOES: EEMPROM *****************************************************************************************************************************************************
//********** FUNCAO: ALTERAR VALOR DE HORARIO DA EEPROM PARA VALOR ESCOLHIDO **********
void alterarhorario(byte horario, byte hora, byte minuto){
apagarhorario(horario);
adicionarhorario( hora, minuto);
arrumarhorario();   
}
//********** FUNCAO: ADICIONAR HORARIO ESCOLHIDO NA EEPROM **********
void adicionarhorario(byte hora, byte minuto){
carregarajustes();
if(AJUSTES0.nhorarios<11)
{hora=constrain(hora,0,23); minuto=constrain(minuto,0,59);
carregarajustes(); AJUSTES0.nhorarios++;salvarajustes();
HORARIO0.hora=hora;HORARIO0.minuto=minuto;
salvarhorario(AJUSTES0.nhorarios);
arrumarhorario();}   
}
//********** FUNCAO: APAGAR HORARIO ESPECIFICO DA EEPROM **********
void apagarhorario(byte horario){
carregarajustes();
for(;horario<AJUSTES0.nhorarios;horario++){carregarhorario(horario+1);salvarhorario(horario);}
AJUSTES0.nhorarios--;salvarajustes();
arrumarhorario(); 
}
//********** FUNCAO: IMPRIMIR HORARIOS DA EEPROM **********
void imprimirhorario(){
carregarajustes();
 for(byte i=1;i<AJUSTES0.nhorarios+1;i++){
 Serial.println(F(""));Serial.print(F("********************************************************************  HORARIO")); Serial.print(i); Serial.println(F("   ********************************************************************"));
carregarhorario(i); Serial.print(F(" //Hora: ")); Serial.print(HORARIO0.hora); Serial.print(F(" //Minuto: ")); Serial.println(HORARIO0.minuto);
}  
}
//********** FUNCAO: ARRUMAR HORARIOS QUE ESTAO NA EEPROM **********
void arrumarhorario(){
 //imprimirhorario();
 carregarajustes();
 for(byte j=1;j<AJUSTES0.nhorarios;j++){
 carregarhorario(1); 
 byte horavelha=HORARIO0.hora; byte minutovelho=HORARIO0.minuto;
  for(byte i=2;i<AJUSTES0.nhorarios+1;i++){carregarhorario(i);
                                         byte horanova=HORARIO0.hora; byte minutonovo=HORARIO0.minuto;
                                        
                                         /*Serial.print(" //ANTESIF//i: "); Serial.println(i); 
                                         Serial.print(" //horanova: "); Serial.print(horanova); Serial.print(" //minutonovo: "); Serial.print(minutonovo);
                                         Serial.print(" //horavelha: "); Serial.print(horavelha); Serial.print(" //minutovelho: "); Serial.print(minutovelho); 
                                         Serial.print(" //HORARIO0.hora: "); Serial.print(HORARIO0.hora); Serial.print(" //HORARIO0.minuto: "); Serial.println(HORARIO0.minuto);*/
                                       
                                        if(horanova<horavelha||(horanova==horavelha&&minutonovo<minutovelho)){
                                                                                                              HORARIO0.hora=horanova; HORARIO0.minuto=minutonovo; salvarhorario(i-1);
                                                                                                              HORARIO0.hora=horavelha; HORARIO0.minuto=minutovelho; salvarhorario(i);
                                                                                                             }
                                        else{}
                                        horavelha=HORARIO0.hora; minutovelho=HORARIO0.minuto;
                                         /*Serial.print(" //DEPOISVELHA//i: "); Serial.println(i); 
                                         Serial.print(" //horanova: "); Serial.print(horanova); Serial.print(" //minutonovo: "); Serial.print(minutonovo);
                                         Serial.print(" //horavelha: "); Serial.print(horavelha); Serial.print(" //minutovelho: "); Serial.print(minutovelho); 
                                         Serial.print(" //HORARIO0.hora: "); Serial.print(HORARIO0.hora); Serial.print(" //HORARIO0.minuto: "); Serial.println(HORARIO0.minuto);*/
                                        }
}
//imprimirhorario();
}
//********** FUNCAO: SALVAR HORARIO0 DA EEPROM **********
void salvarhorario(byte horario){
 memcpy(buffer,&HORARIO0,sizeof(HORARIO));
                    for(int eeAddress=(sizeof(PET)*5+sizeof(DONO)*5+sizeof(AJUSTES)+sizeof(HORARIO)*(horario-1));eeAddress<(sizeof(PET)*5+sizeof(DONO)*5+sizeof(AJUSTES)+sizeof(HORARIO)*(horario-1)+sizeof(HORARIO));eeAddress++){ //Serial.print(" eeAddress: "); Serial.print(eeAddress);
                                                                                                                     if( EEPROM.read(eeAddress) != buffer[eeAddress-(sizeof(PET)*5+sizeof(DONO)*5+sizeof(AJUSTES)+(sizeof(HORARIO))*(horario-1))]){ //Serial.print(" EEPROM.read(eeAddress)"); Serial.print(EEPROM.read(eeAddress)); Serial.print(" buffer[eeAddress-((sizeof(PET))*5+(sizeof(DONO)*(dono-1)))]:"); Serial.println(buffer[eeAddress-((sizeof(PET))*5+(sizeof(DONO)*(dono-1)))]);
                                                                                                                                                                                            EEPROM.write(eeAddress, buffer[eeAddress-( sizeof(PET)*5 + sizeof(DONO)*5 + sizeof(AJUSTES) + (sizeof(HORARIO))*(horario-1) ) ]);
                                                                                                                                                                                            }//Serial.print(" //eeAddress: "); Serial.println(eeAddress);
                                                                                                                     }  
}
//********** FUNCAO: CARREGAR HORARIO0 DA EEPROM **********
void carregarhorario(byte horario){
int eeAddress;
eeAddress=((sizeof(PET))*5+(sizeof(DONO))*5+(sizeof(AJUSTES))+(sizeof(HORARIO))*(horario-1));EEPROM.get(eeAddress,HORARIO0); 
}
//********** FUNCAO: SALVAR AJUSTES0 NA EEPROM **********
void salvarajustes(){
memcpy(buffer,&AJUSTES0,sizeof(AJUSTES));
                    for(int eeAddress=(sizeof(PET)*5+sizeof(DONO)*5);eeAddress<(sizeof(PET)*5+sizeof(DONO)*5+sizeof(AJUSTES));eeAddress++){ //Serial.print(" eeAddress: "); Serial.print(eeAddress);
                                                                                                                     if( EEPROM.read(eeAddress) != buffer[eeAddress-(sizeof(PET)*5+sizeof(DONO)*5)]){ //Serial.print(" EEPROM.read(eeAddress)"); Serial.print(EEPROM.read(eeAddress)); Serial.print(" buffer[eeAddress-((sizeof(PET))*5+(sizeof(DONO)*(dono-1)))]:"); Serial.println(buffer[eeAddress-((sizeof(PET))*5+(sizeof(DONO)*(dono-1)))]);
                                                                                                                                                                                            EEPROM.write(eeAddress, buffer[eeAddress-(sizeof(PET)*5+sizeof(DONO)*5)]);//Serial.print(" //eeAddress: "); Serial.println(eeAddress);
                                                                                                                                                                                            }
                                                                                                                     }
                     
}
//********** FUNCAO: CARREGAR AJUSTES0 DA EEPROM **********
void carregarajustes(){
int eeAddress;
eeAddress=((sizeof(PET))*5+(sizeof(DONO))*5);EEPROM.get(eeAddress,AJUSTES0);  
}
//********** FUNCAO: SALVAR PET0 OU DONO0 NA EEPROM **********
void salvar(byte pet, byte dono){ //salva dados de PET0 na EEPROM na forma update para preservar EEPROM, ou seja, somente irá salvar se o dado mudar
if(pet!=0&&dono==0){memcpy(buffer, &PET0, sizeof(PET));
                    for(int eeAddress=((sizeof(PET))*(pet-1));eeAddress<((sizeof(PET))*(pet-1))+sizeof(PET);eeAddress++){ //Serial.print(" eeAddress: "); Serial.print(eeAddress);
                                                                                                                        if( EEPROM.read(eeAddress) != buffer[eeAddress-((sizeof(PET))*(pet-1))]){ //Serial.print(" EEPROM.read(eeAddress)"); Serial.print(EEPROM.read(eeAddress)); Serial.print(" buffer[eeAddress-((sizeof(PET))*(pet-1))]:"); Serial.println(buffer[eeAddress-((sizeof(PET))*(pet-1))]);
                                                                                                                                                                                               EEPROM.write(eeAddress, buffer[eeAddress-((sizeof(PET))*(pet-1))]);//Serial.print(" //eeAddress: "); Serial.println(eeAddress);
                                                                                                                                                                                                }
                                                                                                                        }
                   }

if(pet==0&&dono!=0){memcpy(buffer, &DONO0, sizeof(DONO));
                    for(int eeAddress=((sizeof(PET))*5+(sizeof(DONO)*(dono-1)));eeAddress<((sizeof(PET))*5+(sizeof(DONO)*(dono-1))+sizeof(DONO));eeAddress++){ //Serial.print(" eeAddress: "); Serial.print(eeAddress);
                                                                                                                     if( EEPROM.read(eeAddress) != buffer[eeAddress-((sizeof(PET))*5+(sizeof(DONO)*(dono-1)))]){ //Serial.print(" EEPROM.read(eeAddress)"); Serial.print(EEPROM.read(eeAddress)); Serial.print(" buffer[eeAddress-((sizeof(PET))*5+(sizeof(DONO)*(dono-1)))]:"); Serial.println(buffer[eeAddress-((sizeof(PET))*5+(sizeof(DONO)*(dono-1)))]);
                                                                                                                                                                                            EEPROM.write(eeAddress, buffer[eeAddress-((sizeof(PET))*5+(sizeof(DONO)*(dono-1)))]);//Serial.print(" //eeAddress: "); Serial.println(eeAddress);
                                                                                                                                                                                            }
                                                                                                                     }
                   }
}
//********** FUNCAO: CARREGAR **********
void carregar(byte pet, byte dono){ //carrega dados da EEPROM em PET0 ou DONO0
int eeAddress;
if(pet!=0&&dono==0){eeAddress=((sizeof(PET))*(pet-1));EEPROM.get(eeAddress,PET0);}
if(dono!=0&&pet==0){eeAddress=((sizeof(PET))*5+(sizeof(DONO))*(dono-1));EEPROM.get(eeAddress,DONO0);}
} // carregar
//********** FUNCAO: APAGARPET **********
void apagarpet(byte pet){
carregarajustes();
for(;pet<AJUSTES0.npets;pet++){carregar(pet+1,0);salvar(pet,0);}
AJUSTES0.npets--; salvarajustes();
} //apagarpet
//********** FUNCAO: APAGARDONO **********
void apagardono(byte dono){
carregarajustes();
for(;dono<AJUSTES0.ndonos;dono++){carregar(0,dono+1);salvar(0,dono);}
AJUSTES0.ndonos--; salvarajustes();
} //apagardono
//********** FUNCAO: DELETAR EEPROM **********
void EEdeletar(){
    for (int i = 0 ; i < EEPROM.length() ; i++) {
                                                EEPROM.write(i, 255);
                                                Serial.print(i); Serial.print(F(":(")); Serial.write(EEPROM.read(i));Serial.println(F(")"));
                                                }
}
//********** FUNCAO: IMPRIMIR EEPROM **********
void EEprint(){
for (int i = 0 ; i < EEPROM.length() ; i++) {
    Serial.print(i); Serial.print(F("-Write:(")); Serial.write(EEPROM.read(i));Serial.print(F(")-Print:(")); Serial.print(EEPROM.read(i));Serial.println(F(")"));
    }
}

void EEprint2(){


  

carregarajustes();
for (byte i = 0 ; i < EEPROM.length() ; i++) {
Serial.print("***i=");Serial.print(i);Serial.print("/ ***");
if(i==0){Serial.println(""); Serial.print(F("PET: "));}
if(i==sizeof(PET)*5){Serial.println(""); Serial.print(F("DONO: "));}
if(i==(sizeof(PET)*5+sizeof(DONO)*5)){Serial.println(""); Serial.print(F("AJUSTES: "));}
if(i==(sizeof(PET)*5+sizeof(DONO)*5+sizeof(AJUSTES))){Serial.println(""); Serial.print(F("HORA: "));}
if(i==(sizeof(PET)*5+sizeof(DONO)*5+sizeof(AJUSTES)+sizeof(HORARIO)*AJUSTES0.nhorarios)){Serial.println(""); Serial.print(F("OUTROS: "));}

if(((i+1)%sizeof(PET)==0)&&(i<sizeof(PET)*5)){Serial.println(""); Serial.print(F("PET: "));}
else if(((i+1-5*sizeof(PET))%sizeof(DONO)==0)&&(i>sizeof(PET)*5)&&(i<(sizeof(PET)*5+sizeof(DONO)*5))){Serial.println(""); Serial.print(F("DONO: "));}
else if(((i+1-5*sizeof(PET)-5*sizeof(DONO))%sizeof(DONO)==0)&&(i>(sizeof(PET)*5+sizeof(DONO)*5))&&(i<(sizeof(PET)*5+sizeof(DONO)*5+sizeof(AJUSTES)))){Serial.println(""); Serial.print(F("AJUSTES: "));}
else if(((i+1-5*sizeof(PET)-5*sizeof(DONO)-sizeof(HORARIO)*AJUSTES0.nhorarios)%sizeof(DONO)==0)&&(i>(sizeof(PET)*5+sizeof(DONO)*5+sizeof(AJUSTES)))&&(i<(sizeof(PET)*5+sizeof(DONO)*5+sizeof(AJUSTES)+sizeof(HORARIO)*AJUSTES0.nhorarios))){Serial.println(""); Serial.print(F("HORA: "));}

Serial.write(EEPROM.read(i)); 
    }
   flag=0; 
}
//********** FUNCAO: LIMPAR BUFFER **********
void limpabuffer(){char *pointer=&buffer[0]; for(byte i=0;i<(sizeof(buffer));i++){*(pointer+i)=' ';}*(pointer+sizeof(buffer)-1)='\0';}





// transformar todos int que puderem em const e fazer F() de todos textos
//                                   tela.print(caracteres[posicaocaracteres],6*posicaoteclado,16); 








