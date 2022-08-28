#define PinoTrigger 4   //O Trigger emite o pulso
#define PinoEcho 3      //O Echo recebe o pulso
#define motor_saida 6   //Bomba que esvazia o reservatório
#define input1 12       
#define input2 13       //Sinais digitais que ligam/desligam o motor

float duracao = 0;   //tempo entre a ida e volta da onda sonora do sensor
float distancia = 0; //converte a duracao para distancia
float velocidade =0; //variável que irá determinar a rotação do motor

void setup (){
Serial.begin(9600);
 
pinMode(PinoTrigger,OUTPUT);
pinMode(PinoEcho,INPUT);
pinMode(motor_saida, OUTPUT);
pinMode(saida_botao, OUTPUT);//define os pinos de entrada e saída de dados
}
void loop(){
  Leitura_de_Distancia();
  Para_Motor();
  Serial.println("Tanque nivelado.\n");
  
while (distancia < 15){//enquanto a distancia entre o sensor e o líquido for <50
  Motor_de_Saida();}
  delay (1000);}

void Motor_de_Saida(){//função que aciona o motor de saída
  velocidade = (-12.75* distancia) + 255;
  if (velocidade < 100){
    velocidade = 100;};//condição que limita vel. mínima em 100
    
  analogWrite(motor_saida, velocidade);//Imprime o valor analógico da
                                       //velocidade na ponte H
  digitalWrite(input1, 1);
  digitalWrite(input2, 0);//aciona o motor

  Serial.print(velocidade);
  Serial.println("\n";
  
  delay(200);//pausa de 0,2 s entre uma leitura e outra
  Leitura_de_Distancia();
}

void Leitura_de_Distancia(){//função de leitura de distância
  digitalWrite(PinoTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(PinoTrigger,LOW);
  duracao = pulseIn(PinoEcho, HIGH); 
  distancia = (duracao / 2) / 29.1;
}

void Para_Motor(){//função que desaciona o motor
 digitalWrite(input1, 0);
 digitalWrite(input2, 0);
}
