#ifndef PAINTCANVAS_HPP
#define PAINTCANVAS_HPP

#include <QActionGroup>
#include <QPaintEvent>
#include <QRect>
#include <QTransform>
#include <QtGui>
#include "../main/enums.hpp"

class AbstractTool;
class AbstractLayer;
class Document;
class FrameCache;

class PaintCanvas : public QWidget {
  Q_OBJECT;

public:
  PaintCanvas(QWidget *parent = 0);
  virtual ~PaintCanvas() {}

  QImage *editImage() const;
  void setEditImage(QImage image);
  QImage *frameImage() const;
  void setFrameImage(QImage &image);
  bool isPainting() const {
    return mIsPainting;
  }
  void setIsPainting(bool isPainting);
  QTransform transform() const {
    return mViewTransform;
  }
  void setViewTransform(QTransform transform);
  void setUserTransform(QTransform transform);

  ToolsEnums currentTool() const {
    return mCurrentTool;
  }
  void setCurrentTool(ToolsEnums tool) {
    mCurrentTool = tool;
  }
  const QActionGroup *toolActionGroup() const {
    return m_pToolActionGroup;
  }
  QAction *toolAction(ToolsEnums tool) const {
    return mToolActions[tool];
  }

  void refreshPixmap();
  void refreshPixmap(const QRect &);

public slots:
  void setDocument(Document *);
  void setCurrentFrame(int);
  void setCurrentLayer(AbstractLayer *);
  void refreshCurrentFrame();

protected:
  void resizeEvent(QResizeEvent *);
  void paintEvent(QPaintEvent *);
  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void tabletEvent(QTabletEvent *);

  QPoint posViewFromReal(QPoint);
  QPoint posRealFromView(QPoint);

  void viewTransformStart(QMouseEvent *);
  void viewTransform(QMouseEvent *);
  void viewTransformEnd(QMouseEvent *);

protected slots:
  void activateToolAction(QAction *);

private:
  void resetCenterTransform();
  void resetViewTransform();
  void resetUserTransform();
  void resetBufferImage();
  void drawCameraFrame();
  void setupToolHandlers();
  void setupShortcuts();

  ToolsEnums mCurrentTool;
  QVector<AbstractTool *> mToolHandlers;
  QVector<QAction *> mToolActions;
  QActionGroup *m_pToolActionGroup;
  QLineF *m_pCursorLine;

  Document *m_pDocument;
  FrameCache *m_pFrameCache;

  QPixmap mPixmap;
  QImage *m_pBufferImage, *m_pEditImage;
  QTransform mCenterTransform, mViewTransform, mUserTransform, mTempTransform;
  bool mIsPainting, mIsDragging;
  QPoint mDragOriginPos, mDragTempPos;
};

#endif /* PAINTCANVAS_HPP */
