#ifndef PDFVIEWER_H
#define PDFVIEWER_H

#include <QtCore>
#include <QtGui>

#include <QtWidgets>

#include "documentwidget.h"

/**
 * @brief PdfViewer Class widget
 * 
 */
class PdfViewer : public QScrollArea
{
    Q_OBJECT
private:

    // the address to the document widget
    DocumentWidget* document;

    // hash containing rendered pdf pages to image format
    QHash<int, QImage> renderedImages;

    // has containing the labels that act as an image container
    QHash<int, QLabel*> pages;

    // list containing the pages visible on screen
    QList<int> visiblePages;

    // zoom value
    double zoom;

    // value containing the current page on screen
    int currentPage;
    // value containing the view mode
    int viewMode;
    // value containing the layout mode
    int layoutMode;

    /**
     * @brief isPageVisible
     *
     * Function returns whether a rendered page is on screen by comparing their view areas
     *
     * @param pageNumber the requested rendered page
     *
     * @return Returns true if the page is on screen, false otherwise
     */
    bool isPageVisible( int );

    /**
     * @brief reshapeView
     *
     * Function called whenever the user resizes the window or changes layout/view mode
     */
    void reshapeView();

private slots:

    /**
     * @brief on_ZoomIn
     *
     * Function is called whenever user zooms in
     */
    void on_ZoomIn();

    /**
     * @brief on_ZoomOut
     *
     * Function is called whenever user zooms out
     */
    void on_ZoomOut();

    /**
     * @brief renderPages
     *
     * Function is called whenever other pages have to be rendered (out of view pages)
     */
    void renderPages();

protected:

    /**
     * @brief resizeEvent
     *
     * Overridden event that triggeres whenever the user resizes the window
     *
     * @param resize the address to the event that triggered the function
     */
    void resizeEvent( QResizeEvent* );

    /**
     * @brief wheelEvent
     *
     * Overridden event that triggeres whenever the user scrolls from the mousewheel
     *
     * @param wheel the address to the event that triggered the function
     */
    void wheelEvent( QWheelEvent* );

    /**
     * @brief keyPressEvent
     *
     * Overridden event that triggeres upon a key press
     *
     * @param key the address to the event that triggered the function
     */
    void keyPressEvent( QKeyEvent* );

public:

    /**
     * @brief The ViewMode enum
     *
     * Contains possible view modes
     */
    enum ViewMode{
        singlePageView,
        doublePageView,
        fitPageForWidth,
        fitPageForHeight,
        bookView
    };

    /**
     * @brief The LayoutMode enum
     *
     * Contains possible layout modes
     */
    enum LayoutMode{
        singlePage,
        continuous,
        book
    };

    /**
     * @brief PdfViewer
     *
     * Constructor of the PDF viewer widget
     *
     * @param parent address to the parent creator
     */
    PdfViewer(QWidget* parent);

    /**
     * @brief documentLoad
     *
     * Function loads a document from the path given
     *
     * @param path = path to the document requested for loading
     */
    void documentLoad( const char* );

    /**
     * @brief documentReload
     *
     * Functions reloads a document in case of failure
     */
    void documentReload();

    /**
     * @brief setViewMode
     *
     * Function switches the view mode
     *
     * @param viewMode enum variable that sets the viewmode requested
     */
    void setViewMode( ViewMode );

    /**
     * @brief setLayoutMode
     *
     * Function switches the layout mode
     *
     * @param layoutMode enum variable that sets the layoutmode requested
     */
    void setLayoutMode( LayoutMode );

    /**
     * @brief setZoom
     *
     * Function that sets the soom value and resizes the render
     *
     * @param zoom zoom value requested
     */
    void setZoom( double );

    /**
     * @brief getViewMode
     *
     * @return Returns the current active view mode
     */
    inline int getViewMode() const { return this->viewMode; }

    /**
     * @brief getLayoutMode
     *
     * @return Returns the current active layout mode
     */
    inline int getLayoutMode() const { return this->layoutMode; }

    /**
     * @brief getZoom
     *
     * @return Returns the current zoom value
     */
    inline double getZoom() const {return this->zoom; }
};

#endif // PDFVIEWER_H
