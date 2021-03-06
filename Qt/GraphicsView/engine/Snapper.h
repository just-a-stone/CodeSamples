#ifndef SNAPPER_H
#define SNAPPER_H

#include <QPointF>

class GraphicsSheet;

#ifdef EXP_SYMBOLS
class Q_DECL_EXPORT Snapper {
#else
class Q_DECL_IMPORT Snapper {
#endif

protected:
    GraphicsSheet* theView;

public:
	virtual ~Snapper();

	virtual void setView(GraphicsSheet* view);

	virtual QPointF snap(const QPointF& pos) = 0;
};


/**
 * This snapper does not snap at all. It just returns back the passed point.
 */
#ifdef EXP_SYMBOLS
class Q_DECL_EXPORT NoSnapper : public Snapper {
#else
class Q_DECL_IMPORT NoSnapper : public Snapper {
#endif

public:
    virtual QPointF snap(const QPointF& pos);
};


/**
 * This snapper calculates the nearest unit based position.
 * Its basically a rounding to the nearest integer - if the position
 * would be 1.3/3.5, then the result is 1/4
 */
#ifdef EXP_SYMBOLS
class Q_DECL_EXPORT UnitSnapper : public Snapper {
#else
class Q_DECL_IMPORT UnitSnapper : public Snapper {
#endif

public:
    virtual QPointF snap(const QPointF& pos);
};


/**
 * This snapper calculates the nearest grid based position.
 * It is similar to the UnitSnapper, but considers the scaling factor
 * of the drawing sheet. If the scale is 1:2, and the position
 * would be 1.3/3.5, then the result is 2/4 (since the smallest grid
 * is at positions 0, 2, 4, 6, ...)
 */
#ifdef EXP_SYMBOLS
class Q_DECL_EXPORT GridSnapper : public Snapper {
#else
class Q_DECL_IMPORT GridSnapper : public Snapper {
#endif

public:
    virtual QPointF snap(const QPointF& pos);
};


/**
 * This snapper calculates the nearest edge of any object within a specific range.
 * If no point is found nearby, the given fallback snapper is used.
 */
#ifdef EXP_SYMBOLS
class Q_DECL_EXPORT EdgeSnapper : public Snapper {
#else
class Q_DECL_IMPORT EdgeSnapper : public Snapper {
#endif

    Snapper* fallbackSnapper;

public:
    EdgeSnapper(Snapper* fallback = new NoSnapper());

    //  @Override
    virtual void setView(GraphicsSheet* view);

    // @Override
    virtual QPointF snap(const QPointF& pos);
};

#endif
