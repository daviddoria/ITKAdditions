/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkLambdaImageAdaptor_h
#define __itkLambdaImageAdaptor_h

#include "itkImageAdaptor.h"
#include "vnl/vnl_math.h"

#include <functional>

namespace itk
{
namespace Accessor
{
/** \class LambdaPixelAccessor
 * \brief Give access to an arbitrary function of a value
 *
 * \ingroup ImageAdaptors
 * \ingroup ITKImageAdaptors
 */
template< class TInternalType, typename TExternalType, typename TLambda >
class ITK_EXPORT LambdaPixelAccessor
{
public:
  /** Required by ImageAdaptor. */
  typedef TInternalType InternalType;
  typedef TExternalType ExternalType;

  std::function<TExternalType(InternalType)> m_Lambda;

  void SetLambda(TLambda lambda)
  {
    m_Lambda = lambda;
  }

  inline TExternalType Get(const TInternalType & input) const
  { return m_Lambda( input ); }

};
} // end namespace Accessor

/** \class LambdaImageAdaptor
 * \brief Presents an image as being composed of an arbitrary function
 * of its pixels
 *
 * \ingroup ImageAdaptors
 * \ingroup ITKImageAdaptors
 */
template< class TImage, typename TExternalType, typename TLambda >
class ITK_EXPORT LambdaImageAdaptor:public
  ImageAdaptor< TImage,
                Accessor::LambdaPixelAccessor<
                  typename TImage::PixelType, TExternalType,
                  TLambda >   >
{
public:
  /** Standard class typedefs. */
  typedef LambdaImageAdaptor Self;
  typedef ImageAdaptor< TImage, Accessor::LambdaPixelAccessor<
                          typename TImage::PixelType, TExternalType,
                          TLambda > >  Superclass;

  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  typedef Accessor::LambdaPixelAccessor<
    typename TImage::PixelType, TExternalType,
    TLambda >  AccessorType;

  void SetLambda(TLambda lambda)
  {
    AccessorType accessor;
    accessor.SetLambda(lambda);
    Superclass::SetPixelAccessor(accessor);
  }

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(LambdaImageAdaptor, ImageAdaptor);
protected:
  LambdaImageAdaptor() {}
  virtual ~LambdaImageAdaptor() {}
private:
  LambdaImageAdaptor(const Self &); //purposely not implemented
  void operator=(const Self &);  //purposely not implemented
};
} // end namespace itk

#endif
