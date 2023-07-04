#include "documentwidget.h"

DocumentWidget::DocumentWidget(const char* documentPath)
{
    this->zoom = 1.0;
    this->isLoaded = false;

    this->pathDocument = (char*)malloc(256);
    memset(this->pathDocument, 0, 256);
    strcpy(this->pathDocument, documentPath);
}

const char* DocumentWidget::documentName() const
{
    return QFileInfo( QString(this->pathDocument) ).baseName().toStdString().c_str();
}

const char* DocumentWidget::documentPath() const
{
    return QFileInfo( QString(this->pathDocument) ).absolutePath().toStdString().c_str();
}

int DocumentWidget::pageCount() const
{
    return this->pdfPages.count();
}

QSizeF DocumentWidget::pageSize(int pageNumber) const
{
    return this->pdfPages.at(pageNumber)->pageSizeF() * this->zoom;
}

void DocumentWidget::documentReload()
{
    this->isLoaded = false;
    this->pdfPages.clear();

    this->documentLoad();
}

QImage DocumentWidget::renderPage(int pageNumber) const
{
    return this->pdfPages.at( pageNumber )->renderToImage( DEFAULTWIDTH*this->zoom, DEFAULTHEIGHT*this->zoom );
}

QImage DocumentWidget::renderPageWidth(int pageNumber , double width ) const
{
    double zoom = zoomWidth( pageNumber, width );
    return this->pdfPages.at( pageNumber )->renderToImage( DEFAULTWIDTH*zoom, DEFAULTHEIGHT*zoom );
}

QImage DocumentWidget::renderPageHeight(int pageNumber, double height) const
{
    double zoom = zoomHeight( pageNumber, height);
    return this->pdfPages.at( pageNumber )->renderToImage( DEFAULTWIDTH*zoom, DEFAULTHEIGHT*zoom );
}

const char* DocumentWidget::pageText(int pageNumber) const
{
    return this->pdfPages.at( pageNumber )->text( QRectF() ).toStdString().c_str();
}

const char* DocumentWidget::text( int pageNumber, QRectF selectedRectangle ) const
{
    return this->pdfPages.at( pageNumber )->text( selectedRectangle ).toStdString().c_str();
}

double DocumentWidget::zoomWidth(int pageNumber, double width) const
{
    if( pageNumber>= this->pdfPages.count() )
        return 0.0;
    return 1.0 * width / this->pdfPages.at( pageNumber )->pageSizeF().width();
}

double DocumentWidget::zoomHeight(int pageNumber, double height) const
{
    if( pageNumber>= this->pdfPages.count() )
        return 0.0;
    return 1.0 * height / this->pdfPages.at( pageNumber )->pageSizeF().height();
}

void DocumentWidget::documentLoad()
{
    this->bookDocument = document::load( this->pathDocument );

    if( this->bookDocument == nullptr)
    {
        emit documentLoadFailed();
        return;
    }

    if( this->bookDocument->isLocked() == true)
    {
        emit documentLoadFailed();
        return;
    }

    this->bookDocument->setRenderHint( document::Antialiasing );
    this->bookDocument->setRenderHint( document::TextAntialiasing );
    this->bookDocument->setRenderHint( document::TextHinting );

    for( int page = 0; page < this->bookDocument->numPages(); page++)
    {
        this->pdfPages.append(this->bookDocument->page(page));
    }

    emit documentLoaded();

    this->isLoaded = true;
}












