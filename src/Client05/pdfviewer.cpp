#include "pdfviewer.h"

PdfViewer::PdfViewer(QWidget* parent) : QScrollArea(parent)
{
    this->setWidgetResizable(true);
    this->setAlignment(Qt::AlignCenter);
    this->setWidget( new QWidget() );

    this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOn );
    this->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );

    this->setMinimumSize( QSize(640, 480) );

    this->document = nullptr;
    this->currentPage = -1;
    this->zoom = 1.0;

    this->viewMode = ViewMode::singlePageView;
    this->layoutMode = LayoutMode::continuous;
}

void PdfViewer::documentLoad(const char * path)
{
    this->document = new DocumentWidget(path);
    this->document->documentLoad();

    if(this->document->pageCount() > 0)
        this->currentPage = 0;

    connect( this->verticalScrollBar(), SIGNAL( valueChanged(int) ), this, SLOT( renderPages() ) );

    this->reshapeView();
}

void PdfViewer::documentReload()
{
    if(this->document != nullptr)
        this->document->documentReload();
}



void PdfViewer::setViewMode(ViewMode viewMode)
{
    this->viewMode = viewMode;

    if(this->viewMode == ViewMode::bookView)
        this->layoutMode = LayoutMode::book;

    this->reshapeView();
}

void PdfViewer::setLayoutMode(LayoutMode layoutMode)
{
    this->layoutMode = layoutMode;

    if(this->layoutMode == LayoutMode::book)
        this->viewMode = ViewMode::bookView;

    this->reshapeView();
}

void PdfViewer::setZoom(double zoom)
{
    if( this->document == nullptr || this->document->isReady() == false )
        return;

    this->zoom = zoom;
    this->document->setZoom(zoom);

    this->pages.clear();
    this->renderedImages.clear();

    this->reshapeView();

    this->viewport()->update();
}

void PdfViewer::renderPages()
{
    if( this->document == nullptr || this->document->isReady() == false )
        return;

    if( this->document->pageCount() <= 0 )
        return;

    this->visiblePages.clear();

    QRectF viewRectangle = QRectF( QPoint( 0, this->verticalScrollBar()->value() ), viewport()->size() );
    double viewArea = viewRectangle.width() * viewRectangle.height();
    double coverage = 0;

    for( int page = 0; page < this->pages.count(); page++ )
    {
        QLabel* pageLabel = this->pages[ page ];
        QRectF pageRectangle = viewRectangle.intersected( pageLabel->geometry() );

        if( pageRectangle.isValid() )
        {
            this->visiblePages << page;
            double pageArea = pageRectangle.width() * pageRectangle.height();
            if( ( pageArea / viewArea ) > coverage )
            {
                this->currentPage = page;
                coverage = (pageArea / viewArea);
            }
        }
    }

    for ( int page : this->visiblePages )
    {
        if( this->renderedImages.value( page ).isNull() )
            this->renderedImages[ page ] = this->document->renderPageWidth( page, this->pages[ page ]->width() );

        if( page == this->currentPage )
        {
            QImage image = this->renderedImages[ page ].copy();
            QPainter imagePainter( &image );
            imagePainter.setPen( Qt::black );
            imagePainter.drawRect( QRectF( QPointF( 0, 0 ), this->pages[ page ]->size() - QSize( 1, 1 ) ) );
            imagePainter.end();
            this->pages.value( page )->setPixmap( QPixmap::fromImage( image ) );
        }
        else
        {
            this->pages.value( page )->setPixmap( QPixmap::fromImage( this->renderedImages[ page ] ) );
        }
    }

    int start = this->visiblePages.first() - 5;
    int stop = this->visiblePages.last() + 5;

    if( start < 0 ) start=0;
    if( stop >= this->document->pageCount() ) stop = this->document->pageCount() - 1;

    for( int page = start; page < this->visiblePages.first(); page++ )
    {
        if( this->renderedImages.value( page ).isNull() )
            this->renderedImages[ page ] = this->document->renderPageWidth( page, this->pages[ page ]->width() );
    }

    for( int page = stop; page < this->visiblePages.last(); page-- )
    {
        if( this->renderedImages.value( page ).isNull() )
            this->renderedImages[ page ] = this->document->renderPageWidth( page, this->pages[ page ]->width() );
    }

    for( int page = 0; page < this->pages.count(); page++ )
    {
        if( page < start || page > stop )
        {
            if( this->renderedImages.value( page ).isNull() == false )
                this->renderedImages.remove( page );
            this->pages.value( page )->clear();
        }
    }
}

