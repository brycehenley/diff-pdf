
#ifndef _bmpviewer_h_
#define _bmpviewer_h_

#include <cairo/cairo.h>

#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/statbmp.h>
#include <wx/scrolwin.h>

// widget for comfortable viewing of a bitmap, with high-quality zooming
class BitmapViewer : public wxScrolledWindow
{
public:
    BitmapViewer(wxWindow *parent);

    // set the bitmap to be shown
    void Set(const wxImage& image);
    void Set(cairo_surface_t *surface);

    float GetZoom() const
    {
        return m_zoom_factor;
    }

    void SetZoom(float factor)
    {
        m_zoom_factor = factor;
        UpdateBitmap();
    }

    // sets the zoom value to "best fit" for current window size
    void SetBestFitZoom();

private:
    // update the content after some change (bitmap, zoom factor, ...)
    void UpdateBitmap();

private:
    wxStaticBitmap *m_content;
    wxImage m_orig_image;
    float m_zoom_factor;
};

#endif // _bmpviewer_h_