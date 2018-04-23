/*
*
* Author: Carlos Esponda
* NetID; Cfe160030
* section: .502
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

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
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
  BinaryFileRecord *myRecord = new BinaryFileRecord();
  BinaryFileRecord *myRecord2 = new BinaryFileRecord();
  BinaryFileRecord *myRecord3 = new BinaryFileRecord();
  BinaryFileRecord *myRecord4 = new BinaryFileRecord();
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
  binInfile.read( (char *)myHeader , sizeof(BinaryFileHeader));
  binInfile.read( (char *)myRecord , sizeof(BinaryFileRecord));
  binInfile.read( (char *)myRecord2 , sizeof(BinaryFileRecord));
  binInfile.read( (char *)myRecord3 , sizeof(BinaryFileRecord));
  binInfile.read( (char *)myRecord4 , sizeof(BinaryFileRecord));
  binInfile.close();

  /*
   * Dipslay a message
   */
  char Magic  [50];
  char Version [50];
  char NumRecords [50];
  char strlen1 [50];
  char strlen2 [50];
  char strlen3 [50];
  char strlen4 [50];
  sprintf(Magic,"%#X", myHeader->magicNumber);
  sprintf(Version,"%u",myHeader->versionNumber);
  sprintf(NumRecords, "%u", myHeader->numRecords);
  sprintf(strlen1, "%u", myRecord->strLength);
  sprintf(strlen2, "%u", myRecord2->strLength);
  sprintf(strlen3, "%u", myRecord3->strLength);
  sprintf(strlen4, "%u", myRecord4->strLength);
  std::string box1 = std::string("Magic: ") + Magic;
  std::string box2 = std::string("Version: ") + Version;
  std::string box3 = std::string("NumRecords: ") + NumRecords;
  std::string box4 = std::string("strlen: ") + strlen1;
  std::string box7 = std::string("strlen: ") + strlen2;
  std::string box10 = std::string("strlen: ") + strlen3;
  std::string box13 = std::string("strlen: ") + strlen4;
  setCDKMatrixCell(myMatrix, 1, 1, box1.c_str());
  setCDKMatrixCell(myMatrix, 1, 2, box2.c_str());
  setCDKMatrixCell(myMatrix, 1, 3, box3.c_str());
  setCDKMatrixCell(myMatrix, 2, 1, box4.c_str());
  setCDKMatrixCell(myMatrix, 2, 2, myRecord->stringBuffer);
  setCDKMatrixCell(myMatrix, 3, 1, box7.c_str());
  setCDKMatrixCell(myMatrix, 3, 2, myRecord2->stringBuffer);
  setCDKMatrixCell(myMatrix, 4, 1, box10.c_str());
  setCDKMatrixCell(myMatrix, 4, 2, myRecord3->stringBuffer);
  setCDKMatrixCell(myMatrix, 5, 1, box13.c_str());
  setCDKMatrixCell(myMatrix, 5, 2, myRecord4->stringBuffer);
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
