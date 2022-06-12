/* Класс работы с каталогом  */
#include <string>
#include <list>

class Catalog {
public:
  Catalog ( char *directory ) { dirc=directory; } ;
  Catalog () {  dirc = ( char * ) "."  ; } ;
  virtual ~Catalog();
  int ls() ;
  int ls( char * ) ;
  int read();
  void browse();
  void save();
  int is_new();
  std::list<std::string> v;
  

private:
  int process( char *, char * );
  char *dirc;
  std::list<long> d;
  std::list<long> d_bak;
        
};
