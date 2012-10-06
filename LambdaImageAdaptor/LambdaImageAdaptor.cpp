#include <iostream>

#include "itkImage.h"
#include "itkImageRegionIterator.h"

#include "itkLambdaImageAdaptor.h"

template <typename TImage>
static void CreateImage(TImage* const image);

int main(int argc, char** argv)
{
  // Create an image
  const unsigned int  Dimension = 2;
  typedef int                                  PixelType;
  typedef itk::Image< PixelType, Dimension >   ImageType;

  ImageType::Pointer image = ImageType::New();

  CreateImage(image.GetPointer());

  // A demo of converting to the same type of pixel
  {
    // Create a lambda
    auto myLambda = [](const ImageType::PixelType& pixel) {
        return pixel + 3;
     };

    // Create the adaptor
    typedef itk::LambdaImageAdaptor<  ImageType, int,
      decltype(myLambda) > LambdaAdaptorType;

    LambdaAdaptorType::Pointer adaptor = LambdaAdaptorType::New();
    adaptor->SetImage(image);
    adaptor->SetLambda(myLambda);

    // Output the result of applying the lambda to every pixel
    itk::ImageRegionIterator<LambdaAdaptorType>
    outputIterator(adaptor,adaptor->GetLargestPossibleRegion());

    while(!outputIterator.IsAtEnd())
    {
      std::cout << outputIterator.Get() << " ";
      ++outputIterator;
    }
    std::cout << std::endl;
  }

  // A demo of converting to a different type of pixel
  {
    // Create a lambda
    auto myLambda = [](const ImageType::PixelType& pixel) {
        return static_cast<float>(static_cast<float>(pixel) + 3.1f);
     };

    // Create the adaptor (we have to know that the lambda will return a float.
    typedef itk::LambdaImageAdaptor<  ImageType, float,
      decltype(myLambda) > LambdaAdaptorType;

    LambdaAdaptorType::Pointer adaptor = LambdaAdaptorType::New();
    adaptor->SetImage(image);
    adaptor->SetLambda(myLambda);

    // Output the result of applying the lambda to every pixel
    itk::ImageRegionIterator<LambdaAdaptorType>
    outputIterator(adaptor,adaptor->GetLargestPossibleRegion());

    while(!outputIterator.IsAtEnd())
    {
      std::cout << outputIterator.Get() << " ";
      ++outputIterator;
    }
    std::cout << std::endl;
  }

  return EXIT_SUCCESS;
}

template <typename TImage>
void CreateImage(TImage* const image)
{
  typename TImage::IndexType corner = {{0,0}};
  typename TImage::SizeType size = {{2,2}};
  typename TImage::RegionType region(corner,size);
  image->SetRegions(region);
  image->Allocate();
  unsigned int counter = 0;

  itk::ImageRegionIterator<TImage>
      imageIterator(image,image->GetLargestPossibleRegion());

  while(!imageIterator.IsAtEnd())
  {
    std::cout << counter << " ";
    imageIterator.Set(counter);
    counter++;
    ++imageIterator;
  }
  std::cout << std::endl;
}
