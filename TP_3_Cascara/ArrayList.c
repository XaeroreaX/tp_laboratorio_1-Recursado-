#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"

// funciones privadas
int resizeUp(ArrayList* pList);
int expand(ArrayList* pList,int index);
int contract(ArrayList* pList,int index);

#define AL_INCREMENT      10
#define AL_INITIAL_VALUE  10
//___________________

/**--------------------------------------------------------------------------*////1)

/** \brief Allocate a new arrayList with AL_INITIAL_VALUE elements.
 * \param void
 * \return ArrayList* Return (NULL) if Error [if can't allocate memory]
 *                  - (pointer to new arrayList) if ok
 */
ArrayList* al_newArrayList(void)
{
    ArrayList* pList;
    ArrayList* returnAux = NULL;
    void* pElements;
    pList =(ArrayList*)malloc(sizeof(ArrayList));

    if(pList != NULL)
    {
        pElements = malloc(sizeof(void *)*AL_INITIAL_VALUE );
        if(pElements != NULL)
        {
            pList->size=0;
            pList->pElements=pElements;
            pList->reservedSize=AL_INITIAL_VALUE;
            pList->add=al_add;
            pList->len=al_len;
            pList->set=al_set;
            pList->remove=al_remove;
            pList->clear=al_clear;
            pList->clone=al_clone;
            pList->get=al_get;
            pList->contains=al_contains;
            pList->push=al_push;
            pList->indexOf=al_indexOf;
            pList->isEmpty=al_isEmpty;
            pList->pop=al_pop;
            pList->subList=al_subList;
            pList->containsAll=al_containsAll;
            pList->deleteArrayList = al_deleteArrayList;
            pList->sort = al_sort;
            returnAux = pList;
        }
        else
        {
            free(pList);
        }
    }

    return returnAux;
}


/**--------------------------------------------------------------------------*////2)

/** \brief  Add an element to arrayList and if is
 *          nessesary resize the array
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (0) if Ok
 *
 */
int al_add(ArrayList* pList,void* pElement)
{
    int returnAux = -1;
    int size;
    int flag = 0;

    if(pList == NULL || pElement == NULL)
    {
        return returnAux;
    }



    if(pList->size == pList->reservedSize)
    {
        flag = resizeUp(pList);
    }


    if(flag == 0)
    {

        size = pList->size;
        pList->pElements[size] = pElement;
        pList->size++;
        returnAux = 0;
    }

    //printf("devuelve: %d\n", returnAux);
    return returnAux;
}

/**--------------------------------------------------------------------------*////3)

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Ok
 *
 */
int al_deleteArrayList(ArrayList* pList)
{
    int returnAux = -1;

    if(pList == NULL) return returnAux;

    free(pList);

    returnAux = 0;

    return returnAux;
}

/**--------------------------------------------------------------------------*////4)

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return length of array or (-1) if Error [pList is NULL pointer]
 *
 */
int al_len(ArrayList* pList)
{

    if(pList == NULL) return -1;

    return pList->size;


}

/**--------------------------------------------------------------------------*////5)

/** \brief  Get an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return void* Return (NULL) if Error [pList is NULL pointer or invalid index] - (Pointer to element) if Ok
 *
 */
void* al_get(ArrayList* pList, int index)
{
    void* returnAux = NULL;

    if(pList == NULL || (index > pList->size || index < 0))
    {
        //free(pList);
        return returnAux;
    }

    returnAux = pList->pElements[index];

    return returnAux;
}

/**--------------------------------------------------------------------------*////6)

/** \brief  Find if pList contains at least one element pElement
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer]
 *                  - ( 0) if Ok but not found a element
 *                  - ( 1) if this list contains at least one element pElement
 *
 */
int al_contains(ArrayList* pList, void* pElement)
{
    int returnAux = -1;
    int index = 0;
    int flag = 0;

    if(pList == NULL || pElement == NULL) return returnAux;

    returnAux++;

    while(index <= pList->len(pList))
    {
        if(pList->get(pList, index) == pElement)
        {
            flag++;
            break;
        }
        index++;

    }

    if(flag > 0) returnAux++;


    return returnAux;
}

/**--------------------------------------------------------------------------*////7)

/** \brief  Set a element in pList at index position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 *
 */
int al_set(ArrayList* pList, int index,void* pElement)
{
    int returnAux = -1;

    if((pList == NULL || pElement == NULL) || (index < 0 || index > pList->size)) return returnAux;

    returnAux++;

    pList->pElements[index] = pElement;

    return returnAux;
}

