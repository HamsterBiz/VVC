#include "LoadFile.h"

LoadFile::LoadFile()
{
  buffer_y_ = nullptr;
  bufffer_u_ = nullptr;
  buffer_v_ = nullptr;
}

void LoadFile::Create(unsigned int width, unsigned int height)
{
  //przypisanie pamiêci
  buffer_y_ = (int*)malloc( width * height);
  bufffer_u_ = (int*)malloc( width * height >> 2);
  buffer_v_ = (int*)malloc( width * height >> 2);

  // ustawienie szerokosci i wysokosci
  width_ = width;
  height_ = height;
}

void LoadFile::CopyToPictureYuv(PictureFile* picture_file, unsigned int index_offset_cuy, unsigned int index_offset_buy, unsigned int part_depth, unsigned int part_index)
{
  CopyToPictureLuma(picture_file, index_offset_cuy, index_offset_buy, part_depth, part_index);
  copyToPictureChroma(picture_file, index_offset_cuy, index_offset_buy, part_depth, part_index);
}
