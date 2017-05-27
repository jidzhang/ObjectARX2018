//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2017 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// Description:
//
// This file implements the class AcGeTorus, a reprsentation for a
// torus.  It is a surface generated by revolving a circular
// arc about an axis of symmetry, where the plane of the arc is a plane
// containing the axis of symmetry.  The torus is located in space by its
// origin which is a point on the axis of symetry.  The locus of the
// center of the circular arc is at a distance of majorRadius from
// the origin of the torus. The radius of the circular arc is the
// minorRadius.
// Parameter u is the longitude, which for a closed torus defaults
// to the range [-PI, PI).  Zero corresponds to the refAxis (which is
// a vector orthogonal to the axis of symetry).  Applying the right
// hand rule along the symetric axis defines the increasing direction
// for u.
// Parameter v parameterizes the circular arc (of revolution), which
// for a closed circle defaults to the range [-PI, PI).  Applying the
// right hand rule along the refAxis X symetricAxis defines the
// increasing direction for v.
// The torus is periodic in u, v with a period of 2PI.
// [umin, umax] x [vmin, vmax] defines a four sided toroidal patch bounded
// by four circular arcs. Following constraints apply to the definition
// of a toroidal patch.
// umin < umax and |umin - umax| <= 2PI.
// vmin < vmax and |vmin - vmax| <= 2PI
//

#ifndef AC_GETORUS_H
#define AC_GETORUS_H

#include "gegbl.h"
#include "gesurf.h"
#include "geintrvl.h"
#include "gevec3d.h"
#pragma pack (push, 8)


class AcGeCircArc3d;

class
GX_DLLEXPIMPORT
AcGeTorus : public AcGeSurface
{
public:
    AcGeTorus();
    AcGeTorus(double majorRadius, double minorRadius,
              const AcGePoint3d& origin, const AcGeVector3d& axisOfSymmetry);
    AcGeTorus(double majorRadius, double minorRadius,
              const AcGePoint3d&  origin, const AcGeVector3d& axisOfSymmetry,
              const AcGeVector3d& refAxis,
              double startAngleU, double endAngleU,
              double startAngleV, double endAngleV);
    AcGeTorus(const AcGeTorus& torus);

    // Geometric properties.
    //
    double          majorRadius    () const;
    double          minorRadius    () const;
    void            getAnglesInU   (double& start, double& end) const;
    void            getAnglesInV   (double& start, double& end) const;
    AcGePoint3d     center         () const;
    AcGeVector3d    axisOfSymmetry () const;
    AcGeVector3d    refAxis        () const;
    Adesk::Boolean  isOuterNormal  () const;

    AcGeTorus&      setMajorRadius (double radius);
    AcGeTorus&      setMinorRadius (double radius);
    AcGeTorus&      setAnglesInU   (double start, double end);
    AcGeTorus&      setAnglesInV   (double start, double end);
    AcGeTorus&      set            (double majorRadius, double minorRadius,
                                    const AcGePoint3d& origin,
                                    const AcGeVector3d& axisOfSymmetry);
    AcGeTorus&      set            (double majorRadius, double minorRadius,
                                    const AcGePoint3d&  origin,
                                    const AcGeVector3d& axisOfSymmetry,
                                    const AcGeVector3d& refAxis,
                                    double startAngleU, double endAngleU,
                                    double startAngleV, double endAngleV);
    // Assignment operator.
    //
    AcGeTorus&      operator =     (const AcGeTorus& torus);

    // Intersection with a linear entity
    //
    Adesk::Boolean  intersectWith  (const AcGeLinearEnt3d& linEnt, int& intn,
                                    AcGePoint3d& p1, AcGePoint3d& p2,
                                    AcGePoint3d& p3, AcGePoint3d& p4,
                                    const AcGeTol& tol = AcGeContext::gTol) const;


    // The following methods classify the shape according to the
    // relationship between the major and minor radii of the torus.
    // Exactly one of the first four functions should return TRUE
    // for any given torus.
    //
    Adesk::Boolean isLemon     () const;
    Adesk::Boolean isApple     () const;
    Adesk::Boolean isVortex    () const;
    Adesk::Boolean isDoughnut  () const;
    Adesk::Boolean isDegenerate() const;
    Adesk::Boolean isHollow    () const;
};

#pragma pack (pop)
#endif
