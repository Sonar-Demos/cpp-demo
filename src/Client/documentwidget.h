#ifndef DOCUMENTWIDGET_H
#define DOCUMENTWIDGET_H

#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <poppler/qt5/poppler-qt5.h>

#define DEFAULTWIDTH 72
#define DEFAULTHEIGHT 72

//typedefs used for ease of use
typedef Poppler::Page page;
typedef Poppler::Document document;

/**
 * @brief The DocumentWidget class
 * Contains the actual document with conversion to image functions
 */
class DocumentWidget : public QObject
{
    Q_OBJECT
public:
    /**
    * @brief DocumentWidget
    *
    * Constructor of the Document Widget window
    *
    * @param documentPath path to the opened temporary document
    */
   DocumentWidget(const char* documentPath = nullptr);

   /**
    * @brief documentReload
    *
    * Function called to realod the document in case of an error
    */
   void documentReload();

   /**
    * @brief setZoom
    *
    * Function that sets the zoom variable
    *
    * @param zoom given zoom value
    */
   inline void setZoom( double zoom ) { this->zoom = zoom; }

   /**
    * @brief isReady
    *
    * Function that returns whether the document is ready to be rendered
    *
    * @return Returns true if it is ready, false otherwise
    */
   inline bool isReady() const { return isLoaded; }

   /**
    * @brief documentName
    *
    * @return Returns the string containing the document name
    */
   const char* documentName() const;

   /**
    * @brief documentPath
    *
    * @return Returns the string containing the path of the document file
    */
   const char* documentPath() const;

   /**
    * @brief pageText
    *
    * @param pageNumber the number of the page for which the text is requested
    *
    * @return Address to the string containing the text on the pageNumber page
    */
   const char * pageText(int) const;

   /**
    * @brief text
    *
    * @param pageNumber the number of the page for which the text is requested
    * @param selectedRectangle the text area that is selected
    *
    * @return Address to the string containing the text selected in the selectedRectangle on the pageNumber page
    */
   const char * text ( int, QRectF ) const;

   /**
    * @brief pageCount
    *
    * @return the number of pages in the pdf
    */
   int pageCount() const;

   /**
    * @brief zoomWidth
    *
    * @param pageNumber the number of the rendered page
    * @param width the width requested to be set
    *
    * @return Returns the new zoom
    */
   double zoomWidth( int, double) const;

   /**
    * @brief zoomHeight
    *
    * @param pageNumber the number of the rendered page
    * @param height the height requested to be set
    *
    * @return Returns the new zoom
    */
   double zoomHeight( int, double) const;

   /**
    * @brief pageSize
    *
    * @param pageNumber the number of the rendered page
    *
    * @return Returns the size of the rendered page
    */
   QSizeF pageSize( int ) const;

   /**
    * @brief renderPage
    *
    * @param pageNumber the number of the page to be rendered
    *
    * @return Returns the pdf page into image format
    */
   QImage renderPage( int ) const;

   /**
    * @brief renderPageWidth
    *
    * @param pageNumber the number of the page to be rendered
    * @param width the width value to be fit to
    *
    * @return Returns the pdf page into image format, fit for width
    */
   QImage renderPageWidth( int, double) const;

   /**
    * @brief renderPageHeight
    *
    * @param pageNumber the number of the page to be rendered
    * @param height the height value to be fit to
    *
    * @return Returns the pdf page into image format, fit for height
    */
   QImage renderPageHeight( int, double) const;


signals:
   /**
     * @brief documentLoaded
     *
     * Function signals when a document has finished laoding
     */
    void documentLoaded();

    /**
     * @brief documentLoadFailed
     *
     * Function signals when a document failed to load
     */
    void documentLoadFailed();

public slots:

    /**
     * @brief documentLoad
     *
     * Function called to load the document
     */
    void documentLoad();

private:

    // address to the document object
    document *bookDocument;

    // list containing the pdf pages
    QList <page*> pdfPages;

    // path to the document
    char* pathDocument;

    // zoom value
    double zoom;

    // value indicating whether the document is loaded or not
    bool isLoaded;
};

#endif // DOCUMENTWIDGET_H