void PdfViewer::reshapeView()
{
    if( this->document == nullptr || this->document->isReady() == false )
        return;

    this->pages.clear();
    this->renderedImages.clear();

    QWidget *viewWidget = new QWidget();
    QGridLayout *pageLayout = new QGridLayout();
    pageLayout->setSpacing(5);
    pageLayout->setContentsMargins(0,5,0,5);

    if( this->layoutMode == LayoutMode::continuous )
    {
        switch( this->viewMode )
        {
            case ViewMode::singlePageView :
                for( int page = 0; page < this->document->pageCount(); page++ )
                {
                    QSizeF pageSize = this->document->pageSize( page );
                    QLabel *pageLabel = new QLabel();

                    pageLabel->setFixedSize( pageSize.toSize() );
                    pageLayout->addWidget( pageLabel, page, 0 );
                    this->pages[ page ] = pageLabel;
                }
                break;

            case ViewMode::doublePageView :
                for( int page = 0; page < this->document->pageCount(); page++ )
                {
                    QSizeF pageSize = this->document->pageSize( page );
                    QLabel *pageLabel = new QLabel();

                    pageLabel->setFixedSize( pageSize.toSize() );
                    pageLayout->addWidget( pageLabel, page/2 , page%2 );
                    this->pages[ page ] = pageLabel;
                }
                break;

            case ViewMode::fitPageForWidth :
            {
                double width = viewport()->width() - style()->pixelMetric( QStyle::PM_ScrollBarExtent ) - 25;

                for( int page = 0; page < this->document->pageCount(); page++ )
                {
                    QSizeF pageSize = this->document->pageSize( page );
                    QLabel *pageLabel = new QLabel();
                    double height = pageSize.height() * width / pageSize.width();

                    pageLabel->setFixedSize( QSize( width, height ) );
                    pageLayout->addWidget( pageLabel, page, 0);
                    this->pages[ page ] = pageLabel;
                }
                break;
            }

            case ViewMode::fitPageForHeight :
            {
                double height = viewport()->height() - 10;

                for( int page = 0; page < this->document->pageCount(); page++ )
                {
                    QSizeF pageSize = this->document->pageSize( page );
                    QLabel *pageLabel = new QLabel();
                    double width = pageSize.width() * height / pageSize.height();

                    pageLabel->setFixedSize( QSize( width, height ) );
                    pageLayout->addWidget( pageLabel, page, 0 );
                    this->pages[ page ] = pageLabel;
                }
                break;
            }
        }
    }
    else if( this->layoutMode == LayoutMode::singlePage )
    {
        QLabel *page1 = new QLabel();
        QLabel *page2 = new QLabel();

        switch( this->viewMode )
        {
            case ViewMode::singlePageView:
            {
                QSizeF pageSize = this->document->pageSize( this->currentPage );

                page1->setFixedSize( pageSize.toSize() );
                pageLayout->addWidget(page1, 0, 0);
                break;
            }

            case ViewMode::fitPageForWidth:
            {
                QSizeF pageSize = this->document->pageSize( this->currentPage );
                double width = viewport()->width() - style()->pixelMetric( QStyle::PM_ScrollBarExtent ) - 25;
                double height = pageSize.height() * width / pageSize.width();

                page1->setFixedSize( QSize( width, height ) );
                pageLayout->addWidget( page1, 0, 0 );

                break;
            }
            case ViewMode::fitPageForHeight:
            {
                QSizeF pageSize = this->document->pageSize( this->currentPage );
                double height = viewport()->height() - 10;
                double width = pageSize.width() * height / pageSize.height();

                page1->setFixedSize( QSize( width, height ) );
                pageLayout->addWidget( page1, 0, 0 );

                break;
            }
            case ViewMode::doublePageView :
            {
                QSizeF pageSize = this->document->pageSize( this->currentPage );

                page1->setFixedSize( pageSize.toSize() );
                pageLayout->addWidget( page1 );

                if( this->currentPage + 1 < this->document->pageCount() )
                {
                    pageSize = this->document->pageSize( this->currentPage + 1 );
                    page2->setFixedSize( pageSize.toSize() );
                    pageLayout->addWidget( page2 );
                }

                break;
            }
        }
    }

    viewWidget->setLayout( pageLayout );
    this->setWidget( viewWidget );

    this->viewport()->update();
    this->renderPages();
}

