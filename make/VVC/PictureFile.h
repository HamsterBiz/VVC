#ifndef _PICTURE_FILE_H_
#define _PICTURE_FILE_H_

#include <cstdlib>
#include <assert.h>
#include <memory.h>

#ifdef __APPLE__
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif
class PictureFile
{
private:
  int* buffer_y_picture_; //m_apiPicBufY
  int* bufffer_u_picture_;
  int* buffer_v_picture_;

  int* picture_y_;            ///< m_apiPicBufY + m_iMarginLuma*getStride() + m_iMarginLuma (m_piPicOrgY)
  int* picture_u_;
  int* picture_v_;

  // ------------------------------------------------------------------------------------------------
  //  Parameter for general YUV buffer usage
  // ------------------------------------------------------------------------------------------------

  int   picture_width_;            ///< Width of picture    m_iPicWidth
  int   picture_height_;           ///< Height of picture

  int   width_of_coding_unit_;             ///< Width of Coding Unit (CU) m_iCuWidth
  int   height_of_coding_unit_;            ///< Height of Coding Unit (CU) m_iCuHeight

  int* m_cuOffsetY;
  int* m_cuOffsetC;
  int* m_buOffsetY;
  int* m_buOffsetC;

  int   luma_margin_x_;
  int   luma_margin_y_;
  int   chroma_margin_x_;
  int   chroma_margin_y_;
public:
  PictureFile();
  //
  void Create(int picture_width, int picture_height, unsigned int max_width_of_coding_unit, unsigned int max_height_of_coding_unit, unsigned int max_depth_of_coding_unit);
  //Get information
  int  getStride() { return (picture_width_)+(luma_margin_x_ << 1); }
  int   getCStride() { return (picture_width_ >> 1) + (chroma_margin_x_ << 1); }
};

#endif //_PICTURE_FILE_H_