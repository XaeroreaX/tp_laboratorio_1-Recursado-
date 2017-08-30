typedef struct
{
    char nombre[20];
    int edad;
    int dni;
    int flagEstado;
}SPersona;
/** \brief un tipo de dato tipo estructura de una persona basica
 *
 * \param nombre (veinte caracteres)
 * \param edad
 * \param dni documento
 * \param flag estado 1 casado 0 soltero
 *
 */


SPersona HarcodearS(char[], int, int, int);
/** \brief funcion para harcodear una bariable tipo SPersona
 *
 * \param nombre char vector de veinte caracteres
 * \param edad entero
 * \param dni entero
 * \param flag del estado (1 o 0)
 * \return retorna todo un dato de la estructura tipo SPersona
 *
 */


SPersona cargarPersonaS();
 /** \brief carga a mano todo los datos de la estructura persona
  *
  * \return un tipo de dato de la estructura persona escrita a mano
  *
  */

void mostraArrayS(int ,SPersona[], int);
/** \brief muestra un vector de la estructura SPersona
 *
 * \param tamaño del vector
 * \param vector de la estructura
 * \param un flag entero que determina si ver la posicion(1) o si no(0)
 *
 */

 void mostrarBarraEdadesS(int ,SPersona[]);
 /** \brief imprime una barra que dependiendp de la edad(<18 19-35 >35) contara con un *
  *
  * \param vector de la estructura SPersona
  * \param tamaño del vector en entero
  *
  */



void mostrarordenarS(int ,SPersona[]);
/** \brief muestra alfabeticamente un vector de la estructura SPersona
 *
 * \param entero tamaño de la estructura
 * \param vector a ordenar
 *
 */


int buscarDatosCargadosS(int ,SPersona[]);
/** \brief busca si hay datos cargados en el vector SPersona fijandose en el parametro dni
 *
 * \param variable entera que representa el tamaño del vector
 * \param variable vector de la estructura SPersona
 * \return un valor entero (1 es que hay valor en el vector y 0 significa que no hay)
 *
 */