/**--------------------------------------------------------------------------*////8)

/** \brief  Remove an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_remove(ArrayList* pList,int index)
{
    int returnAux = -1;
    //void* aux =(void*) malloc(sizeof(void)* 0);

    if(pList == NULL || (index > pList->size || index < 0)) return returnAux;


    returnAux = contract(pList,index);


    return returnAux;
}

/**--------------------------------------------------------------------------*////9)

/** \brief Removes all of the elements from this list
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer]
 *                  - ( 0) if Ok
 */
int al_clear(ArrayList* pList)
{
    int returnAux = -1;

    void* pElements;

    if(pList == NULL) return returnAux;

    returnAux++;

    free(pList->pElements);

    pElements = malloc(sizeof(void *)*AL_INITIAL_VALUE );

    pList->pElements = pElements;

    pList->size = NULL;

    pList->reservedSize=AL_INITIAL_VALUE;

    return returnAux;
}


/**--------------------------------------------------------------------------*////10)
/** \brief Returns an array containing all of the elements in this list in proper sequence
 * \param pList ArrayList* Pointer to arrayList
 * \return ArrayList* Return  (NULL) if Error [pList is NULL pointer]
 *                          - (New array) if Ok
 */
ArrayList* al_clone(ArrayList* pList)
{
    ArrayList* returnAux = NULL;



    if(pList == NULL) return returnAux;

    returnAux = al_newArrayList();

    if(returnAux != NULL)
    {
        returnAux->size= pList->size;
        returnAux->pElements=pList->pElements;
        returnAux->reservedSize=pList->reservedSize;
        returnAux->add=al_add;
        returnAux->len=al_len;
        returnAux->set=al_set;
        returnAux->remove=al_remove;
        returnAux->clear=al_clear;
        returnAux->clone=al_clone;
        returnAux->get=al_get;
        returnAux->contains=al_contains;
        returnAux->push=al_push;
        returnAux->indexOf=al_indexOf;
        returnAux->isEmpty=al_isEmpty;
        returnAux->pop=al_pop;
        returnAux->subList=al_subList;
        returnAux->containsAll=al_containsAll;
        returnAux->deleteArrayList = al_deleteArrayList;
        returnAux->sort = al_sort;
        //returnAux = pList;
    }


    return returnAux;

}

/**--------------------------------------------------------------------------*////11)
/** \brief Inserts the element at the specified position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_push(ArrayList* pList, int index, void* pElement)
{
    int returnAux = -1;

    if((pList == NULL || pElement == NULL) || (index > pList->size || index < 0)) return returnAux;

    returnAux = expand(pList, index);

    pList->pElements[index] = pElement;

    return returnAux;
}


/**--------------------------------------------------------------------------*////12)
/** \brief Returns the index of the first occurrence of the specified element
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (index to element) if Ok
 */
int al_indexOf(ArrayList* pList, void* pElement)
{
    int returnAux = -1;
    int index = 0;
    if(pList == NULL || pElement == NULL) return returnAux;

    while(index <= pList->size)
    {

        if(pElement == pList->pElements[index]) break;
        index++;

    }


    if(index <= pList->size) returnAux = index;

    return returnAux;
}


/**--------------------------------------------------------------------------*////13)
/** \brief Returns true if this list contains no elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Not Empty - (1) if is Empty
 */
int al_isEmpty(ArrayList* pList)
{
    int returnAux = -1;

    if(pList == NULL) return returnAux;

    returnAux++;

    if(pList->size == 0) returnAux++;

    return returnAux;
}



/**--------------------------------------------------------------------------*////14)
/** \brief Remove the item at the given position in the list, and return it.
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid index]
 *                  - ( element pointer) if Ok
 */
void* al_pop(ArrayList* pList,int index)
{
    void* returnAux = NULL;
    int flag;

    if(pList == NULL || (index > pList->size || index < 0)) return returnAux;


    flag = contract(pList,index);

    if(flag == 0)
    {
        returnAux = pList->pElements[index];
    }

    return returnAux;
}

/**--------------------------------------------------------------------------*////15)
/** \brief Returns a new arrayList with a portion of pList between the specified
 *         fromIndex, inclusive, and toIndex, exclusive.
 * \param pList ArrayList* Pointer to arrayList
 * \param from int Initial index of the element (inclusive)
 * \param to int Final index of the element (exclusive)
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid 'from' or invalid 'to']
 *                  - ( pointer to new array) if Ok
 */
