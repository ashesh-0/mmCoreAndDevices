// PROJECT:       Micro-Manager
// SUBSYSTEM:     MMCore
//
// DESCRIPTION:   Camera device instance wrapper
//
// COPYRIGHT:     University of California, San Francisco, 2014,
//                All Rights reserved
//
// LICENSE:       This file is distributed under the "Lesser GPL" (LGPL) license.
//                License text is included with the source distribution.
//
//                This file is distributed in the hope that it will be useful,
//                but WITHOUT ANY WARRANTY; without even the implied warranty
//                of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
//                IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//                CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//                INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES.
//
// AUTHOR:        Mark Tsuchida

#include "CameraInstance.h"


int CameraInstance::SnapImage() { RequireInitialized(); return GetImpl()->SnapImage(); }
const unsigned char* CameraInstance::GetImageBuffer() { RequireInitialized(); return GetImpl()->GetImageBuffer(); }
const unsigned char* CameraInstance::GetImageBuffer(unsigned channelNr) { RequireInitialized(); return GetImpl()->GetImageBuffer(channelNr); }
const unsigned int* CameraInstance::GetImageBufferAsRGB32() { RequireInitialized(); return GetImpl()->GetImageBufferAsRGB32(); }
unsigned CameraInstance::GetNumberOfComponents() const { RequireInitialized(); return GetImpl()->GetNumberOfComponents(); }

std::string CameraInstance::GetComponentName(unsigned component)
{
   RequireInitialized();
   DeviceStringBuffer nameBuf(this, "GetComponentName");
   int err = GetImpl()->GetComponentName(component, nameBuf.GetBuffer());
   ThrowIfError(err, "Cannot get component name at index " +
         ToString(component));
   return nameBuf.Get();
}

int unsigned CameraInstance::GetNumberOfChannels() const { RequireInitialized(); return GetImpl()->GetNumberOfChannels(); }

std::string CameraInstance::GetChannelName(unsigned channel)
{
   RequireInitialized();
   DeviceStringBuffer nameBuf(this, "GetChannelName");
   int err = GetImpl()->GetChannelName(channel, nameBuf.GetBuffer());
   ThrowIfError(err, "Cannot get channel name at index " + ToString(channel));
   return nameBuf.Get();
}

long CameraInstance::GetImageBufferSize() const { RequireInitialized(); return GetImpl()->GetImageBufferSize(); }
unsigned CameraInstance::GetImageWidth() const { RequireInitialized(); return GetImpl()->GetImageWidth(); }
unsigned CameraInstance::GetImageHeight() const { RequireInitialized(); return GetImpl()->GetImageHeight(); }
unsigned CameraInstance::GetImageBytesPerPixel() const { RequireInitialized(); return GetImpl()->GetImageBytesPerPixel(); }
unsigned CameraInstance::GetBitDepth() const { RequireInitialized(); return GetImpl()->GetBitDepth(); }
double CameraInstance::GetPixelSizeUm() const { RequireInitialized(); return GetImpl()->GetPixelSizeUm(); }
int CameraInstance::GetBinning() const { RequireInitialized(); return GetImpl()->GetBinning(); }
int CameraInstance::SetBinning(int binSize) { RequireInitialized(); return GetImpl()->SetBinning(binSize); }
void CameraInstance::SetExposure(double exp_ms) { RequireInitialized(); return GetImpl()->SetExposure(exp_ms); }
double CameraInstance::GetExposure() const { RequireInitialized(); return GetImpl()->GetExposure(); }
int CameraInstance::SetROI(unsigned x, unsigned y, unsigned xSize, unsigned ySize) { RequireInitialized(); return GetImpl()->SetROI(x, y, xSize, ySize); }
int CameraInstance::GetROI(unsigned& x, unsigned& y, unsigned& xSize, unsigned& ySize) { RequireInitialized(); return GetImpl()->GetROI(x, y, xSize, ySize); }
int CameraInstance::ClearROI() { RequireInitialized(); return GetImpl()->ClearROI(); }

/**
 * Queries if the camera supports multiple simultaneous ROIs.
 */
bool CameraInstance::SupportsMultiROI()
{
   RequireInitialized();
   return GetImpl()->SupportsMultiROI();
}

/**
 * Queries if multiple ROIs have been set (via the SetMultiROI method). Must
 * return true even if only one ROI was set via that method, but must return
 * false if an ROI was set via SetROI() or if ROIs have been cleared.
 */
