#include "catalog.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <regex>

Catalog c( ( char * ) "in" ) ;
char *out1 = ( char * ) "out/1.txt";
char *out2 = ( char * ) "out/2.txt";
char *out0 = ( char * ) "out/apple.txt";
std::regex rx0( "^яблок[ои]" );
std::regex rx1( ",\\s*Внешторг" );
std::regex rx2( R"(,\s*агрофирма\s?Сады)" );

int process( std::string ); /*основной процесс*/
int new_out_files();

int main(){

    fprintf( stderr, "\n---===cicle...  quit: ^c===---\n\n" );
    while( 1 ) {    
        c.read(); /*читаем каталог с входными файлами */
        if( c.is_new() ) {  /* если найдены изменения, то */
            printf( "new\n" );
            c.browse();
            c.save();
            new_out_files();  /* очистить выходные файлы */
            std::list<std::string>::iterator pv = c.v.begin();
            while( pv != c.v.end( ) ) {/*обработатть все входные файлы*/
                process( *pv );
                pv++;
           }
            /*todo*/ /*если нужно что-нибудь еще, добавить сюда*/
        }
        sleep( 10 );  /*через 10 секунд начать заново*/
    }
}

int process(std::string fn) {
    std::ofstream of0( out0, std::ios_base::app );
    if( !of0 ) {
        std::cout<< "error create file "<<out0<<std::endl;
        return -1;
    }
    std::cout<< "open file "<<out0<<std::endl;

    std::ofstream of1( out1, std::ios::app );
    if( !of0 ) {
        std::cout<< "error create file "<<out1<<std::endl;
        return -1;
    }
    std::cout<< "open file "<<out1<<std::endl;

    std::ofstream of2( out2, std::ios::app );
    if( !of0 ) {
        std::cout<< "error create file "<<out2<<std::endl;
        return -1;
    }
    std::cout<< "open file "<<out2<<std::endl;

    std::string path = "in/" + fn;
    const char *fname = path.c_str();
    std::cout<< fname <<std::endl;
    std::ifstream in( fname );
    if( !in ) {
        std::cout<< "error open file "<<fname<<std::endl;
        return -1;
    }
    char buf[255];
    while( in ) {
      in.getline( buf, 254 );
      std::cout<< buf << std::endl;
      if( std::regex_search( ( std::string ) buf,rx0 ) ) {
        of0<< buf<< ", покупатель: "<<fn<< std::endl;
        std::cout<<"save "<<out0<<" "<<buf<<std::endl;
      }
      if( std::regex_search( ( std::string ) buf,rx1 ) ) {
        of1<< buf<< ", покупатель: "<<fn<< std::endl;
        std::cout<<"save "<<out1<<" "<<buf<<std::endl;
      }
      if( std::regex_search( ( std::string ) buf,rx2 ) ) {
        of2<< buf<< ", покупатель: "<<fn<< std::endl;
        std::cout<<"save "<<out2<<" "<<buf<<std::endl;
      }
    }
    of0.close();
    of1.close();
    of2.close();
    in.close();
    std::cout<<"close all"<<std::endl;
}

int new_file( char *ou ) {
    std::ofstream out( ou, std::ios::trunc );
    if( !out ) {
        std::cout<< "error create file "<<out<<std::endl;
        return -1;
    }
    out.close();
}
int new_out_files() {
    new_file( out0 );      
    new_file( out1 );      
    new_file( out2 );      
}

