#ifndef _LOAD_FILE_H_
#define _LOAD_FILE_H_
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include <math.h>
#include "PictureFile.h"
class LoadFile
{
private:
  int* buffer_y_;
  int* bufffer_u_;
  int* buffer_v_;

  unsigned int width_;
  unsigned int height_;

public:
  LoadFile();
  ~LoadFile()=default;
  //zarzadzanie pamiecia-----------------
  void Create(unsigned int width, unsigned int height);
  //-------------------------------------
  //kopiowanie do buffora PictureFile
  void CopyToPictureYuv(PictureFile* picture_file, unsigned int index_offset_cuy, unsigned int index_offset_buy, unsigned int part_depth = 0, unsigned int part_index = 0);
  void CopyToPictureLuma(PictureFile* picture_file, unsigned int index_offset_cuy, unsigned int index_offset_buy, unsigned int part_depth = 0, unsigned int part_index = 0);
  void copyToPictureChroma(PictureFile* picture_file, unsigned int index_offset_cuy, unsigned int index_offset_buy, unsigned int part_depth = 0, unsigned int part_index = 0);
};

#endif //_LOAD_FILE_H_