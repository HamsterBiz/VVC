#include "TInputImage.h"

TInputImage::TInputImage(int width, int height, int amount_frame)
{
  width_ = width;
  height_ = height;
  amount_frame_ = amount_frame;
}

void TInputImage::ReadVideo()
{
  
  file_name_ = fopen("frame1_176x144.yuv", "rb");
  buffor.buf_ = (unsigned char*)malloc(width_ * height_ * 1.5 * sizeof(unsigned  char));
  editor.buf_ = (unsigned char*)malloc(width_ * height_ * 1.5 * sizeof(unsigned  char));

  int counter = 0;
  for (int f = 0; f < amount_frame_; f++)
  {
    fread(buffor.buf_, sizeof(unsigned char), (width_ * height_) * 1.5, file_name_);

    for (int j = 0; j < height_; j++)
    {
      for (int i = 0; i < width_; i++)
      {
        unsigned int y = buffor.buf_[j * width_ + i];
        unsigned int u = buffor.buf_[(j / 2) * (width_ / 2) + (i / 2) + (width_ * height_)];
        unsigned int v = buffor.buf_[(j / 2) * (width_ / 2) + (i / 2) + (width_ * height_) + ((width_ * height_) / 4)];
        cerr << "y: " << "buffor [ " << j * width_ + i << " ]" << endl;
        cerr << "u: " << "buffor [ " << (j / 2) * (width_ / 2) + (i / 2) + (width_ * height_) << " ]" << endl;
        cerr << "v: " << "buffor [ " << (j / 2) * (width_ / 2) + (i / 2) + (width_ * height_) + ((width_ * height_) / 4) << " ]" << endl;
        printf("Y: %d, u: %d, v: %d  ", y, u, v);
        cerr << endl;
        counter++;
        //  cin.get();
      }

    }
  }

  //fwrite(editor.buf_, sizeof(unsigned char), (width_ * height_) * 1.5, file_name_edit_);
  cerr << "counter: " << counter << endl;
  fclose(file_name_);
  free(buffor.buf_);
}
