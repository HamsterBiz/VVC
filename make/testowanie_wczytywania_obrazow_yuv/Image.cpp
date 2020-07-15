#include "Image.h"

Image::Image(int width, int height, int amount_frame)
{
  width_ = width;
  height_ = height;
  //video_name_ = video_name;
  amount_frame_ = amount_frame;
  cerr << "1" << endl;
  
  //file_name_ = fopen("foreman_176x144_qcif.yuv", "rb");
}

void Image::ReadVideo()
{
  cerr << "1" << endl;
  file_name_ = fopen("foreman_176x144_qcif.yuv", "rb");
  file_name_edit_ = fopen("edycja_176x144.yuv", "rb");
  cerr << "1" << endl;
  buffor.buf_ = (unsigned char*)malloc(width_ * height_ * 1.5 * sizeof(unsigned  char));
  editor.buf_ = (unsigned char*)malloc(width_ * height_ * 1.5 * sizeof(unsigned  char));
 
  cerr << "1" << endl;
  int counter = 0;
  for (int f = 0; f < amount_frame_; f++)
  {
    cerr << "1" << endl;
    fread(buffor.buf_, sizeof(unsigned char), (width_ * height_) * 1.5, file_name_);
  
    cerr << "1" << endl;
    for (int j = 0; j < height_; j++)
    {
      for (int i = 0; i < width_; i++)
      {
        //buffor.buf_[0] = 5;
        unsigned int y = buffor.buf_[j * width_ + i];
        unsigned int u = buffor.buf_[(j / 2) * (width_ / 2) + (i / 2) + (width_ * height_)];
        unsigned int v = buffor.buf_[(j / 2) * (width_ / 2) + (i / 2) + (width_ * height_) + ((width_ * height_) / 4)];
        cerr << "y: " << "buffor [ " << j * width_ + i << " ]" << endl;
        cerr << "u: " << "buffor [ " << (j / 2) * (width_ / 2) + (i / 2) + (width_ * height_) << " ]" << endl;
        cerr << "v: " << "buffor [ " << (j / 2) * (width_ / 2) + (i / 2) + (width_ * height_) + ((width_ * height_) / 4) << " ]" << endl;
       printf("Y: %d, u: %d, v: %d  ", y, u, v);
        cerr << endl;
        counter++;
       //cin.get();
      }

    }
  }
  fread(editor.buf_, sizeof(unsigned char), (width_ * height_) * 1.5, file_name_edit_);
  for (int i = 0; i < 25341; i++)
  {
    editor.buf_[i] = 200;
  }
  for (int j = 0; j < height_; j++)
  {
    for (int i = 0; i < width_; i++)
    {
      // buffor.buf_[0] = 5;
      unsigned int y = editor.buf_[j * width_ + i];
      unsigned int u = editor.buf_[(j / 2) * (width_ / 2) + (i / 2) + (width_ * height_)];
      unsigned int v = editor.buf_[(j / 2) * (width_ / 2) + (i / 2) + (width_ * height_) + ((width_ * height_) / 4)];
      //  cerr << "y: " << "buffor [ " << j * width_ + i << " ]" << endl;
       // cerr << "u: " << "buffor [ " << (j / 2) * (width_ / 2) + (i / 2) + (width_ * height_) << " ]" << endl;
       // cerr << "v: " << "buffor [ " << (j / 2) * (width_ / 2) + (i / 2) + (width_ * height_) + ((width_ * height_) / 4) << " ]" << endl;
       // printf("Y: %d, u: %d, v: %d  ", y, u, v);
        //cerr << endl;
     // counter++;
       //cin.get();
    }

  }
  //fwrite(editor.buf_, sizeof(unsigned char), (width_ * height_) * 1.5, file_name_edit_);
  cerr <<"counter: "<<counter<< endl;
  fclose(file_name_);
  free(buffor.buf_);
  fclose(file_name_edit_);
  free(editor.buf_);
}
