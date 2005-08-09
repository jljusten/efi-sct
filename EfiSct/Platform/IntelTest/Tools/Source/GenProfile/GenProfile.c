/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  GenProfile.c

Abstract:

  Generate a profile file from binary.

--*/

//
// Includes
//

#include <stdio.h>

//
// Definitions
//

#define MAX_BUFFER_SIZE           2048

//
// Internal functions declaration
//

void
PrintUsage (
  void
  );

void
WriteBlock (
  FILE        *Profile,
  long        Start,
  char        *Buffer,
  int         BufferSize
  );

int
GenProfile (
  FILE        *BinFile,
  FILE        *Profile
  );


//
// External functions implementation
//

int
main (
  int         Argc,
  char        **Argv
  )
{
  int     Result;
  FILE    *BinFile;
  FILE    *Profile;

  //
  // Check parameters
  //
  if (Argc != 3) {
    PrintUsage ();
    return -1;
  }

  //
  // Open the binary file
  //
  BinFile = fopen (Argv[1], "rb");
  if (BinFile == NULL) {
    printf ("Error: Cannot open the binary file\n");
    return -1;
  }

  //
  // Open the profile
  //
  Profile = fopen (Argv[2], "w");
  if (Profile == NULL) {
    printf ("Error: Cannot create the profile\n");
    fclose (BinFile);
    return -1;
  }

  //
  // Generate the profile file
  //
  Result = GenProfile (BinFile, Profile);
  if (Result != 0) {
    printf ("Error: Cannot generate the profile\n");
    fclose (BinFile);
    fclose (Profile);
    return -1;
  }

  //
  // Close the binary file and profile
  //
  fclose (BinFile);
  fclose (Profile);

  //
  // Done
  //
  return 0;
}

//
// Internal functions implementation
//

void
PrintUsage (
  void
  )
{
  printf (
    "Generate a profile file from binary. Version 0.1\n"
    "\n"
    "Usage: GenProfile <Binary File> <Profile>\n"
    "\n"
    );
}


void
WriteBlock (
  FILE        *Profile,
  long        Start,
  char        *Buffer,
  int         BufferSize
  )
{
  int   Index1;
  int   Index2;
  int   Size;

  //
  // Write the buffer one by one
  //
  for (Index1 = 0; Index1 < BufferSize; Index1 += 16) {
    //
    // Put at most 16 bytes in one line
    //
    if (BufferSize - Index1 > 16) {
      Size = 16;
    } else {
      Size = BufferSize - Index1;
    }

    //
    // Print start address, end address, data, ...
    //
    fprintf (Profile, "%08lx %08lx ", Start + Index1, Start + Index1 + Size - 1);

    for (Index2 = 0; Index2 < Size; Index2++) {
      fprintf (Profile, "%02x ", (unsigned char) Buffer[Index1 + Index2]);
    }

    fprintf (Profile, "\n");
  }

  //
  // Done
  //
}


int
GenProfile (
  FILE        *BinFile,
  FILE        *Profile
  )
{
  long  Position;
  char  Buffer[MAX_BUFFER_SIZE];
  int   BufferSize;

  Position = 0;

  //
  // While it is not end of file
  //
  for ( ; ; ) {
    //
    // Get a buffer
    //
    BufferSize = fread (Buffer, 1, MAX_BUFFER_SIZE, BinFile);
    if (BufferSize == 0) {
      break;
    }

    //
    // Write the buffer into profile
    //
    WriteBlock (Profile, Position, Buffer, BufferSize);
    Position += BufferSize;
  }

  //
  // Done
  //
  return 0;
}
