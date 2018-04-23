/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <stdio.h>
#include "cdk.h"


#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;

class BinaryFileHeader
{
public:

  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"a", "b", "c", "d", "e", "f"};
  const char 		*columnTitles[] = {"a", "b", "c", "d", "e", "f"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  //reads the header binary file
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
  binInfile.read( (char *)myHeader , sizeof(BinaryFileHeader));
  binInfile.close();

  /*
   * Dipslay a message
   */
  char Magic  [50];
  char Version [50];
  char NumRecords [50];
  sprintf(Magic,"%#X", myHeader->magicNumber);
  sprintf(Version,"%u",myHeader->versionNumber);
  sprintf(NumRecords, "%u", myHeader->numRecords);
  std::string box1 = std::string("Magic: ") + Magic;
  std::string box2 = std::string("Version: ") + Version;
  std::string box3 = std::string("NumRecords: ") + NumRecords;
  setCDKMatrixCell(myMatrix, 1, 1, box1.c_str());
  setCDKMatrixCell(myMatrix, 1, 2, box2.c_str());
  setCDKMatrixCell(myMatrix, 1, 3, box3.c_str());
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