bool PdfViewer::isPageVisible(int pageNumber)
{
    QRectF pageRect = this->pages[ pageNumber ]->rect();
    QRectF viewRect = QRectF( QPointF( 0, this->verticalScrollBar()->value() ), this->viewport()->size() );

    return viewRect.intersects( pageRect );
}

void PdfViewer::resizeEvent(QResizeEvent * resize)
{
    resize->accept();

    int width = resize->size().width() - style()->pixelMetric( QStyle::PM_ScrollBarExtent ) - 25;
    int height = resize->size().height() - style()->pixelMetric( QStyle::PM_ScrollBarExtent ) - 25;

    if( resize->oldSize() != resize->size() )
    {
        if( resize->oldSize().width() != resize->size().width() )
        {
            switch( this->viewMode )
            {
                case ViewMode::singlePageView :
                    this->setZoom( this->document->zoomWidth( 0, width ) );
                    break;
                case ViewMode::doublePageView :
                    this->setZoom( this->document->zoomWidth( 0, ( width - 5.0 )/2 ) );
                    break;
            }
        }

        if( resize->oldSize().height() != resize->size().height() )
        {
            if( this->viewMode == ViewMode::bookView )
            {
                this->setZoom( this->document->zoomHeight( 0, height / 2 ) );
            }
        }
        this->reshapeView();
    }

    viewport()->repaint();
}

void PdfViewer::wheelEvent(QWheelEvent * wheel)
{
    QScrollArea::wheelEvent( wheel );

    int position = this->verticalScrollBar()->value();
    int degrees = -wheel->delta() / 8;

    this->verticalScrollBar()->setValue( position + degrees * this->verticalScrollBar()->singleStep() );

    wheel->accept();

    viewport()->repaint();
}

void PdfViewer::on_ZoomIn()
{
    if( this->zoom >= 4.0 )
        return;

    if( this->viewMode == ViewMode::bookView )
        return;

    if( this->viewMode != ViewMode::doublePageView )
        this->viewMode = ViewMode::singlePageView;

    this->setZoom( this->zoom + 0.1 );
}

void PdfViewer::on_ZoomOut()
{
    if( this->zoom <= 0.1 )
        return;

    if( this->viewMode == ViewMode::bookView )
        return;

    if( this->viewMode != ViewMode::doublePageView )
        this->viewMode = ViewMode::singlePageView;

    this->setZoom( this->zoom - 0.1 );
}

void PdfViewer::keyPressEvent(QKeyEvent * key)
{
    if( this->viewMode == ViewMode::doublePageView )
    {
        if( key->key() == Qt::Key_Right )
        {
            if( this->currentPage + 2 < this->document->pageCount() )
                this->verticalScrollBar()->setValue( this->pages.value( this->currentPage + 1 )->geometry().top() -5 );
        }
        else if( key->key() == Qt::Key_Left )
        {
            if( this->currentPage - 2 >= 0 )
                this->verticalScrollBar()->setValue( this->pages.value( this->currentPage - 1 )->geometry().top() - 5 );
        }
    }
    else
    {
        switch( key->key() )
        {
            case Qt::Key_Right :
                if( this->currentPage + 1 < this->document->pageCount() )
                    this->verticalScrollBar()->setValue( this->pages.value( this->currentPage + 1 )->geometry().top() - 5 );
                if( this->layoutMode != LayoutMode::continuous )
                {
                    this->currentPage++;
                    this->reshapeView();
                }

                break;
            case Qt::Key_Left :
                if( this->currentPage - 1 >= 0 )
                    this->verticalScrollBar()->setValue( this->pages.value( this->currentPage - 1 )->geometry().top() - 5 );

                if( this->layoutMode != LayoutMode::continuous )
                {
                    this->currentPage--;
                    this->reshapeView();
                }

                break;
            case Qt::Key_Home :
                this->verticalScrollBar()->setValue( 0 );

                if( this->layoutMode != LayoutMode::continuous )
                {
                    this->currentPage = 0;
                    this->reshapeView();
                }

                break;
            case Qt::Key_End :
                this->verticalScrollBar()->setValue( this->widget()->height() );

                if( this->layoutMode != LayoutMode::continuous )
                {
                    this->currentPage = this->document->pageCount() - 1;
                    this->reshapeView();
                }

                break;
            default:
                QScrollArea::keyPressEvent( key );
        }
    }

    this->viewport()->update();
    key->accept();
}
