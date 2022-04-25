//
// Created by Noy Zini on 16/04/2022.
//

#ifndef MAIN_C_ASCIIART_H
#define MAIN_C_ASCIIART_H

#include <stdio.h>
#include <stdbool.h>
#include "RLEList.h"


/**
*   asciiArtRead: Read a given file and outputs an RLE list accordingly.
*
* @param in_stream - The file for which to create RLE list.
*
* @return
* 	RLEList that contains the file content at the RLE method.
 * 	if file reading fails then returns NULL
*/
RLEList asciiArtRead(FILE* in_stream);

/**
*   asciiArtPrint: Writes an image to given file
*
* @param list - An image represented as an RLEList
* @param out_stream - The file to write the image to.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
 * 	RLE_LIST_SUCCESS if the process ended successfully
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);


/**
*   asciiArtPrintEncoded: Writes the image to the file in a compressed form (RLEListExportToEncodedString).
*
* @param list - RLE list that contains the image.
* @param out_stream - The file for which to output the compressed RLE list of the image.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	RLE_LIST_SUCCESS if the process ended successfully
*/
RLEListResult asciiArtPrintEncoded(RLEList list,FILE* out_stream);


#endif //MAIN_C_ASCIIART_H
