#include "tpFTP.h"

void get_file_name (int sokt, char* file_name){
  str_pos = 0;
  while (1) {
    tp_recvfrom(sokt, &(file_name[str_pos]), 1); // Recebe 1 byte do cliente
    if (file_name[str_pos] == '\0') break; // Se a strign estiver no fim, termina o loop
    str_pos++;
  }
}

void read_file_buffer(tam_buffer ,FILE* entr_file,int& flagEOF){
  ii = 0;
  char byte;
  while(ii<tam_buffer){ // enquanto o buffer nao estiver cheio
    byte = fgetc (entr_file); // pega um byte do arquivo
    buffer[ii]=byte; // adiciona o byte ao buffer
    printf("%c",buffer[ii]);
    if (byte==EOF) {  // verifica se o byte significa que o arquivo acabou
      flagEOF = 0;  // transmite informação de fim de arquivo para fora do loop
      break;
    }
    ii++; // incrementa contador
  }
}
