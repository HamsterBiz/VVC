#include "PictureFile.h"

PictureFile::PictureFile()
{
   buffer_y_picture_ = nullptr;
   bufffer_u_picture_ = nullptr;
   buffer_v_picture_ = nullptr;

   picture_y_ = nullptr;            ///< m_apiPicBufY + m_iMarginLuma*getStride() + m_iMarginLuma (m_piPicOrgY)
   picture_u_ = nullptr;
   picture_v_ = nullptr;
}

void PictureFile::Create(int picture_width, int picture_height, unsigned int max_width_of_coding_unit, unsigned int max_height_of_coding_unit, unsigned int max_depth_of_coding_unit)
{
  picture_width_ = picture_width;
  picture_height_ = picture_height;


  width_of_coding_unit_ = max_width_of_coding_unit;
  height_of_coding_unit_ = max_height_of_coding_unit;

  int numCuInWidth = picture_width_ / width_of_coding_unit_ + (picture_width_ % width_of_coding_unit_ != 0);
  int numCuInHeight = picture_height_ / height_of_coding_unit_ + (picture_height_ % height_of_coding_unit_ != 0);

  luma_margin_x_ = max_width_of_coding_unit + 16; // for 16-byte alignment
  luma_margin_y_ = max_height_of_coding_unit + 16;  // margin for 8-tap filter and infinite padding

  chroma_margin_x_ = luma_margin_x_ >> 1;
  chroma_margin_y_ = luma_margin_y_ >> 1;

  buffer_y_picture_ = (int*)malloc((picture_width_ + (luma_margin_x_ << 1)) * (picture_height_ + (luma_margin_y_ << 1)));
  bufffer_u_picture_ = (int*)malloc(((picture_width_ >> 1) + (chroma_margin_x_ << 1))* ((picture_height_ >> 1) + (chroma_margin_y_ << 1)));
  buffer_v_picture_ = (int*)malloc(((picture_width_ >> 1) + (chroma_margin_x_ << 1))* ((picture_height_ >> 1) + (chroma_margin_y_ << 1)));

  picture_y_ = buffer_y_picture_ + luma_margin_y_ * getStride() + luma_margin_x_;
  picture_u_ = bufffer_u_picture_ + chroma_margin_y_ * getCStride() + chroma_margin_x_;
  picture_v_ = buffer_v_picture_ + chroma_margin_y_ * getCStride() + chroma_margin_x_;

 // m_bIsBorderExtended = false;

  m_cuOffsetY = new int[numCuInWidth * numCuInHeight];
  m_cuOffsetC = new int[numCuInWidth * numCuInHeight];
  for (int cuRow = 0; cuRow < numCuInHeight; cuRow++)
  {
    for (int cuCol = 0; cuCol < numCuInWidth; cuCol++)
    {
      m_cuOffsetY[cuRow * numCuInWidth + cuCol] = getStride() * cuRow * height_of_coding_unit_ + cuCol * width_of_coding_unit_;
      m_cuOffsetC[cuRow * numCuInWidth + cuCol] = getCStride() * cuRow * (height_of_coding_unit_ / 2) + cuCol * (width_of_coding_unit_ / 2);
    }
  }

  m_buOffsetY = new int[(size_t)1 << (2 * max_depth_of_coding_unit)];
  m_buOffsetC = new int[(size_t)1 << (2 * max_depth_of_coding_unit)];
  for (int buRow = 0; buRow < (1 << max_depth_of_coding_unit); buRow++)
  {
    for (int buCol = 0; buCol < (1 << max_depth_of_coding_unit); buCol++)
    {
      m_buOffsetY[(buRow << max_depth_of_coding_unit) + buCol] = getStride() * buRow * (max_height_of_coding_unit >> max_depth_of_coding_unit) + buCol * (max_width_of_coding_unit >> max_depth_of_coding_unit);
      m_buOffsetC[(buRow << max_depth_of_coding_unit) + buCol] = getCStride() * buRow * (max_height_of_coding_unit / 2 >> max_depth_of_coding_unit) + buCol * (max_width_of_coding_unit / 2 >> max_depth_of_coding_unit);
    }
  }
  return;
}