bool CameraInstance::IsMultiROISet()
{
   RequireInitialized();
   return GetImpl()->IsMultiROISet();
}

/**
 * Queries for the current set number of ROIs. Must return zero if multiple
 * ROIs are not set (including if an ROI has been set via SetROI).
 */
int CameraInstance::GetMultiROICount(unsigned int& count)
{
   RequireInitialized();
   return GetImpl()->GetMultiROICount(count);
}

/**
 * Set multiple ROIs. Replaces any existing ROI settings including ROIs set
 * via SetROI.
 * @param xs Array of X indices of upper-left corner of the ROIs.
 * @param ys Array of Y indices of upper-left corner of the ROIs.
 * @param widths Widths of the ROIs, in pixels.
 * @param heights Heights of the ROIs, in pixels.
 * @param numROIs Length of the arrays.
 */
int CameraInstance::SetMultiROI(const unsigned int* xs, const unsigned int* ys,
      const unsigned* widths, const unsigned int* heights,
      unsigned numROIs)
{
   RequireInitialized();
   return GetImpl()->SetMultiROI(xs, ys, widths, heights, numROIs);
}

/**
 * Queries for current multiple-ROI setting. May be called even if no ROIs of
 * any type have been set. Must return length of 0 in that case.
 * @param xs (Return value) X indices of upper-left corner of the ROIs.
 * @param ys (Return value) Y indices of upper-left corner of the ROIs.
 * @param widths (Return value) Widths of the ROIs, in pixels.
 * @param heights (Return value) Heights of the ROIs, in pixels.
 * @param numROIs Length of the input arrays. If there are fewer ROIs than
 *        this, then this value must be updated to reflect the new count.
 */
int CameraInstance::GetMultiROI(unsigned* xs, unsigned* ys, unsigned* widths,
      unsigned* heights, unsigned* length)
{
   RequireInitialized();
   return GetImpl()->GetMultiROI(xs, ys, widths, heights, length);
}

int CameraInstance::StartSequenceAcquisition(long numImages, double interval_ms, bool stopOnOverflow) { RequireInitialized(); return GetImpl()->StartSequenceAcquisition(numImages, interval_ms, stopOnOverflow); }
int CameraInstance::StartSequenceAcquisition(double interval_ms) { RequireInitialized(); return GetImpl()->StartSequenceAcquisition(interval_ms); }
int CameraInstance::StopSequenceAcquisition() { RequireInitialized(); return GetImpl()->StopSequenceAcquisition(); }
int CameraInstance::PrepareSequenceAcqusition() { RequireInitialized(); return GetImpl()->PrepareSequenceAcqusition(); }
bool CameraInstance::IsCapturing() { RequireInitialized(); return GetImpl()->IsCapturing(); }

std::string CameraInstance::GetTags()
{
   RequireInitialized();
   // TODO Probably makes sense to deserialize here.
   // Also note the danger of limiting serialized metadata to MM::MaxStrLength
   // (CCameraBase takes no precaution to limit string length; it is an
   // interface bug).
   DeviceStringBuffer serializedMetadataBuf(this, "GetTags");
   GetImpl()->GetTags(serializedMetadataBuf.GetBuffer());
   return serializedMetadataBuf.Get();
}

void CameraInstance::AddTag(const char* key, const char* deviceLabel, const char* value) { RequireInitialized(); return GetImpl()->AddTag(key, deviceLabel, value); }
void CameraInstance::RemoveTag(const char* key) { RequireInitialized(); return GetImpl()->RemoveTag(key); }
int CameraInstance::IsExposureSequenceable(bool& isSequenceable) const { RequireInitialized(); return GetImpl()->IsExposureSequenceable(isSequenceable); }
int CameraInstance::GetExposureSequenceMaxLength(long& nrEvents) const { RequireInitialized(); return GetImpl()->GetExposureSequenceMaxLength(nrEvents); }
int CameraInstance::StartExposureSequence() { RequireInitialized(); return GetImpl()->StartExposureSequence(); }
int CameraInstance::StopExposureSequence() { RequireInitialized(); return GetImpl()->StopExposureSequence(); }
int CameraInstance::ClearExposureSequence() { RequireInitialized(); return GetImpl()->ClearExposureSequence(); }
int CameraInstance::AddToExposureSequence(double exposureTime_ms) { RequireInitialized(); return GetImpl()->AddToExposureSequence(exposureTime_ms); }
int CameraInstance::SendExposureSequence() const { RequireInitialized(); return GetImpl()->SendExposureSequence(); }