ArrayList* al_subList(ArrayList* pList,int from,int to)
{
    void* returnAux = NULL;
    int i;
    int paux;
    int flag = -1;
    ArrayList* aux;

    if(from > to) return returnAux;

    if(pList != NULL && from != to)
    {

        if((from > -1 && from <= pList->len(pList)) && (to > -1 && to <= pList->len(pList)))
        {


            aux = al_newArrayList();
            if(aux != NULL)
            {

                for(i = from; i < to; i++)
                    flag = aux->add(aux, pList->pElements[i]);

            }

        }
    }


    if(flag == 0) returnAux = aux;


    return returnAux ;
}




/**--------------------------------------------------------------------------*////16)
/** \brief Returns true if pList list contains all of the elements of pList2
 * \param pList ArrayList* Pointer to arrayList
 * \param pList2 ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList or pList2 are NULL pointer]
 *                  - (0) if Not contains All - (1) if is contains All
 */
int al_containsAll(ArrayList* pList,ArrayList* pList2)
{
    int returnAux = -1, index;



    if(pList == NULL || pList2==NULL) return returnAux;

    returnAux++;


    for(index = 0; index < pList->len(pList); index++)
    {
        if(pList->contains(pList, pList2->get(pList2, index)) < 1) break;
        printf("%d",pList2->contains(pList2, pList->get(pList, index)));

    }

    if(index == pList->len(pList))
        returnAux++;
    //printf("%d", returnAux);

    return returnAux;
}

/**--------------------------------------------------------------------------*////17)
/** \brief Sorts objects of list, use compare pFunc
 * \param pList ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [pList or pFunc are NULL pointer]
 *                  - (0) if ok
 */
int al_sort(ArrayList* pList, int (*pFunc)(void*,void*), int order)
{
    int returnAux = -1;
    int i, j;
    void* aux;

    if((pList == NULL || pFunc==NULL) || (order > 1 || order <= -1)) return returnAux;
//  printf("size: %d", pList->len(pList));
   for(i = 0; i < pList->len(pList) - 1; i++)

    {
//        printf("i: %d", i);
        for(j = i + 1; j < pList->len(pList) ; j++)
        {
//            printf("j: %d", j);
            if(order == 1)
            {


                if(pFunc(pList->pElements[i], pList->pElements[j]) > 0)
                {

                    aux = pList->pElements[i];
                    pList->pElements[i] = pList->pElements[j];
                    pList->pElements[j] = aux;

                }
            }
            else
            {
                if(pFunc(pList->pElements[i], pList->pElements[j]) < 0)
                {

                    aux = pList->pElements[i];
                    pList->pElements[i] = pList->pElements[j];
                    pList->pElements[j] = aux;

                }
            }
        }

    }

    returnAux = 0;



    return returnAux;
}

/**--------------------------------------------------------------------------*////18)
/** \brief Increment the number of elements in pList in AL_INCREMENT elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
int resizeUp(ArrayList* pList)
{
    int returnAux = -1;
    void* aux;



    if(pList == NULL) return returnAux;


    aux = realloc(pList->pElements, sizeof(void*) * (pList->reservedSize + AL_INCREMENT));
    //printf("REALLOC");
    if(aux == NULL)
    {
        //printf("Se metio aca");
        return returnAux;
    }
    pList->pElements=aux;
    pList->reservedSize += AL_INCREMENT;

    returnAux=0;

    return returnAux;

}

/**--------------------------------------------------------------------------*////19)
/** \brief  Expand an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int expand(ArrayList* pList,int index)
{
    int returnAux = -1;
    int i;
    int flag = 0;

    if(pList == NULL || (index > pList->size || index < 0)) return returnAux;

    returnAux++;

    if(pList->size == pList->reservedSize)
    {
        flag = resizeUp(pList);
    }

    if(flag == 0)
    {


        pList->size++;

        for(i = index; i < pList->size; i++)
        {

            pList->pElements[i + 1] = pList->pElements[i];

        }

    }
    return returnAux;
}

/**--------------------------------------------------------------------------*////20)
/** \brief  Contract an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int contract(ArrayList* pList,int index)
{
    int returnAux = -1;

    int i;

    if(pList == NULL || (index < 0 || index > pList->size)) return returnAux;

    returnAux = 0;


    //if(index)
    for(i = index + 1; i < pList->size; i++)
    {

        pList->pElements[i] = pList->pElements[i + 1];


    }

    pList->size--;

    return returnAux;
}
