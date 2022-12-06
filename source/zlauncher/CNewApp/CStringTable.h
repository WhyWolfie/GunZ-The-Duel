

#pragma once

#ifndef _CSTRINGTABLE_H_
#define _CSTRINGTABLE_H_



// Destroy
extern void STDestroy();

// Load string from a file
extern bool STLoadFromFile( const char* szFileName);

// Load string from memory string
extern bool STLoadFromMemory( const char* szMemString);

// Get string with name
extern const char* STGetString( const char* szName);

// Get string with name
extern void STGetString( const char* szName, char* szString);


#endif
